import theano
import numpy as np
import tensorflow.compat.v1 as tf

##条件随机场CRF
num_examples = 10
num_words = 20
num_features = 100
num_tags = 5
x = np.random.rand(num_examples, num_words, num_features).astype(np.float32)
#构建随机tag
y = np.random.randint(num_tags, size=[num_examples, num_words]).astype(np.int32)
#获取样本句长向量
sequence_lengths = np.full(num_examples, num_words - 1, dtype=np.int32)

with tf.Graph().as_default():
    with tf.compat.v1.Session() as session:
        x_t = tf.constant(x)
        y_t = tf.constant(y)
        sequence_lengths_t = tf.constant(sequence_lengths)
        #设置一个无偏置的线性层
        weights = tf.get_variable("weights", [num_features, num_tags])
        matricized_x_t = tf.reshape(x_t, [-1, num_features])
        matricized_unary_scores = tf.matmul(matricized_x_t, weights)
        unary_scores = tf.reshape(matricized_unary_scores, [num_examples, num_words, num_tags])
        #计算log-likelihood并获得转移矩阵
        log_likelihood, transition_params = tf.contrib.crf.crf_log_likelihood(unary_scores, y_t, sequence_lengths)
        #维特比算法解码，获得解码后的序列
        viterbi_sequence, viterbi_score = tf.contrib.crf.crf_decode(unary_scores, transition_params, sequence_lengths_t)

        loss = tf.reduce_mean(-log_likelihood)
        train_op = tf.train.GradientDescentOptimizer(0.01).minimize(loss)
        session.run(tf.global_variables_initializer())
        mask = (np.expand_dims(np.arange(num_words), axis=0) < np.expand_dims(sequence_lengths, axis=1))
        total_labels = np.sum(sequence_lengths)

        for i in range(1000):
            tf_viterbi_sequence, _ = session.run([viterbi_sequence, train_op])
            if i % 100 == 0:
                correct_labels = np.sum((y == tf_viterbi_sequence) * mask)
                accuracy = 100.0 * correct_labels / float(total_labels)
                print("Accuracy: %.2f%%" % accuracy)