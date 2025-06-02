// диалог индейцев в поселениях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "¡No tenemos nada de que hablar!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> индейцы в поселении
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Cara pálida","Mujer blanca")+"¿quiere hablar?","Tú otra vez, "+GetSexPhrase("Cara pálida","Mujer blanca")+".",""+GetSexPhrase("Al rostro pálido le gusta hablar. Parece una squaw.","La pálida squaw disfruta hablando.")+"","Los espíritus trajeron a mi carapálida "+GetSexPhrase("hermano","hermana")+" a mí.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sí.","Sí, yo de nuevo.","Muy poético.","También estoy contento de verte.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		
		case "IndPearlMan_1":
			dialog.text = "Di, ¿por qué has venido, carapálida?";
			link.l1 = "Oh, nada en particular, solo quería escuchar lo que tenías que decir...";
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat("¿Hombre blanco quiere hablar?","¿Tú de nuevo, carapálida?","Al rostro pálido le gusta hablar.","Los espíritus trajeron a mi hermano de cara pálida hacia mí.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sí.","Sí, yo de nuevo.","Muy poético.","Me alegra verte también.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(""+npchar.name+"escúchate, hijo del mar.","¿Qué quieres de "+npchar.name+", ¿cara pálida?","Mis oídos están abiertos para tus palabras, desconocido.");
			if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase("Tengo algo para ti. ¿Quieres echar un vistazo?","¿Quieres echar un vistazo a algo realmente interesante? Seguro que te gustará...","Tengo algo que te agradará, hijo de la jungla. ¿Quieres echar un vistazo?");
				link.l1.go = "gift";
			}
			link.l9 = "Oh, nada en particular, solo quería escuchar lo que tenías que decir...";
			link.l9.go = "exit";
		break;
		
		case "gift":
			iTemp = 2;
			dialog.text = RandPhraseSimple(""+npchar.name+" quiere mirar. Muéstralo.",""+npchar.name+" está interesado. Muéstrame.");
			if (CheckCharacterItem(pchar, "mineral6"))
			{
				link.l1 = "Dale un espejo.";
				link.l1.go = "gift_1";
			}
			for (i=50; i>=47; i--)
			{
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = "Give"+XI_ConvertString("jewelry"+i)+".";
					link.(sTemp).go = "gift_"+i;
					iTemp++;				
				}
			}
		break;
		
		case "gift_1":
			RemoveItems(pchar, "mineral6", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "¡Oh! Ahora "+npchar.name+"¡puede mirarse a sí misma no solo en el agua del río! ¡Gracias, amable desconocido!";
			link.l1 = "Claro, ahora puedes admirar tu rostro tanto como quieras...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_47":
			RemoveItems(pchar, "jewelry47", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "¡Oh! ¡Qué hermoso! Esta pulsera es para "+npchar.name+"¡Gracias, amable desconocido!";
			link.l1 = "Pónselo en tu mano morena, belleza, te verás terrificante...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_48":
			RemoveItems(pchar, "jewelry48", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "¡Oh! ¿Qué anillo tan hermoso? Es para "+npchar.name+", ¿verdad? ¡Gracias, amable extraño!";
			link.l1 = "Póntelo en el dedo, y todos tus amigos estarán celosos...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_49":
			RemoveItems(pchar, "jewelry49", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "¡Oh! Esas maravillosas cuentas verdes son para "+npchar.name+"¡Tan hermoso! ¡Gracias, amable desconocido!";
			link.l1 = "Adorna tu cuello con ellas, hija de la selva. Todos te admirarán...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_50":
			RemoveItems(pchar, "jewelry50", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "¡Oh, qué hermoso anillo verde! Esto es un regalo para "+npchar.name+"¡Gracias, amable desconocido!";
			link.l1 = "Se verá genial en tu mano, bonita...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_exit":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) // Addon 2016-1 Jason Пиратская линейка
			{
				dialog.text = "Quería preguntar "+npchar.name+"¿algo, hijo del mar?";
				link.l1 = "Tienes razón, hermosa. Yo y mis valientes guerreros nos dirigimos a la selva, al asentamiento español entre las montañas y estamos buscando un guía. Seré generoso tanto con el hombre como con su esposa. Tengo muchas riquezas: hermosas armas, gafas mágicas, espejos, collares, pulseras y anillos. ¿Quizás tu marido pueda ser el guía que estamos buscando?";
				link.l1.go = "hayamee";
			}
			else
			{
				DialogExit();
			}
			ChangeIndianRelation(1.00);
			npchar.quest.gift = true;
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		// Кумвана, вождь деревни араваков
		case "cumvana":
			dialog.text = "Saludos, hijo del mar. Yo soy Kumwana, jefe del clan Tortuga del pueblo Locono. ¿Qué asunto te trae a mi aldea?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Te traje un regalo, jefe. Echa un vistazo, te va a gustar.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "Jefe, he venido a pedir su ayuda. Quiero llegar a una colonia española llamada Merida, está ubicada entre las montañas en su selva, el problema es que no sé cómo llegar allí.";
				link.l1.go = "cumvana_no";
			}
			DelLandQuestMark(npchar);
		break;
		
		case "cumvana_no":
			dialog.text = "Eso es muy bueno para ti, hijo del mar, no conocer el camino allí. Conduce a través de un bosque, tierra de la valiente tribu de Capong. Verdaderos jaguares, son, ¡oh-ey! Yo nunca voy a ese lugar español. Mi gente, gente pacífica, no vamos a la tierra de Capong. Kumwana no puede darte un consejo. Camino demasiado peligroso.";
			link.l1 = "¡Pero los españoles encontraron un camino allí! Y no le tengo miedo a esos Capongs...";
			link.l1.go = "cumvana_no_1";
		break;
		
		case "cumvana_no_1":
			dialog.text = "Pero deberías. Son personas crueles. Han matado a muchos de mi gente en el bosque. Kumwana lo dijo todo.";
			link.l1 = "Bueno, mierda...";
			link.l1.go = "cumvana_no_2";
		break;
		
		case "cumvana_no_2":
			DialogExit();
			AddQuestRecord("Roger_5", "5");
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_1":
			dialog.text = "¡Oh-ey! Tú otra vez, hijo del mar. ¿Qué quieres decirle a Kumwana?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Te traje un regalo, jefe. Echa un vistazo, te va a gustar.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "La esperanza de encontrar a Merida aún está conmigo...";
				link.l1.go = "cumvana_1_1";
			}
		break;
		
		case "cumvana_1_1":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_2":
			dialog.text = "Los Locono siempre se alegran de ver a buenos amigos.";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0)
			{
				link.l1 = "Regala una pistola."; // 5
				link.l1.go = "cumvana_2_1";
			}
			if (CheckCharacterItem(pchar, "compass1")) // 3
			{
				link.l2 = "Regala una brújula.";
				link.l2.go = "cumvana_2_2";
			}
			if (GetCharacterFreeItem(pchar, "spyglass1") > 0)
			{
				link.l3 = "Regala un catalejo barato.";
				link.l3.go = "cumvana_2_3";
			}
			if (GetCharacterFreeItem(pchar, "spyglass2") > 0)
			{
				link.l4 = "Regala un catalejo común."; // 2
				link.l4.go = "cumvana_2_4";
			}
			if (GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l5 = "Regala un catalejo decente."; // 4
				link.l5.go = "cumvana_2_5";
			}
		break;
		
		case "cumvana_2_1":
			Log_Info("Has dado una pistola");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "pistol5", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_3");
			dialog.text = "¡Oh-ey! ¡Qué bonita arma de cara pálida! ¡Kumwana acepta tu regalo! Tú también, hijo del mar, acepta un regalo de Kumwana y del pueblo Locono.";
			link.l1 = "¡Gratitud, jefe!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_2":
			Log_Info("Has dado una brújula");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "compass1", 1);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "¡Oh-ey! ¡Amuleto mágico de caras pálidas! ¡Kumwana acepta tu regalo! Tú también, hijo del mar, acepta un regalo de Kumwana y del pueblo Locono.";
			link.l1 = "¡Gratitud, jefe!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_3":
			Log_Info("Has dado un catalejo barato");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass1", 1);
			GiveItem2Character(pchar, "obereg_2");
			GiveItem2Character(pchar, "indian_5");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "¡Oh-ey! ¡Tubo mágico de caras pálidas! ¡Kumwana acepta tu regalo! Tú también, hijo del mar, acepta un regalo de Kumwana y el pueblo Locono.";
			link.l1 = "¡Gratitud, jefe!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_4":
			Log_Info("Has dado un catalejo común");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass2", 1);
			GiveItem2Character(pchar, "obereg_6");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "¡Oh-ey! ¡Tubo mágico de caras pálidas! ¡Kumwana acepta tu regalo! Tú también, hijo del mar, acepta un regalo de Kumwana y el pueblo Locono.";
			link.l1 = "¡Gratitud, jefe!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_5":
			Log_Info("Has dado un catalejo decente");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass3", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_5");
			dialog.text = "¡Oh-ey! ¡Tubo mágico de caras pálidas! ¡Kumwana acepta tu regalo! Tú también, hijo del mar, acepta un regalo de Kumwana y el pueblo Locono.";
			link.l1 = "¡Gratitud, jefe!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_3":
			dialog.text = "¿Qué te trae a nuestro pueblo, hijo del mar?";
			link.l1 = "Jefe, he venido a pedir tu ayuda. Quiero llegar a un asentamiento español llamado Mérida, está ubicado entre las montañas en tu selva, el problema es que no sé cómo llegar allí. ¿Quizás, podrías proporcionarme un valiente guerrero que nos muestre el camino?";
			link.l1.go = "cumvana_4";
		break;
		
		case "cumvana_4":
			dialog.text = "¡Oh-ey! Camino peligroso, peligroso. El camino allí lleva a través de un bosque, tierra de la tribu sin miedo de Capong. Verdaderos jaguares, son, ¡oh-ey! Yo nunca voy a ese lugar español. Mi gente, gente pacífica, no vamos a la tierra de Capong.";
			link.l1 = "Realmente tengo que llegar a Mérida. Kumwana, pregunta a tus hombres por favor... ¿Quizás alguien acepte unirse a mi unidad? Mis guerreros son experimentados, bien armados y no temen nada, ni siquiera al Diablo. Protegeremos al guía y lo recompensaremos generosamente cuando todo termine.";
			link.l1.go = "cumvana_5";
		break;
		
		case "cumvana_5":
			dialog.text = "Muy bien, hijo del mar. Reuniré un círculo de guerreros y les contaré acerca de tus deseos. Ven a verme mañana después del amanecer.";
			link.l1 = "¡Gratitud, jefe!";
			link.l1.go = "cumvana_6";
		break;
		
		case "cumvana_6":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetStayType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			//AddQuestRecord("Roger_5", "6");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			SetLaunchFrameFormParam("Al día siguiente....", "Mtraxx_MeridaVozhdDialog", 0, 4.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 0, 0);
			RecalculateJumpTable();
		break;
		
		case "cumvana_7":
			dialog.text = "¡Oh-ey! Tú otra vez, hijo del mar. ¿Qué quieres decirle a Kumwana?";
			link.l1 = "Nada aún, jefe.";
			link.l1.go = "cumvana_7x";
			if(CheckAttribute(pchar,"questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_hayamee")
			{
				link.l2 = "Escucha, Kumwana. Mi gente y yo realmente necesitamos cruzar el río y llegar a ese maldito pueblito. Permíteme explicarte cuán crucial es esto para nosotros.";
				link.l2.go = "cumvana_hard";
			}
		break;
		
		case "cumvana_hard":
			dialog.text = "Mis cazadores ya te han informado de que...";
			link.l1 = "No hay necesidad de repetirte dos veces, Kumwana. Pero mira afuera y no sobreestimes tus capacidades. Mis valientes hombres que vinieron aquí por las piedras españolas están dispersos en tu aldea. Y su paciencia se está agotando. Y lo que sucederá cuando finalmente se agote, es mejor que no lo sepas, créeme.";
			link.l1.go = "cumvana_medium_1";
			link.l2 = "Cierra la boca y escucha, mono de piel roja. Mi gente puede ser mucho más terrible que estos malditos Kapongs. No te dejes engañar por el hecho de que somos tan amables ahora. Te doy una elección simple: o encuentras un guía en veinticuatro horas, o ataremos a todos ustedes y los enviaremos a través de la selva delante de nuestro escuadrón. Si nos llevas en la dirección equivocada, perecerás en los pantanos o irás atado a luchar contra los Kapongs. ¿Entendido?";
			link.l2.go = "cumvana_hard_1";
			link.l3 = "Kumwana, necesito esta guía. Hemos recorrido un largo camino y realmente no quiero decirle a mis hombres que fue en vano.";
			link.l3.go = "cumvana_good_1";
			pchar.questTemp.Mtraxx_MeridaZapugivanieIndeets = true;
		break;
		
		case "cumvana_good_1":
			dialog.text = "Kumwana ya dijo, ninguno de los Lokono quiere ir con el rostro pálido.";
			link.l1 = "¿Y no puedes hacer nada al respecto? Pregunta a alguien personalmente. Ordena, después de todo. ¿Eres el jefe o no?";
			link.l1.go = "cumvana_good_2";
		break;
		
		case "cumvana_good_2":
			dialog.text = "El jefe no fuerza al indio. El jefe gobierna y quiere paz para su gente. Los indios saben, el Kapong verá que los Lokono traigan a los caras pálidas. Sus cabezas serán capturadas por Kanaima. Vienen a vengarse de los Lokono. Kapong para matar. Captura a los Lokono, haz esclavos.";
			link.l1 = "¿Y quién capturó vuestras cabezas? ¿Qué espíritu o demonio hace a los indios tan cobardes y miserables? Bueno, tal vez realmente tendré que abandonar la campaña contra Merida. Pero recuerda algo, jefe. Siempre que me preguntan qué sé sobre los Lokono, invariablemente responderé que son una tribu de cobardes sin valor. Liderados por un gobernante tan cobarde y corto de vista como ellos, cuyo rostro está distorsionado por una mueca de horror al mero recuerdo de los Kapongs. No ganarás gloria entre los indios, ni respeto entre nosotros, los caras pálidas.";
			link.l1.go = "cumvana_good_3";
		break;
		
		case "cumvana_good_3":
			dialog.text = "Cara pálida no conoce las costumbres de los indios...";
			link.l1 = "Sé lo suficiente para saber a quién los indios llaman cobarde y a quién un valiente guerrero. Adiós, Kumwana. Y recuerda mis palabras. Eres un gobernante cobarde y miope.";
			link.l1.go = "cumvana_good_4";
		break;
		
		case "cumvana_good_4":
			DialogExit();
			ChangeIndianRelation(5.00);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			pchar.questTemp.Mtraxx = "fail";
			
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.function = "Mtraxx_MeridaHayameeGoodDialog";
		break;
		
		case "cumvana_medium_1":
			dialog.text = "¿Por qué me amenazas así? Creemos que eres bueno...";
			link.l1 = "Estoy bien, siempre y cuando cooperes, ¿entendido? Tienes un día. Y créeme, mi gente hará lo que yo ordene. Somos más fuertes. Y si lo dudas... He visto a tu esposa. Y a tus hijas. Creo que ahora tienes el mensaje.";
			link.l1.go = "cumvana_hard_2";
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "cumvana_hard_1":
			dialog.text = "¿Por qué me amenazas así? Creemos que eres bueno...";
			link.l1 = "Estoy bien, siempre que coopere, ¿entendido? Tienes un día. Y créeme, mi gente hará lo que yo ordene. Somos más fuertes. Y si lo dudas... He visto a tu esposa. Y a tus hijas. Creo que has entendido el mensaje ahora.";
			link.l1.go = "cumvana_hard_2";
		break;
		
		case "cumvana_hard_2":
			dialog.text = "Kumwana entiende, cara pálida. En el pueblo, hay un cazador llamado Tagofa. Quizás él pueda guiarte hasta el asentamiento...";
			link.l1 = "Regresaré en veinticuatro horas. Charlie Prince no tiene nada más que añadir, salvaje.";
			link.l1.go = "cumvana_hard_3";
		break;
		
		case "cumvana_hard_3":
			DialogExit();
			ref Hayam = characterFromId("Hayamee");
			ChangeCharacterAddressGroup(Hayam, "none", "", "");
			Hayam.lifeday = 0;
			pchar.questTemp.Mtraxx = "merida_hayamee_hard";
			npchar.dialog.currentnode = "cumvana_7";
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeHardTagofaWait", 0, 0, 1, false);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			ChangeCharacterComplexReputation(pchar, "nobility", -80);
			ChangeOfficersLoyality("bad", 5);
			ChangeIndianRelation(-50.0);
			//log_Info("The attitude of the Indians has decreased");
			AddQuestRecord("Roger_5", "8a");
			pchar.GenQuest.CannotWait = true; //запретить отдыхать
			
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.function = "Mtraxx_MeridaHayameeHardLepriconDialog";
		break;
		
		case "cumvana_7x":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
		break;
		
		case "cumvana_8":
			dialog.text = "Hijo del mar, eres tú. Kumwana habló con los guerreros del Locono.";
			link.l1 = "¿Y? ¿Tienes un voluntario?";
			link.l1.go = "cumvana_9";
		break;
		
		case "cumvana_9":
			dialog.text = "Tenemos algunos cazadores por aquí que han estado allí. Pero temen a los Capongs, los jaguares están en guerra. No van, dicen que Capong matará a tu unidad. No temen a los rostros pálidos.";
			link.l1 = "¡Mis guerreros son mucho mejores que cualquiera de ellos! ¡Parte de mi unidad ha pasado toda una vida en la selva! ¡No somos unos aficionados!";
			link.l1.go = "cumvana_10";
		break;
		
		case "cumvana_10":
			dialog.text = "Lo siento, hijo del mar. Mis cazadores temen, los Capongs son peligrosos, muy muy.";
			link.l1 = "Bien, entonces quizás, ¿pueden explicar cómo llegar allí? En detalles.";
			link.l1.go = "cumvana_11";
		break;
		
		case "cumvana_11":
			dialog.text = "Para llegar allí debes navegar por el río y luego desembarcar en el lugar especial. Si es un lugar equivocado, acabarás en el pantano y morirás. Nuestra selva está llena de peligros. No encontrarás el lugar por tu cuenta, hijo del mar.";
			link.l1 = RandSwear()+"¿Y qué debería hacer entonces? ¿Cómo persuadir a tus cazadores?";
			link.l1.go = "cumvana_12";
		break;
		
		case "cumvana_12":
			dialog.text = "Kumwana no dice más, hijo del mar.";
			link.l1 = "Bien...";
			link.l1.go = "cumvana_13";
		break;
		
		case "cumvana_13":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "7");
			pchar.questTemp.Mtraxx = "merida_advice";
			LAi_SetHuberType(npchar);
			AddLandQuestMark(characterFromId("Lepricon"), "questmarkmain");
		break;
		
		// Хайами
		case "hayamee":
			if (npchar.id == "Hayamee")
			{
				dialog.text = "Mi marido Tagofa es el mejor cazador de la tribu. ¡Oh-ey!"+npchar.name+" está orgullosa de su marido. "+npchar.name+" a menudo va con Tagofa en Selva. Ve muy lejos. Tagofa sabe dónde está el asentamiento español.";
				if (IsCharacterPerkOn(pchar, "Trustworthy") && stf(pchar.questTemp.Indian.relation) >= 40.0)
				{
					link.l1 = "¿Tagofa conoce el camino a la ciudad española que los caras pálidas llaman Mérida?";
					link.l1.go = "hayamee_1";
				}
				else
				{
					link.l1 = "Bueno, bueno ... ¿Sabe Tagofa cómo llegar a la ciudad española?";
					link.l1.go = "hayamee_bad_1";
				}
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Mi marido no va a la selva, hijo del mar. Él pesca. Buen pescador, ¡oh-ey!","Mi marido buen cazador, oh-ey, pero él no va a la jungla profunda."),RandPhraseSimple("Jaguar hirió a mi marido en la caza. Ahora se sienta en el pueblo, hace flechas, oh-ey!","Hace seis lunas, tres Capongs atacaron a mi marido. ¡Ahora él no va a cazar lejos del pueblo. ¡Nunca! ¡oh-ey!"));
				link.l1 = LinkRandPhrase("Lástima...","Qué pena...","Qué lástima..."));
				link.l1.go = "exit";
			}
		break;
		
		case "hayamee_bad_1":
			dialog.text = "Tagofa creció en esta selva. ¡Conoce cada árbol y cada piedra alrededor!";
			link.l1 = "Te daré a ti y a Tagofa muchos regalos si nos lleva allí. Joyas, armas, cualquier cosa. Todo lo que quieras. Dentro de lo razonable, por supuesto, je-je. ¿Cómo puedo hablar con tu esposo?";
			link.l1.go = "hayamee_bad_2";
		break;
		
		case "hayamee_bad_2":
			dialog.text = "Tagofa no irá con el rostro pálido. Tagofa se quedará en la aldea. Ve a cazar. No pelees con el Kapong.";
			link.l1 = "No tendrá que luchar con el Kapong. En cuanto los vea, puede esconderse. Solo mi gente luchará.";
			link.l1.go = "hayamee_bad_3";
		break;
		
		case "hayamee_bad_3":
			dialog.text = "No, yalanaui. El rostro pálido nunca mantiene su palabra. El rostro pálido habla, y la palabra inmediatamente se va al vacío. El Kapong matará a Tagofa y luego vendrá a nuestro pueblo, matará al Lokono.";
			link.l1 = "¿Crees que estos Kapongs son todo lo que tienes que preocuparte? Estás muy equivocado...";
			link.l1.go = "hayamee_bad_4";
			if (stf(pchar.questTemp.Indian.relation) < 40.0) notification("Los indios no te respetan "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
		break;
		
		case "hayamee_bad_4":
			dialog.text = "¡Yahahu para entrar en el rostro pálido! Hayami ya no habla con yalanaui.";
			link.l1 = "Bueno-bueno...";
			link.l1.go = "hayamee_bad_5";
		break;
		
		case "hayamee_bad_5":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
		break;
		case "hayamee_1":
			dialog.text = "Tagofa se fue a cazar hace un día. Prometió volver mañana cuando el sol duerma. Ven mañana hijo del mar, estaré con Tagofa en esa choza, a la derecha según caminas por la aldea. Le preguntaré si irá contigo o no.";
			link.l1 = "Dile a Tagofa que le regalaré la pistola más bonita. Y a ti, te obsequiaré con muchas joyas.";
link.l1.go = "hayamee_1_1";
		break;
		
		case "hayamee_1_1":
			dialog.text = "Lokono no confía en los Yalanaui. Yalanaui engaña al indio, convierte al indio en esclavo. Pero Lokono oye tu nombre, cara pálida. Mi confianza es tuya. Ven mañana después del atardecer, hijo del mar. Estaré con Tagofa en esa choza. Le preguntaré si irá contigo o no.";
			link.l1 = "Dile a Tagofa que le daré mi pistola más hermosa. Y para ti tengo muchas joyas.";
			link.l1.go = "hayamee_2";
			notification("Los indios te respetan "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			notification("Trustworthy", "Trustworthy");
		break;
		
		case "hayamee_2":
			dialog.text = "¡Oh-ey!";
			link.l1 = "...";
			link.l1.go = "hayamee_3";
		break;
		
		case "hayamee_3":
			DialogExit();
			AddQuestRecord("Roger_5", "9");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.hour  = 22.0;
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.function = "Mtraxx_MeridaHayameeTimer";
		break;
		
		case "hayamee_4":
			pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
			dialog.text = ""+npchar.name+" se alegra de ver a un hijo del mar. Tagofa volvió. Pero ha bebido demasiado kasheeri y duerme. No lo despiertes, Tagofa descansa. Yo hablaré.";
			link.l1 = "Muy bien, "+npchar.name+"¿Tu marido nos guiará a Mérida?";
			link.l1.go = "hayamee_5";
		break;
		
		case "hayamee_5":
			dialog.text = "Tagofa acordó guiar a tus guerreros a través de la selva hasta el pueblo español. Pero hay condiciones...";
			link.l1 = "¿Cuáles son?";
			link.l1.go = "hayamee_6";
		break;
		
		case "hayamee_6":
			dialog.text = "Tú proteges a Tagofa de los guerreros Capong. Tagofa no lucha no español, no Capong. Si se enfrenta al peligro, huirá y nadie lo encontrará, él es el mejor cazador Locono.";
			link.l1 = "Ya veo. Te preocupas por tu hombre, esto es comprensible. Te prometo que nos ocuparemos de todos esos Capongs por nuestra cuenta.";
			link.l1.go = "hayamee_7";
		break;
		
		case "hayamee_7":
			dialog.text = "¡Oh-ey! Tagofa quiere regalos del hijo del mar: uno pequeño para disparar muchas piedras y uno grande para disparar una piedra, los bonitos. También quiere balas para cada pistola: tantas como dedos ambas manos tres veces.";
			link.l1 = "¡Vaya! Tu hombre sabe algo sobre armas, ¿eh? Muy bien. ¿Qué más?";
			link.l1.go = "hayamee_8";
		break;
		
		case "hayamee_8":
			dialog.text = "Y Tagofa quiere un hermoso ojo mágico de caras pálidas.";
			link.l1 = "¿Un catalejo? Bien. ¿Algo más?";
			link.l1.go = "hayamee_9";
		break;
		
		case "hayamee_9":
			dialog.text = "Ya no más para Tagofa."+npchar.name+" quiere cosas bonitas. Anillo de oro con gran piedra roja, y cuentas de muchas muchas piedras verdes. "+npchar.name+" lo vi en la blanca Mary en Maracaibo.";
			link.l1 = "¿Un anillo de oro con cuentas de rubí y jade?";
			link.l1.go = "hayamee_10";
		break;
		
		case "hayamee_10":
			dialog.text = "No es jade. Es brillante y los hombres blancos lo valoran.";
			link.l1 = "¿Esmeralda? ¿Cuentas de esmeralda?";
			link.l1.go = "hayamee_11";
		break;
		
		case "hayamee_11":
			dialog.text = "¡Oh-ey!";
			link.l1 = "Heh, "+npchar.name+" sabe algo sobre joyas! Muy bien, lo conseguirás.";
			link.l1.go = "hayamee_12";
		break;
		
		case "hayamee_12":
			dialog.text = "Lleva todas las cosas a "+npchar.name+" juntos, hijo del mar. Luego Tagofa te guiará a ti y a tus guerreros. No pierdas el tiempo, en medio de una luna Tagofa y yo iremos al pueblo vecino. Por un día alto. Ahora vete, "+npchar.name+" quiere dormir.";
			link.l1 = "No te haré esperar demasiado. Nos vemos.";
			link.l1.go = "hayamee_13";
		break;
		
		case "hayamee_13":
			DialogExit();
			AddQuestRecord("Roger_5", "10");
			LAi_CharacterDisableDialog(npchar);
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeLate", 0, 0, 15, false); // таймер
			// Тагофу в сидячее положение
			pchar.quest.mtraxx_merida_wait2.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.hour  = 9.0;
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.function = "Mtraxx_MeridaTagofaHide";
		break;
		
		case "hayamee_14":
			bOk = GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0;
			dialog.text = "¿Trajiste qué?"+npchar.name+"¿y Tagofa preguntó?";
			if (bOk && GetCharacterFreeItem(pchar, "pistol3") > 0 && GetCharacterFreeItem(pchar, "pistol5") > 0 && GetCharacterItem(pchar, "bullet") >= 30 && GetCharacterItem(pchar, "grapeshot") >= 30 && GetCharacterItem(pchar, "gunpowder") >= 60 && CheckCharacterItem(pchar, "jewelry41") && CheckCharacterItem(pchar, "jewelry42"))
			{
				link.l1 = "Sí. Todo está de acuerdo a tu lista.";
				link.l1.go = "hayamee_15";
			}
			else
			{
				link.l1 = "No, todavía estoy en ello.";
				link.l1.go = "hayamee_14x";
			}
		break;
		
		case "hayamee_14x":
			DialogExit();
			npchar.dialog.currentnode = "hayamee_14";
		break;
		
		case "hayamee_15":
			pchar.quest.Mtraxx_MeridaHayameeLate.over = "yes";
			Mtraxx_MeridaRemoveGifts();
			dialog.text = ""+npchar.name+" está feliz, hijo del mar. Ahora llamo a marido. Él va contigo. ¡Pero recuerda lo que prometiste a "+npchar.name+"!";
			link.l1 = "Sí-sí, recuerdo todo. Lo mantendré a salvo, no te preocupes.";
			link.l1.go = "hayamee_16";
		break;
		
		case "hayamee_16":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee_peace";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7.0);
			DoQuestFunctionDelay("Mtraxx_MeridaTagofaEnter", 20.0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Guarda tu arma, cara pálida, ¡o te obligaremos a hacerlo!";
			link.l1 = LinkRandPhrase("Bien.","Bien.","No te preocupes, lo estoy guardando...");
			link.l1.go = "exit";
		break;  

	}
}
