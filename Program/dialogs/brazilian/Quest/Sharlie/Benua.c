int iBenuaPseudoGlobal;

// аббат Бенуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
    bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) // Addon 2016-1 Jason пиратская линейка 1
			{
				dialog.text = "É bom ver você, meu filho.  Veio aqui para acertar sua dívida?";
				if (PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
				{
					link.l1 = "Sim, pai. Sou eu.";
					link.l1.go = "FastStart_7";
				}
				else
				{
					link.l1 = "Desculpe pela demora, mas não estou aqui por isso. Mas logo estarei, pode ficar tranquilo.";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
			{
				dialog.text = "Precisa de alguma coisa, meu filho?";
				link.l1 = "Sim, pai. Eu gostaria de ver meu irmão, Michel de Montper. Ele disse...";
				link.l1.go = "escape";
				break;
			}
			dialog.text = "Precisa de alguma coisa, meu filho?";
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua"))
			{
				dialog.text = "Olá, meu filho. Fico feliz que tenha vindo. Queria conversar com você.";
				link.l1 = ""+TimeGreeting()+", padre. Pois bem, estou ouvindo.";
				link.l1.go = "SharlieEpilog_Benua_1";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_back"))
			{
				link.l99 = "Gostaria de falar sobre meu pai.";
				link.l99.go = "SharlieEpilog_Benua_3";
			}
			//<-- Эпилог
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Sim, padre. Preciso da sua ajuda. Meu nome é "+GetFullName(pchar)+". Michel de Montper me aconselhou a falar com você.";
				link.l1.go = "FastStart";
			}
			if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Sim, pai. Preciso da sua ajuda. Meu nome é "+GetFullName(pchar)+". Fui aconselhado a falar com você pelo meu irmão, Michel de Monper.";
				link.l1.go = "meet";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Sim, pai. Preciso de um navio para ajudar o Michel, mas acabei de chegar ao Caribe e estou sem um tostão. Meu irmão disse que o senhor poderia me emprestar algum dinheiro...";
				link.l1.go = "FastStart_2";
			}
			
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua"))
			{
				link.l1 = "Saudações, pai. Precisamos da sua ajuda – em um assunto um tanto incomum.";
				link.l1.go = "WildRose_Abb_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2") && PCharDublonsTotal() >= 800)
			{
				link.l3 = "Papai, consegui juntar a quantia necessária. Oitocentas moedas de ouro.";
				link.l3.go = "WildRose_Abb_14_pay";
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3"))
			{
				dialog.text = "Saudações, meu filho. Imagino que você veio saber o resultado do seu... hã, do seu caso?";
				link.l1 = "Tão perspicaz como sempre, pai. Não me faça esperar – diga, o que seu homem descobriu?";
				link.l1.go = "WildRose_Abb_16";
				break;
			}
			//<-- Дикая Роза
			if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Sim, pai. Preciso da sua ajuda.";
				if (CheckAttribute(npchar, "quest.relation_info")) link.l1.go = "help";
				else link.l1.go = "help_start";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
			{
				link.l2 = "Sim, pai. Eu estou.";
				link.l2.go = "FastStart_7";
			}
			link.l9 = "Não, nada, pai.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Benua_meeting":
			DelLandQuestMark(npchar);
			if(CheckAttribute(pchar, "questTemp.Sharlie.Citcount"))
				DeleteAttribute(pchar, "questTemp.Sharlie.Citcount");
			DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			dialog.text = "O que te traz até mim, meu filho?";
			link.l1 = "Olá, pai. Disseram-me para falar com o senhor. Meu nome é Charles de Maure. Estou procurando por Michel de Monper. Pelo que sei, ele deveria estar em algum lugar da Martinica. Eu sou... o irmão dele.";
			link.l1.go = "Benua_meeting_1";			
		break;
		
		case "Benua_meeting_1":
			dialog.text = "Irmão de Michel de Monper? De Maure? Que estranho...";
			link.l1 = "Eu entendo suas dúvidas, senhor. Só temos sobrenomes diferentes. Meu pai é Henri de Montper.";
			link.l1.go = "Benua_meeting_2";			
		break;
		
		case "Benua_meeting_2":
			dialog.text = "Ah, entendi agora. Eu conheci pessoalmente Henri de Monper. Vire-se para a luz, jovem. Isso! Você se parece muito com ele. Mesma aparência, mesmos traços nobres! Fico feliz em ver um filho de Henri de Monper em nossa paróquia.  Quanto à sua pergunta, posso lhe dizer que Michel é um oficial de alta patente da Ordem de Malta, mas ele está... com problemas. Felizmente, um dos cavaleiros da Ordem está me visitando neste momento. Acredito que ele possa concordar em acompanhá-lo até seu infeliz irmão—que o Senhor tenha piedade do destino dele...";
			link.l1 = "Quem é esse homem, padre?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;		
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}			
		break;
		
		case "Benua_meeting_3":
			DialogExit();
			NextDiag.CurrentNode = "Benua_meeting_repeat";
			AddQuestRecord("Sharlie", "4");
			pchar.quest.Sharlie_Benua.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Benua.win_condition.l1.date.hour  = 6;
			pchar.quest.Sharlie_Benua.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Sharlie_Benua.function = "Sharlie_BenuaMaltie";
		break;
		
		case "Benua_meeting_repeat":
			dialog.text = "Meu filho, volte amanhã de manhã. Por enquanto, não tenho mais nada a lhe dizer.";
			link.l1 = "Tudo bem.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Benua_meeting_repeat";
		break;
		
		/* case "Benua_maltie":
			dialog.text = "Olá, meu filho. Como prometido, a pessoa de quem falei ontem já está aqui esperando por você. Ele está pronto para levá-lo até seu irmão, que, pelo que ouvi, está em uma situação lamentável. Que o Senhor tenha piedade da alma dele...";
			link.l1 = "Quem é esse homem, padre?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break; */
		
		case "escape":
			dialog.text = "Sim, Charles, eu sei disso. Mas preciso te decepcionar. Michel não está aqui.";
			link.l1 = "O que quer dizer com ele não estar aqui? Ele disse que estaria me esperando na sua igreja! Padre, o que aconteceu? Onde está meu irmão?!";
			link.l1.go = "escape_1";
		break;
		
		case "escape_1":
			dialog.text = "Meu filho, seu irmão esteve aqui e saiu da minha modesta casa ontem à noite. Para onde foi, não sei. Mas ele deixou esta carta para você.";
			link.l1 = "Eu não acredito... depois de tudo que eu fiz por ele! Me dá essa carta!";
			link.l1.go = "escape_2";
		break;
		
		case "escape_2":
			dialog.text = "Não fique tão irritado, Charles. Aqui está a carta. Leia e depois... depois eu gostaria de conversar com você. Mas primeiro, leia a mensagem do seu irmão.";
			link.l1 = "Estou queimando de impaciência!";
			link.l1.go = "escape_3";
		break;
		
		case "escape_3":
			DialogExit();
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_mishelle");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Mishelle";
			NextDiag.CurrentNode = "escape_4";
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false); // лесник открыл входы
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", false);
		break;
		
		case "escape_4":
			if (CheckAttribute(pchar, "GenQuest.specialletter.read") && pchar.GenQuest.specialletter.read == "Letter_Mishelle")
			{
				dialog.text = "Vejo que você leu a carta. Agora, gostaria de lhe dizer algo, Charles...";
				link.l1 = "Mas... como isso é possível? Que tipo de absurdo é esse? Eu sei que meu irmão é estranho, mas ele não é louco!";
				link.l1.go = "escape_5";
			}
			else
			{
				dialog.text = "Meu filho, leia a carta. Conversaremos depois.";
				link.l1 = "Sim, pai...";
				link.l1.go = "exit";
				NextDiag.TempNode = "escape_4";
			}
		break;
		
		case "escape_5":
			dialog.text = "As ações do seu irmão também me surpreenderam, Charles. Ainda me pego perplexo às vezes. Um servo leal da Ordem e da Trindade, e mesmo assim está agindo como um desertor.";
			link.l1 = "Você faz ideia do que poderia causar um comportamento tão estranho?";
			link.l1.go = "escape_6";
		break;
		
		case "escape_6":
			dialog.text = "Infelizmente, não sei. Mas suponho que ele tenha seus próprios motivos, motivos profundos. Renegar todo o próprio passado só pode indicar uma razão muito séria. Nem consigo imaginar o que pode ser. Mas sinto que envolve algo muito ruim... talvez até terrível.";
			link.l1 = "O que será, pai?";
			link.l1.go = "escape_7";
		break;
		
		case "escape_7":
			dialog.text = "Meu filho, um padre não enxerga com os olhos, mas com o coração. Não posso te explicar em palavras, mas... seu irmão partiu para fazer algo impuro, algo abominável. Nunca pensei que minha boca pudesse dizer isso. No entanto...";
			link.l1 = "Bem, não duvido que meu irmão tenha tramado alguma coisa pelas costas. Consigo até imaginar exatamente o que ele está planejando. Esse 'algo' é amarelo e faz um barulhinho agradável quando tilinta.";
			link.l1.go = "escape_8";
		break;
		
		case "escape_8":
			dialog.text = "Não acho que seja a cobiça pelo ouro que move seu irmão. Eu diria que ele busca algo maior.";
			link.l1 = "Aprendi muito com Michel e entendi sua filosofia, então acho que consigo perceber o que é importante para ele e o que não é. Mas vou levar suas palavras a sério, pai.";
			link.l1.go = "escape_9";
		break;
		
		case "escape_9":
			dialog.text = "Deus te abençoe, meu filho. Vai, vai agora. Que o Senhor te proteja!";
			link.l1 = "Obrigado, pai. Adeus!";
			link.l1.go = "escape_10";
		break;
		
		case "escape_10":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddDialogExitQuestFunction("Sharlie_Benua_BrotherEscape");
		break;
		
		// уменьшение награды за голову
		case "meet":
			dialog.text = "Irmão de Michel de Monper? De Maure? Que estranho...";
			link.l1 = "Eu entendo suas dúvidas, senhor. Só temos sobrenomes diferentes. Meu pai é Henri de Montper.";
			link.l1.go = "meet_1";			
		break;
		
		case "meet_1":
			dialog.text = "Ah, entendi agora. Eu conheci Henri de Monper pessoalmente. Vire-se para a luz, jovem... Isso! Você é a cara dele. Mesmos traços, mesmo perfil nobre! Fico feliz em ver um filho de Henri de Monper em nossa paróquia.\nJá tinha ouvido dizer que Michel recebeu a visita de um homem vindo da Europa, mas nunca imaginei que fosse o próprio irmão. Espero que você consiga ajudar Michel, ele está passando por um momento difícil. Enfim, em que posso ajudar?";
			link.l1 = "O Michel me disse que você poderia me ajudar se eu tivesse problemas com as autoridades.";
			link.l1.go = "help_info";	
			npchar.quest.meet = true;
		break;
		
		case "help_info":
			dialog.text = "Foi isso que Michel lhe disse? Entendo. Bem, posso ajudar nesse tipo de situação. Tenho certa influência tanto na Santa Igreja Romana quanto nas colônias holandesas. Por isso, talvez eu consiga interceder por você junto às autoridades espanholas e holandesas. Claro, não poderei fazer muito se sua má conduta for grave demais – nesse caso, só será possível aliviar um pouco a situação. Será preciso interceder várias vezes para uma reconciliação completa. Além disso, de qualquer forma, você terá que me fornecer dobrões de ouro para obras de caridade e despesas de viagem. E só posso ajudar com uma nação por vez. Se aceitar esses termos, não hesite em me procurar, e veremos o que pode ser feito.";
			link.l1 = "Obrigado! Vou me lembrar disso.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "help_start":
			dialog.text = "O que posso fazer por você, meu filho? Fale, estou ouvindo.";
			link.l1 = "O Michel me disse que você poderia me ajudar se eu tivesse problemas com as autoridades.";
			link.l1.go = "help_info";
		break;
		
		case "help":
			dialog.text = "Como posso ajudar você, meu filho?";
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater"))
			{
				link.l1 = "Vamos voltar à questão do pagamento pela entrega das ordens.";
				link.l1.go = "SharlieEpilog_Benua_DublonsLater_2";
			}
			if (CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				link.l1 = "Quero enviar uma ordem...";
				link.l1.go = "SharlieEpilog_Benua_Delivery";
			}
			//<-- Эпилог
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "Me meti em encrenca com as autoridades espanholas.";
				link.l1.go = "relation_spa";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "Me meti em encrenca com as autoridades holandesas.";
				link.l2.go = "relation_hol";
			}
			link.l9 = "Desculpe, acho que desta vez vou resolver as coisas sozinho.";
			link.l9.go = "exit";
		break;
		
		case "relation_spa": // patch-10
			pchar.GenQuest.BenuaNation = SPAIN;
			dialog.text = "Então, os nobres senhores estão ansiosos para te jogar nas masmorras de Havana...";
			link.l1 = "Exatamente assim, pai...";
			link.l1.go = "relation";
		break;
		
		case "relation_hol":
			pchar.GenQuest.BenuaNation = HOLLAND;
			dialog.text = "Então, os mercadores espertos estão ansiosos para te jogar nas masmorras de Willemstad...";
			link.l1 = "Exatamente isso, pai...";
			link.l1.go = "relation";
		break;
		
		case "relation":
			rate = wdmGetNationThreat(sti(pchar.GenQuest.BenuaNation));
			iBenuaPseudoGlobal = DiplomatDublonPayment(rate, "Benua", false);
			sTemp = FindRussianDublonString(iBenuaPseudoGlobal);
			if (rate < 2)
			{
				dialog.text = "Sim, esses boatos também chegaram à nossa igreja. Posso ajudá-lo com esse dilema. É algo que pode ser resolvido. Eu preciso "+sTemp+" para amenizar sua situação.";
				if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
				{
					link.l1 = "Ótimo! Aqui está o ouro.";
					link.l1.go = "agree";
				}
				link.l2 = "Então é a hora certa para eu encontrar os dobrões.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate < 4)
				{
					dialog.text = "Sim, os rumores sobre seus 'feitos' também chegaram à nossa igreja. Você manchou sua reputação, meu filho. Deveria ser mais prudente. Mas posso ajudá-lo. Eu preciso "+sTemp+" para amenizar sua situação.";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "Ótimo! Aqui está o ouro.";
						link.l1.go = "agree";
					}
					link.l2 = "Então chegou a hora certa de eu procurar os dobrões.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Sim, meu filho. Você é tão desesperado quanto seu irmão... Deve ser coisa de família. Não posso resolver tudo, mas acredito que posso aliviar um pouco sua situação lamentável. E depois podemos fazer mais oferendas, se quiser. Eu preciso "+sTemp+" por enquanto e vou começar a resolver seu dilema imediatamente.";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "Ótimo! Aqui está o ouro.";
						link.l1.go = "agree";
					}
					link.l2 = "Então é a hora certa para eu encontrar os dobrões.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iBenuaPseudoGlobal); // Sinistra legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Agora você vai ter que esperar pelo menos duas semanas. Acho que nesse tempo vou conseguir encontrar e conversar com as pessoas certas.";
			link.l1 = "Obrigado, pai! Estarei esperando...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            bOk = HasShipTrait(pchar, "trait23");
            rate = 10 + hrand(5);
            rate = GetIntByCondition(bOk, rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, rate, false);
			pchar.GenQuest.BenuaNation.Rate = GetDiplomatRate(bOk, sti(pchar.GenQuest.BenuaNation));
			npchar.quest.relation = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка 1
		case "FastStart":
			dialog.text = "De Maure? E você é irmão de Michel de Monper? Que estranho...";
			link.l1 = "Eu entendo suas dúvidas, padre. Meu pai é Henri de Montper.";
			link.l1.go = "FastStart_1";			
		break;
		
		case "FastStart_1":
			dialog.text = "A-ah, entendi. Eu conhecia Henri de Monper pessoalmente. Venha para a luz, rapaz. Isso! Os mesmos olhos, os mesmos traços nobres! Fico feliz em ver um filho de Henri de Monper na minha igreja. Espero que consiga ajudar seu irmão. Ele tem passado por muita dificuldade ultimamente.";
			link.l1 = "Sim, pai. Preciso de um navio para ajudar o Michel, mas acabei de chegar ao Caribe e estou sem um tostão. Meu irmão disse que o senhor poderia me emprestar algum dinheiro...";
			link.l1.go = "FastStart_2";	
			npchar.quest.meet = true;
		break;
		
		case "FastStart_2":
			DelLandQuestMark(npchar);
			dialog.text = "Michel te contou isso?";
			link.l1 = "Padre, talvez eu não pareça muito confiável, mas é verdade. Quanto antes eu conseguir um navio, mais cedo vou poder tirar meu irmão da prisão.";
			link.l1.go = "FastStart_3";
		break;
		
		case "FastStart_3":
			dialog.text = "Entendo, meu filho. Vejo que está falando a verdade. Bem, pelo Michel e pelo seu pai, vou te ajudar. Tenho algumas economias, pode ficar com elas. Imagino que 50.000 pesos e 100 dobrões sejam suficientes.";
			link.l1 = "Obrigado, padre. Quais são os termos?";
			link.l1.go = "FastStart_4";
		break;
		
		case "FastStart_4":
			AddMoneyToCharacter(pchar, 50000);
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Sem pressão. Meio ano para pagar já está bom.";
			link.l1 = "Muito bem, padre. Muito obrigado mais uma vez!";
			link.l1.go = "FastStart_5";
		break;
		
		case "FastStart_5":
			dialog.text = "Vá com a minha bênção, meu filho.";
			link.l1 = "...";
			link.l1.go = "FastStart_6";
		break;
		
		case "FastStart_6":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			npchar.quest.FastStart = "true";
			pchar.questTemp.Sharlie.BenuaLoan = "true";
			SetFunctionTimerCondition("Sharlie_BenuaLoanTime", 0, 0, 180, false);
			AddQuestRecord("Sharlie", "5-2");
		break;
		
		case "FastStart_7":
			dialog.text = "Excelente, meu filho. Espero que aquele dinheiro tenha lhe sido útil.";
			link.l1 = "De fato, conseguiu! Obrigado!";
			link.l1.go = "FastStart_8";
		break;
		
		case "FastStart_8":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddMoneyToCharacter(pchar, -50000);
			RemoveDublonsFromPCharTotal(100);
			pchar.quest.Sharlie_BenuaLoanTime.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.BenuaLoan");
			AddQuestRecord("Sharlie", "5-3");
		break;
		
		// Jason Долго и счастливо
		case "LH_abbat":
			dialog.text = "Charles, não acredito no que estou vendo! O que te traz aqui?!";
			link.l1 = "Abençoe-me, Santo Padre, pois venho trazer boas notícias – vou me casar e gostaria que fosse o senhor a celebrar meu casamento.";
			link.l1.go = "LH_abbat_1";
		break;
		
		case "LH_abbat_1":
			dialog.text = "Meu filho, isso é maravilhoso! Então você recebeu aquela carta do seu pai e decidiu, como sempre, agir do seu próprio jeito? Fico realmente feliz por você! Mas receio que não posso te ajudar, a menos que decida se casar nesta igreja.";
			link.l1 = "Entendo que sua missão está em um impasse, Santo Padre. Posso ajudá-lo em algo? Já que o casamento acontecerá numa capela espanhola, é claro que seria uma aventura que eu gostaria de viver, mas estou decidido a realizar a celebração na Martinica. Moderadamente magnífica, e com a presença de testemunhas respeitáveis e convidados honrados.";
			link.l1.go = "LH_abbat_2";
		break;
		
		case "LH_abbat_2":
			dialog.text = "I'm sorry, my son, but all your authority is worth nothing against the stubbornness of the highest hierarchs of the Catholic Church, especially in the Spanish colonies. We haven't agreed on the question of sharing the influence of the Catholic missions between our countries, and now I'm here, as an honoured guest and an honoured hostage. The Spaniards are waiting for a better offer from our side. I have sent a message to Europe; hopefully the answer will come in two months' time and we will be able to resume negotiations. If it doesn't arrive in two months, it will certainly be here within the next six months.\nAnd yes, while the Pope and Mazarin have reached a compromise in the last couple of weeks, it's too early to talk about a truly warm relationship. Honestly, I'm not sure that we will ever come to any agreement. It seems to me that Palotti simply keeps me as a bargaining chip in his own political power plays. However, I have to say, the inquisitor has excellent coffee!";
			link.l1 = "Eu não tenho nem seis meses, nem dois meses! Preciso cumprir o desejo do meu pai, ou ele vai me obrigar a casar contra a minha vontade. E a saúde dele já não é mais a mesma, mas eu gostaria de ter tempo para apresentá-lo à minha escolhida, a futura senhora de Monper.";
			link.l1.go = "LH_abbat_3";
		break;
		
		case "LH_abbat_3":
			dialog.text = "Receio que você terá que encontrar outro padre para o seu casamento então, meu filho. Infelizmente, vou ficar aqui por muito tempo.";
			link.l1 = "O que você diria se eu te tirasse do café do inquisidor?";
			link.l1.go = "LH_abbat_4";
		break;
		
		case "LH_abbat_4":
			dialog.text = "Eu aceitaria sua ajuda de bom grado. Suspeito que não fui escolhido para esta missão por acaso. No pior dos casos, simplesmente esquecerão do Padre Benoit. E, embora o Senhor tenha me ordenado suportar, me sinto sobrecarregado com minha conclusão, apesar de todas as suas... bênçãos. Mas, repito - é pouco provável que o Padre Palotti vá atender aos seus pedidos.";
			link.l1 = "Então vou poupar meu tempo e nem vou tentar convencê-lo. Assim que a missa acabar, sairemos direto da igreja e iremos para o meu navio. Não hesite, Padre – eles já viram nosso encontro e vão me reconhecer, e será muito mais difícil ajudá-lo se eu tiver que tirá-lo da mansão do governador.";
			link.l1.go = "LH_abbat_5";
		break;
		
		case "LH_abbat_5":
			dialog.text = "É arriscado, meu filho, muito arriscado. Um grupo de guardas está esperando lá fora para me escoltar até a mansão, e a cidade está cheia de soldados.";
			link.l1 = "Vamos apostar no elemento surpresa, Padre Benoit. Só precisa confiar em mim e tudo vai dar certo. Eu tenho uma certa... experiência nesse tipo de situação.";
			link.l1.go = "LH_abbat_6";
		break;
		
		case "LH_abbat_6":
			dialog.text = "Como quiser. Mas, por favor, faça isso sem derramamento de sangue desnecessário! Eu também já passei por situações assim... Guie-nos, meu filho. Estou logo atrás de você. Mas não vou pegar em armas, então nem me peça.";
			link.l1 = "Nem pensei nisso, pai. Eu dou conta. Me siga, mas tome cuidado, podem atirar na gente.";
			link.l1.go = "LH_abbat_7";
		break;
		
		case "LH_abbat_7":
			DialogExit();
			LongHappy_SantiagoBenuaEscape();
		break;
		
		case "LH_abbat_8":
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);
			dialog.text = "Meu filho, não tive tempo de te agradecer por me tirar da prisão. Pelo visto, o bispo espanhol e o inquisidor Palotti queriam atrapalhar as novas relações entre nosso cardeal e a Santa Sé, então você agiu totalmente nos interesses do nosso país. Mais uma vez. Mas ninguém vai dizer 'obrigado', além de mim.";
			link.l1 = "Coisa comum, Padre. Fico feliz por ter conseguido ajudar. Mas também preciso lhe pedir um favor, lembra?";
			link.l1.go = "LH_abbat_9";
		break;
		
		case "LH_abbat_9":
			dialog.text = "Claro! Então vamos ao que interessa – Charles, como estão os preparativos para o seu grande dia?";
			link.l1 = "Está tomando forma aos poucos. Já vi campanhas militares serem preparadas com mais facilidade e rapidez, mas vale a pena!";
			link.l1.go = "LH_abbat_10";
		break;
		
		case "LH_abbat_10":
			dialog.text = "Claro, meu filho! E nesta ocasião, quero esclarecer uma coisa – como você imagina a sua cerimônia de casamento?";
			link.l1 = "Quer dizer, o quão pomposo?";
			link.l1.go = "LH_abbat_11";
		break;
		
		case "LH_abbat_11":
			dialog.text = "Claro! Preciso preparar a igreja, e talvez você queira convidar algumas pessoas importantes.";
			link.l1 = "Nada de especial, Santo Padre. Aqueles que considero nossos amigos vão nos esperar em outro lugar. Aqui só estarão alguns oficiais, meus homens e alguns curiosos comuns.";
			link.l1.go = "LH_abbat_12";
		break;
		
		case "LH_abbat_12":
			dialog.text = "Bem, então, acho que podemos resolver isso com uma pequena doação.";
			link.l1 = "Isso não parece tão assustador assim. E quanto custa uma doação dessas em ouro?";
			link.l1.go = "LH_abbat_13";
		break;
		
		case "LH_abbat_13":
			dialog.text = "Para o coro, o serviço solene e outras despesas – cento e cinquenta, não mais. Além disso, a doação habitual dos noivos, no total – duzentos doblões.";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "Aqui está, Santo Padre.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "Sobre aquelas campanhas militares... Vou ter que ir até o banco e voltar.";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_14":
			DialogExit();
			npchar.dialog.currentnode = "LH_abbat_14_1";
		break;
		
		case "LH_abbat_14_1":
			dialog.text = "E a sua doação, meu filho?";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "Aqui está, Santo Padre.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "Sim, sim, eu vou trazer em breve...";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_15":
			RemoveDublonsFromPCharTotal(200); // Sinistra legendary edition
			dialog.text = "Ainda resta uma pergunta a ser respondida - quem entregará a noiva e será testemunha do casamento em nome dela?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				pchar.questTemp.LongHappy.Pater1 = "Svenson";
				link.l1 = "Jan Svensson, da Blueweld. Ele é inglês, mas um homem respeitado e apegado à Helen como se fosse sua própria filha, e a mãe adotiva dela é Gladys McArthur.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					pchar.questTemp.LongHappy.Pater1 = "Noel";
					link.l1 = "Barão Noël Forget, tenho certeza de que ele me dará essa honra.";
				}
				else
				{
					pchar.questTemp.LongHappy.Pater1 = "Puancie";
					link.l1 = "Cavaleiro Philippe de Poincy, tenho certeza de que ele me concederá essa honra.";
				}
			}
			link.l1.go = "LH_abbat_16";
		break;
		
		case "LH_abbat_16":
			dialog.text = "Bem, e quem vai testemunhar pelo noivo? Lembre-se, tem que ser um homem de nascimento nobre e reputação ilibada.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					link.l1 = "Barão Noël Forget, tenho certeza de que ele me dará essa honra.";
					link.l1.go = "LH_abbat_17_1";
				}
				else
				{
					link.l1 = "Cavaleiro Philippe de Poincy, tenho certeza de que ele me concederá essa honra.";
					link.l1.go = "LH_abbat_17_2";
				}
				link.l2 = "Fadey é um comerciante respeitável de Guadalupe. Só preciso comprar a bebida favorita dele.";
				link.l2.go = "LH_abbat_17_3";
			}
			else
			{
				link.l1 = "Fadey é um comerciante respeitável de Guadalupe. Só preciso providenciar a bebida preferida dele.";
				link.l1.go = "LH_abbat_17_3";
			}
		break;
		
		case "LH_abbat_17_1":
			pchar.questTemp.LongHappy.Pater2 = "Noel";
			dialog.text = "Ótimo, vou enviar os convites, mas os convidados vão precisar de um tempo para chegar. Acredito que tudo estará pronto em um mês, e as pessoas designadas já terão chegado à cidade.";
			link.l1 = "Ótimo! Então tenho tempo para resolver algumas coisas. Até logo, Santo Padre, e me deseje sorte!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_2":
			pchar.questTemp.LongHappy.Pater2 = "Puancie";
			dialog.text = "Ótimo, vou enviar os convites, mas os convidados vão precisar de um tempo para chegar. Acho que tudo estará pronto em um mês, e as pessoas convidadas já terão chegado à cidade.";
			link.l1 = "Ótimo! Então tenho tempo para resolver algumas coisas. Até logo, Santo Padre, e me deseje sorte!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_3":
			pchar.questTemp.LongHappy.Pater2 = "Fadey";
			dialog.text = "Ótimo, vou enviar os convites, mas os convidados vão precisar de um tempo para chegar. Acho que tudo estará pronto em um mês, e as pessoas indicadas já terão chegado à cidade.";
			link.l1 = "Ótimo! Então tenho tempo para resolver algumas coisas. Até logo, Santo Padre, e torça por mim!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_18":
			DialogExit();
			AddQuestRecord("LongHappy", "11");
			SetFunctionTimerCondition("LongHappy_SenPierreGuests", 0, 0, 31, false); // таймер
			if (!CheckAttribute(pchar, "questTemp.LongHappy.MarryRum"))
			{
			pchar.questTemp.LongHappy = "toIslaTesoro";
			LocatorReloadEnterDisable("Pirates_town", "reload4_back", true);//закрыть таверну Исла-Тесоро
			}
			npchar.dialog.currentnode = "First time";
		break;
		
		case "LH_abbat_19":
			dialog.text = "Então, chegou o grande dia, meu filho! Está tudo pronto – em poucas horas poderemos começar. Você está pálido!";
			link.l1 = "Estou um pouco nervoso, Santo Padre.";
			link.l1.go = "LH_abbat_20";
		break;
		
		case "LH_abbat_20":
			dialog.text = "Isso é normal. Este é o dia mais importante da sua vida, e estou sinceramente feliz por você, assim como todos que vieram. Espero que pelo menos se lembre das orações básicas – você nunca foi exatamente um frequentador assíduo da igreja, não é? De qualquer forma, vou te ajudar no que precisar.\nE mais uma coisa – pelo que entendi, a noiva não vai abrir mão de seus princípios e não a veremos de vestido? Pois bem, a alta sociedade está prestes a presenciar mais uma das suas surpresas – você realmente não para de surpreender. Agora vá, meu filho, se apronte e vamos começar.";
			link.l1 = "Sim, Santo Padre. Vamos fazer isso.";
			link.l1.go = "LH_abbat_21";
		break;
		
		case "LH_abbat_21":
			DialogExit();
			chrDisableReloadToLocation = true;
			WaitDate("", 0, 0, 0, 2, 0);
			DoQuestReloadToLocation("FortFrance_church", "reload", "reload1", "LongHappy_MarryInit");
		break;
		
		case "LH_abbat_22":
			pchar.questTemp.LongHappy.Mistake = 0;
			dialog.text = "Pater noster, qui es in caelis, sanctificetur nomen tuum, ad...";
			link.l1 = "...adveniat regnum tuum";
			link.l1.go = "LH_abbat_23_1";
			link.l2 = "...requiem aeternam dona eis";
			link.l2.go = "LH_abbat_23_2";
		break;
		
		case "LH_abbat_23_1":
			dialog.text = "...fiat voluntas tua, sicut in caelo et in terra. O pão nosso de cada dia nos dai hoje, e perdoai as nossas dívidas se...";
			link.l1 = "...assim como nós perdoamos a quem nos tem ofendido";
			link.l1.go = "LH_abbat_24_1";
			link.l2 = "...sicut erat in principio, et nunc et semper, et in saecula saeculorum. Amen";
			link.l2.go = "LH_abbat_24_2";
		break;
		
		case "LH_abbat_23_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "E-e... Hm...";
			link.l1 = "";
			link.l1.go = "LH_abbat_23_1";
		break;
		
		case "LH_abbat_24_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "E-e... Hm...";
			link.l1 = "";
			link.l1.go = "LH_abbat_24_1";
		break;
		
		case "LH_abbat_24_1":
			dialog.text = "et ne nos inducas in tentationem; sed libera nos a malo. Amen.";
			link.l1 = "Amém.";
			link.l1.go = "LH_abbat_25";
		break;
		
		case "LH_abbat_25":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Queridos, estamos aqui reunidos diante de Deus, e na presença desta congregação, para unir este homem e esta mulher em santo matrimônio. Amados "+sld.name+" e Charles, você ouviu a palavra de Deus, que lhe lembrou o significado do amor humano e do matrimônio. Agora, em nome da Santa Igreja, desejo questionar suas intenções.\n"+sld.name+" e Charles, você tem o desejo voluntário e sincero de unir-se em matrimônio diante do nosso Senhor?";
			link.l1 = "Sim.";
			link.l1.go = "LH_abbat_26";
		break;
		
		case "LH_abbat_26":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_27":
			dialog.text = "Vocês pretendem permanecer fiéis um ao outro na saúde e na doença, na alegria e na tristeza, até o fim de seus dias?";
			link.l1 = "Sim.";
			link.l1.go = "LH_abbat_28";
		break;
		
		case "LH_abbat_28":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_22";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_29":
			dialog.text = "Você pretende amar e aceitar os filhos que nosso Senhor lhe enviar, e criá-los na fé cristã?";
			link.l1 = "Sim.";
			link.l1.go = "LH_abbat_30";
		break;
		
		case "LH_abbat_30":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_31":
			dialog.text = "Bem, virem-se um para o outro e façam um voto.";
			link.l1 = "";
			link.l1.go = "LH_abbat_32";
		break;
		
		case "LH_abbat_32":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_33":
			dialog.text = "Se alguém aqui presente souber de algum motivo pelo qual este casal não deva ser unido em santo matrimônio, fale agora ou cale-se para sempre.\nNeste caso, diante do Senhor e das pessoas aqui reunidas, eu os declaro marido e mulher! Em nome do Pai, do Filho e do Espírito Santo. Amém.";
			link.l1 = "Amém.";
			link.l1.go = "LH_abbat_34";
		break;
		
		case "LH_abbat_34":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_35":
			string sTemp;
			if (sti(pchar.questTemp.LongHappy.Mistake) > 1) sTemp = "(Whispering) Charles, my son, just move your lips, I beg you - don't try to make any sound...";
			else sTemp = "";
			dialog.text = "Recém-casados, ajoelhem-se e rezem juntos. Oratio fidelium. "+sTemp+"";
			link.l1 = "";
			link.l1.go = "LH_abbat_36";
		break;
		
		case "LH_abbat_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.lastname = "de Maure";
			sld.SpecialRole = "wife";
			sld.dialog.currentnode = "LongHappy_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 4.0);
		break;
		
		case "LH_abbat_37":
			dialog.text = "Meus parabéns, filho. Seu pai teria orgulho de você, e eu também tenho. Sejam felizes e cuidem um do outro nestes tempos difíceis.";
			link.l1 = "Obrigado, Santo Padre. Foi uma cerimônia maravilhosa e fico feliz que tenha sido o senhor a conduzi-la.";
			link.l1.go = "LH_abbat_38";
		break;
		
		//--> Дикая Роза
		case "WildRose_Abb_2":
			dialog.text = "Então vieram a mim em busca de conselho, meus filhos? Pois bem, estou ouvindo.";
			link.l1 = "Na verdade, por ajuda, pai. Ajuda de um homem que tem conexões e conhece todo tipo de gente...";
			link.l1.go = "WildRose_Abb_3";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua");
		break;

		case "WildRose_Abb_3":
			dialog.text = "Perdoe-me por interrompê-lo, meu filho, mas devo lembrar que sou apenas um humilde abade, não algum agente secreto.";
			link.l1 = "Mas um humilde abade pode conhecer um agente secreto, não pode? Ou pelo menos sugerir como alguém poderia encontrá-lo?";
			link.l1.go = "WildRose_Abb_4_fortune";
			link.l2 = "O assunto que nos trouxe aqui realmente diz respeito a certos segredos há muito esquecidos... Só estamos tentando trazê-los de volta à luz.";
			link.l2.go = "WildRose_Abb_4_stealth";
		break;

		case "WildRose_Abb_4_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Agora, jovem, isso não me agrada. Seja direto, e então veremos como – ou se – posso ajudá-lo.";
			link.l1 = "Sim, pai. Vou tentar ser breve...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_4_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = ""+pchar.name+", não fale em enigmas – confesso que isso é cansativo.";
			link.l1 = "Sim, pai. Vou tentar ser breve...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_5":
			dialog.text = "Vá em frente, meu filho.";
			link.l1 = "Minha companheira, Mary Casper, está procurando por seu pai – ou pelo menos por alguma pista sobre ele. Descobrimos que ele foi oficial da Marinha Inglesa e serviu a bordo da escuna 'Wrangler', que naufragou no Cabo Catoche em 1638.";
			link.l1.go = "WildRose_Abb_6";
		break;

		case "WildRose_Abb_6":
			dialog.text = "E você ainda espera que ele esteja vivo? Depois de tantos anos?";
			link.l1 = "Mesmo que ele não tenha sobrevivido ao naufrágio, Mary quer saber de onde veio seu pai, que tipo de homem ele era, a vida que levou... Os documentos oficiais têm poucos detalhes – mas mesmo neles pode-se encontrar algo de valor, não acha, Padre?";
			link.l1.go = "WildRose_Abb_7";
		break;

		case "WildRose_Abb_7":
			dialog.text = "Você está certo no seu raciocínio, meu filho. O que você faz é nobre e digno. Mas ainda não entendo exatamente o que espera de mim.";
			link.l1 = "Você já vive há muito tempo no Arquipélago, pai. Talvez conheça alguém que tenha acesso aos arquivos coloniais sobre oficiais da Marinha Inglesa?";
			link.l1.go = "WildRose_Abb_8_stealth";
			link.l2 = "Precisamos de alguém com acesso aos arquivos coloniais onde ficam os registros dos oficiais navais ingleses. Certamente o senhor conhece alguém assim, Padre.";
			link.l2.go = "WildRose_Abb_8_charisma";
		break;

		case "WildRose_Abb_8_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "Você entende o que está pedindo, meu filho? A questão não é só que tal informação pode ser um segredo militar...";
			link.l1 = "E o que mais então, pai? Vou falar abertamente...";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_8_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Você entende o que está pedindo, meu filho? A questão não é só que tal informação pode ser um segredo militar...";
			link.l1 = "E o que mais então, pai? Vou falar abertamente...";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_9":
			dialog.text = "O problema está justamente nesses arquivos coloniais. Vinte anos atrás, a Jamaica estava sob domínio espanhol, e St. John’s e Bridgetown viviam sob constante ameaça de ataques. É improvável que houvesse navios da Marinha Real estacionados por lá...";
			link.l1 = "Quer dizer os arquivos da Marinha em Londres, pai?";
			link.l1.go = "WildRose_Abb_10";
		break;

		case "WildRose_Abb_10":
			dialog.text = "Talvez. Os documentos deveriam ter sido enviados para o Almirantado. Conseguir eles não será fácil.";
			link.l1 = "Mas é possível fazer isso, não é, pai?";
			link.l1.go = "WildRose_Abb_11";
		break;

		case "WildRose_Abb_11":
			dialog.text = "Nada é impossível, meu filho. Mas isso vai exigir esforço... e pagamento.";
			link.l1 = "Claro, pai. Devo entregar o dinheiro para você ou preciso encontrar outra pessoa?";
			link.l1.go = "WildRose_Abb_12";
		break;

		case "WildRose_Abb_12":
			dialog.text = "Eu mesmo vou encontrar outra pessoa, meu filho. O que eu preciso de você é... oitocentos dobrões.";
			link.l1 = "Muito bem, pai. Quanto tempo isso vai levar?";
			link.l1.go = "WildRose_Abb_13";
		break;

		case "WildRose_Abb_13":
			dialog.text = "Acho que uns dois meses. E, aliás, você ainda não me disse o nome de quem está procurando.";
			link.l1 = "O nome daquele homem é Joshua Casper.";
			link.l1.go = "WildRose_Abb_14";
		break;

		case "WildRose_Abb_14":
			dialog.text = "Vou me lembrar disso. Se estiver pronto para me entregar o valor total agora — mandarei notícias já amanhã.";
			if (PCharDublonsTotal() >= 800)
			{
				link.l1 = "Claro, pai. Aqui, pegue. Oitocentas moedas de ouro.";
				link.l1.go = "WildRose_Abb_14_pay";
			}
			link.l2 = "Não, pai, não tenho esse dinheiro comigo. Mas voltarei em breve e trarei o que precisa.";
			link.l2.go = "WildRose_Abb_14_nopay";
		break;

		case "WildRose_Abb_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "Muito bem, "+pchar.name+". Volte em dois meses – tenho certeza de que até lá terei uma resposta para você.";
			link.l1 = "Obrigado, pai. Até nos encontrarmos de novo!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2");
		break;

		case "WildRose_Abb_14_nopay":
			dialog.text = "Como você diz, meu filho.";
			link.l1 = "Eu voltarei em breve.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			pchar.questTemp.WildRose_Etap3_Benua_2 = true;
		break;
		
		case "WildRose_Abb_16":
			dialog.text = "Ele aprendeu tanto sobre Joshua Casper quanto sobre seu navio – que, no entanto, não era o 'Wrangler'. Nenhum brigue com esse nome jamais pertenceu à Marinha Real.";
			link.l1 = "Hm... Tenho absoluta certeza de que o navio em que Joshua Casper serviu tinha esse nome. E quanto ao próprio Joshua?";
			link.l1.go = "WildRose_Abb_17";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3");
		break;

		case "WildRose_Abb_17":
			dialog.text = "Aquele homem foi um oficial exemplar, com muitos méritos e condecorações – tudo registrado em seu arquivo pessoal. Embora não professasse a verdadeira fé, era um capitão digno. Mademoiselle pode, com razão, se orgulhar de tais origens.";
			link.l1 = "Isso são boas notícias, pai. Mas, se me permite, vamos voltar ao navio. Se não era o 'Wrangler', então qual era o nome dele?";
			link.l1.go = "WildRose_Abb_19";
			AddQuestRecordInfo("WildRose_Records_3", "1");
		break;

		case "WildRose_Abb_19":
			dialog.text = "'Cornwall'. Ele partiu de Plymouth em janeiro de 1638 com ordens para entregar os salários às guarnições de Antígua e Providência.";
			link.l1 = "Incrível...";
			link.l1.go = "WildRose_Abb_20";
			AddQuestRecordInfo("WildRose_Records_4", "1");
		break;

		case "WildRose_Abb_20":
			dialog.text = "Se o navio chegou ao seu destino final, eu não sei. Mas ele fez escala em St. John’s. No escritório do porto ainda há um relatório do capitão Casper datado de 2 de junho daquele ano.";
			link.l1 = "Eu sabia que você não era tão simples quanto tenta parecer, pai! Este documento, imagino, traz alguns detalhes importantes?";
			link.l1.go = "WildRose_Abb_21_charisma";
			link.l2 = "Estamos eternamente em dívida com o senhor, padre. Já que mencionou esse documento – então ele deve conter algo importante, não?";
			link.l2.go = "WildRose_Abb_21_honor";
			AddQuestRecordInfo("WildRose_Records_5", "1");
		break;

		case "WildRose_Abb_21_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Apenas um relatório sobre a batalha com o galeão espanhol 'Toro' perto dos Açores, na qual um terço da tripulação morreu – leia o relatório, está tudo lá.";
			link.l1 = "Mais uma pergunta: já que você teve acesso aos registros da autoridade portuária de Antígua, por acaso encontrou o nome do Joshua Casper em algum outro lugar?";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_21_honor":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "Apenas um relatório sobre a batalha com o galeão espanhol 'Toro' perto dos Açores, na qual um terço da tripulação pereceu – leia o relatório, está tudo lá.";
			link.l1 = "Mais uma pergunta: já que você teve acesso aos registros da autoridade portuária de Antígua, por acaso encontrou o nome do Joshua Casper em algum outro lugar?";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_22":
			dialog.text = "Você me pede muito, meu filho. Se está querendo dizer que ele pode ter sobrevivido ao naufrágio e depois voltado para a frota – duvido muito disso.";
			link.l1 = "O Senhor age de maneiras misteriosas, Padre.";
			link.l1.go = "WildRose_Abb_23";
		break;

		case "WildRose_Abb_23":
			dialog.text = "De fato, meu filho. Mas veja, o arquivo pessoal dele diz que Joshua Casper nasceu em 1586...";
			link.l1 = "Talvez o senhor esteja certo, pai.";
			link.l1.go = "WildRose_Abb_24_fortune";
			link.l2 = "Sabe, pai, nesses meus anos no Caribe eu já vi coisas que me fariam acreditar até nas histórias mais improváveis.";
			link.l2.go = "WildRose_Abb_24_charisma";
		break;

		case "WildRose_Abb_24_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Certamente um oficial assim merecia morrer em batalha. Mas, filosoficamente falando, de certa forma aquilo também foi uma batalha...";
			link.l1 = "Eu não sou um filósofo, pai. Mas obrigado por tudo...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_24_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Certamente um oficial assim merecia morrer em batalha. Mas, filosoficamente falando, de certo modo aquilo também foi uma batalha...";
			link.l1 = "Eu não sou filósofo, pai. Mas obrigado por tudo...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_25":
			dialog.text = "O Senhor guia vocês neste caminho, meus filhos, e ajudá-los é meu humilde dever. Mas receio que nada mais posso fazer por vocês neste assunto...";
			link.l1 = "Entendo, pai. Então, permita-nos nos retirar.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_5");
		break;
		//<-- Дикая Роза
		
		//--> Эпилог
		case "SharlieEpilog_Benua_1":
			dialog.text = "Estou profundamente preocupado com o estado de saúde de seu pai. Não sei se ele lhe contou isso na carta, mas em sua mensagem para mim confessou: as forças do corpo o estão abandonando, e ele acredita que não lhe resta muito tempo.";
			link.l1 = "Ele mencionou que a enfermidade não recua... Mas, ao que parece, omitiu seus temores.";
			link.l1.go = "SharlieEpilog_Benua_2";
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua");
		break;

		case "SharlieEpilog_Benua_2":
			dialog.text = "Não tenho mais nada a lhe dizer — foi tudo o que ele me contou, mas uma coisa é certa: ele teme apresentar-se diante do Senhor sem voltar a vê-lo.";
			link.l1 = "Ele falou disso. Confesso que eu mesmo pensei em visitá-lo... Mas...";
			link.l1.go = "SharlieEpilog_Benua_3";
		break;

		case "SharlieEpilog_Benua_3":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_1"))
			{
				dialog.text = "Meu filho, somente o Senhor sabe quanto tempo é concedido a cada um de nós. Não adie o encontro: às vezes, um único abraço pode conceder à alma uma paz que nem mil orações seriam capazes de dar.";
				npchar.SharlieEpilog_BenuaRazgovor_1 = true;
			}
			else
			{
				dialog.text = ""+pchar.name+", espero que você não volte a adiar sua visita a ele. Lembre-se de que o tempo joga contra você...";
			}
			link.l1 = "O senhor tem razão, abade. Começarei imediatamente os preparativos para a partida. Considerando a posição que ocupo agora, pode levar bastante tempo até que tudo esteja resolvido...";
			link.l1.go = "SharlieEpilog_Benua_5";
			link.l2 = "Compreendo suas preocupações, santo padre, e prometo refletir sobre isso. Mas neste momento tenho assuntos muito importantes que não podem ser adiados. Voltemos a esta conversa mais tarde.";
			link.l2.go = "SharlieEpilog_Benua_4_exit";
		break;
		
		case "SharlieEpilog_Benua_4_exit":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_2");
		break;

		case "SharlieEpilog_Benua_5":
			dialog.text = "Se você tiver dívidas, meu filho, eu recomendaria começar quitando-as. Agiotas são pessoas muito vingativas: eles podem prejudicar seriamente sua reputação e, com ela, o bom nome de toda a sua família, até mesmo no Velho Mundo\n"+
			"Quanto ao resto — em nome da minha amizade com seu pai e para a glória do Senhor — prestarei toda a ajuda que puder. Você pode redigir por escrito as ordens necessárias, e eu me certificarei de que elas cheguem aos destinatários a tempo. Você só precisará pagar pelo serviço de entrega. Acredito que duzentos dobrões serão suficientes para todas as mensagens.";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Agradeço, santo padre. Sua ajuda será muito bem-vinda. Aqui, aceite.";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "Agradeço por sua preocupação, santo padre. Infelizmente, no momento não tenho essa quantia comigo. Voltaremos a falar disso mais tarde.";
			link.l2.go = "SharlieEpilog_Benua_DublonsLater";
			SharlieEpilog_Benua_Dlg_1();
		break;
		
		case "SharlieEpilog_Benua_DublonsLater":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_3");
		break;
		
		case "SharlieEpilog_Benua_DublonsLater_2":
			dialog.text = "Claro, "+pchar.name+". Suponho que você trouxe os duzentos dobrões?";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Claro. Aqui está.";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "Infelizmente, ainda não tenho a quantia necessária.";
			link.l2.go = "exit";
		break;
		
		case "SharlieEpilog_Benua_6":
			dialog.text = "Excelente, meu filho.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			RemoveDublonsFromPCharTotal(200);
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater");
		break;

		case "SharlieEpilog_Benua_Delivery":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				dialog.text = "Então, por onde você prefere começar?";
				npchar.SharlieEpilog_BenuaRazgovor_2 = true;
			}
			else
			{
				dialog.text = "A quem e sobre o quê você deseja notificar?";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona"))
			{
				link.l1 = "Certa vez encontrei uma ilha que não aparece nos mapas. Já havia alguns colonos por lá, e eu assumi a responsabilidade sobre eles. Com a minha partida, precisarão de um novo 'governador'.";
				link.l1.go = "SharlieEpilog_Benua_IslaMona";
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Baron"))
			{
				link.l2 = "Quero enviar uma carta para Marcus Tirax, de La Vega. Não é um assunto urgente, mas a carta deve ser entregue no prazo.";
				link.l2.go = "SharlieEpilog_Benua_Baron";
			}
			if (CheckCharacterItem(PChar, "patent_fra") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Patent"))
			{
				link.l3 = "Tenho uma patente vigente da França — quero informar à chancelaria de Capsterville sobre minha decisão.";
				link.l3.go = "SharlieEpilog_Benua_Patent";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Money"))
			{
				link.l4 = "Santo padre, ao longo dos anos que passei nestas terras, consegui acumular uma boa quantia de dinheiro. Mas antes que ele chegue às mãos da minha família, eu gostaria de — purificá-lo. Redimir o sangue que talvez esteja ligado a ele. Quero deixar estas terras não como um ladrão com seu saque, mas como um homem cuja consciência e reputação estejam limpas aos olhos da sociedade.";
				link.l4.go = "SharlieEpilog_Benua_Money";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Svenson") && CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona_France"))
			{
				link.l5 = "Gostaria de notificar Jan Svenson, de Blueweld, sobre minha partida. Seria indelicado deixar o arquipélago sem avisá-lo.";
				link.l5.go = "SharlieEpilog_Benua_Svenson";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Houk"))
			{
				link.l6 = "Quero informar sobre minha viagem à família Houk, de Maroon Town.";
				link.l6.go = "SharlieEpilog_Benua_Houk";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Jino"))
			{
				link.l7 = "Quero avisar Gino Guineili, de Saint John's, sobre minha partida para o Velho Mundo.";
				link.l7.go = "SharlieEpilog_Benua_Jino";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_S") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_M") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_L"))
			{
				link.l85 = "É isso, padre... Parece que estou pronto para partir.";
				link.l85.go = "SharlieEpilog_Benua_TimeToGoHome";
			}
			link.l99 = "Desculpe, santo padre, preciso ir.";
			link.l99.go = "SharlieEpilog_exit";
		break;

		case "SharlieEpilog_exit":
			DialogExit();
			LAi_SetStayType(npchar);
			NextDiag.CurrentNode = "First time";
		break;

		case "SharlieEpilog_Benua_Jino":
			dialog.text = "Claro, meu filho.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Jino_2";
			pchar.questTemp.SharlieEpilog_Jino = true;
		break;

		case "SharlieEpilog_Benua_Jino_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Jino_3";
			AddQuestRecord("SharlieEpilog", "8_1");
		break;

		case "SharlieEpilog_Benua_Jino_3":
			dialog.text = "...";
			link.l1 = "Pronto. Pode enviar.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Houk":
			dialog.text = "Claro, meu filho.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Houk_2";
			pchar.questTemp.SharlieEpilog_Houk = true;
		break;

		case "SharlieEpilog_Benua_Houk_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Houk_3";
			AddQuestRecord("SharlieEpilog", "8");
		break;

		case "SharlieEpilog_Benua_Houk_3":
			dialog.text = "...";
			link.l1 = "Pronto. Pode enviar.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Svenson":
			dialog.text = "Jan Svenson de Blueweld... Eu me lembrarei. Entregue-me a carta – ela partirá ainda hoje.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Svenson_2";
			pchar.questTemp.SharlieEpilog_Svenson = true;
		break;
		
		case "SharlieEpilog_Benua_Svenson_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Svenson_3";
			AddQuestRecord("SharlieEpilog", "7");
		break;
		
		case "SharlieEpilog_Benua_Svenson_3":
			dialog.text = "...";
			link.l1 = "Encontrar a casa de Jan não é difícil. Basta perguntar a qualquer morador — dificilmente haverá alguém em todo Blueweld que não saiba quem ele é e onde vive.";
			link.l1.go = "SharlieEpilog_Benua_Svenson_4";
		break;
		
		case "SharlieEpilog_Benua_Svenson_4":
			dialog.text = "Não se preocupe, meu filho, nossos homens entendem bem o que fazem. A carta será entregue a quem deve e dentro do prazo.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Money":
			dialog.text = "Você quer que a igreja abençoe ouro obtido por meios criminosos?";
			link.l1 = "Antes, ele foi obtido a serviço da França e de Sua Majestade.";
			link.l1.go = "SharlieEpilog_Benua_Money_2";
		break;
		
		case "SharlieEpilog_Benua_Money_2":
			dialog.text = "Eu te entendo, meu filho. Eu poderia dizer que a igreja não purifica dinheiro nem ignora o modo como foi obtido. Mas de que adiantaria isso se os famintos continuarem passando fome, os sem‑teto dormindo nas ruas e os doentes morrendo sem ajuda? Estou disposto a dar minha bênção. Em troca, uma pequena parte desses recursos deve servir não a você — mas àqueles que realmente precisam.";
			link.l1 = "Claro, santo padre, estou pronto para doar o quanto o senhor determinar.";
			link.l1.go = "SharlieEpilog_Benua_Money_3";
		break;
		
		case "SharlieEpilog_Benua_Money_3":
			dialog.text = "Então, qual quantia você deseja levar consigo?";
			link.l1 = "Dez milhões de pesos.";
			link.l1.go = "SharlieEpilog_Benua_Money_4";
			if (sti(pchar.Money) >= 250000)
			{
				link.l2 = "Vinte e cinco milhões de pesos.";
				link.l2.go = "SharlieEpilog_Benua_Money_5";
			}
			if (sti(pchar.Money) >= 500000)
			{
				link.l3 = "Cinquenta milhões de pesos.";
				link.l3.go = "SharlieEpilog_Benua_Money_6";
			}
		break;
		
		case "SharlieEpilog_Benua_Money_4":
			dialog.text = "Nesse caso, uma doação de cem mil pesos será suficiente. Com esse valor, poderemos oferecer refeições aos necessitados por muitos meses. Você está pronto para dar essa quantia agora mesmo, meu filho?";
			link.l1 = "Claro. Aqui está. Fico feliz em ajudar aqueles que realmente necessitam, e tenho certeza de que, sob seus cuidados, esse dinheiro será usado com sabedoria e honra.";
			link.l1.go = "SharlieEpilog_Benua_Money_4_1";
			link.l2 = "Desculpe, preciso pensar mais uma vez sobre tudo isso.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Money_5":
			dialog.text = "Nesse caso, sua doação deverá ser de duzentos e cinquenta mil pesos. Esses fundos nos permitirão construir um orfanato que levará seu nome e atenderá suas necessidades pelo menos nos primeiros tempos. Você está pronto para fazer essa doação agora mesmo, meu filho?";
			link.l1 = "Claro. Aqui está. Fico feliz em ajudar aqueles que realmente precisam, e tenho certeza de que, sob sua supervisão, esse dinheiro será bem usado e com honra.";
			link.l1.go = "SharlieEpilog_Benua_Money_5_1";
			link.l2 = "Peço desculpas, preciso pensar mais uma vez sobre tudo isso.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Money_6":
			dialog.text = "Pelo visto, você não perdeu tempo, "+pchar.name+". Acredito que uma doação de quinhentos mil pesos será mais do que suficiente. Com essa contribuição, poderemos construir um hospital e equipá-lo com tudo que for necessário por muitos anos. Você está pronto para fazer essa doação agora mesmo, meu filho?";
			link.l1 = "Claro. Aqui está. Fico feliz em ajudar aqueles que realmente precisam, e tenho certeza de que, sob sua supervisão, esse dinheiro será bem usado e com honra.";
			link.l1.go = "SharlieEpilog_Benua_Money_6_1";
			link.l2 = "Peço desculpas, preciso pensar mais uma vez sobre tudo isso.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Money_4_1":
			dialog.text = "Muito bem, meu filho.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -100000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "10000000");
			AddQuestUserData("SharlieEpilog", "tSum", "100000");
			pchar.questTemp.SharlieEpilog_gold_S = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;
		
		case "SharlieEpilog_Benua_Money_5_1":
			dialog.text = "Muito bem, meu filho.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -250000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "25000000");
			AddQuestUserData("SharlieEpilog", "tSum", "250000");
			pchar.questTemp.SharlieEpilog_gold_M = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;
		
		case "SharlieEpilog_Benua_Money_6_1":
			dialog.text = "Excelente, meu filho.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -500000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "50000000");
			AddQuestUserData("SharlieEpilog", "tSum", "500000");
			pchar.questTemp.SharlieEpilog_gold_L = true;
			pchar.questTemp.SharlieEpilog_Money = true;
			Achievment_Set("ach_CL_205");
		break;
		
		case "SharlieEpilog_Benua_Patent":
			dialog.text = "Qual será sua decisão, meu filho?";
			link.l1 = "Apesar de estar prestes a embarcar em uma longa viagem, gostaria de manter minha patente — e também minha lealdade à França e ao Rei.";
			link.l1.go = "SharlieEpilog_Benua_Patent_2";
			link.l2 = "Decidi renunciar à patente. Tenho uma longa jornada pela frente e não sei quando retornarei. Acredito que será mais sensato não carregar comigo o peso de obrigações e regras que talvez não consiga cumprir.";
			link.l2.go = "SharlieEpilog_Benua_Patent_6";
			pchar.questTemp.SharlieEpilog_Patent = true;
		break;
		
		case "SharlieEpilog_Benua_Patent_2":
			dialog.text = "Fico feliz que tenha chegado a essa decisão, meu filho. Nossa pátria precisa hoje, mais do que nunca, de seus cavaleiros corajosos e fortes. Mas diga-me, "+pchar.name+", você já pensou em se estabelecer, encontrar um lar e parar de arriscar a vida a cada hora? Pois o homem não deve provar a si mesmo nas chamas para sempre.";
			link.l1 = "Não tenho certeza se consigo simplesmente permanecer inativo, santo padre. Mas, como está escrito nas Escrituras: ‘até os guerreiros do Senhor têm descanso quando sua obra está concluída’. Por mais longe que eu esteja de terminar meu trabalho, espero escolher o dia em que guardarei minha lâmina na bainha para sempre.";
			link.l1.go = "SharlieEpilog_Benua_Patent_3";
		break;
		
		case "SharlieEpilog_Benua_Patent_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_4";
			AddQuestRecord("SharlieEpilog", "5_2");
		break;

		case "SharlieEpilog_Benua_Patent_4":
			dialog.text = "Excelente, meu filho. Creio que Sua Majestade não deixará de reconhecer sua lealdade e dedicação.";
			link.l1 = "Agora meus pensamentos estão em outra direção… Espero que o senhor não insista que eu permaneça na nossa propriedade. Não creio estar pronto para isso. Mas, felizmente, terei tempo suficiente para refletir sobre isso.";
			link.l1.go = "SharlieEpilog_Benua_Patent_5";
		break;

		case "SharlieEpilog_Benua_Patent_5":
			dialog.text = "...";
			link.l1 = "Bem, agora voltemos aos assuntos mundanos.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Patent_6":
			dialog.text = "Bem, essa é uma decisão sensata. No entanto, devo observar: sua partida enfraquecerá significativamente o poder da França nestas águas.";
			link.l1 = "Estou certo de que, sob o comando de Sua Majestade, há capitães dignos o suficiente para que a grandeza da França não seja abalada.";
			link.l1.go = "SharlieEpilog_Benua_Patent_7";
		break;
		
		case "SharlieEpilog_Benua_Patent_7":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_8";
			AddQuestRecord("SharlieEpilog", "5_1");
		break;

		case "SharlieEpilog_Benua_Patent_8":
			dialog.text = "...";
			link.l1 = "Isso é tudo. Como se um peso tivesse sido tirado de meus ombros. Confesso que até esqueci quem eu era quando cheguei aqui, no Caribe… Quantas coisas tive de enfrentar.";
			link.l1.go = "SharlieEpilog_Benua_Patent_9";
		break;

		case "SharlieEpilog_Benua_Patent_9":
			dialog.text = "Talvez você já tenha ouvido isso mais de uma vez, meu filho: os caminhos do Senhor são insondáveis. Tudo o que lhe foi destinado desde cima você enfrentou com dignidade. Mas acredito que seus provações ainda não terminaram, e, quem sabe, sua glória ainda está prestes a alcançar seu auge.";
			link.l1 = "A glória pesa, santo padre. Nem todo aquele que a busca é capaz de suportar seu peso… e de parar no momento certo.";
			link.l1.go = "SharlieEpilog_Benua_Patent_10";
		break;

		case "SharlieEpilog_Benua_Patent_10":
			dialog.text = "...";
			link.l1 = "Bem então, agora voltemos aos assuntos mundanos.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Baron":
			dialog.text = "Meu filho, você tem assuntos com o chefe dos piratas?";
			link.l1 = "O senhor conhece o Guardião do Código?";
			link.l1.go = "SharlieEpilog_Benua_Baron_2";
			pchar.questTemp.SharlieEpilog_Baron = true;
		break;

		case "SharlieEpilog_Benua_Baron_2":
			dialog.text = "O Guardião do Código? Não, não o conheço. Sei de Marcus Tirax — um carrasco cuja mão já derramou tanta sangue que nem centenas de anos de oração seriam suficientes para ganhar o perdão do Senhor. E ainda assim… você realmente tem negócios com ele?";
			link.l1 = "Tive que conquistar sua confiança… para tirar Michel da prisão. De qualquer forma, percebi meu erro e não pretendo manter mais contato com ele. Com esta carta, romperei o último laço que nos unia.";
			link.l1.go = "SharlieEpilog_Benua_Baron_3";
			link.l2 = "Agora isso já não importa. Estou deixando o arquipélago, e nossos caminhos naturalmente se separarão, santo padre.";
			link.l2.go = "SharlieEpilog_Benua_Baron_7";
		break;

		case "SharlieEpilog_Benua_Baron_3":
			dialog.text = "E que tipo de laço é esse, meu filho? Espero que não esteja manchado com o sangue de inocentes?";
			link.l1 = "Eu figurava formalmente como chefe da comunidade pirata de Le François. Na prática, porém, outro homem era quem realmente governava. Hoje eu renuncio ao título de barão pirata — definitiva e irrevogavelmente.";
			link.l1.go = "SharlieEpilog_Benua_Baron_4";
		break;

		case "SharlieEpilog_Benua_Baron_4":
			dialog.text = "Fico feliz por você ter trilhado o caminho verdadeiro, meu filho, e orarei pela salvação de sua alma. Todos podem tropeçar, mas o Senhor perdoa apenas aqueles cujo arrependimento é sincero.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Baron_5";
		break;
		
		case "SharlieEpilog_Benua_Baron_5":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_6";
			AddQuestRecord("SharlieEpilog", "4_1");
		break;
		
		case "SharlieEpilog_Benua_Baron_6":
			dialog.text = "Excelente, "+pchar.name+". Entregue‑me a carta — cuidarei para que ela chegue ao destinatário. E não se esqueça de orar, meu filho. Só o arrependimento e a oração ajudam a purificar a alma, mesmo dos pecados mais pesados.";
			link.l1 = "Obrigado, santo padre. Talvez nem tudo esteja perdido para mim.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Baron_7":
			dialog.text = "Por maior que seja o pecado, meu filho, as portas do perdão estão sempre abertas. Arrependimento, oração e boas ações purificam a alma assim como a chuva lava a poeira da pedra.";
			link.l1 = "Tudo a seu tempo, santo padre. Agora preciso cuidar de assuntos mundanos.";
			link.l1.go = "SharlieEpilog_Benua_Baron_8";
		break;
		
		case "SharlieEpilog_Benua_Baron_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_9";
			AddQuestRecord("SharlieEpilog", "4_2");
		break;
		
		case "SharlieEpilog_Benua_Baron_9":
			dialog.text = "...";
			link.l1 = "Aqui está.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_IslaMona":
			dialog.text = "Excelente, meu filho, que você decidiu cuidar dessas pessoas e não se esqueceu delas. A quem você deseja entregar essa ilha?";
			link.l1 = "Acho que deveríamos erguer a bandeira francesa sobre ela. Mais cedo ou mais tarde a ilha será descoberta, e outros países podem tentar tomá‑la. Não posso permitir isso.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France";
			link.l2 = "Esta ilha e seus habitantes merecem viver livres, e não sob a sombra do poder real. Pretendo enviar uma carta ao meu amigo Jan Svenson, de Blueweld. Tenho certeza de que ele concordará em tomar essa terra sob sua proteção. Mas peço, santo padre, que mantenha esta conversa em segredo — pela segurança e bem‑estar dessas pessoas.";
			link.l2.go = "SharlieEpilog_Benua_IslaMona_Pirate";
			pchar.questTemp.SharlieEpilog_IslaMona = true;
		break;
		
		case "SharlieEpilog_Benua_IslaMona_France":
			dialog.text = "Você age com sabedoria, "+pchar.name+". Sob a proteção do Rei, essa ilha terá ordem e segurança.";
			link.l1 = "Enviei a carta correspondente à chancelaria de Capsterville e às pessoas na ilha. Indicarei as coordenadas da ilha no envelope.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_2";
		break;
		
		case "SharlieEpilog_Benua_IslaMona_France_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_France_3";
			pchar.questTemp.SharlieEpilog_IslaMona_France = true;
			AddQuestRecord("SharlieEpilog", "3_1");
		break;
		
		case "SharlieEpilog_Benua_IslaMona_France_3":
			dialog.text = "...";
			link.l1 = "Aqui está. Espero que seus homens consigam encontrar a ilha antes que a frota de Sua Majestade chegue.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_4";
		break;
		
		case "SharlieEpilog_Benua_IslaMona_France_4":
			dialog.text = "Não se preocupe, meu filho. Confiarei a entrega dessas cartas aos melhores dos nossos mensageiros.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_IslaMona_Pirate":
			dialog.text = "Não me cabe julgar se seu caminho é o certo, meu filho. Mais cedo ou mais tarde alguém descobrirá essa ilha, e uma das potências desejará reivindicá‑la. É apenas uma questão de tempo. Mas se você tomou essa decisão — então assim é a vontade de Deus. Não se preocupe: não exporei essas pessoas ao perigo e elevarei orações por elas.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_Pirate_2";
		break;
		
		case "SharlieEpilog_Benua_IslaMona_Pirate_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_Pirate_3";
			pchar.questTemp.SharlieEpilog_IslaMona_Pirate = true;
			AddQuestRecord("SharlieEpilog", "3_2");
		break;
		
		case "SharlieEpilog_Benua_IslaMona_Pirate_3":
			dialog.text = "Jan Svenson, de Blueweld, certo?";
			link.l1 = "Exatamente, santo padre. E a segunda carta precisa ser entregue na própria ilha. As coordenadas estão indicadas no envelope.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_TimeToGoHome":
			dialog.text = "Excelente, meu filho. Se não me engano, você chegou aqui no pinaza '"+GetShipName("Ulysse")+"'?";
			link.l1 = "Correto. Mas por que o senhor pergunta?";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_2";
		break;
		
		case "SharlieEpilog_Benua_TimeToGoHome_2":
			dialog.text = "Porque esse navio foi recentemente colocado em leilão. E você, Charles, tem a chance de voltar para casa no mesmo barco — mas agora como capitão.";
			link.l1 = "Hmm... Devo admitir que a proposta é tentadora. Acho que vale a pena dar uma passada na administração do porto. Obrigado, santo padre.";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_3";
		break;
		
		case "SharlieEpilog_Benua_TimeToGoHome_3":
			DialogExit();
			NextDiag.CurrentNode = "First Time";
			AddDialogExitQuestFunction("SharlieEpilog_PU_Ulysse_1");
		break;
		//<-- Эпилог
		
		case "LH_abbat_38":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
