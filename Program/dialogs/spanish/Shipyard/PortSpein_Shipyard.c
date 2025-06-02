// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?","¿Cómo puedo ayudarte?"),"Intentaste hacerme una pregunta hace un rato...","Jamás he conocido a personas con tanta curiosidad en mi astillero ni en ningún otro lugar de este pueblo.","¿Por qué tantas preguntas? Mi trabajo es construir barcos. Ocupémonos de eso.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...","No tengo nada de qué hablar en este momento."),"Umph, ¿a dónde se ha ido mi memoria...?","Mm, bueno...","Adelante...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Dime, ¿el nombre Juan te dice algo?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Señor, aquí estuvo una fragata bajo el mando de Miguel Dichoso en abril de 1654. Desapareció justo después. ¿No recuerda nada al respecto? Tal vez Dichoso se detuvo para una reparación, y quizás le contó algo...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "No. Nada en absoluto.";
			link.l1 = "Bien. Perdón por molestarte...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Hm. No. No pasó por aquí para una reparación y no me dijo nada en absoluto. Y si algo de eso hubiera ocurrido, no lo recuerdo. Lo siento, no puedo ayudarte, señor.";
			link.l1 = "Está bien. Gracias amigo...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
