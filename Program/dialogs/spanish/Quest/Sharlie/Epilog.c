void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold, NextMonth;
	string attrL, sStr, Month;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "¿Querías algo?";
			link.l1 = "No, nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// диалоги в ПУ
		case "SharlieEpilog_Pikar_1":
			dialog.text = "¡Vaya, quién lo diría! Tú mismo "+GetTitle(NPChar,true)+" "+pchar.lastname+" ¡en persona!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				link.l1 = ""+npchar.name+"¡Vaya, a ti sí que no esperaba verte... Es más, ni siquiera pensaba que siguieras con vida!";
				link.l1.go = "SharlieEpilog_Pikar_2";
			}
			else
			{
				link.l1 = "No puedo creer lo que veo... ¿Guapo? Pero... ¿cómo?";
				link.l1.go = "SharlieEpilog_PikarResurrected_1";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\LE\Rocur\Rocur_03.wav");
		break;
		
		case "SharlieEpilog_Pikar_2":
			if (IsStateTitle())
			  {
				dialog.text = "¡Ja, ja! Pues te equivocas. Como ves, estoy más vivo que nunca. Mira, he decidido comprarme un barquito ‘limpio’. Y tú... cuéntame: ¿cómo has acabado así, amigo?";
			  }
			  else 
			  {
				dialog.text = "¡Ja, ja! Pues te equivocas. Como ves, estoy más vivo que nunca. Mira, he decidido comprarme un barquito 'limpio'. Pero tú... cuéntame, ¿qué te trae por aquí, amigo?";
			  }
			link.l1 = "No aquí. Vamos a la taberna, los asuntos pueden esperar.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_1":
			dialog.text = "Chss... No grites así. Guapo - eso quedó en el pasado, igual que el Príncipe, supongo. ¿No es cierto?";
			link.l1 = "Pero si yo lo vi con mis propios ojos...";
			link.l1.go = "SharlieEpilog_PikarResurrected_2";
		break;

		case "SharlieEpilog_PikarResurrected_2":
			dialog.text = "¿Que si me liquidaron? Ojalá hubiera sido así, amigo. Créeme.";
			link.l1 = "Vamos a la taberna. Me lo contarás todo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_Captain_1":
			dialog.text = "...";
			link.l1 = "Entonces, usted es el nuevo dueño del pinaza '"+GetShipName("Ulysse")+"'?";
			link.l1.go = "SharlieEpilog_Captain_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\z_arest_02.wav");
		break;
		
		case "SharlieEpilog_Captain_2":
			dialog.text = "Yo. "+GetFullName(npchar)+", ya que tanto le interesa. ¿Y usted quién es?";
			link.l1 = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+", y me gustaría comprarles este barco.";
			link.l1.go = "SharlieEpilog_Captain_3";
		break;
		
		case "SharlieEpilog_Captain_3":
			dialog.text = "Claro, claro, he oído hablar de eso. Y yo que pensaba que ya me había librado de todos los que querían hacerse con este barco. Tendré que decepcionarte, "+GetTitle(NPChar,true)+" - '"+GetShipName("Ulysse")+"' ahora es mío, y muy pronto me marcho a Burdeos en él. No me metí en el comercio para echar a perder el primer trato que se me presenta. Es de mala suerte, ¿sabe usted? ";
			link.l1 = "¿Burdeos, dice? Qué curioso... Quizá tenga una propuesta interesante para usted. ¿Por qué no lo hablamos con una jarra de ron?";
			link.l1.go = "SharlieEpilog_Captain_4";
		break;
		
		case "SharlieEpilog_Captain_4":
			dialog.text = "No suelo rechazar ni el ron ni las buenas propuestas. Vamos.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		// диалоги в таверне
		case "SharlieEpilog_Pikar_5":
			if (IsStateTitle())
			  {
				dialog.text = "Bueno, por ti, "+GetTitle(npchar,false)+" "+pchar.lastname+". Sabía yo que un tipo como tú no iba a estar mucho tiempo de recadero para Tirax. Pero que llegarías a ser un pez gordo... sabes cómo sorprender, maldita sea.";
				link.l1 = "Ja, ja. Mira quién habla. Así que decidiste meterte a comerciante, ¿eh?";
			  }
			  else 
			  {
				dialog.text = "¡Por nuestro encuentro! Lo presentía en el fondo, sabía que volveríamos a vernos.";
				link.l1 = "Ja, ja. ¡Por ella! ¿Así que has decidido hacerte comerciante?";
			  }
			
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;

		case "SharlieEpilog_Pikar_6":
			dialog.text = "No voy a estar arriesgando el cuello toda la vida por un par de doblones. Engrasé las palmas a quien debía, cerré la boca a quien no debía — y ya está: no soy ladrón ni pirata, sino un respetable comerciante.";
			link.l1 = "Vaya sorpresa. Ahora ya no sé ni cómo ofrecerte lo que pensaba proponerle al flamante capitán del pinaza '"+GetShipName("Ulysse")+"'.";
			link.l1.go = "SharlieEpilog_Pikar_7";
		break;

		case "SharlieEpilog_Pikar_7":
			dialog.text = "Vamos, cuéntamelo tal cual. Nos conocemos desde hace siglos.";
			link.l1 = "Verás... llegué aquí, al Caribe, en la pinaza que tú compraste. Cuando supe que la subastaban, quise recuperarla y regresar en ella a casa, a Francia.";
			link.l1.go = "SharlieEpilog_Pikar_8";
		break;

		case "SharlieEpilog_Pikar_8":
			dialog.text = "¡Ja-ja-ja-ja! Espera... ¡ja-ja-ja-ja-ja!..";
			link.l1 = "¿Y qué es lo que te hace gracia?";
			link.l1.go = "SharlieEpilog_Pikar_9";
		break;

		case "SharlieEpilog_Pikar_9":
			dialog.text = "Y apenas gané la subasta, se me acercó un petimetre —joven, bien arreglado— y me dice: llévame, buen hombre, junto con mis pertenencias a Burdeos, por una buena suma. Y no solo una suma, ¡sino un maldito saco de monedas!";
			link.l1 = "¿Ah, sí? Ja, ja. De verdad, es gracioso. ¿Y tú qué? ¿Aceptaste?";
			link.l1.go = "SharlieEpilog_Pikar_10";
		break;

		case "SharlieEpilog_Pikar_10":
			dialog.text = ""+pchar.name+", bueno, no soy tan tonto como para rechazar una montaña de oro sólo за cruzar el Atlántico. Sí, habrá que pasar un par de meses comiendo galletas duras y carne salada. Pero, ¿sabes?, me ha tocado arriesgar el cuello por mucho menos. Así que, por supuesto, acepto.";
			link.l1 = "En ese caso, te ofrezco lo mismo. Llévame a Burdeos y recibirás una montaña de monedas igual.";
			link.l1.go = "SharlieEpilog_Pikar_11";
		break;

		case "SharlieEpilog_Pikar_11":
			dialog.text = "¿Estás listo para ser pasajero? Ya conoces nuestras reglas: en el barco solo hay un capitán. Y en mi barco, ese soy yo.";
			link.l1 = "¿Por qué no? Tomaré un respiro, pensaré en la vida. Quizá de verdad debería sentar cabeza, asentarme. Ahora mismo me cuesta imaginarlo, pero tal vez tenga sentido. Incluso tú decidiste mantenerte alejado de las batallas.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Pikar_12_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Pikar_12";
			}
		break;
		
		case "SharlieEpilog_Pikar_12_wife":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				dialog.text = "Ah, si yo tuviera una esposa tan hermosa como la tuya, quizá también dejaría el mar y me asentaría en algún rincón perdido: construiría una casa y me dedicaría a vender vino. Al menos ahora tengo con qué vivir — desde que me sacaste de las garras de los españoles, no he perdido el tiempo.";
			}
			else
			{
				dialog.text = "Ah, si yo tuviera una esposa tan hermosa como la tuya, quizá también dejaría el mar y me asentaría en algún rincón perdido: construiría una casa y me pondría a vender vino. Al fin y al cabo, hay con qué vivir: la viudita del plantador tenía una herencia de las buenas.";
			}
			link.l1 = "¡Esposa! Demonios, "+npchar.name+", aún no he hablado de esto con ella.";
			link.l1.go = "SharlieEpilog_Pikar_13_wife";
		break;
		
		case "SharlieEpilog_Pikar_13_wife":
			dialog.text = "Tienes tiempo de sobra para eso. Yo tengo que equipar mi barco como es debido. Cuando termines con tus asuntos, trae tu trasero aquí. Montaremos una buena fiesta antes de zarpar.";
			link.l1 = "¡Eso sí que me gusta! No te preocupes, no tendrás que esperar mucho.";
			link.l1.go = "SharlieEpilog_Pikar_14_wife";
		break;
		
		case "SharlieEpilog_Pikar_14_wife":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_1");}
			else {AddQuestRecord("SharlieEpilog", "11_5");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_12":
			dialog.text = "Ah, si tuviera esposa, tal vez yo mismo dejaría el mar y me asentaría en algún rincón perdido: construiría una casa y vendería un poco de vino. Pero por ahora... el mar es mi hogar.";
			link.l1 = "¡Con vino de mis plantaciones, ja, ja! En Burdeos, "+npchar.name+", esas muchachas son un verdadero espectáculo. Igual hasta te encuentras alguna que te guste: en asuntos de amor no se quedan cortas. Estaba pensando que, durante los próximos meses, lo único que veremos serán las caras de tus marineros. Así que antes de zarpar, deberíamos organizar una buena fiesta en el burdel local.";
			link.l1.go = "SharlieEpilog_Pikar_13";
		break;
		
		case "SharlieEpilog_Pikar_13":
			dialog.text = "Y usted, monsieur, sí que sabe qué ofrecer. Cuando termines con todos tus asuntos, trae tu trasero aquí. Y luego nos vamos al burdel, puedes estar seguro.";
			link.l1 = "Bien, entonces no voy a perder el tiempo. ¡Manos a la obra!";
			link.l1.go = "SharlieEpilog_Pikar_14";
		break;
		
		case "SharlieEpilog_Pikar_14":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_2");}
			else {AddQuestRecord("SharlieEpilog", "11_6");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_3":
			dialog.text = "¡Por la libertad!";
			link.l1 = "¡Y por ti, Jean! ¡Por tu regreso a la vida! Todavía no me lo creo. ¿Cómo?";
			link.l1.go = "SharlieEpilog_PikarResurrected_4";
		break;

		case "SharlieEpilog_PikarResurrected_4":
			dialog.text = "Me sacaron arrastrando del campo de batalla, medio muerto, cubierto de sangre de pies a cabeza. Me tiraron en una barraca y me dejaron allí para morir como un perro. Entre los esclavos había un tipo muy hábil, Moko. Fue él quien me salvó la vida: me vendó la herida con un trozo de mi propia camisa y me dio de beber.";
			link.l1 = "¿Quieres decir que los españoles te dejaron con vida después de todo eso?";
			link.l1.go = "SharlieEpilog_PikarResurrected_5";
		break;

		case "SharlieEpilog_PikarResurrected_5":
			dialog.text = "Como ves. Pero no fue por bondad. Querían venganza: interrogatorios duros, torturas. Me quemaron, golpearon, cortaron. Amenazaban con sacarme los ojos, todo por un “gran amor” hacia mí. Pero alguien empezó a decir que los piratas planeaban vengarse por mí y ya estaban afilando los cuchillos. Al dueño de la plantación hasta le empezó a temblar el ojo. No quiso esperar la visita de nuestros amigos y se apresuró a marcharse a sus tierras en Campeche. Nos llevó a Moko, a los demás y a mí con él, para que no quedaran testigos. A los otros les dijeron que yo había muerto, y ahí dejaron el asunto.";
			link.l1 = "¿Y qué pasó después? ¿Cómo lograste salir en libertad? ¿Y cómo demonios terminaste aquí?";
			link.l1.go = "SharlieEpilog_PikarResurrected_6";
		break;

		case "SharlieEpilog_PikarResurrected_6":
			dialog.text = "La suerte, amigo. Ciega, sucia suerte. Me llevaron a una plantación, y las torturas continuaron. Ese bastardo decidió saborear cada segundo de mi sufrimiento, pero cada día se debilitaba más... hasta que murió de fiebre. Después de eso, ya a nadie le importaba lo que me pasara. Me echaron al campo como a una bestia, sin olvidar darme generosamente de latigazos.";
			link.l1 = " Todavía no entiendo cómo lograste salir de allí. ";
			link.l1.go = "SharlieEpilog_PikarResurrected_7";
		break;

		case "SharlieEpilog_PikarResurrected_7":
			dialog.text = "¿Has oído hablar de Christopher Myngs?";
			link.l1 = "Alonso mencionó algo... ¡El asalto a Campeche! Vaya paliza que le dieron a los españoles entonces. ¿Así fue como te liberaron?";
			link.l1.go = "SharlieEpilog_PikarResurrected_8";
		break;

		case "SharlieEpilog_PikarResurrected_8":
			dialog.text = "No exactamente. Nos liberamos nosotros mismos. Mientras la guardia se defendía del grupo de bucaneros ingleses, Moko y yo encontramos una rendija en el techo del barracón y organizamos un motín. Tomamos el arsenal y el tesoro de la esposa del difunto bastardo plantador.";
			link.l1 = "¿El tesoro?!  Vaya giro inesperado.";
			link.l1.go = "SharlieEpilog_PikarResurrected_9";
		break;

		case "SharlieEpilog_PikarResurrected_9":
			dialog.text = "No lo pensamos mucho: armados y con nuestras pertenencias, nos internamos en la selva. Durante dos días atravesamos la espesura hasta toparnos con una aldea de los indios Kan Pech. Su chamán fingía obedecer a los españoles, pero no les tenía ningún aprecio. Moko enseguida se entendió con él: nos dieron refugio a cambio de la mitad de nuestro arsenal y de ayudarles en cualquier guerra que se presentara. Así pasé allí un año y medio.";
			link.l1 = "Jean, ya no eres el que eras antes. De ahora en adelante eres el Afortunado.";
			link.l1.go = "SharlieEpilog_PikarResurrected_10";
		break;

		case "SharlieEpilog_PikarResurrected_10":
			dialog.text = "Ja, ja. No me opongo. Pues después, a nuestro batabil llegó un predicador francés. Nos dimos cuenta enseguida: era la oportunidad de salir de allí sin grilletes. Sobornamos a su escolta y pronto ya íbamos rumbo a Tortuga.\nY después, como seguramente ya habrás adivinado, decidí dejar de jugar al escondite con la muerte. Abandoné mi antiguo oficio... y de paso me hice con un '"+GetShipName("Ulysse")+".\n"+"¿Y tú? ¿Cómo llegaste a esto? Ya sabía yo que un tipo tan audaz como tú no iba a durar mucho como chico de los recados de Tirax. Pero que llegaras a convertirte en alguien tan importante... sabes cómo sorprender, maldita sea.";
			link.l1 = "Ja, ja. Mira quién habla. Así que has decidido hacerte comerciante, ¿eh?";
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;
		
		case "SharlieEpilog_Captain_5":
			dialog.text = "¡Por los que están en el mar!";
			link.l1 = "¡Y por la buena fortuna!";
			link.l1.go = "SharlieEpilog_Captain_6";
		break;

		case "SharlieEpilog_Captain_6":
			dialog.text = "Bueno, vayamos al grano. ¿Qué querías proponerme?";
			link.l1 = "Se dirige usted a Burdeos... Verá, yo también voy para allá.";
			link.l1.go = "SharlieEpilog_Captain_7";
		break;

		case "SharlieEpilog_Captain_7":
			dialog.text = "¿Queréis que os lleve a bordo? Que yo sepa, deberíais tener vuestro propio barco. Quizá hasta una flota entera. Y aun así habéis decidido viajar en un navío ajeno. ¿Lo he entendido bien?";
			link.l1 = "Así es. Los últimos acontecimientos me han hecho pensar: quizás ha llegado el momento de echar el ancla, de sentar cabeza... Creo que el papel de simple pasajero en vuestro barco me ayudará a entender si puedo aceptar este nuevo ritmo de vida.";
			link.l1.go = "SharlieEpilog_Captain_8";
		break;

		case "SharlieEpilog_Captain_8":
			dialog.text = "Hmm... Así que se ha cansado de arriesgar el cuello sin motivo, ¿eh? Lo entiendo. Yo mismo... Bueno, no importa. Hay sitio en el barco para usted, incluso para toda su comitiva. El pasaje ya está pagado por un joven francés, y también paga por la rapidez, así que no pienso llenar las bodegas de carga. En cuanto al pago...";
			link.l1 = "No se preocupe, capitán. No soy menos generoso que su empleador y estoy dispuesto a pagar la misma suma.";
			link.l1.go = "SharlieEpilog_Captain_9";
		break;

		case "SharlieEpilog_Captain_9":
			dialog.text = "¡Excelente! ¿Entonces, trato hecho?";
			link.l1 = "¡Trato hecho! ¡Eso merece un brindis!";
			link.l1.go = "SharlieEpilog_Captain_10";
		break;

		case "SharlieEpilog_Captain_10":
			dialog.text = "Sí, este ron está de maravilla... Necesitaré dos semanas para poner el barco en orden y abastecerme de todo lo necesario. Después de eso, podremos zarpar.";
			link.l1 = "Entonces nos vemos aquí mismo dentro de dos semanas. Bueno, hasta pronto, capitán.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Captain_11_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Captain_11";
			}
		break;
		
		case "SharlieEpilog_Captain_11_wife":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_3");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Captain_11":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_4");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "¿Y bien, amigo, ya has arreglado tus asuntos? ¿Le mostramos a este gallinero cómo se debe divertir uno?";
				link.l1 = "Aún no es el momento, "+npchar.name+", todavía me quedan algunos asuntos pendientes.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Capitán, ¿ya está listo para subir a bordo?";
				link.l1 = "Por desgracia, colega, todavía tengo asuntos pendientes.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_Pikar_WaitInTavern";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				// только если знаком с Пикаром и поговорил с женой
				link.l2 = "¡Eh, tabernero! ¡Invito yo a todos a una ronda! ¡Y no cualquier cosa, pon lo mejor que tengas!";
				link.l2.go = "SharlieEpilog_Pikar_WaitInTavern_2";
			}
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern_2":
			dialog.text = "...";
			link.l1 = "Por nosotros, amigo. Por el viento salado, por el mar sin fin y por el horizonte: siempre tentador, siempre inalcanzable...";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_FrameInSea":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_FrameInSea");
		break;
		
		case "SharlieEpilog_Mary_1":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", querida, quiero hablar contigo sobre mi padre.";
			link.l1.go = "SharlieEpilog_Mary_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_2":
			dialog.text = "¿Qué ocurre, querido? Espero que él esté bien, ¿sí?";
			link.l1 = "Bueno, no tan bien como nos gustaría. Hay motivos para pensar que no le queda mucho tiempo, y le inquieta mucho la idea de no poder verme antes de emprender su último viaje.";
			link.l1.go = "SharlieEpilog_Mary_3";
		break;

		case "SharlieEpilog_Mary_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Lo sé, mi querida, lo sé... Pero así es la vida. Me gustaría que lo conocieras. Que vea qué esposa tan maravillosa tengo y nos dé su bendición.";
			link.l1.go = "SharlieEpilog_Mary_4";
		break;

		case "SharlieEpilog_Mary_4":
			dialog.text = "¿Y si no le caigo bien, eh? Al fin y al cabo, yo no soy de sangre noble...";
			link.l1 = "Tonterías, "+npchar.name+", ¿cómo no vas a gustarle? ¡Eres un encanto! Si conquistaste mi corazón, conquistarás también el suyo.";
			link.l1.go = "SharlieEpilog_Mary_5";
		break;

		case "SharlieEpilog_Mary_5":
			dialog.text = "¿De verdad lo crees, querido? Entonces debemos ir a verlo cuanto antes.";
			link.l1 = "Eso es justo lo que pienso hacer. Incluso ya he encontrado un barco para nosotros. Zarpamos en dos semanas.";
			link.l1.go = "SharlieEpilog_Mary_6";
		break;

		case "SharlieEpilog_Mary_6":
			dialog.text = "¿Un barco? ¿No vamos a navegar en nuestro propio navío?";
			link.l1 = "No, querida. Iremos en la pinaza '"+GetShipName("Ulysse")+"'. En él llegué al Caribe, y en él me marcharé.";
			link.l1.go = "SharlieEpilog_Mary_7";
		break;

		case "SharlieEpilog_Mary_7":
			dialog.text = "¿Y tú no serás capitán?";
			link.l1 = "Tarde o temprano, de todos modos tendría que renunciar a este papel. Espero que sea solo por un tiempo. Pero, en cualquier caso, no me vendría mal sentir lo que me espera en el futuro.";
			link.l1.go = "SharlieEpilog_Mary_8";
		break;

		case "SharlieEpilog_Mary_8":
			dialog.text = "¿Y qué será de nuestros oficiales? No podremos llevarlos a todos con nosotros. Y dudo que quieran esperarte aquí.";
			link.l1 = "Eh... Sí, tienes razón. Tendré que hablar con cada uno de ellos y, probablemente, despedirme para siempre. Aunque no será fácil, considerando todo lo que hemos pasado juntos.";
			link.l1.go = "SharlieEpilog_Mary_9";
		break;
			
		case "SharlieEpilog_Mary_9":
			dialog.text = "Quizá deberíamos organizar una pequeña fiesta de despedida en la taberna, ¿no?";
			link.l1 = "Yo también lo he pensado, querida. Sabes... creo que tienes razón. Es realmente una buena idea.";
			link.l1.go = "exit";
			link.l2 = "No creo que sea buena idea. Mejor evitemos las despedidas ruidosas... Así, probablemente, será mejor para todos. A menos que invitemos solo a los amigos más leales...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		case "SharlieEpilog_Helena_1":
			dialog.text = "...";
			link.l1 = "Querida, me gustaría hablar contigo sobre mi padre.";
			link.l1.go = "SharlieEpilog_Helena_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_2":
			dialog.text = "Por supuesto, "+pchar.name+". Espero que esté bien, ¿verdad?";
			link.l1 = "No exactamente. Lleva ya mucho tiempo enfermo y, me temo, la enfermedad pronto acabará por vencerle... Mi padre soporta todo esto con gran entereza. Lo único que de verdad le inquieta es que tal vez no llegue a verme de nuevo. Quiero ir a visitarle... y presentarte ante él. Recibir su bendición para nuestro matrimonio.";
			link.l1.go = "SharlieEpilog_Helena_3";
		break;

		case "SharlieEpilog_Helena_3":
			dialog.text = "Estaré encantada de conocerle, mi amor. ¿Cuándo zarpamos?";
			link.l1 = "En dos semanas. Pero eso no es todo. No iremos en nuestro barco. Al Viejo Mundo nos llevará el pinaza '"+GetShipName("Ulysse")+"– el mismo que una vez me trajo aquí.";
			link.l1.go = "SharlieEpilog_Helena_4";
		break;

		case "SharlieEpilog_Helena_4":
			dialog.text = ""+pchar.name+", pero cambiar de barco antes de un largo viaje es una mala señal.";
			link.l1 = "No vamos a cambiar de barco, querida. Seremos pasajeros.";
			link.l1.go = "SharlieEpilog_Helena_5";
		break;

		case "SharlieEpilog_Helena_5":
			dialog.text = "Pero... mi amor, no entiendo...";
			link.l1 = "Así debe ser, "+npchar.name+". Tarde o temprano tendré que dejar el puesto de capitán. Y quiero saber de antemano qué sentimientos tendré que afrontar.";
			link.l1.go = "SharlieEpilog_Helena_6";
		break;

		case "SharlieEpilog_Helena_6":
			dialog.text = "Si así lo has decidido... ¿Pero qué será de nuestros oficiales? No podremos llevarlos a todos con nosotros. Y dudo mucho que se queden aquí esperándote.";
			link.l1 = "Ejem... Sí, tienes razón. Tendré que hablar con cada uno de ellos y, lo más probable, despedirme para siempre. Aunque no será fácil, considerando todo lo que hemos pasado juntos.";
			link.l1.go = "SharlieEpilog_Helena_7";
		break;
			
		case "SharlieEpilog_Helena_7":
			dialog.text = "Quizá deberíamos organizar una pequeña fiesta de despedida en la taberna, ¿no?";
			link.l1 = "Yo también lo he pensado, querida. Sabes... creo que eso haremos. Es realmente una buena idea.";
			link.l1.go = "exit";
			link.l2 = "No creo que sea buena idea. Mejor evitemos las despedidas ruidosas... Así, probablemente, será mejor para todos. A menos que invitemos solo a los amigos más leales...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		// Диалог с Алонсо в таверне Сен-Пьера
		case "SharlieEpilog_AlonsoInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				dialog.text = "Capitán... Ya hablé con el tabernero: ha preparado la mejor bebida que tiene. ¿Cuándo empezamos?";
				link.l1 = "¡Ahora mismo! ¡Eh, tabernero! ¡Invito yo a todos a una ronda!";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_1";
			}
			else
			{
				dialog.text = "Capitán, me prometió contarme cómo se enteró de 'Ulises'.";
				link.l1 = "Lo recuerdo, lo recuerdo. ¡Eh, tabernero! El mejor ron para esta mesa.";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_3";
			}
			link.l2 = "Es temprano, "+npchar.name+". Todavía tengo asuntos urgentes que atender.";
			link.l2.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_AlonsoInTavern";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_1":
			dialog.text = "...";
			link.l1 = "Bueno, amigo, llama a los demás: ¡vamos a enseñarle a Saint-Pierre cómo celebran los auténticos lobos de mar!";
			link.l1.go = "SharlieEpilog_AlonsoInTavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_AlonsoInTavern_2":
			dialog.text = "¡Ja, ja!  ¡Capitán, no lo va a creer: ya los he llamado!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_FrameInSea";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_3":
			dialog.text = "...";
			link.l1 = "Por nosotros, "+npchar.name+". ¡Por la buena fortuna y por el viento que hincha nuestras velas!";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		// На пинасе Улисс
		case "SharlieEpilog_Alonso_1":
			dialog.text = "Vaya jaleo que armamos, capitán. Ja, ja. Parece que a la taberna solo la salvaron de la ruina total las escasas reservas de ron del tabernero.";
			link.l1 = "No me lo recuerdes, "+npchar.name+", recién ahora empiezo a sentirme un poco mejor.";
			link.l1.go = "SharlieEpilog_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;
		
		case "SharlieEpilog_Alonso_2":
			dialog.text = "Como diga, señor "+pchar.lastname+". Ja, ja. Pero al menos nos despedimos de Martinica como reyes. Allí recordarán vuestra partida durante mucho tiempo.";
			link.l1 = "Creo que nos pasamos un poco cuando metimos al tabernero en el bote y lo mandamos a Le François a por bebida.";
			link.l1.go = "SharlieEpilog_Alonso_2_1";
		break;
		
		case "SharlieEpilog_Alonso_2_1":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2)
				{
					dialog.text = "Ja, ja, ja. No se preocupe por él. En estos días ha conseguido tanto oro que podría comprarse una plantación y, de paso, un título.";
				}
			else
				{
					dialog.text = "Ja, ja, ja. No se preocupe por él. En estos días ha conseguido tanto oro que podría comprarse una plantación y hasta un título de nobleza. Lástima que no haya hablado con ninguno de los oficiales. Los vamos a echar de menos.";
				}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_3";
		break;
		
		case "SharlieEpilog_Alonso_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
				{
					sld = CharacterFromID("Helena");
					locCameraFromToPos(-8.97, 6.39, -12.78, true, -8.54, 4.94, -13.90);
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
				{
					sld = CharacterFromID("Mary");
					locCameraFromToPos(-3.62, 4.03, 2.30, true, -4.98, 2.62, 3.26);
					// locCameraFromToPos(-4.13, 4.23, 2.55, true, -5.71, 2.54, 3.58);
				}
				dialog.text = "Parece que "+sld.name+" todavía está enfadada contigo porque desapareciste casi toda la noche.";
			}
			else
			{
				dialog.text = "Pero con ese comerciante... ahí sí que, capitán, de verdad, se le fue la mano.";
			}
			link.l1 = "Maldita sea, ¿por qué tuvimos que meternos con Jean en esa tienda local…?";
			link.l1.go = "SharlieEpilog_Alonso_4";
		break;
		
		case "SharlieEpilog_Alonso_4":
			dialog.text = "¿Y cómo es que no te atraparon? Eso sí que habría sido divertido - "+GetTitle(PChar,true)+" atrapado intentando robar varias botellas de vino.";
			link.l1 = "Te hace gracia, "+npchar.name+", y ni siquiera recuerdo la mitad de todo esto. La última vez que me emborraché así fue... pues... en realidad, nunca.";
			link.l1.go = "SharlieEpilog_Alonso_5";
			locCameraFromToPos(-8.74, 6.30, 7.38, true, -14.34, 4.16, 6.56);
		break;
		
		case "SharlieEpilog_Alonso_5":
			dialog.text = "Entonces, felicidades por el primer paso, capitán. Ja, ja. Me ha gustado. Yo lo repetiría. ¿Cuándo decías que volvemos?";
			link.l1 = "Mejor ve a echar un vistazo a nuestras cosas. ¿Nos llevamos todo? Yo bajaré después: el aire del almacén seguro que ahora no me hará ningún bien.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_UlysseInSea_8");
		break;
		
		// диалог с Алонсо у горы золота
		case "SharlieEpilog_Alonso_11": // этап 1
			dialog.text = "...";
			link.l1 = "Mira nada más... vaya sacudida le ha dado al barco.";
			link.l1.go = "SharlieEpilog_Alonso_12";
			SharlieEpilog_GoldInTheDeck_1_1();
		break;
		
		case "SharlieEpilog_Alonso_12":
			dialog.text = "¡Aquí hay un maldito montón de oro, capitán!";
			link.l1 = "Veo, "+npchar.name+". Hay que esconder todo esto en los cofres cuanto antes, antes de que la tripulación lo vea. No les conviene tener tales tentaciones.";
			link.l1.go = "SharlieEpilog_Alonso_13";
		break;
		
		case "SharlieEpilog_Alonso_13":
			dialog.text = "No, no podré resistirme...";
			link.l1 = "¿Qué?";
			link.l1.go = "exit";
			locCameraFromToPos(-1.28, 7.70, -10.26, true, 0.74, 5.42, -9.49);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_2");
		break;
			
		case "SharlieEpilog_Alonso_21": // этап 2
			dialog.text = "...";
			link.l1 = "¿Eh, qué te pasa?";
			link.l1.go = "SharlieEpilog_Alonso_22";
			// SharlieEpilog_GoldInTheDeck_6();
		break;
		
		case "SharlieEpilog_Alonso_22":
			dialog.text = "...";
			link.l1 = "Vamos, levántate. Elegiste buen momento...";
			link.l1.go = "SharlieEpilog_Alonso_23";
		break;
		
		case "SharlieEpilog_Alonso_23":
			dialog.text = "Únase a nosotros, capitán.";
			link.l1 = "Levántate, deja de hacer el tonto.";
			link.l1.go = "SharlieEpilog_Alonso_24";
		break;
		
		case "SharlieEpilog_Alonso_24":
			dialog.text = "Relájese, hombre. Tiene que sentirlo.";
			link.l1 = "Está bien, que te den. Anda, hazte a un lado.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_7");
		break;
		
		case "SharlieEpilog_Alonso_31": // этап 3
			dialog.text = "Siempre soñé con hacer esto...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_32";
			SharlieEpilog_GoldInTheDeck_10();
		break;
		
		case "SharlieEpilog_Alonso_32":
			dialog.text = "Es una sensación magnífica, ¿verdad, capitán?";
			link.l1 = "Ja-ja-ja. Así que vine al Caribe solo para averiguar cómo le iba a mi hermano. Seguro que mi padre no esperaba un giro así. ¡Ja-ja!";
			link.l1.go = "SharlieEpilog_Alonso_33";
		break;
		
		case "SharlieEpilog_Alonso_33":
			dialog.text = "Señor "+GetTitle(NPChar,false)+" "+pchar.lastname+"... ¡Ja, ja! ¿Recuerda cómo llegó usted al archipiélago?";
			link.l1 = "Claro que me acuerdo. Ja, ja. Ni siquiera parece real que alguna vez fui tan presumido como ese que ahora pasea por la cubierta. He pasado por tantas cosas en estos malditos Caribes… Intrigas, muertos vivientes, el hermanito Kukulkán…";
			link.l1.go = "SharlieEpilog_Alonso_34";
		break;
		
		case "SharlieEpilog_Alonso_34":
			dialog.text = "Eres endemoniadamente afortunado, capitán. Hacerte con semejante fortuna y seguir con vida... no cualquiera lo logra.";
			link.l1 = "Vaya, sí. Bueno, basta de holgazanear. No vaya a ser que alguien de verdad se dé cuenta.";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_11");
		break;
		
		// диалоги в катсцене с брашпилем
		case "SharlieEpilog_windlass_1":
			dialog.text = "...";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Escucha, amigo, no me convence el seguro del cabrestante en este barco. Es demasiado poco fiable. No vaya a ser que alguien lo suelte sin querer.";
			}
			else
			{
				link.l1 = "Escuche, capitán, no me gusta el seguro del cabrestante en este barco. Es demasiado poco fiable. No vaya a ser que alguien lo suelte sin querer.";
			}
			link.l1.go = "SharlieEpilog_windlass_2";
			locCameraFromToPos(-7.57, 9.68, -21.21, true, -9.79, 7.76, -20.01);
		break;
		
		case "SharlieEpilog_windlass_2":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Vamos, "+pchar.name+",   en el barco todos saben que…";
			}
			else
			{
				dialog.text = "Vamos, capitán. ¿A quién se le ocurriría...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_windlass_3");
		break;
		
		case "SharlieEpilog_windlass_3": // диалог Пикара и дворянина
			dialog.text = "Eh, tú, zoquete... ¿Qué demonios estás haciendo? ¿No te enseñaron a no meter tus patas torcidas donde no debes?";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_4";
			locCameraFromToPos(-10.28, 9.94, -22.90, true, -9.29, 7.86, -21.36);
			NPCsLookEachOther("SharlieEpilog_Pikar", "SharlieEpilog_Bernard_Clone");
			CharacterTurnByChr(pchar, CharacterFromID("SharlieEpilog_Bernard_Clone"));
		break;
		
		case "SharlieEpilog_windlass_4":
			dialog.text = "...";
			link.l1 = "¡Cuidado, no te olvides de quién soy! Soy un noble, y no pienso tolerar...";
			link.l1.go = "SharlieEpilog_windlass_5";
		break;
		
		case "SharlieEpilog_windlass_5":
			dialog.text = "En mi barco no eres nadie. Mis marineros aquí tienen más derechos que tú. Así que o te quedas callado y no molestas a nadie, o yo mismo te lanzo por la borda.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_6";
		break;
		
		case "SharlieEpilog_windlass_6": // диалог Пикара и Шарля
			dialog.text = "...";
			link.l1 = "Ja, ja, ja. Es como si me hubiera visto a mí mismo desde fuera.";
			link.l1.go = "SharlieEpilog_windlass_7";
			SharlieEpilog_windlass_9_1();
		break;
		
		case "SharlieEpilog_windlass_7":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "¿De qué hablas?";
				link.l1 = "Sí, no importa, "+npchar.name+". No seas tan duro con nuestro pasajero. Todo esto todavía es nuevo para él. Al fin y al cabo, nosotros tampoco nos volvimos lobos de mar de la noche a la mañana.";
			}
			else
			{
				dialog.text = "¿De qué hablas?";
				link.l1 = "No le dé importancia, "+npchar.name+". Y no juzguen demasiado a su pasajero. Todo esto es nuevo para él. Al fin y al cabo, nosotros tampoco nos convertimos en lobos de mar de la noche a la mañana.";
			}
			link.l1.go = "SharlieEpilog_windlass_8";
		break;
		
		case "SharlieEpilog_windlass_8":
			dialog.text = "Con su talento, antes se enredará en el cabrestante que hacerse marinero. Hay que tener imaginación...";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Quién sabe, quién sabe. Llegué al archipiélago siendo igual de despreocupado, curioso y arrogante muchacho.";
			}
			else
			{
				link.l1 = "Quién sabe. Cuando llegué al archipiélago, era igual de despreocupado, curioso y arrogante que tú, un jovenzuelo.";
			}
			link.l1.go = "SharlieEpilog_windlass_9";
		break;
		
		case "SharlieEpilog_windlass_9":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Vaya comparación, ¿no?\n"+"Espera\n"+"¿Así que te ves reflejado en él? Ja, ja, ja. Pues entonces hazte cargo tú de él. Yo no voy a estar cuidándolo.";
				link.l1 = "Yo me encargaré de él. Hasta que tú le saques todo el jugo. Pero que pague el ancla hasta el último real.";
			}
			else
			{
				dialog.text = "¿Así que se vio reflejado en él? Ja, ja. Bueno, capitán, entonces tómelo bajo su responsabilidad. Yo no pienso andar cuidándolo.";
				link.l1 = "Yo me encargaré de él. Hasta que ustedes no le saquen el pellejo. Pero por el ancla, que pague como es debido.";
			}
			link.l1.go = "SharlieEpilog_windlass_10";
		break;
		
		case "SharlieEpilog_windlass_10":
			dialog.text = "Elegid el ancla. Esperamos el viento. Mantened el rumbo.";
			link.l1 = "...";
			link.l1.go = "exit";
			SharlieEpilog_windlass_10();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_1");
		break;
		
		// диалоги Старшего матроса и Алонсо		
		case "SharlieEpilog_AlonsoTrollingHighSailor_2": // Алонсо
			dialog.text = "";
			link.l1 = "Levamos anclas. Aprovechamos el viento. Rumbo al noreste.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_3";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_3": // Старший матрос
			dialog.text = "";
			link.l1 = "¡Izad el ancla! Bajad el foque, vamos a atrapar el viento. Manos a la obra...";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_4";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_4": // Алонсо
			dialog.text = "";
			link.l1 = "¿Qué estás haciendo?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_5";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_5": // Старший матрос
			dialog.text = "";
			link.l1 = "¿Qué estás haciendo?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_6";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_6": // Алонсо
			dialog.text = "";
			link.l1 = "No, ¿qué estás haciendo?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_7";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_7": // Старший матрос
			dialog.text = "";
			link.l1 = "Argh... ¿Qué haces? El marinero principal repite las órdenes del capitán.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_8";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_8": // Алонсо
			dialog.text = "";
			link.l1 = "Así que el contramaestre los repite para них.";
			link.l1.go = "exit";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_2");
		break;
		
		// Шарль ругает Алонсо
		case "SharlieEpilog_AlonsoTrollingHighSailor_9":
			dialog.text = "...";
			link.l1 = "Déjalo, Alonso. Aquí solo somos pasajeros. ¿Lo has olvidado?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_10";
			locCameraFromToPos(-8.00, 4.49, -1.91, true, -9.97, 2.64, -1.90);
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_10":
			dialog.text = "Eh... Disculpa, capitán. No pude resistirme\nPero valió la pena. Fue como volver al pasado.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_5");
		break;
		
		// Диалог Шарля с Пикаром о всяком (можно попасть в Поместье де Монпе)
		case "SharlieEpilog_PikarOnUliss":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"... ¿Qué desea?";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A"))
				{
					link.l1 = "Bueno, amigo, ¿cómo te sientes?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_A_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_B"))
				{
					if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
					{
						link.l2 = "Admítelo, "+npchar.name+", tú ya pensabas dedicarte al comercio desde que decidiste separarte de Tirax, ¿verdad?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
					else
					{
						link.l2 = "Admítelo, "+npchar.name+", ¿acaso ya pensabas dedicarte al comercio desde entonces, en la plantación?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_C"))
				{
					link.l3 = "Recuerdo claramente que un mensajero intentó hablar conmigo. Pero, por más que lo intento, no logro recordar de qué se trataba. ¿Tú no sabes nada al respecto?";
					link.l3.go = "SharlieEpilog_PikarOnUliss_C_1";
				}
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_E"))
				{
					link.l1 = "¿Ya ha estado en Burdeos, capitán?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_E_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_F"))
				{
					link.l2 = "Capitán, la verdad es que apenas recuerdo cómo dejamos Martinica. Tenía que recibir un correo importante de una persona, pero parece que nunca llegó a mis manos. ¿Nadie se ha dirigido a usted por este asunto?";
					link.l2.go = "SharlieEpilog_PikarOnUliss_F_1";
				}
			}
			link.l4 = "Parece que sopla una brisa ligera. Es hora de desplegar las velas. (Salir al mar)";
			link.l4.go = "SharlieEpilog_PikarOnUliss_D_1";
			link.l5 = "Por ahora nada. Me voy.";
			link.l5.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_A_1":
			dialog.text = "Ja, ja... ¡Como nunca antes! Lleno de fuerzas y salud.";
			link.l1 = "¿De verdad? Pero tienes una pinta como si te hubiera masticado un tiburón.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_A = true;
		break;

		case "SharlieEpilog_PikarOnUliss_A_2":
			dialog.text = "Mira quién habla. Tú mismo pareces un perro apaleado.";
			link.l1 = "Y yo me siento igual. Ja, ja. Demonios, ni siquiera recuerdo cómo y cuándo zarpamos.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_3";
		break;

		case "SharlieEpilog_PikarOnUliss_A_3":
			dialog.text = "Ah, qué buena fiesta fue esa. Pero maldita sea, salió carísima. Mis idiotas casi prenden fuego al burdel, tuve que soltar una bolsa de monedas para tapar el escándalo. Así que ahora esos zoquetes me deben hasta la tumba.\n¿Y tú qué tal como pasajero? ¿Aún no te mueres de aburrimiento?";
			link.l1 = "Tengo la sensación de que ya no controlo mi propio destino. Pero al mismo tiempo siento un extraño alivio. Como si me hubiera quitado de los hombros una caja llena de balas de cañón.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_4";
		break;

		case "SharlieEpilog_PikarOnUliss_A_4":
			dialog.text = "Ja, ja. Está bien, si alguna vez te invade la melancolía, estoy dispuesto a aceptarte como oficial en mi tripulación.";
			link.l1 = "Es muy generoso de tu parte, pero debo rechazarlo. No hay ron suficiente en todo el Caribe para abastecer nuestras juergas.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_1":
			if (IsStateTitle()) 
			{
				dialog.text = "No exactamente, amigo. Esa idea me rondaba de vez en cuando, pero nunca le presté mucha atención. Volvió a mi cabeza por segunda vez cuando me llegó el rumor de que toda la banda de fieles sabuesos de Tirax había desaparecido sin dejar rastro. Todos, sin excepción: el Machete, el Calvo, y hasta ese viejo y apestoso trapo de Leprechaun.\nY cuando escuché de tus logros, decidí finalmente que ya era suficiente. No se puede arriesgar la cabeza por unas monedas toda la vida.\nTengo oro de sobra para no arrastrarme jamás ante ningún bastardo empolvado. Pero dejar el mar... a eso no estaba preparado. Así que decidí cambiar de oficio.";
			} 
			else 
			{
				dialog.text = "No exactamente, amigo. Esa idea se me pasaba por la cabeza de vez en cuando, pero nunca le presté mucha atención. Volvió a rondarme cuando me llegó el rumor de que toda la banda de fieles sabuesos de Tirax había desaparecido sin dejar rastro. Todos, uno por uno: el Machete, el Calvo, e incluso ese viejo y apestoso trapo de Leprechaun.\nY cuando las balas enemigas casi me vuelan la cabeza dos veces en una sola batalla, decidí por fin que ya era suficiente. No se puede arriesgar la vida por unas monedas eternamente.\nTengo oro de sobra para no arrastrarme nunca ante ningún bastardo empolvado con peluca. Pero separarme del mar... para eso no estaba preparado. Así que decidí cambiar de oficio.";
			}
			link.l1 = "Tesak, Calvo, Duende... ¿Sabes adónde se han ido?";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_B = true;
		break;

		case "SharlieEpilog_PikarOnUliss_B_2":
			dialog.text = "No, no lo sé. Y, la verdad, me da igual adónde se hayan largado esas sabandijas. Aunque sea al mismo demonio.";
			link.l1 = "Más o menos por ahí los mandé yo también.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_3";
		break;

		case "SharlieEpilog_PikarOnUliss_B_3":
			dialog.text = "¿Así que fuiste tú quien acabó con toda su compañía? ¡Vaya sorpresa! ¿Y Markus te lo perdonó?";
			link.l1 = "Él no lo sabe. Y, probablemente, nunca llegue a saberlo.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_4";
		break;

		case "SharlieEpilog_PikarOnUliss_B_4":
			dialog.text = "Así que, maldita sea, los dejé justo a tiempo, ja, ja. No me sorprendería que tampoco hubieras tenido piedad de mi cabeza\nPero hay algo que no logro entender: ¿para qué demonios necesitabas todo eso?";
			link.l1 = "Tenías razón: por un mísero trozo de oro, esos canallas son capaces de ahorcarse, traicionar y matar a cualquiera. Nos tendieron una trampa en una de las mazmorras del Sur del Main, contándonos un cuento sobre tesoros incalculables. Todo estaba planeado al detalle, y esos malditos brutos mordieron el anzuelo sin pensarlo dos veces. En vez de repartir el botín a partes iguales, decidieron que no valía la pena compartir, que era más fácil matarme y quedarse con todo.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_5";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_5":
			dialog.text = "¡Y ni de coña les salió, ja, ja! Espera, ¿y quién fue el que preparó esa trampa?";
			if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l1 = "Un tal Zorro, un justiciero popular español, vino a vengar lo de Cartagena. Quienquiera que hubiera sobrevivido a aquella masacre debía quedarse en las mazmorras para siempre: todas las salidas estaban cerradas. Pero el desgraciado no tuvo suerte: mi oficial lo engañó.";
			}
			else
			{
				link.l1 = "Un tal Zorro, el justiciero popular español, vengándose por Cartagena. Quien lograra sobrevivir a aquella carnicería infernal debía quedarse para siempre en las mazmorras: todas las salidas estaban cerradas a cal y canto. Yo conseguí escapar de allí. Pero a un precio muy alto.";
			}
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_6";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_6":
			dialog.text = "Al menos, sigues con vida. Y supongo que te llevaste todo el oro por el que casi pagaste con tu propio pellejo, ¿no?";
			link.l1 = "No había ningún oro allí. Era plomo dorado...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_7";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_7":
			dialog.text = "...";
			link.l1 = "Después de todo eso, decidí dejar a Tirax. Eres el primero a quien se lo cuento. Si no contar a mis oficiales.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_8";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_8":
			dialog.text = "No me gusta decir 'te lo advertí', pero... te lo advertí.";
			link.l1 = "Parar a tiempo no es precisamente mi punto fuerte. Así que tendrás que darme unas cuantas lecciones.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_9";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_9":
			dialog.text = "Ya me conoces: por un par de jarras de buen ron, hasta te cuento dónde escondo mi oro, je, je.";
			link.l1 = "Pero de mí no esperes tanta generosidad, ja, ja, ja. Con tus provisiones ya tienes suficiente.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_C_1":
			dialog.text = "Ya lo sé. Intentó darte unas cartas, de parte de un tal Ben o quizá Benedicto. Pero tú le soltaste que no conocías a ningún Ben y le amenazaste con echarlo de la taberna si seguía arruinándonos la diversión.";
			link.l1 = "Diablos... Parece que eran cartas del abad Benoît. Cartas importantes.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_C = true;
		break;

		case "SharlieEpilog_PikarOnUliss_C_2":
			dialog.text = "Bueno, entonces menos mal que los cogí yo. Je, je.  Sentí en las tripas que ese chiquillo no se equivocó de destinatario. Toma.";
			link.l1 = "Me has sacado de un buen apuro, "+npchar.name+", gracias.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_3";
		break;

		case "SharlieEpilog_PikarOnUliss_C_3":
			dialog.text = "Un simple 'gracias' no basta, amigo. Me debes una copa, y no cualquiera, sino la mejor que haya en Burdeos.";
			link.l1 = "Tendrás tu trago, mendigo. El ron aquí, claro, no se compara con el del Caribe, pero el vino... Ese seguro que nunca lo has probado.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_E_1":
			dialog.text = "No me ha tocado...";
			link.l1 = "Les envidio. Me gustaría volver a ver Burdeos como la primera vez. Seguramente prefieran el ron, pero aun así les aconsejo pasar por la feria del vino junto al ayuntamiento. Por nuestro clarete, los entendidos en el Caribe están dispuestos a pagar una fortuna.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_E = true;
		break;

		case "SharlieEpilog_PikarOnUliss_E_2":
			dialog.text = "Gracias por el consejo. ¿Me permite hacerle una pregunta?";
			link.l1 = "Por supuesto.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_3";
		break;

		case "SharlieEpilog_PikarOnUliss_E_3":
			dialog.text = "¿Cómo se siente ser pasajera después de tantos años al timón? ¿Ya se ha acostumbrado a su nuevo papel?";
			link.l1 = "Hum... No puedo quitarme de encima la sensación de que ya no tengo mi destino en mis propias manos. Pero al mismo tiempo siento un extraño alivio. Como si me hubiera quitado un cajón de balas de los hombros. Creo que aún es pronto para sacar conclusiones.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_4";
		break;

		case "SharlieEpilog_PikarOnUliss_E_4":
			dialog.text = "Teniendo en cuenta esta maldita calma chicha en la que hemos acabado, tiempo no os va a faltar.";
			link.l1 = "En buena compañía, hasta la calma es agradable. Y con la compañía, capitán, debo admitir que he tenido suerte.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_F_1":
			dialog.text = "Sí, sí, vino un mensajero, de parte de algún abad. Siempre se me olvida entregarle estas cartas. Tenga, aquí están.";
			link.l1 = "Excelente. Me habéis ayudado mucho, capitán. Os lo agradezco.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_F = true;
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A")){dialog.text = "Tienes razón.";}
			else {dialog.text = "Tiene razón.";}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_D_2";
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_2":
			dialog.text = "¡Viento por estribor! ¡Izad todas las velas, desde el foque hasta la cangreja! ¡A toda máquina!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InEstateDeMonpe";
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(CharacterFromID("SharlieEpilog_Pikar"), "quest", "quest10");
		break;
		
		case "SharlieEpilog_InEstateDeMonpe":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe");
		break;
		
		//Матрос 1 на верхней палубе
		case "SharlieEpilog_Sailor_1":
			dialog.text = "Excelente espada, "+GetTitle(NPChar,true)+". ¿Me deja ver?";
			link.l1 = "Quizás en otra ocasión.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_1";
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer05.wav");
		break;
		
		//Матрос 2 на верхней палубе
		case "SharlieEpilog_Sailor_2":
			dialog.text = "¿Cuándo van a sonar esas campanas de arena? Se me va a hacer agua la boca de tanto esperar.";
			link.l1 = "Paciencia, marinero.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-07.wav");
		break;
		
		//Матрос 3 на орудийной палубе
		case "SharlieEpilog_Sailor_3":
			dialog.text = "¿Viste la rata que acaba de pasar? Te juro que en mi vida he visto unas tan enormes.";
			link.l1 = "Vaya...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_3";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-04.wav");
		break;
		
		//Матрос 4 на орудийной палубе
		case "SharlieEpilog_Sailor_4":
			dialog.text = "¿Y ahora qué hago, monsieur? Me he emborrachado tanto que ni recuerdo cómo acabé en este barco. Ni siquiera soy marinero... Y en casa me esperan mi esposa y dos hijos.";
			link.l1 = "Deberías haber bebido menos. Pero ya es tarde: ahora tendrás que hacerte marinero.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_4";
			PlaySound("Voice\" + LanguageGetLanguage() + "\Ransack_2.wav");
		break;
		
		//Старший матрос
		case "SharlieEpilog_HighSailor_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+". Es un honor para nosotros tenerle a bordo de nuestro navío.";
			link.l1 = "Es usted muy cortés, monsieur marinero mayor. La cortesía no es precisamente la virtud más común entre los lobos de mar experimentados. Pero no incomodemos a la tripulación: no estamos en la corte de Su Majestad. Llámame simplemente: capitán.";
			link.l1.go = "SharlieEpilog_HighSailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;

		case "SharlieEpilog_HighSailor_2":
			dialog.text = "Bueno, no hace mucho que me hice marinero. Antes trabajaba de escribiente para el señor Levasseur. Y cuando a él lo… ejem… eliminaron, llegó un nuevo gobernador. Entre los de dentro pronto se supo qué clase de canalla era el señor de René de Boisdufle de Lestre. Entonces entendí que ya no encontraría un trabajo decente. La gente pensaría que yo lo sabía todo… y que me callé.";
			link.l1 = "¿Y no era así?";
			link.l1.go = "SharlieEpilog_HighSailor_3";
		break;

		case "SharlieEpilog_HighSailor_3":
			dialog.text = "Por supuesto que no. Nunca he tenido la costumbre de meterme en asuntos ajenos. Además, Levasseur castigaba con dureza la curiosidad.";
			link.l1 = "Eso lo creo sin dudar.";
			link.l1.go = "SharlieEpilog_HighSailor_4";
		break;

		case "SharlieEpilog_HighSailor_4":
			dialog.text = "Pues bien, cuando lo eliminaste, me enrolé como marinero en el primer barco pirata que encontré. Y, por extraño que parezca, me adapté y cambié bastante rápido. Incluso logré ganarme el respeto de los más temibles rufianes. Pero lo que hacían... No era para mí. Así fue como terminé aquí.";
			link.l1 = "¿Así que sabías de mi implicación en el destino de Levasseur?";
			link.l1.go = "SharlieEpilog_HighSailor_5";
		break;

		case "SharlieEpilog_HighSailor_5":
			dialog.text = "Por supuesto, capitán. Y me alegra que haya librado al mundo de ese monstruo. De paso, me sacó de mi cuartucho rancio. Me hizo mirar mi vida con otros ojos.";
			link.l1 = "Es increíble lo pequeño que es este mundo...";
			link.l1.go = "SharlieEpilog_HighSailor_6";
		break;

		case "SharlieEpilog_HighSailor_6":
			dialog.text = "Aunque suene contradictorio, el mundo es tan pequeño como grande.";
			link.l1 = "Qué curioso. Nunca lo había pensado.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
		break;
		
		case "SharlieEpilog_HighSailor_7":
			dialog.text = "Capitán "+pchar.lastname+"... Es una noche maravillosa, ¿no te parece?";
			link.l1 = "Quizá. Sólo una brisa suave del noroeste podría hacerlo aún mejor.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;
		
		//Диалог с боцманом Моко
		case "SharlieEpilog_Moko_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Capitán "+pchar.lastname+"...";
				link.l1 = "En realidad... Bueno, no importa. ¡Te recuerdo! Te llamas Moko. ¿Fuiste tú quien se bebió un barril entero de ron de una sentada?";
				link.l1.go = "SharlieEpilog_Moko_2";
			}
			else
			{
				dialog.text = "¿Qué desea… monsieur?";
				link.l1 = "No todos los días se ve a un tipo tan grande. ¿Cómo te llamas?";
				link.l1.go = "SharlieEpilog_Moko_4";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Kapitani Korabley-07.wav");
		break;

		case "SharlieEpilog_Moko_2":
			dialog.text = "Yo... Y desperté sólo dos días después.";
			link.l1 = "Otro en tu lugar no habría durado ni un par de horas. Si peleas tan bien como bebes, Jean tiene una suerte endiablada con su contramaestre.";
			link.l1.go = "SharlieEpilog_Moko_3";
		break;

		case "SharlieEpilog_Moko_3":
			dialog.text = "Y yo también tuve suerte con el capitán. Gracias a él encontré la libertad. Y gracias a ustedes. Me habría pudrido en las plantaciones si no hubieran ayudado a Jean.";
			link.l1 = "Ha sido una aventura interesante. Y me alegra que haya terminado mejor de lo que podría haber sido.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_4":
			dialog.text = ""+npchar.name+". Soy el contramaestre de este barco.";
			link.l1 = "Ja, ja, me gustaría ver a quien se atreva a llevarte la contraria. ¿Hace mucho que sirves al capitán?";
			link.l1.go = "SharlieEpilog_Moko_5";
		break;

		case "SharlieEpilog_Moko_5":
			dialog.text = "Unos cuantos años. Le debo mucho. Si no fuera por él, me habría pudrido en...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Moko_6";
		break;

		case "SharlieEpilog_Moko_6":
			dialog.text = "...";
			link.l1 = "¿Querías decir... en la plantación?";
			link.l1.go = "SharlieEpilog_Moko_7";
		break;

		case "SharlieEpilog_Moko_7":
			dialog.text = "...";
			link.l1 = "Déjalo, "+npchar.name+", por supuesto, no tienes por qué contarme nada, pero, si aún no te has dado cuenta, no soy de esos remilgados con peluca. ¿El capitán pagó tu rescate?";
			link.l1.go = "SharlieEpilog_Moko_8";
		break;

		case "SharlieEpilog_Moko_8":
			dialog.text = "Escapamos juntos. De una plantación en Maracaibo. Sin Jean no lo habríamos logrado. Desde entonces estoy en su tripulación. Al principio como marinero, y ahora soy el contramaestre.";
			link.l1 = "¿El capitán estuvo esclavizado? Nunca lo habría imaginado. Aunque, en mi armario también hay un par de esqueletos. Me alegra que hayas escapado de la bota española, "+npchar.name+".   Y   ¿qué tal te sienta ser marinero?";
			link.l1.go = "SharlieEpilog_Moko_9";
		break;

		case "SharlieEpilog_Moko_9":
			dialog.text = "Como si antes no hubiera vivido. El mar es mi hogar ahora.";
			link.l1 = "En eso te entiendo, amigo mío. Como nadie más.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_repeat":
			dialog.text = "Capitán "+pchar.lastname+"... ¿En qué puedo ayudar?";
			link.l1 = "Gracias, "+npchar.name+", por ahora no necesito nada.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		//Диалог с дворянином Бернардом
		case "SharlieEpilog_Bernard_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"¡ Qué alegría ver al menos un rostro sensato en este barco. Estos... marineros... son unos bárbaros.";
			link.l1 = "Yo, en su lugar, no hablaría así a bordo de un barco ajeno. No sé cómo llegó usted al Caribe, pero aquí, ¿sabe?, las reglas son otras. Le convendría mostrar respeto a la tripulación.";
			link.l1.go = "SharlieEpilog_Bernard_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;

		case "SharlieEpilog_Bernard_2":
			dialog.text = "¿Respeto? ¿A ellos? ¡Pero si son unos salvajes! Yo soy un noble, "+GetTitle(NPChar,true)+", estoy acostumbrado al orden, al servicio, a... ¡la civilización! Que se atrevan a llevarme la contraria: mi padre los...";
			link.l1 = "Tu padre creerá que moriste de fiebre en el viaje. Y difícilmente podrá probar lo contrario.";
			link.l1.go = "SharlieEpilog_Bernard_3";
		break;

		case "SharlieEpilog_Bernard_3":
			dialog.text = "¡Maldito sea ese coronel Fox! ¡Todo es por su culpa! Por su hija crucé el océano, renuncié a la comodidad, aguanté esas miradas de soslayo, esa comida espantosa, ese... vaivén. ¡Y ahora encima tengo que viajar en un barco ajeno!";
			link.l1 = "Coronel Fox…";
			link.l1.go = "SharlieEpilog_Bernard_4";
		break;

		case "SharlieEpilog_Bernard_4":
			dialog.text = "¿Lo conoce, "+GetTitle(NPChar,true)+"?";
			link.l1 = "Ejem... He oído hablar de él.";
			link.l1.go = "SharlieEpilog_Bernard_5";
		break;

		case "SharlieEpilog_Bernard_5":
			dialog.text = "Bueno, entonces no se han perdido de mucho. Ese hombre es la personificación de la tozudez ciega de un soldado y de sus prejuicios.";
			link.l1 = "Es militar...";
			link.l1.go = "SharlieEpilog_Bernard_6";
		break;

		case "SharlieEpilog_Bernard_6":
			dialog.text = "¡Exactamente! Y con eso está todo dicho. Cuando fui a pedirle permiso para ver a su hija, ¿sabe lo que hizo? ¿Sabe? ¡Me echó de la casa! ¡Sin decir ni una palabra!";
			link.l1 = "Pero usted, al parecer, no se rindió?";
			link.l1.go = "SharlieEpilog_Bernard_7";
		break;

		case "SharlieEpilog_Bernard_7":
			dialog.text = "¡Por supuesto! ¡Estuve buscando audiencia durante toda una semana! ¡Me humillé! Incluso... intenté sobornar a la guardia. Al final, conseguí colarme hasta él, sin invitación. Solo quería hablar.";
			link.l1 = "No creo que eso le haya hecho mucha gracia.";
			link.l1.go = "SharlieEpilog_Bernard_8";
		break;

		case "SharlieEpilog_Bernard_8":
			dialog.text = "¿Te alegras? ¡Oh, montó un verdadero escándalo! Me echaron, me prohibieron acercarme a la residencia, confiscaron el barco de mi padre y, para colmo, prohibieron a todos los capitanes ingleses llevarme a bordo. Tuve que buscar un barco francés en Martinica... Fue una pesadilla.";
			link.l1 = "Parece que lo habéis enfadado de verdad.";
			link.l1.go = "SharlieEpilog_Bernard_9";
		break;

		case "SharlieEpilog_Bernard_9":
			dialog.text = "Siempre estuvo en mi contra. Su frase favorita era: 'Hija de oficial, esposa de oficial'. A ustedes, "+GetTitle(NPChar,true)+", él consideró que era una pareja mucho más adecuada.";
			link.l1 = "Quizás esta vez tenía otros motivos...";
			link.l1.go = "SharlieEpilog_Bernard_10";
		break;

		case "SharlieEpilog_Bernard_10":
			dialog.text = "...";
			link.l1 = "Así que has venido aquí para ver a tu amada.";
			link.l1.go = "SharlieEpilog_Bernard_11";
		break;

		case "SharlieEpilog_Bernard_11":
			dialog.text = "Sí. No he recibido ni una sola carta de ella desde que se fue de Europa. Estoy seguro de que su padre simplemente intercepta las cartas. ¡No pudo haberme olvidado! Claro, era reservada conmigo... incluso fría... Pero no creo que me haya borrado de su vida.";
			link.l1 = "Lo siento por usted, monsieur. Las heridas del alma sanan mucho más lento que las del cuerpo. Espere... ¿Por qué, siendo usted inglés, va a Burdeos?";
			link.l1.go = "SharlieEpilog_Bernard_12";
		break;

		case "SharlieEpilog_Bernard_12":
			dialog.text = "No pienso volver a casa con la cabeza gacha. Tendré que quedarme un tiempo en la finca de mi tío en Burdeos, hasta que todo se calme. Por cierto, su propiedad es mucho más espaciosa y elegante que la nuestra. Y el servicio está mejor entrenado.";
			link.l1 = "Bueno, supongo que это не la peor salida. Quizá incluso encuentres otra dama de tu agrado. Créeme, en Burdeos abundan las jóvenes encantadoras.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
		break;
		
		case "SharlieEpilog_Bernard_repeat":
			dialog.text = "¿Cuándo llegaremos por fin? "+GetTitle(NPChar,true)+"? Sufro terriblemente rodeada de todos estos... caballeros. Me urge darme un baño.";
			link.l1 = "Me temo que durante los próximos dos meses sólo podrá soñar con ella.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;
		
		//Диалог с Книппелем на корабле Улисс
		case "SharlieEpilog_Knippel_1":
			dialog.text = "Maldito encalmado, que lo reviente un disparo de metralla.";
			link.l1 = "No refunfuñes, "+npchar.name+", tarde o temprano el viento se levantará.";
			link.l1.go = "SharlieEpilog_Knippel_2";
		break;

		case "SharlieEpilog_Knippel_2":
			dialog.text = "¿Y qué se supone que haga mientras tanto, señor? Ni siquiera puedo revisar los cañones... Al fin y al cabo, estamos en un barco ajeno.";
			link.l1 = "Intenta simplemente descansar. No todo es trabajo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		case "SharlieEpilog_Knippel_repeat":
			dialog.text = "Maldito encalmado...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		//Диалог с Лонгвэем на корабле Улисс
		case "SharlieEpilog_Longway_1":
			dialog.text = "No está mal el barco, señor capitán. ¿Usted también lo cree?";
			link.l1 = "¿Incluso mejor que Meifeng?";
			link.l1.go = "SharlieEpilog_Longway_2";
		break;

		case "SharlieEpilog_Longway_2":
			dialog.text = "Para "+npchar.name+" no hay barco mejor que el Meifeng. Ningún otro podrá ceñirse al viento tan bien como él.";
			link.l1 = "Tranquila, "+npchar.name+", era una broma. Por supuesto, Meifeng no tiene rival. Pero el Ulysses también es un buen barco. Sólido.";
			link.l1.go = "SharlieEpilog_Longway_3";
		break;

		case "SharlieEpilog_Longway_3":
			dialog.text = ""+npchar.name+" querer estar al timón. Sentir cómo el barco obedece a la mano...";
			link.l1 = "Por desgracia, amigo mío, este barco no es nuestro. Mejor ve y ofrece a ese grandullón practicar esgrima contigo. A los dos les vendrá bien.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		case "SharlieEpilog_Longway_repeat":
			dialog.text = "¿A qué velocidad podremos ir si el viento es favorable?";
			link.l1 = "Eso no te lo puedo asegurar, "+npchar.name+". Mejor pregúntale a su piloto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		//Диалог с Тонзагом на корабле Улисс
		case "SharlieEpilog_Tonzag_1":
			dialog.text = "¿Viste al gigante que tienen de contramaestre? Dicen que puede aplastar un coco con una sola mano.";
			link.l1 = "Ja, ja. Veo que le tienes algo de miedo, ¿eh?";
			link.l1.go = "SharlieEpilog_Tonzag_2";
		break;

		case "SharlieEpilog_Tonzag_2":
			dialog.text = "¿Y eso por qué? El tamaño no lo es todo. He lidiado con cosas mucho peores.";
			link.l1 = "¿Entonces por qué no le propones una pelea a puño limpio? Uno contra uno, en igualdad de condiciones.";
			link.l1.go = "SharlieEpilog_Tonzag_3";
		break;

		case "SharlieEpilog_Tonzag_3":
			dialog.text = "Argh...";
			link.l1 = "Te has puesto pálido. Ja, ja. Bueno, si no quieres, no quieres. Cuidaremos esos huesos tuyos, que ya no son tan jóvenes.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		case "SharlieEpilog_Tonzag_repeat":
			dialog.text = "En estas aguas hay tantos peces que podrías recogerlos con un balde, y estos holgazanes ni siquiera se han dignado lanzar una red.";
			link.l1 = "Habla con su contramaestre. Creo que sabrá apreciar tu comentario, je, je.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		//Диалог с Тичингиту, охраняющим золото
		case "SharlieEpilog_Tichingitu_21":
			dialog.text = "El oro está a salvo, capitán "+pchar.name+". Que Tichinguito lo vigile bien.";
			link.l1 = "Gracias, amigo. Alonso pronto te relevará.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tichingitu_21";
		break;
		
		//Диалог с Книппелем, охраняющим золото
		case "SharlieEpilog_Knippel_21":
			dialog.text = "¡Rayos y centellas, señor, en este cascarón hay más ratas de las que he visto en toda mi vida!";
			link.l1 = "El barco estuvo mucho tiempo en el puerto, sin el cuidado adecuado. La nueva tripulación pronto se deshará de ellos.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_21";
		break;
		
		//Диалог с Лонгвэем, охраняющим золото
		case "SharlieEpilog_Longway_21":
			dialog.text = "Longway oye el ruido de la cadena. ¿El capitán ha echado el ancla?";
			link.l1 = "Ha sido nuestro pasajero quien ha soltado el seguro. El viento aún es muy flojo, pero espero que no dure mucho.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_21";
		break;
		
		//Диалог с Тонзагом, охраняющим золото
		case "SharlieEpilog_Tonzag_21":
			dialog.text = "Sí, maldita sea... Ahora mismo no me vendría mal una jarra de ron fuerte.";
			link.l1 = "Pronto será la cena, ten paciencia. Alonso te relevará.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_21";
		break;
		
		//Диалог с Мэри перед походом в каюту
		case "SharlieEpilog_Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", querida, ¿cómo te sientes?";
			link.l1.go = "SharlieEpilog_Mary_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_12":
			dialog.text = "...";
			link.l1 = "Vamos, querida, ¿de verdad te has enfadado conmigo solo porque fui a la tienda a por vino?";
			link.l1.go = "SharlieEpilog_Mary_13";
		break;

		case "SharlieEpilog_Mary_13":
			dialog.text = "¿A la tienda por vino? ¡Podrías al menos haber avisado! ¿Cómo voy a saber yo que no estabas en un burdel, con alguna… o con todas a la vez?!";
			link.l1 = "Cariño, ¿crees que me arriesgaría así? Tengo a la esposa más hermosa, inteligente y terriblemente celosa de todo el archipiélago. ¿De verdad piensas que me fijaría en unas baratijas de puerto?";
			link.l1.go = "SharlieEpilog_Mary_14";
		break;

		case "SharlieEpilog_Mary_14":
			dialog.text = "¡Al menos podrías haberme dicho algo, sí! Yo estaba sentada allí y...";
			link.l1 = "Te lo prometo, la próxima vez no solo te avisaré, sino que te llevaré conmigo. Y ahora... de repente me ha entrado curiosidad por saber si todo está en orden con los muebles del camarote del capitán. Especialmente con la cama. ¿Lo comprobamos?";
			link.l1.go = "SharlieEpilog_Mary_15";
		break;

		case "SharlieEpilog_Mary_15":
			dialog.text = ""+pchar.name+"... ¿Y si alguien entra?\nHmm... ahora lo deseo aún más.";
			link.l1 = "Entonces no perdamos ni un segundo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Элен перед походом в каюту
		case "SharlieEpilog_Helena_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", querida, ¿cómo te sientes?";
			link.l1.go = "SharlieEpilog_Helena_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_12":
			dialog.text = "...";
			link.l1 = "Vamos, querida, ¿de verdad te has enfadado conmigo solo porque fui a la tienda a por vino?";
			link.l1.go = "SharlieEpilog_Helena_13";
		break;

		case "SharlieEpilog_Helena_13":
			dialog.text = "Podrías haberme llevado contigo. ¿O crees que lo habría hecho peor que tus compinches?";
			link.l1 = "Creo que no tendrías problemas en eclipsarlas. Pero entonces yo no estaría pensando en el vino.";
			link.l1.go = "SharlieEpilog_Helena_14";
		break;

		case "SharlieEpilog_Helena_14":
			dialog.text = "¿Y sobre qué?";
			link.l1 = "Pensar en estar a solas contigo justo allí... Y esa idea no me deja en paz ahora mismo.";
			link.l1.go = "SharlieEpilog_Helena_15";
		break;

		case "SharlieEpilog_Helena_15":
			dialog.text = "¿Ah, sí? ¿Y dónde piensas esconderte de las miradas curiosas?";
			link.l1 = "En el camarote del capitán. Supongo que deberíamos comprobar la resistencia de su cama.";
			link.l1.go = "SharlieEpilog_Helena_16";
		break;

		case "SharlieEpilog_Helena_16":
			dialog.text = "Ja, ja. ¿Y si el capitán nos sorprende?\nAunque… sólo pensarlo hace que mi corazón lata más rápido.";
			link.l1 = "¡Entonces no perdamos tiempo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Мэри в каюте
		case "SharlieEpilog_Mary_21":
			dialog.text = "Ha sido maravilloso, mi capitán...\nTengo una noticia para ti.";
			link.l1 = "¿Una noticia? Te escucho con atención.";
			link.l1.go = "SharlieEpilog_Mary_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Mary_22":
			dialog.text = ""+pchar.name+"...   Vamos a tener un hijo. Estoy embarazada, sí.";
			link.l1 = "Amor mío... ¿Es verdad?";
			link.l1.go = "SharlieEpilog_Mary_23";
		break;

		case "SharlieEpilog_Mary_23":
			dialog.text = "Vas a ser padre, "+pchar.name+"!";
			link.l1 = ""+npchar.name+"... ¡Es increíble!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Mary_31":
			dialog.text = "¿Estás feliz, mi amor?";
			link.l1 = "¿Feliz? ¿Estás bromeando? ¡Por Dios, soy el hombre más feliz del mundo! Pero... ¿por qué no me lo contaste antes?";
			link.l1.go = "SharlieEpilog_Mary_32";
		break;

		case "SharlieEpilog_Mary_32":
			dialog.text = "¿Para retrasar la partida? Tengo muchas ganas de conocer a tu padre, "+pchar.name+".";
			link.l1 = ""+npchar.name+"... ¡Te amo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		//Диалог с Элен в каюте
		case "SharlieEpilog_Helena_21":
			dialog.text = "Estuviste, como siempre, a la altura, cariño. Tengo una noticia para ti.";
			link.l1 = "¿Una noticia? Soy todo oídos.";
			link.l1.go = "SharlieEpilog_Helena_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Helena_22":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+GetFullName(pchar)+", chevalier de Monpe - vas a ser padre.";
			link.l1 = "¿Es... es verdad?";
			link.l1.go = "SharlieEpilog_Helena_23";
		break;

		case "SharlieEpilog_Helena_23":
			dialog.text = "Tan cierto como que me llamo "+npchar.name+".   En menos de medio año tendremos un hijo: un pequeño monsieur de Mor... o, tal vez, una mademoiselle.";
			link.l1 = "¡Hélène... Esto es increíble!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Helena_31":
			dialog.text = "...";
			link.l1 = "¡Así que por eso no quisiste brindar con nosotros antes de zarpar! Pero… ¿por qué no me lo dijiste antes?";
			link.l1.go = "SharlieEpilog_Helena_32";
		break;

		case "SharlieEpilog_Helena_32":
			dialog.text = "Temía que decidieras no arriesgarte y te quedaras en el archipiélago. Quería que cumplieras el deseo de tu padre. Y además... tengo muchas ganas de conocerlo yo misma.";
			link.l1 = ""+npchar.name+"… ¡Te amo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		// Диалог с Пикаром
		case "SharlieEpilog_PikarInCabin_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Vaya, vaya... ¿Y qué estamos haciendo aquí? ¿Pequeños gascones?";
				link.l1 = "¡Ja, ja, ja!   Voy a tener un hijo, "+npchar.name+"¡ Voy a ser padre !";
				link.l1.go = "SharlieEpilog_PikarInCabin_1_1";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+". ¿No le parece que usar el camarote del capitán sin su permiso es demasiado, incluso para alguien de su rango?";
				link.l1 = "Disculpe, capitán. ¡Pero tengo una buena razón! ¡Voy a ser padre!";
				link.l1.go = "SharlieEpilog_PikarInCabin_12";
			}
			SharlieEpilog_PikarInCabin_camera_2();
		break;
		
		case "SharlieEpilog_PikarInCabin_1_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_2":
			dialog.text = "¡O una hija!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_2_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_2_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_3", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_3":
			dialog.text = "¿Y me lo ocultabas, canalla? ¡Y yo que te consideraba mi amigo!";
			link.l1 = "¡Yo mismo acabo de enterarme! ¿Te imaginas? ¡Yo! ¡Voy a ser padre!";
			link.l1.go = "SharlieEpilog_PikarInCabin_4";
		break;

		case "SharlieEpilog_PikarInCabin_4":
			dialog.text = "¡Ja, ja, ja! ¡De verdad que eres feliz, amigo! Nunca te había visto así.\nBueno, sigan charlando ustedes, yo mientras preparo los cañones para el saludo de celebración. Avísame cuando estés listo para dar la orden.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;

		case "SharlieEpilog_PikarInCabin_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				sld = CharacterFromID("Mary");
			}
			dialog.text = "Ja... Créame, ya me imaginaba para qué había venido usted por aquí.";
			link.l1 = "¡Que no! "+sld.name+" ¡Estoy embarazada! ¡Voy a tener un hijo!";
			link.l1.go = "SharlieEpilog_PikarInCabin_12_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_12_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_13":
			dialog.text = "¡O una hija!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_13_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_13_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_14", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_14":
			dialog.text = "Ejem... ¡Pues bien, mis más sinceras felicitaciones!\nDaré la orden: haremos una salva de celebración con todos los cañones. Avisadme cuando estéis listos para dar la señal.\nMientras tanto... la cabina está a vuestra disposición.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;
		
		// Диалог с Пикаром после интима с женой
		case "SharlieEpilog_PikarZalp_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Ejem, ejem... Bueno, papá... ¿veo que ya quieres encargar otro heredero, eh?";
				link.l1 = "¡Ja, ja! Si fuera por mí, ¡haría una docena de una vez! Bueno, amigo, ¿lanzamos una andanada con todos los cañones?";
				link.l1.go = "SharlieEpilog_PikarZalp_2";
				link.l2 = "Me temo, amigo, que no funciona así. Pero lo intentamos.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"...";
				link.l1 = "¿Y bien, capitán, disparamos una andanada con todos los cañones?";
				link.l1.go = "SharlieEpilog_PikarZalp_3";
				link.l2 = "Ahora no.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_PikarZalp_1";
		break;
		
		case "SharlieEpilog_PikarZalp_2":
			dialog.text = "¡La tripulación solo espera su orden! Dé la señal, "+GetTitle(NPChar,true)+".";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_3":
			dialog.text = "La tripulación está lista. Ordene.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_final":
			dialog.text = "...";
			link.l1 = "¡Artilleros! ¡Fuego con todos los cañones! ¡Disparen!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_ZalpInSea");
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(pchar, "quest", "quest10");
			CharacterTurnToLoc(npchar, "quest", "quest10");
		break;
		
		// Диалог с отцом в поместье де Монпе
		case "SharlieEpilog_HenriDeMonper_1":
			NextMonth = GetDataMonth() + 2;
			if (NextMonth == 13) NextMonth = 1;
			else if (NextMonth == 14) NextMonth = 2;
			Month = XI_ConvertString("MonthVoc_" + NextMonth);
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"... ¡Cuánto me alegra verte, hijo!";
			if (GetDataMonth() >= 4 && GetDataMonth() <= 10)
			{
				link.l1 = "Padre... No puedo creer que esté de vuelta en casa... Ya casi había olvidado cómo es la nieve. Parece que aquí no ha cambiado nada...";
			}
			else
			{
				link.l1 = "Padre... No puedo creer que esté de vuelta en casa... Parece que hasta la nieve ha decidido caer en honor a este momento. "+month+". Aquí no ha cambiado absolutamente nada...";
			}
			link.l1.go = "SharlieEpilog_HenriDeMonper_2";
			locCameraFromToPos(-8.76, 7.86, 0.75, true, -7.41, 6.11, 0.18);
			Achievment_Set("ach_CL_202");
		break;
		
		case "SharlieEpilog_HenriDeMonper_2":
			dialog.text = "¡Pero de ti no se puede decir lo mismo! Tu porte, tu manera de andar, tus cicatrices\n"+"No, ya no eres aquel niño mimado al que despedí cuando partiste a tierras lejanas.";
			link.l1 = "En el Caribe uno madura rápido, padre. Pero ya tendremos tiempo para hablar de eso. Cuénteme mejor, ¿cómo está su salud? Espero que la enfermedad haya retrocedido, si está aquí delante de mí, vestido de gala.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_3";
		break;
		
		case "SharlieEpilog_HenriDeMonper_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				dialog.text = "Por desgracia, "+pchar.name+", ella solo se aferró aún más fuerte a mi cuello. Pero ¿cómo iba yo a recibir a mi querido hijo vestido de manera ordinaria? Para mí, este es un día grandioso, "+pchar.name+"\n"+"Parece que tienes que presentarme a alguien.";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_10");
			}
			else
			{
				dialog.text = "Por desgracia, "+pchar.name+", su carácter solo se ha hecho más fuerte con los años. Pero ¿cómo podía yo recibir a mi querido hijo vestido de manera corriente? Para mí, este es un día grandioso, "+pchar.name+"\n"+"Veo que no has venido solo\n"+"¿Debes de tener hambre después del viaje? ¡Suzanne ha preparado foie gras según tu receta favorita!\n"+"Ven a la mesa, así nos presentas por el camino.";
				link.l1 = "Debo admitir que ya percibí ese aroma al acercarme a la finca.";
				link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "...";
			link.l1 = "Padre, permítame presentarle a mi esposa - "+sld.name+" "+pchar.lastname+". "+sld.name+", este es mi padre: el caballero "+GetCharacterName("Henri")+" "+GetCharacterName("de Monper")+".";
			link.l1.go = "SharlieEpilog_HenriDeMonper_5";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
				dialog.text = ""+pchar.name+", ¡estoy fascinado! Tu elegida no se parece en nada a las consentidas damas de sociedad a las que estamos acostumbrados aquí. Me atrevo a suponer que maneja un barco con la misma seguridad con la que gobierna el corazón de mi hijo.";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_1";
				CharacterTurnByChr(npchar, sld);
			}
			else
			{
				sld = CharacterFromID("Mary");
				dialog.text = "Es un gran placer para mí conocerla, señora. Permítame asegurarle que mi hijo tiene un gusto excelente.";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_1";
				CharacterTurnByChr(npchar, sld);
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2":
			dialog.text = "¡Me halaga, caballero! Tiene razón, de hecho puedo mantener el timón firme incluso en la peor tormenta. Sin embargo, en cuanto al corazón de su hijo, no hay necesidad de gobernarlo. Estamos unidos en nuestras metas y aspiraciones.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_2_1";
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_3":
			dialog.text = "El abad Benoît le describió como una joven sabia y valiente, y parece que no exageró. Me alegra que "+pchar.name+" he encontrado en ti no solo a una esposa, sino también a una compañera de espíritu igual a mí\n"+"¿Debes de tener hambre después del viaje? ¡Suzanne ha preparado foie gras según tu receta favorita!\n"+"¡Bien, invito a todos a la mesa! Y espero que, de camino, podamos conocernos mejor.";
			link.l1 = "Lo confieso, percibí ese aroma incluso antes de llegar a la finca.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2":
			dialog.text = "¡Me alegra conocerle, caballero! "+pchar.name+" me habló mucho de usted, y me lo imaginaba justo así, ¡sí!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_2_1";
			CharacterTurnByChr(pchar, npchar);
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_3":
			sld = CharacterFromID("Mary");
			dialog.text = ""+pchar.name+", ¡estoy fascinado! Tu elegida no se parece en nada a las damas empolvadas de la alta sociedad, y ahí reside su verdadero valor\n"+"Me parece que has elegido una rosa hermosa en vez de unos lirios delicados y caprichosos.";
			link.l1 = "La rosa salvaje, padre… "+sld.name+"  - un verdadero tesoro. Estoy seguro de que estarán de acuerdo conmigo cuando la conozcan mejor.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_4";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_4":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "ты познакомишь меня с остальными";
			else sStr = "ты представишь меня нашему гостю";
			dialog.text = "¡Entonces no vamos a retrasar este momento! ¿Debes de tener hambre después del viaje, verdad? ¡Suzanne ha preparado hígado de oca según tu receta favorita!\n"+"¡Les invito a la mesa! Y de paso, espero que "+sStr+"";
			link.l1 = "Debo admitir que percibí ese aroma incluso antes de llegar a la finca.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			CharacterTurnByChr(CharacterFromID("HenriDeMonper"), pchar);
		break;
		
		case "SharlieEpilog_HenriDeMonper_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_14");
		break;
		
		case "SharlieEpilog_HenriDeMonper_7":
			dialog.text = "...";
			link.l1 = "Querida, tienes que probar esto: nada se compara con el foie gras preparado según nuestra receta familiar. Nos la dejó el abuelo, y a él se la trajeron de regalo desde un país mediterráneo.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_15");
		break;
		
		// диалог на ужине в поместье де Монпе
		case "SharlieEpilog_InKitchenDeMonpe":
			dialog.text = "";
			link.l1 = "No quisiera empezar el banquete con tristeza, pero como familia debemos recordar a quienes se han ido antes que nosotros. Les pido que levanten sus copas por Michel. Que el Señor conceda paz a su alma.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_2":
			dialog.text = "";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "добрых друзей";
				else sStr = "соратника";
				dialog.text = "";
				link.l1 = "Tengo tantas cosas que preguntarte, "+pchar.name+"... Pero antes, deja que escuchemos a tu esposa y "+sStr+". Por favor, contadme cómo conocisteis a Charles.";
			}
			else
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "твоих добрых друзей";
				else sStr = "твоего друга";
				dialog.text = "";
				link.l1 = "Tengo tantas cosas que preguntarte, "+pchar.name+"... Pero antes, déjame escuchar "+sStr+". Por favor, cuéntenos cómo conoció a Charles.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		// if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
		
		case "SharlieEpilog_InKitchenDeMonpe_4":
			dialog.text = "";
			link.l1 = "¡Tengo tantas ganas de escucharlo como usted!";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Estuve en peligro de muerte... "+pchar.name+", como un verdadero caballero, no permitió que ocurriera una desgracia. Me defendió y puso en su sitio a esos canallas, ¡sí!";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = ""+pchar.name+" me arrancaste de las manos de un inglés despreciable que se atrevió a... secuestrarme. Si hubieras llegado aunque fuera una hora más tarde, nunca nos habríamos conocido.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5_1":
			dialog.text = "";
			link.l1 = "No dudaba de que actuaría como corresponde a un verdadero noble. El honor no es solo una palabra para nuestra familia. Estoy orgulloso de ti, hijo.";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = ""+sld.name+" entrar en casa de cara pálida para buscar comida. Cara pálida sorprender "+sld.name+" - y mandarlo a la cárcel. Capitán "+pchar.name+" venir, liberar "+sld.name+" de la cárcel. Desde entonces "+sld.name+" servir al capitán "+pchar.name+" y serte fiel hasta el último aliento.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6_1":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = "Es reconfortante saber que mi hijo no solo es un noble caballero, sino también un hombre de buen corazón. Me alegra que a su lado estén amigos tan leales como usted, "+sld.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Un día el capitán vino a mi casa buscando trabajo. Le di un encargo y lo cumplió como era debido. Al jefe le cayó bien, y cada vez lo fue metiendo más en sus asuntos, mientras que a mí me mandó a su barco para vigilarlo... Y luego ese... señor levó anclas en silencio, que me arranquen la barba, y se largó del archipiélago sin decirle una palabra al capitán. Lo dejó solo en el lío que él mismo había montado. Le ofrecí mi ayuda al capitán y, aunque Richard se portó con él como un canalla, que le revienten la popa, el capitán no me echó.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Longwei y el señor capitán trabajaban para la misma persona. Pero esa persona traicionó a Longwei. Entonces Longwei decidió: no servir más a esa persona. El señor capitán me llevó a su barco como oficial y ha hecho mucho por Longwei.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "La primera vez que nos cruzamos fue en la taberna de Bridgetown: "+pchar.name+" estaba buscando un encargo, y yo - a alguien de confianza para llevarlo a cabo. Ese encuentro fue solo el principio: después vinieron acontecimientos que entrelazaron nuestros destinos. Me convertí en su oficial, y ahora, sin dudarlo, puedo llamarlo mi amigo: un hombre por el que arriesgaría la vida.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7_2":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Ver a la persona más allá de las circunstancias es una habilidad poco común. Eso, quizás, demuestra que mi hijo no carece de sensatez.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Me alegra que mi hijo no sea un militar sin alma, sino un verdadero líder capaz de cuidar de sus compañeros.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "No todos los días se oyen palabras así. Diría que es la mejor prueba de que mi hijo no solo es un hábil marinero, sino también un buen amigo.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8":
			dialog.text = "";
			link.l1 = "Nos conocimos en Burdeos. El capitán se embarcó con nosotros como pasajero y lo llevamos hasta Martinica. Desde entonces, y hasta que partimos hacia aquí, fui la voz de su tripulación y observé cómo "+GetFullName(pchar)+" paso a paso se fue convirtiendo en quien es ahora.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8_1":
			dialog.text = "";
			link.l1 = "¿Así que usted conoció a Charles siendo aún ese muchacho insoportable que, por mi insistencia, dejó su hogar? Supongo, monsieur, que tendremos mucho de qué hablar.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_9";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_9":
			dialog.text = "";
			link.l1 = "Mi querido "+pchar.name+", has recorrido un camino largo y glorioso... Partiste a la salvaje sabana tras la piel de un simple conejo, pero luchaste contra un león y regresaste triunfante, llevando su piel sobre tus hombros. Ahora estoy más tranquilo que nunca por el destino de nuestra hacienda y de todas nuestras tierras.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_10";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_10":
			dialog.text = "";
			link.l1 = "No veo la hora de entregarte cuanto antes las riendas de todos los asuntos de nuestra familia. Habrá mucho trabajo por delante, pero creo firmemente que el mismo Señor te mira con bendición, y que no solo podrás preservar el legado que se te confía, sino también aumentar el honor y la prosperidad de la familia de Monpe.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_11";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_11": //выбор Шарля
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = "Es un gran honor para mí ser su hijo y heredero. Asumiré con gusto todas las responsabilidades de nuestra familia. Estoy seguro de que mi esposa será un apoyo fiel en esta tarea. Prometo hacer todo lo posible para engrandecer aún más nuestro linaje... Y el primer paso para su prosperidad será el nacimiento de un hijo.";
				link.l1.go = "SharlieEpilog_ChooseEstate_HaveWife_1";
			}
			else
			{
				link.l1 = "Es un gran honor para mí ser su hijo y heredero. Asumo con gusto todas las responsabilidades de nuestra familia y prometo hacer todo lo posible para engrandecer aún más nuestro apellido.";
				link.l1.go = "SharlieEpilog_ChooseEstate_Single_1";
			}
			link.l2 = "Padre, los años en el Nuevo Mundo me han cambiado. Me temo que ya no podré acostumbrarme al ritmo pausado de la vida aquí, en Europa.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_HaveWife_1";
			}
			else
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_Single_1";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		// --> Выбрал остаться в поместье с женой
		case "SharlieEpilog_ChooseEstate_HaveWife_1":
			dialog.text = "";
			link.l1 = ""+pchar.name+", ¿de verdad...?";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_HaveWife_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "Sí, padre. "+sld.name+" estoy embarazada.";
			link.l1.go = "SharlieEpilog_HaveWife_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_13":
			dialog.text = "";
			link.l1 = "¡Son verdaderamente grandes noticias, mi querido hijo! ¡El Señor ha escuchado mis plegarias! Que todos los presentes sean testigos: en honor al recién nacido, ¡organizaré el baile más fastuoso que haya conocido nuestra hacienda! Alcemos las copas, ¡por el heredero!";
			link.l1.go = "SharlieEpilog_HaveWife_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_HaveWife_14":
			dialog.text = "";
			link.l1 = "¡O a la heredera!";
			link.l1.go = "SharlieEpilog_HaveWife_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_15":
			dialog.text = "";
			link.l1 = "¡Por un nuevo capítulo en la historia de nuestra familia!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_16":
			dialog.text = "";
			link.l1 = "¡Por el futuro guerrero o la buena hija!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_HaveWife_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "¡Por la buena salud del recién nacido!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "¡Por el destino que os unió!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "¡Por el brillante futuro de vuestra familia!";
			}
			link.l1.go = "SharlieEpilog_HaveWife_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_HaveWife_18":
			dialog.text = "";
			link.l1 = "¡Por el futuro de Alonso de Mor o de Alonsita de Mor!";
			link.l1.go = "SharlieEpilog_HaveWife_19";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_HaveWife_19":
			dialog.text = "";
			link.l1 = "¡Ja, ja, ja!";
			link.l1.go = "SharlieEpilog_HaveWife_20";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_20":
			dialog.text = "";
			link.l1 = "¡Ja, ja!";
			link.l1.go = "SharlieEpilog_HaveWife_21";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_21":
			dialog.text = "";
			link.l1 = "¡Ja, ja, ja!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_toast":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_toast");
		break;
		// <-- Выбрал остаться в поместье с женой
		
		// --> Выбрал остаться в поместье будучи холостяком
		case "SharlieEpilog_ChooseEstate_Single_1":
			dialog.text = "";
			link.l1 = "Para mí es un gran honor ser su hijo y heredero. Con gusto asumiré todas las responsabilidades de nuestra familia y prometo hacer todo lo posible para engrandecer aún más nuestro apellido.";
			link.l1.go = "SharlieEpilog_ChooseEstate_Single_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_ChooseEstate_Single_2":
			dialog.text = "";
			link.l1 = "Dime, "+pchar.name+", ¿has pensado en mi propuesta de casarte con Ivonne?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_13":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_ChooseCaribbean"))
			{
				link.l1 = "Lo confieso, padre… Yvonne nunca estuvo cerca de mi corazón. Pero en el Nuevo Mundo hay muchas mujeres encantadoras. Se lo prometo: cuando encuentre a una digna, no dudaré.";
			}
			else
			{
				link.l1 = "Lo confieso, padre... Yvonne nunca estuvo cerca de mi corazón. Pero en Francia hay muchas muchachas encantadoras. Se lo prometo: cuando encuentre a una digna, no dudaré.";
			}
			link.l1.go = "SharlieEpilog_Single_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_14":
			dialog.text = "";
			link.l1 = "Me agrada tu actitud, mi querido hijo. Levantemos las copas: por ti, por tus logros y por tu digno regreso a casa.";
			link.l1.go = "SharlieEpilog_Single_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_15":
			dialog.text = "";
			link.l1 = "Por los amigos leales, sin los cuales no sobreviviríamos en el Nuevo Mundo.";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_Single_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_16":
			dialog.text = "";
			link.l1 = "¡Por el gran corazón del capitán Charles!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_Single_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "¡Por la férrea voluntad del capitán!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "¡Por la sabiduría del señor capitán!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "¡Por la lealtad a la causa!";
			}
			link.l1.go = "SharlieEpilog_Single_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_Single_18":
			dialog.text = "";
			link.l1 = "¡Por la habilidad de salir siempre bien parado!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		// <-- Выбрал остаться в поместье будучи холостяком
		
		// Шарль губернатор разговаривает с зелёным капитаном
		case "SharlieEpilog_GreenCaptain":
			dialog.text = "";
			link.l1 = "He oído que ha solicitado una audiencia con gran insistencia. Entonces, ¿qué desea del gobernador de Martinica?";
			link.l1.go = "SharlieEpilog_GreenCaptain_1";
			locCameraFromToPos(-1.80, 3.84, -9.08, true, -2.38, 2.21, -7.33);
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer_common_2.wav");
		break;
		
		case "SharlieEpilog_GreenCaptain_1":
			dialog.text = "Quiero hablar sobre trabajar para el bien de la corona de Francia.";
			link.l1 = "Sí, tengo un encargo para el que necesitarás actuar con la máxima rapidez y demostrar tu destreza en el combate naval. ¿Estás listo para mostrar de lo que eres capaz?";
			link.l1.go = "SharlieEpilog_GreenCaptain_2";
		break;

		case "SharlieEpilog_GreenCaptain_2":
			dialog.text = "Su Excelencia, ¿podría explicar con más detalle en qué consiste la tarea que se avecina?";
			link.l1 = "Por supuesto. Debe encontrar un barco correo español llamado 'Santa Esperanza', abordarlo y traerme los documentos que encuentre en el camarote del capitán. El barco que le indico pasará cerca de Trinidad dentro de unos doce días.";
			link.l1.go = "SharlieEpilog_GreenCaptain_3";
		break;

		case "SharlieEpilog_GreenCaptain_3":
			dialog.text = "De acuerdo, me encargo de esta tarea. ¿Y qué documentos debo buscar?";
			link.l1 = "La correspondencia postal. Allí, entre otras cosas, habrá documentos muy importantes para mí. Pero no necesita revisar los papeles, simplemente tráigame el paquete completo. Por este favor le pagaré quince mil pesos... Así que le esperaré en mi residencia con los resultados de su trabajo.";
			link.l1.go = "SharlieEpilog_GreenCaptain_4";
		break;

		case "SharlieEpilog_GreenCaptain_4":
			dialog.text = "Supongo que no les haré esperar mucho, Su Alteza.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_5");
		break;
		
		//Шарль разговаривает с комендантом форта
		case "SharlieEpilog_KomendantFort":
			dialog.text = "Su Excelencia... ¿Me permite informar?";
			link.l1 = "Informe, "+GetAddress_Form(NPChar)+" "+npchar.lastname+".";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) link.l1.go = "SharlieEpilog_KomendantFort_1";
			else link.l1.go = "SharlieEpilog_KomendantFort_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\military02.wav");
		break;
		
		case "SharlieEpilog_KomendantFort_1":
			dialog.text = "Ejém, ejém...";
			link.l1 = "Hable con libertad. No tengo secretos para mi esposa.";
			link.l1.go = "SharlieEpilog_KomendantFort_2";
		break;
		
		case "SharlieEpilog_KomendantFort_2":
			dialog.text = "La inteligencia informa: una escuadra ha zarpado de Willemstad. Al mando va el navío de línea de segundo rango ‘Gouden Leeuw’, una auténtica bestia del mar. La potencia total de la escuadra supera los doscientos cincuenta cañones y más de mil quinientos soldados. Su objetivo es Saint-Pierre.";
			link.l1 = "Mm... Así que prácticamente no tenemos tiempo para prepararnos.";
			link.l1.go = "SharlieEpilog_KomendantFort_3";
		break;

		case "SharlieEpilog_KomendantFort_3":
			dialog.text = "¿Cómo procederemos, señor gobernador?";
			link.l1 = "En la rada tenemos varios barcos capaces de atacar al enemigo por la retaguardia...";
			link.l1.go = "SharlieEpilog_KomendantFort_4";
		break;

		case "SharlieEpilog_KomendantFort_4":
			dialog.text = "¿Piensas atacarles por ambos flancos?";
			link.l1 = "Exacto. El fuerte atraerá el fuego sobre sí. Y cuando caiga la noche, la escuadra bajo mi mando atacará desde el mar. Distraeremos su atención, y entonces desde el puerto partirán brulotes cargados de brea y tablones. No quedará ni una astilla de su flota.";
			link.l1.go = "SharlieEpilog_KomendantFort_5";
		break;

		case "SharlieEpilog_KomendantFort_5":
			dialog.text = "¡Un plan excelente, Su Excelencia! ¿Me permite dar la orden para comenzar los preparativos?";
			link.l1 = "Empezad. Y que el Señor esté con nosotros.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_11");
		break;
		
		// Стражник вызывает Алонсо
		case "SharlieEpilog_Guard":
			dialog.text = "";
			link.l1 = "Guardias, llamen a Alonso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoArrive");
		break;
		
		//Шарль разговаривает с Алонсо после коменданта
		case "SharlieEpilog_Alonso35":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")))
			{
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
				dialog.text = "Señor gobernador...";
				link.l1 = ""+npchar.name+", una escuadra holandesa llegará aquí de un día a otro y comenzará el asedio. Escucha la orden: lleva a Philippe y "+sld.name+", y llévalos de inmediato con el abad. Que reúna a todas las mujeres, niños y ancianos y se ocupe de su seguridad.";
				link.l1.go = "SharlieEpilog_Alonso36_Wife";
				break;
			}
			dialog.text = "Señor gobernador...";
			link.l1 = ""+npchar.name+", una escuadra holandesa llegará aquí de un día para otro y pondrá sitio a la ciudad. Dile al abad que reúna a todas las mujeres, niños y ancianos y se ocupe de su seguridad. En cuanto a ti, planeo confiarte el mando de un brulote. Los detalles después. Lo primero es proteger a los civiles.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;

		case "SharlieEpilog_Alonso36_Wife":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "No creo que "+sld.name+" aceptará unirse a las demás mujeres. Se muere de aburrimiento.";
			link.l1 = "Hmm... Entonces dile que se prepare para la batalla. Tú tampoco te quedarás de brazos cruzados: vas a comandar el brulote. Los detalles después. Ahora, cuida de mi hijo.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;
		
		case "SharlieEpilog_Alonso37":
			dialog.text = "¡Será un honor! ¿Me permite proceder?";
			link.l1 = "Te lo permito. Hazlo. Cada segundo cuenta para nosotros.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_13");
		break;
		// --> Выбрал отправиться назад на Карибы с женой
		case "SharlieEpilog_ChooseCaribbean_HaveWife_1":
			dialog.text = "";
			link.l1 = "Bueno... Debo admitir que esperaba que dijeras eso, aunque aún tenía la esperanza de oír otra respuesta. Pero respeto tu decisión y no voy a insistir ni tratar de convencerte.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_2":
			dialog.text = "";
			link.l1 = "Entiendo que les he decepcionado. Pero tengo una noticia para ustedes que, espero, eclipsará todo lo que se ha dicho antes.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_3":
			dialog.text = "";
			link.l1 = "Te escucho con atención.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "Voy a quedarme aquí al menos un año. "+sld.name+" en su estado, el vaivén del barco está totalmente contraindicado.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_5";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_5":
			dialog.text = "";
			link.l1 = ""+pchar.name+", ¿de verdad...?";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		// <-- Выбрал отправиться назад на Карибы с женой
		
		// --> Выбрал отправиться назад на Карибы один
		case "SharlieEpilog_ChooseCaribbean_Single_1":
			dialog.text = "";
			link.l1 = "Bueno... Debo admitir que esperaba que dijeras eso, aunque aún tenía la esperanza de oír otra respuesta. Pero respeto tu decisión y no voy a insistir más. Pero dime, "+pchar.name+", ¿has pensado en mi propuesta de casarte con Ivonne?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		// <-- Выбрал отправиться назад на Карибы один
		
		//Диалог Шарль и Мишеля на Рифе Скелета
		case "SharlieEpilog_Mishelle_1":
			dialog.text = "No pudiste detenerte, ¿eh?";
			link.l1 = "¿Tú?! ¿Esto es un sueño?";
			link.l1.go = "SharlieEpilog_Mishelle_2";
			SharlieEpilog_OnReefs_6();
			PlaySound("Voice\" + LanguageGetLanguage() + "\sharlie\mishelle-04.wav");
		break;

		case "SharlieEpilog_Mishelle_2":
			dialog.text = "La sed de dinero fácil, el poder, la ilusión de invulnerabilidad... ¿Qué de todo eso te perdió, hermano? ¿Qué nubló tu juicio, como nubla la mente de todos los rostros pálidos?";
			link.l1 = "¡Lárgate! ¡No eres más que un fantasma! ¡Tú no estás aquí!";
			link.l1.go = "SharlieEpilog_Mishelle_3";
		break;

		case "SharlieEpilog_Mishelle_3":
			dialog.text = "¿Todavía no lo entiendes? Spectra sunt memoria peccatorum. El fantasma eres tú... La leyenda caribeña de un hombre devorado por la codicia y la vanidad ciega. ¿A cuántos mataste por oro, "+pchar.name+"?";
			link.l1 = "Bueno, querido hermano, ¡no me importaría matarte por segunda vez! ¡Tú mismo te lo buscaste!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_OnReefs_9");
		break;
		
		
		
		
		
	}
}