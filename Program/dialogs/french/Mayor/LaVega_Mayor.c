// заместитель Маркуса Тиракса в Ла Веге
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
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
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = NPCStringReactionRepeat("Tu as quelque chose à me dire ? Non ? Alors, dégage d'ici !","Je crois avoir été clair, cessez de m'importuner.","Bien que je me sois exprimé clairement, vous continuez à m'ennuyer !","D'accord, je commence à en avoir marre de cette impolitesse.","répéter",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Je pars déjà.","D'accord"+npchar.name+"...","Désolé, "+npchar.name+"... ","Oups...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", je suis heureux de vous voir ! Que souhaitez-vous ?","Que d'autre ?"," Encore vous ? Ne dérangez pas les gens si vous n'avez rien à faire !","Je sais que vous êtes un homme respectable. Mais j'en ai fini de discuter avec vous.","répéter",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Rien. Je voulais juste te voir.","Rien...","D'accord, "+npchar.name+"Désolé...","Merde, c'est uniquement de ma faute...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Vol !!! Es-tu sérieux ?! Tu es fini, mon pote...","Attends, mais qu'est-ce que c'est que ce bordel? Il s'avère que tu es un voleur! C'en est fini de toi...");
			link.l1 = LinkRandPhrase("Merde !","Carramba !!","Merde !!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Va-t'en","Va-t'en ")+" d'ici !","Sors de chez moi !");
			link.l1 = "Oups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Ne me dérange pas avec tes bavardages bon marché. La prochaine fois, tu n'aimeras pas le résultat...";
        			link.l1 = "Je l'ai.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "C'est fini, pas de discussions.";
			link.l1 = RandPhraseSimple("Comme vous le souhaitez...","D'accord alors...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "J'espère que tu me montreras plus de respect et cesseras d'être impoli ? Sinon, je devrais te tuer. Ce serait fort désagréable.";
        			link.l1 = ""+npchar.name+", soyez-en sûr, je le ferai.";
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
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ_1":
			dialog.text = "Ah, c'est toi, de Maure. Eh bien, quelle surprise. Par le diable des mers, ton arrivée est la chose la plus intéressante qui soit arrivée depuis longtemps, que diable.";
			link.l1 = "Ravi de te voir aussi, Vensan. Apprécies-tu de gouverner le village ?";
			link.l1.go = "PZ_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_2":
			dialog.text = "Comment pourrais-je ? Je suis un capitaine, un sacré bon en plus, pas un foutu comptable. Et j'ai attendu plus longtemps les messagers de Marcus pour qu'ils me convoquent à un nouveau voyage que je n'ai attendu Noël, sacrées malédictions !";
			link.l1 = "Noël et malédictions dans une seule phrase, voilà quelque chose. Aye, je ne t'envie pas. Pourtant, beaucoup aimeraient être à ta place actuelle. Mais je suis venu te voir pour affaires, Vensan.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Des affaires ?! Eh bien, crache le morceau alors - as-tu pensé à quelque chose ? As-tu une bonne piste ? Je suis sur le point de vider la cave locale par pur ennui et tous ces foutus calculs.";
			link.l1 = "Eh bien, c'est plutôt que j'ai une question pour vous, rien de plus.";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "Mille tonnerres ! Mais d'accord, je t'écoute, Charles.";
			link.l1 = "Une femme est-elle venue vous voir ? Ou peut-être l'avez-vous aperçue à La Vega ? Elle se fait appeler Belle Étoile, bien que ce ne soit qu'un pseudonyme, donc elle aurait pu se présenter sous un autre nom. Ce qui est important, c'est qu'elle... elle a la peau jaune. Mais ce n'est ni une esclave ni une ouvrière - c'est une femme riche.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			dialog.text = "Au teint jaune, mais riche ? On n'a jamais eu quelqu'un comme ça ici, jamais ! On dirait que vous continuez à vivre cette vie intéressante, de Maure ! Je suis presque jaloux.";
			link.l1 = "Est-ce ainsi... Eh bien, merci pour votre temps, Vensan. Je ne vous distrairai plus de votre comptabilité, héh-héh.";
			link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "40");
			
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1 = "location";
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PZ_SetHeavyFrigate.win_condition = "PZ_SetHeavyFrigate";
			DelMapQuestMarkCity("LaVega");
			AddMapQuestMarkCity("PortPax", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
		break;
	}
}
