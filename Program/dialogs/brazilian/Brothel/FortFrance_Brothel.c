// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;   
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas, "+GetSexPhrase("rapaz","senhorita")+"?","O que você precisa, "+GetSexPhrase("bonito","bonitinha")+"? Pode perguntar."),"Perguntas de novo","Tee-hee, se não se importa - perguntas...",""+GetSexPhrase("Hum, por que você não escolhe uma das beldades pra você? Estou começando a desconfiar de você...","Hm, por que você não escolhe uma das nossas belezas para si? Receio que não temos nenhum rapaz por aqui, hihi...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia, com licença.","Na verdade, deixa pra lá."),"Eu... desculpe, não tenho perguntas por enquanto.","Você tem razão, já é a terceira vez. Me perdoe.","Talvez na próxima vez, madame.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start")
			{
				DelLandQuestMark(npchar);
				link.l1 = "Escute, Aurora, preciso de uma moça para esta noite. E quero levá-la comigo para casa. Você pode providenciar isso?";
                link.l1.go = "Gigolo";
			}	
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Gigolo":
			dialog.text = "Claro, querido. Já encontrou uma donzela adequada ou devo eu procurar?";
			link.l1 = "De fato, sim. Estou de olho numa moça chamada Lucille.";
			link.l1.go = "Gigolo_1";
		break;
		
		case "Gigolo_1":
			dialog.text = "Você está falando da Lucille Montaigne?";
			link.l1 = "Pra ser sincero, não perguntei o sobrenome dela. Só sei que é uma moça jovem, bonita, de cabelos loiros, chamada Lucille.";
			link.l1.go = "Gigolo_2";
		break;
		
		case "Gigolo_2":
			dialog.text = "Sim, essa descrição combina muito com ela. Tudo bem. Mas me diga, por que ela? As outras moças não lhe agradam?";
			link.l1 = "Veja bem... ela acabou de começar a trabalhar aqui, então acredito que ainda não tem experiência suficiente no 'Ramo' para pesar demais no meu bolso.";
			link.l1.go = "Gigolo_2_1";
			link.l2 = "Veja, eu adoro loiras de pele clara. Lucille será perfeita nesse sentido.";
			link.l2.go = "Gigolo_2_2";
		break;
		
		case "Gigolo_2_1":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand1) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 5000;
				dialog.text = "Now Monsieur, that isn't true! She is young, pretty, and experienced; my clients all but admire her. She will cost you a lot. Five thousand pesos for a night with her, and not a single peso less.";
				if (sti(pchar.money) >= 5000)
				{
					link.l1 = "Caro, mas muito bem. Aqui está sua moeda.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Está caro demais! Não tenho tudo isso. Falo com você depois.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 2500;
				dialog.text = "Suspiro, você tem razão, Monsieur, ela é bonita e jovem, mas não tem experiência. Meus clientes geralmente nem reparam nela, por isso perguntei. Mas se você realmente gosta de moças discretas, diria que ela é uma boa escolha. Vai lhe custar dois mil e quinhentos pesos.";
				if (sti(pchar.money) >= 2500)
				{
					link.l1 = "Pois bem, ela servirá perfeitamente. Pegue suas moedas.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Está caro! Não tenho tudo isso. Falo com você depois.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_2_2":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand2) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 4500;
				dialog.text = "Você não seria o primeiro, bonitão. Às vezes meus clientes fazem fila pela atenção dela, já que ela é bem diferente das filhas de pele escura das nossas ilhas. Vai te custar quatro mil e quinhentos pesos.";
				if (sti(pchar.money) >= 4500)
				{
					link.l1 = "Caro, mas muito bem. Pegue sua moeda.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Está caro! Não tenho tudo isso. Falo com você depois.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 3000;
				dialog.text = "Sério, Monsieur? Já está com saudade de casa? Minhas crioulas e, principalmente, minhas mulatas são bem mais apaixonadas do que essa parisiense preguiçosa. Mas enfim, a escolha é sua. Ela vai lhe custar três mil pesos.";
				if (sti(pchar.money) >= 3000)
				{
					link.l1 = "Caro, mas muito bem. Aqui está sua moeda.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Está caro! Não tenho tudo isso. Falo com você depois.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharlie.Gigolo.Money));
			dialog.text = "Como quiser, querido. Lucille estará te esperando ansiosamente às onze horas da noite. Além disso, ela deve voltar até, no máximo, sete horas da manhã. Se você não chegar antes da meia-noite, ela atenderá outro cliente, e então você terá que esperar até a noite seguinte para vê-la. E nem pense em... machucá-la de qualquer forma, ou vai se arrepender. Considere-se avisado, querido.";
			link.l1 = "Não se preocupe, vou tratá-la como uma amante, não como um bruto. Vou encontrá-la às onze horas. Agora, o que devo fazer até lá?";
			link.l1.go = "Gigolo_4a";
		break;
		
		case "Gigolo_4a":
			dialog.text = "Olha, eu nem sei, querido. Passe na taverna, converse com o barman...";
			link.l1 = "Boa ideia. Vou fazer isso mesmo. Tenha um bom dia!";
			link.l1.go = "Gigolo_4";
		break;
		
		case "Gigolo_4":
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			DialogExit();
			AddQuestRecord("SharlieC", "2");
			pchar.questTemp.Sharlie.Gigolo = "girl";
			Sharlie_CreateGigoloGirl();
			QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerDelLoc("fortfrance_brothel", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
			//NewGameTip("Доступна функция перемотки времени! Она доступна через опцию 'мысли вслух' в меню действий (ENTER).");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
