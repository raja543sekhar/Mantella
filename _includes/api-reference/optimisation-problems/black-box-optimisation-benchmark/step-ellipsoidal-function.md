<div class="custom-callout custom-callout-info">
#### Inheritance

Extends the black-box optimisation benchmark base class
</div>

**Objective function:**

$$\begin{align}
F(X) &:=  0.1 \max\left( \frac{\left| Z_1 \right|}{10000}, T_\text{conditioning}^{100} \cdot Q \cdot \tilde{Z} \right)\\
Z &:= T_\text{conditioning}^\sqrt{10} \cdot X \\
\tilde{Z} &:= \begin{cases}
\left\lfloor 0.5 + Z_i\right\rfloor & \text{if } Z_i > 0.5\\
\frac{\left\lfloor 0.5 + 10Z_i\right\rfloor}{10} & \text{otherwise}\\
\end{cases}\\
Q &:= \text{Some rotation matrix.}
\end{align}$$

**Soft-constraints function:**

$$C(X) := F_\text{penality}(X)$$

<div class="custom-callout custom-callout-info">
#### Default values

The default values are set as specified by the black box optimisation benchmark.

- The parameter space translation \\(X_T\\) is randomly and uniformly chosen from \\([-4, 4]^N\\), rounded up to 4 decimal places. If the translation of a dimension would be zero, it is set to -0.00001 instead.
- The parameter space rotation \\(X_R\\) is set to a randomly and uniformly chosen rotation matrix.
- \\(Q\\) is set to a randomly and uniformly chosen rotation matrix.
</div>

Example code, sampling and plotting of the step ellipsoidal function.

Create a new source file called **bbob_step_ellipsoidal_function.cpp**:
{% highlight cpp %}
{% include {{ api_reference_folder }}/_examples/bbob_step_ellipsoidal_function.cpp %}
{% endhighlight %}

Compilation and execution:
{% highlight bash %}
{% include {{ api_reference_folder }}/_examples/bbob_step_ellipsoidal_function.core.sh %}
{% endhighlight %}

Visualisation of the sampled function, using Matlab:
{% highlight matlab %}
{% include {{ api_reference_folder }}/_examples/bbob_step_ellipsoidal_function.m %}
{% endhighlight %}

![Sampling of the step ellipsoidal function - surface plot]({{ site.baseurl }}/assets/images/{{ api_reference_folder }}/bbob_step_ellipsoidal_function_surface.png)
![Sampling of the step ellipsoidal function - contour plot]({{ site.baseurl }}/assets/images/{{ api_reference_folder }}/bbob_step_ellipsoidal_function_contour.png)

---
- Constructor<br>
  {% include reference prefix=include.anchor_prefix name="StepEllipsoidalFunction" %}
- Parameterisation<br>
  {% include reference prefix=include.anchor_prefix name="setParameterRotationQ" %}
- Miscellaneous<br>
  {% include reference prefix=include.anchor_prefix name="toString" %}
  
{% include label prefix=include.anchor_prefix name="StepEllipsoidalFunction" %}
**StepEllipsoidalFunction( <small>unsigned int</small> N )** {% include continuous-only %}

- Creates an *N*-dimensional optimisation problem instance of this class.
- **Requirement:** The dimension *N* must be greater than or equal to 2.

---
{% include label prefix=include.anchor_prefix name="setParameterRotationQ" %}
**<small>void</small> .setParameterRotationQ( <small>arma::Mat&lt;double&gt;</small> Q )**

- Parameterises the rotation by \\(Q\\).
- **Requirement:** The number of rows and columns in *Q* must each match the problem dimension.
- **Requirement:** *Q* must be square, orthonormal (\\(Q^{t} = Q^{-1}\\)) and its determinant equal be to 1 or -1.

---
{% include label prefix=include.anchor_prefix name="toString" %}
**<small>std::string</small> .toString()** {% include noexcept %}

- Returns a filesystem friendly name of the problem, e.g. *bbob_step_ellipsoidal_function*.

