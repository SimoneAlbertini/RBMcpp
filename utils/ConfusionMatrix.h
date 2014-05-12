/* 
 * File:   ConfusionMatrix.h
 * Author: Simone Albertini
 * 
 * albertini.simone@gmail.com
 * http://www.dicom.uninsubria.it/~simone.albertini/
 * 
 */

#ifndef CONFUSIONMATRIX_H
#define	CONFUSIONMATRIX_H

#include <opencv2/core/core.hpp>

namespace artelab
{

    class ConfusionMatrix 
    {
    public:
        ConfusionMatrix();
        ConfusionMatrix(int num_classes);
        ConfusionMatrix(const ConfusionMatrix& orig);
        virtual ~ConfusionMatrix();

        ConfusionMatrix& operator=(const ConfusionMatrix& other);

        void add(int actual_class, int truth_class);
        void add(cv::Mat classification, cv::Mat truth);

        double precision(int cl);
        double recall(int cl);
        double fmeasure(int cl);
        double true_negative_rate(int cl);
        double kappa();
        double overall_accuracy();

        int total_data();
        int total_truth(int cl);
        int tp(int cl);

        void reset();
        int num_classes();

        cv::Mat matrix;

    private:


    };

}

#endif	/* CONFUSIONMATRIX_H */

