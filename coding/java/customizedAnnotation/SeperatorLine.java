package customizedAnnotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;


/**
Meta-Annotations
Meta annotations are actually annotations being used by annotations.

@Target – specifies the type pf element this annotation is attached to.
		ElementType.TYPE-can be applied to any element of a class
		ElementType.FIELD-can be applied to a field or property
		ElementType.METHOD-can be applied to a method level annotation
		ElementType.PARAMETER-can be applied to the parameters of a method
		ElementType.CONSTRUCTOR-can be applied to constructors
		ElementType.LOCAL_VARIABLE-can be applied to local variables
		ElementType.ANNOTATION_TYPE-indicates that the declared type itself is an annotation type

@Retention – specifies the retention level of this annotation.
		RetentionPolicy.SOURCE—Retained only at the source level and will be ignored by the compiler
		RetentionPolicy.CLASS—Retained by the compiler at compile time, but will be ignored by the VM
		RetentionPolicy.RUNTIME—Retained by the VM so they can be read only at run-time

@Documented – by default annotations are mentioned in java doc, this 
			  meta-annotation will make this annotation to be mentioned.
			  
@Inherited – Indicates that the annotation will automatically be 
             inherited (take a look at the example attached to this post).

*/

@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
public @interface SeperatorLine {
	boolean value() default true;
}
