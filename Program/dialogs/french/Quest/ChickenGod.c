int questShips[50];
int questShipsNum = 0;

extern void InitGunExt(string id,			
				string sAttr,       
				string sBullet,     
				string sGunPowder,  
				float  DmgMin_NC,   
				float  DmgMax_NC,   
				float  DmgMin_C,    
				float  DmgMax_C,    
				float  EnergyP_NC,  
				float  EnergyP_C,   
				bool   Stun_NC,     
				bool   Stun_C,      
				bool   MultiDamage, 
				int    MisFire,     
				bool   SelfDamage,  
				bool   Explosion,   
				float  Accuracy,    
				int    ChargeSpeed, 
				bool   isDefault );

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp, attr, companion;
	ref chref;
	int iTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string node = Dialog.CurrentNode;
	if(HasSubStr(node, "joruba_p3_ship_")) {
		iTemp = findsubstr(node, "joruba_p3_ship_", 0);
	 	companion = strcut(node, iTemp + strlen("joruba_p3_ship_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p3";
	}
	
	if(HasSubStr(node, "joruba_p4_off_")) {
		iTemp = findsubstr(node, "joruba_p4_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_p4_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p4_off";
	}

	if(HasSubStr(node, "joruba_o6_off_")) {
		iTemp = findsubstr(node, "joruba_o6_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_o6_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_o6_off";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Tu n'es pas censé voir ça.";
			link.l1 = "C'est l'heure de rédiger un rapport de bug.";
			link.l1.go = "exit";
		break;
		
        case "native":
			dialog.text = "Eh bien ! Ta'kahi, jeune homme. Je ne veux pas être impoli, mais comment êtes-vous entré ici ? J'ai fortement conseillé à Madame de fermer l'établissement pendant la durée de mon séjour.";
			link.l1 = "En effet, ça craint. Comment t'ont-ils laissé entrer ? Pourquoi ce bordel n'a-t-il pas déjà été réduit en cendres par des gens pieux et furibonds ?";
			link.l1.go = "native_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Panama");
		break;
		
        case "native_1":
			dialog.text = "Les doublons d'or ouvrent tous les chemins et rendent les blancs plus heureux. Ne le saurais-tu pas ?";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+" Je peux sentir l'odeur presque vieillie de Versailles, où tu as été admis avec un tel grincement.";
			}
			link.l1 = "Ne me parle pas comme ça, face de rat. C'est vrai que je suis nouveau ici, bien que je ne sache pas comment tu l'as appris. Je pourrais te tirer dessus là où tu te tiens et obtenir n'importe quelle fille pour la nuit pour compenser le désagrément.";
			link.l1.go = "native_var1";
			link.l2 = "Je ne sais pas qui t'a raconté ces balivernes, mais tu parles plutôt bien, je te le concède. C'est la première fois que je vois un indigène aussi instruit.";
			if (HasSubStr(pchar.model, "Sharle")) {
				link.l2 = link.l2+"Versailles, mon cul!";
			}
			link.l2.go = "native_var2";
		break;
		
        case "native_var1":
			dialog.text = "Non, Capitaine, vous ne savez rien. Je suis parfaitement en securite ici... pour l'instant. Cependant, puisque nous sommes devenus si familiers si rapidement, essayons encore. Boisson ?";
			link.l1 = "Je peux faire cela, tu as définitivement éveillé mon intérêt.";
			link.l1.go = "native_play";
		break;
		
        case "native_var2":
			dialog.text = "Bravo ! Je vois que nous sommes déjà familiers et que nous échangeons des piques. Maintenant, je propose de boire à la paix et de parler affaires.";
			link.l1 = "Je peux faire cela, vous avez certainement éveillé mon intérêt.";
			link.l1.go = "native_play";
		break;
		
        case "native_play":
			dialog.text = "Etant donné l'objet de cet endroit, votre commentaire, Capitaine, m'inquiète beaucoup ! Je suis coincé ici depuis presque un mois maintenant. J'ai essayé tout ce qui me venait à l'esprit, et je suis prêt à grimper les murs d'ennui et d'inutilité.";
			link.l1 = "Partez alors. Visitez une église pour changer... où ils ne vous laisseront pas entrer.";
			link.l1.go = "native_play_1";
		break;
		
        case "native_play_1":
			dialog.text = "Ce n'est pas si simple car je suis obligé de passer encore vingt-quatre heures dans ce bordel, selon mon... contrat.";
			link.l1 = "Ça semble affreux bien sûr, mais tu n'auras aucune sympathie de ma part. Une location exclusive de bordel pour un mois est un rêve devenu réalité !";
			link.l1.go = "native_play_2";
		break;
		
        case "native_play_2":
			dialog.text = "Redoutez vos désirs, Capitaine. Je ne sais pas comment vous êtes arrivé ici, car j'étais censé passer ce mois seul. Seul avec une squaw et du vin, mais je n'ai pu faire que du vin vers le troisième jour, à peu près. Et aujourd'hui était le jour où j'en ai eu assez aussi.";
			link.l1 = "Et que veux-tu que je fasse ? Partager un tas de filles et de vin avec toi ?";
			link.l1.go = "native_play_3";
		break;
		
        case "native_play_3":
			dialog.text = "Peut-être, mais je suggère que nous jouions d'abord ! Mille pièces d'argent par carte ! Mon nom est Agueybana, d'ailleurs.";
			link.l1 = "La mienne est "+GetFullName(pchar)+"Bien sûr, jouons.";
			link.l1.go = "native_accept";
			link.l2 = "Le mien est "+GetFullName(pchar)+". Mille pesos ? Pas mal. Je vais y réfléchir, mais sans promesses.";
			link.l2.go = "native_decline";
		break;
		
        case "native_play_again":
			dialog.text = "Vous avez changé d'avis, capitaine ? On y va ?";
			link.l1 = "D'accord, pourquoi diable pas.";
			link.l1.go = "native_accept";
			link.l2 = "Pas encore.";
			link.l2.go = "native_decline";
		break;
		
        case "native_decline":
			DialogExit();
			
			NextDiag.CurrentNode = "native_play_again";
		break;
		
        case "native_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1");
		break;
		
        case "native_cards_loss":
			dialog.text = "Merci pour le jeu, capitaine. Je pensais que cela me remonterait le moral, mais ce n'est pas le cas. Laissez-moi tranquille, je me débrouillerai encore un jour de plus tout seul, d'une façon ou d'une autre. Maudit soit ce salaud !";
			link.l1 = " C'est tout ? Je l'avoue, ma déception est plus grande que l'amertume de perdre un sacré paquet d'argent.";
			link.l1.go = "native_cards_loss_1";
		break;
		
        case "native_cards_loss_1":
			dialog.text = "Vous n'étiez même pas censé être ici, capitaine. Mais si vous brûlez d'envie de savoir de quoi il s'agissait... cherchez un ancien temple sur le continent. Et apportez beaucoup de tuunich kaane'. Tenez, prenez-en un.";
			link.l1 = "Une pierre d'aspic ? Une pierre avec un trou correspond certainement à l'endroit. Merci, Agueybana";
			link.l1.go = "native_cards_loss_2";
		break;
		
        case "native_cards_loss_2":
			dialog.text = "Adieu, capitaine.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game1LossGoAway");
		break;
		
        case "native_cards_win":
			dialog.text = "Zut alors ! Merci, capitaine ! Dommage pour l'argent, mais au moins j'ai de nouveau goûté à la vie !";
			link.l1 = "Ouais, c'est la première fois que je vois quelqu'un s'enthousiasmer autant pour un itinéraire comme celui-ci. Où as-tu trouvé tout cet argent, d'ailleurs ?";
			link.l1.go = "native_cards_win_1";
		break;
		
        case "native_cards_win_1":
			dialog.text = "Une question impolie que vous ne poseriez jamais à votre égal, capitaine ! Mais la nuit est encore jeune, et il me reste pas mal de pièces. Que diriez-vous d'une revanche ?";
			link.l1 = "Pourquoi diable pas ? Faisons-en un autre !";
			link.l1.go = "native_cards_win_2";
		break;
		
        case "native_cards_win_2":
			dialog.text = "Je propose que cette fois-ci nous jouions aux dés et augmentions un peu les enjeux. J'ai aussi une histoire à te raconter, alors loue une chambre à l'étage pour nous deux, je te prie. Trop d'oreilles ici ! Je t'apprécierais si tu allais chez Madame et payais pour la chambre. Mon crédit, malheureusement, ne s'applique pas à toi.";
			link.l1 = "Louer une chambre ? Pour deux ? Ici ? Va te faire foutre, Agueybana ! Je me tire d'ici !";
			link.l1.go = "native_cards_rematch_decline";
			link.l2 = "Oh, bon sang. Cette histoire finira soit en bonne anecdote, soit en bain de sang très coûteux. Mon épée reste avec moi, alors pas de plaisanteries, ha-ha ! Attends ici, je vais régler ça.";
			link.l2.go = "native_cards_rematch_accept";
		break;
		
        case "native_cards_rematch_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinNoRematch");
		break;
		
        case "native_cards_rematch_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinRematch");
		break;
		
        case "native_dice":
			dialog.text = "Alors ?";
			link.l1 = "J'espère sincèrement que tu m'as appelé ici uniquement pour boire et jouer.";
			link.l1.go = "native_dice_1";
		break;
		
        case "native_dice_1":
			dialog.text = "Ne t'inquiète pas, capitaine, je ne suis pas intéressé par de telles sottises ! Bien que, si tu étais arrivé ici le premier jour... ha ha ! Commençons-nous ?";
			link.l1 = "La fortune sourit aux audacieux !";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game2");
		break;
		
        case "native_dice_win":
			dialog.text = "Uh-oh !  Cela fait du bien !  Félicitations pour votre victoire, Capitaine.";
			link.l1 = "Ne va pas trop loin. Il est temps que tu m'éclaires sur ce qui se passe ici, bon sang ?";
			link.l1.go = "native_dice_story";
			link.l2 = "Tu es étrange, Agueybana. Maintenant, si je ne quitte pas cet endroit immédiatement, ma réputation de gentilhomme et d'homme sera irrémédiablement ternie. Donne-moi mon argent et séparons-nous.";
			link.l2.go = "native_dice_win_not_story";
		break;
		
        case "native_dice_loss":
			dialog.text = "Quel dommage, j'espérais finir la journée sur une autre note...";
			link.l1 = "C'est la première fois que je vois un homme si contrarié de gagner ce jeu plébéien. Peux-tu au moins m'éclairer maintenant sur ce qui diable se passe ici ?!";
			link.l1.go = "native_dice_story";
			link.l2 = "Va te faire foutre, Agueybana ! J'en ai assez de ça !";
			link.l2.go = "native_dice_loss_not_story";
		break;
		
        case "native_dice_story":
			dialog.text = "Autant que je peux, capitaine. Je ne suis pas sûr d'en avoir le droit, mais vous avez illuminé mes derniers jours... Dans ce bordel, je veux dire.";
			link.l1 = "Et de quoi s'agissait-il ?";
			link.l1.go = "native_dice_story_1";
		break;
		
        case "native_dice_story_1":
			dialog.text = "N'oublie pas... Écoute ici, homme blanc ! Je suis le grand chef du peuple Taino, Agueybana. Parfois, je rêve que je suis né cent ans plus tôt et que j'ai chassé les envahisseurs espagnols de mes îles ! Mais à la place j'ai vendu trois mille de mes tribus aux mines pour dix doublons par tête.";
			link.l1 = "Une biographie digne. J'ai soudain l'envie de te tirer dessus, Agueybana, et de te laisser pourrir dans ce trou à vin aigre.";
			link.l1.go = "native_dice_story_2";
		break;
		
        case "native_dice_story_2":
			dialog.text = "Peu importe, capitaine. Tout ce que j'ai toujours voulu, c'était être comme vous.";
			link.l1 = "Comme moi ?";
			link.l1.go = "native_dice_story_3";
		break;
		
        case "native_dice_story_3":
			dialog.text = "J'ai vu vos navires - merveilles du génie humain - et j'en ai voulu un pour moi. J'ai vu vos femmes dans des corsets serrés, et rêvé d'en enlever un moi-même. J'ai observé même les plus misérables de vos commandants exercer un pouvoir au-delà des rêves de n'importe lequel de nos dirigeants. J'ai entendu des histoires sur l'Europe et les immenses maisons de pierre où les gens vivent au lieu de survivre. Et j'ai tout eu ! De plus, je suis même allé en Europe et tout cela l'année dernière !";
			link.l1 = "Tu as bu trop de vin, chef. Les seuls billets pour l'Europe pour toi seraient des chaînes, au grand plaisir du Vatican et des saltimbanques. Ce dont tu parles est tout simplement impossible dans le monde où nous vivons.";
			link.l1.go = "native_dice_story_4";
		break;
		
        case "native_dice_story_4":
			dialog.text = "C'est le monde dans lequel nous vivons, capitaine. Il m'a déjà été expliqué que notre monde est faux, imaginaire, et que tout est possible.";
			link.l1 = "Et qui est l'imbécile qui t'a dit ça ? Apparemment, ils ne te laissent pas seulement entrer dans les bordels, mais aussi dans les asiles !";
			link.l1.go = "native_dice_story_5";
		break;
		
        case "native_dice_story_5":
			dialog.text = "Maintenant, nous arrivons au cœur de mon histoire. Vous savez comment les choses fonctionnent ici, n'est-ce pas ? Les Espagnols et les Anglais payent nos prisonniers de guerre avec des armes, des outils et de la poudre à canon. J'ai payé pour les membres de ma tribu avec votre argent. Pourquoi pensez-vous que c'est ainsi ?";
			link.l1 = "J'ai l'impression que tu es sur le point de m'éclairer.";
			link.l1.go = "native_dice_story_6";
		break;
		
        case "native_dice_story_6":
			dialog.text = "Seuls les dieux peuvent satisfaire nos désirs les plus profonds et les plus honteux. Si tu ne peux pas vivre la vie que tu veux, alors demande-leur d'interférer avec le destin. Eux seuls peuvent satisfaire nos désirs les plus profonds et les plus honteux. C'est la voie. Mais voilà le problème : presque tous nos dieux sont déjà morts, et même s'ils ne l'étaient pas, ils ne s'intéressaient jamais à l'or de toute façon. Heureusement, la nature a horreur du vide, et un nouveau dieu est apparu dans l'une des anciennes pyramides. Il se moque de qui tu es : local ou Européen, méchant ou héros - paie simplement et tu obtiendras ce que tu as demandé ! Toutes les tribus le savent, et certains de tes gens aussi. J'ai payé le prix en or et vécu comme l'un de vous. Demain, ça fera un an.";
			link.l1 = "Quel dieu ? En Europe et retour en un an ? Et le point culminant de ton voyage était un misérable bordel dans les Caraïbes ? Oh, diable. Ça ressemble à l'histoire d'un ivrogne, et je l'achèterai comme telle. Prenons un verre et continuez ton histoire.";
			link.l1.go = "native_dice_story_7";
		break;
		
        case "native_dice_story_7":
			dialog.text = "Tout ce que je t'ai dit est la vérité. Il n'y a rien de plus à raconter.";
			link.l1 = "Tu n'as pas vécu assez longtemps dans notre monde, Agueybana. Chaque fable inspirée par l'alcool, surtout celle racontée ivre dans un bordel, doit se terminer par une morale. Nous devrions certainement philosopher avant de finir notre salon correctement.";
			link.l1.go = "native_dice_story_8";
		break;
		
        case "native_dice_story_8":
			dialog.text = "Comment finissent-ils habituellement ?";
			link.l1 = "Tu ne sais pas ? Ça dépend du sexe du participant, bien sûr ! Bataille à poings nus avec les hommes, emmène les femmes au lit. Parfois, la mode impose le contraire cela dit. Alors, quelle est la morale de ta fable ? L'argent ne fait pas le bonheur ? Ennuyeux !";
			link.l1.go = "native_dice_story_9";
		break;
		
        case "native_dice_story_9":
			dialog.text = "Cela n'est pas la morale de ma fable, comme tu dis. Mais puisque tu l'as commencée, je ressens le besoin de dire que je ne suis pas d'accord avec ton point de vue. Au contraire, je crois que l'argent achète le bonheur et rend les gens meilleurs.";
			link.l1 = "Balivernes ! Vous semblez maintenant vous contredire. Vous avez amassé une fortune considérable grâce au commerce de votre propre peuple. Vous souvenez-vous du montant total de vos bénéfices ? Près de trente mille pièces d'or ? Prenez un moment pour réfléchir, mais il est clair pour moi que l'argent ne vous a pas apporté le bonheur. Cela vous a toutefois acheté ce joli appartement.";
			link.l1.go = "native_dice_story_10";
		break;
		
        case "native_dice_story_10":
			dialog.text = "Très bien, je vais ajuster mon point de départ : l'argent rend la vie et les gens meilleurs.";
			link.l1 = "C'est mieux, mais qu'est-ce qui te fait penser que cela rend les gens meilleurs ? Tu es donc un modèle de vertu maintenant ? Et qu'en est-il de ceux qui n'ont pas beaucoup d'argent ? Allons-nous les étiqueter comme de mauvaises personnes ?";
			link.l1.go = "native_dice_story_11";
		break;
		
        case "native_dice_story_11":
			dialog.text = "Vous savez, capitaine, j'apprécie vraiment cette conversation. Permettez-moi de préciser encore : l'argent améliore la vie et les gens, mais seulement ceux qui possèdent déjà une étincelle de vertu.";
			link.l1 = "Ecoutez, ecoutez ! Alors, pas d'étincelle pour vous, hein ?";
			link.l1.go = "native_dice_story_12";
		break;
		
        case "native_dice_story_12":
			dialog.text = "Non. J'étais le chef de mon peuple et, contrairement à l'argent, le pouvoir corrompt assurément les hommes. Vous savez quoi, capitaine ? Je vous regarde maintenant et je réalise que vous ferez face au même dilemme un jour.";
			link.l1 = "Ton idole t’a aussi doté"+GetSexPhrase("","e")+" du don de voyance ? Alors tu devrais aller à Santiago, j’ai entendu"+GetSexPhrase("","e")+" dire qu’on y porte un intérêt particulier aux médiums et aux devins.";
			link.l1.go = "native_dice_story_13";
		break;
		
        case "native_dice_story_13":
			dialog.text = "Finissons notre... euh, salon sans bagarres ni coucheries, s'il vous plaît. Je n'ai pas réussi à tirer une morale de mon histoire, alors je voudrais proposer un toast à la place.";
			link.l1 = "Tu es complètement perdu, chef. Mais sur un point, tu as raison. Buvons plutôt !";
			link.l1.go = "native_dice_story_14";
		break;
		
        case "native_dice_story_14":
			dialog.text = "Que nos souhaits soient toujours en accord avec nos besoins. Merci, Capitaine, c'est une fin appropriée à... notre soirée. Si vous souhaitez un jour tester la véracité de ma fable, allez sur le continent et trouvez-y un ancien temple. Apportez avec vous cent treize tuunich kaane'. Il m'en reste quatre-vingt-dix-neuf - prenez-les et adieu !";
			link.l1 = "Un tas de pierres avec des trous ? Ça convient bien à l'endroit. Merci pour la soirée, Agueybana. À bientôt ?";
			link.l1.go = "native_dice_story_15";
		break;
		
        case "native_dice_story_15":
			dialog.text = "Non, tu ne le feras pas. Adieu, capitaine.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_BuyAmulets");
		break;
		
        case "native_dice_win_not_story":
			dialog.text = "Je comprends, capitaine. Pour le meilleur ou pour le pire, je vais vous donner un tuyau sur le trésor. Après tout, vous avez égayé mes derniers jours... Dans ce bordel, je veux dire. Cherchez un ancien temple dans la grande terre et rapportez un tas de tuunich kaane'. Tenez, prenez-en un.";
			link.l1 = "Une pierre d'aspic? Comme c'est charmant et une pierre avec un trou convient certainement à l'endroit. J'en ai assez de ton traitement !";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_loss_not_story":
			dialog.text = "Je comprends que vous soyez contrarié, capitaine. Pour le meilleur ou pour le pire, je vais vous donner un tuyau sur le trésor. Après tout, vous avez égayé mes derniers jours... Dans ce bordel, je veux dire. Cherchez un ancien temple dans la grande terre et rapportez une pile de tuunich kaane'. Tenez, prenez-en un.";
			link.l1 = "Une pierre d'aspic ? Comme c'est charmant et une pierre avec un trou s'accorde parfaitement à l'endroit. J'en ai assez de votre traitement !";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_not_story":
			dialog.text = "Adieu, capitaine.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotBuyAmulets");
		break;
		
		case "joruba":
			dialog.text = "Encore un autre ? Oh putain, j'en ai ras le bol de vous tous !";
			link.l1 = "A-a-ah! Va-t'en!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_1";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_1":
			dialog.text = "Eh? Oui, c'est ça. Incline-toi devant moi, mortel ! Contemple le pouvoir de ma pyramide !";
			link.l1 = "(crier désespérément)";
			link.l1.go = "joruba_2";
			link.l2 = "(tue le monstre)";
			link.l2.go = "joruba_3";
		break;
		
		case "joruba_2":
			dialog.text = "C'est exact. Bienvenue dans ma modeste factorie, capitaine.";
			link.l1 = "Q-qui es-tu ?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_3":
			DialogExit();
			
			NextDiag.CurrentNode = "joruba_3_next";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_3_next":
			dialog.text = "Je te félicite pour ta persévérance. Quelle est ta prochaine manœuvre, capitaine ? Que penses-tu de faire un peu de commerce ?";
			link.l1 = "Q-qui es-tu ?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_4":
			dialog.text = "Peu importe ce que je suis, c'est la fonction que je remplis qui compte. En ce moment, je mène des transactions commerciales avec les habitants de ce trou à rats pour un bénéfice mutuel.";
			link.l1 = "Le trou à rats ? Tu parles de ce temple ?";
			link.l1.go = "joruba_6";
			
			AddDialogExitQuestFunction("ChickenGod_JorubaToNormal");
		break;
		
		case "joruba_6":
			dialog.text = "Votre premier et dernier avertissement, capitaine ! Cependant, cette pyramide est en effet un peu à l'étroit, évidemment je l'ai dépassée.";
			link.l1 = "Tu as mentionné quelque chose à propos du commerce. De quel genre de commerce parles-tu ?";
			if (CheckAttribute(pchar, "questTemp.ChickenGod.SawJoruba")) {
				link.l1.go = "joruba_7A";
			} else {
				link.l1.go = "joruba_7";
			}
		break;
		
		case "joruba_7":
			dialog.text = "Je donne ce dont les gens ont le plus besoin.";
			link.l1 = "Vous exaucez des voeux? Comme un génie d'un conte de fées? Bon Dieu, que se passe-t-il ici?!";
			link.l1.go = "joruba_7_1";
		break;
		
		case "joruba_7_1":
			dialog.text = "N'aie pas l'absurdité ! J'aide seulement les gens à obtenir ce pour quoi ils sont venus en ce monde de la manière la plus rapide et agréable.";
			link.l1 = "Es-tu un chaman ou quelque chose du genre ?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_7A":
			dialog.text = "Eh bien, vous avez rencontré Agueybana, cela devrait vous donner quelques idées.";
			link.l1 = "Cet Indien pauvre, perdu et ivre était ton oeuvre?";
			link.l1.go = "joruba_7A_1";
		break;
		
		case "joruba_7A_1":
			dialog.text = "Ce n'est pas moi qui ai vendu sa tribu pour quelques milliers de livres d'or, ce n'est pas moi qui lui ai versé des tonneaux de liqueur dans la gorge, et je ne l'ai certainement pas forcé à attraper chaque maladie, connue et inconnue, de centaines de catins. C'est lui qui m'a demandé de le transformer en aristocrate blanc, alors je l'ai fait. Comme son destin me l'a ordonné.";
			link.l1 = "Vous exaucez des voeux ? Comme un génie d'un conte de fées ? Bon Dieu, qu'est-ce qui se passe ici ?!";
			link.l1.go = "joruba_7A_2";
		break;
		
		case "joruba_7A_2":
			dialog.text = "N'ayez pas l'absurdité ! Je ne fais qu'aider les gens à obtenir ce pour quoi ils sont venus dans ce monde de la manière la plus rapide et agréable. Agueybana était censé sauver son peuple du joug des envahisseurs européens, mais à la place, il bavait trop sur le corset de la fille du commandant et a décidé de mettre en gage le sien.\nDès lors, le seul sens qui restait dans sa vie était de réaliser la profondeur de son erreur et de recommencer bientôt. Une année en Europe, la cirrhose et le temps que vous avez passé dans un bordel ont dû aider. Mais j'admets, il a passé de bonnes vacances, ha ha !";
			link.l1 = "Cirrho quoi ? Es-tu un chaman ou quelque chose comme ça ?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_8":
			dialog.text = "Ou quelque chose. Cependant, mon offre te plaira. Et, pour changer, je serai vraiment heureux d'aider.";
			link.l1 = "Très bien. Combien?";
			link.l1.go = "joruba_9A";
			link.l2 = "Pourquoi ? Suis-je spécial ?";
			link.l2.go = "joruba_9B";
		break;
		
		case "joruba_9A":
			dialog.text = "Pas trop mal, capitaine. Soit t'es malin, soit t'es bête comme un âne, mais tes chances viennent d'augmenter un peu. Le prix ne sera pas un problème.";
			link.l1 = "As-tu besoin de tuer quelqu'un ? Je ne fais pas ça.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_9B":
			dialog.text = "Car ton but dans cette vie est de faire des trous dans un bon ami à moi, ha ha !";
			link.l1 = "As-tu besoin de tuer quelqu'un ? Je ne fais pas ça.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_10":
			dialog.text = "Premièrement, tu le fais. Deuxièmement, nous mènerons quatre transactions majeures, et quatre autres plus petites. Chacune te rendra beaucoup plus fort et augmentera tes chances dans ce monde cruel et étrange. Si tu termines chaque affaire, je garantis qu'un jour tu pourras sortir et combattre des dieux à armes égales, sans parler des simples mortels.";
			link.l1 = "Ça a l'air amusant. Parle-m'en.";
			link.l1.go = "joruba_11";
		break;
		
		case "joruba_11":
			dialog.text = "Choix judicieux ! D'habitude, mes discours conduisent les gens à être emmenés à Blueweld avec une suspicion de crise cardiaque, mais tu tiens plutôt bien le coup. Voici la liste des tâches : de petites courses de nature commerciale que j'attends que tu fasses. Pas de délais, hehe.";
			link.l1 = "Curieux. Je lirai la liste plus tard. Autre chose ?";
			link.l1.go = "joruba_12";
		break;
		
		case "joruba_12":
			dialog.text = "Ouais, la première grande transaction. Deux mille doublons, c'est le prix.";
			link.l1 = "Peut-être que je m'y risquerai... Mais c'est une sacrée somme! Pourquoi as-tu besoin de tant? Puis-je payer en pesos?";
			link.l1.go = "joruba_13";
			link.l2 = "Es-tu fou ? Je peux acheter une frégate avec cet argent !";
			link.l2.go = "joruba_insult";
		break;
		
		case "joruba_13":
			dialog.text = "La pyramide a besoin de réparations - la maçonnerie tombe parfois sur la tête des clients et cela nuit aux affaires. Mes hommes la réparent tous les jours, mais notre organisation a besoin d'une injection urgente d'argent de l'extérieur pour régler la situation définitivement. Quant aux pesos - je ne les apprécie guère, car leur taux de change est assez volatil.";
			link.l1 = "Tu es injuste envers les honnêtes pesos... Attends une minute, tu n'es pas seul ici ?";
			link.l1.go = "joruba_14";
		break;
		
		case "joruba_14":
			dialog.text = "Non, je suis la facade d'une organisation serieuse. Alors, tu es partant?";
			link.l1 = "Je vais y réfléchir, mais d'abord, j'aimerais savoir ce que je vais obtenir pour une somme si conséquente.";
			link.l1.go = "joruba_15";
		break;
		
		case "joruba_15":
			dialog.text = "Pourquoi gâcher la surprise ? De plus, considère cet argent comme une taxe. Ton acquisition la plus précieuse sera de débloquer les prochaines affaires. Les récompenses seront divines. Uniques aussi, note-le bien, car tu ne les trouveras nulle part ailleurs !";
			link.l1 = "D'accord. Comment vous appelez-vous déjà ?";
			link.l1.go = "joruba_16";
		break;
		
		case "joruba_16":
			dialog.text = "Aruba la Magnifique. Une dernière chose, "+pchar.name+", l'entrée à la pyramide n'est autorisée qu'une fois par jour. Ne retardez pas les autres clients et ne me dérangez pas pour rien.";
			link.l1 = "Je ne vois pas la file d'attente se former... Adieu, votre majesté.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			AddDialogExitQuestFunction("ChickenGod_GiveFirstTask");
		break;
		
		case "joruba_wait":
			dialog.text = "Ahoy, capitaine. Qu'as-tu pour moi ?";
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1.Completed") && PCharDublonsTotal() >= 2000) {
				link.p1 = "Here are your doubloons. It's hard enough to carry that damned metal around... but it is even harder to part with it!";
				link.p1.go = "joruba_p1";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2.Completed") && GetCharacterItem(pchar, "cannabis7") >= 15) {
				link.p2 = "I kept my end of the bargain. Here's your herb, Aruba.";
				link.p2.go = "joruba_p2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3.Completed") && ChickenGod_FindQuestShips()) {
				for (i = 0; i < questShipsNum; i++) {
					sTemp = "p3_" + (i + 1);
				
					chref = GetCharacter(questShips[i]);
					sld = GetRealShip(sti(chref.ship.type));
					link.(sTemp) = "Aruba, ahoy! " + GetStrSmallRegister(XI_ConvertString(sld.BaseName)) + " '" + chref.Ship.Name + "' is all yours!";
					link.(sTemp).go = "joruba_p3_ship_" + questShips[i];
					if (FindCompanionShips(SHIP_PINK) && sti(pchar.questTemp.ChickenGod.Tasks.Schyot) <= 1 && startHeroType != 4)
					{
						link.(sTemp) = "Aruba, ahoy! Pink '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_PinkOtkaz";
					}
					/*if (FindCompanionShips(SHIP_GALEON_SM))
					{
						link.(sTemp) = "Aruba, ahoy! Galeon '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_HolyMercy";
					}*/
				}
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_p4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Lady") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Completed")) {
				link.o2 = "I am bringing you a bride and troubles with the Spanish authorities, sir. The lady is taking a stroll outside, well protected by my men. I will not give her to you until you convince me of the nobility of your intentions.";
				link.o2.go = "joruba_o2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3.Completed") && GetCharacterFreeItem(pchar, "cirass4") >= 1) {
				link.o3 = "Here's your armor, Aruba. Make sure my reward will make up for it.";
				link.o3.go = "joruba_o3";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4.Completed") && GetPrisonerQty() >= 30) {
				link.o4 = "I have the prisoners you asked for.";
				link.o4.go = "joruba_o4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5.Completed") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.p2 = "I brought you your junk. Here, a hundred and thirteen stones, just like you asked for.";
				link.p2.go = "joruba_o5";
			}
			
			bOk = (PCharDublonsTotal() >= 25000) || (ChickenGod_HaveOfficers());
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.Completed") && bOk) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_o6";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.respec = "(Respec character's stats)";
				link.respec.go = "joruba_respec";
			}
			
			link.exit = "I am just passing by.";
			link.exit.go = "joruba_wait_1";
			
			NextDiag.TempNode = "joruba_wait";
		break;
		
		case "joruba_wait_1":
			dialog.text = "La prochaine fois alors.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "joruba_p1":
			dialog.text = "Pas mal, je vais faire bon usage de cet or. Tenez, un petit bijou autrefois possédé par un chef Taino très vertueux. Aide à porter des tas d'or. Cela l'a certainement aidé, héhé...";
			link.l1 = "Merci et j'espère que je ne le regretterai pas. Quel est le prochain marché ?";
			link.l1.go = "joruba_p1_1";
			link.l2 = "Attends une minute. Je t'ai donné un tas d'or et j'ai reçu un morceau d'argile en retour ? Eh bien, j'ai besoin d'un remboursement !";
			link.l2.go = "joruba_insult";
			
			RemoveDublonsFromPCharTotal(2000);
			pchar.questTemp.ChickenGod.Gold = 2000;
			
			pchar.questTemp.ChickenGod.Tasks.p1.Completed = true;
			GiveItem2Character(pchar, "talisman13");
			//Log_info("You received Taino Figurine");
			PlaySound("interface\important_item.wav");
		break;
		
		case "joruba_p1_1":
			dialog.text = "Eh? Aye, la prochaine affaire. Cet or devrait suffire pour l'instant, alors il est temps de considérer des marchandises plus spirituelles. Il faut que je me trouve un remède.";
			link.l1 = "Pourquoi, es-tu malade ?";
			link.l1.go = "joruba_p1_2";
		break;
		
		case "joruba_p1_2":
			dialog.text = "Mon ame l'est. Voyez-vous, les pretres evitent ma humble pyramide depuis cet incident avec l'Inquisition, alors nous devons compter sur des methodes plus traditionnelles. J'ai besoin, enfin, ma factoria a besoin de quinze plantes de magarosa pour rester operationnelle.";
			if (!ChickenGod_TalkedToAmelia()) {
				link.l1 = "Est-ce une herbe ?";
			} else {
				link.l1 = "Je sais ce que c'est, héhé.";
			}
			link.l1.go = "joruba_p1_3";
		break;
		
		case "joruba_p1_3":
			dialog.text = "Je serai honnête - c'est une herbe rare de grande valeur. Réfléchis bien si tu es vraiment prêt à passer des années à la récolter dans tout l'archipel ?";
			link.l1 = "Aucune promesse, mais je vous souhaite bonne santé et j'espère que ma récompense pour l'herbe en vaudra bien la peine.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveSecondTask");
		break;
		
		case "joruba_p2":
			dialog.text = "Très bien, je déclare officiellement que c'est mon jour de congé ! Un marché comme celui-ci vaut un véritable trésor. Regardez !\nCe machette a failli écraser la tête de cet imbécile de Kanek ! Par conséquent, elle m'est très chère et je vous demande humblement d'en prendre grand soin. Elle est ancienne, mais d'une fabrication exceptionnelle, on ne forge plus l'acier comme ça de nos jours.";
			link.l1 = "Kanek ? Qui est-ce ?";
			link.l1.go = "joruba_p2_1";
			
			TakeNItems(pchar, "cannabis7", -15);
			pchar.questTemp.ChickenGod.Tasks.p2.Completed = true;
			if (pchar.rank >= 21)
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 80.0;
			}
			else
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 60.0;
			}
			GiveItem2Character(pchar, "machete2");
			//Log_info("You received Machete Conquistador");
			PlaySound("interface\important_item.wav");
			SetAlchemyRecipeKnown("bullet_double");
			SetAlchemyRecipeKnown("grapeshot_double");
			ChickenGod_InitAmmo();
		break;
		
		case "joruba_p2_1":
			dialog.text = "Oh, vous deux vous rencontrerez. Maintenant, j'espère que vous n'êtes pas l'un de ces salauds pompeux qui méprisent le travail manuel? Si c'est le cas, vous êtes dans la merde, car la deuxième partie de la récompense est les plans des munitions à double charge.";
			if (pchar.HeroParam.HeroType == "HeroType_4") {
				link.l1 = "Oh, je les adore. Mais qu'ont-ils d'unique ? Une double charge de poudre n'est pas une nouveauté, donc je conclus que vous n'avez évidemment pas quitté votre pyramide depuis l'époque de cette machette de musée.";
			} else {
				link.l1 = "C'est tout ? Hé...";
			}
			link.l1.go = "joruba_p2_2";
		break;
		
		case "joruba_p2_2":
			dialog.text = "Ne fais pas l'imbécile et écoute ! N'importe quel idiot peut mettre deux piles de poudre à canon dans un tonneau et risquer de devenir aveugle, de se brûler le visage ou de se casser le nez. Je te propose un petit tour de magie : vérifie la qualité de la poudre avec soin, broie-la à la bonne consistance, mets-y une balle ou de la chevrotine, et assaisonne le tout avec un doublon haché. Le bang déchirera même une cuirasse en lambeaux !";
			link.l1 = "Tirer de l'argent, hein ? Tellement comme toi.";
			link.l1.go = "joruba_p2_3";
		break;
		
		case "joruba_p2_3":
			dialog.text = "Tu es insupportable ! Très bien, prends un mortier à main, et une douzaine de grenades pour aller avec. Si tu es si foutrement malin, tu obtiendras les plans des grenades par toi-même en un rien de temps !";
			link.l1 = "Je vous remercie, mon seigneur. Quelle est la suite ?";
			link.l1.go = "joruba_p2_4";
			
			//Log_info("You received Hand mortar");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "mortairgun");
			TakeNItems(pchar, "grenade", 10);
		break;
		
		case "joruba_p2_4":
			dialog.text = "Tu ne vas pas l'aimer. J'ai besoin d'un navire... non, j'ai besoin du navire. Tu sais, avec une histoire derriere elle.";
			link.l1 = "Pourquoi ? Tu n'es même pas capitaine.";
			link.l1.go = "joruba_p2_5";
		break;
		
		case "joruba_p2_5":
			dialog.text = "Aucune de tes affaires ! Mieux vaut te concentrer sur ta recompense, car je peux exiger de nettoyer cette pyramide de haut en bas pour cela, et tu me devrais encore !";
			link.l1 = "Tu n'es certainement pas un capitaine, sinon tu saurais qu'un navire a besoin d'un quai ou d'une baie pour accoster. Comment diable veux-tu que je fasse entrer un navire dans ta pyramide ?!";
			link.l1.go = "joruba_p2_6";
		break;
		
		case "joruba_p2_6":
			dialog.text = "Avez-vous remarqué un lac géant derrière ma pyramide par hasard? C'est ça. Amarre-toi simplement au bon navire dans l'escadron à proximité et mes hommes feront le reste. Maintenant, fous le camp d'ici, tu ralentis la file.";
			link.l1 = "Mais bien sûr. Adieu!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveThirdTask");
		break;
		
		case "joruba_p3":
			sld = GetCharacter(sti(companion));
			pchar.questTemp.ChickenGod.Tasks.p3.ship = sld.ship.type;
			RemoveCharacterCompanion(pchar, sld);
			AddPassenger(pchar, sld, false);
						
			npchar.ship.type = pchar.questTemp.ChickenGod.Tasks.p3.ship;
			SetCharacterShipLocation(npchar, "Temple");
						
			sld = GetRealShip(sti(pchar.questTemp.ChickenGod.Tasks.p3.ship));
					
			dialog.text = "Super! Je l'ai!";
			link.l1 = "Laisse tomber ton air insolent et donne-moi ma récompense !";
			link.l1.go = "joruba_p3_1";
			switch (sti(sld.BaseType)) {
				case SHIP_MAYFANG:
					dialog.text = "Et les deux autres ? Tu n'as pas pu les garder pour toi-même ? Hé-hé.";
				break;
				
				case SHIP_MIRAGE:
					dialog.text = "Et les deux autres ? Tu n'as pas pu les garder pour toi ? Hé hé.";
				break;
				
				case SHIP_VALCIRIA:
					dialog.text = "Et les deux autres ? Tu n'as pas pu les garder pour toi ? Heh-heh.";
				break;
				
				case SHIP_FRIGATE_L:
					dialog.text = "Merde, je suis impressionné que tu n'aies pas voulu la garder pour toi. Maintenant, c'est ce que j'appelle un navire avec une histoire ! Bon sang, William... J'aurais vraiment souhaité que tu rentres chez toi et fondes une grande banque comme tu en as toujours rêvé.";
				break;
				
				case SHIP_CORVETTE_QUEST:
					sTemp = "privateer";
					if (isMainCharacterPatented()) {
						sTemp = GetStrSmallRegister(GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)));
					}
					
					dialog.text = "Regardez-moi ça ! Vous êtes une honte pour votre commission, "+sTemp+" !";
				break;
				
				case SHIP_POLACRE_QUEST:
					dialog.text = "Charlie Prince a décidé de se débarrasser des preuves compromettantes dans ma vieille pyramide ? J'approuve !";
				break;
				
				case SHIP_ECLIATON:
					dialog.text = "Bonne chance pour expliquer à vos supérieurs la perte du vaisseau amiral, Amiral. Oh, pardonnez-moi, gouverneur-général.";
				break;
				
				case SHIP_CURSED_FDM:
					dialog.text = "Es-tu un imbécile superstitieux ou juste un imbécile ? Elle vaut une fortune ! Je ne suis pas sûr que ce soit un échange équitable, mais peu importe.";
				break;
				
				case SHIP_FDM:
					dialog.text = "Es-tu un imbécile superstitieux ou juste un imbécile? Elle vaut une fortune! Je ne suis pas sûr que ce soit un échange équitable, mais peu importe.";
				break;
				
				case SHIP_RENOVATED_FDM:
					dialog.text = "Serez-vous un imbécile superstitieux ou juste un imbécile? Elle vaut une fortune! Je ne suis pas sûr que ce soit un échange équitable, mais peu importe.";
				break;
				
				case SHIP_ELCASADOR:
					dialog.text = "Bonne décision ! J'adore les Castillans, tu sais. Peut-être que je la leur rendrai quand j'en aurai fini.";
				break;
				
				case SHIP_HIMERA:
					dialog.text = "Parbleu, tu n'as point de coeur, Capitaine. Ce navire pue la trahison. Je la prendrai.";
				break;
				
				case SHIP_PINK:
					if (startHeroType == 4)
					{
						dialog.text = "Oui, ce navire peut avoir une histoire... mais n'était-il pas trop facile à obtenir ? Ah, soit. Ton cas est spécial, ma chère, alors je vais l'accepter. Ça me rappelle au moins quelques souvenirs de ma jeunesse.";
						Achievment_Set("ach_CL_127");
					}
					else 
					{
						dialog.text = "Oui, ce navire peut avoir une histoire... mais n'était-ce pas trop facile à obtenir ? Oh, et puis zut. Bon, Cap, je vais laisser passer celle-ci, puisque tu as fait du bon boulot avec ces tâches de ma liste. Je le prends. Ça me rappelle au moins quelques souvenirs de ma jeunesse.";
					}
				break;
				
				case SHIP_GALEON_SM:
					dialog.text = "Et avez-vous vu le prêtre? Eh bien, vous le rencontrerez. Et vous feriez mieux de faire le plein de munitions à double charge pour pistolet. Si cela ne fonctionne pas - essayez un pieu en bois.";
				break;
				
				case SHIP_LADYBETH:
					dialog.text = "Et avez-vous vu le prêtre? Eh bien, vous le rencontrerez. Et vous feriez mieux de faire le plein de munitions à double charge pour pistolet. Si cela ne fonctionne pas - essayez un pieu en bois.";
				break;
			}
		break;
		
		/*case "joruba_p3_HolyMercy":
			dialog.text = "Et as-tu vu le pretre ?";
			link.l1 = "Quel pretre ?";
			link.l1.go = "joruba_p3_HolyMercy_2";
		break;
		
		case "joruba_p3_HolyMercy_2":
			dialog.text = "Eh bien, tu le rencontreras. Et tu ferais mieux de faire le plein de charges doubles pour pistolets. Si cela ne marche pas - essaie un pieu en bois.";
			link.l1 = "D'accord...";
			link.l1.go = "joruba_p3_1";
		break;*/
		
		case "joruba_p3_PinkOtkaz":
			dialog.text = "Oui, ce navire peut avoir une histoire... mais n'était-ce pas trop facile à obtenir ? Aucun moyen ! Tu as encore une tonne de travail inachevé sur la liste. Une fois que tu auras fait cela, nous discuterons à nouveau de ce sacrifice.";
			link.l1 = "... ";
			link.l1.go = "exit";
		break;
		
		case "joruba_p3_1":
			dialog.text = "Je te bénis, "+GetFullName(pchar)+". Que la mer te soit favorable. Maintenant, discutons de la prochaine transaction...";
			link.l1 = "Attends, quoi ? Même les idiots de bouseux ne tombent pas dans de telles balivernes à notre époque de raison ! Je n'ai pas mis un centime dans ta boîte de charité, je t'ai donné un navire de guerre à part entière !";
			link.l1.go = "joruba_insult";
			link.l2 = "Attends une seconde. Qu'est-ce que ta bénédiction signifie exactement pour moi ?";
			link.l2.go = "joruba_p3_2";
			
			pchar.questTemp.ChickenGod.Tasks.p3.Completed = true;
		break;
		
		case "joruba_p3_2":
			dialog.text = "Tout navire que vous commanderez sera désormais béni d'une coque renforcée, tandis que vos ennemis subiront le contraire. De plus, le temps en mer s'écoulera plus lentement pour vous. Et si cela ne suffit pas pour mettre ce trou à rats à genoux, vous feriez mieux d'aller voir votre papa et de demander un remboursement !";
			link.l1 = "Si ça ne fonctionne pas, je jure que je reviendrai ici ce soir et je brûlerai ta pyramide ! Parle-moi du prochain marché !";
			link.l1.go = "joruba_p3_3";
			notification("+10% hull defence", "None");
			notification("+10% damage to enemy ships hull", "None");
			notification("+5% speed on the Global Map", "None");
			PlaySound("Interface\new_level.wav");
		break;
		
		case "joruba_p3_3":
			dialog.text = "Vous commencez à y prendre goût, hein capitaine ? Malheureusement pour vous, moi aussi. Pourquoi croyez-vous que j'ai choisi cette pyramide pour mon bureau ?";
			link.l1 = "Probablement parce que la chasse aux sorcières est encore d'actualité ?";
			link.l1.go = "joruba_p3_4";
		break;
		
		case "joruba_p3_4":
			dialog.text = "Heh-heh, non, pas tout à fait. Je mène mes affaires ici parce que les meilleures affaires exigent du sang. Cette pyramide exige du sang. J'exige du sang. C'est comme ça que ça a été, c'est comme ça que ça va être.";
			link.l1 = "Ne pense même pas à ça, espèce de monstre. Je ne livrerai pas de victimes pour que tu les tues !";
			link.l1.go = "joruba_p3_5";
		break;
		
		case "joruba_p3_5":
			dialog.text = "Et combien en as-tu tué, hein? Attends, je vais même te dire le nombre exact : tu as personnellement tué "+(Statistic_AddValue(pchar,"Soudeurs",0)+Statistic_AddValue(pchar,"Citoyen_s",0)+Statistic_AddValue(pchar,"Guerrier_s",0)+Statistic_AddValue(pchar,"Soudard_g",0)+Statistic_AddValue(pchar,"Citoyen_g",0)+Statistic_AddValue(pchar,"Guerrier_g",0))+" gens ! Vous avez mis une montagne de cadavres sur l'autel de votre ambition et de votre soif de richesse ! ";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+" La dette de votre frère a déjà tué plus de gens qu'une guerre européenne moyenne ! ";
			}
			dialog.text = dialog.text+"Ne commence même pas à me faire la morale ici, surtout que je ne vais pas te juger. Le succès de certains sera toujours payé par les tragédies d'autres, et les dieux, oh, dieux, ils regarderont et prendront leur part !";
			link.l1 = "Je ne peux pas te donner une réponse tout de suite... Je dois sortir d'ici.";
			link.l1.go = "joruba_p3_6";
		break;
		
		case "joruba_p3_6":
			dialog.text = "Un besoin urgent de te vider la tête ? Très bien, mais écoute-moi d'abord. Je te donnerai pouvoir et contrôle total sur ton corps et ton esprit, si tu m'amènes un homme de grande valeur. Pas un figurant, pas une souris grise sans visage des rues ou un rat des cales puantes. Amène-moi un homme qui te suit et joue un rôle important dans ta tragicomédie.";
			link.l1 = "Un de mes officiers ? Tu ne peux pas tomber plus bas, Aruba ! Si cela s'ébruite...";
			link.l1.go = "joruba_p3_7";
		break;
		
		case "joruba_p3_7":
			dialog.text = "Je m'occuperai du secret comme je le fais toujours. Et avant que tu ne commences à te plaindre à nouveau, je te ferai savoir qu'il y a une autre voie.";
			link.l1 = "Qu'est-ce que cela est censé signifier ? Donc je n'ai pas à traîner mes propres gens à l'autel ?";
			link.l1.go = "joruba_p3_8";
		break;
		
		case "joruba_p3_8":
			dialog.text = "Non, mais vous n'aimerez pas l'alternative. Si vous ne voulez pas payer de votre sang, vous pouvez payer en or. Trois mille doublons et une conscience tranquille. L'argent peut faire cela et plus encore - j'adore ça !";
			link.l1 = "Adieu, Aruba. Je ne veux plus te parler.";
			link.l1.go = "joruba_p3_9";
		break;
		
		case "joruba_p3_9":
			dialog.text = "Tu sais où me trouver.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveFourthTask");
		break;
		
		case "joruba_p4":
			dialog.text = "Faisons cela vite avant que l'Inquisition espagnole ne débarque. Sang ou or ?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "L'or, c'est bien. Voici tes trois mille, bien que je ne puisse imaginer comment tu peux dépenser une telle somme énorme dans ce désert.";
				link.l1.go = "joruba_p4_1";
			}
			if (ChickenGod_HaveOfficers()) 
			{
				link.l2 = "Sang.";
				link.l2.go = "joruba_p4_other";
			}
			link.l3 = "Peu importe.";
			link.l3.go = "exit";
		break;
		
		case "joruba_p4_1":
			dialog.text = "... ";
			link.l1 = "Tu as fini? Parlons de ma récompense.";
			link.l1.go = "joruba_p4_reward_1";
			RemoveDublonsFromPCharTotal(3000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 3000;
		break;
		
		case "joruba_p4_other":
			dialog.text = "D'accord. Dis le nom.";
			
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Irons");
		break;
		
		case "joruba_p4_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand n'est pas un officier, mais un mercenaire impitoyable, donc choisis une autre victime.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "J'accepte votre tribut. Vous n'avez pas besoin de regarder.";
			link.l1 = "Non, je ne le fais pas. Je reviendrai pour ma récompense dans une heure.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_p4_reward";
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
		break;
		
		case "joruba_o6_money":
			dialog.text = "Excellent choix. Je déteste nettoyer l'autel de tout ce sang, donc l'or est préférable. Tiens, prends cette potion - un compliment d'un bon ami à moi.";
			link.l1 = "Le goût n'est pas mauvais du tout...";
			link.l1.go = "exit";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			RemoveDublonsFromPCharTotal(25000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 25000;
			
			if (sti(pchar.questTemp.ChickenGod.Gold) >= 30000) {
				Achievment_Set("ach_CL_87");
			}
			
			notification("+3 P.I.R.A.T.E.S. point", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_p4_reward":
			dialog.text = "";
			link.l1 = "Tu as fini ? Parlons de ma récompense.";
			link.l1.go = "joruba_p4_reward_1";
		break;
		
		case "joruba_p4_reward_1":
			dialog.text = "Parlez-moi à tout moment si vous souhaitez changer votre destin.";
			link.l1 = "Mais qu'est-ce que cela signifie exactement pour moi ?";
			link.l1.go = "joruba_p4_reward_2";
		break;
		
		case "joruba_p4_reward_2":
			dialog.text = "Maîtrise-toi! Essaie de temps en temps et tu l'adoreras. En attendant, laisse-moi te parler de la prochaine transaction. La plus importante.";
			link.l1 = "Je ne suis plus sûr que cela en vaille la peine !";
			link.l1.go = "joruba_p4_reward_3";
			link.l2 = "Allez, crache le morceau déjà.";
			link.l2.go = "joruba_p4_reward_3";
		break;
		
		case "joruba_p4_reward_3":
			dialog.text = "Vous avez l'opportunité de non seulement changer votre destin, mais de vous tenir aux côtés des génies et des dieux de notre temps. Oui, vous pouvez changer votre corps et votre esprit autant que vous le souhaitez maintenant, mais vous ne sauterez jamais au-dessus de votre tête, car une personne ordinaire ne peut pas exceller en tout. Ce que je propose, c'est que vous brisiez ces frontières.";
			link.l1 = "Qu'est-ce que ça va me coûter ? Plus de sang ? De l'or ?";
			link.l1.go = "joruba_p4_reward_4";
		break;
		
		case "joruba_p4_reward_4":
			dialog.text = "Aye. Soit tu m'apportes vingt-cinq mille doublons, soit un de tes compagnons. Une fois que nous aurons terminé, il n'y aura plus de transactions.";
			link.l1 = "Je vais y réfléchir.";
			link.l1.go = "joruba_p4_reward_5";
		break;
		
		case "joruba_p4_reward_5":
			dialog.text = "Tu sais où me trouver. Et n'hésite pas à me rendre visite quand tu veux changer ton destin.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			
			pchar.questTemp.ChickenGod.Tasks.p4.Completed = true;
			AddDialogExitQuestFunction("ChickenGod_GiveFifthTask");
		break;
		
		case "joruba_respec":
			dialog.text = "Comme vous voulez.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ChickenGod_Respec");
		break;
		
		case "joruba_o2":
			dialog.text = "Tout d'abord, c'est ma femme, pas une mariée. Ensuite, vous avez un problème avec les Castillans, pas moi. Et enfin, je l'ai déjà prise et j'ai renvoyé vos hommes. Et quant aux intentions honorables... Regardez-moi, ne suis-je pas le modèle d'un gentleman respectable ? Tlazolteotl, bénissez-le pour qu'il puisse lui aussi un jour connaître une vraie femme. Ou un homme.";
			link.l1 = "Va te faire foutre, Aruba !";
			link.l1.go = "exit";
			
			notification("+ 10 HP, + 10 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(10.0);
			pchar.questTemp.ChickenGod.Tasks.o2.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			sld = CharacterFromID(pchar.questTemp.ChickenGod.Tasks.o2.Lady);
			RemovePassenger(pchar, sld);
			ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto1");
			LAi_SetCitizenTypeNoGroup(sld);
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o3":
			dialog.text = "Pas mal, merci. Franchement, je n'en ai pas vraiment besoin, mais peut-être que je le porterai dans un salon ou quelque chose comme ça. Au nom d'Ishtar je te bénis. Maintenant va et pèche.";
			link.l1 = "Quelle étrange sensation...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o3.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			TakeItemFromCharacter(pchar, "cirass4");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o4":
			dialog.text = "Je les prendrai. Quoi ? J'ai besoin de cadavres dans mon équipage comme toi, sauf que contrairement à toi, je ne peux pas aller dans les tavernes recruter. Maintenant, Bast, bénis le héros pour ses futures aventures.";
			link.l1 = "Quelle étrange sensation...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o4.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
			
			AddDialogExitQuestFunction("ChickenGod_RemovePrisoners");
		break;
		
		case "joruba_o5":
			dialog.text = "Oui, nous devrons les disperser à nouveau, car les gens les perdent tout le temps, et nous avons besoin de clients. Freya, protège ce grand collectionneur de pierres.";
			link.l1 = "Quelle étrange sensation...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o5.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6":
			dialog.text = "Faisons cela rapidement avant que l'Inquisition espagnole ne se pointe. Sang ou or ?";
			
			if (PCharDublonsTotal() >= 25000)
			{
				link.money = "Here's your gold, you greedy bastard.";
				link.money.go = "joruba_o6_money";
			}
			
			if (ChickenGod_HaveOfficers())
			{
				link.blood = "Blood.";
				link.blood.go = "joruba_o6_blood";
			}
			link.l3 = "Oublie ça.";
			link.l3.go = "exit";
		break;
		
		case "joruba_o6_blood":
			dialog.text = "Dis le nom.";
			
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Irons");
			
			if (!CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Helena");
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Mary");
			}
		break;
		
		case "joruba_o6_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Mary" || pchar.questTemp.ChickenGod.Sacrifice == "Helena") {
				pchar.questTemp.ChickenGod.Tasks.o6.gf = true;
				sTemp = "future wife";
				sld = CharacterFromID(pchar.questTemp.ChickenGod.Sacrifice);
				if (sld.lastname == pchar.lastname) {
					sTemp = "current wife";
				}
				
				dialog.text = "C'est fort tentant, mais je ferai une exception juste cette fois - je n'accepterai pas ton sacrifice. Je ne dévoilerai pas cela à ton "+sTemp+", même si je devrais probablement. Souviens-toi que tu n'es rien sans elle. Maintenant, fiche le camp et ne me dérange pas aujourd'hui.";
				link.l1 = "";
				link.l1.go = "exit";
				
				AddDialogExitQuestFunction("ChickenGod_KickedFromTemple");
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand n'est pas un officier, mais un mercenaire impitoyable, alors choisis une autre victime.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "Ainsi soit-il.   Ici, prends cette potion - un compliment d'un bon ami à moi.";
			link.l1 = "Le goût n'est pas mauvais du tout...";
			link.l1.go = "joruba_o6_reward";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			notification("+3 P.I.R.A.T.E.S. points", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6_reward":
			dialog.text = "Jusqu'à la prochaine fois, capitaine.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.OnExitKick = true;
		break;
		
		case "joruba_final":
			dialog.text = "Ahoy-hoy! Enfin, tout est fini!";
			link.l1 = "Quoi ?";
			link.l1.go = "joruba_final_1";
		break;
		
		case "joruba_final_1":
			dialog.text = "Nous en avons terminé ici, Capitaine. Les affaires sont conclues, tout le monde est satisfait, et il n'y a pas de place pour les remboursements. Notre bureau ferme et se déplace.";
			link.l1 = "Attends un moment, Aruba. Je t'ai donné plein d'or, payé avec du sang, amené des femmes et des prisonniers dans ce repaire diabolique. Je peux gérer des événements surnaturels qui apparemment se produisent dans les Caraïbes. Mais nos 'transactions' avec toi défient toute logique. Explique-toi, je te prie.";
			link.l1.go = "joruba_final_2";
		break;
		
		case "joruba_final_2":
			dialog.text = "You know what? I'll tell you.\nI'm fed up with this world, and I want out. Every day, it's the same old routine: an ancient pyramid with a crumbling ceiling, those loathsome identical palm trees, and a never-ending stream of captains, each with their own ingenious ideas. Yes, I provide people with what they desire; it's my calling, and I take pride in it. But by the gods, how I detest all of you!";
			link.l1 = "Quelqu'un te retient ici ? La sortie est juste là, génie !";
			link.l1.go = "joruba_final_3";
		break;
		
		case "joruba_final_3":
			dialog.text = "Tu as absolument raison, personne ne me retient ici. Plus maintenant. Et c'est grâce à toi, mon ami.";
			link.l1 = "C'est un changement de coeur soudain. Je m'attendais à une histoire, mais tout ce que j'ai entendu jusqu'à présent, ce sont les divagations insignifiantes d'un vil petit dieu dans une pyramide poussiéreuse.";
			link.l1.go = "joruba_final_4";
		break;
		
		case "joruba_final_4":
			dialog.text = "Eh bien, tout le monde a besoin de se défouler de temps en temps, n'est-ce pas ? Je suis vraiment content que tu sois venu ici parce que, grâce à toi, je peux enfin quitter ce monde. De l'or, un équipage, de l'équipement et un navire, mon ami. Tu te souviens ? Ça te dit quelque chose ? C'est tout ce qu'il me fallait, et tu m'as tout fourni.";
			link.l1 = "De rien. Cependant, cela n'éclaircit toujours pas ta manière de parler si étrange et tes pouvoirs presque divins. Si tu es si tout-puissant, tu aurais pu invoquer ton propre navire, équipage et or depuis bien longtemps !";
			link.l1.go = "joruba_final_5";
		break;
		
		case "joruba_final_5":
			dialog.text = "Ce que j'ai fait, comme tu peux le voir. Chacun a ses propres méthodes.";
			link.l1 = "Mais comment diable ? Qui es-tu, exactement ?";
			link.l1.go = "joruba_final_6";
		break;
		
		case "joruba_final_6":
			dialog.text = "Eh bien... c'est ce que je fais, simplement. À bientôt dans le nouveau monde, "+GetPersonaName()+". Vraiment nouveau la prochaine fois, j'espère. Merci et adieu.";
			link.l1 = "Non, je ne veux plus jamais te revoir.";
			link.l1.go = "exit";
			link.l2 = "Alors à plus tard, Aruba... c'était intéressant.";
			link.l2.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_FinalGood");
		break;
		
		case "joruba_insult":
			dialog.text = "On dirait que tous les accords sont annulés. Il est temps de partir, capitaine.";
			link.l1 = "Il est temps pour toi de t'...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Insult");
		break;
		
		case "ChickenGod_TheInquisition_1":
			dialog.text = "Au nom de l'Inquisition espagnole, déclinez votre identité !";
			link.l1 = "Capitaine "+GetFullName(pchar)+". Et c'est vrai ce qu'ils disent, personne ne s'attend à l'Inquisition espagnole...";
			link.l1.go = "ChickenGod_TheInquisition_2";
		break;
		
		case "ChickenGod_TheInquisition_2":
			dialog.text = "... Cette plaisanterie est toujours pertinente, bien qu'elle ait conduit pas mal de chretiens innocents au bucher.";
			link.l1 = "...";
			link.l1.go = "ChickenGod_TheInquisition_3";
		break;
		
		case "ChickenGod_TheInquisition_3":
			dialog.text = "Je plaisante, Capitaine. Vous plaisantiez, et je plaisantais. Mon nom est Padre Emilio Bocanegra, et ces soldats du Christ sont mes gardes armés.";
			link.l1 = "Que puis-je faire pour vous, padre ?";
			link.l1.go = "ChickenGod_TheInquisition_4";
		break;
		
		case "ChickenGod_TheInquisition_4":
			dialog.text = "Sais-tu qui est un certain señor Aruba ?";
			link.l1 = "Oui, il a vécu dans cette vieille pyramide jusqu'à récemment.";
			link.l1.go = "ChickenGod_TheInquisition_5";
		break;
		
		case "ChickenGod_TheInquisition_5":
			dialog.text = "Que veux-tu dire par il vivait là ? Est-il possible de vivre là-bas ? Et pourquoi 'jusqu'à récemment' ?";
			link.l1 = "Ce señor vient de nous quitter sur un navire il y a quelques minutes.";
			link.l1.go = "ChickenGod_TheInquisition_6";
		break;
		
		case "ChickenGod_TheInquisition_6":
			dialog.text = "Comment le sais-tu ? La baie la plus proche est à plusieurs jours d'ici !";
			link.l1 = "Ce lac doit être plus grand qu'il n'en a l'air. Je n'ai pas d'autre explication pour vous, padre.";
			link.l1.go = "ChickenGod_TheInquisition_7";
		break;
		
		case "ChickenGod_TheInquisition_7":
			dialog.text = "Des choses étranges se passent dans les terres du vice-royaume.";
			link.l1 = "Ce sont des terres anglaises, padre.";
			link.l1.go = "ChickenGod_TheInquisition_8";
		break;
		
		case "ChickenGod_TheInquisition_8":
			dialog.text = "Laissez les hérétiques continuer à le penser. Nous récupérerons sûrement notre dû. Pardonnez-moi, mon fils, de poser tant de questions : Santiago m'a chargé de mener une enquête officielle sur cette pyramide... et son ancien occupant.";
			link.l1 = "Que s'est-il passé exactement, padre ?";
			link.l1.go = "ChickenGod_TheInquisition_9";
		break;
		
		case "ChickenGod_TheInquisition_9":
			dialog.text = "Puisque l'affaire sera probablement classée, je peux vous divertir avec une petite histoire.\nDes rumeurs de cet endroit circulent partout sur le Main depuis un certain temps. Nous avions reçu des rapports fiables indiquant qu'un certain nombre de personnes qui avaient laissé une marque significative dans l'histoire de la région avaient fait des visites régulières ici dans le passé.\nCependant, Santiago a commencé à prêter une réelle attention à ces rumeurs après l'incident de Panama.\nUn certain Indien avait fait grand bruit dans cette glorieuse cité et avait même prononcé plusieurs sermons d'une nature plutôt philosophique. Malheureusement, les habitants de Panama ont tiré des conclusions plutôt superficielles et se sont convaincus que cette pyramide contient d'innombrables trésors et exauce tous les souhaits.\nHérésie de la plus pure espèce, bien sûr... nous avons donc dû engager des poursuites contre certains résidents panaméens et cet Indien, Aguebana.";
			link.l1 = "Pourquoi les autorités panaméennes n'ont-elles pas sévi contre cela ?";
			link.l1.go = "ChickenGod_TheInquisition_10";
		break;
		
		case "ChickenGod_TheInquisition_10":
			dialog.text = "Comme ils le font toujours dans ces cas, ils ont prétendu être ensorcelés. Cette échappatoire légale aurait pu être fermée si nous avions interrogé Aguebana, mais il est mort soudainement.";
			link.l1 = "Comment est-il mort ?";
			link.l1.go = "ChickenGod_TheInquisition_11";
		break;
		
		case "ChickenGod_TheInquisition_11":
			dialog.text = "L'ivresse l'a tué. Cependant, sa mort n'a pas résolu nos problèmes, car l'hérésie avait pris racine dans tout l'archipel, et des centaines de personnes se lançaient dans une sorte de pèlerinage vers ce temple ancien.";
			link.l1 = "Je n'ai jamais vu des foules de gens ici auparavant... Alors quoi, vous alliez envahir Aruba et le juger ?";
			link.l1.go = "ChickenGod_TheInquisition_12";
		break;
		
		case "ChickenGod_TheInquisition_12":
			dialog.text = "Bien sûr que non, mon fils. Le jugement de l'Inquisition est sévère mais juste. Il doit y avoir une bonne raison pour un procès. Non, j'allais seulement recueillir le témoignage de senor Aruba et le remettre à Santiago.";
			link.l1 = "Eh bien, c'est malheureux pour vous.";
			link.l1.go = "ChickenGod_TheInquisition_13";
		break;
		
		case "ChickenGod_TheInquisition_13":
			dialog.text = "On ne sait jamais, mon fils. C'est la volonté de Dieu.";
			link.l1 = "Adieu, mon père.";
			link.l1.go = "ChickenGod_TheInquisition_14";
		break;
		
		case "ChickenGod_TheInquisition_14":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Temple", "reload2", false);
			LAi_SetActorType(npchar);
			//LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "ChickenGod_TheInquisitionLeave", -1);
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition = "ChickenGod_TheInquisitionLeave";
		break;
		
	}
} 

void ChickenGod_InitAmmo() {
	if(LoadSegment("items\initItems.c")) {
		InitGunExt(		 "pistol1", "t3", 	 "bullet_double",               "", 100.0, 300.0,  60.0, 260.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 20, 0);
		InitGunExt( 	 "pistol2", "t2", "grapeshot_double",               "",  60.0, 160.0,  20.0, 100.0,  0.0,  0.0, 0, 1, 1, 0, 1, 1, 40, 20, 0);
		InitGunExt(		 "pistol3", "t2", "grapeshot_double",               "",  80.0, 180.0,  30.0, 110.0,  0.0,  0.0, 0, 1, 1, 2, 1, 1, 40, 20, 0);
		InitGunExt(		 "pistol4", "t3",    "bullet_double",               "",  70.0, 270.0,  30.0, 230.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 35, 30, 0);
		InitGunExt(		 "pistol5", "t3", 	 "bullet_double",               "", 130.0, 330.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 2, 0, 0, 70, 30, 0);
		InitGunExt(		 "pistol6", "t3",    "bullet_double",               "", 100.0, 300.0,  60.0, 260.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 50, 20, 0);
		InitGunExt(		 "pistol8", "t4", "grapeshot_double",               "",  50.0, 100.0,  30.0,  60.0,  5.0,  5.0, 1, 1, 1, 0, 1, 1, 20, 20, 0);
		InitGunExt(		 "pistol9", "t3", 	 "bullet_double",               "", 100.0, 320.0,  80.0, 280.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 30, 0);
		InitGunExt(		 "pistol10", "t3",   "bullet_double",               "", 140.0, 280.0, 100.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 30, 0);
		InitGunExt(		 "pistol11", "t3",   "bullet_double",               "",  10.0, 700.0,  10.0, 620.0, 40.0, 30.0, 1, 1, 0, 0, 0, 0, 45,100, 0);
		InitGunExt(		 "pistol12", "t3",   "bullet_double",               "",  80.0, 290.0,  60.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 20, 0);
		InitGunExt(		 "pistol13", "t3",   "bullet_double",               "", 130.0, 300.0,  90.0, 260.0, 15.0,  0.0, 1, 1, 0, 0, 0, 0, 60, 30, 0);
		InitGunExt(		 "howdah",  "t3", "grapeshot_double",	            "",  50.0, 140.0,  30.0,  70.0,  5.0,  5.0, 1, 1, 1, 0, 0, 1, 50, 30, 0);
		InitGunExt(		 "pistol14", "t3",   "bullet_double",               "", 130.0, 330.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 4, 0, 0, 70, 34, 0); // Дуэльный двухзарядный пистоль cle 1.3
		
		UnloadSegment("items\initItems.c");
	}
	
	CGInitGrapeGunExt(	"pistol2",	"t2",		3,		50,		4.25,	5.0,	3);		// трёхствольный дробовик, двойной заряд
	CGInitGrapeGunExt(	"pistol3",	"t2",		4,		40,		6.0,	5.0,	4);		// тромбон, двойной заряд
	CGInitGrapeGunExt(	"pistol8",	"t4",		4,		110,	5.0,	3.0,	2);		// бландербуз, двойной заряд
	CGInitGrapeGunExt(	"howdah",	"t3",		3,		85,		3.0,	5.5,	2);		// гауда, двойной заряд
	CGInitGrapeGunExt(	"mushket3",	"t2",		3,		60,		6.0,	3.0,	3);		// аркебуза, картечь
	CGInitGrapeGunExt(	"mushket6",	"t3",		3,		90,		4.0,	3.5,	2);		// башенный мушкетон, картечь
}

void CGInitGrapeGunExt(string id, string sAttr, int basedmg, int shards, float width, float height, int dispersion)
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).basedmg = basedmg;
	gun.type.(sAttr).shards = shards;
	string sArea = "grapes_area_"+dispersion;
	gun.type.(sAttr).area = XI_ConvertString(sArea);
	gun.type.(sAttr).width = width;
	gun.type.(sAttr).height = height;
}

bool ChickenGod_FindQuestShips() {
	questShipsNum = 0;
	
	for(int i = 1; i < COMPANION_MAX; i++) {
		int index = GetCompanionIndex(pchar, i);
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		int shipIndex = sti(sld.ship.type);
		if (shipIndex == SHIP_NOTUSED) {
			continue;
		}
		
		ref realShip = GetRealShip(shipIndex);
		if (!CheckAttribute(realShip, "QuestShip")) {
			continue;
		}
		
		if (!GetRemovable(sld) || !GetShipRemovable(sld)) {
			continue;
		}
		
		if (CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip")) {
			if (sti(realShip.BaseType) == SHIP_MAYFANG || sti(realShip.BaseType) == SHIP_MIRAGE || sti(realShip.BaseType) == SHIP_VALCIRIA) {
				continue;
			}
		}
		
		questShips[questShipsNum] = sti(sld.index);
		questShipsNum++;
	}
	
	return (questShipsNum > 0);
}

void ChickenGod_AddOfficerLink(aref link, string prefix, string id) {
	if (GetCharacterIndex(id) < 0) {
		return;
	}
	
	if (!CheckPassengerInCharacter(pchar, id)) {
		return;
	}
	
	if (id == "Mary" && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) {
		return;
	}
	
	if (id == "Helena" && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
		return;
	}
	
	sld = CharacterFromID(id);
	
	if (!GetRemovable(sld)) {
		return;
	}
	
	link.(id) = GetFullName(sld) + ".";
	link.(id).go = prefix + id;
}

bool ChickenGod_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}

bool ChickenGod_HaveOfficers() {
	object fakelink;
	
	ChickenGod_AddOfficerLink(&fakelink, "", "Duran");
	ChickenGod_AddOfficerLink(&fakelink, "", "Baker");
	ChickenGod_AddOfficerLink(&fakelink, "", "Folke");
	ChickenGod_AddOfficerLink(&fakelink, "", "Avendel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tonzag");
	if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(&fakelink, "", "Longway");
	ChickenGod_AddOfficerLink(&fakelink, "", "Knippel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tichingitu");
	ChickenGod_AddOfficerLink(&fakelink, "", "Irons");
	
	if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
		ChickenGod_AddOfficerLink(&fakelink, "", "Helena");
		ChickenGod_AddOfficerLink(&fakelink, "", "Mary");
	}
	
	return (GetAttributesNum(&fakelink) > 0);
}
