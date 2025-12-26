// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Que tipo de perguntas?","O que você quer?");
			link.l1 = RandPhraseSimple("Mudei de ideia.'","Não tenho nada a dizer agora.");
		    link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince" && !CheckAttribute(npchar, "quest.Guardoftruth"))
			{
				link.l1 = "Me conte, "+GetAddress_FormToNPC(NPChar)+", o galeão 'Santa Margarita' esteve por aqui recentemente? Talvez como um prêmio de corsário?";
                link.l1.go = "guardoftruth";
			}
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
			dialog.text = "Por acaso eu pareço algum investigador? Eu não sei, não sei de nada.";

            link.l1 = "Você é mesmo um cabeça de vento! Vai embora.";
			link.l1.go = "exit";
			link.l2 = "Mais alguma pergunta, então?";
			link.l2.go = "new question";
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Não, não me lembro de nenhum galeão com esse nome. Navios tão grandes quase não aparecem por aqui.","O quê? Um galeão? Aqui? Não faço ideia.","Não, senhor, esse navio não atracou aqui recentemente, pelo menos não me lembro disso ter acontecido.");
			link.l1 = LinkRandPhrase("Certo...","Muito bem...","Entendi, que pena...");
			link.l1.go = "exit";
			npchar.quest.Guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
