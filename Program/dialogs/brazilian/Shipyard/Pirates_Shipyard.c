// диалог по городам
// Это мастер тюнинга
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    string 	sTemp;
	int 	amount, iSan, iOil, iSil, iRop;
	int iTemp, iSum; // 280912
	ref 	shTo;
	string 	s1;
 
	switch (Dialog.CurrentNode)
	{		
		// -----------------------------------Диалог первый - первая встреча
		case "First time":  // перехват основного диалога, только один раз
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Ufa... Que clima terrível... Meu nome é "+GetFullName(npchar)+", e que Deus me amaldiçoe se eu não for o melhor construtor naval dessas ilhas esquecidas por Ele. Mas essa umidade está acabando comigo...";
				Link.l1 = pcharrepphrase("Mil tubarões, era só o que me faltava—resmungos de um velho. Meu nome é "+GetFullName(pchar)+", acredito que já ouviu falar de mim.","Não é a umidade, é a idade mesmo, senhor. Meu nome é "+GetFullName(pchar)+", acredito que já ouviu falar de mim.");
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else // нужно, если по квестам будет сброс на  "First time"
			{
				dialog.text = "Ah, você de novo, sempre reclamando dos seus problemas... (tosse).";
				link.l1 = pcharrepphrase("Você tem razão, sou eu de novo. Mas vamos falar de negócios enquanto você ainda não entregou sua alma a Deus.","Sua memória está afiada, e agora, se me permite, vamos passar para algumas perguntas mais específicas.");
				link.l1.go = "node_3";
				link.l2 = pcharrepphrase("Cansei do seu resmungo. Adeus.","Já está na hora de eu ir. Desculpe incomodar você");
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Master_Ship";
			Dialog.CurrentNode = "Master_Ship";
		break;
		
		case "Master_Ship":
		//Jason ----------------------------------- Хронометр Алекса ------------------------------------------
			if (CheckAttribute(npchar, "quest.sextant") && CheckAttribute(pchar, "questTemp.AlexClock") && pchar.location == "Pirates_shipyard" && !CheckAttribute(npchar, "quest.clock"))
			{
				dialog.text = "Aha, Capitão "+GetFullName(pchar)+"! Que bom que você apareceu!";
				Link.l1 = "Parece que você precisa de mim para alguma coisa, não é? Normalmente você não é tão cortês assim.";
				Link.l1.go = "clock_begin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "clock" && pchar.location == "Pirates_shipyard")
			{
				dialog.text = "Vejo que voltou de mãos vazias, capitão! O que aconteceu com os... convidados?";
				Link.l1 = "Eles foram embora. Eu perguntei, e eles se foram.";
				Link.l1.go = "clock_complete";
				break;
			}
		//<-- хронометр Алекса
			dialog.text = "Ah, você de novo, sempre reclamando dos seus problemas... (tosse)";
			link.l1 = pcharrepphrase("Você está certo, sou eu de novo. Mas vamos falar de negócios enquanto você ainda não entregou sua alma a Deus.","Sua memória está afiada, e agora, se me permite, vamos passar para algumas perguntas mais específicas.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("Cansei do seu resmungo. Adeus.","Está na hora de eu ir. Desculpe incomodar você.");
			link.l2.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "node_1":
			dialog.text = "Jovens de hoje em dia... Nunca mostram respeito. Cabeças quentes, mãos pesadas, o que vocês querem?";
			link.l1 = pcharrepphrase("Isso mesmo. Mas cedo ou tarde, tudo chega ao fim, e parece que sua hora está chegando...","Algo me diz que, na sua juventude, você também não tinha muito respeito pelos mais velhos. Estou certo?");
			link.l1.go = "node_2";
		break;

		case "node_2":
			dialog.text = "Não discuta com os mais velhos, garoto.";
			link.l1 = pcharrepphrase("Calma, agora. Se acalme. Não se esforce demais, senão pode acabar tendo um ataque do coração. Não quero ser acusado de causar a morte do melhor construtor naval do Caribe. Vamos ao que interessa.","Eu te perdoo pela grosseria, só por respeito à sua idade. E agora, se já terminou, vamos ao que interessa.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("Certo, já falei demais! Até logo!","Vejo que não vamos chegar a um acordo. Adeus.");
			link.l2.go = "exit";
		break;

		case "node_3":
			dialog.text = "(tosse)... As pessoas não deixam um velho em paz. O que você quer de mim desta vez, "+GetAddress_Form(NPChar)+"? ";
			link.l1 = pcharrepphrase("Preciso usar os serviços do estaleiro.","Quero usar os serviços do estaleiro.");
			link.l1.go = "shipyard_dlg";
            Link.l2 = "Tenho uma pergunta.";
			Link.l2.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = "Quero falar sobre finanças.";
				link.l3.go = "LoanForAll";//(перессылка в файл города)
			}
			link.l9 = pcharrepphrase("Droga, tenho alguns assuntos urgentes para resolver. Adeus.","Está na hora de eu ir. Desculpe.");
			link.l9.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;
		
		case "shipyard_dlg":			
			dialog.Text = "Vamos lá, o que você quer? Não venha incomodar um velho...";
			link.l2 = "Eu só quero usar os serviços do estaleiro.";
			link.l2.go = "shipyard";
			link.l3 = "Preciso de armas para o navio.";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l4 = "Quero mudar o visual das minhas velas.";
					link.l4.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_hull"))
			{
					link.l50 = "Meu navio é bem... especial. Gostaria de fazer algumas mudanças.";
					link.l50.go = "FDM";
			}
			/*if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_cabin") && npchar.quest.FDM_cabin == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "Tenho mais baús para a reconstrução da cabine.";
					link.l50.go = "FDM_cabin_pay";
			}*/
			// Xenon -->
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmoney")
			{
					link.l50 = "Vim falar sobre a reconstrução do navio.";
					link.l50.go = "FDM_hull_givemoney";
			}

			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmaterials")
			{
					link.l50 = "Vim falar sobre a reconstrução do navio.";
					link.l50.go = "FDM_hull_checkmaterials";
			}
			// <-- Xenon
			link.l9 = pcharrepphrase("Merda, tenho alguns assuntos urgentes para resolver, até logo.","Está na hora de eu ir. Desculpe.");
			Link.l9.go = "ship_tunning_not_now";
		break;	
		
		///////////////////////////////  квестовые ветки
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais perguntas você tem?","Como posso ajudar você?"),"Você tentou me fazer uma pergunta há pouco tempo...","Eu nunca conheci pessoas tão curiosas no meu estaleiro ou em qualquer outro lugar desta cidade.","Por que tantas perguntas? Meu trabalho é construir navios. Vamos cuidar disso.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Hum, onde foi parar minha memória...","Hum, bem...","Certo, vamos...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "Step_Door"))
			{
				link.l2 = "Olha, eu gostaria de passar, mas essa porta está trancada...";
				link.l2.go = "Step_Door_1";
			}

			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
			{
				link.l1 = "Gostaria de propor um acordo.";
				link.l1.go = "Al_ShipLetters_1";// генератор  "Найденные документы"
				pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
			}
			if(CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "go") // 280912
			{
				link.l1 = "Vim falar sobre os materiais para a fragata.";
				link.l1.go = "clock";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Escute, "+npchar.name+", você viu o Miguel Dichoso na Isla Tesoro ultimamente?";
				link.l1.go = "tieyasal";
			}
		break;
//*************************** Генератор - "Найденные судовые документы" **************
		
		case "Al_ShipLetters_1":
			dialog.text = "Diga seus termos.";
			s1 = "I lucked into finding an absolutely legal ship's documents packet that hasn't been called for search yet.";
			s1 = s1 + "The ship is afloat and it hasn't been excluded from the registry, don't worry. Just a blind fool-owner had the misfortune of losing these papers...";
			link.l1 = s1;
			link.l1.go = "Al_ShipLetters_2";			
		break;
		case "Al_ShipLetters_2":
			s1 = "Let me take a look! It really looks to be freshly filled out. Well, luck is in your favor, sir! ";
			s1 = s1 + "I actually needed a packet just like this. I, in turn, will offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What do you say?";
			dialog.text = s1;
			link.l1 = "Que generosidade real! Claro que eu concordo!";
			link.l1.go = "Al_ShipLetters_3";
			link.l2 = "Não, acho que não.";
			link.l2.go = "exit";
		break;
		case "Al_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		

//*************************** Открывание двери ***************************
 		case "Step_Door_1":
			dialog.text = "Isso mesmo. Se quiser passar por essa porta, vai ter que me pagar 20.000 pesos. Se não pagar, não vou abrir. Aqui não é casa de caridade. E nem recomendo que vá lá, de qualquer forma. Seria melhor pra você se não fosse...";
			if(sti(pchar.money) >= 20000)
			{
    			link.l1 = "Aqui está o seu dinheiro. Abra.";
    			link.l1.go = "Step_Door_2";
            }
            else
            {
    			link.l1 = "Eu não tenho tanto dinheiro assim.";
    			link.l1.go = "Step_Door_3";
            }
            link.l2 = "De jeito nenhum! Eu nunca pagaria por uma porta.";
    		link.l2.go = "exit";
		break;
		
 		case "Step_Door_2":
			npchar.Step_Door = true; // fix
			dialog.text = "Pode entrar. A porta está aberta. Não precisa me agradecer!";
			link.l1 = "Não, por que não. Obrigado. "+npchar.name+"...";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            AddMoneyToCharacter(pchar, -20000);
			pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
            pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;
		
 		case "Step_Door_3":
			dialog.text = "Bem, quando tiver isso, volte. Caso contrário, não tente me convencer. É inútil...";
			link.l1 = "Argh, estou completamente sem palavras!";
			link.l1.go = "exit";
		break;
		
	// ------------------------------------------- хронометр Ђлекса ----------------------------------------------// Addon-2016 Jason замена дублонов на песо везде
		case "clock_begin":
			dialog.text = "Vamos lá, não seja tão rígido com um velho... Eu realmente preciso da sua ajuda, capitão.";
			link.l1 = "Conte-me, mestre. O que aconteceu com você?";
			link.l1.go = "clock_begin_1";
		break;
		
		case "clock_begin_1":
			sTotalTemp = "Steven Dodson";
			if (pchar.questTemp.Alex.Clock == "terrax") sTotalTemp = "Marcus Tyrex";
			dialog.text = "Nosso novo líder da Irmandade da Costa, "+sTotalTemp+", encomendou um novo navio, uma fragata. Também pediu tarefas bem difíceis: casco reforçado, alta velocidade e boa manobrabilidade, além de canhões do maior calibre possível\nEu entendo que o navio de um almirante—desculpe, do líder dos irmãos—precisa ser algo especial, mas isso significa que vou precisar de materiais especiais para construí-lo. Você já deve ter ouvido falar deles. Pau-ferro, resina, seda naval e cordas...";
			link.l1 = "Então diga isso ao líder dos Irmãos. Ou está receoso de que "+sTotalTemp+" vou cortar sua cabeça por isso?";
			link.l1.go = "clock_begin_2";
		break;
		
		case "clock_begin_2":
			dialog.text = "Eu disse a ele... O fato é que nosso novo líder não tem tempo nem oportunidade para encontrar e trazer esses materiais. Você precisa entender como eles são raros. E não tem como eu construir uma fragata com essas características sem eles.";
			link.l1 = "E eu imagino que você quer que eu encontre os materiais para o navio?";
			link.l1.go = "clock_begin_3";
		break;
		
		case "clock_begin_3":
			dialog.text = "Bem, sim. Você é um bom amigo do nosso líder. "+sTotalTemp+" diz que lhe deve muito e insiste que você merece todo respeito... Então pensei: já que você é amigo dele, talvez não se importe em ajudá-lo? E ao mesmo tempo, entende a situação delicada em que estou? Todos os materiais serão pagos, "+sTotalTemp+" não é mão fechada com o ouro dele.";
			link.l1 = "Me desculpe mesmo, capitão, mas estou tão ocupado quanto "+sTotalTemp+". Receio que juntar os materiais possa levar uma eternidade. Então, é melhor você pedir para outra pessoa.";
			link.l1.go = "clock_exit";
			link.l2 = "Bem, se "+sTotalTemp+" encomendei um navio com você – então é claro que vou tentar ajudar. Nós realmente somos amigos, e amigos precisam se ajudar. De quantos materiais você precisa?";
			link.l2.go = "clock_begin_4";
		break;
		
		case "clock_exit":
			dialog.text = "Que pena. Que pena mesmo. Eu estava contando com você. Bem, como dizem, não é não...";
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.AlexClock");
		break;
		
		case "clock_begin_4":
			dialog.text = "Estou precisando de 100 unidades de madeira de ferro, 150 recipientes de resina, 110 rolos de seda naval e 90 rolos de corda de cânhamo. O que acha? Consegue encontrar tudo isso pra mim em até quatro meses? Acho que não tenho mais tempo que isso.";
			link.l1 = "Posso ao menos tentar. E quanto ao pagamento?";
			link.l1.go = "clock_begin_5";
		break;
		
		case "clock_begin_5":
			dialog.text = "Aqui estão meus preços: madeira de lei por 4000 pesos a peça, resinas por 1400 pesos o recipiente, seda por 2500 pesos o rolo e cordas por 1500 pesos a bobina. E se você trouxer tudo isso para mim, vai ganhar um presente muito especial meu.";
			link.l1 = "O que será, hein?";
			link.l1.go = "clock_begin_6";
		break;
		
		case "clock_begin_6":
			dialog.text = "Traga-me os materiais primeiro. Mas lhe garanto: vai ser útil para você, e essa peça é única. Não existe outra igual no Caribe, nem no mundo inteiro até agora. Espero que essa faísca de curiosidade tenha despertado seu interesse em reunir os materiais para mim.";
			link.l1 = "Bom, você é mais esperto que um duende, capitão! Tudo certo, temos um acordo.";
			link.l1.go = "clock_begin_7";
		break;
		
		case "clock_begin_7":
			dialog.text = "Estou muito feliz. Vou esperar ansiosamente pelo seu retorno.";
			link.l1 = "Espero que não demore muito...";
			link.l1.go = "clock_begin_8";
		break;
		
		case "clock_begin_8":
			DialogExit();
			pchar.questTemp.AlexClock = "go";
			npchar.quest.clock = "true";
			SetFunctionTimerCondition("AlexClock_Over", 0, 0, 122, false); // таймер
			AddQuestRecord("alex_clock", "1");
			// запоминаем переменные
			pchar.questTemp.AlexClock.Sandal = 100;
			pchar.questTemp.AlexClock.Oil = 150;
			pchar.questTemp.AlexClock.Shipsilk = 110;
			pchar.questTemp.AlexClock.Ropes = 90;
		break;
		
		case "clock":
			dialog.text = "Excelente! O que você trouxe para mim hoje?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && !CheckAttribute(npchar, "quest.sandal"))
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "Madeira de ferro, na quantidade de "+FindRussianQtyString(iSan)+".";
				link.l1.go = "sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && !CheckAttribute(npchar, "quest.oil"))
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "Resinas, na quantidade de "+FindRussianQtyString(iOil)+".";
				link.l2.go = "oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && !CheckAttribute(npchar, "quest.shipsilk"))
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "Seda de navio, na quantidade de "+FindRussianQtyString(iSil)+".";
				link.l3.go = "shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && !CheckAttribute(npchar, "quest.ropes"))
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "Cordas de cânhamo, na quantidade de "+FindRussianQtyString(iRop)+".";
				link.l4.go = "ropes";
			}
			link.l5 = "Nada no momento. Só queria ter certeza de que nosso acordo ainda está de pé.";
			link.l5.go = "exit";
		break;
		
		case "clock_1":
			if (CheckAttribute(npchar, "quest.sandal") && CheckAttribute(npchar, "quest.oil") && CheckAttribute(npchar, "quest.shipsilk") && CheckAttribute(npchar, "quest.ropes")) // все привез
			{
				dialog.text = "Maravilha! Já tenho todos os materiais de que preciso. Muito obrigado pela ajuda, capitão. Você me salvou de verdade.";
				link.l1 = "Sim, a qualquer hora, capitão. Também estou satisfeito: ajudei um amigo e ainda ganhei um bom dinheiro. Agora, vamos voltar à nossa conversa sobre aquele item misterioso que você me prometeu.";
				link.l1.go = "clock_2";
			}
			else
			{
				dialog.text = "Mais alguma surpresa para mim, capitão?";
				link.l1 = "Infelizmente, por enquanto é só. Apenas continue esperando.";
				link.l1.go = "exit";
				link.l2 = "Sim, tenho mais uma coisa...";
				link.l2.go = "clock";
			}
		break;
		
		case "sandal": // бакаут
			amount = sti(pchar.questTemp.AlexClock.Sandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 4000*iSan;
				dialog.text = "Certo, tudo bem. Vou precisar de "+FindRussianQtyString(amount)+" de madeira de ferro. Você trouxe para mim "+FindRussianQtyString(iSan)+". . Então, o que ainda falta você me trazer é "+FindRussianQtyString(iTemp)+" . Tudo certo, a uma taxa de 4000 pesos por peça, sua recompensa totaliza "+FindRussianMoneyString(iSum)+". Por favor, aceite.";
				link.l1 = "Obrigado! O restante estará pronto em breve.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				pchar.questTemp.AlexClock.Sandal = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 4000*amount;
				dialog.text = "Certo, tudo bem. Também vou precisar de "+FindRussianQtyString(amount)+"  de madeira de ferro. Você me trouxe "+FindRussianQtyString(iSan)+". Pronto, já resolvemos a questão da madeira de ferro! Muito bem, a uma taxa de 4000 pesos por peça, sua recompensa fica em "+FindRussianMoneyString(iSum)+". Por favor, aceite.";
				link.l1 = "Obrigado!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.sandal = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "oil": // смолы
			amount = sti(pchar.questTemp.AlexClock.Oil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1400*iOil;
				dialog.text = "Certo, tudo bem. Também vou precisar "+FindRussianQtyString(amount)+" resinas. Você me trouxe "+FindRussianQtyString(iOil)+". Então, o que falta você me trazer é "+FindRussianQtyString(iTemp)+". Certo, a uma taxa de 1400 pesos por contêiner, sua recompensa totaliza "+FindRussianMoneyString(iSum)+". Por favor, aceite.";
				link.l1 = "Obrigado! Em breve você receberá o restante.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				pchar.questTemp.AlexClock.Oil = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "resins");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1400*amount;
				dialog.text = "Certo, tudo bem. Também vou precisar "+FindRussianQtyString(amount)+" resinas. Você me trouxe "+FindRussianQtyString(iOil)+". Pronto, já cuidamos das resinas! Certo, a uma taxa de 1400 pesos por contêiner, sua recompensa fica em "+FindRussianMoneyString(iSum)+". Por favor, aceite.";
				link.l1 = "Obrigado!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.oil = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "resins");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "shipsilk": // шёлк
			amount = sti(pchar.questTemp.AlexClock.Shipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 2600*iSil;
				dialog.text = "Certo, tudo bem. Também vou precisar de "+FindRussianQtyString(amount)+" seda. Você me trouxe "+FindRussianQtyString(iSil)+". Então, o que falta você me trazer é "+FindRussianQtyString(iTemp)+". Certo, a uma taxa de 2600 pesos por peça, sua recompensa totaliza "+FindRussianMoneyString(iSum)+". Por favor, aceite.";
				link.l1 = "Obrigado! O resto estará pronto em breve.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				pchar.questTemp.AlexClock.Shipsilk = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "silk");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 2600*amount;
				dialog.text = "Certo, tudo bem. Também vou precisar "+FindRussianQtyString(amount)+" seda. Você me trouxe "+FindRussianQtyString(iSil)+". Pronto, cuidamos da seda! Então, a uma taxa de 2600 pesos por peça, sua recompensa fica em "+FindRussianMoneyString(iSum)+". Por favor, aceite.";
				link.l1 = "Obrigado!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.shipsilk = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "silk");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "ropes": // канаты
			amount = sti(pchar.questTemp.AlexClock.Ropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1500*iRop;
				dialog.text = "Certo, tudo bem. Também vou precisar de "+FindRussianQtyString(amount)+" cordas. Você me trouxe "+FindRussianQtyString(iRop)+". Então, o que você ainda precisa me trazer é "+FindRussianQtyString(iTemp)+". Então, a uma taxa de 1500 pesos por peça, sua recompensa totaliza "+FindRussianMoneyString(iSum)+". Por favor, aceite.";
				link.l1 = "Obrigado! Em breve você receberá o restante.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				pchar.questTemp.AlexClock.Ropes = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ropes");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1500*amount;
				dialog.text = "Certo, tudo bem. Eu vou precisar de "+FindRussianQtyString(amount)+" cordas. Você trouxe para mim "+FindRussianQtyString(iRop)+". Então, já cuidamos das cordas. Certo, a uma taxa de 1500 pesos por peça, sua recompensa totaliza "+FindRussianMoneyString(iSum)+". Por favor, aceite.";
				link.l1 = "Obrigado!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.ropes = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ropes");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "clock_2":
			dialog.text = "Sim, sim... sobre o meu assunto, claro. M-m-mmm... Hmmm... onde foi que eu... ahhh...";
			link.l1 = "O que foi, mestre? Você parece bem preocupado. Aconteceu alguma coisa? Algum problema?";
			link.l1.go = "clock_3";
		break;
		
		case "clock_3":
			dialog.text = "Exatamente. Problemas. Recentes. Malditos caçadores de tesouros...";
			link.l1 = "Calma, calma. Não faz bem pra sua idade ficar se preocupando assim. Deus me livre, pode ser só um passo pro outro lado. Quem é que ia construir a fragata pro chefe da Irmandade então? Se acalme e me explique, quem são esses caçadores de tesouros?";
			link.l1.go = "clock_4";
		break;
		
		case "clock_4":
			dialog.text = "Ali, perto da minha mesa, tem uma porta. Ela leva direto para um cofre antigo. Nesse cofre, em um dos baús de tesouro, eu guardo minha caixa de metal com os objetos que estavam comigo quando fui puxado por aquele maldito funil, vinte anos atrás, e vim parar aqui...";
			link.l1 = "Que funil? Do que você está falando?";
			link.l1.go = "clock_5";
		break;
		
		case "clock_5":
			dialog.text = "Ah, perdoe meu desabafo. Envelhecer não é fácil, rapaz. Me desculpe. Mas isso não vem ao caso. O que importa é que uma caixa com um presente pra você está no baú que está no calabouço, ocupado no momento por uns canalhas. Eles não são dos nossos, nem de Isla Tesoro.\nCaçadores de tesouros—alguém deve ter contado pra eles que este lugar está cheio de riquezas. Eles não teriam coragem de aparecer por aqui, mas eu mesmo tenho medo de ir lá, entende? As caras deles são...";
			link.l1 = "Entendi. Abra a porta. Eu vou expulsar seus convidados indesejados.";
			link.l1.go = "clock_6";
		break;
		
		case "clock_6":
			dialog.text = "Assim, do nada? Você vai expulsá-los? Sozinho? Não tem medo? Toda a nossa comunidade lutaria por você, era só pedir...";
			link.l1 = "Menos conversa, mais ação, mestre. Abra essa porta e deixe o resto comigo. Em qual baú você guarda suas coisas?";
			link.l1.go = "clock_7";
		break;
		
		case "clock_7":
			dialog.text = "Logo ali no corredor tem uma coleção de barris de madeira vazios. Atrás deles, no chão, num canto mais escondido, está um baú pequeno. Eu preguei um cadeado nele, então duvido que aqueles invasores consigam meter as mãos sujas lá dentro, mesmo que encontrem. Aqui, pegue a chave.";
			link.l1 = "Fico feliz que você pense adiante. Espere aqui e não vá a lugar nenhum.";
			link.l1.go = "clock_8";
		break;
		
		case "clock_8":
			DialogExit();
			GiveItem2Character(pchar, "key3"); 
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", true);//офицеров не пускать
			pchar.quest.Alex_Chest.win_condition.l1 = "location";
			pchar.quest.Alex_Chest.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.Alex_Chest.function = "AlexClock_Chest";
			pchar.quest.AlexClock_Over.over = "yes"; //снять прерывание
			pchar.questTemp.AlexClock = "chest";
			AddQuestRecord("alex_clock", "3");
		break;
		
		case "clock_complete":
			dialog.text = "Eles só te ouviram e foram embora?";
			link.l1 = "Isso mesmo. Eles acabaram sendo sujeitos bem educados. Expliquei que a presença deles estava assustando o velho e renomado mestre de obras, e por respeito à sua idade, eles foram embora. Pode descer lá tranquilo.";
			link.l1.go = "clock_complete_1";
		break;
		
		case "clock_complete_1":
			dialog.text = "Ah-ha, está tirando sarro de um velho! Tudo bem. Me dê minha caixa e eu abro para te entregar o aparelho que você ganhou com justiça.";
			link.l1 = "Por favor, aceite...";
			link.l1.go = "clock_complete_2";
		break;
		
		case "clock_complete_2":
			RemoveItems(pchar, "alexs_chest", 1);
			dialog.text = "Obrigado! Vamos abrir. Aqui, pegue isto. Um temporizador mecânico automático—ninguém faz aparelhos assim por aqui, e ninguém fará pelos próximos trezentos anos... ah, desculpe, perdoe este velho. Só quero dizer que isso aqui é único.\nEle faz todo o trabalho sozinho, você não vai precisar daqueles relógios de areia bobos e afins. Sem erros! Só mantenha longe de pancadas fortes e da água, ou você vai perder. Até um macaco conseguiria usar esse temporizador.";
			link.l1 = "Veja só isso! Nunca vi nada tão incrível na minha vida! Muito obrigado, mestre.";
			link.l1.go = "clock_complete_3";
		break;
		
		case "clock_complete_3":
			GiveItem2Character(pchar, "clock3");
			Log_Info("You've received an automatic mechanical timer");
			SetAlchemyRecipeKnown("sextant2");
			PlaySound("interface\important_item.wav");
			dialog.text = "De nada. Agora você sempre vai saber que horas são. Não me pergunte onde consegui isso. Não vou te contar.";
			link.l1 = "Todo mundo tem seus segredos, não é, capitão? Tudo bem... guarde seus segredos e eu não vou me meter nos seus assuntos. Obrigado pelo presente!";
			link.l1.go = "clock_complete_4";
		break;
		
		case "clock_complete_4":
			dialog.text = "E obrigado pela sua ajuda, Capitão. Venha me visitar algum dia. Não se esqueça deste velho construtor naval.";
			link.l1 = "Como se eu pudesse te esquecer... Enfim, pode deixar, Alexus, o Mestre. Até logo!";
			link.l1.go = "clock_complete_5";
		break;
		
		case "clock_complete_5":
			DialogExit();
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
			LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", false);
			AddQuestRecord("alex_clock", "5");
			CloseQuestHeader("alex_clock");
			DeleteAttribute(pchar, "questTemp.AlexClock");
			// belamour legendary edition на пару с Акулой
			pchar.questTemp.SharkGoldFleet.KGBB = true;
			if(CheckAttribute(pchar,"questTemp.SharkFrigate")) SetTimerCondition("SharkGoldFleet", 0, 0, 30, false);
		break;
	// <-- хронометр Алекса
		
		// город майя
		case "tieyasal":
			dialog.text = "Aha, Miguel! Meu velho conhecido. Eu me lembro dele. Ele me perguntava sobre cada pequeno detalhe, repetidas vezes. Mas como eu ia explicar pra ele como um rádio é construído por dentro, se ele nem tinha visto um simples telégrafo?";
			link.l1 = "O quê?.. Do que você está falando, mestre?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Ah, desculpe, rapaz. Não ligue muito para o que eu digo... Nosso curioso Michel matou a curiosidade dele e sumiu. Faz só três dias que conversamos.";
			link.l1 = "Onde está o Miguel agora, se não for incômodo perguntar?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Vai saber. Talvez ele esteja cuidando dos negócios dele em Sharptown, ou quem sabe já tenha partido de Isla Tesoro.";
			link.l1 = "Entendi. Obrigado, mestre!";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Калеуче
		case "FDM":
			if(CheckAttribute(npchar, "quest.FDM_secondtime"))
				dialog.text = "De novo com esse seu 'navio fantasma'... Saiba de uma coisa – só estou trabalhando nele porque ainda tenho esperança de que vire algo decente. Caso contrário, eu nem chegaria perto. Acho que todo mundo no mar pensa mais ou menos igual. O que você quer fazer com ele desta vez?";
			else	
				dialog.text = "Ah, o 'navio fantasma'! As mães usam seu galeão para assustar as crianças travessas. E você decidiu ficar com essa embarcação maldita em vez de afundá-la! Os marinheiros tremem quando veem seu navio no horizonte... Então, o que pretende fazer com ele?";
			/*if (!CheckAttribute(npchar, "quest.FDM_cabin"))
			{
				link.l1 = "Gosto da ideia desses covardes apavorados. Mas o interior me deixa triste. Já viu a cabine? Parece um caixão. Tanto mofo e poeira. Quero arrumar isso. Você pode fazer isso, mestre?";
				link.l1.go = "FDM_cabin";
			}
			if (!CheckAttribute(npchar, "quest.FDM_sails"))
			{
				link.l2 = "Estou cansado desses trapos pretos rasgados. Admito, eles pegam o vento tão bem quanto velas normais, mas a aparência... É horrível. Quero velas comuns, bem branquinhas. Topa, mestre?";
				link.l2.go = "FDM_sails";
			}*/
			
			if (!CheckAttribute(npchar, "quest.FDM_hull"))
			{
				link.l3 = "Bem, acho que está na hora de transformar isso em algo decente. O navio é bom, a tripulação já está acostumada, mas não é digno para um capitão respeitável navegar numa embarcação que assusta até adulto, quem dirá criança. Quero reconstruí-lo completamente, de modo que outros capitães sintam inveja quando virem meu navio, em vez de se benzerem. E a quem mais eu recorreria senão ao melhor construtor naval do arquipélago?";
				link.l3.go = "FDM_hull";
			}
		break;
		
		case "FDM_cabin":
			dialog.text = "Por que não? Minhas mãos ainda estão firmes.";
			link.l1 = "...";
			link.l1.go = "FDM_cabin_s";
			//link.l2 = "Não adianta exagerar nos luxos. Mantenha o padrão.";
			//link.l2.go = "FDM_cabin_s";
		break;
		
		case "FDM_cabin_m":
			dialog.text = "Certo. Dez baús de dobrões e estará pronto em cinco dias.";
			link.l1 = "Fechado!";
			link.l1.go = "FDM_cabin_m1";
			link.l2 = "Dez baús? Mil e quinhentos dobrões? Hm, preciso de um tempo para pensar em um gasto desses...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_s":
			dialog.text = "Sete baús de dobrões e estará pronto em cinco dias.";
			link.l1 = "Fechado!";
			link.l1.go = "FDM_cabin_s1";
			link.l2 = "Sete baús? Mais de mil doblões? Hm, preciso de um tempo para pensar em um gasto desses...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_m1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 10;
			npchar.quest.FDM_cabin.type = "Cabin_Huge";
			dialog.text = "Ótimo, vou aguardar o pagamento.";
			if (iTemp > 0)
			{
				link.l1 = "Tenho baús comigo. Vamos ver. Aqui, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "Preciso ir colocar moedas nos baús.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_s1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin.chest = 7;
			npchar.quest.FDM_cabin.type = "Cabin";
			dialog.text = "Ótimo, vou aguardar o pagamento.";
			if (iTemp > 0)
			{
				link.l1 = "Tenho baús comigo. Vamos ver. Aqui, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "Preciso ir colocar moedas nos baús.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_wait":
			DialogExit();
			npchar.quest.FDM_full = "cabin";
		break;
		
		case "FDM_cabin_pay":
			iTemp = GetCharacterItem(pchar, "Chest");
			amount = sti(npchar.quest.FDM_cabin.chest)-iTemp;
			Log_Info("You have given chests to Master Alexus");
			PlaySound("interface\important_item.wav");
			if (amount <= 0) // всё принес
			{
				RemoveItems(pchar, "chest", sti(npchar.quest.FDM_cabin.chest));
				dialog.text = "Então, você teve que me trazer "+FindRussianQtyString(sti(npchar.quest.FDM_cabin.chest))+" baús, você trouxe "+FindRussianQtyString(iTemp)+". Eu tenho o pagamento. Agora é minha vez. Vai dar uma volta. Não se preocupe, vou fazer o meu melhor.";
				link.l1 = "Bom...";
				link.l1.go = "FDM_cabin_do";
			}
			else
			{
				RemoveItems(pchar, "chest", iTemp);
				dialog.text = "Então, você teve que me trazer "+FindRussianQtyString(sti(npchar.quest.FDM_cabin.chest))+" baús, você trouxe "+FindRussianQtyString(iTemp)+". "+FindRussianQtyString(amount)+" baús restantes.";
				link.l1 = "Muito bem, mestre.";
				link.l1.go = "FDM_cabin_wait";
				npchar.quest.FDM_cabin.chest = amount;
			}
		break;
		
		case "FDM_cabin_do":
			DialogExit();
			SetLaunchFrameFormParam("Five days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.CabinType = npchar.quest.FDM_cabin.type;
			if (CheckAttribute(npchar, "quest.FDM_sails")) npchar.quest.FDM_full = "done";
			else DeleteAttribute(npchar, "quest.FDM_full");
			npchar.quest.FDM_cabin = "done";
		break;
		
		case "FDM_sails":
			dialog.text = "Claro, posso fazer isso! Pois bem... Isso significa que teremos que jogar fora todos os trapos velhos e colocar velas novas, limpas, feitas de algodão. Tem muito trabalho pela frente. Cem mil pesos pelo serviço e pelos materiais. Fechado?";
			if (sti(Pchar.money) >= 100000)
			{
				link.l1 = "Claro, por mim tudo bem. Fechado!";
				link.l1.go = "FDM_sails_do";
			}
			link.l2 = "Hm. Acho que preciso pensar sobre isso...";
			link.l2.go = "exit";
		break;
		
		case "FDM_sails_do":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Ótimo. Já tenho as moedas, agora vou trabalhar. Dê uma volta até eu terminar e não se preocupe.";
			link.l1 = "Bem...";
			link.l1.go = "FDM_sails_done";
		break;
		
		case "FDM_sails_done":
			DialogExit();
			SetLaunchFrameFormParam("Two days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//белый хлопковый парус
			npchar.quest.FDM_sails = "true";
			if (CheckAttribute(npchar, "quest.FDM_cabin")) npchar.quest.FDM_full = "done";
		break;
		//--> Xenon
		case "FDM_hull":
			dialog.text = "Bom, fico feliz em finalmente ouvir isso. E é verdade – você parece ser um bom sujeito, mas está navegando sabe-se lá em quê. Mas já vou avisando, esse serviço não é coisa de algumas horas, e vai te custar uma boa grana. ";
			link.l1 = "Certo, você pode ser um pouco mais específico?";
			link.l1.go = "FDM_hull_01";
		break;

		case "FDM_hull_01":
			dialog.text = "Alright, let's do the math... For a full rebuild of the ship's hull I'll need 150 units each of bakaut, ropes, ship silk and resin — and 10,000 gold doubloons. Don't look at me like that; most of the money will go on materials. This job is equivalent to dismantling the ship and building it again from scratch.";
			link.l1 = "Não, acho que não. Ainda não estou pronto para trazer tantos recursos e entregar uma pilha de ouro pela reconstrução. Vou ficar com o que tenho.";
			link.l1.go = "FDM_hull_thinking";
			link.l2 = "É, o que a gente não faz pelo nosso navio... Tudo bem, está combinado.";
			link.l2.go = "FDM_hull_02";
		break;

		case "FDM_hull_02":
			dialog.text = "Certo, menos conversa, mais ação. Vou esperar o dinheiro de você para começar a comprar tudo que preciso. Assim que eu tiver o dinheiro, você pode começar a me trazer os materiais. E então vou trabalhar no seu navio.";
			if(PCharDublonsTotal() >= 10000)
			{
    			link.l1 = "Bem, dinheiro não é problema. Eu tenho aqui comigo. Aqui está, mestre.";
    			link.l1.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "No momento, não tenho esse dinheiro. Espere um pouco, eu vou trazer para você.";
    			link.l1.go = "FDM_hull_waitmoney";
            }
		break;

		case "FDM_hull_waitmaterials":
			RemoveDublonsFromPCharTotal(10000);
			npchar.quest.FDMsandal = 0;
			npchar.quest.FDMoil = 0;
			npchar.quest.FDMshipsilk = 0;
			npchar.quest.FDMropes = 0;
			AddQuestRecord("renovate_fdm", "1");

			npchar.quest.FDM_hull = "hull_waitmaterials";
			dialog.text = "Não tem medo de andar por um assentamento pirata com essa quantia toda, hein? Brincadeira, aqui todo mundo é honesto, à sua maneira. Agora só falta o material. Só pra lembrar, você vai precisar trazer um total de 150 madeiras de ferro, 150 rolos de corda, 150 rolos de seda naval e 150 barris de resina.";
			link.l1 = "Aguente firme, vou trazer seus materiais.";
			link.l1.go = "exit";
		break;

		case "FDM_hull_checkmaterials":
			dialog.text = "Muito bem! O que você trouxe pra mim hoje?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && sti(npchar.quest.FDMsandal) < 150)
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "Ironwood na quantidade de "+FindRussianQtyString(iSan)+".";
				link.l1.go = "FDM_sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && sti(npchar.quest.FDMoil) < 150)
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "Resina na quantidade de "+FindRussianQtyString(iOil)+".";
				link.l2.go = "FDM_oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && sti(npchar.quest.FDMshipsilk) < 150)
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "Enviar seda na quantidade de "+FindRussianQtyString(iSil)+".";
				link.l3.go = "FDM_shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && sti(npchar.quest.FDMropes) < 150)
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "Cordas na quantidade de "+FindRussianQtyString(iRop)+".";
				link.l4.go = "FDM_ropes";
			} 
			link.l5 = "Ainda nada. Só queria confirmar se o acordo continua de pé.";
			link.l5.go = "exit";
		break;

		case "FDM_hull_checkmaterials_1":
			if (sti(npchar.quest.FDMsandal) > 149 && sti(npchar.quest.FDMoil) > 149 && sti(npchar.quest.FDMshipsilk) > 149 && sti(npchar.quest.FDMropes) > 149)
			{
				dialog.text = "Maravilha! Todos os materiais estão aqui. Agora, deixe esse monstro comigo. Finalmente, ele vai ter a aparência que merece.";
				link.l1 = "Certo, chega de reclamação, mestre. Estou ansioso pelo resultado.";
				link.l1.go = "FDM_hull_building";
			}
			else
			{
				dialog.text = "Tem mais alguma coisa pra alegrar meu dia, Capitão?";
				link.l1 = "Bem, por enquanto é só.";
				link.l1.go = "exit";
				link.l2 = "Sim, tenho outra coisa para você...";
				link.l2.go = "FDM_hull_checkmaterials";
			}
		break;

		case "FDM_sandal": // бакаут
			amount = 150 - sti(npchar.quest.FDMsandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) 
			{
				dialog.text = "Vamos ver... Eu preciso de "+FindRussianQtyString(amount)+" de madeira de ferro. Você trouxe "+FindRussianQtyString(iSan)+". de pau-ferro. Portanto, você ainda precisa me trazer "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Obrigado! Em breve eu trago o resto pra você.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + iSan;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Vamos ver... Ainda preciso "+FindRussianQtyString(amount)+" de madeira de ferro. Você me trouxe  "+FindRussianQtyString(iSan)+". Portanto, terminamos com a madeira de ferro!";
				link.l1 = "Obrigado!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood"); 
			}
		break;

		case "FDM_oil": // смолы
			amount = 150 - sti(npchar.quest.FDMoil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) 
			{
				dialog.text = "Vamos ver... Eu preciso de "+FindRussianQtyString(amount)+" de resina. Você trouxe "+FindRussianQtyString(iOil)+". Portanto, você ainda precisa me trazer "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Obrigado! Em breve trago o restante para você.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				npchar.quest.FDMoil = sti(npchar.quest.FDMoil) + iOil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Deixe-me ver... Ainda preciso "+FindRussianQtyString(amount)+" de resina. Você me trouxe "+FindRussianQtyString(iOil)+"  Portanto, terminamos com a resina! ";
				link.l1 = "Obrigado!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.FDMoil = makeint(npchar.quest.FDMoil) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
			}
		break;

		case "FDM_shipsilk": // шёлк
			amount = 150 - sti(npchar.quest.FDMshipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) 
			{
				dialog.text = "Vamos ver... Eu preciso de "+FindRussianQtyString(amount)+" de seda de navio. Você trouxe "+FindRussianQtyString(iSil)+". Portanto, você ainda precisa me trazer "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Obrigado! Logo trago o resto pra você";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + iSil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Vamos ver... Ainda preciso "+FindRussianQtyString(amount)+" de seda de navio. Portanto, você ainda precisa me trazer "+FindRussianQtyString(iSil)+". Portanto, terminamos com a seda de navio";
				link.l1 = "Obrigado!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk"); 
			}
		break;

		case "FDM_ropes": // канаты
			amount = 150 - sti(npchar.quest.FDMropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) 
			{
				dialog.text = "Vamos ver... Eu preciso de "+FindRussianQtyString(amount)+" de cordas. Você trouxe "+FindRussianQtyString(iRop)+". Portanto, você ainda precisa me trazer "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Obrigado! Vou trazer o resto em breve";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + iRop;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Vamos ver... Eu preciso de  "+FindRussianQtyString(amount)+" de cordas. Você trouxe "+FindRussianQtyString(iRop)+". Portanto, terminamos com as cordas!";
				link.l1 = "Obrigado!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
			}
		break;

		case "FDM_hull_thinking":
			DialogExit();
			npchar.quest.FDM_secondtime = true;
		break;

		case "FDM_hull_waitmoney":
			DialogExit();
			npchar.quest.FDM_hull = "hull_waitmoney";
		break;

		case "FDM_hull_givemoney":
			dialog.text = "Então, trouxe o dinheiro";
			if(PCharDublonsTotal() >= 10000)
			{
    			link.l2 = "Sim, eu trouxe. 10.000 dobrões de peso cheio, conforme combinado.";
    			link.l2.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "Ainda não, espere um pouco, mestre.";
    			link.l1.go = "exit";
            }
		break;

		case "FDM_hull_building":
			DialogExit();
			SetLaunchFrameFormParam("Five days passed..."+ NewStr() +"Master Alexus completed the job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //Pass time
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			
			shTo = &RealShips[sti(pchar.Ship.Type)];
			object newShip;
			aref arTuning;
			CopyAttributes(&newShip, shTo);
			
			pchar.Ship.Type = GenerateShipExt(SHIP_RENOVATED_FDM, 0, pchar);
			
			if(CheckAttribute(newShip, "Tuning"))
			{
				makearef(arTuning, newShip.tuning);
				for (int iQty = 0; iQty < GetAttributesNum(arTuning); iQty++)
				{
					aref realTuning = GetAttributeN(arTuning, iQty);
					string tuningName = GetAttributeName(realTuning);
					UpgradeShipParameter(pchar, tuningName);
				}
			}
			if(CheckAttribute(newShip, "Traits")) RealShips[sti(pchar.Ship.Type)].Traits = newShip.Traits;
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//White cotton sail
			pchar.ship.hp = GetCharacterShipMaxHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");	
			CloseQuestHeader("renovate_fdm");
			Achievment_Set("ach_CL_178");
		break;
		//<-- Xenon
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
