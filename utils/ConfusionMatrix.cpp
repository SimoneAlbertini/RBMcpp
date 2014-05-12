/* 
 * File:   ConfusionMatrix.cpp
 * Author: Simone Albertini
 * 
 * albertini.simone@gmail.com
 * http://www.dicom.uninsubria.it/~simone.albertini/
 * 
 */

#include "ConfusionMatrix.h"

namespace artelab
{

    ConfusionMatrix::ConfusionMatrix() {}

    ConfusionMatrix::ConfusionMatrix(int num_classes) 
    {
        matrix.create(num_classes, num_classes, CV_32S);
        matrix.setTo(cv::Scalar(0));
    }

    ConfusionMatrix::ConfusionMatrix(const ConfusionMatrix& orig) 
    {
        *this = orig;
    }

    ConfusionMatrix::~ConfusionMatrix() {}

    ConfusionMatrix& ConfusionMatrix::operator =(const ConfusionMatrix& other)
    {
        this->matrix = other.matrix;
        return *this;
    }

    void ConfusionMatrix::reset() 
    {
        matrix.create(matrix.rows, matrix.cols, CV_32S);
        matrix.setTo(cv::Scalar(0));
    }

    int ConfusionMatrix::num_classes()
    {
        return matrix.rows;
    }

    void ConfusionMatrix::add(int actual_class, int truth_class)
    {
        matrix.at<int>(actual_class, truth_class)++;
    }

    void ConfusionMatrix::add(cv::Mat classification, cv::Mat truth)
    {
        CV_Assert(classification.rows == truth.rows);

        classification.convertTo(classification, CV_32S);
        truth.convertTo(truth, CV_32S);

        for(int i=0; i < classification.rows; i++)
        {
            int cl = classification.at<int>(i, 0);
            int tr = truth.at<int>(i, 0);
            matrix.at<int>(cl, tr)++;
        }
    }

    double ConfusionMatrix::overall_accuracy()
    {
        double corrects = cv::trace(matrix)[0];
        double total = cv::sum(matrix)[0];

        return corrects / total;
    }

    double ConfusionMatrix::precision(int cl)
    {
        double tp = matrix.at<int>(cl, cl);
        double producer = cv::sum(matrix.row(cl))[0];
        return tp / producer;
    }

    double ConfusionMatrix::recall(int cl)
    {
        double tp = matrix.at<int>(cl, cl);
        double user = cv::sum(matrix.col(cl))[0];
        return tp / user;
    }

    double ConfusionMatrix::fmeasure(int cl)
    {
        double p = precision(cl);
        double r = recall(cl);

        return 2 * p * r / (p + r);
    }

    double ConfusionMatrix::true_negative_rate(int cl)
    {
        double tn = 0;
        for(int r=0; r < matrix.rows; r++)
            for(int c=0; c < matrix.cols; c++)
                if(r != cl && c != cl)
                    tn += matrix.at<int>(r,c);

        double xx = tn + cv::sum(matrix.col(cl))[0] - matrix.at<int>(cl, cl);

        return tn / xx;
    }

    double ConfusionMatrix::kappa()
    {
        double pc = 0;
        for(int i=0; i < matrix.rows; i++)
        {
            double r_sum = cv::sum(matrix.row(i))[0];
            double c_sum = cv::sum(matrix.col(i))[0];
            pc += r_sum * c_sum;
        }
        pc /= pow(cv::sum(matrix)[0], 2);

        return (overall_accuracy() - pc) / (1 - pc);
    }

    int ConfusionMatrix::total_data()
    {
        return cv::saturate_cast<int>(cv::sum(matrix)[0]);
    }

    int ConfusionMatrix::total_truth(int cl)
    {
        return cv::saturate_cast<int>(cv::sum(matrix.col(cl))[0]);
    }

    int ConfusionMatrix::tp(int cl)
    {
        return matrix.at<int>(cl, cl);
    }

}