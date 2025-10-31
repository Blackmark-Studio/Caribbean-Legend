void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Que voulez-vous?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;
		
		case "OZ_Kuznets_1":
			//PlaySound("VOICE\Russian\Master_05.wav");
			dialog.text = "Que désirez-vous, "+GetAddress_Form(NPChar)+"? Désolé, mais je n'accepte plus de nouvelles commandes. J'ai simplement... beaucoup de travail...";
			link.l1 = "Ah oui? On dit que vous avez récemment perdu aux cartes quelque chose de très précieux, est-ce vrai?";
			link.l1.go = "OZ_Kuznets_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_2":
			dialog.text = "Eh bien, si vous êtes venu pour vous réjouir de mon malheur, mettez-vous dans la file - il y a déjà assez de volontaires sans vous. Mais aucun n’a proposé de m’aider. Mon destin ne tient qu’à un fil, et il dépend entièrement de Javier Castillo, tandis que les gens ne cherchent qu’à se moquer de mon échec.";
			link.l1 = "Je ne suis pas de ceux qui rient du malheur des autres. Racontez-moi comment tout s’est passé. Peut-être pourrai-je vous aider.";
			link.l1.go = "OZ_Kuznets_3";
			link.l2 = "Aider? Et pourquoi quelqu’un devrait-il le faire? Certainement pas moi. Vous êtes l’artisan de votre propre bonheur... et de votre malheur aussi. Alors arrêtez de jouer la victime - acceptez simplement les conséquences de vos actes, elles sont plus que logiques.";
			link.l2.go = "OZ_Kuznets_NoAgree";
		break;
		
		case "OZ_Kuznets_NoAgree":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Kuznets_NoAgree");
		break;
		
		case "OZ_Kuznets_3":
			dialog.text = "Cette soirée n'aurait pas dû être fatale. Je suis simplement entré dans la taverne pour boire une chope de rhum après que l’amiral Eugenio de la Torre lui-même m’ait passé une grosse commande. Mais, bien échauffé, je me suis assis à une table pour jouer aux cartes. C’est là que Javier s’en est pris à moi\nAu début, la chance était de mon côté - j’ai même gagné une somme convenable, mais dès que j’ai commencé à croire en ma veine, la situation a complètement changé. Javier ne cessait de verser du rhum dans ma chope, et je perdais coup après coup : d’abord tout mon argent liquide, puis l’argent mis de côté pour les matériaux, et enfin toutes mes économies\nQuand j’ai réalisé combien j’avais déjà perdu, il était trop tard pour reculer. J’étais obsédé par une seule idée - me refaire à tout prix. Alors j’ai mis en jeu mon livre. Ce vaurien de Javier l’a estimé à seulement cinq mille pesos\nBien sûr, il vaut bien plus, mais j’étais tellement aveuglé par le jeu que j’ai accepté. Et ensuite... Je pense que vous connaissez la suite. J’ai perdu. Vous savez, cela ne m’était jamais arrivé. Je crois que ce scélérat m’a drogué.";
			link.l1 = "Et en quoi, permettez-moi de demander, puis-je vous aider? Vous vous êtes assis de votre plein gré à cette table, vous avez vous-même mis vos biens en jeu et tout perdu. Maintenant, vous refusez simplement d’accepter les conséquences? Et qu’a donc ce livre de si précieux pour que vous soyez si accablé?";
			link.l1.go = "OZ_Kuznets_4";
		break;
		
		case "OZ_Kuznets_4":
			dialog.text = "Ce livre est la chose la plus précieuse que je possédais. Il contient des secrets transmis de maître à élève pendant des siècles. Il est le cœur de ma forge, l’âme de mon métier. J’ai accepté ma défaite, "+GetAddress_Form(NPChar)+", mais comment puis-je accepter la perte de ce livre? J’ai proposé à Javier de le racheter pour cinq mille pesos\nJ’étais prêt à m’endetter juste pour le récupérer. Mais savez-vous ce qu’il a dit? Il a dit qu’il en voulait cent mille! Cent, "+GetAddress_Form(NPChar)+"! Je n’ai pas cet argent. Et il refuse de baisser le prix ou d’accepter un paiement échelonné. Je l’ai supplié... mais il n’a fait que se moquer de moi. Je vois que vous êtes "+GetSexPhrase("un homme courageux, marin... ou peut-être même capitaine. Et votre arme n’est pas là pour faire joli","une femme peu ordinaire, capable sûrement de trouver la bonne approche avec n’importe quel homme")+"\nJe vous en prie, parlez à Javier. Peut-être qu’il vous écoutera et acceptera un délai pour le paiement de la dette. Sans ce livre... ma vie n’a pas de sens. En échange, je pourrai toujours vous vendre des matériaux de qualité à bon prix lorsque je me remettrai sur pied, et peut-être même fabriquer quelque chose de spécial pour vous, capitaine.";
			link.l1 = "Eh bien, parler n’est pas bien compliqué. Voyons ce que cela donnera. Mais d’abord, permettez-moi de me présenter : je m’appelle "+GetFullName(pchar)+", capitaine de mon propre navire.";
			link.l1.go = "OZ_Kuznets_5";
		break;
		
		case "OZ_Kuznets_5":
			dialog.text = ""+GetSexPhrase("Et moi, je suis Sebastián Córdoba...","Une femme capitaine de son propre navire? J’en ai entendu parler, mais en rencontrer une et lui parler, jamais.")+" Ravi de faire votre connaissance, capitaine "+pchar.lastname+". Et merci à vous. De nos jours, il est plus facile de trouver des gens qui se moquent du malheur des autres que ceux prêts à aider. Vous savez, si mon livre me revient, je jure de ne plus jamais jouer à des jeux d’argent.";
			link.l1 = "Il n’y a encore rien à me remercier. Je vais d’abord m’occuper de mes affaires, et ensuite, si j’ai le temps, je parlerai à Javier.";
			link.l1.go = "OZ_Kuznets_6";
		break;
		
		case "OZ_Kuznets_6":
			dialog.text = "J’ai peur que vous ne soyez déjà trop tard. Javier s’est montré bien plus rapide que je ne le pensais\nIl a déjà trouvé un acheteur pour le livre - c’est Étienne Renoir, un maître armurier français. Si l’amiral apprend que par ma faute une telle valeur est tombée entre les mains des Français... je perdrai la tête. La prison serait une punition légère.";
			link.l1 = "Hmm... Très bien. Je vais m’occuper de votre problème immédiatement.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			AddDialogExitQuestFunction("OZ_Kuznets_Agree");
		break;
		
		case "OZ_Kuznets_repeat":
			dialog.text = "Capitaine "+ pchar.lastname +"! Avez-vous parlé à Javier? Quelles nouvelles?";
			link.l1 = "Pas encore, mais je me rends justement à la taverne.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			if (CheckCharacterItem(PChar, "OZ_book"))
			{
				link.l1 = "J’ai parlé"+GetSexPhrase("","e")+". Et avec succès. Javier est parti précipitamment pour l’autre monde, mais avant cela, il a rendu votre livre. Tenez.";
				link.l1.go = "OZ_Kuznets_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "OZ_Kuznets_11":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", vous n’imaginez pas ce que cela signifie pour moi! Grâce à vous, je vais pouvoir exécuter toutes les commandes, y compris celle de l’amiral lui-même! Je n’ai malheureusement pas d’argent, mais j’ai tout de même préparé une récompense pour vous\nTenez, prenez cette cuirasse - je l’ai fabriquée pour un don, mais je suis sûr qu’il pourra attendre un peu. Et j’ai aussi quelques matériaux qui vous seront utiles si vous décidez de fabriquer quelque chose vous-même.";
			link.l1 = "Merci, "+npchar.name+", vous êtes très généreux!";
			link.l1.go = "OZ_Kuznets_12";
			TakeItemFromCharacter(pchar, "OZ_book");
		break;
		
		case "OZ_Kuznets_12":
			dialog.text = "Et encore, passez me voir si vous avez besoin de matériaux. Mes livraisons ont lieu une fois par mois, donc il y aura toujours quelque chose d’utile pour vous - et à bon prix. Je tiens mes promesses.";
			link.l1 = "J’y manquerai pas! Eh bien, "+npchar.name+", portez-vous bien. Quant à moi, je dois y aller, j’ai des affaires.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Nagrada");
			GiveItem2Character(PChar, "cirass3");
			AddItems(PChar, "jewelry13", 10);
			AddItems(PChar, "jewelry12", 5);
			AddItems(PChar, "jewelry10", 5);
			AddItems(PChar, "jewelry11", 2);
			AddQuestRecordInfo("Useful_Acquaintances", "7");
		break;
		
		case "OZ_Kuznets_Fail":
			dialog.text = "Capitaine "+ pchar.lastname +"! Avez-vous parlé à Javier? Quelles nouvelles?";
			link.l1 = "Voyez-vous... le livre était entre mes mains. Mais... les circonstances ont fait qu’il a été vendu.";
			link.l1.go = "OZ_Kuznets_Fail_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_Fail_2":
			dialog.text = "Quoi?! Vous... vous l’avez vendu?! Mon livre?!";
			link.l1 = "Le livre que vous avez perdu aux cartes. Il a été vendu à ce Français auquel Javier l’avait promis.";
			link.l1.go = "OZ_Kuznets_Fail_3";
		break;
		
		case "OZ_Kuznets_Fail_3":
			dialog.text = "Mais... c’est ma fin. Le livre est chez les Français, la commande de l’amiral ne sera pas exécutée... ma vie est détruite... Je... je suis perdu!";
			link.l1 = "Vous vous êtes mis vous-même dans ce pétrin. Je pense que cela vous servira de bonne leçon. Adieu.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Fail");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "OZ_Shuler_1":
			PlaySound("Voice\english\tavern\Igroki v Tavernah-01.wav"); 
			dialog.text = "Hé, "+GetSexPhrase("marin","jolie demoiselle")+", tu veux tenter ta chance aux cartes? Assieds-toi, les mises sont ici raisonnables... du moins, pour les débutants.";
			link.l1 = "Je parie que tu es exactement celui que je cherche. C’est ainsi que tu as attiré Sebastián avant de le plumer jusqu’au dernier sou? Je suis ici pour lui rendre son livre.";
			link.l1.go = "OZ_Shuler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_2":
			dialog.text = "Eh bien, parfait. Donne cent mille - et tu peux le reprendre. Ce livre ne me sert à rien, je ne saurais même pas distinguer des pinces d’un marteau.";
			link.l1 = "Je te donne cinq mille - c’est toi-même qui avais fixé ce prix en battant le forgeron.";
			link.l1.go = "OZ_Shuler_3";
		break;
		
		case "OZ_Shuler_3":
			dialog.text = "Ha! Tu me prends pour un idiot? Je connais parfaitement la vraie valeur de ce livre. Cent mille, pas une pièce de moins. Ou alors, il partira chez les Français - eux n’ont aucun problème d’argent.";
			link.l1 = "Tu crois que les autorités fermeront les yeux sur le fait que tu t’apprêtes à vendre aux Français des plans espagnols? L’amiral sera furieux quand il l’apprendra.";
			link.l1.go = "OZ_Shuler_4";
		break;
		
		case "OZ_Shuler_4":
			dialog.text = "Oh, allons. Les autorités se moquent bien d’un vieux bouquin, elles ont déjà assez de soucis. Quant à l’amiral? Oui, il déteste les Français de tout son cœur, mais je n’ai aucune intention de l’attendre - avec une telle somme, je serai le bienvenu dans n’importe quelle colonie du Nouveau Monde.";
			link.l1 = "Alors faisons un marché. Tu recevras ton argent, mais pas tout de suite. Le forgeron te remboursera par versements, et le livre retournera aujourd’hui même chez lui en gage de mon honneur de capitaine. Pour toi, rien ne change - il te paiera quand même, et tu ne perdras pas un seul peso.";
			link.l1.go = "OZ_Shuler_5";
		break;
		
		case "OZ_Shuler_5":
			dialog.text = "On dirait que tu ne m’écoutes pas. J’ai été clair - j’ai besoin de l’argent tout de suite. Pas dans une semaine, ni dans un mois, ni quand le forgeron aura gratté la somme, mais maintenant. Je compte quitter cette île misérable au plus vite. Donc, soit la somme entière est dans mes mains sur-le-champ, soit le livre part aux Français, et ton honneur de capitaine, tu iras le mettre en gage chez le bourreau de l’amiral.";
			if (sti(pchar.Money) >= 100000 && GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
				link.l1 = "Écoute : jouons. Mes cent mille contre le livre. Si tu gagnes, tu quittes l’île en homme riche. Si tu perds, je prends le livre. Ou alors, tu ne joues qu’avec ceux qui tiennent les cartes pour la première fois?";
				link.l1.go = "OZ_Shuler_6";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "OZ_Shuler_6_No_Money";
				AddDialogExitQuestFunction("OZ_GameCards_Fail");
			}
		break;
		
		case "OZ_Shuler_6_No_Money":
			DialogExit();
			Notification_Money(false, 100000, "peso");
			LAi_CharacterDisableDialog(npchar);
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
			Notification_Skill(true, 30, SKILL_SNEAK);
			}
			else
			{
			Notification_Skill(false, 30, SKILL_SNEAK);
			}
		break;
		
		case "OZ_Shuler_6":
			dialog.text = "Ha! Je n’ai pas besoin de devenir riche - je le suis déjà! Pourquoi prendre le risque de perdre ce qui me rapportera une fortune?";
			link.l1 = "Eh bien, qui l’eût cru, Javier Castillo a peur de jouer? Et moi qui pensais"+GetSexPhrase("","e")+" que tu étais un joueur aguerri, et pas juste un escroc profitant de pauvres ivrognes.";
			link.l1.go = "OZ_Shuler_7";
			Notification_Money(true, 100000, "peso");
			Notification_Skill(true, 30, SKILL_SNEAK);
		break;
		
		case "OZ_Shuler_7":
			dialog.text = "Je n’ai pas peur, je ne vois juste pas l’intérêt de m’asseoir à la table alors que j’ai déjà tout ce qu’il me faut.";
			link.l1 = "Allez, je vois bien que tu trembles rien qu’à l’idée de jouer contre quelqu’un qui sait tenir des cartes. Laisse-moi deviner, tu es si pressé de partir parce que tu as honte? Tout le monde a déjà compris que tu ne peux pas battre un adversaire plus coriace qu’un ivrogne?";
			link.l1.go = "OZ_Shuler_8";
		break;
		
		case "OZ_Shuler_8":
			dialog.text = "Comment oses-tu? J’ai battu des gens qui ne daigneraient même pas s’asseoir à la même table que toi! On a déjà eu des mises assez grosses pour acheter un navire à chaque capitaine aussi insolent que toi! Jouons. Cinq mille par carte, chacun met cent mille, et celui qui n’a plus d’argent perd. On verra bien qui l’emporte.";
			link.l1 = "Moins de paroles, plus d’action. Distribue.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards");
		break;
		
		case "OZ_Shuler_Win_1":
			dialog.text = "Diable! C’est impossible...";
			link.l1 = "Alors, ce n’est pas si amusant quand c’est l’autre qui gagne?";
			link.l1.go = "OZ_Shuler_Win_2";
		break;
		
		case "OZ_Shuler_Win_2":
			dialog.text = "Espèce de tricheur! Tu crois que je n’ai rien vu? Pas question que je te laisse m’arnaquer! Je préfère encore te tailler en pièces.";
			link.l1 = "Tricheur? Ha-ha! On dirait surtout que tu ne sais pas perdre, mon ami. Mais puisque tu es si pressé de partir pour l’autre monde, je vais t’y aider. Aux armes!";
			link.l1.go = "exit";
			pchar.questTemp.OZ_Draka = true;
			AddDialogExitQuestFunction("OZ_GameCards_Duel");
		break;
		
		case "OZ_Shuler_Lose_1":
			dialog.text = "Ha! Alors, "+GetSexPhrase("mon ami","ma jolie")+", ça fait quoi de se sentir dépouill"+GetSexPhrase("é","ée")+"? On dit que l’audace est un second bonheur, mais pas dans ton cas.";
			link.l1 = "Ne te réjouis pas trop. Tu as juste eu de la chance.";
			link.l1.go = "OZ_Shuler_Lose_2";
		break;
		
		case "OZ_Shuler_Lose_2":
			dialog.text = "Les perdants disent toujours ça. Allez, tu as jou"+GetSexPhrase("é","ée")+" - tu as perdu, ne sois pas amer"+GetSexPhrase("","e")+". Si jamais tu trouves encore cent mille, tu pourras retenter ta chance... Mais il est peu probable que le résultat change...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards_Lose");
			AddLandQuestMark(characterFromId("PortSpein_Tavern"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_1":
			dialog.text = "Bonjour "+GetAddress_Form(NPChar)+". À quoi dois-je l’honneur de votre visite?";
			link.l1 = "Salutations. Je suis le capitaine "+GetFullName(pchar)+", et je souhaite vous parler de Javier Castillo.";
			link.l1.go = "OZ_Felip_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_2":
			dialog.text = "Hmm... Si ce filou vous doit aussi de l’argent, j’ai bien peur que vous deviez prendre place dans une longue file. Javier n’a jamais été pressé de rembourser ses dettes. Mais s’il obtient de l’argent, il commencera par me payer - j’ai fait en sorte qu’il n’ait pas d’autre choix.";
			link.l1 = "Heureusement, je ne suis pas son créancier. Combien vous doit-il exactement? Et quelles mesures avez-vous prises?";
			link.l1.go = "OZ_Felip_3";
		break;
		
		case "OZ_Felip_3":
			dialog.text = "Le montant total de sa dette est de cent cinquante mille pesos. Il n’a payé que dix mille, pensant sans doute que cela suffisait. Mais je lui ai vite fait comprendre qu’il se trompait. Mes hommes lui ont arraché vingt mille de plus. Le reste, il doit le rendre sous une semaine, et le délai touche à sa fin. Heureusement, j’ai entendu dire qu’il allait bientôt recevoir une belle somme grâce à la vente d’un livre.";
			link.l1 = "Vous pensez vraiment qu’il compte vous rendre cet argent? Je doute qu’il faille vous y fier. Javier ne cache même pas que, dès qu’il aura l’argent, il s’enfuira.";
			link.l1.go = "OZ_Felip_4";
		break;
		
		case "OZ_Felip_4":
			dialog.text = "Je le sais, capitaine. Mais rassurez-vous, j’ai déjà pris mes précautions pour qu’il ne puisse pas s’enfuir sans me rembourser.";
			link.l1 = "Je vois que vous contrôlez la situation. Mais, croyez-moi, un peu de sécurité en plus ne fait jamais de mal. Voyez-vous, je suis justement un"+GetSexPhrase("","e")+" spécialiste en recouvrement de dettes. Si vous me laissez agir en votre nom, je pourrai vous récupérer cet argent.";
			link.l1.go = "OZ_Felip_5";
		break;
		
		case "OZ_Felip_5":
			dialog.text = "Hélas, capitaine, le recouvrement de cette dette me coûte déjà trop cher, et je ne peux pas me permettre de payer vos services en plus...";
			link.l1 = ""+UpperFirst(GetAddress_Form(NPChar))+", ne vous inquiétez pas pour cela. J’ai un intérêt personnel dans cette affaire, et je vous aiderai gratuitement.";
			link.l1.go = "OZ_Felip_6";
		break;
		
		case "OZ_Felip_6":
			dialog.text = "Puis-je savoir quel est exactement cet intérêt?";
			link.l1 = "Disons que certaines de ses petites manigances à la table de jeu ne peuvent rester impunies.";
			link.l1.go = "OZ_Felip_7";
		break;
		
		case "OZ_Felip_7":
			dialog.text = "Eh bien, si cela ne me coûte rien, je ne vois pas pourquoi je refuserais. Une seule chose, capitaine : je vous prie de ne pas aller trop loin. Si ce vaurien rejoint ses ancêtres avant de m’avoir remboursé, je n’y gagnerai rien.";
			link.l1 = "Ne vous en faites pas, Felipe, j’agirai avec prudence.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
			AddDialogExitQuestFunction("OZ_Felip_2");
			pchar.questTemp.OZ_Dolg = true;
		break;
		
		case "OZ_Felip_again":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"! Déjà de retour? Auriez-vous réglé cela si vite?";
			link.l1 = "Malheureusement, pas encore. Mais j’y travaille.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
		break;
		
		case "OZ_Shuler_11":
			if (CheckAttribute(npchar, "quest.OZ_Shuler_Lose"))
			{
				dialog.text = "Ah, "+GetSexPhrase("capitaine","ma jolie")+"-prétentieux"+GetSexPhrase("","e")+"! Encore toi? Tu veux perdre encore quelques milliers?";
			}
			else
			{
				dialog.text = "Encore toi? Je t’ai pourtant dit clairement : l’argent sur la table - ou dégage.";
			}
			link.l1 = "Change de ton, Javier. Et sors ta bourse - je ne suis pas ici pour rien. Tu n’as pas oublié ta dette envers Felipe Alarcón? Je représente désormais ses intérêts. Alors choisis : soit tu rembourses ta dette immédiatement, soit je chercherai l’argent dans tes poches après que tu auras rejoint tes ancêtres.";
			link.l1.go = "OZ_Shuler_12";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_12":
			dialog.text = "Que le diable t’emporte! J’ai une affaire en cours, tu ne vois pas? Reviens dans quelques heures - on en parlera alors.";
			link.l1 = "On dirait que tu ne m’as pas entendu. J’ai été clair"+GetSexPhrase("","e")+" - j’ai besoin de l’argent tout de suite. Pas dans une semaine, pas dans un mois, ni quand tu les auras grattés, mais maintenant. Cent vingt mille pesos, pas un de moins. Le livre, je peux l’accepter comme équivalent de cinq mille.";
			link.l1.go = "OZ_Shuler_13";
		break;
		
		case "OZ_Shuler_13":
			dialog.text = ""+GetSexPhrase("Sale bâtard","Espèce de garce")+"! Si tu crois pouvoir te débarrasser de moi facilement, c’est la plus grosse erreur de ta misérable vie.";
			link.l1 = "On verra.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Shuler_Bitva");
		break;
		
		case "OZ_Frantsuz_1":
			//PlaySound("VOICE\Russian\tra_quest_1.wav");
			if (CheckAttribute(pchar, "questTemp.OZ_Draka"))
			{
				dialog.text = "Quel spectacle... Je dois avouer, "+GetAddress_Form(NPChar)+", que vous m’avez réjoui. Vous maniez la lame à merveille. Permettez-moi de me présenter - "+GetFullName(npchar)+". Et ce malheureux, si je ne m’abuse, est Javier Castillo?";
				link.l1 = "Exactement, c’est lui. Et moi, je suis le capitaine "+GetFullName(pchar)+".";
				link.l1.go = "OZ_Frantsuz_1_1";
			}
			else
			{
				dialog.text = "Quel spectacle... Je dois avouer, "+GetAddress_Form(NPChar)+", que vous m’avez réjoui. Vous maniez la lame à merveille. C’est amusant comme les circonstances se présentent parfois - le livre pour lequel j’ai fait un si long voyage a changé de propriétaire de la façon la plus inattendue. Mais j’espère tout de même ne pas repartir les mains vides.";
				link.l1 = "Hmm... Et à combien estimez-vous ce livre?";
				link.l1.go = "OZ_Frantsuz_2";
			}
		break;
		
		case "OZ_Frantsuz_1_1":
			dialog.text = "Voyez-vous, capitaine, j’ai parcouru une grande distance pour un certain livre... Et il semble qu’il soit désormais entre vos mains. J’espère sincèrement que nous pourrons parvenir à un accord - je ne voudrais pas quitter cet endroit les mains vides.";
			link.l1 = "Hmm... Et à combien estimez-vous ce livre?";
			link.l1.go = "OZ_Frantsuz_2";
		break;
		
		case "OZ_Frantsuz_2":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", je connais la valeur des choses vraiment rares. Quatre-vingt mille pesos. C’est une somme plus que généreuse, et croyez-moi, vous ne recevrez sans doute pas une telle offre deux fois.";
			link.l1 = "En effet, ce livre est précieux, et je vous avoue que je posais la question par simple curiosité. Mais je ne compte pas marchander le destin d’un homme. Hélas, monsieur, il n’y aura pas d’affaire - ce livre doit retourner à son propriétaire.";
			link.l1.go = "OZ_Frantsuz_3";
			link.l2 = "C’est une somme ridicule. Ce livre contient les secrets des meilleurs maîtres forgerons. Cent cinquante mille pesos - soit vous acceptez, soit il retourne à son propriétaire. Pas de négociation.";
			link.l2.go = "OZ_Frantsuz_4";
		break;
		
		case "OZ_Frantsuz_3":
			dialog.text = "Je vous en prie, ne refusez pas si vite. J’ai parcouru un long chemin pour elle. Je suis prêt à vous offrir cent mille, uniquement par respect pour l’habileté avec laquelle vous vous êtes occupé de cet homme.";
			link.l1 = "J’ai tout dit. Sur ce, excusez-moi, mais je dois y aller.";
			link.l1.go = "OZ_Frantsuz_4_1";
		break;
		
		case "OZ_Frantsuz_4_1":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "OZ_Frantsuz_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", j’apprécie votre assurance, mais cent cinquante mille, ce n’est plus un prix, c’est une absurdité. Ne transformons pas cette affaire en farce. Cent mille pesos, c’est raisonnable, acceptez, personne ne donnera plus pour ce livre.";
			link.l1 = "Il semble que nous ne parlions pas le même langage. Je ne vois donc aucune raison de poursuivre cette conversation. Adieu, monsieur.";
			link.l1.go = "OZ_Frantsuz_5";
		break;
		
		case "OZ_Frantsuz_5":
			dialog.text = "Attendez! Très bien, vous avez gagné. Cent cinquante mille. Marché conclu?";
			link.l1 = "Je suis heureux que vous ayez fait le bon choix. Le livre est à vous. Je pense qu’avec lui, vous deviendrez le meilleur artisan des Caraïbes.";
			link.l1.go = "OZ_Frantsuz_6";
			TakeItemFromCharacter(pchar, "OZ_book");
			AddMoneyToCharacter(pchar, 150000);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterNationReputation(pchar, SPAIN, -10);
			ChangeCharacterReputation(pchar, -5);
		break;
		
		case "OZ_Frantsuz_6":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", même sans ce livre, je n’avais pas d’égal. Mais je dois avouer qu’il est agréable d’obtenir un trophée aussi rare. Et maintenant, excusez-moi - j’ai hâte de vérifier si elle mérite vraiment tous les éloges que j’ai entendus à son sujet.";
			link.l1 = "Alors je ne vais pas vous retenir. Adieu.";
			link.l1.go = "OZ_Frantsuz_7";
		break;
		
		case "OZ_Frantsuz_7":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_2");
		break;
		
		case "OZ_Bandit_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Eh bien, qu’avons-nous là? Tu pensais piller notre coffre et filer? Erreur, mon ami. On va plutôt te fourrer tout entier dans ce coffre et clouer le couvercle!";
			}
			else
			{
				dialog.text = "Tiens donc... Qui voilà? Tu ne t’es pas perdue, ma jolie? Tu pensais piller le coffre et filer discrètement? Erreur, ma chère. On va d’abord bien te fouiller - et voir ce que tu caches dans tes poches... et ailleurs.";
			}
			link.l1 = "Trop de paroles pour de misérables vers comme vous. Sortez vos lames, voyons ce que vous valez vraiment.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Grot_4");
		break;
		
		case "OZ_Felip_11":
			dialog.text = "Capitaine! On m’a déjà rapporté que Javier a rendu l’âme par votre main. Et pourtant, je vous avais demandé de ne pas le tuer trop tôt! J’espère que vous êtes ici pour me rendre mon argent?";
			if (sti(pchar.Money) >= 100000)
			{
				link.l1 = "Exactement. J’ai trouvé sa planque, et il y avait cent mille pesos. C’est tout ce qu’il avait.";
				link.l1.go = "OZ_Felip_12";
			}
			link.l2 = "Oui, j’ai dû le tuer. Mais il m’a attaqué, et j’ai dû me défendre. Il n’avait pas un sou sur lui. Hélas, je n’ai pas pu récupérer la dette.";
			link.l2.go = "OZ_Felip_14";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.OZ_Dolg");
		break;
		
		case "OZ_Felip_12":
			dialog.text = "Cent mille... Bien sûr, ce n’est pas la somme complète, mais connaissant Javier, je doute que quelqu’un puisse lui soutirer davantage. Eh bien, merci à vous, capitaine. Il semble que je n’aie pas engagé les bonnes personnes. Vous êtes vraiment un maître dans votre domaine.";
			link.l1 = "Ce n’était pas difficile. Sur ce, je suis contraint"+GetSexPhrase("","e")+" de vous dire au revoir. Les affaires m’attendent.";
			link.l1.go = "OZ_Felip_13";
			AddMoneyToCharacter(pchar, -100000);
		break;
		
		case "OZ_Felip_13":
			dialog.text = "Au revoir, capitaine.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_good");
		break;
		
		case "OZ_Felip_14":
			dialog.text = "Espèce de salaud"+GetSexPhrase("","e")+"! Tu me mens droit dans les yeux?! Tu ne t’en sortiras pas comme ça!";
			link.l1 = "Argh...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_bad");
		break;
		
		case "OZ_Kuznets_Tovar":
			//PlaySound("VOICE\Russian\Master_02.wav");
			//PlaySound("VOICE\Spanish\Master_02.wav");
			dialog.text = "Bonjour, "+pchar.name+"! Voulez-vous acheter des matériaux ou des articles?";
			link.l1 = ""+TimeGreeting()+". Voyons ce que vous avez.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "Bonjour à vous aussi, "+npchar.name+"! Merci pour la proposition, mais je voulais simplement vous saluer.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
			SetFunctionTimerCondition("OZ_Kuznets_Reset", 0, 0, 1, false);
			if (!CheckAttribute(npchar, "quest.OZ_Kuznets_tovar")) 
			{
				SetFunctionTimerCondition("OZ_Kuznets_Reset_2", 0, 0, 30, false);
				npchar.quest.OZ_Kuznets_tovar = true;
			}
		break;
		
		case "OZ_Kuznets_Tovar_repeat":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", vous avez finalement décidé d’acheter quelque chose?";
			link.l1 = "Exactement. Montrez-moi ce que vous avez aujourd’hui.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "Hélas, je m’en vais déjà.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
		case "OZ_Kuznets_Tovar_2":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
	}
}