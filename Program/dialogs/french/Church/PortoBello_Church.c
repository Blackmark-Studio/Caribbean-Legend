// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quel genre de questions, "+GetSexPhrase("mon fils","mafille")+"?","Posez vos questions, je vous écoute..."),"Je vous écoute, parlez maintenant, "+GetSexPhrase("mon fils","mafille")+"... -> ","Pour la troisième fois, "+GetSexPhrase("mon fils","ma fille")+", demande   ce dont tu as besoin.","Un homme d'église a beaucoup de travail et vous me distrayez, "+GetSexPhrase("mon fils","mafille")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Pas en ce moment, padre..."),"Je n'ai rien à dire, mes excuses.","Je demanderai, mais plus tard. Pardonnez-moi, mon père.","Pardonnez-moi, saint père...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Church_1"))
            {
                link.l1 = "Mon père, je cherche Marisa Caldera. On dit qu’elle est très pieuse et qu’elle fréquentait souvent l’église. Pouvez-vous m’indiquer où la trouver ?";
                link.l1.go = "LFD_Church_1_1";
            }
			//<-- Письмо от покойника
		break;
		//--> Письмо от покойника
		case "LFD_Church_1_1":
			dialog.text = "Marisa était l’une des fidèles les plus dévouées de notre paroisse, véritable âme de notre église. Son absence est une perte immense pour la communauté. Ce qui l’a poussée à disparaître m’est inconnu, mais je n’ai aucun doute : elle a subi des épreuves imméritées, et tout cela n’est pas étranger aux machinations du diable et de ses serviteurs\nParfois, on me rapporte quelques rumeurs selon lesquelles elle serait réapparue en ville, mais rien de plus. Il ne nous reste qu’à nous confier à la volonté du Seigneur et espérer qu’un jour, elle reviendra et retrouvera du réconfort sous l’ombre de l’église.";
			link.l1 = "Peut-être connaissez‑vous quelqu’un qui pourrait m’en dire davantage à son sujet ?";
			link.l1.go = "LFD_Church_1_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LFD_Church_1_2":
			dialog.text = ""+GetSexPhrase("Mon fils","Ma fille")+", dis-moi, pourquoi as-tu besoin de Marisa ? Je sais que, de temps en temps, des personnes la cherchent, et toutes ne semblent pas animées par la vertu. Le monde est plein de tentations, et tous ceux qui la recherchent ne sont pas poussés par le bien. Avant de prononcer le moindre mot, je dois être sûr que tu n’apporteras ni mal à elle, ni à ceux qui pourraient être liés à elle.";
			link.l1 = "Je comprends vos inquiétudes, mon père, mais je vous assure : je n’ai aucune mauvaise intention. Je souhaite seulement lui remettre une lettre qui a mis trop de temps à lui parvenir. Qui sait ? Elle pourrait contenir quelque chose d’important pour elle. Tenez, regardez.";
			link.l1.go = "LFD_Church_1_3";
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Remis : Lettre pour Marisa Caldera", "None");
		break;
		
		case "LFD_Church_1_3":
			dialog.text = "Oui, cette lettre semble avoir traversé bien des tempêtes avant d’arriver entre vos mains. Qui sait ce qu’elle renferme, et quelles conséquences sa lecture pourrait entraîner... Mais vous agissez noblement, capitaine, en la restituant à sa destinataire. Si quelqu’un sait où se trouve Marisa à l’heure actuelle, c’est bien son amie Dolores Monjo, la seule en qui elle pouvait avoir confiance\nSa maison se trouve à gauche de l’administration portuaire. Puissent ces mots ne pas apporter davantage de souffrance à Marisa, car les épreuves ne lui ont pas manqué jusqu’à présent.";
			link.l1 = "Merci, mon père. Que le Seigneur vous garde.";
			link.l1.go = "LFD_Church_1_4";
			GiveItem2Character(PChar, "LFD_letter");
		break;
		
		case "LFD_Church_1_4":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Church_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
