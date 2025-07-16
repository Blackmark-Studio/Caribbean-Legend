// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Quel genre de questions ?","Que voulez-vous ?");
			link.l1 = RandPhraseSimple("J'ai changé d'avis.","Je n'ai rien à dire maintenant.");
		    link.l1.go = "exit";
		break;
		
		case "info":
			dialog.text = LinkRandPhrase("Qui vous intéresse ?","De qui parlez-vous ?","Eh bien, qui est-ce ?");
			link.l1 = "Je veux en savoir plus sur Fadey le Moscovite.";
			link.l1.go = "fadey";
			link.l2 = "Personne, peu importe.";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("Où voulez-vous aller ? ","Que cherchez-vous ?","Que vous faut-il exactement ?");
            link.l1 = "Où se trouve la maison de Fadey ?";
			link.l1.go = "fadey_house";
			link.l2 = "Parlons d'autre chose...";
			link.l2.go = "new question";
		break;
		
		case "fadey":
			dialog.text = RandPhraseSimple("Ah, un homme important. Il possède la fabrique locale et il est proche des hautes sphères de Basse-Terre. Il a un fort accent et il aime vraiment boire... mais il ne se saoule jamais.","C'est un gros bonnet et un ami du gouverneur. Fadey possède une fabrique locale. Il vient d'un pays du nord, très, très loin d'ici... Je ne connais même pas son nom. Il a des mains fortes et il est capable de boire tout un tonneau de rhum sans être ivre.");
			link.l1 = "Je vous remercie.";
			link.l1.go = "exit";
		break;
		
		case "fadey_house":
			dialog.text = RandPhraseSimple("Allez tout droit depuis le quai jusqu'à ce que vous voyiez la place, la maison à gauche est le manoir de Fadey.","Allez au quai en passant par la place depuis la résidence du gouverneur, la maison à droite est le manoir de Fadey.");
			link.l1 = "Je vous remercie.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
