// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais são as suas perguntas?","Como posso ajudar você?"),"Você tentou me fazer uma pergunta há pouco tempo...","Ninguém faz perguntas assim numa loja de Tortuga há muito tempo...","Perguntas, perguntas e mais perguntas...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Hum, onde foi parar minha memória...","Certo, já faz muito tempo.","Mais perguntas, hein...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga2")
			{
				link.l1 = "Escute, preciso encontrar Gaius Marchais. Disseram que ele está envolvido com corso e se tornou um grande negociador, depois de tomar um excelente galeão dos espanhóis. Por acaso ele comprou alguma mercadoria sua para negociar?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Gaius Marchais? Ah, sim, claro que me lembro dele! Mas ele não comprou nada. Ofereceu o navio dele para frete. Por acaso eu precisava de um navio com porão espaçoso – era um lote grande de peles brutas.";
			link.l1 = "E onde era o ponto de descarga?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Philipsburg, Saint Maarten.";
			link.l1 = "Certo. Obrigado, você me ajudou muito!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Sempre que quiser, capitão. Passe na minha loja quando quiser!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "10");
			pchar.questTemp.Guardoftruth = "maarten";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
