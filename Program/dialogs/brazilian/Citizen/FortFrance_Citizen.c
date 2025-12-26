// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = RandPhraseSimple("Que tipo de perguntas?","O que você quer?");
			link.l1 = RandPhraseSimple("Mudei de ideia.'","Não tenho nada a dizer agora.");
			link.l1.go = "exit";
			//Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && !CheckAttribute(npchar, "quest.Sharlie"))
			{
				link.l1 = "Com licença, "+GetAddress_FormToNPC(NPChar)+" Você poderia me dizer onde posso encontrar Michel de Monper? Ouvi dizer que ele está nesta cidade.";
				link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "findskiper" && !CheckAttribute(npchar, "quest.Sharlie1"))
			{
				link.l1 = "Escute, "+GetAddress_FormToNPC(NPChar)+", quero te perguntar uma coisa... Estou procurando um navegador para servir no meu navio, você conhece alguém?";
				link.l1.go = "Sharlie_1";
			}
			//Бремя гасконца
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Você acha que eu trabalho para o serviço secreto de "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Bem... não. Então, até logo.";
			link.l1.go = "exit";
			link.l2 = "Mais alguma pergunta, então?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Eu pareço algum tipo de investigador? Não sei, não sei de nada.";

            link.l1 = "Você é mesmo um cabeça de vento! Cai fora.";
			link.l1.go = "exit";
			link.l2 = "Mais alguma pergunta, então?";
			link.l2.go = "new question";
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			if (sti(pchar.questTemp.Sharlie.Citcount) == 3)
			{
				dialog.text = "Hmm... I suspect you've only just arrived here, since you so fearlessly ask such questions... I advise you to stop if you don't want any trouble. Speak to the Abbot; he may help you 'come to your senses'. You can find him at the church.";
				link.l1 = "Entendi...";
				link.l1.go = "exit";
				AddDialogExitQuest("Sharlie_SetBenua");
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
			else
			{
				dialog.text = LinkRandPhrase("Não, nunca ouvi falar dele.","Não posso te ajudar, tenho trabalho a fazer.","Quem? Não me lembro, não. Vou seguir meu caminho.");
				link.l1 = "Entendi...  Vou seguir meu caminho então. ";
				link.l1.go = "exit";
				npchar.quest.Sharlie = "true";
			}
		break;
		
		case "Sharlie_1":
			dialog.text = LinkRandPhrase("Não, não conheço nenhum navegador.","Tenho trabalho a fazer e não, pergunte a outra pessoa...","Infelizmente, não posso te ajudar. Não conheço ninguém.");
			link.l1 = "Entendi. Vou perguntar em outro lugar então.";
			link.l1.go = "exit";
			npchar.quest.Sharlie1 = "true";
			npchar.dialog.currentnode = "first time";
		break;
		//<-- Бремя Гасконца
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
