// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Habla, te escucho";
			link.l1 = "Me equivoqué. Adiós.";
			link.l1.go = "Exit";
			
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaZalog"))
			{
				link.l1 = "Recientemente, uno de los soldados de la ciudad arrestó y detuvo a Charlie Knippel. ¿Sigue aquí?"; 
				link.l1.go = "DTSG_AntiguaZalog_2";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов
		case "DTSG_AntiguaZalog_2":
			dialog.text = "Así es, pero ¿por qué preguntas?";
			link.l1 = "El asunto es que Charlie es uno de mis oficiales. Me gustaría saber de qué se le acusa. Los soldados que se lo llevaron no me dijeron nada."; 
			link.l1.go = "DTSG_AntiguaZalog_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaZalog_3":
			dialog.text = "Correcto. No es de conocimiento común. Desafortunadamente, ni siquiera para usted. Es un secreto de estado, señor.";
			link.l1 = "Entonces, supongo que la fianza no es una opción."; 
			link.l1.go = "DTSG_AntiguaZalog_4";
		break;
		
		case "DTSG_AntiguaZalog_4":
			dialog.text = "Exactamente. Entiendo que es desagradable perder a un miembro valioso de la tripulación, pero ni usted ni yo podemos hacer nada al respecto. Lo siento mucho, Capitán.";
			link.l1 = "Sin fianza, veo. Entonces, ¿qué tal... una compensación? Una generosa, debo añadir. Para ti y todos tus hombres, para que nadie quede afuera."; 
			link.l1.go = "DTSG_AntiguaZalog_5";
		break;
		
		case "DTSG_AntiguaZalog_5":
			dialog.text = "¿Un soborno? Valiente de tu parte, Capitán, pero ninguna cantidad de dinero nos salvará de la ira de aquellos que descubran que dejamos ir a Charlie.";
			link.l1 = "Quizás... Pero, ¿puedo al menos hablar con él?"; 
			link.l1.go = "DTSG_AntiguaZalog_6";
		break;
		
		case "DTSG_AntiguaZalog_6":
			dialog.text = "¿Por qué no? No puedes hacer nada para rescatarlo o ayudarle a escapar, así que... adelante. Está en una de las celdas.";
			link.l1 = "Ja, ¿y si me dice de qué se le acusa y revela ese secreto de Estado que tanto te preocupa, oficial?"; 
			link.l1.go = "DTSG_AntiguaZalog_7";
		break;
		
		case "DTSG_AntiguaZalog_7":
			dialog.text = "No me preocupa eso. Comprenderás por qué. Ve, habla con tu antiguo oficial antes de que cambie de opinión.";
			link.l1 = "Gracias."; 
			link.l1.go = "DTSG_AntiguaZalog_8";
		break;
		
		case "DTSG_AntiguaZalog_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaZalog");
			pchar.questTemp.jailCanMove = true;
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto9");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Killer", "sold_eng_10", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Killer";
			LAi_SetStayType(sld);
			sld.talker = 5;
			GiveItem2Character(sld, "blade_14");
			EquipCharacterbyItem(sld, "blade_14");
			GiveItem2Character(sld, "pistol4");
			EquipCharacterbyItem(sld, "pistol4");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload12");
			sld.rank = 30;
			SetSelfSkill(sld, 80, 80, 80, 80, 80);
			LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
			LAi_SetImmortal(sld, true);
		break;
		
		case "DTSG_AntiguaTrevoga_2":
			dialog.text = "No hay necesidad, Capitán. Como dije, habrías sido arrojado a la misma celda con ese tonto de Charlie. Pero, primero, el Gobernador valoró que no te resistieras al arresto, y segundo, no le agradó la reciente visita del prestamista, cuyos gritos casi rompieron las ventanas del palacio...";
			link.l1 = "¿Pidió mi arresto?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaTrevoga_3":
			dialog.text = "No pidió, exigió. Y a Su Excelencia no le gusta que le exijan nada. Por lo tanto, a ese usurero se le mostró la puerta.";
			link.l1 = "Divertidísimo. Ahora..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_4";
		break;
		
		case "DTSG_AntiguaTrevoga_4":
			dialog.text = "Ahora le sugiero que haga lo mismo, Capitán de Maure. Y no haga preguntas para las que no obtendrá respuestas.";
			link.l1 = "No me iré de aquí sin Charlie Knippel."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H1";
			link.l2 = "Por favor, señor, déjeme hablar con Charlie Knippel. O al menos averiguar qué..."; 
			link.l2.go = "DTSG_AntiguaTrevoga_Ch1";
		break;
		
		case "DTSG_AntiguaTrevoga_H1":
			dialog.text = "En ese caso, únete a él. No en una celda, sino en el más allá.";
			link.l1 = "Entonces, está muerto..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H2";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_H2":
			dialog.text = "Eres condenadamente perspicaz, Capitán. Y espero que te des cuenta de que no te diré quién lo hizo ni por qué.";
			link.l1 = "¿Es así?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_H3";
		break;
		
		case "DTSG_AntiguaTrevoga_H3":
			dialog.text = "Exactamente. Y ahora no pongas a prueba mi paciencia, antes de que ordene que te lancen a una celda por matar a un soldado inglés.";
			link.l1 = "Teniendo en cuenta que no muchos salen de tus celdas, no me gustaría acabar allí. No te desearé un buen día."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_Ch1":
			dialog.text = "Charlie Knippel no hablará con nadie. Excepto quizás con el Creador...";
			link.l1 = "¿Está muerto?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_Ch2";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_Ch2":
			dialog.text = "La sentencia ha sido ejecutada. No puedo darte ningún detalle. Y espero que no insistas, podría terminar mal para ti. No solo con una celda. ¿Queda claro, Capitán de Mor?";
			link.l1 = "Más que claro. Adiós."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaTrevoga");
			AddQuestRecord("DTSG", "10");
			CloseQuestHeader("DTSG");
			ChangeCharacterComplexReputation(pchar, "authority", -10);
			AddCrewMorale(Pchar, -30);
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
