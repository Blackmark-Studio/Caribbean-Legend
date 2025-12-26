// Захария Марлоу, Чёрный Пастор, Пуэрто-Принсипе, Куба
int iMarlowTotalTemp;
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
                    if (npchar.angry.name == "pirate_threat")
                    {
                        if (Dialog.CurrentNode == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                        else Dialog.CurrentNode = "AngryRepeat_1";
                    }
                break;
            }
        }
    } //<-- блок angry

	switch(Dialog.CurrentNode)
	{
		case "First time":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Você ficou maluco? Queria bancar o açougueiro? Todos os piratas estão furiosos com você, garoto, é melhor cair fora daqui.","Parece que você perdeu o juízo, garoto. Queria se mostrar um pouco? Sem ofensa, mas você não tem nada pra fazer aqui. Cai fora!");
				link.l1 = RandPhraseSimple("Escuta, eu quero resolver essa situação...","Me ajude a resolver esse problema...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", eu gostaria" + GetSexPhrase("","a") + " de discutir minha segurança no mar. Os rapazes da Irmandade Costeira estão demonstrando interesse demais na minha humilde pessoa. Você poderia dar uma segurada neles?";
			link.l0.go = "pirate_threat";
			
            dialog.text = NPCStringReactionRepeat("Tem alguma coisa pra me dizer? Não? Então cai fora daqui!",
						"Acho que fui bem claro, pare de me irritar.","Apesar de eu já ter deixado tudo claro, você continua me irritando!",
						"Certo, já estou ficando cansado dessa grosseria.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Já estou indo embora.",
						"Claro, "+npchar.name+"...",
						"Desculpa, "+npchar.name+"...",
						"Ai...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && !CheckAttribute(npchar, "quest.sharkbegin"))
			{
				link.l1 = "Estou tentando encontrar o Shark Dodson. Dizem que você foi o último a vê-lo. Pode me ajudar com isso?";
				link.l1.go = "Shark";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax" && CheckCharacterItem(pchar, "witches_hammer"))
			{
				link.l1 = "Por que você é tão grosseiro? Ou será que não está interessado em conseguir o livro que tanto quer comigo?";
				link.l1.go = "book";
			}
			//<-- Сага
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Quero falar sobre o seu prisioneiro.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "Olá, Pastor. Quero falar sobre sua missão.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "Quero falar sobre o seu prisioneiro.";
					link.l1.go = "CapComission6";
				}
			}
		break;
		
		case "shark":
			dialog.text = "Steven Dodson? I don't know how my story would help you, because Shark has been missing for the last few months and no one has seen him. It's not a surprise though; he killed Blaze Sharp and disgraced his own name with that foolish act. He made a few powerful corsairs his enemies.";
			link.l1 = "Tenho todos os motivos para acreditar que o Shark é inocente da morte do Sharp. Não posso provar, mas talvez o próprio Shark consiga. Vai me contar algo sobre ele?";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "Alguns meses atrás, o Steven veio até mim e propôs um acordo bem estranho: ele deixou a fragata dele, a 'Fortune', como garantia por um mês em troca de um brigue carregado de mantimentos. Depois, ele teria que devolver o brigue e pagar pelas provisões, ou então eu ficaria com a fragata dele. O mês passou – nem sinal do Shark, meu brigue, nem do dinheiro. Além disso, ouvi boatos de que o Blaze foi assassinado e que o Shark era o principal suspeito. O que eu poderia pensar? Exatamente! Achei que o Steven tinha fugido do pior. Vendi a fragata dele para um inglês chamado William Patterson, que ficou muito satisfeito e pagou uma bela pilha de dobrões pelo navio. Portanto, recuperei completamente meus gastos e não guardo rancor nenhum dele. Não me importo com a morte do Sharp, tenho meus próprios problemas para resolver.";
			link.l1 = "Você não acha que, se ele quisesse fugir, não precisaria do seu brigue? Ele tinha o próprio navio, cem vezes melhor que qualquer brigue. Parece que o Tubarão tinha um plano, mas algo deu errado e ele não voltou a tempo.";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "Como já te disse, não me importo com os problemas do Dodson. Cumpri minha parte do acordo. Quanto ao navio, é melhor perguntar a ele por que precisava daquela maldita escuna. Não fui eu quem o obrigou a pegar.";
			link.l1 = "Tá bom, não vamos mais falar sobre isso. Você está certo, claro. Me diga, você sabe para onde o Steven estava indo no seu brigue?";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "Quem sabe ao certo. Mas eu tenho alguns palpites. Ele navegou para noroeste, em direção ao continente. Então, ou foi para a Baía do Perigo, famosa pelos índios hostis, ou para a Nova Espanha, conhecida pelos papistas e pela Inquisição. Duvido que ele tenha ido para qualquer um desses lugares. Mas dizem que existe um lugar estranho chamado 'Cidade dos Navios Abandonados' a noroeste de Cuba. Muita gente acha que isso é só um mito, mas eu não. Não porque eu seja um sonhador, mas porque existem pessoas de verdade que já chegaram lá em seus botes. Pelo menos, antigamente iam.";
			link.l1 = "E quem são eles?";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "Bucaneiros de Cuba. Eles carregavam suas barcas com carcaças de boi e partiam para o noroeste. Sempre voltavam um pouco depois com os bolsos cheios de dinheiro ou com mercadorias raras e valiosas.";
			link.l1 = "Interessante! Onde posso encontrar esses bucaneiros?";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "Why are you asking me? Search Cuba's woods. Even if you find them, they won't tell you anything; why would they reveal the source of their good fortune? So don't waste your time, no one has seen them at it for a long while.\nAlso, I heard of some notes written by the Spanish sailor Alvarado, who visited the island himself. So I am curious, perhaps Steven did sail there after all.";
			link.l1 = "A ilha desconhecida que não está em nenhum mapa... Bem. Isso não é uma informação animadora.";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "Eu te disse desde o começo que minha história não ia te ajudar. E por que você precisa do Dodson?";
			link.l1 = "O Diabo da Floresta e eu queremos elegê-lo como líder dos Irmãos da Costa. Como já te disse, há motivos sérios para acreditar que Blaze foi assassinado por outra pessoa.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "Heh! Então o Jan está apoiando ele? Bem, você conhece a lei – o Dodson vai ter que conseguir um voto de cada barão.";
			link.l1 = "Eu conheço a lei. Minha segunda pergunta então. Você vai votar no Dodson na eleição?";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "Well, he should return first. Actually, I don't care who leads the Brethren as long as he does his business well and doesn't bother me. As I said, I have problems of my own. Do you know how many witches and mages are on our island? No? I'll tell you: a legion! Besides, there are also a lot of Papists in Santiago and Havana.\nSpeaking of mages. There is a book called 'Hammer for the Witches'. I really want to get it, but only in English; I don't need Latin, German, or Spanish translations, I don't know these languages. Bring me the book and I will vote for Dodson.\nBe aware that Jackman promised me to find it too, so if he succeeds first... don't blame me then.";
			link.l1 = "Tá bom, vou pensar nisso. Obrigado pelo seu tempo. Até mais.";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "after_marlow";
			npchar.quest.sharkbegin = "true";
			AddQuestRecord("SharkHunt", "2");
		break;
		
		case "book":
			dialog.text = "O livro? Imagino que esteja falando do 'Martelo das Bruxas'?";
			link.l1 = "Claro. Consegui encontrar pra você. Está em inglês, como você pediu.";
			link.l1.go = "book_1";
		break;
		
		case "book_1":
			dialog.text = "Ha, desculpe pela recepção bruta, camarada. Não vai se repetir... Deixa eu ver essa maravilha!";
			link.l1 = "Claro, pode dar uma olhada.";
			link.l1.go = "book_2";
		break;
		
		case "book_2":
			RemoveItems(pchar, "witches_hammer", 1); // удалить трактат
			dialog.text = "Finalmente! Tremam agora, servos do Inferno! Não vou deixar vocês em paz enquanto minha mão ainda puder golpear...";
			link.l1 = "Fico feliz por você, Pastor. Então, e o seu voto?";
			link.l1.go = "book_3";
		break;
		
		case "book_3":
			dialog.text = "Como eu já disse, 'não me importa quem vire o chefe.' Tenho certeza de que o Svenson não vai escolher um homem indigno. Então, fique com meu voto. Faça o que quiser com ele. Aqui está meu fragmento.";
			link.l1 = "Obrigado, Zechariah. Te vejo lá!";
			link.l1.go = "book_4";
		break;
		
		case "book_4":
			GiveItem2Character(pchar, "splinter_zm"); // дать осколок
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "27");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Você ficou maluco? Quis brincar de açougueiro? Todos os piratas estão furiosos com você, garoto, então é melhor dar o fora daqui...","Parece que você perdeu o juízo, garoto. Queria se mostrar um pouco? Sem ofensa, mas você não tem nada pra fazer aqui. Cai fora!");
				link.l1 = RandPhraseSimple("Escuta, eu quero resolver essa situação...","Me ajude a resolver esse problema...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", eu gostaria" + GetSexPhrase("","a") + " de discutir minha segurança no mar. Os rapazes da Irmandade Costeira estão demonstrando interesse demais na minha humilde pessoa. Você poderia dar uma segurada neles?";
			link.l0.go = "pirate_threat";
			
            dialog.text = NPCStringReactionRepeat("Tem alguma coisa pra me dizer? Não? Então cai fora daqui!",
						"Acho que fui bem claro, pare de me irritar.","Apesar de eu já ter deixado tudo claro, você continua me irritando!",
						"Certo, já estou ficando cansado dessa grosseria.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Já estou indo embora.",
						"Claro, "+npchar.name+"...",
						"Desculpa, "+npchar.name+"...",
						"Ai...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "É sobre o seu prisioneiro.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}		
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "É sobre o seu prisioneiro.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "Olá, Pastor, estou aqui por causa da sua missão.";
				link.l1.go = "CapComission3";
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && CheckAttribute(pchar, "questTemp.LongHappy"))
			{ // лесник . похититель  ( после ДЛС ДиС ,когда барбазона уже нет)
				link.l1 = "Ouvi dizer que você está envolvido em negócios relacionados a prisioneiros...";
				link.l1.go = "Marginpassenger";
			}
		break;
		
	//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "Ha-ha. Você acha que só tenho um prisioneiro aqui? Diga o nome dele.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+". Ele está aqui?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Ele foi. Eu o vendi para aquele fazendeiro de Barbados – o coronel Bishop, quando ele esteve aqui há uma semana.";
				link.l1 = "Droga...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ah, finalmente. Eu já estava pensando em vendê-lo para aquele fazendeiro de Barbados, ele chega aqui em uma ou duas semanas... Você trouxe o resgate?";
				link.l1 = "Olha, tem um pequeno problema... Na verdade, eu não tenho tanto dinheiro assim. Mas estou disposto a trabalhar.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Que bom que você não o vendeu. Aqui estão suas moedas – 150.000 pesos. Onde posso encontrá-lo?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Você foi lento demais... E por que se importa com ele? Eu só estava negociando com os parentes dele.";
			link.l1 = "Me pediram para vir aqui.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Bem, você está atrasado. Não posso fazer nada.";
			link.l1 = "Escuta, por quanto você vendeu ele, se não for segredo?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "É, não é. Mas não vou te contar... você vai rir se eu contar. Ha-ha-ha-ha! Adeus.";
			link.l1 = "Até mais.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));																															 
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{
				dialog.text = "Bem, "+pchar.name+", sabe, não é assim que funciona. Volte com o dinheiro e você terá seu fracote, ha-ha.";
				link.l1 = "Tá bom. Até mais.";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "Pois é, pois é... Tenho um serviço pra resolver... Nem sei por onde começar. Preciso afundar um pirata que passou dos limites.";
				link.l1 = "Ele não pode simplesmente ser morto na selva?";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Não é assim que os negócios funcionam, sabe... Não preciso que ele morra, só preciso ensinar pra alguns que não se pega a minha parte do saque. Mas não vou lamentar se ele morrer.";
			link.l1 = "Por que você mesmo não manda seus homens atrás dele?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "Hm... Bem, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" convenceu alguns piratas de que a parte deles do saque está guardada no nosso esconderijo não muito longe de "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". Os dois navios deles '"+pchar.GenQuest.CaptainComission.ShipName1+"' e '"+pchar.GenQuest.CaptainComission.ShipName2+"' levantou âncora há pouco tempo e partiu para "+sLoc+". Agora você entende por que não posso confiar esse trabalho aos meus homens?";
			link.l1 = "Sim. Quanto tempo eu tenho?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 a 15 dias, não mais. É importante pra mim que eles não cheguem ao esconderijo, senão não faz sentido afundar eles com a carga valiosa. Nesse caso, seria melhor se trouxessem tudo pra cá...";
			link.l1 = "Certo, eu topo. Vou tentar pegá-los.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка																			   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			//pchar.GenQuest.CaptainComission.PirateShips = "sdatkwest";	// лесник - заменил проверку для сдачи сразу.
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Não se preocupe. Meus homens vão levá-lo até o seu navio. E por que você se importa com ele?";
			link.l1 = "Eu não. Os parentes dele me pediram para trazê-lo.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, tudo bem. Quase fiquei com pena de oferecer um preço tão baixo pelo seu homem. Ha-ha-ha-ha. Adeus.";
			link.l1 = "Até mais.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen	
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																																			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");		// лесник																											 
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "Então, , "+GetFullName(pchar)+", você afundou meus camaradas? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Não. Não consegui pegá-los. E também não os encontrei no caminho de volta.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Fui eu. Mandei eles virarem comida de tubarão.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Droga! Se eu os encontrei ou não, tanto faz agora! E qual vai ser sua próxima sugestão?";
			link.l1 = "Talvez você tenha um trabalho mais fácil pra mim?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Escuta, "+NPChar.name+", abaixe o preço pelo prisioneiro...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Não.";
			link.l1 = "Adeus então...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Diminuir o preço?! Acabei de perder meu estoque por causa da sua incompetência! Agora é que eu posso aumentar o preço! Pode levar ele por 200.000 pesos se quiser, ou então caia fora daqui.";
			link.l1 = "Está caro demais... Adeus...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Droga, pega suas moedas.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow");		// лесник																								   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правка	// лесник																											 
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Pode levar esse fracote...";
			link.l1 = "Adeus.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правки имени в сж лесник																										  
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Muito bem! Leve seu fracote e boa sorte.";
			link.l1 = "Obrigado. Adeus.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
			/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "Trouxe o resgate "+GetSexPhrase("","ла")+"? Eu não estava brincando quando disse que o venderia para os fazendeiros.";			
			link.l1 = "Escuta, "+NPChar.name+", é o seguinte... Eu não tenho esse tipo de dinheiro. Mas estou disposto"+GetSexPhrase("","а")+" cumprir.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Que bom que você não o vendeu. Aqui estão suas moedas - 150.000 pesos. Onde posso encontrá-lo?"link.l2.go ="CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "Trouxe o dinheiro? Eu não estava brincando sobre vender aquele homem para a plantação.";			
			link.l1 = "Eu não tenho o dinheiro, "+NPChar.name+", mas estou cuidando disso.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Que bom que você não o vendeu. Aqui estão suas moedas – 150.000 pesos. Onde posso encontrá-lo?"link.l2.go ="CapComission2_3";
			}			
		break;

																																				 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "E por que você se importa com o que eu faço? Sabe, é melhor você ir embora...";
			link.l1 = "Tshh, calma aí. Tenho um assunto pra tratar com você. É sobre o seu prisioneiro.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Ah, tudo bem. Quem você quer resgatar?";
			link.l1 = "Espere. Não vim aqui para comprar ninguém, vim oferecer a chance de comprar um prisioneiro. E você ainda vai ter a oportunidade de conseguir um resgate por ele.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. E por que você precisa da minha ajuda? Por que não quer pegar o dinheiro direto pra você?";
			link.l1 = "Isso é bem arriscado pra mim. Posso ter problemas com as autoridades.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... tá bom então. Vamos dar uma olhada. Quem é seu prisioneiro?";
			link.l1 = "Isto é "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Entendo... seria uma troca justa, se você não estiver mentindo. Acho que posso te pagar por esse homem "+iTemp+" pesos ou então me traga alguma informação interessante. Você escolhe.";
			link.l1 = "É melhor eu pegar os pesos. Já cansei desse negócio...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha! Conte-me mais. Tenho certeza de que você tem algo interessante pra mim.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Dinheiro então. Pegue-os. Agora não é mais problema seu. Traga o objeto da venda aqui.";
			link.l1 = "Ele já deve estar perto dos portões da cidade agora. Obrigado! Você me ajudou de verdade.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "De nada, traga mais pra mim... Até mais!";
			link.l1 = "Boa sorte...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "É bom fazer negócios com um homem esperto. Agora escute: em alguns dias "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat")+" uma expedição espanhola vai chegar do continente, carregada de mercadorias valiosas. Eles vão esperar por um navio que deve levar a carga. Se você chegar lá dentro de uma semana, vai ter a chance de pegar a carga para você.\nSe eu fosse você, já estaria indo para o meu navio. E traga o prisioneiro aqui.";
					link.l1 = "Valeu! Essas mercadorias vão compensar bem o meu trabalho. E o meu passageiro já deve estar perto dos portões da cidade. Ele será trazido até você.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "É bom fazer negócios com um homem esperto. Agora escute: daqui a mais ou menos uma semana, um brigantino espanhol '"+pchar.GenQuest.Marginpassenger.ShipName1+"' carregado com mercadorias valiosas vai zarpar de "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" para "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". Se você se apressar, vai pegá-lo facilmente.\nAinda está aqui? Se eu fosse você, já estaria indo para o meu navio. E traga o prisioneiro aqui.";
					link.l1 = "Valeu! Essas mercadorias vão compensar bem o meu trabalho. E o meu passageiro já deve estar perto dos portões da cidade. Ele será trazido até você.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen: Abl - это к Залив"ом", нужен дательный
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen : как-то странно, наводку даёт Захар, а в сж Добряк дефолтом
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen 
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Roubo! Isso é inaceitável! Prepare-se, "+GetSexPhrase("garoto","garota")+"...","Ei, que diabos você está fazendo aí?! Achou que podia me roubar? Você está acabado...","Espera aí, mas que porra é essa? Tira as mãos de mim! Então você é um ladrão! Chegou seu fim, desgraçado...");
			link.l1 = LinkRandPhrase("Merda!","Caramba!!","Maldição!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Cai fora ","Cai fora")+" daqui!","Saia da minha casa!");
			link.l1 = "Opa...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Não me venha com suas conversas baratas. Da próxima vez, você não vai gostar do resultado...";
        			link.l1 = "Entendi.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Acabou, sem conversa.","Não quero mais conversar com você, então é melhor não me incomodar.");
			link.l1 = RandPhraseSimple("Como quiser...","Tá, então tá...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Espero que você mostre mais respeito e pare de ser grosseiro?";
        			link.l1 = "Pode ter certeza, Pastor, eu vou.";
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
            DoReloadCharacterToLocation("Puertoprincipe_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "Resolver o problema? Você faz ideia do que acabou de fazer? Enfim, traga-me um milhão de pesos e eu convenço os rapazes a esquecerem o que você fez. Se não gostou da ideia, pode ir para o inferno.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Certo, estou pronto para pagar.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Entendido. Estou indo embora.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Ótimo! Considere-se limpo de novo. Mas espero que não volte a fazer coisas tão nojentas.";
			link.l1 = "Não vou. Muito caro pra mim. Adeus...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		case "pirate_threat":
			if (GetNpcQuestPastDayWOInit(NPChar, "ThreatTalk") == 0)
			{
				dialog.text = NPCStringReactionRepeat("Já falamos sobre isso hoje.",
													  "Fui pouco claro?",
													  "Sua insistência já está passando dos limites.",
													  "Já estou de saco cheio. Cai fora!",
													  "repeat", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Então, deixamos pra outra vez...",
												   "Claro, "+npchar.name+"...",
												   "Desculpa, "+npchar.name+"...",
												   "Ai...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
				break;
			}
			if (iGPThreat != 0)
			{
				iBarbazonTotalTemp = 10 * iGPThreatRate;
				dialog.text = "Ha! A galera da nossa irmandade tá pegando no seu pé, né, " + GetSexPhrase("camarada", "amiga") + "? Claro que posso conter eles por um tempo. Mas você vai ter que desembolsar uma boa grana. " + FindRussianDublonString(iBarbazonTotalTemp) + " na mesa e temos um acordo.";
				if (PCharDublonsTotal() > iBarbazonTotalTemp)
				{
					if (iGPThreat < 5) link.l0 = "Claro, aqui está o seu dinheiro.";
					else link.l0 = "Parece que não tenho escolha. Aqui está o seu dinheiro.";
					link.l0.go = "pirate_threat_pay";
				}
				link.l1 = "Acho melhor voltar outra hora...";
				link.l1.go = "exit";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
				if (NextDiag.TempNode != "I_know_you_good")
					dialog.text = "Você ficou maluco" + GetSexPhrase("", "a") + "? Nossos caras fogem de você como o diabo foge da cruz. Some daqui e para de encher!";
				else
					dialog.text = "Do que você tá falando, " + GetSexPhrase("camarada", "amiga") + "? Você é uma dor de cabeça — até os cachorros sentem isso. Ninguém quer se meter contigo.";
				link.l1 = "Entendi...";
				link.l1.go = "exit";
			}
		break;
		
		case "pirate_threat_pay":
            iGPThreatRate = 0;
            iGPThreat = 0;
            SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
			RemoveDublonsFromPCharTotal(iBarbazonTotalTemp);
            DialogExit();
            PiratesDecreaseNotif("");
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
