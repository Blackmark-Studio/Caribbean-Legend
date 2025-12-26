// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Que tipo de perguntas?","O que você quer?");
			link.l1 = RandPhraseSimple("Mudei de ideia.'","Não tenho nada a dizer agora.");
		    link.l1.go = "exit";
			
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && npchar.sex == "man")
			{
				link.l1 = "Por acaso você conhece um tal de Joep van der Vink, conhece?";
				link.l1.go = "PZ_1";
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
			dialog.text = "Por acaso eu pareço algum tipo de investigador? Eu não sei, não sei de nada.";

            link.l1 = "Você é tão cabeça de vento! Cai fora.";
			link.l1.go = "exit";
			link.l2 = "Mais alguma pergunta, então?";
			link.l2.go = "new question";
		break;
		
		case "PZ_1":
			dialog.text = "Olha, eu não conheço ele pessoalmente, mas vejo ele por aqui de vez em quando. Por que a pergunta?";
			link.l1 = "Fui encarregado de entregar um pacote para ele pessoalmente. Mas ninguém quer falar sobre ele, e eu não sei por quê. Você sabe? Ele é uma pessoa ruim? Eu agradeceria sua opinião sincera.";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "De novo, nós não nos conhecemos pessoalmente, então eu quase não sei nada. Mas ele tem um amigo próximo na cidade, e eles são vistos juntos com frequência. Procure por ele – vai depender dele te contar mais ou não. O nome do amigo dele é Rober Martene.";
			link.l1 = "Rober Martene, você disse... E quem é ele? Onde posso encontrá-lo?";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Em vários lugares, mas agora ele está no nosso farol — consertando seu galeão depois de uma tempestade terrível. Chama-se 'Voltigeur'.";
			link.l1 = "Muito obrigado! Você não faz ideia do quanto me ajudou.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateRobertMartin");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
