<?xml version="1.0" encoding="UTF-8"?>
<model ref="r:3180398c-552f-4226-a34c-a00e166902fa(main@generator)">
  <persistence version="9" />
  <languages>
    <devkit ref="a2eb3a43-fcc2-4200-80dc-c60110c4862d(jetbrains.mps.devkit.templates)" />
  </languages>
  <imports>
    <import index="4707" ref="r:4b93e23c-85d5-42ff-b8c1-3edc1281dd68(Tortilla.structure)" />
    <import index="dxuu" ref="6354ebe7-c22a-4a0f-ac54-50b52ab9b065/java:javax.swing(JDK/)" />
    <import index="z60i" ref="6354ebe7-c22a-4a0f-ac54-50b52ab9b065/java:java.awt(JDK/)" />
    <import index="tpck" ref="r:00000000-0000-4000-0000-011c89590288(jetbrains.mps.lang.core.structure)" />
    <import index="tpee" ref="r:00000000-0000-4000-0000-011c895902ca(jetbrains.mps.baseLanguage.structure)" implicit="true" />
    <import index="wyt6" ref="6354ebe7-c22a-4a0f-ac54-50b52ab9b065/java:java.lang(JDK/)" implicit="true" />
    <import index="guwi" ref="6354ebe7-c22a-4a0f-ac54-50b52ab9b065/java:java.io(JDK/)" implicit="true" />
    <import index="mhbf" ref="8865b7a8-5271-43d3-884c-6fd1d9cfdd34/java:org.jetbrains.mps.openapi.model(MPS.OpenAPI/)" implicit="true" />
    <import index="tpek" ref="r:00000000-0000-4000-0000-011c895902c0(jetbrains.mps.baseLanguage.behavior)" implicit="true" />
  </imports>
  <registry>
    <language id="f3061a53-9226-4cc5-a443-f952ceaf5816" name="jetbrains.mps.baseLanguage">
      <concept id="1082485599095" name="jetbrains.mps.baseLanguage.structure.BlockStatement" flags="nn" index="9aQIb">
        <child id="1082485599096" name="statements" index="9aQI4" />
      </concept>
      <concept id="4836112446988635817" name="jetbrains.mps.baseLanguage.structure.UndefinedType" flags="in" index="2jxLKc" />
      <concept id="1202948039474" name="jetbrains.mps.baseLanguage.structure.InstanceMethodCallOperation" flags="nn" index="liA8E" />
      <concept id="1465982738277781862" name="jetbrains.mps.baseLanguage.structure.PlaceholderMember" flags="ng" index="2tJIrI" />
      <concept id="1188207840427" name="jetbrains.mps.baseLanguage.structure.AnnotationInstance" flags="nn" index="2AHcQZ">
        <reference id="1188208074048" name="annotation" index="2AI5Lk" />
      </concept>
      <concept id="1188208481402" name="jetbrains.mps.baseLanguage.structure.HasAnnotation" flags="ng" index="2AJDlI">
        <child id="1188208488637" name="annotation" index="2AJF6D" />
      </concept>
      <concept id="2820489544401957797" name="jetbrains.mps.baseLanguage.structure.DefaultClassCreator" flags="nn" index="HV5vD">
        <reference id="2820489544401957798" name="classifier" index="HV5vE" />
      </concept>
      <concept id="1197027756228" name="jetbrains.mps.baseLanguage.structure.DotExpression" flags="nn" index="2OqwBi">
        <child id="1197027771414" name="operand" index="2Oq$k0" />
        <child id="1197027833540" name="operation" index="2OqNvi" />
      </concept>
      <concept id="1145552977093" name="jetbrains.mps.baseLanguage.structure.GenericNewExpression" flags="nn" index="2ShNRf">
        <child id="1145553007750" name="creator" index="2ShVmc" />
      </concept>
      <concept id="1137021947720" name="jetbrains.mps.baseLanguage.structure.ConceptFunction" flags="in" index="2VMwT0">
        <child id="1137022507850" name="body" index="2VODD2" />
      </concept>
      <concept id="1070475354124" name="jetbrains.mps.baseLanguage.structure.ThisExpression" flags="nn" index="Xjq3P" />
      <concept id="1070475926800" name="jetbrains.mps.baseLanguage.structure.StringLiteral" flags="nn" index="Xl_RD">
        <property id="1070475926801" name="value" index="Xl_RC" />
      </concept>
      <concept id="1182160077978" name="jetbrains.mps.baseLanguage.structure.AnonymousClassCreator" flags="nn" index="YeOm9">
        <child id="1182160096073" name="cls" index="YeSDq" />
      </concept>
      <concept id="1081236700938" name="jetbrains.mps.baseLanguage.structure.StaticMethodDeclaration" flags="ig" index="2YIFZL" />
      <concept id="1070533707846" name="jetbrains.mps.baseLanguage.structure.StaticFieldReference" flags="nn" index="10M0yZ">
        <reference id="1144433057691" name="classifier" index="1PxDUh" />
      </concept>
      <concept id="1070534058343" name="jetbrains.mps.baseLanguage.structure.NullLiteral" flags="nn" index="10Nm6u" />
      <concept id="1070534760951" name="jetbrains.mps.baseLanguage.structure.ArrayType" flags="in" index="10Q1$e">
        <child id="1070534760952" name="componentType" index="10Q1$1" />
      </concept>
      <concept id="1068390468200" name="jetbrains.mps.baseLanguage.structure.FieldDeclaration" flags="ig" index="312cEg" />
      <concept id="1068390468198" name="jetbrains.mps.baseLanguage.structure.ClassConcept" flags="ig" index="312cEu">
        <child id="1165602531693" name="superclass" index="1zkMxy" />
      </concept>
      <concept id="1068431474542" name="jetbrains.mps.baseLanguage.structure.VariableDeclaration" flags="ng" index="33uBYm">
        <child id="1068431790190" name="initializer" index="33vP2m" />
      </concept>
      <concept id="1068498886296" name="jetbrains.mps.baseLanguage.structure.VariableReference" flags="nn" index="37vLTw">
        <reference id="1068581517664" name="variableDeclaration" index="3cqZAo" />
      </concept>
      <concept id="1068498886292" name="jetbrains.mps.baseLanguage.structure.ParameterDeclaration" flags="ir" index="37vLTG" />
      <concept id="1225271177708" name="jetbrains.mps.baseLanguage.structure.StringType" flags="in" index="17QB3L" />
      <concept id="1225271283259" name="jetbrains.mps.baseLanguage.structure.NPEEqualsExpression" flags="nn" index="17R0WA" />
      <concept id="4972933694980447171" name="jetbrains.mps.baseLanguage.structure.BaseVariableDeclaration" flags="ng" index="19Szcq">
        <child id="5680397130376446158" name="type" index="1tU5fm" />
      </concept>
      <concept id="1068580123132" name="jetbrains.mps.baseLanguage.structure.BaseMethodDeclaration" flags="ng" index="3clF44">
        <child id="1068580123133" name="returnType" index="3clF45" />
        <child id="1068580123134" name="parameter" index="3clF46" />
        <child id="1068580123135" name="body" index="3clF47" />
      </concept>
      <concept id="1068580123165" name="jetbrains.mps.baseLanguage.structure.InstanceMethodDeclaration" flags="ig" index="3clFb_" />
      <concept id="1068580123155" name="jetbrains.mps.baseLanguage.structure.ExpressionStatement" flags="nn" index="3clFbF">
        <child id="1068580123156" name="expression" index="3clFbG" />
      </concept>
      <concept id="1068580123157" name="jetbrains.mps.baseLanguage.structure.Statement" flags="nn" index="3clFbH" />
      <concept id="1068580123136" name="jetbrains.mps.baseLanguage.structure.StatementList" flags="sn" stub="5293379017992965193" index="3clFbS">
        <child id="1068581517665" name="statement" index="3cqZAp" />
      </concept>
      <concept id="1068580123137" name="jetbrains.mps.baseLanguage.structure.BooleanConstant" flags="nn" index="3clFbT">
        <property id="1068580123138" name="value" index="3clFbU" />
      </concept>
      <concept id="1068580320020" name="jetbrains.mps.baseLanguage.structure.IntegerConstant" flags="nn" index="3cmrfG">
        <property id="1068580320021" name="value" index="3cmrfH" />
      </concept>
      <concept id="1068581242864" name="jetbrains.mps.baseLanguage.structure.LocalVariableDeclarationStatement" flags="nn" index="3cpWs8">
        <child id="1068581242865" name="localVariableDeclaration" index="3cpWs9" />
      </concept>
      <concept id="1068581242863" name="jetbrains.mps.baseLanguage.structure.LocalVariableDeclaration" flags="nr" index="3cpWsn" />
      <concept id="1068581517677" name="jetbrains.mps.baseLanguage.structure.VoidType" flags="in" index="3cqZAl" />
      <concept id="1204053956946" name="jetbrains.mps.baseLanguage.structure.IMethodCall" flags="ng" index="1ndlxa">
        <reference id="1068499141037" name="baseMethodDeclaration" index="37wK5l" />
        <child id="1068499141038" name="actualArgument" index="37wK5m" />
      </concept>
      <concept id="1073063089578" name="jetbrains.mps.baseLanguage.structure.SuperMethodCall" flags="nn" index="3nyPlj" />
      <concept id="1212685548494" name="jetbrains.mps.baseLanguage.structure.ClassCreator" flags="nn" index="1pGfFk" />
      <concept id="1107461130800" name="jetbrains.mps.baseLanguage.structure.Classifier" flags="ng" index="3pOWGL">
        <property id="521412098689998745" name="nonStatic" index="2bfB8j" />
        <child id="5375687026011219971" name="member" index="jymVt" unordered="true" />
      </concept>
      <concept id="1107535904670" name="jetbrains.mps.baseLanguage.structure.ClassifierType" flags="in" index="3uibUv">
        <reference id="1107535924139" name="classifier" index="3uigEE" />
      </concept>
      <concept id="1081773326031" name="jetbrains.mps.baseLanguage.structure.BinaryOperation" flags="nn" index="3uHJSO">
        <child id="1081773367579" name="rightExpression" index="3uHU7w" />
        <child id="1081773367580" name="leftExpression" index="3uHU7B" />
      </concept>
      <concept id="1178549954367" name="jetbrains.mps.baseLanguage.structure.IVisible" flags="ng" index="1B3ioH">
        <child id="1178549979242" name="visibility" index="1B3o_S" />
      </concept>
      <concept id="1146644602865" name="jetbrains.mps.baseLanguage.structure.PublicVisibility" flags="nn" index="3Tm1VV" />
      <concept id="1146644623116" name="jetbrains.mps.baseLanguage.structure.PrivateVisibility" flags="nn" index="3Tm6S6" />
      <concept id="1146644641414" name="jetbrains.mps.baseLanguage.structure.ProtectedVisibility" flags="nn" index="3Tmbuc" />
      <concept id="1170345865475" name="jetbrains.mps.baseLanguage.structure.AnonymousClass" flags="ig" index="1Y3b0j">
        <reference id="1170346070688" name="classifier" index="1Y3XeK" />
      </concept>
    </language>
    <language id="b401a680-8325-4110-8fd3-84331ff25bef" name="jetbrains.mps.lang.generator">
      <concept id="1114706874351" name="jetbrains.mps.lang.generator.structure.CopySrcNodeMacro" flags="ln" index="29HgVG" />
      <concept id="1095416546421" name="jetbrains.mps.lang.generator.structure.MappingConfiguration" flags="ig" index="bUwia">
        <child id="1200911492601" name="mappingLabel" index="2rTMjI" />
        <child id="1167328349397" name="reductionMappingRule" index="3acgRq" />
        <child id="1167514678247" name="rootMappingRule" index="3lj3bC" />
      </concept>
      <concept id="1168559333462" name="jetbrains.mps.lang.generator.structure.TemplateDeclarationReference" flags="ln" index="j$656" />
      <concept id="1168619357332" name="jetbrains.mps.lang.generator.structure.RootTemplateAnnotation" flags="lg" index="n94m4">
        <reference id="1168619429071" name="applicableConcept" index="n9lRv" />
      </concept>
      <concept id="1095672379244" name="jetbrains.mps.lang.generator.structure.TemplateFragment" flags="ng" index="raruj" />
      <concept id="1200911316486" name="jetbrains.mps.lang.generator.structure.MappingLabelDeclaration" flags="lg" index="2rT7sh">
        <reference id="1200911342686" name="sourceConcept" index="2rTdP9" />
        <reference id="1200913004646" name="targetConcept" index="2rZz_L" />
      </concept>
      <concept id="1722980698497626400" name="jetbrains.mps.lang.generator.structure.ITemplateCall" flags="ng" index="v9R3L">
        <reference id="1722980698497626483" name="template" index="v9R2y" />
      </concept>
      <concept id="1167169188348" name="jetbrains.mps.lang.generator.structure.TemplateFunctionParameter_sourceNode" flags="nn" index="30H73N" />
      <concept id="1167169308231" name="jetbrains.mps.lang.generator.structure.BaseMappingRule" flags="ng" index="30H$t8">
        <reference id="1167169349424" name="applicableConcept" index="30HIoZ" />
      </concept>
      <concept id="1092059087312" name="jetbrains.mps.lang.generator.structure.TemplateDeclaration" flags="ig" index="13MO4I">
        <reference id="1168285871518" name="applicableConcept" index="3gUMe" />
        <child id="1092060348987" name="contentNode" index="13RCb5" />
      </concept>
      <concept id="1087833241328" name="jetbrains.mps.lang.generator.structure.PropertyMacro" flags="ln" index="17Uvod">
        <child id="1167756362303" name="propertyValueFunction" index="3zH0cK" />
      </concept>
      <concept id="1087833466690" name="jetbrains.mps.lang.generator.structure.NodeMacro" flags="lg" index="17VmuZ">
        <reference id="1200912223215" name="mappingLabel" index="2rW$FS" />
      </concept>
      <concept id="1167327847730" name="jetbrains.mps.lang.generator.structure.Reduction_MappingRule" flags="lg" index="3aamgX">
        <child id="1169672767469" name="ruleConsequence" index="1lVwrX" />
      </concept>
      <concept id="1167514355419" name="jetbrains.mps.lang.generator.structure.Root_MappingRule" flags="lg" index="3lhOvk">
        <reference id="1167514355421" name="template" index="3lhOvi" />
      </concept>
      <concept id="1131073187192" name="jetbrains.mps.lang.generator.structure.MapSrcNodeMacro" flags="ln" index="1pdMLZ" />
      <concept id="1167756080639" name="jetbrains.mps.lang.generator.structure.PropertyMacro_GetPropertyValue" flags="in" index="3zFVjK" />
      <concept id="1167770111131" name="jetbrains.mps.lang.generator.structure.ReferenceMacro_GetReferent" flags="in" index="3$xsQk" />
      <concept id="1167951910403" name="jetbrains.mps.lang.generator.structure.SourceSubstituteMacro_SourceNodesQuery" flags="in" index="3JmXsc" />
      <concept id="1118786554307" name="jetbrains.mps.lang.generator.structure.LoopMacro" flags="ln" index="1WS0z7">
        <child id="1167952069335" name="sourceNodesQuery" index="3Jn$fo" />
      </concept>
      <concept id="1088761943574" name="jetbrains.mps.lang.generator.structure.ReferenceMacro" flags="ln" index="1ZhdrF">
        <child id="1167770376702" name="referentFunction" index="3$ytzL" />
      </concept>
    </language>
    <language id="fd392034-7849-419d-9071-12563d152375" name="jetbrains.mps.baseLanguage.closures">
      <concept id="1199569711397" name="jetbrains.mps.baseLanguage.closures.structure.ClosureLiteral" flags="nn" index="1bVj0M">
        <child id="1199569906740" name="parameter" index="1bW2Oz" />
        <child id="1199569916463" name="body" index="1bW5cS" />
      </concept>
    </language>
    <language id="d7706f63-9be2-479c-a3da-ae92af1e64d5" name="jetbrains.mps.lang.generator.generationContext">
      <concept id="1216860049627" name="jetbrains.mps.lang.generator.generationContext.structure.GenerationContextOp_GetOutputByLabelAndInput" flags="nn" index="1iwH70">
        <reference id="1216860049628" name="label" index="1iwH77" />
        <child id="1216860049632" name="inputNode" index="1iwH7V" />
      </concept>
      <concept id="1216860049635" name="jetbrains.mps.lang.generator.generationContext.structure.TemplateFunctionParameter_generationContext" flags="nn" index="1iwH7S" />
    </language>
    <language id="446c26eb-2b7b-4bf0-9b35-f83fa582753e" name="jetbrains.mps.lang.modelapi">
      <concept id="4733039728785194814" name="jetbrains.mps.lang.modelapi.structure.NamedNodeReference" flags="ng" index="ZC_QK">
        <reference id="7256306938026143658" name="target" index="2aWVGs" />
      </concept>
    </language>
    <language id="7866978e-a0f0-4cc7-81bc-4d213d9375e1" name="jetbrains.mps.lang.smodel">
      <concept id="1177026924588" name="jetbrains.mps.lang.smodel.structure.RefConcept_Reference" flags="nn" index="chp4Y">
        <reference id="1177026940964" name="conceptDeclaration" index="cht4Q" />
      </concept>
      <concept id="1179409122411" name="jetbrains.mps.lang.smodel.structure.Node_ConceptMethodCall" flags="nn" index="2qgKlT" />
      <concept id="7400021826774799413" name="jetbrains.mps.lang.smodel.structure.NodePointerExpression" flags="ng" index="2tJFMh">
        <child id="7400021826774799510" name="ref" index="2tJFKM" />
      </concept>
      <concept id="4065387505485742749" name="jetbrains.mps.lang.smodel.structure.AbstractPointerResolveOperation" flags="ng" index="2yCiFS">
        <child id="3648723375513868575" name="repositoryArg" index="Vysub" />
      </concept>
      <concept id="2396822768958367367" name="jetbrains.mps.lang.smodel.structure.AbstractTypeCastExpression" flags="nn" index="$5XWr">
        <child id="6733348108486823193" name="leftExpression" index="1m5AlR" />
        <child id="3906496115198199033" name="conceptArgument" index="3oSUPX" />
      </concept>
      <concept id="1143234257716" name="jetbrains.mps.lang.smodel.structure.Node_GetModelOperation" flags="nn" index="I4A8Y" />
      <concept id="1145404486709" name="jetbrains.mps.lang.smodel.structure.SemanticDowncastExpression" flags="nn" index="2JrnkZ">
        <child id="1145404616321" name="leftExpression" index="2JrQYb" />
      </concept>
      <concept id="3648723375513868532" name="jetbrains.mps.lang.smodel.structure.NodePointer_ResolveOperation" flags="ng" index="Vyspw" />
      <concept id="1139613262185" name="jetbrains.mps.lang.smodel.structure.Node_GetParentOperation" flags="nn" index="1mfA1w" />
      <concept id="1140137987495" name="jetbrains.mps.lang.smodel.structure.SNodeTypeCastExpression" flags="nn" index="1PxgMI" />
      <concept id="1138056022639" name="jetbrains.mps.lang.smodel.structure.SPropertyAccess" flags="nn" index="3TrcHB">
        <reference id="1138056395725" name="property" index="3TsBF5" />
      </concept>
      <concept id="1138056143562" name="jetbrains.mps.lang.smodel.structure.SLinkAccess" flags="nn" index="3TrEf2">
        <reference id="1138056516764" name="link" index="3Tt5mk" />
      </concept>
      <concept id="1138056282393" name="jetbrains.mps.lang.smodel.structure.SLinkListAccess" flags="nn" index="3Tsc0h">
        <reference id="1138056546658" name="link" index="3TtcxE" />
      </concept>
    </language>
    <language id="ceab5195-25ea-4f22-9b92-103b95ca8c0c" name="jetbrains.mps.lang.core">
      <concept id="1133920641626" name="jetbrains.mps.lang.core.structure.BaseConcept" flags="ng" index="2VYdi">
        <child id="5169995583184591170" name="smodelAttribute" index="lGtFl" />
      </concept>
      <concept id="3364660638048049750" name="jetbrains.mps.lang.core.structure.PropertyAttribute" flags="ng" index="A9Btg">
        <property id="1757699476691236117" name="name_DebugInfo" index="2qtEX9" />
        <property id="1341860900487648621" name="propertyId" index="P4ACc" />
      </concept>
      <concept id="3364660638048049745" name="jetbrains.mps.lang.core.structure.LinkAttribute" flags="ng" index="A9Btn">
        <property id="1757699476691236116" name="role_DebugInfo" index="2qtEX8" />
        <property id="1341860900488019036" name="linkId" index="P3scX" />
      </concept>
      <concept id="1169194658468" name="jetbrains.mps.lang.core.structure.INamedConcept" flags="ng" index="TrEIO">
        <property id="1169194664001" name="name" index="TrG5h" />
      </concept>
    </language>
    <language id="83888646-71ce-4f1c-9c53-c54016f6ad4f" name="jetbrains.mps.baseLanguage.collections">
      <concept id="1204796164442" name="jetbrains.mps.baseLanguage.collections.structure.InternalSequenceOperation" flags="nn" index="23sCx2">
        <child id="1204796294226" name="closure" index="23t8la" />
      </concept>
      <concept id="1203518072036" name="jetbrains.mps.baseLanguage.collections.structure.SmartClosureParameterDeclaration" flags="ig" index="Rh6nW" />
      <concept id="1225727723840" name="jetbrains.mps.baseLanguage.collections.structure.FindFirstOperation" flags="nn" index="1z4cxt" />
    </language>
  </registry>
  <node concept="bUwia" id="JWnzaFEpt1">
    <property role="TrG5h" value="main" />
    <node concept="3lhOvk" id="$iHUFdug2a" role="3lj3bC">
      <ref role="30HIoZ" to="4707:JWnzaFEptb" resolve="Canvas" />
      <ref role="3lhOvi" node="$iHUFdug2c" resolve="map_Canvas" />
    </node>
    <node concept="3aamgX" id="$iHUFdvGcZ" role="3acgRq">
      <ref role="30HIoZ" to="4707:JWnzaFEpt3" resolve="Circle" />
      <node concept="j$656" id="$iHUFdvGd5" role="1lVwrX">
        <ref role="v9R2y" node="$iHUFdvGd3" resolve="reduce_Circle" />
      </node>
    </node>
    <node concept="3aamgX" id="$iHUFdvGd8" role="3acgRq">
      <ref role="30HIoZ" to="4707:JWnzaFEpt7" resolve="Square" />
      <node concept="j$656" id="$iHUFdvGdg" role="1lVwrX">
        <ref role="v9R2y" node="$iHUFdvGde" resolve="reduce_Square" />
      </node>
    </node>
    <node concept="2rT7sh" id="$iHUFdww65" role="2rTMjI">
      <property role="TrG5h" value="graphicParam" />
      <ref role="2rTdP9" to="4707:JWnzaFEptb" resolve="Canvas" />
      <ref role="2rZz_L" to="tpee:fz7vLUk" resolve="ParameterDeclaration" />
    </node>
  </node>
  <node concept="312cEu" id="$iHUFdug2c">
    <property role="TrG5h" value="map_Canvas" />
    <node concept="312cEg" id="$iHUFduDcF" role="jymVt">
      <property role="TrG5h" value="panel" />
      <node concept="3Tm6S6" id="$iHUFduC4s" role="1B3o_S" />
      <node concept="3uibUv" id="$iHUFduDbc" role="1tU5fm">
        <ref role="3uigEE" to="dxuu:~JPanel" resolve="JPanel" />
      </node>
      <node concept="2ShNRf" id="$iHUFduDM5" role="33vP2m">
        <node concept="YeOm9" id="$iHUFduFdz" role="2ShVmc">
          <node concept="1Y3b0j" id="$iHUFduFdA" role="YeSDq">
            <property role="2bfB8j" value="true" />
            <ref role="37wK5l" to="dxuu:~JPanel.&lt;init&gt;()" resolve="JPanel" />
            <ref role="1Y3XeK" to="dxuu:~JPanel" resolve="JPanel" />
            <node concept="3Tm1VV" id="$iHUFduFdB" role="1B3o_S" />
            <node concept="3clFb_" id="$iHUFduFgE" role="jymVt">
              <property role="TrG5h" value="printComponent" />
              <node concept="3Tmbuc" id="$iHUFduFgF" role="1B3o_S" />
              <node concept="3cqZAl" id="$iHUFduFgH" role="3clF45" />
              <node concept="37vLTG" id="$iHUFduFgI" role="3clF46">
                <property role="TrG5h" value="graphics" />
                <node concept="3uibUv" id="$iHUFdxdLw" role="1tU5fm">
                  <ref role="3uigEE" to="z60i:~Graphics" resolve="Graphics" />
                </node>
                <node concept="1pdMLZ" id="$iHUFdxeiw" role="lGtFl">
                  <ref role="2rW$FS" node="$iHUFdww65" resolve="graphicParam" />
                </node>
              </node>
              <node concept="3clFbS" id="$iHUFduFgN" role="3clF47">
                <node concept="3clFbF" id="$iHUFduFgR" role="3cqZAp">
                  <node concept="3nyPlj" id="$iHUFduFgQ" role="3clFbG">
                    <ref role="37wK5l" to="dxuu:~JComponent.printComponent(java.awt.Graphics)" resolve="printComponent" />
                    <node concept="37vLTw" id="$iHUFduFgP" role="37wK5m">
                      <ref role="3cqZAo" node="$iHUFduFgI" resolve="graphics" />
                    </node>
                  </node>
                </node>
                <node concept="3clFbF" id="$iHUFduGqZ" role="3cqZAp">
                  <node concept="2OqwBi" id="$iHUFduGN9" role="3clFbG">
                    <node concept="10M0yZ" id="$iHUFduGs3" role="2Oq$k0">
                      <ref role="3cqZAo" to="wyt6:~System.out" resolve="out" />
                      <ref role="1PxDUh" to="wyt6:~System" resolve="System" />
                    </node>
                    <node concept="liA8E" id="$iHUFduHjA" role="2OqNvi">
                      <ref role="37wK5l" to="guwi:~PrintStream.println(java.lang.String)" resolve="println" />
                      <node concept="Xl_RD" id="$iHUFduIk7" role="37wK5m">
                        <property role="Xl_RC" value="Draw here" />
                      </node>
                    </node>
                  </node>
                  <node concept="1WS0z7" id="$iHUFdvFsR" role="lGtFl">
                    <node concept="3JmXsc" id="$iHUFdvFsU" role="3Jn$fo">
                      <node concept="3clFbS" id="$iHUFdvFsV" role="2VODD2">
                        <node concept="3clFbF" id="$iHUFdvFt1" role="3cqZAp">
                          <node concept="2OqwBi" id="$iHUFdvFsW" role="3clFbG">
                            <node concept="3Tsc0h" id="$iHUFdvFsZ" role="2OqNvi">
                              <ref role="3TtcxE" to="4707:JWnzaFEptg" resolve="shapes" />
                            </node>
                            <node concept="30H73N" id="$iHUFdvFt0" role="2Oq$k0" />
                          </node>
                        </node>
                      </node>
                    </node>
                  </node>
                  <node concept="29HgVG" id="$iHUFdvG0f" role="lGtFl" />
                </node>
              </node>
              <node concept="2AHcQZ" id="$iHUFduFgO" role="2AJF6D">
                <ref role="2AI5Lk" to="wyt6:~Override" resolve="Override" />
              </node>
            </node>
          </node>
        </node>
      </node>
    </node>
    <node concept="2tJIrI" id="$iHUFduEGT" role="jymVt" />
    <node concept="3clFb_" id="$iHUFduBBQ" role="jymVt">
      <property role="TrG5h" value="initialize" />
      <node concept="3clFbS" id="$iHUFduBBT" role="3clF47">
        <node concept="3clFbF" id="$iHUFduJdE" role="3cqZAp">
          <node concept="2OqwBi" id="$iHUFduMog" role="3clFbG">
            <node concept="Xjq3P" id="$iHUFduJdD" role="2Oq$k0" />
            <node concept="liA8E" id="$iHUFduN7k" role="2OqNvi">
              <ref role="37wK5l" to="z60i:~Frame.setTitle(java.lang.String)" resolve="setTitle" />
              <node concept="Xl_RD" id="$iHUFduNMR" role="37wK5m">
                <property role="Xl_RC" value="Title" />
                <node concept="17Uvod" id="$iHUFdvEdy" role="lGtFl">
                  <property role="2qtEX9" value="value" />
                  <property role="P4ACc" value="f3061a53-9226-4cc5-a443-f952ceaf5816/1070475926800/1070475926801" />
                  <node concept="3zFVjK" id="$iHUFdvEd_" role="3zH0cK">
                    <node concept="3clFbS" id="$iHUFdvEdA" role="2VODD2">
                      <node concept="3clFbF" id="$iHUFdvEdG" role="3cqZAp">
                        <node concept="2OqwBi" id="$iHUFdvEdB" role="3clFbG">
                          <node concept="3TrcHB" id="$iHUFdvEdE" role="2OqNvi">
                            <ref role="3TsBF5" to="tpck:h0TrG11" resolve="name" />
                          </node>
                          <node concept="30H73N" id="$iHUFdvEdF" role="2Oq$k0" />
                        </node>
                      </node>
                    </node>
                  </node>
                </node>
              </node>
            </node>
          </node>
        </node>
        <node concept="3clFbF" id="$iHUFduOPn" role="3cqZAp">
          <node concept="2OqwBi" id="$iHUFduPZK" role="3clFbG">
            <node concept="Xjq3P" id="$iHUFduOPl" role="2Oq$k0" />
            <node concept="liA8E" id="$iHUFduRDj" role="2OqNvi">
              <ref role="37wK5l" to="dxuu:~JFrame.setDefaultCloseOperation(int)" resolve="setDefaultCloseOperation" />
              <node concept="10M0yZ" id="$iHUFduWSj" role="37wK5m">
                <ref role="3cqZAo" to="dxuu:~JFrame.EXIT_ON_CLOSE" resolve="EXIT_ON_CLOSE" />
                <ref role="1PxDUh" to="dxuu:~JFrame" resolve="JFrame" />
              </node>
            </node>
          </node>
        </node>
        <node concept="3clFbF" id="$iHUFduXO9" role="3cqZAp">
          <node concept="2OqwBi" id="$iHUFduYYX" role="3clFbG">
            <node concept="Xjq3P" id="$iHUFduXO7" role="2Oq$k0" />
            <node concept="liA8E" id="$iHUFduZXI" role="2OqNvi">
              <ref role="37wK5l" to="z60i:~Container.add(java.awt.Component)" resolve="add" />
              <node concept="37vLTw" id="$iHUFdv0L4" role="37wK5m">
                <ref role="3cqZAo" node="$iHUFduDcF" resolve="panel" />
              </node>
            </node>
          </node>
        </node>
        <node concept="3clFbF" id="$iHUFdv3jn" role="3cqZAp">
          <node concept="2OqwBi" id="$iHUFdv7rf" role="3clFbG">
            <node concept="37vLTw" id="$iHUFdv61q" role="2Oq$k0">
              <ref role="3cqZAo" node="$iHUFduDcF" resolve="panel" />
            </node>
            <node concept="liA8E" id="$iHUFdvjLi" role="2OqNvi">
              <ref role="37wK5l" to="dxuu:~JComponent.setPreferredSize(java.awt.Dimension)" resolve="setPreferredSize" />
              <node concept="2ShNRf" id="$iHUFdvlJa" role="37wK5m">
                <node concept="1pGfFk" id="$iHUFdvnSX" role="2ShVmc">
                  <ref role="37wK5l" to="z60i:~Dimension.&lt;init&gt;(int,int)" resolve="Dimension" />
                  <node concept="3cmrfG" id="$iHUFdvoC5" role="37wK5m">
                    <property role="3cmrfH" value="500" />
                  </node>
                  <node concept="3cmrfG" id="$iHUFdvrkO" role="37wK5m">
                    <property role="3cmrfH" value="500" />
                  </node>
                </node>
              </node>
            </node>
          </node>
        </node>
        <node concept="3clFbF" id="$iHUFdvt5Y" role="3cqZAp">
          <node concept="2OqwBi" id="$iHUFdvuDX" role="3clFbG">
            <node concept="Xjq3P" id="$iHUFdvt5W" role="2Oq$k0" />
            <node concept="liA8E" id="$iHUFdvvUy" role="2OqNvi">
              <ref role="37wK5l" to="z60i:~Window.pack()" resolve="pack" />
            </node>
          </node>
        </node>
        <node concept="3clFbF" id="$iHUFdvxsK" role="3cqZAp">
          <node concept="2OqwBi" id="$iHUFdvyMw" role="3clFbG">
            <node concept="Xjq3P" id="$iHUFdvxsI" role="2Oq$k0" />
            <node concept="liA8E" id="$iHUFdv$79" role="2OqNvi">
              <ref role="37wK5l" to="z60i:~Window.setVisible(boolean)" resolve="setVisible" />
              <node concept="3clFbT" id="$iHUFdv_1t" role="37wK5m">
                <property role="3clFbU" value="true" />
              </node>
            </node>
          </node>
        </node>
      </node>
      <node concept="3Tm1VV" id="$iHUFduBpG" role="1B3o_S" />
      <node concept="3cqZAl" id="$iHUFduBBp" role="3clF45" />
    </node>
    <node concept="2tJIrI" id="$iHUFduEJe" role="jymVt" />
    <node concept="2YIFZL" id="$iHUFduta$" role="jymVt">
      <property role="TrG5h" value="main" />
      <node concept="37vLTG" id="$iHUFduta_" role="3clF46">
        <property role="TrG5h" value="args" />
        <node concept="10Q1$e" id="$iHUFdutaA" role="1tU5fm">
          <node concept="17QB3L" id="$iHUFdutaB" role="10Q1$1" />
        </node>
      </node>
      <node concept="3cqZAl" id="$iHUFdutaC" role="3clF45" />
      <node concept="3Tm1VV" id="$iHUFdutaD" role="1B3o_S" />
      <node concept="3clFbS" id="$iHUFdutaE" role="3clF47">
        <node concept="3cpWs8" id="$iHUFduujc" role="3cqZAp">
          <node concept="3cpWsn" id="$iHUFduujd" role="3cpWs9">
            <property role="TrG5h" value="canvas" />
            <node concept="3uibUv" id="$iHUFduuje" role="1tU5fm">
              <ref role="3uigEE" node="$iHUFdug2c" resolve="map_Canvas" />
            </node>
            <node concept="2ShNRf" id="$iHUFduuRS" role="33vP2m">
              <node concept="HV5vD" id="$iHUFduyAE" role="2ShVmc">
                <ref role="HV5vE" node="$iHUFdug2c" resolve="map_Canvas" />
              </node>
            </node>
          </node>
        </node>
        <node concept="3clFbF" id="$iHUFduzaS" role="3cqZAp">
          <node concept="2OqwBi" id="$iHUFdvAmV" role="3clFbG">
            <node concept="37vLTw" id="$iHUFduzaQ" role="2Oq$k0">
              <ref role="3cqZAo" node="$iHUFduujd" resolve="canvas" />
            </node>
            <node concept="liA8E" id="$iHUFdvChm" role="2OqNvi">
              <ref role="37wK5l" node="$iHUFduBBQ" resolve="initialize" />
            </node>
          </node>
        </node>
      </node>
    </node>
    <node concept="3Tm1VV" id="$iHUFdug2d" role="1B3o_S" />
    <node concept="n94m4" id="$iHUFdug2e" role="lGtFl">
      <ref role="n9lRv" to="4707:JWnzaFEptb" resolve="Canvas" />
    </node>
    <node concept="3uibUv" id="$iHUFduqIO" role="1zkMxy">
      <ref role="3uigEE" to="dxuu:~JFrame" resolve="JFrame" />
    </node>
    <node concept="17Uvod" id="$iHUFdvCKC" role="lGtFl">
      <property role="2qtEX9" value="name" />
      <property role="P4ACc" value="ceab5195-25ea-4f22-9b92-103b95ca8c0c/1169194658468/1169194664001" />
      <node concept="3zFVjK" id="$iHUFdvCKF" role="3zH0cK">
        <node concept="3clFbS" id="$iHUFdvCKG" role="2VODD2">
          <node concept="3clFbF" id="$iHUFdvCKM" role="3cqZAp">
            <node concept="2OqwBi" id="$iHUFdvCKH" role="3clFbG">
              <node concept="3TrcHB" id="$iHUFdvCKK" role="2OqNvi">
                <ref role="3TsBF5" to="tpck:h0TrG11" resolve="name" />
              </node>
              <node concept="30H73N" id="$iHUFdvCKL" role="2Oq$k0" />
            </node>
          </node>
        </node>
      </node>
    </node>
  </node>
  <node concept="13MO4I" id="$iHUFdvGd3">
    <property role="TrG5h" value="reduce_Circle" />
    <ref role="3gUMe" to="4707:JWnzaFEpt3" resolve="Circle" />
    <node concept="9aQIb" id="$iHUFdvGdj" role="13RCb5">
      <node concept="3clFbS" id="$iHUFdvGdk" role="9aQI4">
        <node concept="3cpWs8" id="$iHUFdvGds" role="3cqZAp">
          <node concept="3cpWsn" id="$iHUFdvGdt" role="3cpWs9">
            <property role="TrG5h" value="g" />
            <node concept="3uibUv" id="$iHUFdvGdu" role="1tU5fm">
              <ref role="3uigEE" to="z60i:~Graphics" resolve="Graphics" />
            </node>
            <node concept="10Nm6u" id="$iHUFdvGdL" role="33vP2m" />
          </node>
        </node>
        <node concept="9aQIb" id="$iHUFdvGe1" role="3cqZAp">
          <node concept="3clFbS" id="$iHUFdvGe3" role="9aQI4">
            <node concept="3clFbF" id="$iHUFdvGed" role="3cqZAp">
              <node concept="2OqwBi" id="$iHUFdvGjE" role="3clFbG">
                <node concept="37vLTw" id="$iHUFdvGeb" role="2Oq$k0">
                  <ref role="3cqZAo" node="$iHUFdvGdt" resolve="g" />
                  <node concept="1ZhdrF" id="$iHUFdwEKo" role="lGtFl">
                    <property role="2qtEX8" value="variableDeclaration" />
                    <property role="P3scX" value="f3061a53-9226-4cc5-a443-f952ceaf5816/1068498886296/1068581517664" />
                    <node concept="3$xsQk" id="$iHUFdwEKp" role="3$ytzL">
                      <node concept="3clFbS" id="$iHUFdwEKq" role="2VODD2">
                        <node concept="3clFbF" id="$iHUFdwFs2" role="3cqZAp">
                          <node concept="2OqwBi" id="$iHUFdwFBD" role="3clFbG">
                            <node concept="1iwH7S" id="$iHUFdwFs1" role="2Oq$k0" />
                            <node concept="1iwH70" id="$iHUFdwFS5" role="2OqNvi">
                              <ref role="1iwH77" node="$iHUFdww65" resolve="graphicParam" />
                              <node concept="1PxgMI" id="$iHUFdwH8E" role="1iwH7V">
                                <node concept="chp4Y" id="$iHUFdwHb1" role="3oSUPX">
                                  <ref role="cht4Q" to="4707:JWnzaFEptb" resolve="Canvas" />
                                </node>
                                <node concept="2OqwBi" id="$iHUFdwGlX" role="1m5AlR">
                                  <node concept="30H73N" id="$iHUFdwGb8" role="2Oq$k0" />
                                  <node concept="1mfA1w" id="$iHUFdwGAy" role="2OqNvi" />
                                </node>
                              </node>
                            </node>
                          </node>
                        </node>
                      </node>
                    </node>
                  </node>
                </node>
                <node concept="liA8E" id="$iHUFdvGKV" role="2OqNvi">
                  <ref role="37wK5l" to="z60i:~Graphics.setColor(java.awt.Color)" resolve="setColor" />
                  <node concept="10M0yZ" id="$iHUFdvGLI" role="37wK5m">
                    <ref role="3cqZAo" to="z60i:~Color.red" resolve="red" />
                    <ref role="1PxDUh" to="z60i:~Color" resolve="Color" />
                    <node concept="1ZhdrF" id="$iHUFdvJf4" role="lGtFl">
                      <property role="2qtEX8" value="variableDeclaration" />
                      <property role="P3scX" value="f3061a53-9226-4cc5-a443-f952ceaf5816/1068498886296/1068581517664" />
                      <node concept="3$xsQk" id="$iHUFdvJf5" role="3$ytzL">
                        <node concept="3clFbS" id="$iHUFdvJf6" role="2VODD2">
                          <node concept="3clFbF" id="$iHUFdvJF1" role="3cqZAp">
                            <node concept="2OqwBi" id="$iHUFdvTJh" role="3clFbG">
                              <node concept="2OqwBi" id="$iHUFdvQIm" role="2Oq$k0">
                                <node concept="2OqwBi" id="$iHUFdvKKS" role="2Oq$k0">
                                  <node concept="2tJFMh" id="$iHUFdvJEZ" role="2Oq$k0">
                                    <node concept="ZC_QK" id="$iHUFdvK1E" role="2tJFKM">
                                      <ref role="2aWVGs" to="z60i:~Color" resolve="Color" />
                                    </node>
                                  </node>
                                  <node concept="Vyspw" id="$iHUFdvLS1" role="2OqNvi">
                                    <node concept="2OqwBi" id="$iHUFdvOwv" role="Vysub">
                                      <node concept="liA8E" id="$iHUFdvPzN" role="2OqNvi">
                                        <ref role="37wK5l" to="mhbf:~SModel.getRepository()" resolve="getRepository" />
                                      </node>
                                      <node concept="2JrnkZ" id="$iHUFdvOwC" role="2Oq$k0">
                                        <node concept="2OqwBi" id="$iHUFdvMrV" role="2JrQYb">
                                          <node concept="30H73N" id="$iHUFdvM5s" role="2Oq$k0" />
                                          <node concept="I4A8Y" id="$iHUFdvN_I" role="2OqNvi" />
                                        </node>
                                      </node>
                                    </node>
                                  </node>
                                </node>
                                <node concept="2qgKlT" id="$iHUFdvTbu" role="2OqNvi">
                                  <ref role="37wK5l" to="tpek:4_LVZ3pBr7M" resolve="staticFields" />
                                </node>
                              </node>
                              <node concept="1z4cxt" id="$iHUFdvXtv" role="2OqNvi">
                                <node concept="1bVj0M" id="$iHUFdvXtx" role="23t8la">
                                  <node concept="3clFbS" id="$iHUFdvXty" role="1bW5cS">
                                    <node concept="9aQIb" id="$iHUFdvY0g" role="3cqZAp">
                                      <node concept="3clFbS" id="$iHUFdvY0h" role="9aQI4">
                                        <node concept="3clFbF" id="$iHUFdvYfQ" role="3cqZAp">
                                          <node concept="17R0WA" id="$iHUFdw6V5" role="3clFbG">
                                            <node concept="2OqwBi" id="$iHUFdw9Sp" role="3uHU7w">
                                              <node concept="2OqwBi" id="$iHUFdw8op" role="2Oq$k0">
                                                <node concept="2OqwBi" id="$iHUFdw7vo" role="2Oq$k0">
                                                  <node concept="30H73N" id="$iHUFdw7ej" role="2Oq$k0" />
                                                  <node concept="3TrEf2" id="$iHUFdw81l" role="2OqNvi">
                                                    <ref role="3Tt5mk" to="4707:$iHUFdtNnW" resolve="color" />
                                                  </node>
                                                </node>
                                                <node concept="3TrEf2" id="$iHUFdw94I" role="2OqNvi">
                                                  <ref role="3Tt5mk" to="4707:$iHUFdtNnG" resolve="target" />
                                                </node>
                                              </node>
                                              <node concept="3TrcHB" id="$iHUFdwaMJ" role="2OqNvi">
                                                <ref role="3TsBF5" to="tpck:h0TrG11" resolve="name" />
                                              </node>
                                            </node>
                                            <node concept="2OqwBi" id="$iHUFdvYEH" role="3uHU7B">
                                              <node concept="37vLTw" id="$iHUFdvYfP" role="2Oq$k0">
                                                <ref role="3cqZAo" node="$iHUFdvXtz" resolve="it" />
                                              </node>
                                              <node concept="3TrcHB" id="$iHUFdw21A" role="2OqNvi">
                                                <ref role="3TsBF5" to="tpck:h0TrG11" resolve="name" />
                                              </node>
                                            </node>
                                          </node>
                                        </node>
                                      </node>
                                    </node>
                                  </node>
                                  <node concept="Rh6nW" id="$iHUFdvXtz" role="1bW2Oz">
                                    <property role="TrG5h" value="it" />
                                    <node concept="2jxLKc" id="$iHUFdvXt$" role="1tU5fm" />
                                  </node>
                                </node>
                              </node>
                            </node>
                          </node>
                        </node>
                      </node>
                    </node>
                  </node>
                </node>
              </node>
            </node>
            <node concept="3clFbF" id="$iHUFdvH8H" role="3cqZAp">
              <node concept="2OqwBi" id="$iHUFdvHew" role="3clFbG">
                <node concept="37vLTw" id="$iHUFdvH8F" role="2Oq$k0">
                  <ref role="3cqZAo" node="$iHUFdvGdt" resolve="g" />
                  <node concept="1ZhdrF" id="$iHUFdwHeY" role="lGtFl">
                    <property role="2qtEX8" value="variableDeclaration" />
                    <property role="P3scX" value="f3061a53-9226-4cc5-a443-f952ceaf5816/1068498886296/1068581517664" />
                    <node concept="3$xsQk" id="$iHUFdwHeZ" role="3$ytzL">
                      <node concept="3clFbS" id="$iHUFdwHf0" role="2VODD2">
                        <node concept="3clFbF" id="$iHUFdwHYW" role="3cqZAp">
                          <node concept="2OqwBi" id="$iHUFdwIgx" role="3clFbG">
                            <node concept="1iwH7S" id="$iHUFdwHYV" role="2Oq$k0" />
                            <node concept="1iwH70" id="$iHUFdwIwX" role="2OqNvi">
                              <ref role="1iwH77" node="$iHUFdww65" resolve="graphicParam" />
                              <node concept="1PxgMI" id="$iHUFdwJlo" role="1iwH7V">
                                <node concept="chp4Y" id="$iHUFdwJnJ" role="3oSUPX">
                                  <ref role="cht4Q" to="4707:JWnzaFEptb" resolve="Canvas" />
                                </node>
                                <node concept="2OqwBi" id="$iHUFdwIUO" role="1m5AlR">
                                  <node concept="30H73N" id="$iHUFdwIJZ" role="2Oq$k0" />
                                  <node concept="1mfA1w" id="$iHUFdwJ3o" role="2OqNvi" />
                                </node>
                              </node>
                            </node>
                          </node>
                        </node>
                      </node>
                    </node>
                  </node>
                </node>
                <node concept="liA8E" id="$iHUFdvHFx" role="2OqNvi">
                  <ref role="37wK5l" to="z60i:~Graphics.drawOval(int,int,int,int)" resolve="drawOval" />
                  <node concept="3cmrfG" id="$iHUFdvHFS" role="37wK5m">
                    <property role="3cmrfH" value="10" />
                    <node concept="17Uvod" id="$iHUFdvHOw" role="lGtFl">
                      <property role="2qtEX9" value="value" />
                      <property role="P4ACc" value="f3061a53-9226-4cc5-a443-f952ceaf5816/1068580320020/1068580320021" />
                      <node concept="3zFVjK" id="$iHUFdvHOz" role="3zH0cK">
                        <node concept="3clFbS" id="$iHUFdvHO$" role="2VODD2">
                          <node concept="3clFbF" id="$iHUFdvHOE" role="3cqZAp">
                            <node concept="2OqwBi" id="$iHUFdvHO_" role="3clFbG">
                              <node concept="3TrcHB" id="$iHUFdvHOC" role="2OqNvi">
                                <ref role="3TsBF5" to="4707:JWnzaFEpt4" resolve="x" />
                              </node>
                              <node concept="30H73N" id="$iHUFdvHOD" role="2Oq$k0" />
                            </node>
                          </node>
                        </node>
                      </node>
                    </node>
                  </node>
                  <node concept="3cmrfG" id="$iHUFdvHHi" role="37wK5m">
                    <property role="3cmrfH" value="10" />
                    <node concept="17Uvod" id="$iHUFdvIak" role="lGtFl">
                      <property role="2qtEX9" value="value" />
                      <property role="P4ACc" value="f3061a53-9226-4cc5-a443-f952ceaf5816/1068580320020/1068580320021" />
                      <node concept="3zFVjK" id="$iHUFdvIan" role="3zH0cK">
                        <node concept="3clFbS" id="$iHUFdvIao" role="2VODD2">
                          <node concept="3clFbF" id="$iHUFdvIau" role="3cqZAp">
                            <node concept="2OqwBi" id="$iHUFdvIap" role="3clFbG">
                              <node concept="3TrcHB" id="$iHUFdvIas" role="2OqNvi">
                                <ref role="3TsBF5" to="4707:JWnzaFEpt5" resolve="y" />
                              </node>
                              <node concept="30H73N" id="$iHUFdvIat" role="2Oq$k0" />
                            </node>
                          </node>
                        </node>
                      </node>
                    </node>
                  </node>
                  <node concept="3cmrfG" id="$iHUFdvHIS" role="37wK5m">
                    <property role="3cmrfH" value="10" />
                    <node concept="17Uvod" id="$iHUFdvIwE" role="lGtFl">
                      <property role="2qtEX9" value="value" />
                      <property role="P4ACc" value="f3061a53-9226-4cc5-a443-f952ceaf5816/1068580320020/1068580320021" />
                      <node concept="3zFVjK" id="$iHUFdvIwH" role="3zH0cK">
                        <node concept="3clFbS" id="$iHUFdvIwI" role="2VODD2">
                          <node concept="3clFbF" id="$iHUFdvIwO" role="3cqZAp">
                            <node concept="2OqwBi" id="$iHUFdvIwJ" role="3clFbG">
                              <node concept="3TrcHB" id="$iHUFdvIwM" role="2OqNvi">
                                <ref role="3TsBF5" to="4707:JWnzaFEpt6" resolve="radius" />
                              </node>
                              <node concept="30H73N" id="$iHUFdvIwN" role="2Oq$k0" />
                            </node>
                          </node>
                        </node>
                      </node>
                    </node>
                  </node>
                  <node concept="3cmrfG" id="$iHUFdvHK5" role="37wK5m">
                    <property role="3cmrfH" value="10" />
                    <node concept="17Uvod" id="$iHUFdvIRy" role="lGtFl">
                      <property role="2qtEX9" value="value" />
                      <property role="P4ACc" value="f3061a53-9226-4cc5-a443-f952ceaf5816/1068580320020/1068580320021" />
                      <node concept="3zFVjK" id="$iHUFdvIR_" role="3zH0cK">
                        <node concept="3clFbS" id="$iHUFdvIRA" role="2VODD2">
                          <node concept="3clFbF" id="$iHUFdvIRG" role="3cqZAp">
                            <node concept="2OqwBi" id="$iHUFdvIRB" role="3clFbG">
                              <node concept="3TrcHB" id="$iHUFdvIRE" role="2OqNvi">
                                <ref role="3TsBF5" to="4707:JWnzaFEpt6" resolve="radius" />
                              </node>
                              <node concept="30H73N" id="$iHUFdvIRF" role="2Oq$k0" />
                            </node>
                          </node>
                        </node>
                      </node>
                    </node>
                  </node>
                </node>
              </node>
            </node>
          </node>
          <node concept="raruj" id="$iHUFdvHMo" role="lGtFl" />
        </node>
      </node>
    </node>
  </node>
  <node concept="13MO4I" id="$iHUFdvGde">
    <property role="TrG5h" value="reduce_Square" />
    <ref role="3gUMe" to="4707:JWnzaFEpt7" resolve="Square" />
    <node concept="9aQIb" id="$iHUFdwbl6" role="13RCb5">
      <node concept="3clFbS" id="$iHUFdwbl7" role="9aQI4">
        <node concept="3cpWs8" id="$iHUFdwbli" role="3cqZAp">
          <node concept="3cpWsn" id="$iHUFdwblj" role="3cpWs9">
            <property role="TrG5h" value="g" />
            <node concept="3uibUv" id="$iHUFdwblk" role="1tU5fm">
              <ref role="3uigEE" to="z60i:~Graphics" resolve="Graphics" />
            </node>
            <node concept="10Nm6u" id="$iHUFdwblA" role="33vP2m" />
          </node>
        </node>
        <node concept="9aQIb" id="$iHUFdwczC" role="3cqZAp">
          <node concept="3clFbS" id="$iHUFdwczD" role="9aQI4">
            <node concept="3clFbF" id="$iHUFdwczE" role="3cqZAp">
              <node concept="2OqwBi" id="$iHUFdwczF" role="3clFbG">
                <node concept="37vLTw" id="$iHUFdwczG" role="2Oq$k0">
                  <ref role="3cqZAo" node="$iHUFdwblj" resolve="g" />
                  <node concept="1ZhdrF" id="$iHUFdwz0g" role="lGtFl">
                    <property role="2qtEX8" value="variableDeclaration" />
                    <property role="P3scX" value="f3061a53-9226-4cc5-a443-f952ceaf5816/1068498886296/1068581517664" />
                    <node concept="3$xsQk" id="$iHUFdwz0h" role="3$ytzL">
                      <node concept="3clFbS" id="$iHUFdwz0i" role="2VODD2">
                        <node concept="3clFbF" id="$iHUFdwChO" role="3cqZAp">
                          <node concept="2OqwBi" id="$iHUFdwCzU" role="3clFbG">
                            <node concept="1iwH7S" id="$iHUFdwChN" role="2Oq$k0" />
                            <node concept="1iwH70" id="$iHUFdwCOm" role="2OqNvi">
                              <ref role="1iwH77" node="$iHUFdww65" resolve="graphicParam" />
                              <node concept="1PxgMI" id="$iHUFdwDTK" role="1iwH7V">
                                <node concept="chp4Y" id="$iHUFdwDW7" role="3oSUPX">
                                  <ref role="cht4Q" to="4707:JWnzaFEptb" resolve="Canvas" />
                                </node>
                                <node concept="2OqwBi" id="$iHUFdwDiL" role="1m5AlR">
                                  <node concept="30H73N" id="$iHUFdwD7W" role="2Oq$k0" />
                                  <node concept="1mfA1w" id="$iHUFdwDzm" role="2OqNvi" />
                                </node>
                              </node>
                            </node>
                          </node>
                        </node>
                      </node>
                    </node>
                  </node>
                </node>
                <node concept="liA8E" id="$iHUFdwczH" role="2OqNvi">
                  <ref role="37wK5l" to="z60i:~Graphics.setColor(java.awt.Color)" resolve="setColor" />
                  <node concept="10M0yZ" id="$iHUFdwczI" role="37wK5m">
                    <ref role="1PxDUh" to="z60i:~Color" resolve="Color" />
                    <ref role="3cqZAo" to="z60i:~Color.red" resolve="red" />
                    <node concept="1ZhdrF" id="$iHUFdwczJ" role="lGtFl">
                      <property role="2qtEX8" value="variableDeclaration" />
                      <property role="P3scX" value="f3061a53-9226-4cc5-a443-f952ceaf5816/1068498886296/1068581517664" />
                      <node concept="3$xsQk" id="$iHUFdwczK" role="3$ytzL">
                        <node concept="3clFbS" id="$iHUFdwczL" role="2VODD2">
                          <node concept="3clFbF" id="$iHUFdwczM" role="3cqZAp">
                            <node concept="2OqwBi" id="$iHUFdwczN" role="3clFbG">
                              <node concept="2OqwBi" id="$iHUFdwczO" role="2Oq$k0">
                                <node concept="2OqwBi" id="$iHUFdwczP" role="2Oq$k0">
                                  <node concept="2tJFMh" id="$iHUFdwczQ" role="2Oq$k0">
                                    <node concept="ZC_QK" id="$iHUFdwczR" role="2tJFKM">
                                      <ref role="2aWVGs" to="z60i:~Color" resolve="Color" />
                                    </node>
                                  </node>
                                  <node concept="Vyspw" id="$iHUFdwczS" role="2OqNvi">
                                    <node concept="2OqwBi" id="$iHUFdwczT" role="Vysub">
                                      <node concept="liA8E" id="$iHUFdwczU" role="2OqNvi">
                                        <ref role="37wK5l" to="mhbf:~SModel.getRepository()" resolve="getRepository" />
                                      </node>
                                      <node concept="2JrnkZ" id="$iHUFdwczV" role="2Oq$k0">
                                        <node concept="2OqwBi" id="$iHUFdwczW" role="2JrQYb">
                                          <node concept="30H73N" id="$iHUFdwczX" role="2Oq$k0" />
                                          <node concept="I4A8Y" id="$iHUFdwczY" role="2OqNvi" />
                                        </node>
                                      </node>
                                    </node>
                                  </node>
                                </node>
                                <node concept="2qgKlT" id="$iHUFdwczZ" role="2OqNvi">
                                  <ref role="37wK5l" to="tpek:4_LVZ3pBr7M" resolve="staticFields" />
                                </node>
                              </node>
                              <node concept="1z4cxt" id="$iHUFdwc$0" role="2OqNvi">
                                <node concept="1bVj0M" id="$iHUFdwc$1" role="23t8la">
                                  <node concept="3clFbS" id="$iHUFdwc$2" role="1bW5cS">
                                    <node concept="9aQIb" id="$iHUFdwc$3" role="3cqZAp">
                                      <node concept="3clFbS" id="$iHUFdwc$4" role="9aQI4">
                                        <node concept="3clFbF" id="$iHUFdwc$5" role="3cqZAp">
                                          <node concept="17R0WA" id="$iHUFdwc$6" role="3clFbG">
                                            <node concept="2OqwBi" id="$iHUFdwc$7" role="3uHU7w">
                                              <node concept="2OqwBi" id="$iHUFdwc$8" role="2Oq$k0">
                                                <node concept="2OqwBi" id="$iHUFdwc$9" role="2Oq$k0">
                                                  <node concept="30H73N" id="$iHUFdwc$a" role="2Oq$k0" />
                                                  <node concept="3TrEf2" id="$iHUFdwc$b" role="2OqNvi">
                                                    <ref role="3Tt5mk" to="4707:$iHUFdtNnW" resolve="color" />
                                                  </node>
                                                </node>
                                                <node concept="3TrEf2" id="$iHUFdwc$c" role="2OqNvi">
                                                  <ref role="3Tt5mk" to="4707:$iHUFdtNnG" resolve="target" />
                                                </node>
                                              </node>
                                              <node concept="3TrcHB" id="$iHUFdwc$d" role="2OqNvi">
                                                <ref role="3TsBF5" to="tpck:h0TrG11" resolve="name" />
                                              </node>
                                            </node>
                                            <node concept="2OqwBi" id="$iHUFdwc$e" role="3uHU7B">
                                              <node concept="37vLTw" id="$iHUFdwc$f" role="2Oq$k0">
                                                <ref role="3cqZAo" node="$iHUFdwc$h" resolve="it" />
                                              </node>
                                              <node concept="3TrcHB" id="$iHUFdwc$g" role="2OqNvi">
                                                <ref role="3TsBF5" to="tpck:h0TrG11" resolve="name" />
                                              </node>
                                            </node>
                                          </node>
                                        </node>
                                      </node>
                                    </node>
                                  </node>
                                  <node concept="Rh6nW" id="$iHUFdwc$h" role="1bW2Oz">
                                    <property role="TrG5h" value="it" />
                                    <node concept="2jxLKc" id="$iHUFdwc$i" role="1tU5fm" />
                                  </node>
                                </node>
                              </node>
                            </node>
                          </node>
                        </node>
                      </node>
                    </node>
                  </node>
                </node>
              </node>
            </node>
            <node concept="3clFbF" id="$iHUFdwc$j" role="3cqZAp">
              <node concept="2OqwBi" id="$iHUFdwc$k" role="3clFbG">
                <node concept="37vLTw" id="$iHUFdwc$l" role="2Oq$k0">
                  <ref role="3cqZAo" node="$iHUFdwblj" resolve="g" />
                  <node concept="1ZhdrF" id="$iHUFdwzDf" role="lGtFl">
                    <property role="2qtEX8" value="variableDeclaration" />
                    <property role="P3scX" value="f3061a53-9226-4cc5-a443-f952ceaf5816/1068498886296/1068581517664" />
                    <node concept="3$xsQk" id="$iHUFdwzDg" role="3$ytzL">
                      <node concept="3clFbS" id="$iHUFdwzDh" role="2VODD2">
                        <node concept="3clFbF" id="$iHUFdw$n1" role="3cqZAp">
                          <node concept="2OqwBi" id="$iHUFdw_sj" role="3clFbG">
                            <node concept="1iwH7S" id="$iHUFdw$n0" role="2Oq$k0" />
                            <node concept="1iwH70" id="$iHUFdwAm$" role="2OqNvi">
                              <ref role="1iwH77" node="$iHUFdww65" resolve="graphicParam" />
                              <node concept="1PxgMI" id="$iHUFdwC5M" role="1iwH7V">
                                <node concept="chp4Y" id="$iHUFdwC89" role="3oSUPX">
                                  <ref role="cht4Q" to="4707:JWnzaFEptb" resolve="Canvas" />
                                </node>
                                <node concept="2OqwBi" id="$iHUFdwAVO" role="1m5AlR">
                                  <node concept="30H73N" id="$iHUFdwAEa" role="2Oq$k0" />
                                  <node concept="1mfA1w" id="$iHUFdwB7y" role="2OqNvi" />
                                </node>
                              </node>
                            </node>
                          </node>
                        </node>
                      </node>
                    </node>
                  </node>
                </node>
                <node concept="liA8E" id="$iHUFdwc$m" role="2OqNvi">
                  <ref role="37wK5l" to="z60i:~Graphics.drawOval(int,int,int,int)" resolve="drawOval" />
                  <node concept="3cmrfG" id="$iHUFdwc$n" role="37wK5m">
                    <property role="3cmrfH" value="10" />
                    <node concept="17Uvod" id="$iHUFdwdJ3" role="lGtFl">
                      <property role="2qtEX9" value="value" />
                      <property role="P4ACc" value="f3061a53-9226-4cc5-a443-f952ceaf5816/1068580320020/1068580320021" />
                      <node concept="3zFVjK" id="$iHUFdwdJ6" role="3zH0cK">
                        <node concept="3clFbS" id="$iHUFdwdJ7" role="2VODD2">
                          <node concept="3clFbF" id="$iHUFdwdJd" role="3cqZAp">
                            <node concept="2OqwBi" id="$iHUFdwdJ8" role="3clFbG">
                              <node concept="3TrcHB" id="$iHUFdwdJb" role="2OqNvi">
                                <ref role="3TsBF5" to="4707:JWnzaFEpt8" resolve="upperLeftX" />
                              </node>
                              <node concept="30H73N" id="$iHUFdwdJc" role="2Oq$k0" />
                            </node>
                          </node>
                        </node>
                      </node>
                    </node>
                  </node>
                  <node concept="3cmrfG" id="$iHUFdwc$v" role="37wK5m">
                    <property role="3cmrfH" value="10" />
                    <node concept="17Uvod" id="$iHUFdwet4" role="lGtFl">
                      <property role="2qtEX9" value="value" />
                      <property role="P4ACc" value="f3061a53-9226-4cc5-a443-f952ceaf5816/1068580320020/1068580320021" />
                      <node concept="3zFVjK" id="$iHUFdwet7" role="3zH0cK">
                        <node concept="3clFbS" id="$iHUFdwet8" role="2VODD2">
                          <node concept="3clFbF" id="$iHUFdwete" role="3cqZAp">
                            <node concept="2OqwBi" id="$iHUFdwet9" role="3clFbG">
                              <node concept="3TrcHB" id="$iHUFdwetc" role="2OqNvi">
                                <ref role="3TsBF5" to="4707:JWnzaFEpt9" resolve="upperLeftY" />
                              </node>
                              <node concept="30H73N" id="$iHUFdwetd" role="2Oq$k0" />
                            </node>
                          </node>
                        </node>
                      </node>
                    </node>
                  </node>
                  <node concept="3cmrfG" id="$iHUFdwc$B" role="37wK5m">
                    <property role="3cmrfH" value="10" />
                    <node concept="17Uvod" id="$iHUFdwf9H" role="lGtFl">
                      <property role="2qtEX9" value="value" />
                      <property role="P4ACc" value="f3061a53-9226-4cc5-a443-f952ceaf5816/1068580320020/1068580320021" />
                      <node concept="3zFVjK" id="$iHUFdwf9K" role="3zH0cK">
                        <node concept="3clFbS" id="$iHUFdwf9L" role="2VODD2">
                          <node concept="3clFbF" id="$iHUFdwf9R" role="3cqZAp">
                            <node concept="2OqwBi" id="$iHUFdwf9M" role="3clFbG">
                              <node concept="3TrcHB" id="$iHUFdwf9P" role="2OqNvi">
                                <ref role="3TsBF5" to="4707:JWnzaFEpta" resolve="size" />
                              </node>
                              <node concept="30H73N" id="$iHUFdwf9Q" role="2Oq$k0" />
                            </node>
                          </node>
                        </node>
                      </node>
                    </node>
                  </node>
                  <node concept="3cmrfG" id="$iHUFdwc$J" role="37wK5m">
                    <property role="3cmrfH" value="10" />
                    <node concept="17Uvod" id="$iHUFdwfQm" role="lGtFl">
                      <property role="2qtEX9" value="value" />
                      <property role="P4ACc" value="f3061a53-9226-4cc5-a443-f952ceaf5816/1068580320020/1068580320021" />
                      <node concept="3zFVjK" id="$iHUFdwfQp" role="3zH0cK">
                        <node concept="3clFbS" id="$iHUFdwfQq" role="2VODD2">
                          <node concept="3clFbF" id="$iHUFdwfQw" role="3cqZAp">
                            <node concept="2OqwBi" id="$iHUFdwfQr" role="3clFbG">
                              <node concept="3TrcHB" id="$iHUFdwfQu" role="2OqNvi">
                                <ref role="3TsBF5" to="4707:JWnzaFEpta" resolve="size" />
                              </node>
                              <node concept="30H73N" id="$iHUFdwfQv" role="2Oq$k0" />
                            </node>
                          </node>
                        </node>
                      </node>
                    </node>
                  </node>
                </node>
              </node>
            </node>
          </node>
          <node concept="raruj" id="$iHUFdwc$R" role="lGtFl" />
        </node>
        <node concept="3clFbH" id="$iHUFdwblR" role="3cqZAp" />
      </node>
    </node>
  </node>
</model>

