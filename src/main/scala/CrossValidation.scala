import scalala.tensor.dense.{DenseVectorCol, DenseMatrix}


/**
 * Created with IntelliJ IDEA.
 * User: Sascha
 * Date: 22.04.12
 * Time: 15:56
 * To change this template use File | Settings | File Templates.
 */

object CrossValidation {
  def main(args : Array[String]) {

  }

  def crossValidate (data : DenseMatrix[Double]) = {

    val partitionsize = 10

    val datapackets = partitionize(data, partitionsize)

    def partitionize () = {
      for (i <- 0 to partitionsize)
      DenseMatrix.zeros[Double](data.numRows / partitionsize , data.numCols)
    }

    val X = DenseMatrix.zeros[Double](1,2)
    val y = DenseVectorCol.zeros[Double](2)

    for (i <- 0 to data.length) {
      LinearRegression.optimalBeta(X,y)
    }
  }

}
