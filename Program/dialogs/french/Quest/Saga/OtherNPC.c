// диалог прочих НПС по квесту Саги
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Tu veux quelque chose ?";
			link.l1 = "Non, rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//---------------------------------------------Джимми в доме в Марун-Тауне------------------------------------
		case "Jimmy":
			dialog.text = "Que veux-tu ? Ne vois-tu pas que je suis en deuil ! Dégage avant que je te botte en bas des escaliers !";
			link.l1 = "Eh bien, achète-toi une maison plus grande avec des escaliers pour cela. Ensuite, nous parlerons de faire dégringoler les gens dans les escaliers, héros...";
			link.l1.go = "Jimmy_1_1";
			link.l2 = "Pourquoi es-tu si contrarié, Jimmy ? Pas de rhum pour moi pour le reste de ma fichue vie si ça n'a pas un rapport avec une belle femme ! Seule une femme pourrait faire qu'un vieux loup de mer comme toi menace ses vieux amis...";
			link.l2.go = "Jimmy_1_2";
		break;
		
		case "Jimmy_1_1":
			dialog.text = "Je déteste les gens pointilleux comme toi ! Vous obtenez toujours les meilleurs morceaux du gâteau. Ils ne m'ont pas laissé tuer un parvenu alors je vais passer ma colère sur toi !";
			link.l1 = "... ";
			link.l1.go = "Jimmy_fight";
		break;
		
		case "Jimmy_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_KillJimmy");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Jimmy_1_2":
			dialog.text = "Ouai ?! Te connais-je ? Je ne me souviens pas de toi, nom de dieu...";
			link.l1 = "C'est moi, "+pchar.name+"! Nous avons passé un bon moment à Blueweld après que tu aies failli éventrer ce gredin insolent en manteau. Comment s'appelait-il déjà ? J'ai oublié... Quoi qu'il en soit, je me moquerai des canons de sa corvette si jamais je le croise en mer !";
			link.l1.go = "Jimmy_2";
		break;
		
		case "Jimmy_2":
			dialog.text = "Il s'appelait Arthur ! Arthur Donovan, capitaine de la corvette 'Arbutus' ! Sale bâtard ! Alors tu es d'accord que j'étais près de l'envoyer au diable ?";
			link.l1 = "Bien sûr ! Il n'avait absolument aucune chance, mais tes compagnons ont interféré. Pardonne-les, ils ne voulaient pas que tu sois pendu pour le meurtre d'un officier de marine.";
			link.l1.go = "Jimmy_3";
		break;
		
		case "Jimmy_3":
			dialog.text = "Argh ! Si seulement j'avais un navire ! Ce salaud peut être facilement repéré près d'Antigua... ha ! Je te dois une fière chandelle si tu l'envoies par le fond !";
			link.l1 = "Marché conclu, ha-ha ! Au fait, est-ce que la Rumba vaut vraiment tes souffrances ?";
			link.l1.go = "Jimmy_4";
		break;
		
		case "Jimmy_4":
			dialog.text = "Bien sûr ! Je n'ai jamais rencontré quelqu'un de mieux qu'elle. Mais elle se moque de moi. Tout le monde veut cette sirène. Des marins m'ont secrètement dit que notre Jacob cherche une fille qui ressemble à ma Rumba. Lui aussi la veut ! Comment puis-je suivre ses ordres maintenant ?";
			link.l1 = "Tais-toi, l'ami ! Les murs ont des oreilles... Et pourquoi penses-tu que Jackman cherche la Rumba ?";
			link.l1.go = "Jimmy_5";
		break;
		
		case "Jimmy_5":
			dialog.text = "Il l'est, c'est sûr ! Il cherche un certain Henry le Bourreau et une jeunette de vingt ans aux cheveux blonds et aux yeux bleus. Une certaine Gladys Chandler de Belize doit être sa tutrice.";
			link.l1 = "Attends ! Gladys a un autre nom de famille. Et elle est sa mère !";
			link.l1.go = "Jimmy_6";
		break;
		
		case "Jimmy_6":
			dialog.text = "Jackman est rusé ! Vous ne pouvez pas le prendre au dépourvu ! J'ai courtisé Rumba pendant un moment et j'ai découvert que Gladys a épousé Sean McArthur il y a exactement vingt ans. Et avant cela, elle vivait à Belize. Son premier mari s'appelait Pete Chandler.\nPauvre Pete a été tué dans une rixe d'ivrognes. On dit que McArthur lui-même était responsable car il avait des sentiments pour la dodue Gladys à l'époque. Elle est devenue veuve avec un bébé dans les bras. L'enfant n'a pas survécu longtemps à son père et est mort de fièvre peu après.\nEt juste quelques mois après, Gladys et Sean sont apparus avec une fille, censée être la fille de McArthur, à Blueweld. Alors, comment Gladys a-t-elle pu donner naissance à un autre bébé si rapidement ? Vous suivez ?";
			link.l1 = "As-tu informé quelqu'un d'autre à ce sujet ?";
			link.l1.go = "Jimmy_7";
		break;
		
		case "Jimmy_7":
			dialog.text = "Pas encore. Ferme ta gueule ou... eh bien, tu me connais !";
			link.l1 = "Oui, je le fais. Tu as une langue pourrie qui révèle ses secrets à n'importe qui. Rumba a bien fait de t'envoyer ailleurs, bavard...";
			link.l1.go = "Jimmy_8_1";
			link.l2 = "Bien sûr ! Je serai muet comme une tombe ! Et maintenant, je dois y aller. Adieu, Jimmy.";
			link.l2.go = "Jimmy_8_2";
		break;
		
		case "Jimmy_8_1":
			dialog.text = "Qu... qu'as-tu dit?!";
			link.l1 = "Tu ne pourras le dire à personne d'autre...";
			link.l1.go = "Jimmy_fight";
			pchar.questTemp.Saga.Jimmysecret = "true";
		break;
		
		case "Jimmy_8_2":
			DialogExit();
			pchar.questTemp.Saga = "jackman";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "4_1");
		break;
// <-- Джимми 
		
//-------------------------------------------корвет Донована, абордаж-----------------------------------------
		//Донован
		case "Donovan_abordage":
			PlaySound("Voice\English\saga\Artur Donovan.wav");
			dialog.text = "Argh, toi, monstre !";
			link.l1 = "Vous parlez tout seul, Monsieur ?! Où est Rumba ?";
			link.l1.go = "Donovan_abordage_1";
		break;
		
		case "Donovan_abordage_1":
			dialog.text = "Quelle Rumba ? Je n'ai pas de racaille avec des surnoms sur mon navire. C'est un vaisseau de guerre anglais !";
			link.l1 = "Ne fais pas l'idiot avec moi, Donovan. Tu comprends parfaitement de qui je parle. Où est la fille ? Où est Helen ? Réponds-moi, sale bâtard...";
			link.l1.go = "Donovan_abordage_2";
		break;
		
		case "Donovan_abordage_2":
			dialog.text = "Helen ? Il n'y a pas de putains de terre sur mon navire, espèce de salaud !";
			link.l1 = "Pas de putains de terre ? Difficile à croire puisque l'une d'elles se tient juste devant moi en ce moment même... Je suppose qu'il n'y a aucun intérêt à poursuivre notre conversation. Meurs, vermisseau pathétique !";
			link.l1.go = "Donovan_abordage_3";
		break;
		
		case "Donovan_abordage_3":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterDonovanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Takehelen = "true";//признак, что абордировали судно
		break;
		
		//наш матрос
		case "Tempsailor":
			dialog.text = "Capitaine, nous avons fouillé toutes les cabines et la cale comme vous nous l'avez dit. Nous avons trouvé une fille enchaînée dans la cale...";
			link.l1 = "Quel salaud ! Comme je le pensais... As-tu libéré la fille ?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Bien sûr, Capitaine. Elle a été amenée en toute sécurité sur votre navire.";
			link.l1 = "Bien joué ! Emmenez-la dans ma cabine, je veux lui parler une fois que nous aurons terminé ici.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Oui-oui, Capitaine !";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
		break;
		//<-- абордаж корвета Донована
		
//----------------------------------------поиск Энрике Гонсалеса, Картахена----------------------------------
		//фальшивый Гонсалес №1, дом
		case "GonsalesA":
			dialog.text = "Tu veux quelque chose ?";
			link.l1 = "Bonjour, Bourreau ! Le capitaine Boucher te passe le bonjour.";
			link.l1.go = "GonsalesA_1_1";
			link.l2 = "Je m'appelle Charles de Maure. Je cherche Enrique, le fils de senora Gonzales de la part de son vieil ami. Je pense que c'est vous...";
			link.l2.go = "GonsalesA_2_1";
		break;
		
		case "GonsalesA_1_1":
			dialog.text = "Que diable ! Je ne connais aucun Boucher !";
			link.l1 = "Allez, Henry. Dis-moi pourquoi les pirates de Jackman te cherchent et je ne te ferai pas de mal.";
			link.l1.go = "GonsalesA_1_2";
		break;
		
		case "GonsalesA_1_2":
			dialog.text = "À l'aide ! Pirates ! Meurtre !";
			link.l1 = "Tais-toi, imbécile ! La moitié de la ville va accourir à cause de tes cris. Ah, c'est ce que tu veux ?!";
			link.l1.go = "GonsalesA_1_fight";
		break;
		
		case "GonsalesA_1_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesA");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesA_2_1":
			dialog.text = "Hm... Monsieur, vous devez faire erreur. J'ai grandi dans une famille étrangère, je ne me souviens pas de ma mère biologique. J'ai pris le nom de famille de mon tuteur. Je ne connais pas le nom de ma mère mais je doute que ce soit Gonzales. Vous pouvez vous renseigner à mon sujet et n'importe quel ancien résident confirmera mes paroles. Mon beau-père était un homme célèbre, il n'avait pas d'enfants à lui, donc j'ai hérité de cette maison et...";
			link.l1 = "Je suis désolé. Il semble que je me sois trompé. Adieu.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesA_3_1";
			else link.l1.go = "GonsalesA_2_2";
		break;
		
		case "GonsalesA_2_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "17");
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesA_3_1":
			dialog.text = "Je ne pense pas.";
			link.l1 = "Excusez-moi ?";
			link.l1.go = "GonsalesA_3_2";
		break;
		
		case "GonsalesA_3_2":
			dialog.text = "Vous savez, récemment notre colonie a été vicieusement attaquée par des pirates. Je crois que vous en avez entendu parler ? À la suite de cette attaque, d'innombrables personnes ont souffert. Je n'ai pas été blessé, mais mon entreprise héritée traverse maintenant des moments difficiles. Et le coupable de toute cette calamité est le chef de ces pirates, un vaurien nommé Charlie Prince.";
			link.l1 = "Je suis navré, mais qu'est-ce que cela a à voir avec moi ?";
			link.l1.go = "GonsalesA_3_3";
		break;
		
		case "GonsalesA_3_3":
			dialog.text = "Ha-ha, regardez-moi cet agneau innocent ! Je vous suggère de couvrir mes pertes, puisque vous en êtes le responsable. Je serai satisfait d'une somme de quinze mille pesos. Et je ferai semblant que vous n'avez jamais mis les pieds dans ma maison.";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "Que vous êtes tous vindicatifs... Voici votre argent. Et souvenez-vous, si quelqu'un découvre que j'étais dans cette ville, je reviendrai pour vous.";
				link.l1.go = "GonsalesA_3_4";
			}
			link.l2 = "Quinze mille ? Hm... Je ne pense pas que ta vie vaille autant. Alors, je suppose qu'il est moins coûteux de te pourfendre pour t'empêcher de bavarder.";
			link.l2.go = "GonsalesA_3_5";
		break;
		
		case "GonsalesA_3_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "171");
		break;
		
		case "GonsalesA_3_5":
			dialog.text = "Gardes ! Pirates ! Meurtre !";
			link.l1 = "Tais-toi, imbécile !";
			link.l1.go = "GonsalesA_3_6";
		break;
		
		case "GonsalesA_3_6":
			DialogExit();
			iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2;
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SpSold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, iTemp, true);         
				LAi_SetWarriorType(sld); 
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
			sld = GetCharacter(NPC_GenerateCharacter("SpOfficer", "off_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 100, 100, "blade_13", "pistol6", "bullet", 150);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesAK");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		// <-- участвовал в событиях Картахены
		
		// фальшивый Гонсалес №2, улицы
		case "GonsalesB":
			PlaySound("Voice\English\citizen\Pirati v Gorode-08.wav");
			dialog.text = "Je vois que tu aimes mon sabre. Je peux te le vendre si tu veux. Je ne demanderai pas grand-chose, je meurs d'envie de boire du rhum et mes poches sont vides.";
			link.l1 = "Et pourquoi diable en aurais-je besoin ? Le Diable de la Forêt m'a demandé de te transmettre ses salutations.";
			link.l1.go = "GonsalesB_1_1";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = "Eh bien, oui. Vous avez un beau sabre en effet. Combien ?";
				link.l2.go = "GonsalesB_2_1";
			}
		break;
		
		case "GonsalesB_1_1":
			dialog.text = "Il aurait mieux fait de me donner quelques centaines de pesos à la place !";
			link.l1 = "Alors, tu connais Svenson ?";
			link.l1.go = "GonsalesB_1_2";
		break;
		
		case "GonsalesB_1_2":
			dialog.text = "Va te faire foutre et va te faire foutre avec ton Svenson, envoie-le au diable. Au diable de la forêt ou au diable de la mer, je m'en fous. Si tu n'es pas prêt à aider un homme malade en achetant son sabre, alors je te l'enfoncerai dans le cul gratuitement.";
			link.l1 = "Vraiment? Voyons voir comment tu comptes faire ça, face de rat!";
			link.l1.go = "GonsalesB_1_fight";
		break;
		
		case "GonsalesB_1_fight":
			chrDisableReloadToLocation = true;
			DialogExit();
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesB");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesB_2_1":
			dialog.text = "Je vois que vous êtes un homme d'expérience ! Mille pesos et c'est à vous.";
			link.l1 = "Marché conclu !";
			link.l1.go = "GonsalesB_2_2";
		break;
		
		case "GonsalesB_2_2":
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(pchar, "blade_10");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "Il n'y a que deux sabres comme celui-ci à Carthagène - le mien et celui du vieux Alvares du phare. Mais il ne vendra pas le sien. C'est un hypocrite, je sens un ancien pirate à un mille de distance. La lame est une sorte de talisman pour lui.\nIl semble que le pauvre bougre se lamente sur des choses qu'il veut oublier. Cela doit être la raison pour laquelle il va à l'église tous les mois, à cause de péchés qui ne le laissent pas dormir.";
			link.l1 = "Et je vois que vous avez aussi un passé. Cela doit être vous dont Svenson parlait. Il a dit de vous transmettre ses salutations au cas où je vous rencontrerais à Carthagène.";
			link.l1.go = "GonsalesB_2_3";
		break;
		
		case "GonsalesB_2_3":
			dialog.text = "Svenson ? Jamais entendu parler de lui. Mon nom est Enrique Gallardo. Mais si ton Svenson a une bouteille de rhum pour moi, je veux bien être Henry pour lui. Appelle-moi comme tu veux, mais ne m'appelle pas en retard pour le dîner. Alors, on y va ?";
			link.l1 = "Pas aujourd'hui. Svenson est loin, mais la taverne est proche. Tes poches ne sont plus vides, alors prends garde, Enrique.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesB_3_1";
			else link.l1.go = "GonsalesB_2_4";
		break;
		
		case "GonsalesB_2_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "19");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesB_3_1":
			dialog.text = "Ils ne sont pas complètement pleins cependant. Je veux plus. Et tu me paieras.";
			link.l1 = "Je suis perplexe... N'accordez-vous pas de valeur à votre vie ? Vous comptez me dévaliser en plein milieu de la ville ? Et cela après m'avoir vendu votre arme vous-même ?";
			link.l1.go = "GonsalesB_3_2";
		break;
		
		case "GonsalesB_3_2":
			dialog.text = "Non, tu me paieras de ta propre poche. Et sais-tu pourquoi ?";
			link.l1 = "Curieux d'entendre.";
			link.l1.go = "GonsalesB_3_3";
		break;
		
		case "GonsalesB_3_3":
			dialog.text = "Je t'ai reconnu. J'étais dans les cachots pour une bagarre ivre à la taverne quand tes gars ont fait irruption dans la prison et ont abattu tous les gardes. J'ai réussi à atteindre le cadavre du garde avec les clés et suis sorti dans les rues. La ville était en flammes, des cadavres, du sang et de la fumée de poudre à canon partout... Comme lors d'un abordage ! Et à travers cette fumée, je t'ai vu sortir de la résidence du gouverneur. Poétique, n'est-ce pas ? Yo-ho-ho, bonjour, Prince Charlie !";
			link.l1 = "Arrête de crier comme ça ! Avec ce que tu sais, tu devrais surtout éviter d'essayer de me soutirer de l'argent. Te rends-tu même compte de ce que je peux te faire ?";
			link.l1.go = "GonsalesB_3_4";
		break;
		
		case "GonsalesB_3_4":
			dialog.text = "Au milieu de la ville que tu as déjà pillée ? Tu ne peux rien faire. Donc, pour conclure... nous allons procéder ainsi : tu me donnes... disons, dix mille pesos tout de suite. Je pense que cela suffira pour un mois. Et tu prends ton chemin ! Que ce soit vers ton cher Henry, vers Svenson, ou vers n'importe quel autre démon de ton choix... Et si tu ne le fais pas, il me suffit de crier, et ils te traîneront dans une chambre personnelle spécialement préparée, remplie d'outils de torture.";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Merde, prends tes dix mille et disparais de ma vue ! Et, que Dieu m'en garde, si je te revois.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "Ça suffit, j'en ai assez de tout ça. Ton arme est à moi, donc tu n'as aucune chance, vermine.";
			link.l2.go = "GonsalesB_3_7";
			link.l3 = "Haha, tu es doué ! Tu sais quoi ? J'aurais déjà étripé n'importe qui d'autre du ventre à la gorge. Mais des gens comme toi, j'en ai besoin. Que dirais-tu de ceci : je te donne dix mille pesos, je te rends ton 'Pendu', et je t'ajoute trois mille de plus chaque mois - ça devrait suffire pour la bibine - Et tu deviendras pensionnaire sur mon navire.";
			link.l3.go = "GonsalesB_3_9";
		break;
		
		case "GonsalesB_3_5":
			dialog.text = "D'accord, d'accord, je suis déjà parti ! Bonne chance dans ta quête, Prince Charlie !";
			link.l1 = "... ";
			link.l1.go = "GonsalesB_3_6";
		break;
		
		case "GonsalesB_3_6":
			AddMoneyToCharacter(pchar, -10000);
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "191");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		case "GonsalesB_3_7":
			dialog.text = "Gardes ! Gardes !!! C'est Charlie Prince !!!";
			link.l1 = "Pourquoi, espèce de salaud !";
			link.l1.go = "GonsalesB_3_8";
		break;
		
		case "GonsalesB_3_8":
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			LAi_group_AttackGroup("Spain_citizens", LAI_GROUP_PLAYER);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "192");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
		break;
		
		case "GonsalesB_3_9":
			dialog.text = "Voulez-vous dire que je devrais rejoindre votre équipage ?";
			link.l1 = "Exactement. Mais c'est une offre unique. Alors, qu'en dis-tu ? Acceptes-tu, ou je te vide les tripes. Tu ne crois tout de même pas pouvoir faire chanter Charlie Prince si facilement, n'est-ce pas ?";
			link.l1.go = "GonsalesB_3_10";
		break;
		
		case "GonsalesB_3_10":
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 && makeint(pchar.reputation.nobility) < 48)
			{
				dialog.text = "Diable ! Charlie Prince lui-même m'offre de rejoindre son équipage ! Maudit soit-tu, j'accepte ! Rends-moi ma lame et dix mille pesos. Jamais je n'aurais pensé que cela tournerait ainsi !";
				link.l1 = "Tiens. Et garde ta bouche fermée : personne dans cette ville n'a besoin de savoir qui je suis, compris ?";
				link.l1.go = "GonsalesB_3_11";
				break;
			}
			if(makeint(pchar.reputation.nobility) > 47)
			{
				dialog.text = "Non. Vous êtes peut-être un capitaine décent, mais il me semble que vous êtes un peu trop coincé. Oui, vous avez appris aux Espagnols à craindre une fois, en menant un raid audacieux sur Carthagène - mais tout cela n'était que grâce à l'aide de Marcus Tyrex. Vous n'avez pas les tripes pour faire du pillage honnête par vous-même. Alors, crachez le pognon !";
			}
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
			{
				dialog.text = "Non. Tu es certainement un pirate notoire, mais en tant que capitaine, tu ne sembles pas si impressionnant. Tu n'as réussi à piller la colonie qu'avec l'aide de Marcus Tyrex - tu n'oserais même pas aborder un sloop délabré tout seul. Alors, crache la galette !";
			}
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Merde, prends tes dix mille et disparais de ma vue ! Et, Dieu m'en garde, que je te revois.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "Ça suffit, j'en ai assez de ça. Ton arme est à moi, donc tu n'as aucune chance, vermine.";
			link.l2.go = "GonsalesB_3_7";
		break;
		
		case "GonsalesB_3_11":
			dialog.text = "Compris, je ne suis pas un imbécile.";
			link.l1 = "Bien.";
			link.l1.go = "GonsalesB_3_12";
		break;
		
		case "GonsalesB_3_12":
			DialogExit();
			AddMoneyToCharacter(pchar, -10000);
			LAi_RemoveLoginTime(npchar);
			npchar.quest.OfficerPrice = 3000;
			npchar.reputation.nobility = 30;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			npchar.loyality = MAX_LOYALITY;
			GiveItem2Character(npchar, "blade_10");
			EquipCharacterByItem(npchar, "blade_10");
			TakeItemFromCharacter(pchar, "blade_10");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			AddQuestRecord("Saga", "193");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
		break;
		// <-- участвовал в событиях Картахены
		
		//настоящий Гонсалес - Ортега, маяк
		case "Ortega":
			dialog.text = "Je n'attends aucun invité, ni aujourd'hui ni un autre jour. Que voulez-vous?";
			link.l1 = "Bonjour, Bourreau. Le Diable de la Forêt m'a envoyé. C'est bien que je t'aie trouvé avant les gars de Jackman. Ses hommes te cherchent partout dans les Caraïbes. Heureusement pour toi, Henry, seul Svenson sait où tu es né. Il m'a demandé de te prévenir.";
			link.l1.go = "Ortega_1";
		break;
		
		case "Ortega_1":
			dialog.text = "Je vois maintenant... Alors, il semble que Svenson soit toujours en vie et n'ait pas oublié son vieil ami. Beaucoup de sang a coulé depuis que je l'ai vu pour la première fois comme un novice sur le pont d'une brigantine endommagée... La vie est passée trop vite et je n'ai plus beaucoup de temps devant moi\nJe voulais mourir de causes naturelles sur cette terre désolée, loin de l'humanité et près de la mer. Mais si Jackman est de retour dans les Caraïbes, il ne me laissera pas en paix. Ce n'était pas ma faute, mais je dois à son maître. De toute façon, qui me croira maintenant.\nJe n'ai pas peur de la mort, mais de la douleur. Et Jackman en sait beaucoup sur la douleur. La simple pensée de cela fait arrêter mon cœur et tout devient sombre.";
			link.l1 = "Le Boucher a été pendu il y a vingt ans, donc tu n'as pas de dettes à rembourser à qui que ce soit. Tu peux me donner ta dette si tu as peur de Jackman. Je pense que tu le rencontreras de toute façon.";
			link.l1.go = "Ortega_2";
		break;
		
		case "Ortega_2":
			dialog.text = "Il n'est pas facile de pendre des gens comme le Boucher. L'ancien bourreau de St. John's pourrait vous raconter beaucoup d'histoires intéressantes sur les morts revenus de l'enfer. Et Jacob a été bien formé par son capitaine, donc je ne sais pas de qui j'ai le plus peur.";
			link.l1 = "Pourquoi Jackman a-t-il besoin de vous ?";
			link.l1.go = "Ortega_3";
		break;
		
		case "Ortega_3":
			dialog.text = "Je devais livrer de l'or à une veuve en paiement pour avoir gardé la fille du Boucher en sécurité. Pourquoi me regardez-vous ainsi? Oui, elle est née peu de temps avant que le 'Neptune' ne soit coulé. Il ne pouvait pas revenir pour elle à temps, alors il m'a envoyé m'occuper du bébé et de sa nourrice.";
			link.l1 = "Le nom de la gardienne était-il Gladys Chandler ?";
			link.l1.go = "Ortega_4";
		break;
		
		case "Ortega_4":
			dialog.text = "Ne fais pas l'idiot. Si Jackman me cherche, c'est parce qu'il a besoin de la fille de Butcher. Tu dois déjà savoir qu'il cherche une femme de Belize nommée Gladys et son enfant adoptif. Sois honnête avec moi et je pourrais te faire confiance.";
			link.l1 = "Qu'etiez-vous cense dire a Gladys ?";
			link.l1.go = "Ortega_5";
		break;
		
		case "Ortega_5":
			dialog.text = "Rien. Je devais lui montrer l'anneau du Boucher, c'est ainsi qu'elle saurait que j'étais un coursier envoyé par le capitaine. Je devais aussi lui donner un coffre de doublons pour les besoins du bébé. J'ai dû tuer un salaud pour lui prendre l'anneau. Cela m'a fait prolonger mon séjour à Antigua d'un mois supplémentaire.\nEt quand j'ai enfin atteint Belize, Gladys était déjà partie et la ville avait été brûlée et pillée par les Espagnols. Elle a réussi à vendre sa maison et à s'enfuir avec son nouveau compagnon et le bébé Hélène. J'espère qu'elle s'est occupée d'elle et n'a pas vendu la fille aux gitans ou au bordel.";
			link.l1 = "Le nom de la fille du Boucher était Helen, n'est-ce pas ?";
			link.l1.go = "Ortega_6";
		break;
		
		case "Ortega_6":
			dialog.text = "Exactement. En l'honneur de la mère du Boucher. Si tu n'as pas peur des morts-vivants et des pirates te fixant de leurs yeux morts, alors je peux te donner la bague et l'or. Je n'y ai jamais touché. Je mourais de faim mais je n'y ai pas touché. Fais-en ce que tu veux. Et en retour, je te demande...";
			link.l1 = "Que se passe-t-il, Henry ?!";
			link.l1.go = "Ortega_7";
		break;
		
		case "Ortega_7":
			dialog.text = "Toi...t... Je de...ma... oh!";
			link.l1 = "Non !";
			link.l1.go = "Ortega_8";
		break;
		
		case "Ortega_8":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			AddQuestRecord("Saga", "20");
			pchar.questTemp.Saga = "svenson1";
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "bucher_ring"); //перстень Бучера
			//таймер на возврат смотрителя
			SetFunctionTimerCondition("Saga_LightmanReturn", 0, 0, 10, false);
			//ставим прерывания, если ГГ наследил в городе
			if (CheckAttribute(pchar, "questTemp.Saga.Trap"))
			{
				pchar.quest.Saga_Trap.win_condition.l1 = "location";
				pchar.quest.Saga_Trap.win_condition.l1.location = "Mayak11";
				pchar.quest.Saga_Trap.function = "Saga_CreateTrapBandos";
				TraderHunterOnMap(true);
			}
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs");
			//pchar.questTemp.HelenDrinking = "end_henry";
		break;
		
		//бандиты в поисках Гонсалеса, маяк
		case "saga_trap":
			dialog.text = "A-ah, voilà notre ami curieux ! As-tu enfin trouvé Gonzales ? Bien joué, tu nous as menés à lui... nous n'avons plus besoin de toi. Les gars, tuez ce bouffon !";
			link.l1 = "Il est temps de mourir, tripes de crabe !";
			link.l1.go = "saga_trap_1";
		break;
		
		case "saga_trap_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			int n = makeint(MOD_SKILL_ENEMY_RATE/3);
			for (i=1; i<=3+n; i++)
			{	
				sld = characterFromId("sagatrap_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		//<-- поиск Гонсалеса, Картахена
		
//--------------------------------------------НПС по квесту Возвращение барона---------------------------------
		
		// доминиканский вождь
		case "DominicaHead":
			dialog.text = "Ou-ah ! Ou-ah ! Le grand Kukulcan exige une nouvelle victime ! O-èh ! L'esprit du puissant guerrier du passé est venu dans notre village pour être sacrifié au grand Kukulcan ! O-èh ! Tous s'inclinent devant l'esprit du puissant guerrier !";
			link.l1 = "(faiblement) Mais qu'est-ce que c'est que ce bordel, où suis-je ?";
			link.l1.go = "DominicaHead_1";
			NextDiag.TempNode = "DominicaHead";
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A Comanche potion is used", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("You are feeling that your health is restored!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "DominicaHead_1":
			dialog.text = "O-eh! Grand guerrier veut être dévoré par le grand Kukulcan! Le soleil se lève, les ombres raccourcissent! Le grand Kukulcan sera bientôt vivant! Nous te conduisons à lui, ô puissant guerrier, et tu continues à traverser la terre des ancêtres!";
			link.l1 = "(faiblement) Balivernes... Kukulcan encore ? Hé, chef, je suis venu en paix ! Je suis ici pour...";
			link.l1.go = "DominicaHead_2";
		break;
		
		case "DominicaHead_2":
			dialog.text = "O-eh ! Grand guerrier dit qu'il veut être sacrifié à Kukulcan immédiatement. Oh, grand guerrier ! Nous allons maintenant à Kukulcan et attendons sa visite ! Guerriers ! Nous avons le grand honneur d'apporter l'esprit de l'ancêtre à Kukulcan !";
			link.l1 = "(faiblement) Idiot... Bon, je dois aller avec eux. Heureusement qu'ils ne m'ont pas encore attaqué, je ne pourrais pas me défendre dans ce truc...";
			link.l1.go = "DominicaHead_3";
		break;
		
		case "DominicaHead_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1_back", "Saga_DominicaDollyReload", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
			}
		break;
		
		case "DominicaHead_4":
			dialog.text = "Nous venons à Kukulcan, grand esprit ancêtre. Bientôt le soleil se couchera, les ombres grandiront et Kukulcan nous visitera. Attends, grand guerrier...";
			link.l1 = "(faiblement) Maintenant je vois, chef de guerre indien...";
			link.l1.go = "DominicaHead_5";
		break;
		
		case "DominicaHead_5":
			DialogExit();
			bDisableCharacterMenu = true;//лочим Ф2
			AddQuestRecord("BaronReturn", "7");
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_DominicaDollyWait", 5.0);
			pchar.questTemp.Saga.BaronReturn = "third_teleport";
		break;
		
		case "DominicaHead_6":
			dialog.text = "Kukulcan vivant ! Kukulcan avec nous ! Grand guerrier peut être sacrifié à Kukulcan ! Guerriers, inclinez-vous devant le grand esprit ancêtre !";
			link.l1 = "(faiblement) Reste à l'écart, Chef. Je le ferai moi-même. Ce n'est pas ma première fois...";
			link.l1.go = "DominicaHead_7";
		break;
		
		case "DominicaHead_7":
			DialogExit();
			bDisableCharacterMenu = false;//разлочим Ф2
			AddQuestRecord("BaronReturn", "8");
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
			}
		break;
		
//----------------------------------------НПС по квесту Искушение Барбазона----------------------------------
		// капитан рыболовного баркаса, стыривший шелк, море
		case "BarbCapBarkas":
			dialog.text = "Comment puis-je vous aider, monsieur?";
			link.l1 = "Eh bien, eh bien... dis-moi, mon pote, que fais-tu ici ?";
			link.l1.go = "BarbCapBarkas_1";
		break;
		
		case "BarbCapBarkas_1":
			dialog.text = "Que fais-je ici ? Je suis un pêcheur et je pêche ici. Et pourquoi diable m'interrogez-vous sur ce ton ?";
			link.l1 = "Ne me mens pas, mon gars. Peut-être es-tu vraiment un pêcheur, mais tu n'as pas pêché du poisson ici. De la précieuse soie de navire a été jetée à la mer, ici à cet endroit. Et ta simple présence me paraît assez suspecte.";
			link.l1.go = "BarbCapBarkas_2";
		break;
		
		case "BarbCapBarkas_2":
			dialog.text = "Quelle sottise ? De quelle soie parles-tu même ?";
			link.l1 = "Quels soies? Celles de Chine... Ne fais pas l'idiot! Écoute-moi bien : soit tu sors immédiatement la soie de ta cale et tu me la donnes, soit je la prends moi-même. Mais d'abord, mes hommes d'abordage s'occuperont de toi et de tes gens. Alors? Dois-je appeler mes hommes?";
			link.l1.go = "BarbCapBarkas_3";
		break;
		
		case "BarbCapBarkas_3":
			dialog.text = "Non ! Mynheer, je ne savais pas... Ces ballots flottaient juste autour alors j'ai décidé...";
			link.l1 = "Apportez la soie à mon navire. Faites vite !";
			link.l1.go = "BarbCapBarkas_4";
		break;
		
		case "BarbCapBarkas_4":
			dialog.text = "Oui, oui, bien sûr. Nous ferons cela immédiatement, juste ne prends pas mon bateau !";
			link.l1 = "Remue-toi le cul ! Je n'ai pas beaucoup de temps...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_BarbBarkasSilk");
		break;
		
		case "BarbCapBarkas_5":
			dialog.text = "Nous avons tout apporté - les neuf balles. C'est tout, je le jure...";
			link.l1 = "D'accord. Tu peux continuer ta pêche, mais ne convoite pas les biens des autres à l'avenir !";
			link.l1.go = "BarbCapBarkas_6";
		break;
		
		case "BarbCapBarkas_6":
			DialogExit();
			npchar.DontDeskTalk = true;
			npchar.lifeday = 0;
			LAi_SetStayType(npchar);
			pchar.quest.BarbBarkas_Sink.over = "yes"; //снять прерывание
			pchar.quest.BarbBarkas_Abordage.over = "yes"; //снять прерывание
			NextDiag.CurrentNode = "BarbCapBarkas_7";
			AddQuestRecord("BarbTemptation", "6");
			pchar.questTemp.Saga.BarbTemptation = "give_silk";
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "BarbCapBarkas_7":
			dialog.text = "Tu as déjà obtenu ce que tu voulais. Je n'ai plus rien ! Que veux-tu encore ?";
			link.l1 = "Détends-toi, l'ami. Je m'en vais.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BarbCapBarkas_7";
		break;
		
		// Моррель, капитан потопленного судна, тюрьма
		case "Morelle":
			dialog.text = "Si tu es envoyé par Barbazon, alors dis-lui que je ne veux pas quitter la prison moi-même. Je préfère attendre le procès. Même le chanvre hollandais autour du cou est préférable à sa gentillesse.";
			link.l1 = "Ne pète pas encore. Ton navigateur a dit à Jacques que tu étais mort. Il m'a envoyé chercher la soie que tu as jetée à la mer. Combien y en avait-il sur ta brigantine ?";
			link.l1.go = "Morelle_1";
		break;
		
		case "Morelle_1":
			dialog.text = "C'était de ma faute, bon sang. Le courrier a apporté neuf ballots de soie pour Barbazon. J'ai ordonné de le suivre. Il est devenu bruyant, alors nous avons dû lui trancher la gorge. Il avait trois ballots supplémentaires dans sa cachette que j'ai pris pour moi et cachés dans ma propre cachette. Mais il semble que nous avons attiré une attention indésirable.\nIls nous ont trouvés rapidement et une patrouille hollandaise attendait le 'Chien Salé' en pleine mer. Nous n'avons pas réussi à nous échapper. Tu peux prendre la soie pour toi si tu ne dis rien à Barbazon à mon sujet. La cachette est située à Grand Case Beach entre les pierres près de l'impasse. Il est peu probable que j'en ai besoin à nouveau.";
			link.l1 = "D'accord. Je ne dirai pas à Barbazon que tu es encore en vie. Si ce qu'on dit de lui est vrai, alors il vaut mieux pour toi d'être pendu par les Hollandais. Ou, peut-être auras-tu de la chance et ils te condamneront aux travaux forcés.";
			link.l1.go = "Morelle_2";
		break;
		
		case "Morelle_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			// тайник - модель
			//int m = Findlocation("Shore40");
			//locations[m].models.always.Roll = "Roll_of_rolls";
			//Locations[m].models.always.Roll.locator.group = "quest";
			//Locations[m].models.always.Roll.locator.name = "quest1";
			pchar.quest.Saga_MorelGoods.win_condition.l1 = "locator";
			pchar.quest.Saga_MorelGoods.win_condition.l1.location = "Shore40";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator = "quest1";
			pchar.quest.Saga_MorelGoods.function = "Saga_SetMorelGoods";
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
		
		// Валет, брат Джекмана в Капстервиле
		case "valet":
			dialog.text = "J'attends l'homme qui sait quand commencera la chasse au requin blanc.";
			link.l1 = "La chasse a commencé.";
			link.l1.go = "valet_1";
		break;
		
		case "valet_1":
			dialog.text = "Enfin ! Maintenant écoute attentivement. Tu devras rendre visite à Marcus Tyrex à La Vega et lui dire que la brigantine 'Separator' a été attaquée près de l'île des Turcs et se cache maintenant dans la baie du Sud. Son capitaine est grièvement blessé et l'équipage attend des secours. Tu as récupéré un marin du 'Separator' et il t'a tout raconté. Il est mort maintenant. C'est tout ce que tu sais. Compris ?";
			link.l1 = "Et pourquoi as-tu besoin de moi pour cela ? J'ai attendu trop longtemps juste pour ça...";
			link.l1.go = "valet_2";
		break;
		
		case "valet_2":
			dialog.text = "Vous êtes payé pour faire votre travail et non pour poser des questions. Cependant, vous avez raison. Je dois vous avertir que Tyrex ne vous laissera pas partir tant qu'il ne sera pas sûr que vous dites la vérité. Mais une fois qu'il aura tout découvert, il vous paiera bien. Si toutefois il en est capable...";
			link.l1 = "Tu me roules dans la farine, monsieur... Pourquoi ne veux-tu pas recevoir ses remerciements toi-même ?";
			link.l1.go = "valet_3";
		break;
		
		case "valet_3":
			dialog.text = "Carramba ! Je n'aime pas ta curiosité ! Tes bavardages te mèneront droit dans la tombe un jour.";
			link.l1 = "Oui, parfois je suis insupportable. Surtout quand je vois que quelqu'un va essayer de me rouler. Non, mon gars, maintenant on va jouer selon mes règles. Qui est ton maître, bon sang ? Réponds ou je vais te faire parler !";
			link.l1.go = "valet_4";
		break;
		
		case "valet_4":
			dialog.text = "Toi... salaud ! Barbazon paiera pour ça et ta vie va se terminer, bouffeur de merde !";
			link.l1 = "Ha ! Je m'y attendais. Prépare-toi, vaurien !";
			link.l1.go = "valet_5";
		break;
		
		case "valet_5":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_ValetDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "vensan":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				dialog.text = "Charlie Prince ? Que fais-tu ici ? A-argh, sacrebleu, c'était toi ! Tout cela est de ton fait !";
				link.l1 = "Calme-toi Bernie. Je suis de ton côté. L'embuscade est éliminée, toi et ton navire êtes en sécurité.";
				link.l1.go = "vensan_8";
			}
			else
			{
				dialog.text = "Qui diable es-tu ? Comment es-tu arrivé ici ? Pars maintenant, mon navire est piégé et les salauds sur le rivage peuvent le faire sauter d'un coup.";
				link.l1 = "Ne vous inquiétez pas, Monsieur. L'embuscade sur le rivage a été éliminée. Votre navire est en sécurité maintenant tant que vous n'allez pas allumer une pipe sur le pont, bien sûr. Quel est votre nom ?";
				link.l1.go = "vensan_1";
			}
		break;
		
		case "vensan_1":
			dialog.text = "Vincent. Bernard Vincent. Et comment t'appelles-tu ?";
			link.l1 = "Capitaine "+GetFullName(pchar)+". Je vais couper ces cordes et te libérer...";
			link.l1.go = "vensan_2";
		break;
		
		case "vensan_2":
			LAi_SetStayType(npchar);
			dialog.text = "Oh... ma gratitude. Comment puis-je vous remercier ?";
			link.l1 = "Ce n'est pas encore fini, Monsieur. Y a-t-il encore quelqu'un de votre équipage en vie ?";
			link.l1.go = "vensan_3";
		break;
		
		case "vensan_3":
			dialog.text = "Trois douzaines de mes hommes sont enfermés dans la cale à marchandises...";
			link.l1 = "Libérez-les et partez d'ici immédiatement. ";
			link.l1.go = "vensan_4";
		break;
		
		case "vensan_4":
			dialog.text = "Mais...";
			link.l1 = "Ne perds pas de temps, Bernard. Tu pourras me remercier plus tard à La Vega... Tyrex pourrait aussi me remercier.";
			link.l1.go = "vensan_5";
		break;
		
		case "vensan_5":
			dialog.text = "Alors, tu n'es pas ici par hasard ? Tu savais tout ?";
			link.l1 = "Oui, je savais. J'ai réussi à dévoiler la machination de Jackman et ses plans pour tuer Marcus. Oh, demande à Tyrex de rester tranquille, ses ingérences peuvent effrayer Jackman.";
			link.l1.go = "vensan_6";
		break;
		
		case "vensan_6":
			dialog.text = "Je lui dirai, c'est sûr ! Tu pars maintenant ?";
			link.l1 = "Oui. Et tu devrais te dépêcher aussi.";
			link.l1.go = "vensan_7";
		break;
		
		case "vensan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto2", "none", "", "", "", 5.0);
			Ship_SetTaskRunaway(SECONDARY_TASK, GetCharacterIndex("Cap_Vensan"), GetMainCharacterIndex());
			pchar.questTemp.Saga.BarbTemptation.Vensan_free = "true";
			if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.vensan_attack"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
				else sld = characterFromId("Helena");
				sld.dialog.currentnode = "sea_bomb"; 
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			sld = characterFromId("Cap_Vensan");
			sld.lifeday = 1;
			sld.DontDeskTalk = true;
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "vensan_8":
			dialog.text = "Vraiment ? Écoute, je suis désolé, frère...";
			link.l1 = "Laisse tomber. Laisse-moi juste couper les cordes et te libérer.";
			link.l1.go = "vensan_9";
		break;
		
		case "vensan_9":
			LAi_SetStayType(npchar);
			dialog.text = "Merde... Je ne sens plus mes mains...";
			link.l1 = "Bernie, y a-t-il plus de survivants sur le navire ?";
			link.l1.go = "vensan_10";
		break;
		
		case "vensan_10":
			dialog.text = "Trente hommes sont enfermés dans la cale à cargaison...";
			link.l1 = "Libérez-les et dégagez d'ici. Maintenant !";
			link.l1.go = "vensan_11";
		break;
		
		case "vensan_11":
			dialog.text = "Mais...";
			link.l1 = "Naviguez vers La Vega immédiatement. Dites à Marcus tout sur ce bazar en détails complets.";
			link.l1.go = "vensan_12";
		break;
		
		case "vensan_12":
			dialog.text = "Est-ce que Marcus t'a envoyé ?";
			link.l1 = "Il ne l'a pas fait. J'ai réussi à dévoiler le complot d'un salaud. Il prévoyait d'éliminer Marcus par cette intrigue. Demandez-lui de rester tranquille et de ne pas intervenir pour l'instant... Je lui expliquerai tout moi-même, plus tard. Et s'il vous plaît, dites-lui d'arrêter d'être en colère contre moi.";
			link.l1.go = "vensan_7";
		break;
		
 //--------------------------------------НПС по Завещанию Шарпа--------------------------------------------------
		// Устрица, Поль Моллиган
		case "molligan":
			dialog.text = "Que voulez-vous sur mon navire, Monsieur ?";
			link.l1 = "Bonne journée, Paul. Votre nom est Paul Molligan, n'est-ce pas ?";
			link.l1.go = "molligan_0";
		break;
		
		case "molligan_0":
			dialog.text = "Oui, c'est moi. Comment puis-je vous aider?";
			link.l1 = "Mon nom est "+GetFullName(pchar)+" et Jan Svenson m'a envoyé.";
			link.l1.go = "molligan_1";
		break;
		
		case "molligan_1":
			dialog.text = "Jan ? A-ah, je me souviens de toi. Bien sûr ! Tu as visité sa maison sans cesse ces derniers temps. Alors, que veut Jan de moi ?";
			link.l1 = "Tu étais tellement pressé de quitter Blueweld. Jan voulait charger ton navire avec deux cents quintaux de bois d'acajou supplémentaires pour les livrer à lord Willoughby à Bridgetown. Prépare ton vaisseau, mes hommes mettront l'acajou dans ta cale.";
			link.l1.go = "molligan_2";
		break;
		
		case "molligan_2":
			dialog.text = "Acajou ? Jan a dit cela ? Hum. Et pourquoi ne le livreras-tu pas toi-même à la Barbade ? Pourquoi moi ?";
			link.l1 = "Parce que tu navigues là-bas et moi non. J'ai une mission immédiate de Svenson, donc je ne peux pas perdre mon temps à naviguer jusqu'à Bridgetown aussi. En outre, Jan ne me fait pas confiance pour traiter avec lord Willoughby et il veut que ce soit toi qui le fasses. Je suis désolé. Maintenant, chargeons la cargaison, je dois partir.";
			link.l1.go = "molligan_3";
		break;
		
		case "molligan_3":
			dialog.text = "Écoute, je n'ai pas de place libre dans ma cale. Je ne pourrai pas faire ce que Jan me demande, même si j'aimerais bien.";
			link.l1 = "Pas de place ? Étrange... Jan m'a dit que vous aviez de l'espace libre.";
			link.l1.go = "molligan_4";
		break;
		
		case "molligan_4":
			dialog.text = "C'est vrai, mais Jan ne savait pas que j'ai équipé l'‘Oyster’ de canons plus lourds. Je ne peux pas charger plus de cargaison que je n'en ai déjà. Alors livre le bois à la Barbade toi-même, hein, l'ami ? Dis à Jan que je ne pouvais pas le faire. Traiter avec Willoughby est facile : il suffit de le voir, lui donner la cargaison et prendre ton reçu. Assez simple.";
			link.l1 = "Hm. Ce n'était pas mon plan... Vérifions votre cale, voulez-vous? Mon quartier-maître est très talentueux pour ranger les choses, il sera capable de mettre les marchandises dans votre cale et même vous laisser un peu d'espace libre...";
			link.l1.go = "molligan_5";
		break;
		
		case "molligan_5":
			dialog.text = "Ami, je ne peux pas prendre d'autres marchandises. Veux-tu que je me débarrasse de mes canons et que je laisse l' 'Huitre' sans protection ?";
			link.l1 = "Eh bien, si tu en es si sûr... Mais Jan n'aimera pas ça, tiens-le en considération !";
			link.l1.go = "molligan_6";
		break;
		
		case "molligan_6":
			dialog.text = "Je vais l'expliquer à Svenson, ne t'inquiète pas. Après tout, c'est de sa faute, il ne m'a pas demandé le tonnage de mon navire.";
			link.l1 = "Eh, et maintenant je devrai naviguer avec ces bûches jusqu'à la Barbade, nom d'un chien... Adieu, l'ami.";
			link.l1.go = "molligan_7";
		break;
		
		case "molligan_7":
			DialogExit();
			// ставим проверку скрытности
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > (10+hrand(50)))
			{
				pchar.questTemp.Saga.Molligan.friend = "true"; // будет шанс критического залпа картечью
				sTemp = "The scoundrel is still not suspecting a thing. I should get closer and shoot at him with grapeshot. A sudden strike will always win in any battle. ";
				log_Testinfo("Friends");
				AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
				AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			}
			else
			{
				pchar.questTemp.Saga.Molligan.enemy = "true"; // нападет
				sTemp = "";
				log_Testinfo("Enemies");
				AddCharacterExpToSkill(pchar, "Sneak", 150);//скрытность
			}
			AddQuestRecord("Testament", "7");
			AddQuestUserData("Saga", "sText", sTemp);
			NextDiag.CurrentNode = "molligan_8";
			npchar.DontDeskTalk = true; // patch-5
		break;
		
		case "molligan_8":
			dialog.text = "Nous sommes clairs, n'est-ce pas ?";
			link.l1 = "Oui, oui. Je vais à mon navire.";
			link.l1.go = "exit";
			NextDiag.TempNode = "molligan_8";
		break;
		
	//-----------------------------------------НПС по Теням прошлого--------------------------------------------
		// Джим Бенсон, плешивая мэгги
		case "benson":
			dialog.text = "Que veux-tu de moi ? Je n'aime pas les commérages ni le jeu. Et je bois mon rhum seul. En plus, je suis de mauvaise humeur après ma dernière croisière.";
			link.l1 = "Et quelle chose spéciale s'est passée lors de ta dernière croisière ?";
			link.l1.go = "benson_1";
		break;
		
		case "benson_1":
			dialog.text = "Un brave homme m'a fait confiance et je l'ai jeté par-dessus bord parce que mon équipage l'exigeait.";
			link.l1 = "Et quelle était sa faute?";
			link.l1.go = "benson_2";
		break;
		
		case "benson_2":
			dialog.text = "Je suis un nouveau venu et je ne connais pas grand monde ici. C'est pourquoi j'ai engagé ce bon gros homme comme chirurgien sans connaître son passé. Les pirates nous poursuivaient depuis notre départ de la Barbade. Pourquoi auraient-ils besoin de ma coquille d'œuf ?\nNous avons à peine réussi à nous échapper, grâce à un fort coup de vent. Nous avons bu un coup pour l'occasion. Et le gros idiot n'a rien trouvé de mieux à faire que de dire à tout le monde que les pirates le poursuivaient probablement parce qu'il est l'ancien bourreau et qu'il sait des choses qu'il ne devrait pas savoir.\nBien sûr, mes marins étaient vraiment en colère. Vraiment ?! Un bourreau à bord, servant de chirurgien ! Et personne ne voulait s'en prendre aux pirates non plus... Alors j'ai dû débarquer le pauvre bougre. C'est entièrement de sa faute, il n'avait qu'à ouvrir sa bouche. Mais je me sens mal pour le péquenaud, c'était un excellent médecin. Il ne lui a fallu qu'une minute pour guérir ma gueule de bois.";
			link.l1 = "Merde ! Votre médecin s'appelait Raymond Baker, n'est-ce pas ?";
			link.l1.go = "benson_3";
		break;
		
		case "benson_3":
			dialog.text = "Oui. Exactement. Et comment le savez-vous ? Vous me suiviez ?";
			link.l1 = "Non, ce n'était pas moi. J'ai juste besoin de cet homme, c'est un excellent médecin. Où l'avez-vous débarqué ?";
			link.l1.go = "benson_4";
		break;
		
		case "benson_4":
			dialog.text = "Latitude 15 degrés 28' nord, longitude 63 degrés 28' ouest. Dépêchez-vous, Monsieur ! Il doit encore être en vie et vous me disculperez si vous le sauvez !";
			link.l1 = "Je lève déjà mes ancres!";
			link.l1.go = "benson_5";
		break;
		
		case "benson_5":
			DialogExit();
			NextDiag.CurrentNode = "benson_6";
			AddQuestRecord("Shadows", "3");
			npchar.lifeday = 0;
			bQuestDisableMapEnter = false;
			pchar.quest.Saga_Shadows_Baker.win_condition.l1 = "location";
			pchar.quest.Saga_Shadows_Baker.win_condition.l1.location = "Dominica";
			pchar.quest.Saga_Shadows_Baker.function = "Saga_SetBakerBoat";
			DeleteAttribute(pchar, "Cheats.SeaTeleport");
		break;
		
		case "benson_6":
			dialog.text = "Capitaine, dépêchez-vous ! Il doit encore être en vie !";
			link.l1 = "Oui, oui, je suis en route...";
			link.l1.go = "exit";
			NextDiag.TempNode = "benson_6";
		break;
		
	//---------------------------------------бандиты у джекмановского рудника-------------------------------
		case "mine_bandit":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Hé ! Restez là ! Ne bougez pas. Ce territoire est sécurisé !";
				link.l1 = "Ne sois pas trop dur, l'ami ! Amis ! Jackman nous a envoyés. Nous devons aller à la mine. Ordre du maître...";
				link.l1.go = "mine_attack";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hé ! Restez là ! Ne bougez pas. Ce territoire est sécurisé !";
				link.l1 = "Hm. Mais je veux passer... Pourquoi diable m'arrêtes-tu ?";
				link.l1.go = "mine_bandit_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "A-ah, toi encore? Je vois que tu ne comprends pas... Les gars, feu!!";
				link.l1 = "... -> ";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_bandit_0":
			dialog.text = "Allez, avancez !";
			link.l1 = "Très bien...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_bandit_0";
		break;
		
		case "mine_bandit_1":
			dialog.text = "Parce que la mine derrière moi est une propriété privée et je suis ici pour empêcher tout étranger comme toi de passer. Tu ferais mieux de faire demi-tour et de quitter cet endroit, étranger. Nos canons sont chargés de mitraille, juste un pas de plus et tu deviendras une flaque mouillée.";
			link.l1 = "Eh bien, je vois. Ta mine est bien gardee. Très bien, je m'en vais.";
			link.l1.go = "mine_bandit_exit";
			link.l2 = "Toi, salaud ! Eh bien, nous verrons qui deviendra une flaque !";
			link.l2.go = "mine_bandit_2";
		break;
		
		case "mine_bandit_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestReloadToLocation("Mine_02", "reload", "reload3", "");
		break;
		
		case "mine_bandit_2":
			dialog.text = "Je t'ai donné une chance... Les gars, feu !!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_bandit_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsFire", 1.5);
		break;
		
		case "mine_banditx":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Hé ! Va-t'en ! Ce territoire est sécurisé !";
				link.l1 = "Eh, détends-toi, l'ami ! Jackman nous a envoyés. Nous devons nous rendre à la mine. Ordre du maître...";
				link.l1.go = "mine_attackx";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hé ! Va-t'en ! Ce territoire est sécurisé !";
				link.l1 = "Hm. Et qu'y a-t-il là?";
				link.l1.go = "mine_banditx_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah-ah, vous encore ? Je vois que vous ne comprenez pas... Les gars, feu !!";
				link.l1 = "... ";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_banditx_1":
			dialog.text = "Aucune affaire à toi. Fiche le camp ou nous te tirerons dessus, je le jure !";
			link.l1 = "Calme-toi. Je m'en vais.";
			link.l1.go = "mine_banditx_exit";
			link.l2 = "Toi, salaud ! Eh bien, nous verrons qui tirera sur qui !";
			link.l2.go = "mine_banditx_2";
		break;
		
		case "mine_banditx_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			DoQuestReloadToLocation("Mine_04", "reload", "reload3", "");
		break;
		
		case "mine_banditx_2":
			dialog.text = "Je t'ai donné une chance... Mousquets prêts ! Feu !!";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_banditx_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsxFire", 0.6);
		break;
		
		case "mine_attackx":
			dialog.text = "Vraiment ? Vous devez alors connaître le mot de passe. Parlez, mais vous le regretterez si vous mentez...";
			link.l1.edit = 5;
			link.l1 = "";
			link.l1.go = "mine_attackx_1";
		break;
		
		case "mine_attackx_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[5]);
			if (sTemp == "neptune")
			{
				dialog.text = "Correct. Mais toi, mon gars, tu es arrivé ici du mauvais côté. Ne t'ont-ils pas prévenu ? Retourne et prends le chemin à gauche du puits sec. Ensuite, contourne la colline et là tu verras la porte principale.";
				link.l1 = "Je ne peux pas entrer ici ?";
				link.l1.go = "mine_attackx_2";
			}
			else
			{
				dialog.text = "Les gars, nous avons un fouineur ! Mousquets prêts ! Feu !!";
				link.l1 = "... ";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_attackx_2":
			dialog.text = "Non. Uniquement par l'entrée centrale.";
			link.l1 = "D'accord, l'ami... Hé ! Regarde ! C'est quoi ce bordel en haut de la palissade ?";
			link.l1.go = "mine_attackx_3";
		break;
		
		case "mine_attackx_3":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mine_banditx_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			sld = characterFromId("Svensons_sold_12");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
			LAi_ActorAnimation(sld, "shot", "Saga_MineBanditxDie", 1.0);
		break;
		
		case "mine_attack":
			dialog.text = "Vraiment? Tu dois donc connaître le mot de passe. Parle fort et dis-le pour que je puisse l'entendre. Et si tu essaies de me tromper, ce sera la dernière blague que tu feras à quelqu'un dans ta vie.";
			link.l1.edit = 5;
			link.l1 = "";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[5]);
			if (sTemp == "neptune")
			{
				dialog.text = "Correct. Avancez. Le chef du camp se trouve dans la maison à gauche de l'entrée de la mine. Allez le voir.";
				link.l1 = "Bien, mon pote...";
				link.l1.go = "mine_attack_2";
			}
			else
			{
				dialog.text = "Les gars, nous avons un fouineur ! Canons, ouvrez le feu !!";
				link.l1 = "Salut, mon ami.";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_attack_2":
			DialogExit();
			NextDiag.CurrentNode = "mine_attack_3";
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetActorDialogAny2Pchar(npchar.id, "", 0.0, 0.0);
		break;
		
		case "mine_attack_3":
			dialog.text = "Quoi d'autre? As-tu oublié quelque chose?";
			link.l1 = "Oui. On m'a demandé de te transmettre les meilleures salutations.";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "Pour moi ? Ha-ha ! De qui ?";
			link.l1 = "Jan Svenson, espèce de salaud !";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			DialogExit();
			LAi_SetPlayerType(pchar);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Mine_bandit_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			if (pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetActorType(sld);
				LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
				LAi_ActorAnimation(sld, "shot", "Saga_MineBanditDie", 1.0);
			}
			else
			{
				for (i=1; i<=6; i++)
				{
					sld = characterFromId("Mine_bandit_"+i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "Saga_BanditsDestroyed");
				AddDialogExitQuest("MainHeroFightModeOn");	
			}
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "NPC_Death";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.character = "Mine_bandit_1";
			pchar.quest.Saga_MineAttack_07.win_condition.l2 = "NPC_Death";
			pchar.quest.Saga_MineAttack_07.win_condition.l2.character = "Mine_bandit_2";
			pchar.quest.Saga_MineAttack_07.function = "Saga_SvensonMineexitAttack";
		break;
		
	// ----------------------------- диалоги НПС при штурме бандитского рудника -------------------------------
		case "Svensons_off":
			dialog.text = LinkRandPhrase("Nous allons déchirer ces salauds !","J'ai hâte de rosser ces vauriens !","Les sbires de Jackman n'ont aucun droit d'être à la Terre Ferme Occidentale ! Nous les chasserons d'ici !");
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_off";
		break;
		
		case "Svensons_sold":
			dialog.text = LinkRandPhrase("Nous sommes prêts à nous battre !","Nous leur montrerons !","Ils ne savent même pas à qui ils s'en prennent !");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_sold";
		break;
		
		case "gunner":
			PlaySound("Voice\English\evilpirates01.wav");
			dialog.text = "Commandant, le canon est prêt. Il a été chargé avec une bombe, comme vous l'avez ordonné.";
			link.l1 = "Je suppose que personne ne nous attend ici... Il est temps de nous présenter. Jan m'a dit que leur camp est derrière cette colline. Pourras-tu l'atteindre ?";
			link.l1.go = "gunner_0_1";
		break;
		
		case "gunner_0_1":
			dialog.text = "Ça suffit, Commandant. Levons un peu le baril, ça devrait le faire... c'est fait.\nPréparez-vous!.. Feu!!";
			link.l1 = "Hello, friend.";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "1";
		break;
		
		case "gunner_0_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_Gunfire", 3.0);
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_1":
			dialog.text = "";
			link.l1 = "Hm. Randolf, tu penses qu'on a heurté quelque chose ? J'aimerais entendre ton avis.";
			link.l1.go = "gunner_1_1";
		break;
		
		case "gunner_1_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Commandant, nous avons touché quelque chose ou quelqu'un, mais je ne peux être plus précis... cette maudite colline bloque la vue. Je vais changer l'angle.\nPrêt ! Feu !";
			link.l1 = "... ";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "2";
		break;
		
		case "gunner_2":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			dialog.text = "Ha ! Regarde, Commandant ! Il y a de la fumée ! Sacrebleu, nous avons dû toucher une grange de bandits ! Hourra-ah !";
			link.l1 = "Oui, je vois la fumée... Une victoire épique déjà, sans doute. Recharge le canon et pointe-le vers le chemin, on dirait que nos invités arrivent. Nous les accueillerons comme il se doit !";
			link.l1.go = "gunner_2_1";
		break;
		
		case "gunner_2_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Aye-aye, Commandant ! Chargez une bombe ! Équipage d'artillerie prêt ! Mèche prête ! Feu à mon signal !";
			link.l1 = "... ";
			link.l1.go = "gunner_2_2";
			npchar.quest.canonada = "3";
		break;
		
		case "gunner_2_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_01", 6.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_3":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			PlaySound("Voice\English\evilpirates05.wav");
			dialog.text = "Ha-ha, ça doit faire mal !";
			link.l1 = "Ne te détends pas encore ! Charge le canon ! Je ne crois pas qu'ils en aient eu assez. D'autres arrivent !";
			link.l1.go = "gunner_3_1";
		break;
		
		case "gunner_3_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");//
			dialog.text = "Aye-aye, Commandant ! Chargez une bombe ! Prêt ! Feu à mon commandement !";
			link.l1 = "...";
			link.l1.go = "gunner_3_2";
			npchar.quest.canonada = "4";
		break;
		
		case "gunner_3_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_02", 5.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_5":
			PlaySound("types\warrior04.wav");
			PlaySound("Voice\English\evilpirates06.wav");
			dialog.text = "Ha-ha-ha, les salauds nous ont tourné le dos ! Viande de chien ! Le mitraille les écrase à une telle distance ! On dirait qu'ils n'ont pas assez de courage pour nous attaquer à nouveau !";
			link.l1 = "Maintenant c'est à notre tour. Randolph, tu resteras ici près du canon. Tire quelques fois sur le chemin, puis vise la fumée - brûle leur repaire ! Mais ne nous tire pas dessus.";
			link.l1.go = "gunner_5_1";
		break;
		
		case "gunner_5_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Oui-oui, Commandant ! Préparez le canon ! Chargez une bombe !";
			link.l1 = "Hommes! Aux armes! Suivez-moi, attaquez! Hourra!!";
			link.l1.go = "attack";
		break;
		
		case "attack":
			DialogExit();
			n = Findlocation("mine");
			Locations[n].hidden_fire = true;
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			if (GetCharacterIndex("Svensons_sold_12") != -1 && pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=8; i++)
			{
				if (GetCharacterIndex("Ourmine_sold_"+i) != -1)
				{
					sld = characterFromId("Ourmine_sold_"+i);
					if (i == 1) sld.MusketerDistance = 10; 
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_NEITRAL);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_05Die");
			AddDialogExitQuest("MainHeroFightModeOn");	
			DoQuestCheckDelay("Saga_MineSetMusic", 0.3);
			// запускаем автобабахалку на 10 выстрелов
			iTotalTemp = 0;
			DoQuestCheckDelay("Saga_GunAutoFire", 7.0);
			bDisableCharacterMenu = false;//разлочим интерфейсы
			InterfaceStates.Buttons.Save.enable = true;//разрешим сохраняться
		break;
		
		case "convict":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = LinkRandPhrase("Ne me fais pas de mal, je ne suis pas l'un d'eux ! Tue les bandits !","Libère-nous, camarade ! Et tue-les tous !","Coupe-les, ami, coupe-les! Fais-les périr!");
				link.l1 = "Ha ! Ne t'inquiète pas, c'est exactement ce que nous faisons en ce moment.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Notre esclavage est-il terminé ? Nous libérerez-vous ?","Héhé, ai-je vraiment réussi à survivre jusqu'à ce jour ?","Les salauds nous ont saigné à blanc....");
				link.l1 = "Je pense que tu pourras bientôt profiter de ta liberté, camarade...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "convict";
		break;
		
		// жена Яна Свенсона
		case "js_girl":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Vous feriez mieux de quitter cet endroit, Monsieur. Nous ne protégeons pas les criminels et nous ne voulons pas de conflits avec les autorités de la colonie.";
				link.l1 = "D'accord, je m'en vais...";
				link.l1.go = "exit";
				NextDiag.TempNode = "js_girl";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				// Первый диалог с Элен
				if(startHeroType == 4)
				{
					dialog.text = "Ah, Helene. Tu aurais pu t'habiller un peu plus décemment avant de venir voir Jan, plutôt que de lui montrer qui tu es vraiment. C'est dommage qu'il ne me croie pas.";
					link.l1 = "Et comment suis-je exactement ? Il m'a aidée à me élever depuis l'enfance et me connaît mieux que quiconque. Je n'ai aucun secret pour lui. Je souffre de cette chaleur depuis que je suis enfant, alors j'ai dû m'y habituer à ma manière, c'est tout.";
					link.l1.go = "js_helen_ft";
					NextDiag.TempNode = "js_girl";
					NPChar.quest.meeting = "1";
					break;
				}
				dialog.text = TimeGreeting()+", Monsieur. Voulez-vous voir Jan ?";
				link.l1 = "Bonjour. C'était un plaisir de vous rencontrer, Mademoiselle ?..";
				link.l1.go = "js_girl_1";
			}
			else
			{
				// заглушка элен
				if(startHeroType == 4)
				{
					dialog.text = "Jan est à l'intérieur. Vas-y, il n'y a rien à voir ici, et tu commences à me taper sur les nerfs.";
					link.l1 = "Je n'étais pas vraiment d'humeur de toute façon.";
					link.l1.go = "exit";
					NextDiag.TempNode = "js_girl";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Joan")) {
					dialog.text = "Grrr !";
					link.l1 = "Et une bonne santé à vous aussi, Madame Svensson.";
					link.l1.go = "exit";
					break;
				}
				
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
				{
					dialog.text = TimeGreeting()+", Capitaine "+GetFullName(pchar)+"Si vous êtes ici pour Jan, alors je dois vous décevoir - il n'est pas là. Il est parti mener quelque affaire importante.";
					link.l1 = "Merde ! Et j'ai besoin de lui ! Dites-moi, Madame Svenson, vous a-t-il dit quand il sera de retour ?";
					link.l1.go = "js_girl_3";
					break;
				}
				dialog.text = "A-ah,   vous encore, Capitaine "+GetFullName(pchar)+"... circulez, Jan est à l'étage, comme d'habitude.";
				link.l1 = "Merci, Madame Svenson...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_1":
			dialog.text = "Madame, Madame Johanna Svenson.";
			link.l1 = "Capitaine "+GetFullName(pchar)+".";
			link.l1.go = "js_girl_2";
		break;
		
		case "js_girl_2":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				dialog.text = "Capitaine ? Eh bien, je suis heureux de vous accueillir dans ma maison. Mais si vous êtes ici pour Jan, je dois vous décevoir - il n'est pas là. Il est parti s'occuper de quelques affaires importantes.";
				link.l1 = "Merde ! Et j'ai besoin de lui ! Dites-moi, Madame Svenson, vous a-t-il dit quand il va revenir ?";
				link.l1.go = "js_girl_3";
				break;
			}
			dialog.text = "Capitaine ? Eh bien, je suis ravie de vous accueillir dans ma maison. Mon mari est au deuxième étage dans son bureau. Montez à l'étage.";
			link.l1 = "J'ai compris, Madame Svenson...";
			link.l1.go = "exit";
			NPChar.quest.meeting = "1";
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_3":
			dialog.text = "Non. Il ne m'a même pas dit la date exacte de son retour, car il ne sait pas lui-même combien de temps durera la recherche.";
			link.l1 = "Je suis désolé d'intervenir, mais j'ai vraiment besoin de lui... Quelle recherche mène-t-il ?";
			link.l1.go = "js_girl_4";
		break;
		
		case "js_girl_4":
			dialog.text = "Je vais te le dire. La charmante Hélène, aussi connue sous le nom de Rumba, fille de feu son ami Sean McArthur, a disparu. Jan traite cette jeune diablesse comme si elle était sa propre fille. Elle lui rappelle son ancien amour, qui avait le même tempérament téméraire. Du moins, c'est la raison de l'attraction, je crois.\nQuoi qu'il en soit, la fille a disparu il y a une semaine avec sa goélette 'Arc-en-ciel' et tout son équipage. Sean McArthur lui a appris la navigation et l' 'Arc-en-ciel' lui a été léguée par testament. Et maintenant, elle joue au capitaine...";
			link.l1 = "Que pourrait-il lui être arrivé ?";
			link.l1.go = "js_girl_5";
		break;
		
		case "js_girl_5":
			dialog.text = "Qui sait... Une semaine, ce n'est pas si long, mais la veuve McArthur est convaincue qu'il est arrivé quelque chose à sa fille et elle a réussi à convaincre Jan aussi. Il a rassemblé ses hommes et a commencé à la chercher lui-même, sans résultat pour l'instant. Personnellement, je pense qu'Hélène va bien et que Jan se torture pour rien.\nIl a trop écouté les sornettes de cette vieille femme grosse et s'est affolé. La fille s'amuse très probablement avec un autre galant à cet instant, loin des regards indiscrets dans un endroit sûr. Elle rentrera dès qu'elle aura apaisé sa faim.";
			link.l1 = "Johanna, où puis-je trouver Gladys ? Je veux lui parler...";
			link.l1.go = "js_girl_6";
		break;
		
		case "js_girl_6":
			dialog.text = "Sa maison est près du quai, sur la gauche. Mais elle n'y est probablement pas. Elle perd son temps chaque jour à se tenir sur les murailles du fort, à chercher sa précieuse fille.";
			link.l1 = "Je vois. Merci beaucoup pour vos informations !";
			link.l1.go = "js_girl_7";
		break;
		
		case "js_girl_7":
			DialogExit();
			NextDiag.CurrentNode = "js_girl_8";
			sld = characterFromId("Gladis"); //устанавливаем Глэдис на форт
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "js_girl_8":
			dialog.text = "Jan n'est pas encore là, Capitaine, alors revenez plus tard.";
			link.l1 = "Je vois...";
			link.l1.go = "exit";
			NextDiag.TempNode = "js_girl_8";
		break;
		
		case "js_helen_ft":
			dialog.text = "You're always in heat, I'd say. You should go to church; I've barely ever seen you there.";
			link.l1 = "Ma conscience est tranquille - je n'ai rien à demander pardon. Toujours amère qu'il ait aidé à approvisionner mon navire au lieu d'acheter une autre robe pour toi, Joanna ?";
			link.l1.go = "js_helen_ft_1";
		break;
		
		case "js_helen_ft_1":
			dialog.text = "Moi ? Amer ? Tu n'en vaux pas la peine. C'est juste que tout te vient trop facilement, et tu ne le mérites pas.";
			link.l1 = "Mais dès que j'ai eu ce navire, j'ai commencé à gagner ma vie tout seul. Et depuis qu'il t'a ramassé comme un chat de gouttière, tu n'as pas travaillé un seul jour. Alors, qui vit vraiment à ses crochets ?";
			link.l1.go = "js_helen_ft_2";
		break;
		
		case "js_helen_ft_2":
			dialog.text = "Continue à parler ainsi, et un jour tu recevras ce qui te revient. Jan et Gladys auraient dû t'apprendre les bonnes manières. Très bien, vas-y, dis ce que tu as à dire - et disparais de ma vue, Hélène. Il est à l'intérieur.";
			link.l1 = "Stupide poule. Bien sûr, ça sera fait.";
			link.l1.go = "exit";
		break;
		
		// хронометр Алекса
		case "Alexs_bandos":
			dialog.text = "Hé ! Que fais-tu ici ?";
			link.l1 = "Je voudrais te poser la même question - que fais-tu ici avec tes compagnons, dans mon cachot?";
			link.l1.go = "Alexs_bandos_1";
		break;
		
		case "Alexs_bandos_1":
			dialog.text = "Ha ! Ton cachot ? Et quand est-il devenu le tien, pédé ?";
			link.l1 = "Le jour où ton père a fait l'erreur de baiser ta mère.";
			link.l1.go = "Alexs_bandos_2";
		break;
		
		case "Alexs_bandos_2":
			dialog.text = "Tu cherches des ennuis ?";
			link.l1 = "Écoute, mon pote, je te donne une dernière chance de quitter cet endroit. C'est mon cachot et je ne laisserai personne y entrer librement, tu comprends ? Il me suffit de siffler une fois, et la moitié des pirates d'Isla Tesoro sera ici en une minute.";
			link.l1.go = "Alexs_bandos_3";
		break;
		
		case "Alexs_bandos_3":
			dialog.text = "Eh bien, nous allons essayer de te faire taire alors !";
			link.l1 = "Ha-ha ! Tu es pathétique, vermine !";
			link.l1.go = "Alexs_bandos_4";
		break;
		
		case "Alexs_bandos_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Bermudes_Dungeon")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Alexs_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int iScl = 25+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Alexs_bandos_5", "mush_ctz_8", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2+50);
			ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "AlexClock_BandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "helendrinking_gypsy":
			dialog.text = "Attends un instant, faucon !";
			link.l1 = "Pas le meilleur moment, ma douce.";
			link.l1.go = "helendrinking_gypsy_1";
		break;
		
		case "helendrinking_gypsy_1":
			dialog.text = "Oh, tu te trompes, beau gosse. Cette fille t'aime bien, et ce sentiment est mutuel, je le vois.";
			link.l1 = "Pas la meilleure recommandation... D'accord, que veux-tu ? Une aumône ?";
			link.l1.go = "helendrinking_gypsy_2";
		break;
		
		case "helendrinking_gypsy_2":
			dialog.text = "Je veux vous offrir mon soutien dans votre entreprise ardue. Regardez ça ! Une chope magique et une pommade interdite. La chope vous aidera dans les affaires de boisson, et la pommade - dans les affaires d'amour. Que choisirez-vous ? Seulement deux mille !";
			link.l1 = "Je n'ai besoin de rien - j'ai déjà donné un tas d'argent à des gens comme toi.";
			link.l1.go = "helendrinking_gypsy_refuse";
			if (sti(pchar.money) >= 2000) {
				link.l2 = "Un onguent interdit, tu dis ? Eh bien, je ne suis pas un saint, je l'admets. Donne-le-moi.";
				link.l2.go = "helendrinking_gypsy_fuck";
				link.l3 = "Une chope ? Ai-je l'air d'un ivrogne ? Eh bien, qui est-ce que je berne... Je la prends !";
				link.l3.go = "helendrinking_gypsy_drink";
			}
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_refuse":
			dialog.text = "Beau mais insensé. Envole-toi donc, faucon.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_drink":
			dialog.text = "Oh, ne le cache pas dans tes poches sans fond ! Envole-toi, faucon, et ne pèche pas !";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_01");
			Log_Info("Talisman 'Throat of cast iron' acquired!");
			PlaySound("interface\important_item.wav");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_fuck":
			dialog.text = "Oh, ne le cache pas dans tes poches sans fond ! Envole-toi, faucon, et ne pèche pas !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_03");
			Log_Info("Talisman 'Cupid's Balm' acquired!");
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			notification("Helen disapproves", "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_joan":
			dialog.text = "Ah ! Sors d'ici, vaurien ! Combien de fois t'ai-je dit de ne pas entrer chez moi ! Et qui est-ce ?";
			link.l1 = "Madame, nous nous connaissons déjà.";
			link.l1.go = "helendrinking_joan_1";
		break;
		
		case "helendrinking_joan_1":
			dialog.text = "Monsieur de Maure ? Eh bien, c'est charmant ! C'est ainsi que vous faites affaire avec mon mari ?! Je le savais ! J'avais prévenu Jan : un jour cette traînée commencera à détourner ses hommes ! Et qu'avez-vous dans vos mains ?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog1");
		break;
		
		case "helendrinking_joan_2":
			dialog.text = "Wha-a-a-at?! How dare you, wretch?! You're not going anywhere; my husband will be here any moment now and he'll teach you how to talk to the elders!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog3");
		break;
		
		case "helendrinking_fort_officer":
			dialog.text = "Que se passe-t-il ici ? Mademoiselle MacArthur ! J'avais un grand respect pour votre père, et M. Svensson est notre ami... Mais ne vous souvenez-vous pas comment tout cela s'est terminé la dernière fois ?\nC'est décevant, parole d'officier, décevant ! Vous auriez pu nous inviter !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog");
		break;
		
		case "helendrinking_fort_officer_1":
			dialog.text = "Je vous remercie pour votre hospitalité, Mademoiselle MacArthur. Permettez-moi de dire que nous sommes tous très heureux de vous revoir parmi nous. Ce qui s'est passé est un grand mystère, mais il n'est pas surprenant que la ville en ait eu vent. Toutefois, je peux vous assurer que personne ne colportera de ragots. Je vous présente mes plus sincères excuses pour le comportement récent de l'un de nos capitaines. Et je tiens à vous remercier tout particulièrement, Monsieur de Maure.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog3");
		break;
		
		case "helendrinking_fort_officer_2":
			dialog.text = "Tout ira bien, Mademoiselle. Monsieur de Maure, je serai franc - bien que Donovan se conduise comme un véritable scélérat et bandit, la flotte ne le condamnera jamais ouvertement. Plus probablement, ils le défendront même. Votre petite expédition a été mentionnée dans les rapports et a considérablement compliqué les relations entre nos pays. Néanmoins, compte tenu de l'influence de Monsieur Svensson, ainsi que des concessions remarquables qui vous ont été faites par Capsterville, vous n'avez rien à craindre.";
			link.l1 = "C'est splendide. Je dis que nous devrions boire à cela !";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog1");
		break;
		
		case "helendrinking_poorman":
			dialog.text = "Excusez-moi, fort obligeamment, qu'en est-il du travail ?";
			link.l1 = "Es-tu encore là ?";
			link.l1.go = "helendrinking_poorman_1";
		break;
		
		case "helendrinking_poorman_1":
			dialog.text = "Mon cher monsieur, où pourrais-je aller d'autre? Je suis juste allé me soulager, j'ai entendu votre conversation sentimentale, et je me suis un peu réchauffé. Émotionnellement, je veux dire!";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.BoughtRainbow")) {
				link.l1 = "Bon Dieu ! Eh bien, puisque je t'ai donné ma parole, il n'y a pas d'autre choix. Va, prends le commandement.";
				link.l1.go = "helendrinking_poorman_bought";
			} else {
				link.l1 = "Je n'ai pas de travail pour vous, monsieur.";
				link.l1.go = "helendrinking_poorman_notbought";
			}
		break;
		
		case "helendrinking_poorman_bought":
			dialog.text = "Oui, oui, Capitaine !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helendrinking_poorman_notbought":
			dialog.text = "Dommage ! Quoi qu'il en soit, merci pour le festin, Capitaine !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helensleep_amelia_mary":
			dialog.text = "Au nom du Père et du Fils et du Saint-Esprit... entre, mon fils.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Bonjour, Mere Amelia. Vas-tu me crier dessus aussi ?";
				link.l1.go = "helensleep_amelia_mary_know";
			} else {
				link.l1 = "Disparaissez ! Quel genre de cauchemar est-ce ? Que se passe-t-il ? Suis-je en train de rêver ?";
				link.l1.go = "helensleep_amelia_mary_notknow";
			}
		break;
		
		case "helensleep_amelia_mary_know":
			dialog.text = "Non, mon petit faucon. Et pardonne à Jan - le pauvre homme s'est agité. Mais oui, je veux te gronder. Pourquoi es-tu venu à l'église ? Pour te repentir de tes péchés ? Ou étais-tu après la rousse ?";
			link.l1 = "Je ne me connais pas moi-même...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "L'as-tu vue aussi ? Elle a capté mon regard.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_mary_notknow":
			dialog.text = "Disparais-toi. Nous aurions dû nous rencontrer déjà, mais tu fais traîner les choses. Pourquoi es-tu venu à l'église ? Pour te repentir de tes péchés ? Ou étais-tu après la rousse ?";
			link.l1 = "Je ne sais pas moi-même...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "L'avez-vous vue aussi ? Elle a attiré mon regard.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen":
			dialog.text = "Bonjour, mon faucon. La réception n'a pas encore commencé, attendez en ligne, s'il vous plaît.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Bonjour, Votre Excellence. Allez-vous me crier dessus aussi ?";
				link.l1.go = "helensleep_amelia_helen_know";
			} else {
				link.l1 = "Disparaissez ! Quel genre de cauchemar est-ce ? Que se passe-t-il ? Suis-je en train de rêver ?";
				link.l1.go = "helensleep_amelia_helen_notknow";
			}
		break;
		
		case "helensleep_amelia_helen_know":
			dialog.text = "No, my falcon. And forgive Jan, the poor man got worked up. No need to scold you; you did everything right - didn't go after the red-haired one to the church. Good boy!";
			link.l1 = "Recevoir des éloges, c'est plaisant. Surtout quand on sait clairement pourquoi.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Tu l'as vue aussi ? Elle a attiré mon regard.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen_notknow":
			dialog.text = "Disparais-toi. Nous aurions déjà dû nous rencontrer, mais tu traînes tout. Viens ici, je vais te féliciter - tu n'as pas suivi la rousse jusqu'à l'église. Bon garçon !";
			link.l1 = "Recevoir des éloges, c'est plaisant. Surtout quand on sait pourquoi.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Tu l'as vue aussi ? Elle a attiré mon regard.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia":
			dialog.text = "Je ne vais pas t'ennuyer avec les détails, idiot, mais je te dirai ceci : tu es destiné à devenir une grande personne. Tu causeras beaucoup de mal, mais bien plus de bien. Cependant, le bonheur ne t'est pas garanti. Le bonheur, mon faucon, n'est donné qu'à ceux qui suivent leur chemin sans dévier. Et une femme fidèle t'aidera à ne pas dévier.\nTu en auras deux, et toutes deux apporteront le bonheur, mais tu dois choisir celle aux cheveux clairs.";
			link.l1 = "Pourquoi donc ? Je déciderai moi-même !";
			link.l1.go = "helensleep_amelia_1";
		break;
		
		case "helensleep_amelia_1":
			dialog.text = "Bien sûr, choisis pour toi-même, mais la blonde est meilleure. Nous l'avons décidé ainsi.";
			link.l1 = "Qui sommes-nous ?";
			link.l1.go = "helensleep_amelia_2";
		break;
		
		case "helensleep_amelia_2":
			dialog.text = "Cette pauvre fille ne connaît même pas son vrai nom. Prononce-le, et elle sera tienne. Ainsi dit-on.";
			link.l1 = "Je ne comprends plus rien.";
			link.l1.go = "helensleep_amelia_3";
		break;
		
		case "helensleep_amelia_3":
			dialog.text = "Entends-tu ce tapotement ? Ouvre, et ne te trompe pas.";
			link.l1 = "En effet, quelqu'un frappe... Entrez !";
			link.l1.go = "exit";
			
			PlaySound("interface\knock.wav");
			
			AddDialogExitQuestFunction("HelenSleep_WakeUp");
		break;
		
		case "helendrinking_notifier":
			dialog.text = "Monsieur, M. Svensson a demandé que vous lui consacriez un peu de votre temps.";
			link.l1 = "Merde, cela ne présage rien de bon. Je vais essayer, mais sans promesses.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_End");
		break;
		
		case "islatesoro_pirate1":
			dialog.text = "Jour de chance, les gars ! Je vous avais dit qu'elle viendrait ici tôt ou tard, non ? Allez, ma belle, rends-nous les armes et viens avec nous.";
			link.l1 = "Vous vous trompez, les gars. Elle est avec moi.";
			link.l1.go = "islatesoro_pirate1_1";
		break;
		
		case "islatesoro_pirate1_1":
			dialog.text = "Ne te mêle pas de ça, ou je te tirerai dessus comme un chien. Il y a une belle somme offerte pour la fille, et nous sommes des gars affamés, dépourvus de principes.";
			link.l1 = "Continuez à me parler sur ce ton, et je résoudrai votre problème de faim de façon permanente.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroSpawnSecond");
		break;
		
		case "islatesoro_pirate1_2":
			dialog.text = "Es-tu devenu complètement fou, Lucky ? Nous l'avons trouvée en premier ! Tu ferais mieux d'avoir une bonne raison de me jacasser avec ta bouche stupide !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog1");
		break;
		
		case "islatesoro_pirate1_3":
			dialog.text = "You're the rat here! We had just torn a big fat Spaniard apart; we can sit on our asses for a year!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog3");
		break;
		
		case "islatesoro_pirate2":
			dialog.text = "Eh bien, regardez qui nous avons là. Allez, tout le monde, dégagez, et vous, madame, venez avec nous.";
			link.l1 = "Bonjour, ami.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog");
		break;
		
		case "islatesoro_pirate2_1":
			dialog.text = "Nous sommes plus nombreux que toi, et nous sommes plus coriaces, Danois. Quelle autre raison te faut-il, rat de cale ? Cela fait six mois que tu n'as pas vu de prise décente, et tu manges des miettes de pain sur la table de Vuazie !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog2");
		break;
		
		case "islatesoro_pirate2_2":
			dialog.text = "";
			link.l1 = "On dirait qu'il n'y aura pas de résolution pacifique ici.";
			link.l1.go = "islatesoro_pirate_a";
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB")) {
				link.l2 = "Que dis-tu? Chanceux? J'ai entendu une rumeur selon laquelle lui et Vuazie ont conspiré pour te donner des conseils douteux. Cela explique ta série de malchance en mer.";
				link.l2.go = "islatesoro_pirate_b";
			}
			bOk = (!CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice")) || (pchar.questTemp.Mtraxx.Retribution.Choice == "bad");
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC") && CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold") && bOk) {
				link.l3 = "Je suis las de cette farce. Isla Tesoro, écoutez-moi ! Qui était avec moi à Carthagène ?! Qui a brûlé Mérida avec moi ?! Ces rats osent s'en prendre au Prince Charlie en personne ! Montrons-leur, les gars !";
				link.l3.go = "islatesoro_pirate_c";
			}
		break;
		
		case "islatesoro_pirate_a":
			dialog.text = "Tu es encore là, méduse ? Très bien, les gars, allons-y : attachez le capitaine, et on s'occupera de la fille plus tard, compris ?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog4");
		break;
		
		case "islatesoro_pirate_a_1":
			dialog.text = "Bien sûr, répandons un peu de sang au moins. Hehe.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroA");
		break;
		
		case "islatesoro_pirate_b":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedB = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 60) {
				dialog.text = "Quoi ?! Diable, je savais que tu complotais avec ce scélérat à lunettes ! Tranchez-les tous, les gars, et on ramassera la fille plus tard !";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroB");
			} else {
				dialog.text = "De quoi tu jacasses, capitaine ? Dégage pendant que les gens respectables discutent affaires.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "islatesoro_pirate_c":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedC = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 50) {
				DialogExit();
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroC");
			} else {
				dialog.text = "Qu'est-ce que tu jacasses, Capitaine ? J'ai vu Charlie Prince, et tu ne lui arrives pas à la cheville. Dégage pendant que les gens respectables discutent affaires.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "francois":
			dialog.text = "Charles de Maure ? Fils d'Henri de Monpe ?";
			link.l1 = "C'est exact, monsieur. Et qui êtes-vous ?";
			link.l1.go = "francois_1";
		break;
		
		case "francois_1":
			dialog.text = "Colonel Francois de Tavanne. You may consider this a direct challenge, monsieur; the gauntlet for the duel has been laid. I don't even wish to dirty my hands with you, but I swear, my blade will taste your blood!";
			link.l1 = "Un duel ? Dans ce cas, vous devrez faire bien plus d'efforts, Colonel. En ce moment, on pourrait vous confondre avec un brigand, et par ici, la conversation avec ces gens-là est brève ! Expliquez-vous !";
			link.l1.go = "francois_2";
		break;
		
		case "francois_2":
			dialog.text = "Vous avez séduit ma femme, monsieur ! Tandis que je répandais mon sang pour le roi et la patrie, vous... vous vous amusiez avec ma femme !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog");
		break;
		
		case "francois_3":
			dialog.text = "Silence, madame. Votre tenue audacieuse déshonore toute femme, bien que vous sembliez tout à fait appropriée à côté de cet indigne séducteur de noble dame !";
			link.l1 = "Ce n'est toujours pas une raison suffisante pour un duel, Colonel. Et puis-je souligner que vous vous conduisez tout aussi indignement ici.";
			link.l1.go = "francois_4";
		break;
		
		case "francois_4":
			dialog.text = "Est-ce insuffisant? J'ai enquêté - à ma place pourrait se trouver une douzaine de maris nobles, monsieur. Mais si vous voulez les détails, alors à ma honte, je confesse que l'une de vos passions fut Lulu de Tavann, la plus belle et honnête des femmes!";
			link.l1 = "Lulu, tu dis... Et comment va-t-elle ?";
			link.l1.go = "francois_5";
		break;
		
		case "francois_5":
			dialog.text = "Silence ! Ma femme, incapable de supporter le tourment que tu as infligé, est récemment décédée ! J'ai passé presque un an et une fortune à te retrouver, scélérat ! Assez de mots ! Soit tu acceptes le défi, soit je te tue comme un chien. Richard ! Sois mon témoin !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog2");
		break;
		
		case "francois_6":
			dialog.text = "Silence, monsieur ! Acceptez le défi ou perdez les derniers vestiges d'honneur qu'il vous reste !";
			if (pchar.HeroParam.HeroType == "HeroType_1") {
				link.l1 = "Un duel est un duel. Je ne vais pas mentir, j'apprécie ceux-ci. Capitaine, transmettez au colonel qu'il est temps pour lui de commander un cercueil approprié.";
			} else {
				link.l1 = "Tu veux te battre ? Tu en auras pour ton compte ! Capitaine, dis au colonel qu'il est temps pour lui de commander un cercueil approprié.";
			}
			link.l1.go = "francois_duel";
			link.l2 = "Ce n'est pas l'Europe, Colonel. L'honneur aux Caraïbes est plus difficile à gagner mais pas si facile à perdre non plus. Je refuse votre duel parce que je ne le veux tout simplement pas.";
			link.l2.go = "francois_refuse";
		break;
		
		case "francois_7":
			dialog.text = "Ton père est déjà à un pas de la tombe, ordure ! Et je m'assurerai qu'il connaisse ta lâcheté !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog7");
		break;
		
		case "richard":
			dialog.text = "Colonel, je confirme votre droit à un duel, mais je n'autoriserai pas du simple banditisme ! Monsieur de Maure, je suis le Capitaine Richard Small. Êtes-vous prêt à donner satisfaction au Colonel de Tavann ?";
			link.l1 = "Un instant, Capitaine. Je connaissais bien Lulu... et elle... avait tendance à changer d'admirateurs fréquemment, et sa santé était meilleure que la mienne... Comment est-elle morte, Colonel ? Avant ou après votre retour chez vous ?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog3");
		break;
		
		case "richard_1":
			dialog.text = "Je vous en prie, Francois, permettez-moi. Monsieur de Maure, vous avez été défié. La société des officiers de Blueweld a reconnu que la demande de satisfaction du Colonel de Tavann est justifiée. Acceptez le défi ou perdez votre honneur.";
			link.l1 = " ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog5");
		break;
		
		case "richard_2":
			dialog.text = "Charles, s'il te plaît, nous sommes des gentilshommes ici. Cela ne convient pas. Le Colonel a voyagé si loin pour te rencontrer ! C'est un scandale !";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog8");
		break;
		
		case "richard_3":
			dialog.text = "O-oui, bien sûr, mademoiselle. Mais je vais...";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "helen");
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath1");
		break;
		
		case "richard_4":
			dialog.text = "Capitaine de Maure, le jour est à vous ! Pas le combat le plus propre, mais vous avez défendu votre honneur aujourd'hui.";
			link.l1 = "Avez-vous dit quelque chose, Capitaine ? Je pourrais peut-être caser un autre duel dans mon emploi du temps d'aujourd'hui.";
			link.l1.go = "richard_5";
		break;
		
		case "richard_5":
			dialog.text = "Mes excuses, Capitaine. Ce sont juste les nerfs!";
			link.l1 = "Je pense que ta présence ici n'est plus nécessaire.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory");
		break;
		
		case "richard_duel":
			dialog.text = "Une décision équitable ! Même si elle n'a pas été présentée de la manière la plus digne... Messieurs ! Commençons !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuel");
		break;
		
		case "alonso":
			dialog.text = "Capitaine, je ne comprends peut-être pas tous ces grands mots que ces dignitaires balancent, mais voyez-vous, si quelqu'un est traité de lâche, on ne le laisse généralement pas s'en tirer aussi facilement. Frappez le gars, Capitaine, sinon notre équipage va s'inquiéter.";
			link.l1 = "Vous voulez du sang ? La vie est trop ennuyeuse, pas d'excitation ? Vous aurez votre sang, bande d'animaux !";
			link.l1.go = "francois_duel";
			link.l2 = "Ouah ouah, j'ai tellement peur. Avez-vous terminé ici, messieurs ? J'ai des endroits où aller.";
			link.l2.go = "alonso_refuse";
		break;
		
		case "alonso_1":
			dialog.text = "It won't look good if our captain backs down from a public challenge. Just give that nobleman a good whack; we know you're great with a sword!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog9");
		break;
		
		case "alonso_refuse":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog6");
		break;
		
		case "francois_refuse":
			dialog.text = "Lâche ! Libertin ! Rat ! As-tu peur, vaurien ? Avez-vous tous été témoins de cela ?! Richard, je le tuerai de toute façon !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog4");
		break;
		
		case "francois_duel":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuelDialog");
		break;
		
		case "francois_sit":
			dialog.text = "Sa-salaud ! Ça va, j'ai l'habitude des blessures. Je vais m'en remettre, et...";
			link.l1 = "On dirait une menace, Colonel. Et je ne prends pas les menaces à la légère.";
			link.l1.go = "francois_sit_kill";
			link.l2 = "Une fois rétabli, n'oubliez pas de vous vanter des circonstances de votre blessure auprès de la communauté des officiers.";
			link.l2.go = "francois_sit_taunt";
		break;
		
		case "francois_sit_kill":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			notification("Helen disapproves", "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_FinishFrancois");
		break;
		
		case "francois_sit_taunt":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			notification("Helen approves", "Helena");
			AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 300);
			AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 300);
			
			AddDialogExitQuestFunction("HelenDrinking_SpareFrancois");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenSleep_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}
