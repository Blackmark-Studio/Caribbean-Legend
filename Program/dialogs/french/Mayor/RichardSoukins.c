// Соукинс в Пуэрто-Принсипе
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = "As-tu des affaires avec moi ? Non ? Alors, hors d'ici !";
			link.l1 = "Je pars déjà.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";


					if (npchar.city == int(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "Avez-vous du travail pour moi ?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "J'ai trouvé la piste, mais j'ai besoin de quelques pièces - 30.000 pesos pour débusquer le rat de son trou.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Tiens, regarde cette lettre que j'ai trouvée sur le cadavre du contrebandier";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "C'est fait. Norman Vigo et son navire sont partis vers le diable des mers.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Hm... du travail, avez-vous dit? En fait, c'est bien que vous m'ayez demandé. J'ai besoin d'un homme de l'extérieur. Je veux découvrir quelque chose dans la ville la plus proche, mais mes hommes y sont connus. Je ne peux pas vous promettre grand-chose, mais vous obtiendrez quelque chose.";
			link.l1 = "Chouette ! Quelle est la mission ?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Désolé, mais je ne prendrai pas le risque pour quelques broutilles. Adieu.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "Alors écoutez, j'avais un accord pour livrer 200 esclaves il y a un mois avec le capitaine de la goélette 'Saintblue'. Je voulais les vendre au propriétaire de la plantation locale. Le temps a passé et le client a commencé à s'inquiéter, mais hier on m'a dit que la goélette avait été aperçue non loin de l'île. Mais ! Le capitaine ne s'est pas montré. Aujourd'hui, mon client m'a demandé de lui rendre son avance et a dit qu'on lui avait proposé d'acheter des esclaves d'un autre vendeur. Plus cher, mais tout le lot d'esclaves et d'un coup.";
			link.l1 = "Et alors ? Je dois trouver 200 esclaves en quelques jours pour te sauver de perdre une avance ? Pour quelques piastres ?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Bien sûr que non. Ai-je l'air d'un idiot ? Je ne lui rendrai pas son avance de toute façon. Mais j'ai besoin de preuves que ces esclaves qui lui ont été proposés sont les miens. Trouvez ceux qui lui ont proposé un nouvel accord et vous obtiendrez vos 10 000 pesos. Marché conclu ?";
			link.l1 = "Je suis partant. Avez-vous des soupçons? Qui pourrait faire ça?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Pas question. Cherchez quelqu'un d'autre. Seulement pour 10 000 ? Désolé mais ça ne marchera pas.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "Si j'avais la moindre idée, je n'aurais jamais recours à vos services. Ces hommes seraient déjà morts. Mais je suis impatient de savoir comment ils ont découvert la cargaison du 'Saintblue' et mon client. Il semble que cela ait été assez facile pour eux. Vous voyez maintenant ?";
			link.l1 = "Oui, quelqu'un vous a vendu.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "Exactement ! Je le cherche. Tuer mes concurrents et me rendre mes esclaves ne sont pas ta priorité. J'ai besoin de ce rat, en fait de sa tête sur une pique pour être honnête. Voyez maintenant pourquoi mes hommes ne devraient rien savoir de votre mission ? Je soupçonnerai tout le monde jusqu'à ce que je découvre qui vend l'information. Et je ne veux vraiment pas ça...";
			link.l1 = "Je vois. Alors je resterai discret. Je suis en route.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Trente mille tu dis? C'est une grosse somme... Je ne peux te donner que 5.000 pesos, c'est tout ce que j'ai maintenant. Et n'essaie même pas de t'enfuir avec l'argent ou je te retrouverai et je te pendrai à la clôture la plus proche! Compris?";
			link.l1 = "D'accord, donne-moi cinq mille alors...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Prenez-le. J'attends le résultat de votre recherche.";
			link.l1 = "Tout ira bien.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ha! Excellente nouvelle ! J'étais sûr que tu y arriverais. J'ai des informations intrigantes.";
			link.l1 = "J'ai accompli ma tâche et je veux avoir mes dix mille.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Bien sûr, voici ta récompense. Mais ne pars pas, j'ai encore une mission pour toi.\nPfaifer est un membre d'équipage de Norman Vigo du lougre 'Septima'. Je suis sûr que Norman Vigo est le rat, même s'il est l'un des nôtres. Il a été récemment aperçu dans les eaux de l'île. Ton travail est d'envoyer ce rat chez le diable des mers. Tu ne m'as pas déçu la première fois, c'est pourquoi je veux te demander de t'occuper aussi de cette affaire. Je te paierai 15 000 pesos. Marché conclu ?";
			link.l1 = "Je m'en occupe ! Considérez le traître Norman Vigo comme mort.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "Vous savez, je ne veux pas m'impliquer là-dedans... De toute façon, je n'ai pas le temps. Désolé, mais je m'en vais.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "Je sais, je sais. Mes hommes observaient la bataille et m'ont déjà rapporté votre victoire éclatante. Bien, vous avez bien fait votre travail. Voici les 15 000 pesos que j'avais promis. Et merci, vous m'avez grandement aidé.";
			link.l1 = "C'est bien, j'étais heureux d'aider ! Mais je dois y aller maintenant, je suis resté ici trop longtemps et j'ai beaucoup de choses à faire. Adieu !";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;


	}
}
