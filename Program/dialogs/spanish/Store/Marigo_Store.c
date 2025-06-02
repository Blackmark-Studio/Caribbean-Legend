// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat("Adelante, ¿qué quieres?", "Acabábamos de hablar de eso. Debes haberlo olvidado...", "Esta es la tercera vez hoy que hablas de alguna pregunta...", "Escucha, esto es una tienda. La gente compra cosas aquí. ¡No me molestes!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Sabes, " + NPChar.name + ", tal vez la próxima vez.", "Bien, lo he olvidado por alguna razón...", "Sí, realmente es la tercera vez...", "Hm, no lo haré...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		// Jason --> Португалец
		if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Findcloves" && !CheckAttribute(npchar, "quest.Portugal"))
		{
			link.l1 = "Escucha, necesito ropa elegante. Cara, quiero lucir como un verdadero noble. ¿Tienes algo de ese tipo?";
			link.l1.go = "Portugal_cloves";
		}
		//<-- Португалец
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten")
		{
			link.l1 = "Un galeón llamado 'Admirable' te trajo un cargamento de pieles recientemente. ¿Lo recuerdas?";
			link.l1.go = "guardoftruth";
		}
		break;

	// Jason --> Португалец
	case "Portugal_cloves":
		dialog.text = "¿Ropa noble? Claro, tengo un conjunto por aquí: pantalones, un jubón, una camisa de seda y botas. Cuesta 20 000 pesos. La ropa es de muy alta calidad, es cómoda y tiene un aspecto notable, así que no aceptaré menos por ella.";
		if (sti(pchar.money) >= 20000)
		{
			link.l1 = "¡Estupendo! Me la llevo.";
			link.l1.go = "Portugal_cloves_1";
		}
		link.l2 = "Mm... No tengo tanto dinero en este momento.";
		link.l2.go = "Portugal_cloves_nomoney";
		break;

	case "Portugal_cloves_nomoney":
		dialog.text = "Entonces regresa cuando tengas el dinero.";
		link.l1 = "Está bien. ¡Regresaré!";
		link.l1.go = "exit";
		break;

	case "Portugal_cloves_1":
		AddMoneyToCharacter(pchar, -20000);
		GiveItem2Character(pchar, "suit_1");
		Log_Info("¡Has recibido ropa cara!");
		PlaySound("interface\important_item.wav");
		dialog.text = "Aquí tienes.";
		link.l1 = "¡Gracias!";
		link.l1.go = "exit";
		npchar.quest.Portugal = "true";
		sld = characterFromId("PortugalDoctor");
		sld.dialog.currentnode = "Portugal_doctor_4";
		DelLandQuestMark(characterFromId("Marigo_trader"));
		AddLandQuestMark(characterFromId("PortugalDoctor"), "questmarkmain");
		QuestPointerDelLoc("marigo_town", "reload", "reload6_back");
		QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
	//<-- Португалец
	case "guardoftruth":
		dialog.text = "Sí. Llegó a tiempo, descargó la mercancía y se la pagué como habíamos acordado. ¿Por qué preguntas?";
		link.l1 = "El capitán de ese barco es Gaius Marchais, mi viejo conocido. Así que estoy tratando de encontrarlo. ¿Podrías decirme qué hizo después de eso? ¿Quizás le proporcionaste algún cargamento adicional o mencionó hacia dónde se dirigía?";
		link.l1.go = "guardoftruth_1";
		break;

	case "guardoftruth_1":
		dialog.text = "Nada de eso. No le ofrecí ningún flete; ni siquiera me lo pidió. No compartió conmigo sus planes de futuro. Ni siquiera recuerdo todos los detalles, ¿sabes cuánta gente ha entrado y salido de aquí desde entonces? Descargó y zarpó, y eso es todo lo que puedo decir de él.";
		link.l1 = "Está bien. Bueno, gracias de todas formas. ¡Todo lo mejor!";
		link.l1.go = "guardoftruth_2";
		break;

	case "guardoftruth_2":
		DialogExit();
		AddQuestRecord("Guardoftruth", "11");
		pchar.questTemp.Guardoftruth = "maarten1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
