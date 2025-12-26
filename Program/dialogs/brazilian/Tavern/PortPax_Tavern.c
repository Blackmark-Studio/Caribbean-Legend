// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Todos os boatos sobre "+GetCityName(npchar.city)+" ao seu dispor. O que gostaria de saber?","Estávamos justamente falando sobre isso. Você deve ter esquecido...","Essa já é a terceira vez hoje que você faz essa pergunta...","Você está repetindo as mesmas coisas feito um papagaio...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabe, "+NPChar.name+", talvez da próxima vez.","Certo, por algum motivo eu esqueci...","Sim, realmente é a terceira vez...","É...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince")
			{
				link.l1 = "Me diga, por acaso um galeão chamado 'Santa Margarita' passou pela sua colônia recentemente? Talvez como prêmio de algum corsário?";
                link.l1.go = "guardoftruth";
			}
			//--> Украденное воспоминание
			if (CheckAttribute(pchar, "questTemp.UV_DialogCitizen"))
			{
				link.l1 = "Tristan Renier passou por aqui recentemente?";
				link.l1.go = "UV_DialogTavern";
			}
			//<-- Украденное воспоминание
		break;
		
		case "guardoftruth":
			dialog.text = "Mate, it's pretty rare for anyone to stop by our colony with prizes, and we haven't seen a galleon by that name. Hispaniola is a wild island and we're a small colony. It's quiet here. We trade with the buccaneers in the highlands for cowhides and dried beef. Privateers don't usually linger; we don't have any brothels here, and the Spanish are close by. Go search for your galleon somewhere else.";
			link.l1 = "Entendi. Obrigado pelo conselho!";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "7");
			pchar.questTemp.Guardoftruth = "tortuga";
		break;
		
		//--> Украденное воспоминание
		case "UV_DialogTavern":
			dialog.text = "Renier? Sim, ele não só esteve aqui, como ainda não foi embora. Ele alugou um quarto.";
			link.l1 = "A sorte sorri para mim! Meus assuntos com o bom capitão não podem esperar—sua privacidade terá que ceder à necessidade. Em qual quarto posso encontrá-lo?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RoomInTavern");
			DelLandQuestMark(npchar);
		break;
		//<-- Украденное воспоминание

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
