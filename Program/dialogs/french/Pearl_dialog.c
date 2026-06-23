void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Nous n'avons rien à discuter!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> пиплы в поселении
		case "PearlMan":
			NextDiag.TempNode = "PearlMan";
			dialog.text = NPCStringReactionRepeat("Bonjour ! Mon nom est  "+GetFullName(npchar)+". Que puis-je faire pour vous?","Bonjour encore une fois !","Les visiteurs sont très rares dans ce trou perdu...","C'est un tel plaisir de parler avec un nouveau visage ! Je suis déjà malade de tous ces vieux groin-groin...","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Oh, rien...","Moi aussi...","Je vois...","Heh...",npchar,Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
		break;
		case "PearlMan_1":
			dialog.text = "Nous rassemblons ici des perles, au service  "+NationNameGenitive(int(npchar.nation))+", tu sais...";
			link.l1 = "Ouais, je sais...";
			link.l1.go = "exit";
			link.l2 = "Hé, écoute, est-il possible d'acheter plusieurs de ces petits bibelots directement auprès du 'producteur', que dirais-tu?";
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = "Oh non, bien sûr, pas du tout ! Le vol d'une seule petite perle est puni par la mort !";
				link.l1 = "Des ordres cruels que vous avez ici, c'est sûr...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Oui, nous avons des ordres sévères ici, et on peut facilement perdre sa tête pour tout méfait. Je ne m'occupe pas de ça, mais je peux te conseiller de parler avec les Indiens locaux à ce sujet. Ils ont quelque part où s'enfuir si quelque chose tourne mal, donc ils devraient être plus audacieux que nous...";
				link.l1 = "Je vois... D'accord, merci.";
				link.l1.go = "exit";
			}
		break;
		case "PearlMan_Sharp_1":
			dialog.text = LinkRandPhrase("Es-tu completement  "+GetSexPhrase("fou ? Va-t'en, idiote","fou? Va-t'en, stupide idiot")+"!",""+GetSexPhrase("Quoi?! Es-tu fou, idiot","Quoi?! Es-tu folle, maudite fille?")+"?! Fiche le camp avec toutes tes questions...",""+GetSexPhrase("Vous avez perdu l'esprit, cher? Quels pirates? Ici?! Allez-vous-en, vous imbécile","Tu as perdu la tête, chérie? Quels pirates? Ici?! Va-t'en, tu es une idiote")+"...");
			link.l1 = RandPhraseSimple("Pas besoin d'être grossier...","Surveille ta langue!");
			link.l1.go = "exit";
		break;

		// ==> индейцы в поселении
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Visage pâle","Squaw blanche")+" veut parler ?","Vous encore, "+GetSexPhrase("visage pâle","squaw blanche")+".",""+GetSexPhrase("Visage pâle aime parler. Il ressemble à une squaw.","La squaw blanche aime parler.")+"","Les esprits ont amené mon visage pâle "+GetSexPhrase("frère","soeur")+" à moi.","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Oui.","Ouais, c'est encore moi.","Très poétique.","Je suis ravi de te voir aussi",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = "Dites-moi, pourquoi êtes-vous venu.";
			link.l1 = "Oh, rien de particulier, je voulais juste écouter ce que tu as à dire.";
			link.l1.go = "exit";
		break;
		
				
		case "CitizenNotBlade":
			dialog.text = "Capitaine, que faites-vous? Cachez votre arme, avant de causer beaucoup de problèmes!";
			link.l1 = LinkRandPhrase("D'accord.","D'accord.","Ne t'inquiète pas, je suis déjà en train de le ranger...");
			link.l1.go = "exit";
		break;  

	}
}
