// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué tipo de preguntas, " + GetSexPhrase("hijo mío", "hija mía") + "?", "Pregunta lo que desees, estoy escuchando..."), "Te escucho, habla ahora, " + GetSexPhrase("hijo mío", "hija mía") + "...", "Por tercera vez, " + GetSexPhrase("hijo mío", "hija mía") + ", pide lo que necesites.", "Un clérigo tiene mucho trabajo y me estás distrayendo, " + GetSexPhrase("hijo mío", "hija mía") + "... ", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "No en este momento, padre..."), "No tengo nada que decir, mis disculpas.", "Preguntaré, pero más tarde. Perdóname, padre.", "Perdóneme, santo padre...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_pastor"))
			{
				link.l1 = "Santo Padre, deseo hablar con usted sobre la hija de Thomas Morrison.";
                link.l1.go = "dwh_pastor_1";
			}
			if (CheckAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi"))
			{
				link.l1 = "Santo Padre, Thomas me pidió que le dijera que aceptará la penitencia, se dedicará a buenas obras y proporcionará a la parroquia una nueva campana, sin importar lo que le cueste.";
                link.l1.go = "dwh_pastor_VD_5";
			}
			// <-- Тёмные воды исцеления
		break;
		
		// --> Тёмные воды исцеления
		case "dwh_pastor_1":
			dialog.text = "Habla, hijo mí"+GetSexPhrase("o","a")+", te escucho.";
			link.l1 = "Sé que está en contra de permitir que la gitana ayude a la niña. Pero, ¿cómo puede obligar a un padre a rechazar la más mínima posibilidad de salvar a su hija? Aunque sus métodos parezcan cuestionables, posee conocimientos que podrían ayudar.";
			link.l1.go = "dwh_pastor_2";
			DelLandQuestMark(npchar);
		break;
		
		case "dwh_pastor_2":
			dialog.text = "Hijo mí"+GetSexPhrase("o","a")," solo el Señor puede sanar a la niña. La fe en Su providencia es lo que nos guía a través de las pruebas. Si Thomas reza con diligencia, sigue la palabra de Dios y dona generosamente a la iglesia, el Señor escuchará sus oraciones y mostrará misericordia.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Confiable) Pero seguramente incluso usted debe reconocer que el Señor actúa a través de las personas. ¿Y si la gitana es simplemente un instrumento en las manos de Dios? ¿Y si Su designio es tan profundo que nosotros, simples mortales, no podemos comprenderlo? Los caminos del Señor son misteriosos, ¿no es así?";
				link.l1.go = "dwh_pastor_VD_1";
				notification("Confiable", "Trustworthy");
			}
			else
			{
				link.l1 = "Está obligando a un padre a ver cómo su hija se desvanece lentamente en lugar de permitirle intentar salvarla. ¿Es eso misericordia?";
				link.l1.go = "dwh_pastor_bez_VD_1";
				notification("Habilidad no desbloqueada", "Trustworthy");
			}
		break;
		
		case "dwh_pastor_VD_1":
			dialog.text = "Tus palabras, capitán, son ciertamente sabias. Sin embargo, no puedo permitir que la herejía penetre en el corazón mismo de nuestra congregación y sacuda la fe de uno de sus hijos más devotos.";
			link.l1 = "Nada podría sacudir más su fe que la muerte de su propia hija. Si le permite usar cualquier medio, incluso aquellos que podrían considerarse pecaminosos, su fe no se debilitará; por el contrario, se volverá más fuerte que antes.";
			link.l1.go = "dwh_pastor_VD_2";
		break;

		case "dwh_pastor_VD_2":
			dialog.text = "Pero... ¿Qué ejemplo dará esto a los demás miembros de la congregación?";
			link.l1 = "Un ejemplo de que la iglesia no castiga a ciegas, sino que guía hacia el verdadero arrepentimiento. ¿No nos enseña la Escritura que el arrepentimiento sincero y las buenas obras pueden redimir el pecado? Una generosa donación al tesoro de la iglesia podría ser el primer paso hacia la redención.";
			link.l1.go = "dwh_pastor_VD_3";
		break;

		case "dwh_pastor_VD_3":
			dialog.text = "Tal vez tengas razón, capitán. Estoy dispuesto a darle esta oportunidad a Thomas. Pero debes saber que si se desvía del camino verdadero y pierde la firmeza de su fe, ¡la responsabilidad también caerá sobre ti! En cuanto a las donaciones, la iglesia no necesita riquezas, tenemos todo lo necesario. Aunque nuestra campana resultó dañada durante el ataque español...";
			link.l1 = "Le transmitiré sus palabras a Thomas. Gracias por la conversación, Santo Padre. Que Dios lo proteja.";
			link.l1.go = "dwh_pastor_VD_4";
		break;
		
		case "dwh_pastor_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_11";
		break;
		
		case "dwh_pastor_bez_VD_1":
			dialog.text = "No es insensibilidad, capitán, es fe. No dejamos el destino de la niña al azar, sino que lo ponemos en manos del Señor Dios. Si Thomas ora, cree y espera con humildad, estoy seguro de que el Señor escuchará nuestras súplicas y le concederá la sanación.";
			link.l1 = "Seguramente sabe que incluso la nobleza de esta isla, incluido el gobernador, ha recurrido a los servicios de la gitana. Y no han sido excomulgados. ¿Por qué entonces es usted tan categórico en el caso de Thomas?";
			link.l1.go = "dwh_pastor_bez_VD_2";
		break;

		case "dwh_pastor_bez_VD_2":
			dialog.text = "Por supuesto que lo sé, hijo mí"+GetSexPhrase("o","a")+". Pero ellos son almas perdidas, que no han conocido la verdadera luz del Señor. Thomas, en cambio, es un pilar de nuestra congregación, uno de los mejores. Permitir que el maligno debilite su fe sería poner en peligro a toda la Iglesia, y no puedo permitir semejante pecado.";
			link.l1 = "¿Entonces rechaza usted incluso la más mínima oportunidad? ¿Es ese realmente el camino justo?";
			link.l1.go = "dwh_pastor_bez_VD_3";
		break;

		case "dwh_pastor_bez_VD_3":
			dialog.text = "Lo que ustedes llaman salvación puede ser un camino directo hacia la perdición. Hablo por experiencia. Una vez, contra mi voluntad, una curandera así trató a mi sobrina. La niña murió entre sufrimientos, y solo el Señor sabe si los ritos brujeriles condenaron su alma a un tormento eterno. Así que no intenten convencerme - es útil.";
			link.l1 = "Está bien. Si esa es su decisión final, no discutiré. Que el Señor le guarde.";
			link.l1.go = "dwh_pastor_bez_VD_4";
		break;
		
		case "dwh_pastor_bez_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			
			AddQuestRecord("DWH", "4");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetCitizenType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_6";
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto23");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "dwh_pastor_VD_5":
			dialog.text = "Excelente, hijo mío. La nueva campana simbolizará su devoción al Señor y a la iglesia. Que haga lo necesario, pero recuerde que el ojo del Todopoderoso vigila cada una de sus acciones, y no hay en este mundo asunto oculto a la voluntad de Dios.";
			link.l1 = "Que así sea, santo padre. Adiós.";
			link.l1.go = "dwh_pastor_VD_6";
			DelLandQuestMark(npchar);
		break;
		
		case "dwh_pastor_VD_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_15";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "barmen", "bar1");
			DelLandQuestMark(sld);
		break;
		// <-- Тёмные воды исцеления
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
