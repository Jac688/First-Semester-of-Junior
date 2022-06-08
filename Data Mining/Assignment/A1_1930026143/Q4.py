import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

height = [180, 183, 176, 168, 174, 170, 180, 179, 175]
weight = [73, 75, 70, 60, 65, 59, 78, 80, 75]

print(pd.DataFrame(height).describe())
print(pd.DataFrame(weight).describe())

# 1
data1 = {
    'height': height,
}
data2 = {
    'weight': weight,
}
df1 = pd.DataFrame(data1)
df2 = pd.DataFrame(data2)

df1.plot.box(title="Box plots of the height")
plt.grid(linestyle="--", alpha=0.5)
df2.plot.box(title="Box plots of the weight")
plt.grid(linestyle="--", alpha=0.5)
plt.show()

# 2
plt.scatter(df1, df2)
plt.show()
corr = np.corrcoef(height, weight)
print("The correlation coefficient: ")
print(corr)

# 3
data = {    
    'height': height,
    'weight': weight
}

print(data)
