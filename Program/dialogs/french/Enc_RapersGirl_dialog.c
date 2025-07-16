void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd, iRnd1;
	string sTemp, sGems;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "exit":
			LAi_SetCitizenTypeNoGroup(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Begin_1":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Capitaine","Dame")+"! S'il vous plaît, soyez miséricordieux! Protégez-moi, je vous en supplie!","Au secours ! "+GetSexPhrase("Étranger","Jeune dame")+", sauvez-moi, je vous en supplie!");
			link.l1 = LinkRandPhrase("Qu'est-ce qui s'est passé?","Quoi de neuf?",RandPhraseSimple("Quel est le problème?","Qu'est-ce qui se passe?"));
			link.l1.go = "Begin_11";
		break;

		case "Begin_2":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Capitaine! Capitaine","Jeune fille! Jeune fille")+", veuillez patienter!","Attends, "+GetSexPhrase("Capitaine","jeune dame")+"! S'il vous plaît.");
			link.l1 = LinkRandPhrase("Que s'est-il passé ?","Quoi de neuf ?",RandPhraseSimple("Quel est le problème?","Qu'est-ce qui se passe?"));
			link.l1.go = "Begin_21";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = "Oh, m"+GetSexPhrase("soeur","iss")+"! S'il vous plaît, aidez une pauvre fille, je vous en supplie ! Ces gens veulent me faire quelque chose de terrible !";
			link.l1 = LinkRandPhrase("Qu'est-ce qui s'est passé ?","Quoi de neuf?",RandPhraseSimple("Quel est le problème?","Qu'est-ce qui se passe?"));
			link.l1.go = "Begin_31";
		break;
		
		case "Begin_11":
			dialog.text = RandPhraseSimple("Ces mécréants vont me violer ! Pour tout ce qui est bon, ne les laissez pas faire !","Au nom de Dieu, protège-moi de ces monstres ! Ils vont me déshonorer !");
			link.l1 = "Arrête de paniquer"+GetSexPhrase(", beauté","")+". Que s'est-il passé ici?";
			link.l1.go = "exit_1";
		break;

		case "Begin_21":
			dialog.text = RandPhraseSimple("Des violeurs me poursuivent !"+GetSexPhrase("Te lèverais-tu pour l'honneur d'une dame?","")+"","Capitaine, "+GetSexPhrase("sois un homme","tu es une femme, aussi")+"ne sauveriez-vous pas une fille de la disgrâce!");
			link.l1 = "Arrête de paniquer"+GetSexPhrase(", beauté","")+". Qu'est-ce qui s'est passé ici?";
			link.l1.go = "exit_1";
		break;
		
		case "Begin_31":
			dialog.text = "Ils me pourchassent! Les bandits! Dites-leur de me laisser tranquille!";
			link.l1 = "Arrête de paniquer"+GetSexPhrase(", beauté","")+". Qu'est-ce qui s'est passé ici?";
			link.l1.go = "exit_1";
		break;
		
		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = LinkRandPhrase("Au secours! Au secours! Ils me poursuivent! Sauvez-moi!","Aaah ! Au secours, "+GetSexPhrase("étranger","jeune dame")+"! Sauvez-moi de ces coquins!","Montrez de la pitié et protégez-moi de ces coquins ! S'il vous plaît !");
			Link.l1 = LinkRandPhrase("Qu'est-ce qui se passe?","Qu'est-ce qui se passe ?","Qu'est-ce qui s'est passé ?");
			Link.l1.go = "Node_2";			
		break;        

		case "Node_2":
			dialog.text = LinkRandPhrase("Ils... ils vont me violer ! Pour tout ce qui est bon, ne les laissez pas faire ! S'il vous plaît !","Ces bêtes... elles préparent quelque chose d'horrible... Protégez-moi d'elles, s'il vous plaît!","Au nom de notre Seigneur, sauvez-moi de ces bêtes lubriques ! Ils veulent me déshonorer !");
			Link.l1 = "Réglons tout cela, alors.";
			Link.l1.go = "exit_1";			
		break;

		case "ThanksForHelp":
			if(pchar.GenQuest.EncGirl == "Begin_11")
			{
				if(rand(1) == 0)
				{
					dialog.text = RandPhraseSimple("Merci, "+GetSexPhrase("Capitaine","jeune dame")+". J'étais si effrayé!","Merci de m'avoir sauvé ! Je vous suis tellement reconnaissant !");
					link.l1 = "D'accord, "+GetSexPhrase("beaute","cher")+", calmez-vous, c'est du passé.";
					link.l1.go = "Node_11";
				}
				else
				{
					dialog.text = "Oh, merci, "+GetSexPhrase("noble homme ! Vous êtes un vrai gentleman !","madame! Vous m'avez sauvé!")+"";
					link.l1 = "Je ne pouvais pas faire autrement.";
					link.l1.go = "Node_12";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_22")
			{
				if(rand(1) == 0)
				{
					dialog.text = "Oh, je vous remercie, "+GetSexPhrase("noble homme! Vous êtes un vrai gentleman!","étranger! Tu m'as sauvé!")+"";
					link.l1 = "Je ne pouvais pas faire autrement.";
					link.l1.go = "Node_12";	
				}
				else
				{
					dialog.text = "Que avez-vous fait? Pourquoi les avez-vous tués?! Maintenant, ils me chercheront! Mon Dieu, qu'ai-je fait pour mériter ça!";
					link.l1 = "Voilà de la gratitude !";
					link.l1.go = "Node_22";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_33")
			{
				dialog.text = "Qu'avez-vous fait, "+GetSexPhrase("capitaine","jeune dame")+"?! Pourquoi les avez-vous tués? Ils ont été envoyés par mon père... Oh mon Dieu, il va sûrement me tuer maintenant...";
				link.l1 = "Voilà des nouvelles ! Et à quoi pensais-tu en criant que tu étais poursuivi par des bandits ?!";
				link.l1.go = "Node_31";
			}
		break;
		
		case "Node_11":
			Diag.TempNode = "Node_1Next";
			addMoneyToCharacter(pchar, makeint((sti(pchar.rank))*25 + frand(2)*500));
			dialog.text = "J'ai de l'argent, s'il vous plaît, acceptez-le comme un gage de ma gratitude. Je vais maintenant le dire à tout le monde, "+GetSexPhrase("quel homme bon et noble vous êtes","quelle femme bonne et noble tu es")+".";
			link.l1 = "Certainement que tu le feras. Merci... Maintenant, rentre simplement chez toi.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "Node_12":
			dialog.text = "Je ne peux toujours pas me ressaisir. Pourriez-vous s'il vous plaît apporter "+GetSexPhrase("une dame","moi")+" à l'établissement de "+XI_ConvertString("Colonie"+pchar.GenQuest.EncGirl.city)+"? Vous savez, maintenant il me semble voir des violeurs derrière chaque buisson.";
			link.l1 = RandPhraseSimple("Ne t'inquiète pas tant, vraiment... D'accord, allons-y.","Tu es un tel lâche, n'est-ce pas? D'accord, je t'y emmènerai.");
			link.l1.go = "Node_121Next";
			link.l2 = "Je suis désolé, mon chéri, mais je n'ai tout simplement pas de temps, je suis trop occupé.";
			link.l2.go = "Node_3End";
		break;
						
		case "Node_22":
			dialog.text = "Je pensais que vous alliez simplement les effrayer ! Maintenant, vous devez m'emmener à la taverne dans la colonie de "+XI_ConvertString("Colonie"+pchar.GenQuest.EncGirl.city)+", je n'ai personne d'autre que vous à qui je pourrais demander de l'aide.";
			link.l1 = "Oh, zut! D'accord, allons-y. Juste ne reste pas en arrière.";
			link.l1.go = "Node_122Next";
			link.l2 = "Non, c'est tout, "+GetSexPhrase("beauté","cher")+"! J'en ai eu assez de surprises pour aujourd'hui. Cherchez quelqu'un d'autre pour vous aider.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_31":
			dialog.text = "Et qu'est-ce que je devais faire?! Mon père veut que je me marie avec le fils de l'usurier, ce laitier... juste parce que son papa a une tonne d'argent dans ses coffres! Mais j'aime un autre homme! Emmenez-moi chez lui, s'il vous plaît...";
			link.l1 = "Quel fardeau tu es! Bon, d'accord, allons-y. Je ne peux pas simplement te laisser ici, n'est-ce pas?.. Quel est le nom de ton élu, où dois-je t'emmener?";
			link.l1.go = "Node_32";
			link.l2 = "Non, c'est tout, "+GetSexPhrase("beauté","cher")+"! J'en ai eu assez de surprises pour aujourd'hui. Cherchez quelqu'un d'autre pour vous aider.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_32":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "Son nom est "+pchar.GenQuest.EncGirl.sLoverId+", c'est un nouveau venu. Pour l'instant, il séjourne à la colonie de "+XI_ConvertString("Colonie"+pchar.GenQuest.EncGirl.city)+", a essayé de trouver un travail là-bas, mais ce sont des temps difficiles. Tout le monde parle de crise... Et maintenant, de toute façon, je ne peux plus rentrer chez moi.";
			link.l1 = "Une crise? Ha... Pour un vrai pirate, une crise c'est quand il y a une caravane commerciale à l'horizon, mais pas de vent pour gonfler les voiles...";
			link.l1.go = "Node_12Next";
		break;
		
		case "Node_12Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "FindLover";
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_121Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_253";
			pchar.GenQuest.EncGirl = "FindCoins";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_122Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_12End":
			Diag.TempNode = "Node_12End";
			dialog.text = RandPhraseSimple("Tu sais, "+GetSexPhrase("capitaine","jeune dame")+"? J'étais tellement effrayé que mes jambes tremblent encore un peu.","Oh, tu sais, j'étais si effrayé. C'est formidable que Dieu t'ait envoyé sur mon chemin.");
			link.l1 = RandPhraseSimple("Dieu merci, tu es toujours en vie.","Ne le prends pas à coeur. C'est bien que cela se soit terminé ainsi, tu sais.");
			link.l1.go = "exit";
		break;
		
		case "Node_1Next":
			dialog.text = RandPhraseSimple("Merci, "+GetSexPhrase("capitaine","jeune dame")+", encore une fois. Vraiment, je vous suis tellement redevable.","Merci beaucoup, "+GetSexPhrase("capitaine","jeune dame")+". Je n'ai aucune idée de ce que je ferais sans votre aide.");
			link.l1 = RandPhraseSimple("Cela devrait être une leçon pour toi. Très bien, bonne chance...","La prochaine fois, tu devrais être plus prudent... Maintenant, rentre chez toi, j'ai des choses à faire.");
			link.l1.go = "Node_1End";
			link.l2 = "Comment pourrais-tu être si insouciant? Pourquoi es-tu allé dans la jungle seul?";
			link.l2.go = "Node_13";
		break;
		
		case "Node_1End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_3End":
			Diag.TempNode = "Node_3Final";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "Node_3Final":
			Diag.TempNode = "Node_3Final";
			dialog.text = RandPhraseSimple("Avez-vous changé d'avis?","Capitaine, c'est formidable que vous ayez changé d'avis !");
			link.l1 = RandPhraseSimple("Non-non, chérie, je passe.","N'ayez pas de faux espoirs...");
			link.l1.go = "exit";
		break;
		
		case "Node_13":
			if(pchar.GenQuest.EncGirl == "FindCoins") 
			{
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
				pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			}
			pchar.GenQuest.EncGirl = "Begin_11";
			switch(sti(pchar.GenQuest.EncGirl.variant))
			{
				case 0:
					if(rand(1) == 0)
					{
						dialog.text = "Vous allez probablement rire de moi, mais... je rassemblais un philtre d'amour... Une sorcière m'a dit qu'il y avait une racine qui peut aider dans les affaires d'amour.";
						link.l1 = "Oh mon dieu! Quoi "+GetSexPhrase("à quoi pensent ces femmes","pensiez-vous à")+"?! Apparemment, tu en as rassemblé beaucoup, il y avait un bon nombre de prétendants à tes trousses, j'ai eu du mal à tous les repousser. Ha-ha-ha-ha... Au revoir.";
						link.l1.go = "Node_1End";
					}
					else
					{
						dialog.text = "Je suis juste sorti pour une promenade pour ramasser quelques herbes et prendre un peu d'air frais. Apparemment, ce n'était pas le meilleur moment pour se promener.";
						link.l1 = "Quelle négligence?! Dieu merci, je suis arrivé à temps. Eh bien, bonne chance à toi.";
						link.l1.go = "Node_1End";
					}
				break;
				case 1:
					dialog.text = "Ma maîtresse a éparpillé les perles de son collier quelque part ici, lorsqu'elle était en promenade. En rentrant chez elle, elle m'a crié dessus et m'a ordonné de sortir et de les ramasser. Elle a dit, 'Ne montre même pas ton visage ici jusqu'à ce que tu les aies tous ramassés !', Et je ne connais même pas l'endroit exact. De plus, comment suis-je censé les trouver de toute façon dans cette herbe épaisse? Les perles sont si petites... Alors, je me promène ici sans avoir la moindre idée de ce que je devrais même faire...";
					link.l1 = "Et quel genre de collier était-ce ? Peut-être, il serait plus facile d'acheter simplement un nouveau plutôt que de se promener dans la jungle ? Combien de perles votre maîtresse a-t-elle perdues ?";
					link.l1.go = "Node_131";
				break;
				case 2:
					dialog.text = "Mon défunt père m'a laissé une carte, et ses compagnons voulaient me la prendre. Tant qu'il était en vie, ils tremblaient tous de peur devant lui, mais juste après l'avoir enterré, les temps troublés ont commencé. D'abord, ils ont tenté d'acheter cette carte de moi, mais j'ai refusé, et donc ils ont commencé à me intimider.";
					link.l1 = "Et pourquoi ne l'avez-vous pas simplement vendu ? Qu'est-ce qui est si spécial à propos de cette carte, que les gangs de pirates la cherchent ?";
					link.l1.go = "Node_132";
				break;
			}	
		break;
		
		case "Node_131":
			pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
			pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
			dialog.text = "Ce collier était composé de perles sélectionnées, on ne peut pas les acheter à bas prix. Il y avait "+sti(pchar.GenQuest.EncGirl.BigCoins)+" grandes perles et "+sti(pchar.GenQuest.EncGirl.SmallCoins)+" des plus petites. Si ces perles étaient trouvées, nous pourrions commander un autre collier comme celui-là.";
			link.l1 = "Sûrement que ce ne sera pas un travail facile... Eh bien, si ta maîtresse t'a donné un ordre, alors il n'y a pas grand-chose que tu peux faire. Essaye de trouver les perles. Bonne chance.";
			link.l1.go = "Node_131End";
			link.l2 = "C'est inutile. Ce serait plus facile de trouver une aiguille dans une botte de foin que les perles dans cette herbe épaisse. Sans parler du fait que tu ne connais même pas l'endroit où les perles ont été perdues...";
			link.l2.go = "Node_133";
		break;
		
		case "Node_131End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
			pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132":
			pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1); 
			dialog.text = "Mon père a marqué un endroit où il avait caché son trésor. Avez-vous entendu parler du célèbre pirate "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.mapOwner,NAME_VOC)+"?";
			link.l1 = "Non, jamais entendu parler de lui.";
			link.l1.go = "Node_132_1";
		break;
		
		case "Node_132_1":
			dialog.text = "Eh bien, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.mapOwner,NAME_NOM)+" était mon père. Tout le monde avait peur de lui, personne n'osait dire un mot. Maintenant, bien sûr, ils sont devenus effrontés. Quand j'ai refusé de leur vendre la carte, ils ont prétendu qu'ils devaient aussi avoir leur part du trésor. Je voulais cacher la carte, mais ils m'ont quand même retrouvé...";
			link.l1 = "Et pourquoi l'auriez-vous caché, en premier lieu ? Affrétez un navire et partez, revendiquez votre trésor. Votre père ne l'aurait pas caché pour rien.";
			link.l1.go = "Node_132_2";
		break;
		
		case "Node_132_2":
			dialog.text = "Plus facile à dire qu'à faire. Je n'ai pas d'argent pour affréter un navire, et... j'ai peur... Comment suis-je supposé déterrer tout ça, le transporter jusqu'au navire... Et où emmènerais-je le trésor ensuite ? N'importe qui fera de moi une proie facile en cours de route...";
			link.l1 = "C'est un bon point... D'accord, vas-y et cache ta carte, alors. N'oublie juste pas de bien la placer.";
			link.l1.go = "Node_132_2End";
			if(GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = "Hmm... C'est probablement vrai. D'autant plus, tu aurais dû le vendre.";
				link.l2.go = "Node_132_3";
			}
			link.l3 = "Avez-vous essayé de trouver un compagnon?";
			link.l3.go = "Node_132_8";	
		break;
		
		case "Node_132_2End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_3":
			dialog.text = "Cela me chagrine de perdre une telle opportunité... Mon père m'a parlé des trésors qu'il avait cachés là-bas. Personne ne me donnerait autant...";
			link.l1 = "Eh bien, ne le vendez pas trop bon marché. Et de toute façon, l'or ne vaut pas votre vie. Sans parler du fait que c'est le moyen le plus facile pour vous, vous collectez simplement votre argent et vous vous débarrassez de tous les ennuis...";
			link.l1.go = "Node_132_4";
		break;
		
		case "Node_132_4":
			pchar.GenQuest.EncGirl.mapPrice = 20000 + 500 * sti(pchar.rank);
			dialog.text = "Cela semble tentant... Et combien pouvez-vous m'offrir pour cela?";
			link.l1 = "Je ne pense pas que cela puisse valoir plus que "+sti(pchar.GenQuest.EncGirl.mapPrice)+" pesos.";
			link.l1.go = "Node_132_5";
		break;
		
		case "Node_132_5":
			if((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
			{
				dialog.text = "Heh, être une femme n'est pas facile... D'accord, je suis d'accord. Enfin, ce cauchemar sera terminé... Peut-être, c'est mieux que cette carte vous appartient,"+GetSexPhrase(" un noble gentilhomme","")+", qu'à ces coquins.";
				link.l1 = "Bien. Voici ton argent... essaie juste de ne pas tout dépenser d'un coup.";
				link.l1.go = "Node_132_6";
			}
			else
			{
				dialog.text = "Non, "+GetSexPhrase("capitaine","jeune dame")+". Je ne le vendrai pas. J'épouserai un bon homme, et ensuite nous réclamerons le trésor ensemble.";
				link.l1 = "Eh bien, c'est à toi de décider. Ton bout de papier ne vaut pas plus, de toute façon.";
				link.l1.go = "Node_132_2End";
			}	
		break;
		
		case "Node_132_6":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice))); 
			ref rMap = ItemsFromID("map_full"); // mitrokosta фикс пустой карты
			FillMapForTreasure(rMap);
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_8":
			dialog.text = "Et où les trouverai-je? Les jeunes ne sont pas fiables, et ils ne se soucient pas autant des trésors que, d'autres choses. Et je crains les plus âgés, ils me rappellent tous les amis de mon père. Si rusés et traîtres, on ne sait jamais à quoi s'attendre d'eux.";
			link.l1 = "Ha-ha-ha... D'accord, mais m'emporteras-tu avec toi?";
			link.l1.go = "Node_132_9";
		break;
		
		case "Node_132_9":
			dialog.text = "Vous? Et iriez-vous? Mais alors, vous devrez me ramener ici, à l'établissement de "+XI_ConvertString("Colonie"+pchar.GenQuest.EncGirl.city)+", d'accord?";
			link.l1 = "D'accord, je te donne ma parole. Montre-moi juste le chemin.";
			link.l1.go = "Node_132_10";
		break;
		
		case "Node_132_10":
			EncGirl_GenQuest_GetChestPlaceName();
			dialog.text = "Le trésor est caché dans la grotte sur "+XI_ConvertString(pchar.GenQuest.EncGirl.islandId+"Acc")+", nous devons accoster à "+XI_ConvertString(pchar.GenQuest.EncGirl.shoreId+"Gén")+", l'endroit où je me montrerai... Mais n'oublie pas, tu n'auras que la moitié!";
			link.l1 = "D'accord, je ne te tromperai pas, je te le promets. Suis-moi et ne reste pas en arrière.";
			link.l1.go = "Node_132_11";
		break;
		
		case "Node_132_11":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "GetChest";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_11_1":
			dialog.text = "Capitaine, maintenant nous devons trouver la grotte.";
			link.l1 = "D'accord, jetons un coup d'oeil maintenant.";
			link.l1.go = "exit";
			Diag.TempNode = "Node_132_11_2";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_11_2":
			Diag.TempNode = "Node_132_11_2";
			dialog.text = "Capitaine, nous devons trouver la grotte.";
			link.l1 = "D'accord, jetons un coup d'oeil maintenant.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_12":
			dialog.text = "Ici! Je l'ai trouvé! Tout comme mon père l'a dit! Un énorme tas de trésor! La moitié est à toi, comme convenu.";
			link.l1 = "Voyez? Ce n'était pas difficile, alors il n'y avait rien à craindre.";
			link.l1.go = "Node_132_13";
		break;
		
		case "Node_132_13":
			dialog.text = "Ha-ha-ha! Je suis riche maintenant! Prendras-tu ta part maintenant?";
			link.l1 = "Je suppose.";
			link.l1.go = "Node_132_15";
		break;
		
		case "Node_132_15":
			dialog.text = "Alors prenez-le et aidez-moi s'il vous plaît à transporter toutes ces choses au navire. Vous vous souvenez encore que vous avez promis de me ramener chez moi?";
			link.l1 = "Je n'ai pas oublié! Bien sûr, je vous emmènerai.";
			link.l1.go = "Node_132_16";
		break;
		
		case "Node_132_16":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.		
			LAi_LocationDisableMonstersGen(pchar.location, false);
			chrDisableReloadToLocation = false;
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 2+hrand(6));
			TakeNItems(pchar, "jewelry1", 30+hrand(15));
			TakeNItems(pchar, "jewelry2", 30+hrand(15));
			TakeNItems(pchar, "jewelry3", 30+hrand(15));
			TakeNItems(pchar, "jewelry4", 30+hrand(15));
			TakeNItems(pchar, "jewelry5", 30+rand(10));
			TakeNItems(pchar, "jewelry6", 10+rand(10));
			TakeNItems(pchar, "jewelry42", 20+rand(10));
			TakeNItems(pchar, "jewelry44", 30+rand(10));
			TakeNItems(pchar, "jewelry46", 50+rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));		
			pchar.GenQuest.EncGirl = "ChestGetted";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Node_132_17";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			pchar.quest.EncGirl_AddPassenger.win_condition.l1 = "location";// лесник на корабль девицу. 
			pchar.quest.EncGirl_AddPassenger.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.EncGirl_AddPassenger.function = "EncGirl_AddPassenger";
		break;
		
		case "Node_132_17":
			Diag.TempNode = "Node_132_17";
			dialog.text = "Être riche est tout simplement fantastique! Je me sens si différent maintenant."; 
			link.l1 = "Je suis content pour toi.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_18":
			dialog.text = "D'accord, capitaine. Mon voyage est terminé maintenant. Merci pour votre aide.";
			link.l1 = "Je vous en prie... Alors, que comptez-vous faire avec vos nouvelles richesses? Acheter une plantation avec des esclaves?";
			link.l1.go = "Node_132_19";
		break;
		
		case "Node_132_19":
			dialog.text = "Je ne sais pas, je n'ai pas encore décidé. Peut-être que je déménagerai en Europe...";
			link.l1 = "D'accord, eh bien ! Bonne chance à toi.";
			link.l1.go = "Node_132_20";
		break;
		
		case "Node_132_20":
			dialog.text = "Attendez... Ce bibelot faisait partie des trésors de mon père. Je n'en ai pas besoin, mais vous pourriez l'aimer. S'il vous plaît, acceptez-le comme ma gratitude personnelle pour ce que vous avez fait pour moi. C'est de ma part, ha-ha-ha !";
			link.l1 = "Wow, c'est vraiment un beau cadeau. Merci"+GetSexPhrase(", beaute","")+". Trouve-toi un beau mari, veux-tu...";
			link.l1.go = "Node_132_21";
		break;
		
		case "Node_132_21":
			chrDisableReloadToLocation = false;		
			RemovePassenger(pchar, npchar);			
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
            LAi_SetActorType(npchar); // отправил восвояси чтоб не стояла. лесник.
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
            pchar.quest.EncGirl_EnterToSea.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.	
            PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.						
		break;
		
		case "Node_133":
			dialog.text = "Mais que puis-je faire? Je ne peux pas ignorer les ordres de ma maîtresse, elle me écorchera vif.";
			link.l1 = "Attends-moi dans l'église de la colonie de "+XI_ConvertString("Colonie"+pchar.GenQuest.EncGirl.city)+", je vous apporterai les perles pour faire un nouveau collier.";
			link.l1.go = "Node_133_1";
			if(sti(pchar.money) >= 15000)
			{
				link.l2 = "Voici. Prenez ces 15000 pesos. Cela devrait être plus que suffisant pour sélectionner les perles pour le collier, ou pour en acheter un nouveau.";
				link.l2.go = "Node_135";
			}							
		break;
		
		case "Node_133_1":
			pchar.GenQuest.EncGirl = "GetCoins";
			pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
			pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";	
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");// лесник - девица убегает если ГГ сказал ждать в цервки
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);			
			Diag.TempNode = "Node_134"; 
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1"); 
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","")); 
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigCoins)); 
			AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallCoins)); 		
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_134":
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Capitaine","Jeune demoiselle")+", je suis si heureux de vous revoir! Avez-vous réussi à collecter des perles pour le collier?","Bonjour, capitaine ! Avez-vous apporté les perles ? Vous savez, ma maîtresse devient tellement nerveuse...");
			if (GetCharacterItem(pchar, "jewelry52") >= sti(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry53") >= sti(pchar.GenQuest.EncGirl.SmallCoins))
			{
				link.l1 = "Oui. Voici tes perles. Apporte-les à ta maîtresse et dis-lui d'être plus prudente la prochaine fois.";
				link.l1.go = "Node_134_1";
			}
			else
			{
				link.l1 = "Pas encore. Ce n'est pas si facile, tu sais... Mais je les apporterai, tu n'as qu'à attendre.";
				link.l1.go = "Node_134_2";
			}	
		break;
		
		case "Node_134_1":
			TakeNItems(pchar, "jewelry52", -sti(pchar.GenQuest.EncGirl.BigCoins)); 
			TakeNItems(pchar, "jewelry53", -sti(pchar.GenQuest.EncGirl.SmallCoins)); 
			pchar.quest.EncGirl_GetCoins.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = "Oh, "+GetSexPhrase("Capitaine","jeune dame")+", je suis si heureux de vous avoir rencontré! En signe de ma gratitude pour tout ce que vous avez fait pour moi, je veux vous donner ce bibelot et ces gemmes. J'espère vraiment que vous les trouverez utiles.";
			link.l1 = "Wow! Eh bien, merci aussi"+GetSexPhrase(", beauté","")+", je ne m'attendais pas... Au revoir, et soyez heureux.";
			link.l1.go = "Node_134_End";
		break;
		
		case "Node_134_2":
			dialog.text = "Oh, "+GetSexPhrase("capitaine","jeune demoiselle")+", je compte sur toi.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetStayType(NPChar);
		break;
		
		case "Node_134_End":
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			TakeNItems(pchar, "jewelry1", 15+hrand(8));
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_135":
			addMoneyToCharacter(pchar, -15000);
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			dialog.text = "Oh, "+GetSexPhrase("capitaine","jeune dame")+", vous m'avez aidé pour la deuxième fois aujourd'hui. Merci beaucoup. Je n'oublierai jamais votre gentillesse.";
			link.l1 = "Vous êtes le bienvenu. Dites 'bonjour' à votre maîtresse...";
			link.l1.go = "Node_135End";
		break;
		
		case "Node_135End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			NPChar.lifeDay = 0;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;	
		
		case "ThanksForSave":
			if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga") 
			{
				if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse")) 
				{
					iRnd = 2;
					pchar.GenQuest.EncGirl.BrothelCity = true;
				}	
				else
				{	
					iRnd = 1;
				}	
			}
			else
			{
				iRnd = 1;
			}
			switch(rand(iRnd))
			{
				case 0:
					dialog.text = RandPhraseSimple("Vous n'auriez pas dû leur donner de l'argent. Ils mentaient.","Ne les croyez pas. Ce sont des menteurs. Et vous n'auriez pas dû leur donner de l'argent.");
					link.l1 = "Aurais-je dû les tuer?";
					link.l1.go = "Node_200";
				break;
				case 1:
					dialog.text = "Oh, quel acte noble ! Je savais tout de suite que tu étais "+GetSexPhrase("un vrai gentilhomme","une dame noble")+"! S'il vous plaît, acceptez ma gratitude la plus sincère. J'espère que vous n'avez pas cru ce que ces fripouilles disaient?";
					link.l1 = "Cela n'a pas d'importance. Une fille et une bande de gueux dans la jungle, c'est tellement naturel...";
					link.l1.go = "Node_210";
					link.l2 = "De quoi parles-tu, "+GetSexPhrase("beaute","cher")+"? Comment pourrais-je ?";
					link.l2.go = "Node_211";
				break;
				case 2:
					dialog.text = "Merci, capitaine. Je suis désolé de vous avoir mêlé à cette affaire désagréable, mais je n'avais tout simplement pas d'autre choix.";
					link.l1 = "Eh bien, je vois que tu es aussi bien coincé. Comment en sommes-nous arrivés là?";
					link.l1.go = "Node_220";		
				break;
			}
		break;
		
		case "Node_200":
			if(rand(1) == 0)
			{
				dialog.text = "Peut-être... Ils ne me laisseront jamais tranquille maintenant.";
				link.l1 = "Oh, allez! Rentrez chez vous, vous n'avez plus rien à craindre maintenant.";
				link.l1.go = "Node_200End";
				link.l2 = "Wow! Pourquoi as-tu une telle aversion pour les hommes?";
				link.l2.go = "Node_201";
			}
			else
			{
				dialog.text = "Bien sûr que non! Mais ils ne me laisseront pas tranquille, de toute façon. Pourriez-vous m'amener à la colonie de "+XI_ConvertString("Colonie"+pchar.GenQuest.EncGirl.city)+", s'il vous plaît?";
				link.l1 = "Rentrez simplement chez vous, ils ne vous toucheront pas. Ils devraient se rendre à la taverne en ce moment pour gaspiller leur argent facile.";
				link.l1.go = "Node_200End";
				link.l2 = RandPhraseSimple("Ne t'inquiète pas tant, vraiment... D'accord, allons-y.","Tu es un tel lâche, n'est-ce pas? D'accord, je t'y amènerai..");
				link.l2.go = "Node_121Next";
			}
		break;
		
		case "Node_201":
			dialog.text = "Oh non, que dites-vous? Je connais trop bien ces vauriens. Ce sont d'anciens camarades de mon père. Ils essaient de localiser l'endroit où il avait caché ses trésors.";
			link.l1 = "Et quelle est l'histoire avec ton père?";
			link.l1.go = "Node_202";
		break;
		
		case "Node_202":
			dialog.text = "Il était autrefois le capitaine d'un navire pirate. Il est mort récemment... Ils ont tous été si courtois lors de l'enterrement, mais avec le temps, ils l'ont oublié, et peu après leur honneur et leur honnêteté aussi. C'est bien que je les ai remarqués. Dès qu'ils apprennent où sont les trésors, je suis fichu.";
			link.l1 = "C'est une triste histoire. Alors, comptez-vous continuer à vous cacher d'eux?";
			link.l1.go = "Node_203";
		break;
		
		case "Node_203":
			dialog.text = "Je ne peux pas garder des bijoux chez moi, je n'ai personne pour me protéger. Alors je vais la nuit dans la grotte, quand l'argent s'épuise...\nEmmenez-moi, s'il vous plaît, à la grotte, et je vous donnerai l'argent que vous leur avez donné... Je pense, les pirates ne risqueraient pas de nous suivre pendant que vous êtes avec moi.";
			link.l1 = "Désolé, ma chérie, mais j'ai d'autres plans. Tu récupéreras ton trésor une autre fois.";
			link.l1.go = "Node_200End";
			link.l2 = "D'accord, allons-y, si tu n'as pas peur de moi.";
			link.l2.go = "Node_204";
		break;
		
		case "Node_204":
			dialog.text = "Tu sais, pour une raison quelconque, je ne suis pas...";
			link.l1 = "Eh bien, c'est une bonne chose.";
			link.l1.go = "Node_205";
		break;
		
		case "Node_205":
			Diag.TempNode = "Node_206";
			EncGirl_GenerateChest(npchar);
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_206":
			Diag.TempNode = "Node_206";
			dialog.text = "Capitaine, vous avez promis de m'emmener à la grotte.";
			link.l1 = "Allons-y...";
			link.l1.go = "exit";
		break;
		
		case "Node_207":
			dialog.text = "D'accord, capitaine, j'ai pris autant que j'en avais besoin. Nous pouvons maintenant retourner.";
			link.l1 = "Vos copains ne sont pas dans le coin, je vois.";
			link.l1.go = "Node_208";
		break;
		
		case "Node_208":
			dialog.text = "Dieu merci. Je n'ai pas besoin de plus d'ennuis... Tiens, prends ces lingots... cela devrait suffire à couvrir tes dépenses. Va seul, je prendrai un chemin différent...";
			link.l1 = "D'accord, bonne chance à toi, si tu n'as pas peur.";
			link.l1.go = "Node_209";
		break;
		
		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			i = makeint(sti(pchar.GenQuest.EncGirl.price)/100.0);
			TakeNItems(pchar, "jewelry6", i);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;
		
		case "Node_200End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_210":
			dialog.text = "Hmm, "+GetSexPhrase("capitaine","jeune dame")+", Je n'aime pas ton ironie.";
			link.l1 = "Tu es prêt à partir, "+GetSexPhrase("beaute","cher")+". Et tu ferais mieux de te dépêcher vers la ville, avant qu'ils ne te pourchassent à nouveau.";
			link.l1.go = "Node_1End";
		break;
		
		case "Node_211":
			dialog.text = "J'étais tellement agité ! Pourriez-vous s'il vous plaît m'emmener à la taverne dans la colonie de "+XI_ConvertString("Colonie"+pchar.GenQuest.EncGirl.city)+"? Sinon, je crains qu'ils ne me poursuivent de nouveau.";
			link.l1 = "Peut-être, tu as raison. Allons-y...";
			link.l1.go = "Node_122Next";
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
		break;
		
		case "Node_220":
			dialog.text = "Oh, capitaine, c'est une longue histoire, et je ne suis pas sûr que vous la trouverez intéressante. Bien que... Je ne le ferai toujours pas sans votre aide maintenant. Pourriez-vous s'il vous plaît m'amener à la taverne dans la colonie de "+XI_ConvertString("Colonie"+pchar.GenQuest.EncGirl.city)+"? J'ai peur qu'ils ne me laissent simplement pas tranquille.";
			link.l1 = "Désolé, chéri, je n'ai pas de temps pour ça. J'ai des choses à faire.";
			link.l1.go = "Node_221";
			link.l2 = "Pourquoi es-tu si secret?";
			link.l2.go = "Node_222";
		break;
		
		case "Node_221":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_222":
			dialog.text = "Et comment ne puis-je pas être secret, si tout le monde essaie de profiter de mon malheur?";
			link.l1 = "D'accord, alors...";
			link.l1.go = "Node_223";
		break;
		
		case "Node_223":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();		
		break;
		
		case "Node_224":
			dialog.text = "Capitaine, vous m'avez promis de m'amener à la taverne dans la colonie de "+XI_ConvertString("Colonie"+pchar.GenQuest.EncGirl.city)+".";
			link.l1 = RandPhraseSimple("Je me souviens.","Ne t'inquiète pas, je te verrai là-bas.");
			link.l1.go = "exit";
		break;
		
		case "Node_225":
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15)
				{
					dialog.text = "Il y a trop de monde là-bas. Allons dans la chambre privée. J'ai quelque chose à te dire.";
					link.l1 = LinkRandPhrase("J'ai déjà fait trop pour vous, alors adieu à vous maintenant.","Tu ne devrais pas abuser de ma faveur. Au revoir, chéri.","Je n'ai pas besoin de vos histoires à partir de maintenant, vous pouvez tout comprendre par vous-même.");
					link.l1.go = "Node_226";
					link.l2 = "Hmm, d'accord. Je prendrai les clés du barman alors.";
					link.l2.go = "Node_227";
				}
				else
				{
					dialog.text = "Merci beaucoup pour votre aide, capitaine. Je ne l'oublierai pas.";
					link.l1 = "Oh, ne vous dérangez pas. Essayez juste d'être plus prudent à l'avenir.";
					link.l1.go = "Node_226_1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") // Addon-2016 Jason, французские миниквесты (ФМК)
				{
					dialog.text = "Merci beaucoup pour votre aide, capitaine. Je ne l'oublierai pas.";
					link.l1 = "Oh, ne vous dérangez pas. Essayez simplement d'être plus prudent à l'avenir.";
					link.l1.go = "Node_226_1";
				}
				else
				{
					dialog.text = "Il y a trop de monde là-bas. Allons dans la chambre privée. J'ai quelque chose à te dire.";
					link.l1 = LinkRandPhrase("J'ai déjà fait trop pour toi, alors adieu maintenant.","Tu ne devrais pas abuser de ma faveur. Au revoir, cherie.","Je n'ai plus besoin de tes histoires à partir de maintenant, tu peux tout comprendre par toi-même.");
					link.l1.go = "Node_226";
					link.l2 = "Hmm, d'accord. Je prendrai les clés du barman alors.";
					link.l2.go = "Node_227";
				}
			}
		break;
		
		case "Node_226":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_226_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_227":
			pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
			pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_228":
			if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar,"GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15) // душещипательная история о невинной девочке попавшей в бордель
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
				dialog.text = "Alors, tu veux toujours entendre mon histoire ?";
				link.l1 = "Hmm... Je suppose que c'est le moment pour moi de partir. Au revoir !";
				link.l1.go = "Node_232";
				link.l2 = "Eh bien, crache le morceau, alors.";
				link.l2.go = "Node_233";	
			}
			else						
			{
				dialog.text = "Oh, mon noble sauveur, enfin je peux te remercier de cette manière qu'une femme peut seulement exprimer\nQuand je t'ai vu dans la jungle, tout a changé en moi. J'ai oublié les violeurs et les feuilles de palmier acérées qui fouettaient mes joues. J'ai oublié où courir, pourquoi courir ... Je ne voyais que toi. Et je ne voulais que toi ... Et après ce que tu as fait pour moi...";
				link.l1 = "Wow! Quel caractère! Vos poursuivants savaient sûrement qui poursuivre...";
				link.l1.go = "Node_229"; // ГГ допрыгался - щас его попросту трахнут
				link.l2 = "Ecoute, beauté, je peux parfaitement comprendre, mais s'il te plaît, garde ton humeur pour toi.";
				link.l2.go = "Node_230"; // Послал в пешее эротическое путешествие
			}
		break;
		
		case "Node_229":
			dialog.text = "Viens à moi maintenant, mon héros...";
			link.l1 = "Oh, ma cherie...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "EncGirl_facking";
			DoQuestCheckDelay("PlaySex_1", 3.0);
		break;
		
		case "Node_230":
			dialog.text = "Oh! Comment... Comment osez-vous?! Quel salaud! Une fille vous a remercié de tout son cœur et son âme, et vous...";
			link.l1 = "Eh bien, si tu ne draguais pas autant et que tu ne faisais pas un blocage sur le premier homme que tu rencontres, tu aurais sûrement eu moins d'ennuis. Je ne sauve plus ces dragueuses dans la jungle...";
			link.l1.go = "Node_231";
		break;
		
		case "Node_231":
			dialog.text = "Je n'ai jamais entendu de tels mots de personne avant! Et je ne les pardonnerai pas! Tu te souviendras encore de moi!";
			link.l1 = "Allez déjà, d'accord ? Et essayez de vous rafraîchir un peu, à moins que vous ne vouliez être sauvé encore une fois ...";
			link.l1.go = "Node_231_1";
		break;
		
		case "Node_231_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","", -1.0);
			npchar.lifeDay = 0;
			DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0);
			DialogExit();		
		break;
		
		case "Node_232":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			dialog.text = "Ma famille vit dans la colonie de "+XI_ConvertString("Colonie"+pchar.GenQuest.EncGirl.Parents_City)+". Je suis arrivée ici par hasard, sur le navire, sur lequel mon fiancé m'emmenait chez ses parents, mais il a été capturé par des pirates. Le navire a été emporté, et les passagers ont été débarqués à la baie non loin d'ici. Mon fiancé a été tué lors de l'abordage du navire, et j'étais gravement malade lors de la transition à travers la jungle\nLa maîtresse du bordel local m'a soignée, et quand je me suis remise sur pied, elle a exigé de travailler de l'argent dépensé pour le traitement. J'étais une prostituée mais je ne plaisais pas à la Madame, et alors la maîtresse m'a vendue à des bandits pour gagner au moins un peu d'argent. La suite de l'histoire, vous la connaissez déjà.";
			link.l1 = "Alors abandonne et rentre chez toi! Pourquoi te laisses-tu traiter comme un esclave?!";
			link.l1.go = "Node_234";
		break;
		
		case "Node_234":
			dialog.text = "Je ne peux pas ! Toutes mes affaires : vêtements convenables, argent, documents... Ils sont tous dans le bordel dans mon sac de voyage. Je l'ai caché dans la salle de rendez-vous. Et tant que je suis habillé comme ça, tous les marins du port me courront après. Et qui me prendra à bord sans documents ou argent ? Et maintenant je ne peux même pas montrer mon visage en ville, ou je serai jeté derrière les barreaux...";
			link.l1 = "Ça ne devrait pas être un problème. Allons-y. Je te ramènerai chez toi moi-même.";
			link.l1.go = "Node_235";
			link.l2 = "Attendez ici. Je vais vous apporter votre sac de voyage.";
			link.l2.go = "Node_236";													
			if(sti(pchar.money) >= 5000) 
			{
				link.l3 = "Qui se soucie de vos papiers? Combien d'argent avez-vous besoin pour rentrer chez vous?";
				link.l3.go = "Node_237";							
			}			
		break;
		
		case "Node_235":
			dialog.text = "Oh, merci, capitaine... Mais... vous savez, je n'ai rien pour vous payer.";
			link.l1 = "De quel paiement parlez-vous? Allons-y avant qu'ils ne soient trouvés...";
			link.l1.go = "Node_240";				
		break;
		
		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit(); 		
		break;
		
		case "Node_236":
			dialog.text = "Oh, capitaine, vous savez, je n'oserais jamais demander...";
			link.l1 = "N'ayez pas peur. Je serai de retour bientôt.";
			link.l1.go = "Node_239";				
		break;		
		
		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);

			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";
						
			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
		
		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = "Oh, je commençais déjà à m'inquiéter que quelque chose aurait pu vous arriver.";
			if(CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = "Que pourrait-il se passer ? Tiens, prends tes affaires.";
				link.l1.go = "Node_241";
			}	
			else
			{
				link.l1 = "Ecoute, je n'ai rien trouvé là-bas. Es-tu sûr que tu as laissé ton sac de voyage dans la salle de rencontre ?";
				link.l1.go = "Node_242";			
			}	
		break;
		
		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = "Merci, "+GetSexPhrase("noble capitaine","jeune fille noble")+". Je n'oublierai jamais ce que vous avez fait pour moi. Je n'ai pas grand-chose, mais veuillez accepter cet amulette. Peut-être, c'était ce bibelot qui a sauvé ma vie pendant l'attaque des pirates.";
			link.l1 = "Merci et bon voyage! Adieu maintenant...";
			link.l1.go = "Node_243";
		break;
		
		case "Node_242":
			dialog.text = "Ont-ils vraiment trouvé mon sac?";
			if(sti(pchar.money) >= 5000)
			{
				link.l1 = "Combien d'argent avez-vous besoin pour rentrer chez vous?";
				link.l1.go = "Node_237";
			}
			link.l2 = "Peut-être l'ont-ils fait. Quoi qu'il en soit, nos routes se séparent ici maintenant. Adieu!";
			link.l2.go = "Node_244";
		break;
		
		case "Node_243":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_244":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_245":
			dialog.text = "Merci, capitaine. Vous savez, c'est difficile à croire que je suis enfin chez moi. S'il vous plaît, venez avec moi, je vais vous présenter à mes parents.";
			link.l1 = "Écoutez, "+GetSexPhrase("beauté","chéri")+", Je n'ai vraiment pas le temps pour ça. Peut-être une autre fois?";
			link.l1.go = "Node_246";
		break;
		
		case "Node_246":
			dialog.text = "Quel dommage... Eh bien, adieu alors, et que le Seigneur veille sur vous. Je n'ai rien pour vous rembourser, mais veuillez accepter cet amulette.";
			link.l1 = "Merci! Rentre chez toi maintenant, fais plaisir à tes parents!";
			link.l1.go = "Node_247";
		break;
		
		case "Node_247":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);		
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl","sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "Node_248":
		break;
		
		case "Node_237":
			dialog.text = "Eh bien, je ne sais pas... Peut-être, je devrai attendre un passage. Mais je ne peux pas te demander de l'argent.";
			if(makeint(pchar.money)>=5000)
			{
				link.l1 = "Je vois. Très bien, prenez 5000 pesos. Cela devrait suffire.";
				link.l1.go = "Node_237_1";
			}
			if(makeint(pchar.money)>=25000)
			{
				link.l2 = "Je vois. D'accord, prends 25000 pesos et rentre chez toi.";
				link.l2.go = "Node_237_2";
			}
			if(makeint(pchar.money)>=35000)
			{
				link.l3 = "Je vois. Très bien, prenez 35000 pesos. Cela devrait suffire pour acheter la meilleure cabine sur le navire.";
				link.l3.go = "Node_237_3";
			}
		break;
		
		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			dialog.text = "Merci, "+GetSexPhrase("capitaine noble","jeune fille noble")+". Je n'oublierai jamais ce que vous avez fait pour moi.";
			link.l1 = "Bon voyage, alors. Adieu...";
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;
		
		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			dialog.text = "Merci, "+GetSexPhrase("capitaine noble","jeune fille noble")+". Je n'oublierai jamais ce que tu as fait pour moi.";
			link.l1 = "Bon voyage, alors. Adieu...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			dialog.text = "Merci, "+GetSexPhrase("noble capitaine","jeune fille noble")+". Je n'oublierai jamais ce que tu as fait pour moi.";
			link.l1 = "Bon voyage, alors. Au revoir...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_238":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			if(pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney") 
			{
				AddSimpleRumour(RandPhraseSimple("Have you heard? A whore was trying to sneak on board of a ship without documents, but she was caught and taken back to the brothel. They say she owed the madam quite a sum.",  
				"Have you heard? A whore without documents was caught at the port. They say she had cleaned out madam's coffers before attempting to flee from the brothel. I say, that source of filth and thievery must have been closed off long ago. Our kids are even seeing this and what can they learn from such an example?"), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_250":
			dialog.text = "Ne ruinez pas ma vie, capitaine! Mon père veut que je me marie avec le fils de l'usurier, ce laitier immonde... juste parce que son papa a une merde d'argent dans ses coffres! Eh bien, je préférerais rester dans la jungle pour être dévorée par des bêtes sauvages plutôt que de prendre une peine de vie avec lui!";
			link.l1 = "Quel est le problème avec votre mariage, "+GetSexPhrase("beauté","mon cher")+"? Retiens celui qui cherche à t'épouser, et sois heureuse. Après un certain temps, tu serais heureuse d'épouser ce mou, mais il pourrait être trop tard...";
			link.l1.go = "Node_251";
		break;
		
		case "Node_251":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "Non! Non, capitaine, j'aime "+pchar.GenQuest.EncGirl.sLoverId+" et je n'épouserai aucun autre homme ! Et mon père ne veut rien entendre ! Il dit que "+XI_ConvertString("Colonie"+pchar.GenQuest.EncGirl.city)+" n'est qu'un visiteur ici, alors il ne trouvera jamais de travail ici, et il est destiné à mourir dans la pauvreté, et moi avec lui! Et j'irais avec lui jusqu'au bout du monde, juste pour être à ses côtés! Emmenez-moi à lui, je vous en supplie!";
			link.l1 = "D'accord, allons-y. Je suppose que je vais trouver quoi faire de toi...";
			link.l1.go = "Node_252";
		break;
		
		case "Node_252":
			Diag.TempNode = "Node_253";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl","sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId); 
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_253":
			Diag.TempNode = "Node_253";
			dialog.text = "Capitaine, vous avez promis de m'amener à l'établissement de "+XI_ConvertString("Colonie"+pchar.GenQuest.EncGirl.city)+".";
			link.l1 = RandPhraseSimple("Je me souviens.","Ne t'inquiète pas, je t'y emmènerai.");
			link.l1.go = "exit";			
		break;
		
		case "Node_260":
			chrDisableReloadToLocation = false;
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Merci, "+GetSexPhrase("capitaine","jeune dame")+", encore une fois. Vraiment, je suis tellement redevable envers vous.","Merci beaucoup, "+GetSexPhrase("capitaine","jeune dame")+". Je n'ai aucune idée de ce que je ferais sans votre aide.");
				link.l1 = RandPhraseSimple("Cela devrait être une leçon pour toi. Très bien, bonne chance...","La prochaine fois, tu devrais être plus prudent... Maintenant, rentre chez toi, j'ai des choses à faire.");
				link.l1.go = "Node_260End";
				link.l2 = "Comment pourrais-tu être si insouciant ? Pourquoi es-tu allé dans la jungle tout seul ?";
				link.l2.go = "Node_13";
			}
			else
			{
				dialog.text = "Oh, "+GetSexPhrase("capitaine","jeune dame")+", Je n'ai vraiment aucune idée de comment vous remercier.";
				link.l1 = "C'était rien. Toujours heureux d'aider...";
				link.l1.go = "Node_261";
			}
		break;
		
		case "Node_260End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");			
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_261":
			dialog.text = "Pouvez-vous m'emmener à la taverne ? J'ai besoin d'attendre ma tante et de me reposer, cette 'aventure' m'a épuisé toute mon énergie...";
			link.l1 = "Non, "+GetSexPhrase("beauté","mon cher")+", c'est certainement assez pour moi. J'ai beaucoup à faire.";
			link.l1.go = "Node_262";
			link.l2 = ""+GetSexPhrase("Oh, les femmes ! Y a-t-il quelque chose qu'elles peuvent faire sans l'aide d'un homme ?","Pourquoi es-tu si impuissant?")+"Allons-y...";
			link.l2.go = "Node_263";
		break;
		
		case "Node_262":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_263":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";					
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
				
		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if(makeint(Pchar.reputation.nobility) >= 80)
			{
				dialog.text = "J'ai de l'argent... S'il vous plaît, acceptez-le comme un gage de ma gratitude!";
				Link.l1 = "Merci. Essayez d'être plus prudent la prochaine fois.";
				Link.l1.go = "exit";
			}
			else 
			{
				if(hrand(1) == 0)
				{
					dialog.text = "Je dirai à tout le monde que tu m'as sauvé! Que tout le monde le sache, "+GetSexPhrase("quel homme brave et courageux vous êtes","quelle dame courageuse et brave vous êtes")+"!";
					Link.l1 = "Merci. Et maintenant, vous devriez rentrer chez vous.";
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank)*100);
					dialog.text = "J'ai un peu d'argent... S'il vous plaît, acceptez-le comme un signe de ma gratitude !";
					Link.l1 = "Merci. Essayez d'être plus prudent la prochaine fois.";
					Link.l1.go = "exit";
				}
			}
		break;

		case "ThanksAgain":
            Diag.TempNode = "ThanksAgain";
            dialog.text = "Je dirai à tout le monde que tu m'as sauvé ! Que tout le monde le sache, "+GetSexPhrase("quel homme brave et courageux vous êtes","quelle dame brave et courageuse vous êtes")+"!";
			Link.l1 = "Merci. Et maintenant, tu devrais rentrer chez toi.";
			Link.l1.go = "exit";
		break;
	}
}
