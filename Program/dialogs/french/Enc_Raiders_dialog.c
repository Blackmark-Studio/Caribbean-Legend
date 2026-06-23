void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk, bOk1;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = int(npchar.EncQty);
	string sTemp = "Gang" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_Robbed":
			int iMoney = int(int(Pchar.money)/20)*10;
			AddMoneyToCharacter(pchar, -iMoney);
			AddSimpleRumour(LinkRandPhrase("Have you heard? The local robber " + GetFullName(npchar) + " found a new victim. One captain got scared and bought off. They say, he gave him " + FindRussianMoneyString(iMoney) + ", he-he... ", 
				"Yeah, captain " + GetFullName(pchar) + ", I already heard that you had to pay " + FindRussianMoneyString(iMoney) + ", to buy off a local bandit, " + GetFullName(npchar) + ". Now that's what I call bad luck! Ha-ha-ha!", 
				"Have you heard that the local bandits attacked one captain? He was totally robbed, he lost " + FindRussianMoneyString(iMoney) + "!"), int(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgain";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();			
		break;

		case "exit_fight":
			sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_RunFight":
			AddSimpleRumour(LinkRandPhrase(RandPhraseSimple("Have you heard? That bandit " + GetFullName(npchar) + " has finally found justice. He and his boys tried to rob "+ GetSexPhrase("some captain, but he turned out to be","some lady captain, but she turned out to be") +" a tough nut. So our dear robber shited his pants, ha-ha! That will be a lesson for him! Robbing the local farmers is one thing, but a brave captain is a different story!", 
				"Thank you, captain " + GetFullName(pchar) + ", for finally dealing with the gang of that bandit " + GetFullName(npchar) + ". Those rascals were really a pain in everyone's ass. We were scared to even send couriers to the farm for milk, they could have intercepted them and rob of all the money."), 
				"Have you heard, "+ GetSexPhrase("finally, some captain","finally, some lady captain") +" stopped that rascal " + GetFullName(npchar) + ", who was in 'charge' of the jungle, terrorizing all the local farmers. I do hope, it will stop them from their dirty deeds for long enough...", 
				"Have you heard that local bandit " + GetFullName(npchar) + " and his boys attempted to rob "+ GetSexPhrase("some captain","some lady captain") +"? Bah! Nothing of the sort! That captain turned out to be a tough nut. They say, he chased on these robbers over all the jungle like a shark chases flock of sardines. Thank God that there are still people who can stand up for us at time when the authorities do nothing, too busy with their dark deeds..."), int(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorAfraid(sld, Pchar, true);
				sld.Dialog.CurrentNode = "GetTheHellOut";
			}
			DialogExit();
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "GetLost";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}		
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase(LinkRandPhrase("Reste où tu es et lâche ton arme ! Ton argent ou ta vie !","Reste où tu es, "+GetSexPhrase("voyageur","demoiselle")+"!) Ne touche pas à ton arme et pas de mouvements brusques!","Reste où tu es, "+GetSexPhrase("voyageur","fillette")+"! C'est un péage. Si tu veux passer, tu dois payer le péage."),LinkRandPhrase("Hey, "+GetSexPhrase("camarade","demoiselle")+"! Pas si vite! Je veux voir combien votre bourse est lourde.","Pourriez-vous vous rapprocher, monami. Je veux entendre le tintement de l'or dans votre bourse.","Attends, "+GetSexPhrase("compagnon","jeune fille")+". Moi et mes gars avons parié sur combien d'or peut entrer dans votre bourse. Maintenant, nous devons le vérifier avant que les choses ne deviennent violentes."),"Ne te presse pas, "+GetSexPhrase("voyageur","chérie")+"! Allons avoir une conversation de coeur à coeur, le ferons-nous?");				
			Link.l1 = LinkRandPhrase(LinkRandPhrase("Pourquoi dis-tu ces absurdités?","Quoi de neuf?","De quoi parles-tu?"),"Que voulez-vous dire?","Qu'est-ce que vous insinuez exactement?");
			Link.l1.go = "Node_2";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("Des brigands?! Excellent, j'avais envie d'une bagarre!","Oh, vous êtes des brigands ! Vous cachez-vous de la justice, je suppose ? Eh bien, il semble que la justice vous ait juste rattrapé...","N'avez-vous pas été enseigné que déranger les étrangers avec vos absurdités est un signe de mauvaises manières? Il semble que je dois vous enseigner cette leçon..."),LinkRandPhrase("Oh, tu es un insolent, n'est-ce pas?! J'espère que ta lame est aussi tranchante que ta langue.","Je vois que vous êtes un maître de votre langue, j'espère que vous êtes aussi un maître de votre épée.","Oh, des bandits ! Tant de ton genre ont été pendus, mais tu ne peux toujours pas t'empêcher de marcher droit vers la potence."),LinkRandPhrase(RandPhraseSimple("Oh, brigands! Vous savez, je ne perds généralement pas de mots avec votre genre!","Quel impertinent! Sent comme un tas de merde fumante et ose encore s'adresser à un honnête "+GetSexPhrase("gars","fille")+"."),"Je ne perdrai pas de mots avec toi, mais tu trouveras mon pistolet très éloquent!","Encore des brigands ! Eh bien, je ne vous promets pas la potence, mais je peux certainement vous faire quelques trous dans le ventre !"));
			Link.l2.go = "CheckSkills";	
			Link.l3 = LinkRandPhrase("Et savez-vous qu'une patrouille me suit de près? Je n'ai qu'à leur donner un coup de sifflet et vous êtes fini.",RandPhraseSimple("Tu sais, je peux appeler la patrouille, n'as-tu pas peur de cela? Ils sont à proximité. Je suppose, à ta recherche.","Un groupe de patrouille a été récemment envoyé pour vous trouver, et ils seront ici à tout moment. Vous prenez un grand risque."),RandPhraseSimple("Je vous conseillerais de courir aussi vite que vous le pouvez. Une patrouille se dirige par ici, je viens de parler avec leur officier.","J'aurais volontiers continué notre conversation, mais j'ai peur que l'unité de patrouille que je viens de rencontrer, ne laisse pas notre connaissance se transformer en une amitié étroite."));
			Link.l3.go = "Node_3";
		break;
		
		case "Node_2":
			dialog.text = LinkRandPhrase(LinkRandPhrase("Ne jouez pas l'imbécile ! De l'argent comptant et peut-être alors je te laisserai partir !","N'avez-vous pas entendu parler de la solde de voyage? Si vous ne vous séparez pas de votre or, vous vous séparerez d'une tête!","Heh, cette aventure ordinaire te coûtera une bourse... si je ne me mets pas en colère."),RandPhraseSimple("C'est très simple. Tu nous donnes tout ton or et ensuite tu es libre de partir, ou tu restes ici, et nous prenons tout ton or, de toute façon. Mais je pense que ce dernier n'est pas ce que tu aimerais, he-he.","Ne faites pas semblant de ne pas comprendre! Donnez-moi votre bourse si vous ne voulez pas que je la prenne de votre cadavre!"),"Je vais expliquer, si tu es si lent d'esprit. Tu me donnes tout ton argent, si tu tiens à ta vie.");
			Link.l1 = "Sacrebleu, fripouille ! Je n'ai que "+int(int(Pchar.money)/20)*10+" pesos.";
			Link.l1.go = "CheckMoney";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("Tu veux mon argent? Viens le chercher, et je verrai combien tu vaux!","Comment osez-vous, rustre ! Je vais vous donner une leçon de bonnes manières !","Quelle assurance ! Eh bien, voyons comment tu te tiens face à un vrai "+GetSexPhrase("loup de mer","Louve des mers")+"!"),LinkRandPhrase("Tu devrais être fouetté pour une telle outrage!","Vous, canailles! Priez vos démons pour une place chaude en enfer!","Vous auriez dû être pendu il y a longtemps, oiseaux de la potence ! Eh bien, il semble que je vais devoir tacher mon sabre de votre sang !"),RandPhraseSimple("Et qu'est-ce qui te fait penser que je te donnerai mon argent?","Et n'as-tu pas remarqué que je suis bien armé et que je ne suis pas venu ici pour une simple promenade?"));
			Link.l2.go = "CheckSkills";	
		break;

		case "Node_3":
			bOk = int(pchar.reputation.nobility) < 11 || int(pchar.reputation.nobility) > 90;
			if(bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				dialog.text = RandPhraseSimple("Maudit! D'accord, tu peux partir. Mais ne pense même pas à faire du bruit pendant que tu es ici!","Cette fois, tu as eu de la chance, mais la prochaine fois tu nous devras le double ! N'oublie pas de nous le rappeler, he-he.");
				Link.l1 = RandPhraseSimple("Mais bien sûr.","Fuis déjà, pendant que tu le peux encore.");
				Link.l1.go = "Exit_NoFight";
			}
			else
			{
				bOk = int(pchar.reputation.nobility) < 51 && int(pchar.reputation.nobility) > 41; // Captain Beltrop, 23.01.21 - жесть!!! Надо было всего лишь убрать единичку!
				if(!bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
				{
					dialog.text = RandPhraseSimple("Nous te tuerons en silence, tu ne lâcheras même pas un couinement.","Sacrebleu! Nous devrons te trancher rapidement avant que tu ne déclenches l'alarme.");
					Link.l1 = "Eh bien, c'est ton enterrement. Je t'ai prévenu.";
					Link.l1.go = "Exit_Fight";
				}
				else
				{
					dialog.text = RandPhraseSimple("Et pourquoi devrais-je m'inquiéter de votre patrouille? Je les paie. Alors, donnez-moi votre bourse et arrêtez de jacasser.","Tu penses pouvoir me faire peur? Je suis moi-même 'la patrouille' pour ceux comme toi dans cette jungle. Personne encore n'est parti sans payer un droit de passage!");
					Link.l1 = "Sacré bleu, canaille ! Je n'ai que "+int(int(Pchar.money)/20)*10+" pesos.";
					Link.l1.go = "CheckMoney";	
					Link.l2 = RandPhraseSimple(LinkRandPhrase("He-h, je ne vais pas obéir aux ordres d'un gringalet comme toi.","Je vais te faire quelques nouveaux trous dans le crâne à cause de tant d'impudence ! Juste pour aérer un peu ton cerveau.","Une telle impudence ne restera pas impunie!"),"Tu n'aurais pas dû faire ça...");
					Link.l2.go = "CheckSkills";
				}
			}
		break;
		
		case "CheckSkills":
		    bool isStrong = (GetCharacterSkillToOld(Pchar, "FencingL") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingS") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingH") >= 7);
			bool z_ok = (isStrong) && (int(Pchar.Rank) >= 8) && (int(PChar.reputation.nobility) <= 30); // Captain Beltrop & mitrokosta, 23.01.21 проверяем на оружие (новый вариант)
			if (z_ok || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				Diag.TempNode = "GetLost";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Eh bien, ne soyez pas si excité, "+GetSexPhrase("camarade","fillette")+"! Je plaisantais seulement ! Vous pouvez continuer votre chemin !","D'accord, j'ai changé d'avis. Tu peux partir, si tu es si redoutable."),"Quoi, un "+GetSexPhrase("'capitaine galant'","'jeune fille militante'")+"? encore? D'accord, va en paix...","Détendez-vous, "+GetSexPhrase("camarade","jeune fille")+". Vous voyez, nous nous sommes trompés, "+GetSexPhrase("nous pensions que vous étiez un marchand","nous pensions que vous étiez un marchand")+". Vous pouvez partir.");
				Link.l1 = LinkRandPhrase(LinkRandPhrase("D'accord, jusqu'à ce que nous nous retrouvions!","Tu devrais arrêter de voler les gens, pendant que tu le peux encore.","D'accord, mais si je te revois jamais..."),RandPhraseSimple("La prochaine fois, fais attention à qui tu menaces, gueux.","Dieu merci que je suis de bonne humeur aujourd'hui."),RandPhraseSimple("Ce commerce criminel te tuera sûrement à la fin. Adieu.","C'est une décision sage. Eh bien, bonne chance!"));
				Link.l1.go = "Exit_NoFight";
				Link.l99 = LinkRandPhrase("Non, mon pote. Maintenant, je vais t'apprendre les bonnes manières!","Oh, tu as eu peur? Eh bien, on devrait répondre de ses actes, non?","Non! Maintenant, je ne me calmerai pas avant de t'écorcher vif!");
				Link.l99.go = "GetTheHellOut";
			}
			else 
			{
				dialog.text = LinkRandPhrase("Et tu aurais pu partir en paix! Maintenant, tu ne peux t'en prendre qu'à toi-même!","Tu n'aurais pas du commencer, espèce de coquin! Maintenant tu vas mourir comme un chien!","Ah bien! Je te déchirerai en morceaux! Découpe le foie et donne-le aux chiens!");
				Link.l1 = RandPhraseSimple("Je vais te faire ravaler tes paroles!","A qui tu menaces, raclure?!");
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "CheckMoney":
			if(int(int(Pchar.money)/20)*10 >= int(Pchar.rank)*100)
			{
				Diag.TempNode = "OnceAgain";
				dialog.text = LinkRandPhrase(RandPhraseSimple("D'accord! Donne-le moi et dégage!","Pas grand chose, mais toujours mieux que rien. C'est bon de traiter avec une personne intelligente! Tu es libre d'y aller."),"Maintenant, c'est une histoire différente ! Comme disait mon ami 'il est toujours bon d'écouter quelqu'un qui est intelligent, mais parler avec le fou est beaucoup mieux' ! He-he !","En échange de votre or, je vous donnerai un conseil, vous ne devriez pas vous promener dans la jungle, si vous êtes "+GetSexPhrase("un tel froussard. Bois ton rhum à la taverne, afin que toi et ta bourse restiez en sécurité!","une demoiselle. Être volé n'est pas le pire qui aurait pu vous arriver.")+".");
				Link.l1 = "Maudits soyez-vous !";
				Link.l1.go = "Exit_Robbed";				
			}
			else
			{
				dialog.text = "Je suppose que tu essaies de me tromper ! Ne t'inquiète pas, je vais te chatouiller avec mon couteau, et peut-être que quelque chose tombera.";
				Link.l1 = "Sacrebleu!";
				Link.l1.go = "Exit_Fight";				
			}				
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase("Vous encore? Rentrez chez vous à votre maman, avant que je ne me fâche avec vous!","Quoi? Tu ne m'as pas encore donné tout ton or? Ha-ha!","Regarde, "+GetSexPhrase("camarade","fillette")+", J'en ai marre de toi! Sors de ma vue pendant que tu es encore en vie!");
			Link.l1 = "Ouais, je suis déjà en train de partir.";
			Link.l1.go = "Exit";
			Link.l2 = "Je pensais que ce ne serait pas juste. Donc, j'ai décidé de remettre les choses à leur place...";
			Link.l2.go = "Exit_Fight";
		break;
				
		case "GetLost":
			Diag.TempNode = "GetLost";
			dialog.text = LinkRandPhrase("Quoi d'autre avez-vous besoin? Nous avons déjà convenu que vous partez!","Laisse-moi tranquille, "+GetSexPhrase("camarade","demoiselle")+". Je m'occupe de mes affaires, et tu as les tiennes, et nous ne devrions pas essayer de nous entendre !","Partez maintenant, "+GetSexPhrase("camarade","fillette")+"! Bon sang, es-tu vraiment prêt à donner tout ton argent?");
			Link.l1 = "Ouais, je pars déjà.";
			Link.l1.go = "Exit";
			Link.l2 = "Je me suis rappelé que tu n'as pas dit au revoir ! Alors disons un adieu correct...";
			Link.l2.go = "Exit_Fight";
		break;

		case "GetTheHellOut":
			Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase("Laissez-moi tranquille! Aidez-moi! Je veux vivre!","Aidez-moi ! "+GetSexPhrase("Il est un maniaque","Elle est une maniaque")+"! Ne me tuez pas !","Epargnez-moi ! Je ne suis qu'un humble brigand ! Je suis trop jeune pour mourir !");
			Link.l1 = LinkRandPhrase(LinkRandPhrase("Si tu étais resté à la maison, tu aurais survécu !","Tu aurais dû y penser avant !","Vous auriez dû savoir qu'il y a toujours des conséquences !"),"Tôt ou tard, cela devait arriver.","Trop tard pour se repentir, maintenant combats, racaille!");
			Link.l1.go = "exit_Fight";			
		break; 				
	}
}
