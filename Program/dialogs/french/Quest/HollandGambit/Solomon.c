// Соломон Шнеур - старый еврей
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
//--------------------------------------за Голландию------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyFather")
				{
					dialog.text = "Que veux-tu de ce vieux Juif, jeune homme ?";
					link.l1 = "Salomon, j'ai besoin que tu te concentres et te souviennes de l'île perdue sur laquelle tu as fait naufrage. Tu y as caché un trésor. J'ai parlé avec ta fille. Mon patron Lucas Rodenburg m'a donné carte blanche pour agir dans l'intérêt de ta famille. À mon avis, la chose la plus importante pour toi en ce moment est de récupérer le capital de ta famille, et tu n'auras pas une once de cet or sans mon aide.";
					link.l1.go = "SolomonBonanza";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && int(Pchar.money) >= 200000)
				{
					dialog.text = "Oh, mon jeune homme, c'est toi ? Ne peux-tu pas me dire quelque chose de bon ? Êtes-vous des chrétiens ici pour tourmenter ce pauvre vieux juif avec encore des questions ?";
					if (CheckCharacterItem(pchar, "SkullAztec"))
					{
						link.l1 = "J'ai trouvé l'île, bien que ce fût assez difficile. J'ai aussi trouvé votre coffre avec l'argent et ce crâne. Je suppose que c'est le crâne de votre grand-père-patriarche, peu importe ce dont vous parliez.";
						link.l1.go = "SolomonBonanza_2";
					}
					link.l2 = "J'ai trouvé l'île, bien que cela n'ait pas été chose aisée. J'ai aussi trouvé votre coffre avec l'argent. Mais il n'y avait pas de crânes dans ce coffre.";
					link.l2.go = "SolomonBonanza_3";
					link.l3 = "Non, je n'ai pas de questions pour le moment.";
					link.l3.go = "exit";
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "GiveLucasMoney" && GetQuestPastDayParam("questTemp.HWIC.Holl.LucasMoney") > 7)
				{
					dialog.text = "Oh, mon jeune homme, c'est toi ? Peux-tu me dire quelque chose de bon ? Ou vas-tu encore tourmenter ce pauvre vieux Juif avec des questions ?";
					link.l1 = "J'ai trouvé l'île, bien que ce fût assez difficile. J'ai également trouvé votre coffre avec l'argent. Le voici.";
					link.l1.go = "SolomonBonanza_5";
					break;
				}
				dialog.text = "Bonjour, jeune homme. Que veux-tu de ce pauvre vieux juif ?";
				link.l1 = "Bon après-midi. Non, rien, je suis juste venu dire bonjour.";
				link.l1.go = "exit";
				break;
			}
//----------------------------------------за Англию-----------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "toAbigile")
				{
					dialog.text = "Bon après-midi, jeune homme. Je vois que tu es venu pour une raison... Que veux-tu ? Vais-je en tirer quelque chose ou ai-je raté quelque chose ?";
					link.l1 = "Bon après-midi, Solomon. Je voudrais parler à Abigail.";
					link.l1.go = "Solomon_treasure";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Bonjour, jeune homme. Que veux-tu de ce pauvre vieux Juif ?";
				link.l1 = "Bon après-midi, Solomon. Rien, je suis juste venu te saluer.";
				link.l1.go = "exit";
				break;
			}
//-----------------------------------------против всех-------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "Bonjour, jeune homme. Je vois que vous êtes ici pour une raison... Que désirez-vous ? Est-ce que j'en retire quelque chose ou ai-je manqué quelque chose ?";
					link.l1 = "Je dois parler à Abigail. J'ai une lettre pour elle.";
					link.l1.go = "Abigile_kidnap";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDayOver")
				{
					dialog.text = "Bonjour jeune homme. Que veux-tu? Une autre lettre pour ma fille?";
					link.l1 = "Non. Où est Abigail ?";
					link.l1.go = "Abigile_GoOver";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistory")
				{
					dialog.text = "Eh bien... Parles-tu de mon argent, jeune homme ?";
					link.l1 = "Oui, monsieur. A propos de l'argent que vous avez caché sur une île. Est-il vrai que vous et Abigail ne vous souvenez pas de son emplacement ?";
					link.l1.go = "Solomon_history";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryAfter")
				{
					dialog.text = "D'accord. Je me souviens du flûte et de son capitaine. Je l'avais même déjà vu une fois à Amsterdam. Le flûte s'appelait 'Leiden' et le capitaine s'appelait Toff Keller.";
					link.l1 = "C'est un début ! J'ai une piste maintenant.";
					link.l1.go = "Solomon_history_3";
					pchar.questTemp.HWIC.Self = "SolomonHistoryEnd";
					break;
				}
				dialog.text = "Oy vey, que veux-tu de ce pauvre vieux Juif cette fois-ci ?";
				link.l1 = "Bon après-midi. Non, rien, je suis juste venu dire bonjour.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Oy vey, que veux-tu de ce pauvre vieux Juif cette fois ?";
			link.l1 = "Bon après-midi. Non, rien, je suis juste venu dire bonjour.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-----------------------------------------------За Голландию-----------------------------------
		case "SolomonBonanza":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "Et que voulez-vous de moi ? Ai-je l'air d'un homme qui sait quelque chose ? Comment pourrais-je savoir qu'en un jour aussi maudit par Dieu, il y avait exactement un terrain avec des marchandises et de l'or à prendre là-bas ? Imaginez combien de gentils là-bas dans les rues veulent déjouer un Juif comme moi et prendre mon argent !\nIl y a une île. Pas un seul homme là-bas, à part Abi et moi. Pas un seul. Personne du tout. Il y avait une grotte au milieu. J'ai mis mon coffre là-bas pour le sauver de ce pirate goyim Amalek ! Un coffre rempli d'or, pas une babiole parmi eux. Je l'ai trimballé depuis le Vieux Pays ! Tout ce que j'ai gagné à la sueur de mon front est là. En plus, le crâne de mon grand-père... Croyez-moi, cette chose nous a sauvés, oui-oui\nOh-ho-ho, c'est un ancien talisman chargé de magie talmudique ! Que Dieu nous sauve d'Amalek ! Oy vey, c'est difficile de recommencer à cet âge des gentils ! J'aimerais que vous sachiez, jeune homme ! Oh, j'aimerais que vous sachiez !";
			link.l1 = "Qu'est-ce que tu baragouines, espèce de fou ? Peu m'importe. Je m'en occuperai moi-même. Adieu !";
			link.l1.go = "SolomonBonanza_1";
		break;
		
		case "SolomonBonanza_1":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbySeekIsland";
			pchar.quest.Joakim_meeteng.win_condition.l1 = "location";
			pchar.quest.Joakim_meeteng.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Joakim_meeteng.function = "Create_Joakim";
		break;
		
		case "SolomonBonanza_2"://отдаем всё
			dialog.text = "Oy, il y a un Dieu et vous êtes un vrai mensch ! Vous avez ramené non seulement mon or, mais vous avez aussi restauré le nom Shneur ! Quel shande vous avez évité ! Mynheer Rodenburg peut être légitimement fier d'avoir des capitaines comme vous sous son commandement. Je donnerai le crâne à mynheer Rodenburg, il a promis de payer une somme considérable pour cela. Je tiens à vous remercier personnellement, vous êtes un excellent shabbos goy - veuillez accepter cet amulette en signe de gratitude de ce Juif.";
			link.l1 = "Euh, merci, je suppose.";
			link.l1.go = "SolomonBonanza_4";
			RemoveItems(PChar, "SkullAztec", 1);
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			AddDialogExitQuestFunction("DeleteJoakimFromRoom");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Joakim"));
			pchar.questTemp.Caleuche.SolomonSkul = true;
		break;
		
		case "SolomonBonanza_3":
			dialog.text = "Oy, il y a un Dieu et tu es un vrai mensch ! Tu as ramené non seulement mon or mais tu as aussi racheté le nom Shneur ! Quel shande tu as évité ! Quant au crâne - oh bien, peu importe, c'était de toute façon un meshuggeneh schmuck ! Mynheer Rodenburg peut être légitimement fier d'avoir des capitaines comme toi sous son commandement. Je tiens à te remercier personnellement, tu es un excellent shabbos goy - s'il te plaît, accepte cet amulette en souvenir.";
			link.l1 = "Euh, merci, je suppose.";
			link.l1.go = "SolomonBonanza_4";
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "obereg_10");
			pchar.questTemp.HWIC.Holl.ScullnotReturn = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			DelLandQuestMark(npchar);
		break;
		
		case "SolomonBonanza_4":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyLeavesMarried";//теперь можно говорить с Аби
			AddQuestRecord("Holl_Gambit", "1-32");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "SolomonBonanza_5":
			dialog.text = "Quoi ? Que dites-vous, jeune homme ? Est-ce vrai ? Laissez-moi voir... ";
			link.l1 = "Voici votre argent. Il vous appartient, à vous et à Abigail. Mais hélas, je n'ai pas trouvé le crâne de votre grand-père.";
			link.l1.go = "SolomonBonanza_6";
		break;
		
		case "SolomonBonanza_6":
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			dialog.text = "Oh l'argent, l'argent, l'argent, merveilleux argent... Hmm, cela ne ressemble pas à mon argent, pourtant... Cela ne sent pas mon cher pécule. Mais après tout - l'argent est toujours le même, jeune homme, n'est-ce pas? Je ne vais pas m'en plaindre. 'Ne regarde pas un cheval donné dans la bouche,' comme on aime dire! Merci beaucoup d'avoir ramené mes économies. Je tiens à vous remercier aussi, s'il vous plaît, acceptez cet amulette. Maintenant, allez et dites à Abi la bonne nouvelle. Je dois compter cela.";
			link.l1 = "Beaucoup de bonheur pour toi, Salomon.";
			link.l1.go = "SolomonBonanza_4";
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

//-------------------------------------------за Англию------------------------------------------------
		
		case "Solomon_treasure":
			dialog.text = "Bon sang, fais attention à toi ! Mynheer Rodenburg est à un pas de devenir mon gendre goy. Tous les soldats de la garnison seront ici en un clin d'œil si je crie à l'aide !";
			link.l1 = "Putain, qui es-tu ?";
			link.l1.go = "Solomon_treasure_1";
		break;
		
		case "Solomon_treasure_1":
			dialog.text = "Ecoute-moi, capitaine. Je suis son père Salomon. Fais ce qu'il faut, ramène-moi mes pièces perdues et le crâne de jade de son arrière-grand-père. Ce vieil Juif n'est peut-être pas aussi rusé que toi, mais même lui sait que tu veux quelque chose de sa fille\nPeut-être que tu as été envoyé par quelqu'un, par un capitaine qui me connaît, je dirai tout à Abi, ne t'inquiète pas. Elle n'est pas à la maison maintenant, elle prie pour les âmes des pécheurs gentils comme toi.";
			link.l1 = "Ça n'avait presque aucun sens... Nom d'une pipe, t'es vraiment un sacré numéro. Adieu, vieux grippe-sou.";
			link.l1.go = "Solomon_treasure_2";
		break;
		
		case "Solomon_treasure_2":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-17");
			pchar.questTemp.HWIC.Eng = "AbigileInChurch";
			sld = characterFromId("Abigile");
			sld.greeting = "abigile_3";
			ChangeCharacterAddressGroup(sld, "Villemstad_church", "goto", "goto1");//Аби в церковь
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
//----------------------------------------------против всех---------------------------------------------	
		
		case "Abigile_kidnap":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Villemstad");
			dialog.text = "Une lettre ? Sans blague ! Écoute-moi bien, goy, Mynheer Rodenburg est à un pas de devenir mon gendre. Tu peux te tirer d'ici parce que je l'aime bien !";
			link.l1 = "Ecoutez, je me fous de qui est votre gendre. Je suis obligé de remettre cette lettre à Abigail. Savez-vous où je peux la trouver ? Et qui diable êtes-vous ?";
			link.l1.go = "Abigile_kidnap_1";
		break;
		
		case "Abigile_kidnap_1":
			dialog.text = "Qui suis-je ? Je suis son père Salomon... Et je ne t'aime pas, goy.";
			link.l1 = "Je serais plus inquiet si tu disais que tu m'aimes bien. Maintenant, vas-tu continuer à me traiter avec condescendance ou vas-tu chercher Abigail ? Je le répète, je suis un messager ! J'ai une lettre pour ta fille !";
			link.l1.go = "Abigile_kidnap_2";
		break;
		
		case "Abigile_kidnap_2":
			dialog.text = "Donnez-moi cette lettre. Je la remettrai à ma fille.";
			link.l1 = "Je vais te raser les cheveux et te pincer le nez avant de te remettre cette lettre. J'ai l'ordre de remettre ce message à elle personnellement. On ne m'a pas dit un mot sur son père et je m'en fiche éperdument. Où puis-je trouver Abigail ?";
			link.l1.go = "Abigile_kidnap_3";
		break;
		
		case "Abigile_kidnap_3":
			dialog.text = "Dès que je crie, jeune goy, chaque soldat de la ville sera ici en un clin d'œil. Ne sois pas si têtu, tu vois bien que j'ai toutes les cartes en main.";
			link.l1 = "Jésus, Marie, et Joseph ! Vraiment ? Et ensuite quoi ? Tu t'attends à ce qu'ils me jettent aux fers pour avoir livré une lettre ? Ne sois pas ridicule !";
			link.l1.go = "Abigile_kidnap_4";
		break;
		
		case "Abigile_kidnap_4":
			DialogExit();
			sld = characterFromId("Abigile");
			ChangeCharacterAddressGroup(sld, "Villemstad_houseSP2", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_GoOver":
			dialog.text = "Es-tu fou ? Tu as affolé ma pauvre fille à moitié morte avec ta lettre... Elle a décidé de poursuivre ce salaud de capitaine anglais ! Elle est partie sur le premier bateau disponible ! Oy veyy, ma pauvre fille ! Que va faire ce vieux Juif maintenant ? Ma vie est ruinée ! C'est une honte ! Laisse-moi à ma misère, ou reste et réjouis-toi, je m'en moque ! Ohhh ma pauvre Abigail ! Tu as conduit la tête grise de ton père au Sheol dans le désespoir !";
			link.l1 = "Eh bien, que penses-tu de ça ! Je suppose qu'elle n'a pas pu attendre un instant de plus. Adieu, Salomon !";
			link.l1.go = "Abigile_GoOver_1";
		break;
		
		case "Abigile_GoOver_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-69");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
		break;
		
		case "Solomon_history":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "Qu'est-ce que ça ressemble à ça ? C'est juste une île sans personne d'autre que moi et Abigail. Là, j'ai caché mon coffre, pour empêcher ce pirate goy Amalek de le prendre. Tout ce que j'avais honnêtement gagné à la sueur de mon front est dans ce coffre...";
			link.l1 = "Dis-moi, Solomon, peut-être pourrais-tu te rappeler le nom du fluyt dont ta fille parlait ? Et quel était le nom de son capitaine ?";
			link.l1.go = "Solomon_history_1";
		break;
		
		case "Solomon_history_1":
			dialog.text = "Hmm... Eh bien, je ne sais pas. La tête de ce pauvre vieux Juif est embrouillée comme une poêle de gefilte fish ! Et pourquoi me demandes-tu cela, jeune homme ?";
			link.l1 = "Je veux juste aider ta fille, Solomon. Je ne peux rien promettre, mais j'aimerais essayer. Mon ancien patron l'a maltraitée, et après cela, je pense être obligé de l'aider à s'installer d'une façon ou d'une autre.";
			link.l1.go = "Solomon_history_2";
		break;
		
		case "Solomon_history_2":
			dialog.text = "Oy vey, eh bien si c'est le cas...";
			link.l1 = "";
			link.l1.go = "Solomon_history_3";
			pchar.questTemp.HWIC.Self = "SolomonHistoryNext";
		break;
		
		case "Solomon_history_3":
			DialogExit();
			sld = characterFromId("Abigile");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Solomon_thanks":
			dialog.text = "Jeune homme ! Attendez !";
			link.l1 = "Oui ?";
			link.l1.go = "Solomon_thanks_1";
		break;
		
		case "Solomon_thanks_1":
			dialog.text = "Jeune homme ! Je tiens à vous remercier pour tout ce que vous avez fait pour moi et ma fille. Vous nous avez sauvés. Je suis désolé de vous avoir réservé un accueil difficile la première fois que nous nous sommes rencontrés et d'avoir douté de votre sincère désir d'aider. Je vous prie de pardonner ce vieux Juif. Vous êtes vraiment un homme béni parmi les goyim. Maintenant, dites-moi, n'avez-vous rien trouvé d'autre que mon argent dans la grotte ?";
			link.l1 = "Non, Solomon. Il n'y avait rien d'autre que de l'argent. J'ai dû combattre les bandits de van Berg - c'est lui qui a coulé votre navire il y a des mois. Il se pourrait qu'ils aient déjà volé quelque chose... Qu'est-ce qui était censé s'y trouver d'autre ?";
			link.l1.go = "Solomon_thanks_2";
		break;
		
		case "Solomon_thanks_2":
			dialog.text = "Oh rien d'important... Une relique familiale ancienne... Bon, peu importe ! Oublie ça, c'était un imbécile de toute façon ! Et... Juste une chose de plus, jeune homme... ";
			link.l1 = "Continuez.";
			link.l1.go = "Solomon_thanks_3";
		break;
		
		case "Solomon_thanks_3":
			dialog.text = "Vous... eh bien, j'ai découvert quelque chose à votre sujet. Notre gouverneur vous tient en haute estime, et vous êtes un capitaine remarquable. Je vais vous confier un secret... ma fille vous aime beaucoup. Elle me l'a dit elle-même. Peut-être... y réfléchirez-vous? Abigail est une très bonne fille, je vous l'assure, meilleure que toutes les fripouilles que vous avez pu rencontrer lors de vos voyages.";
			link.l1 = "Oy vey... Ce n'est pas si simple, Salomon. Ta fille est vraiment un bijou rare. Prends-en bien soin.";
			link.l1.go = "Solomon_thanks_4";
		break;
		
		case "Solomon_thanks_4":
			dialog.text = "Pensez-y bien, jeune homme. Réfléchissez encore et revenez ! Nous serions ravis de vous revoir !";
			link.l1 = "Bien sûr...au revoir, Solomon.";
			link.l1.go = "Solomon_thanks_5";
		break;
		
		case "Solomon_thanks_5":
			DialogExit();
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload1", false);
			AddQuestRecord("Holl_Gambit", "3-65");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "Solomon_poor":
			dialog.text = "Oyyy... Parfois, il est impossible de commencer une nouvelle vie, jeune homme. Vivre dans la pauvreté - quoi de pire pour un vieux bon à rien comme moi ?";
			link.l1 = "Je suis désolé, Salomon. Tiens bon et cherche le Christ.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Solomon_poor";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Tu es un "+GetSexPhrase("voleur, monsieur ! Gardes, attrapez-le","voleuse, fille ! Gardes, attrapez-la")+"!!!","Regardez-moi ça ! Dès que je me perds dans mes pensées, vous décidez de fouiller dans mon coffre ! Attrapez le voleur !!!","Gardes ! Vol ! Attrapez le voleur !!!");
			link.l1 = "Merde !";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
