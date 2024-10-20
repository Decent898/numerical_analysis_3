from manim import *
import numpy as np

class GaussianEliminationSolver(Scene):
    def gaussian_elimination(self, A):
        """ Perform Gaussian elimination on matrix A and return intermediate steps """
        n = len(A)
        steps = []
        for i in range(n):
            # Make the diagonal element 1
            if A[i][i] != 0:
                A[i] = A[i] / A[i][i]
            steps.append(A.copy())

            # Make the elements below the pivot in column i to be 0
            for j in range(i + 1, n):
                if A[j][i] != 0:
                    A[j] = A[j] - A[j][i] * A[i]
            steps.append(A.copy())
        
        # Perform back substitution to ensure upper triangular form
        for i in range(n - 1, -1, -1):
            for j in range(i - 1, -1, -1):
                A[j] = A[j] - A[j][i] * A[i]
            steps.append(A.copy())

        return steps

    def construct(self):
        # User input for the matrix
        matrix_str = input("Please enter the matrix rows, separated by commas. (e.g., 2,1,-1,8;-3,-1,2,-11;-2,1,2,-3):\n")
        A = self.parse_matrix_input(matrix_str)

        # Perform Gaussian elimination and get steps
        steps = self.gaussian_elimination(A)

        # Display each step
        for idx, step in enumerate(steps):
            matrix = MathTex(self.matrix_to_tex(step))
            matrix.set(width=6)  # Set fixed width for all matrices
            self.play(Write(matrix))
            self.wait()
            self.play(FadeOut(matrix))

        # Final solution text
        end_text = Text("Gaussian Elimination completed")
        self.play(Write(end_text))
        self.wait()

    def parse_matrix_input(self, matrix_str):
        """ Convert user input string to a NumPy array """
        rows = matrix_str.split(';')
        matrix = [list(map(float, row.split(','))) for row in rows]
        return np.array(matrix)

    def matrix_to_tex(self, matrix):
        """ Convert numpy matrix to LaTeX bmatrix string """
        matrix_tex = r"\begin{bmatrix}"
        rows, cols = matrix.shape
        for i in range(rows):
            row_tex = " & ".join([f"{matrix[i, j]:.2f}" for j in range(cols)])
            matrix_tex += row_tex
            if i < rows - 1:
                matrix_tex += r" \\ "
        matrix_tex += r"\end{bmatrix}"
        return matrix_tex
