// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas?","O que você quer, "+GetAddress_Form(NPChar)+"?"),"Você já tentou me fazer uma pergunta "+GetAddress_Form(NPChar)+"...","Você já fez essa pergunta pela terceira vez hoje...","Olha, se você não tem nada pra me contar sobre os assuntos do porto, então não me incomode com suas perguntas.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia.","Não tenho nada para conversar."),"Deixa pra lá.","De fato, já é a terceira vez...","Desculpe, mas no momento não estou interessado nos assuntos do porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "ship" && !CheckAttribute(npchar, "quest.RescueDaughter"))
		{
			DelLandQuestMark(npchar);
			link.l1 = "Senhor, estou procurando trabalho. Mas não como carregador, algo mais à altura do meu posto. Uma missão, um serviço, algo que envolva questões delicadas... Aceito qualquer tarefa que o senhor tiver.";
			link.l1.go = "Sharlie";
		}
		//<-- Бремя гасконца
		
		// Jason „олго и счастливо
		if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "portman")
		{
			link.l1 = "Disseram que havia uma carta para mim. Meu nome é Capitão Charles de Maure.";
			link.l1.go = "LH_letter";
		}
		//--> Эпилог
		if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PU_Ulysse"))
		{
			link.l1 = "Ouvi dizer que o pínace '"+GetShipName("Ulysse")+"' foi recentemente colocado em leilão. É verdade?";
			link.l1.go = "SharlieEpilog_PU_Ulysse_1";
		}
		//<-- Эпилог
		break;
		
		case "Sharlie":
			dialog.text = "Ajuda? Hm. Eu estou bem, graças a Deus. Mas um dos meus amigos realmente precisa de ajuda, e é urgente. Ele vai entrar sozinho na selva para enfrentar os índios, isso é uma loucura total!\nTentei fazê-lo mudar de ideia, implorei, mas ele não me ouviu! Ele se preocupa demais com a filha e está pronto para dar a vida por ela!";
			link.l1 = "Espere, vamos começar de novo: quem é seu amigo, onde posso encontrá-lo e que tipo de ajuda ele precisa?";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			dialog.text = "Ah, me perdoe, estou muito ansioso. O nome dele é Prosper... Prosper Troubale. Ele vai morrer, com certeza! E eu não posso ajudá-lo – não sou soldado. A filha dele está desaparecida e ele acredita que os índios locais são os responsáveis.\nImagine só, ele pretende ir atrás desses selvagens sozinho! Eles vão despedaçá-lo... Neste momento ele está comprando um mosquete e se preparando para entrar na selva!";
			link.l1 = "Você é um contador de histórias lamentável, senhor. Onde posso encontrar seu amigo... como era mesmo o nome dele... Prosper?";
			link.l1.go = "Sharlie_2";			
		break;
		
		case "Sharlie_2":
			dialog.text = "Acabei de falar com ele e tentei fazê-lo mudar de ideia. Ele não está longe dos portões da cidade, perto do poço, conferindo o mosquete e a munição. Vá até ele e faça alguma coisa! Se ele entrar sozinho na selva, não vai voltar, tenho certeza disso. Aqueles demônios de pele vermelha vão despedaçá-lo...";
			link.l1 = "Pare de divagar, você está parecendo uma velha! Vou falar com seu amigo agora mesmo. Espero conseguir ajudá-lo.";
			link.l1.go = "Sharlie_3";			
		break;
		
		case "Sharlie_3":
			DialogExit();
			AddQuestRecord("SharlieF", "1");
			RescueDaughter_CreateProsper();
			npchar.quest.RescueDaughter = "true";
			QuestPointerDelLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		// Jason „олго и счастливо
		case "LH_letter":
			dialog.text = "Sim, você está certo – tem um envelope. Aqui está, mas antes, você precisa pagar pela entrega – doze mil pesos de prata.";
			if (sti(pchar.money) >= 12000)
			{
				link.l1 = "Sempre desconfiei que seu ofício tinha algo de ladrão, mas parece que me enganei, hm. Por favor, aqui está o seu dinheiro.";
				link.l1.go = "LH_letter_1";
			}
			else
			{
				link.l1 = "Vou voltar daqui a pouco, acho que deixei minha bolsa de moedas na taverna.";
				link.l1.go = "exit";
			}
		break;
		
		case "LH_letter_1":
			DialogExit();
			AddMoneyToCharacter(pchar, -12000);
			LongHappy_RecibeLetter();
		break;
		
		//--> Эпилог
		case "SharlieEpilog_PU_Ulysse_1":
			dialog.text = "É isso mesmo. O dono do navio se afundou em dívidas com seguros e colocou a embarcação em leilão. Só que você chegou um pouco tarde – o leilão já terminou, e o novo proprietário está cuidando da papelada.";
			link.l1 = "Sabe me dizer onde posso encontrá-lo? Preciso falar com ele.";
			link.l1.go = "SharlieEpilog_PU_Ulysse_2";
			DelLandQuestMark(npchar);
			SharlieEpilog_SpawnPikar();
		break;
		
		case "SharlieEpilog_PU_Ulysse_2":
			dialog.text = "E por que procurá-lo? Vire-se – ele está bem atrás de você.";
			link.l1 = "...";
			link.l1.go = "exit";			
		break;
		//<-- Эпилог
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
