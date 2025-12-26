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
            dialog.text = NPCStringReactionRepeat("Tem algo a me dizer? Não? Então saia daqui!","Acho que fui claro, pare de me importunar.","Apesar de eu ter sido claro, você continua me irritando!","Certo, já estou cansado dessa grosseria.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Já estou de saída.","Claro"+npchar.name+"...","Desculpe, "+npchar.name+"...","Opa...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", fico feliz em vê-lo! O que deseja?","O que mais?"," Você de novo? Não incomode as pessoas se não tem nada para fazer!","Eu sei que você é um homem decente. Mas já terminei de falar com você.","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nada. Só queria te ver.","Nada...","Certo, "+npchar.name+", desculpe...","Maldição, a culpa é toda minha...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Roubo?! Você está falando sério?! Acabou pra você, camarada...","Espere, mas que diabos? Então você é um ladrão! Acabou pra você...");
			link.l1 = LinkRandPhrase("Merda!","Caramba!!","Droga!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Vá embora","Saia daqui ")+" daqui!","Saia da minha casa!");
			link.l1 = "Opa...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Não me aborreça com suas conversas baratas. Da próxima vez, o resultado não vai te agradar...";
        			link.l1 = "Entendi.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "Acabou, sem conversa.";
			link.l1 = RandPhraseSimple("Como desejar...","Está bem então...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Espero que passe a me tratar com mais respeito e pare de ser grosseiro. Caso contrário, terei que matá-lo. Isso seria extremamente desagradável.";
        			link.l1 = ""+npchar.name+", pode ter certeza, eu vou.";
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
			dialog.text = "Ah, é você, de Maure. Ora, que surpresa. Pelo diabo do mar, sua chegada é a coisa mais interessante que aconteceu em muito tempo, maldição.";
			link.l1 = "Também é bom te ver, Vensan. Está gostando de governar a vila?";
			link.l1.go = "PZ_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_2":
			dialog.text = "Como eu poderia? Sou um capitão, e dos bons, não algum maldito contador. E já estou esperando pelos mensageiros do Marcus me chamarem para uma nova viagem há mais tempo do que espero pelo Natal, malditas pragas!";
			link.l1 = " Natal e maldições na mesma frase, isso sim é algo curioso. Olha, não queria estar no seu lugar. Mas muitos adorariam estar na sua posição agora. Mas vim até você por negócios, Vensan.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Negócios?! Então, fale logo — pensou em alguma coisa? Tem alguma pista boa? Estou prestes a esvaziar a adega local de tanto tédio com esses malditos cálculos.";
			link.l1 = "Bem, na verdade eu é que tenho uma pergunta para você, só isso.";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "Droga! Tudo bem, estou ouvindo, Charles.";
			link.l1 = "Uma mulher veio procurá-lo? Ou talvez tenha visto ela em La Vega? Ela atende pelo nome de Belle Étoile, embora esse seja apenas um pseudônimo, então pode ter se apresentado com outro nome. O importante é que ela... ela tem a pele amarela. Mas não é uma escrava nem trabalhadora — é uma mulher rica.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			dialog.text = "Pele amarelada, mas rico? Nunca tivemos alguém assim por aqui, jamais! Parece que você continua levando essa sua vida interessante, de Maure! Quase sinto inveja.";
			link.l1 = "É mesmo... Bem, obrigado pelo seu tempo, Vensan. Não vou mais tomar o seu tempo com a contabilidade, heh-heh.";
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
