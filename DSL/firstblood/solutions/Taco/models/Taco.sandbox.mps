<?xml version="1.0" encoding="UTF-8"?>
<model ref="r:321cfd63-698a-47dc-9571-a7e1c5a41441(Taco.sandbox)">
  <persistence version="9" />
  <languages>
    <use id="3b690b42-594e-46b6-b96f-f010313cf097" name="Tortilla" version="-1" />
  </languages>
  <imports>
    <import index="vhg0" ref="r:de64978b-2a7e-4d90-8aaf-bcaca0c67ca7(Tortilla.colors)" implicit="true" />
  </imports>
  <registry>
    <language id="ceab5195-25ea-4f22-9b92-103b95ca8c0c" name="jetbrains.mps.lang.core">
      <concept id="1169194658468" name="jetbrains.mps.lang.core.structure.INamedConcept" flags="ng" index="TrEIO">
        <property id="1169194664001" name="name" index="TrG5h" />
      </concept>
    </language>
    <language id="3b690b42-594e-46b6-b96f-f010313cf097" name="Tortilla">
      <concept id="863668800269686594" name="Tortilla.structure.Shape" flags="ng" index="2wls_K">
        <child id="653786840141608444" name="color" index="34po9m" />
      </concept>
      <concept id="863668800269686595" name="Tortilla.structure.Circle" flags="ng" index="2wls_L">
        <property id="863668800269686598" name="radius" index="2wls_O" />
        <property id="863668800269686596" name="x" index="2wls_Q" />
        <property id="863668800269686597" name="y" index="2wls_R" />
      </concept>
      <concept id="863668800269686599" name="Tortilla.structure.Square" flags="ng" index="2wls_P">
        <property id="863668800269686602" name="size" index="2wls_S" />
        <property id="863668800269686600" name="upperLeftX" index="2wls_U" />
        <property id="863668800269686601" name="upperLeftY" index="2wls_V" />
      </concept>
      <concept id="863668800269686603" name="Tortilla.structure.Canvas" flags="ng" index="2wls_T">
        <child id="863668800269686608" name="shapes" index="2wls_y" />
      </concept>
      <concept id="653786840141608427" name="Tortilla.structure.ColorReference" flags="ng" index="34po91">
        <reference id="653786840141608428" name="target" index="34po96" />
      </concept>
    </language>
  </registry>
  <node concept="2wls_T" id="JWnzaFEwqV">
    <property role="TrG5h" value="A" />
    <node concept="2wls_L" id="JWnzaFEwqW" role="2wls_y">
      <property role="2wls_Q" value="10" />
      <property role="2wls_R" value="20" />
      <property role="2wls_O" value="30" />
      <node concept="34po91" id="$iHUFdu3IS" role="34po9m">
        <ref role="34po96" to="vhg0:$iHUFdtNnE" resolve="green" />
      </node>
    </node>
    <node concept="2wls_P" id="JWnzaFEwr2" role="2wls_y">
      <property role="2wls_U" value="100" />
      <property role="2wls_V" value="200" />
      <property role="2wls_S" value="50" />
      <node concept="34po91" id="$iHUFdu3IU" role="34po9m">
        <ref role="34po96" to="vhg0:$iHUFdtNnD" resolve="yellow" />
      </node>
    </node>
  </node>
</model>

