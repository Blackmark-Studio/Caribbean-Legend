// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Adelante, ¿qué deseas?","Justo estábamos hablando de eso. Debes haberlo olvidado...","Esta es la tercera vez hoy que hablas de alguna pregunta...","Escucha, esto es una tienda. La gente compra cosas aquí. ¡No me molestes!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabes, "+NPChar.name+", quizás la próxima vez.","Correcto, lo he olvidado por alguna razón...","Sí, realmente es la tercera vez...","Hum, no lo haré...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Dime, ¿el nombre Juan te dice algo?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "En abril de 1654, una fragata atracó en tu puerto bajo el mando del Capitán Miguel Dichoso, después de lo cual desapareció. ¿Te suena su nombre? Posiblemente, podría haber comprado alguna mercancía de ti o haber dicho algo...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "¡Oh, vamos, capitán! Hoy ya he tenido dos Juanes en mi tienda, y otro ayer. ¿Qué, se supone que debo recordar a cada uno?";
			link.l1 = "Está bien. Perdona por molestarte...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "¡Oh, capitán, he visto tantos bergantines y galeones entrar y salir de aquí en ese tiempo, Miguels y Carloses...";
			link.l1 = "Ya veo. Entonces, no puedes ser de ayuda...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
