import scala.io.Source
import scalala.scalar._;
import scalala.tensor.::;
import scalala.tensor.mutable._;
import scalala.tensor.dense._;
import scalala.tensor.sparse._;
import scalala.library.Library._;
import scalala.library.LinearAlgebra._;
import scalala.library.Statistics._;
import scalala.library.Plotting._;
import scalala.operators.Implicits._;

object LinearRegression {
  def main(args: Array[String]) {

    val (x,y) = matrixFromFile(args(0))

    val X = computeLinearFeatures(x)
  
   println("X cols: " + X.numCols )
    println("X rows: " + X.numRows )
    val beta = optimalBeta(X, y);
    
    println(" beta: "+beta)

    val z = generateTestDataZ(10)

    val newY = computeLinearFeatures(z) * beta

    println("newY: "+newY)

    val (quad_x, quad_y ) = matrixFromFile(args(1))
    val quad_beta = optimalBeta(computeQuadraticFeatures(quad_x), quad_y)

    println("quad_beta: " + quad_beta)

    val (quad2_x, quad2_y ) = matrixFromFile(args(2))
    val quad2_beta = optimalBeta(computeQuadraticFeatures(quad2_x), quad2_y)

    println("quad2_beta: " + quad2_beta)

  }

  /**
   * Reads data from a file where the last entry in a line is considered
   * the expected value.
   * @param file
   * @return a tuple of a matrix and a result vector
   */
  def matrixFromFile(file: String) = {
    
    val lines = Source.fromFile(file).mkString.split("\n")

    // initialise Matrices
    val x = DenseMatrix.zeros[Double](lines.length, lines(0).trim.split(" ").length - 1);
    val y = DenseVectorCol.zeros[Double](lines.length)

    // fill Matrix with values
    for (i <- (0 until lines.length)) {
      val split = lines(i).trim.split(" ")
      for (j <- 0 until split.length) {
        if (j < split.length - 1) {
          x(i, j) = split(j).toDouble
        } else {
          y(i) = split(j).toDouble
        }
      }
    }

    (x, y)
  }

  /**
   * This method prepends the Matrix with a (1, .. ,1).transposed Vector.
   */
  def computeLinearFeatures(x: DenseMatrix[Double]) = {

	  prependOne(x)
	  
  }

  def computeQuadraticFeatures(x: DenseMatrix[Double]) = {

    // dimensions from folie 8/20
    val newX = DenseMatrix.zeros[Double](x.numRows, x.numCols + (x.numCols * (x.numCols + 1)) / 2)

    newX( :: , 0 until x.numCols) := x

    for (row <- 0 until x.numRows) {
      var index = 0
      for (i <- 0 until x.numCols){
        for (j <- i until x.numCols){
          newX(row, x.numCols + index) = x(row, i) * x(row,j)
          index += 1
        }
      }
    }

    prependOne(newX)
  }

  def prependOne(x: DenseMatrix[Double]) = {
    val newX = DenseMatrix.zeros[Double](x.numRows, x.numCols + 1)

    newX(:: , 0) := 1
    newX(:: , 1 to (x.numCols) ) := x

    newX
  }
  
  def optimalBeta(X : DenseMatrix[Double], y : DenseVectorCol[Double]) = {
    
    val beta = ( inv( X.t * X ) * X.t) * y
    
    beta
  }

  def generateTestDataZ(i : Int) = {
    val m = DenseMatrix.zeros[Double](i * i , 2)

    for (x1 <- 0 until i) {
      for (x2 <- 0 until i) {
        m(x1*i + x2, 0) = x1
        m(x1*i + x2, 1) = x2
      }
    }

    m
  }
}

abstract class LinearRegression {
  val x: DenseMatrix[Double]

}

