// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Todos os boatos sobre "+GetCityName(npchar.city)+" ao seu dispor. O que gostaria de saber?","Estávamos justamente falando sobre isso. Você deve ter esquecido...","Já é a terceira vez hoje que você toca nesse assunto...","Você está repetindo a mesma coisa feito um papagaio...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabe, "+NPChar.name+", talvez na próxima vez.","Certo, por algum motivo eu me esqueci...","Sim, realmente é a terceira vez...","É...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPanama")
            {
                link.l1 = "Ouvi dizer que há um corsário chamado François Gontier na sua cidade. Você saberia onde posso encontrá-lo?";
                link.l1.go = "Panama_rat_1";
            }
			// Addon-2016 Jason ”ЊЉ-ѓваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_panama")
            {
                link.l1 = "Olha, estou procurando um homem chamado Bertrand Pinette, já ouviu falar dele? Ele chegou ao Panamá há pouco tempo. Um cavalheiro imponente, de peruca. Talvez tenha passado por aqui...";
                link.l1.go = "FMQG";
            }
		break;

		//-->работорговец
		case "Panama_rat_1":
			dialog.text = NPCStringReactionRepeat("Sim, tivemos um sujeito assim na cidade. Ele andava rondando lugares escuros... Depois, alguns comparsas vieram visitá-lo, pareciam um bando de facínoras. Ele foi embora da cidade com eles.","Você já perguntou sobre isso e eu já te respondi.","Eu já te disse, você já perguntou sobre esse tal de Gontier.","Escuta, vai embora e para de me incomodar! Você ficou maluco de vez?","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("E para onde ele foi, você sabe?","Hm, acho que sim...","Sim, isso mesmo, eu pedi isso...","Desculpe, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "Panama_rat_2";
		break;
		
		case "Panama_rat_2":
			dialog.text = "Bem, só tem um jeito de sair daqui a pé – Portobelo. E ele foi pra lá. Então procure por ele lá.";
			link.l1 = "Muito obrigado, você foi de grande ajuda!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello";
			AddQuestRecord("Slavetrader", "21_1");
		break;
		//<--работорговец
		
		// Addon-2016 Jason ”ЊЉ-ѓваделупа
		case "FMQG":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("panama");
			dialog.text = "Bertrand Pinette? Francês? Nunca ouvi falar dele. Não, amigo, faz tempo que não vemos franceses por aqui.";
			link.l1 = "Que pena... Tem certeza? Ele é amigo de um importante hidalgo chamado Dom Carlos de Milyar. Eles deveriam chegar aqui juntos.";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Senhor de Milyar? Esse cavalheiro visitou o Panamá há um ano. Na verdade, Don Carlos de Milyar mora em Portobello. Ele é um grande amigo do governador local.";
			link.l1 = "Entendi. Não precisava perder tempo e fôlego na selva. Obrigado, amigo.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			pchar.questTemp.FMQG = "headhunter_portobello";
			AddQuestRecord("FMQ_Guadeloupe", "8");
			AddMapQuestMarkCity("PortoBello", true);
			AddLandQuestMark(characterFromId("PortoBello_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
