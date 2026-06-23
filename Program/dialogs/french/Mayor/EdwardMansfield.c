// Эдвард Мэнсфилд, глава буканьеров и авторитетный пират, английская линейка
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
            if (CheckAttribute(npchar, "Sp5LaVegaAttackDone"))
            {
            	if (NPChar.quest.meeting == "0")
				{
					dialog.Text = TimeGreeting()+" ! Je suis "+GetFullName(NPChar)+", le nouveau gouverneur de ce trou. Il ne sera pas facile de mettre au pas les voyous locaux, mais ils ne représentent plus de menace pour les colonies espagnoles.";
					Link.l1 = "Je suis ravi de vous rencontrer. Je suis le capitaine "+GetFullName(Pchar)+"Désolé, mais je dois y aller.";
					Link.l1.go = "exit";
					NPChar.quest.meeting = "1";
				}
				else
				{
					dialog.Text = TimeGreeting()+"Je suis occupé, vraiment très occupé, je dois contrôler les ruffians locaux pour éviter toute menace envers les colonies espagnoles.";
					Link.l1 = "Je ne vous dérangerai pas alors.";
					Link.l1.go = "exit";
				}
            }
            else
            {
				dialog.text = NPCStringReactionRepeat("As-tu quelque chose à me dire ? Non ? Alors "+GetSexPhrase("va-t'en d'ici !","Je vous prie de ne pas me déranger.")+"","Je pense que je me suis bien fait comprendre...","Bien que je me sois expliqué, tu continues à m'importuner !","Eh bien, vous êtes hors de mesure "+GetSexPhrase("trop impoli, mon chéri","une telle inconvenance, fille","quelle discourtoisie, fille")+"...","répéter",30,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Je m'en vais.","Oui, "+npchar.name+", je vois cela.","Désolé, "+npchar.name+"... ","Aïe...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}


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
								link.l2 = "J'ai trouvé la piste, mais j'ai besoin de quelques pièces - 30 000 pesos pour attirer le rat hors de son trou.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Tiens, regarde cette lettre que j'ai trouvée sur le cadavre du contrebandier";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "C'est fait. Norman Vigo et son navire appartiennent au diable des mers.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Hm.. Travail, vous dites ? En fait, c'est bien que vous m'ayez demandé. J'ai besoin d'un homme de l'extérieur. Je veux découvrir quelque chose dans la ville la plus proche mais mes hommes sont connus là-bas. Je ne peux pas vous promettre beaucoup mais vous obtiendrez quelque chose.";
			link.l1 = "Quelle est la mission ?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Désolé, mais je ne prendrai pas le risque pour quelques miettes. Adieu.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "Alors écoute, j'avais conclu un marché pour livrer 200 esclaves il y a un mois avec le capitaine de la goélette 'Saintblue'. Je voulais les vendre au propriétaire de la plantation locale. Le temps a passé et le client a commencé à s'inquiéter, mais hier on m'a dit que la goélette a été vue non loin de l'île. Mais ! Le capitaine ne s'est pas montré. Aujourd'hui, mon client m'a demandé de lui rendre son avance et a dit qu'on lui a proposé d'acheter des esclaves d'un autre vendeur. Plus cher, mais tout le lot d'esclaves d'un coup.";
			link.l1 = "Et alors ? Je dois trouver 200 esclaves en quelques jours pour vous sauver de perdre une avance ? Pour quelques piastres ?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Bien sûr que non. Ai-je l'air d'un idiot ? Je ne lui rendrai pas l'avance de toute façon. Mais j'ai besoin de preuves que ces esclaves qui lui ont été proposés sont les miens. Trouvez ceux qui lui ont proposé un nouvel accord et vous obtiendrez vos 10 000 pesos. Marché conclu ?";
			link.l1 = "Je suis partant. Avez-vous des soupçons sur qui cela pourrait être ?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Pas question. Cherchez quelqu'un d'autre, seulement pour 10 000 ? Désolé mais cela ne marchera pas.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "Si j'avais la moindre idée, je n'aurais jamais recours à vos services. Ces hommes seraient déjà morts. Mais je suis impatient de savoir comment ils ont découvert la cargaison du 'Saintblue' et mon client. On dirait que cela a été assez facile pour eux. Vous voyez maintenant ?";
			link.l1 = "Oui, quelqu'un vous a trahi.";
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
			dialog.text = "Exactement ! Je suis à sa recherche. Tuer mes concurrents et me rendre mes esclaves ne sont pas ta priorité. J'ai besoin de ce rat, en fait de sa tête sur une pique, pour être franc. Comprends-tu maintenant pourquoi mes hommes ne doivent rien savoir de ta mission ? Je soupçonnerai tout le monde jusqu'à ce que je découvre qui vend les informations. Et je ne le veux vraiment pas...";
			link.l1 = "Je vois. Alors, je resterai discret. Je suis en route.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Trente mille, vous dites ? C'est une somme considérable... Je ne peux vous donner que 5 000 pesos, c'est tout ce que j'ai maintenant. Et n'essayez même pas de vous enfuir avec l'argent ou je vous retrouverai et je vous pendrai à la clôture la plus proche ! Compris ?";
			link.l1 = "D'accord, donne-moi cinq mille alors...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Prenez-le. J'attends le résultat de votre recherche.";
			link.l1 = "Ce sera bien.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ha ! Excellente nouvelle ! J'étais sûr que vous y arriveriez. J'ai des informations intrigantes.";
			link.l1 = "J'ai fait mon travail et je veux recevoir mes dix mille.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Bien sûr, voici ta récompense. Mais ne t'enfuis pas, j'ai une autre mission pour toi.\nPfaifer est un membre d'équipage de Norman Vigo du lougre 'Septima'. Je suis sûr que Norman Vigo est le rat, même s'il est l'un des nôtres. Il a récemment été vu dans les eaux de l'île. Ton travail est d'envoyer ce rat au diable des mers. Tu ne m'as pas déçu la première fois, donc je veux te demander de t'occuper de cette affaire aussi. Je te paierai 15.000 pesos. Marché conclu ?";
			link.l1 = "Je m'en charge ! Considérez le traître comme mort.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "Tu sais, je ne veux pas y participer... De toute façon, je n'ai pas le temps. Désolé, mais je m'en vais.";
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
			dialog.text = "Je sais, je sais. Mes hommes ont observé la bataille et m'ont déjà rapporté votre victoire éclatante. Bien, vous avez bien fait votre travail. Voici 15 000 pesos, comme je l'avais promis. Et merci, vous m'avez grandement aidé.";
			link.l1 = "C'est bien, j'étais heureux d'aider ! Mais je dois partir maintenant, je suis resté ici trop longtemps et j'ai beaucoup de choses à faire. Adieu !";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;
				
 		case "No_Mansfield_first_time":
			dialog.text = "Salutations, je me nomme Alistair Good. J'ai été élu chef des boucaniers après la mort de Mansfield.";
			link.l1 = "Enchanté de vous rencontrer, Alistair.";
			link.l1.go = "exit";
			NextDiag.TempNode = "No_Mansfield";
  		break;
 		case "No_Mansfield":
			dialog.text = "Je n'ai pas le temps de te parler. Reviens me voir plus tard.";
			link.l1 = "Je pars déjà.";
			link.l1.go = "exit";
  		break;
		

// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple("Bonjour, mon ami."+GetSexPhrase("Prendre","Prendre")+" dehors!","Va-t'en de chez moi !");
			link.l1 = "Oups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Мэнсфилдом через 30 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > int(npchar.angry.terms))
                {
         			dialog.text = "Ne me dérange pas, souviens-toi de cela.";
        			link.l1 = "Je l'ai compris.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("LaVega_town","reload","reload6");
		break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
