void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp,sTemp1, str, str1;
	int	s1,s2,s3,s4,s5,p1, iColony, crewWhoreCost, charWhoreCost = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
		
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	crewWhoreCost = 50 + 7 * MOD_SKILL_ENEMY_RATE - hrand(40);
	charWhoreCost = 2460 + sti(pchar.rank) * 40;
	
	switch(Dialog.CurrentNode)
	{
		// ============= хозяйка борделя =============
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase(""+GetSexPhrase("Que garotas, querido?! Metade da guarnição está atrás de você, e mesmo assim você vem direto para o bordel!","Cai fora, vai! Metade da guarnição está atrás de você!")+"","Todos os guardas da cidade estão atrás de você. Não sou tolo de te ajudar agora ...","Você não tem nada para fazer aqui!"),LinkRandPhrase(""+GetSexPhrase("Se ousar encostar nas minhas meninas, eu arranco sua pele viva!","Cai fora, seu nojento!")+"","Imundo"+GetSexPhrase("","")+" Assassino, saia do meu estabelecimento, agora! Guardas!!!","Eu não tenho medo de você, "+GetSexPhrase("canalha","rato")+" ! Logo você será enforcado em nosso forte, não vai chegar longe... "));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, um alarme nunca é problema pra mim...","Eles nunca vão me pegar."),RandPhraseSimple("Cala a boca, sua velha estúpida.","Cale a boca se não quiser arrumar confusão..."));
				link.l1.go = "exit";
				break;
			}
			//--> Мерзкий Божок
			if (CheckAttribute(pchar, "questTemp.ChickenGod.HostessDialog")) {
				dialog.text = "Meu Deus! Como você entrou aqui? Capitão, por favor, vá embora – eu lhe imploro! Nosso estabelecimento está fechado no momento!";
				link.l1 = "Que bom te ver, querido(a) "+npchar.name+". Eu estava na lista de convidados. Porém, em lugares assim, até os convidados precisam pagar, então... Por favor, não complique as coisas pra mim, mas quero pagar por um quarto.";
				link.l1.go = "chicken_god";
				
				DeleteAttribute(pchar, "questTemp.ChickenGod.HostessDialog");
				break;
			}
			//<-- Мерзкий Божок
			//--> туториал Мартиника
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start" && npchar.location == "FortFrance_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				link.l1 = "Escuta, Aurora, preciso de uma moça para esta noite. E quero levá-la para casa comigo. Você pode arranjar isso?";
                link.l1.go = "Gigolo";
				break;
			}
			//<-- туториал Мартиника
			//Jason --> Заносчивый аристократ
			if (!CheckAttribute(pchar, "GenQuest.Badboy") && !CheckAttribute(npchar, "quest.Badboy") && !CheckAttribute(pchar, "questTemp.ZA.Block") && makeint(environment.time) > 15.0 && makeint(environment.time) < 21.0 && sti(pchar.questTemp.HorseQty) > 4)
			{
				dialog.text = "Você é um homem tão distinto. Além disso, minhas meninas gostam muito de você. Gostaria de lhe pedir um pequeno favor para o meu estabelecimento.";
				link.l5 = "Fico lisonjeado, com certeza. Em que posso te ajudar?";
				link.l5.go = "Badboy";
				link.l8 = "Desculpe, mas estou ocupado no momento.";
				link.l8.go = "exit";
				npchar.quest.Badboy = "true";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Badboy.Complete") || CheckAttribute(pchar, "GenQuest.Badboy.Continue"))
			{
				if (npchar.City == pchar.GenQuest.Badboy.Brothel.City)
				{
					dialog.text = "Oh, você voltou! Já resolveu aquilo "+pchar.GenQuest.Badboy.Brothel.Name+" deixar minhas garotas em paz?";
					link.l5 = "Sim. Ele não vai mais aparecer por aqui.";
					link.l5.go = "Badboy_complete";
				break;
				}
			}
			// <-- Заносчивый аристократ
			
			//--> Jason Португалец
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (!CheckAttribute(pchar, "questTemp.Portugal") && bOk && !CheckAttribute(npchar, "quest.Portugal") && npchar.location == "Marigo_SecBrRoom" && makeint(environment.time) > 6.0 && makeint(environment.time) < 22.0 && sti(pchar.rank) >= 7)
				{
					DelMapQuestMarkCity("marigo");
					DelLandQuestMark(npchar);
					dialog.text = "Capitão, posso lhe pedir um favor?";
					link.l5 = "Para você, senhora, o que quiser! Estou ao seu dispor!";
					link.l5.go = "Portugal";
					link.l8 = "Desculpe, mas estou ocupado no momento.";
					link.l8.go = "exit";
					npchar.quest.Portugal = "true";
					DelLandQuestMark(npchar);
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "HostressMoney" && npchar.location == "Marigo_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Você já falou com o Hugo, senhor Capitão?";
				if (sti(pchar.money) >= 10000)
				{
					link.l1 = "Além disso, senhora, aqui está o seu dinheiro. Tudo correu da melhor forma possível...";
					link.l1.go = "Portugal_3";
				}
				else
				{
					link.l1 = "Sim, transmiti seu pedido a ele.";
					link.l1.go = "Portugal_exit";
				}
				break;
			}
			//<--Португалец
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "Meu Deus, olhem só! Charlie Prince, o famoso corsário! Em pessoa!";
				link.l1 = RandSwear()+"Olá, Janette. Estou aqui em uma missão para Marcus Tyrex.";
				link.l1.go = "mtraxx_R";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel_repeat" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "Está pronto para um tratamento restaurador inesquecível, meu bravo corsário?";
				if (sti(pchar.money) >= 31000)
				{
					link.l1 = "Sou eu! Charlie Prince não desperdiça palavras como desperdiça dinheiro, ha-ha!";
					link.l1.go = "mtraxx_R2";
				}
				else
				{
					link.l1 = "Quase... Acho que perdi minha bolsa no seu estabelecimento... Vou voltar com dinheiro!";
					link.l1.go = "exit";
				}
				break;
			}
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+". Bem-vindo à minha casa do amor. Meu nome é "+npchar.name+", e eu sou o proprietário. "+GetSexPhrase("O que posso fazer por você, "+GetAddress_Form(NPChar)+"?","Para ser sincero, estou um pouco surpreso em te ver aqui, "+GetAddress_Form(NPChar)+", mas garanto que oferecemos serviços não só para homens.")+"",TimeGreeting()+". Eu lhe dou as boas-vindas, "+GetSexPhrase("estranho","moça")+", ao meu humilde estabelecimento. Permita-me apresentar, eu sou "+NPChar.Name+" - guardiã deste refúgio para homens famintos pelo toque de uma mulher. "+GetSexPhrase("O que posso fazer por você?","Embora também tenhamos um certo interesse pelas damas...")+"");
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+". Como posso ajudar você, "+GetAddress_Form(NPChar)+"?",TimeGreeting()+". O que posso fazer por você, "+GetAddress_Form(NPChar)+"?");
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))//не идёт квест девочки
			{
				if (!CheckAttribute(pchar, "GenQuest.BrothelLock"))// нет запрета от Мэри 280313
				{
					link.l2 = npchar.name+", quero passar um tempo de qualidade com uma das suas garotas.";
					link.l2.go = "Hostess_1";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // не идёт старт Шарля
			{
				if (sti(pchar.ship.type) != SHIP_NOTUSED && GetCrewQuantity(pchar) > 0) // Rebbebion - а смысл, если нет как корабля, так и команды?
				{
					link.l3 = "Faz tempo que não dou um agrado pros meus homens. Posso fazer um pedido grande de garotas pro meu pessoal?";
					link.l3.go = "ForCrew";
				}
			}
			link.l4 = "Tenho uma pergunta.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakBrothelMadam"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l4.go = "ShipLetters_1";// генератор  "Найденные документы"
				}
				else
				{
					link.l4.go = "quests";
				}	
			}
			else
			{
				link.l4.go = "quests";//(перессылка в файл города)
			}	
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = "Escute, "+npchar.name+", estou procurando o anel do governador. Ele se hospedou no seu estabelecimento e provavelmente o perdeu aqui.";
				link.l5.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра

			// belamour ночной приключенец -->
			if(CheckAttribute(pchar, "GenQuest.NightAdventureVar") && pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleWhoreMoney")
			{
				link.l8 = "Olha, eu gostaria de ficar com a melhor moça que você tem.";
				link.l8.go = "NA_Girl";
			}
			// <-- приключенец
			link.l9 = "Deixa pra lá, já estou indo embora.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_1":
				pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
				dialog.text = RandPhraseSimple("O que você quer, bonitão?","Estou ouvindo você, Capitão.");
				link.l1 = "Escute, "+npchar.name+", encontrei estes papéis em uma sala privada da sua instituição ...";
				link.l1.go = "ShipLetters_2";				
		break;
		
		case "ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Deixe-me ver! Hmm... algum capitão perdeu seus documentos, certo? Acho que você deveria perguntar ao mestre do porto sobre isso.";
				link.l1 = "Talvez, talvez...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Deixe-me dar uma olhada! Oh! Pelo nome, pertencem ao meu estimado cliente e um cidadão respeitável da nossa cidade. Posso entregar esses documentos a ele pessoalmente.";
				link.l1 = "Provavelmente não...";
				link.l1.go = "exit";
				link.l2 = "Excelente! Sempre fico feliz em ajudar uma boa pessoa e um estabelecimento digno.";
				link.l2.go = "ShipLetters_3";										
			}	
		break;
		
		case "ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "2");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Hostess_1":
			if (!CheckAttribute(npchar, "quest.selected"))
			{
				if (CheckNPCQuestDate(npchar, "quest.date"))
				{
					dialog.text = ""+GetSexPhrase("Sempre temos prazer em atender um cliente. Agora me diga, bonitão – já escolheu alguém, ou tanto faz pra você?","Bem, minhas garotas certamente podem... ajudá-lo. Já escolheu alguma, ou não faz muita questão?")+"";
					Link.l1 = ""+GetSexPhrase("Heh, eu só preciso de uma prostituta e preciso dela agora. Não me importa qual, todas as suas garotas me parecem ótimas...","Qualquer uma serve, desde que saiba cumprir seus deveres, é claro...")+"";
					Link.l1.go = "Hostess_NotChoice";	
					Link.l2 = "Sim, tem um, "+GetSexPhrase("que chamou minha atenção...","ela seria a mais gentil...")+"";
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = "Hoje não tenho nenhuma moça livre pra você, já estamos cheios de clientes. Volte amanhã, você não vai se arrepender!";
					Link.l1 = "Que pena, eu estava começando a gostar disso.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Hum. Você já pagou pela moça. Por favor, não me distraia.";
				Link.l1 = "Certo, estou indo.";
				Link.l1.go = "exit";	
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
			{
				dialog.text = "Não tenho nenhuma moça disponível no momento, você vai ter que voltar daqui a alguns dias.";
				Link.l1 = "Está bem, como quiser.";
				Link.l1.go = "exit";	
			}
			else
			{
				// belamour legendary edition Орден Святого Людовика -->
				if(IsEquipTalisman9() && npchar.nation == FRANCE)
				{
					dialog.text = ""+GetSexPhrase("Bem, garanhão, isso é excelente!","Todos eles são habilidosos, pode ter certeza.")+"Posso oferecer uma bela moça chamada "+GetFullName(sld)+", ela está livre agora.\nOra, o que é isso que você esconde aí com tanta modéstia?! É a mais alta condecoração da França? Dizem por aí que quem carrega essa insígnia é lendário não só nos campos de batalha... Bem, você sabe do que estou falando, meu filibusteiro... Além disso, qualquer um consideraria uma honra tocar no seu 'Ordem', então hoje à noite você descansa por conta da casa. Recusar não é opção, bonitão.";
					Link.l1 = "Claro que eu concordo, que dúvidas poderiam haver?!";
					Link.l1.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
					break;
				}
				// <-- legendary edition
				dialog.text = ""+GetSexPhrase("Muito bem, meu garanhão!","Eles são todos muito habilidosos no que fazem, pode ter certeza.")+" Posso lhe oferecer uma moça muito encantadora, o nome dela é "+GetFullName(sld)+", e ela está disponível no momento. Esse prazer vai lhe custar "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+". Concorda?";
				Link.l1 = "Não. Acho que não. É caro demais...";
				Link.l1.go = "exit";
				if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
				{
					Link.l2 = "Claro, como eu poderia recusar?!";
					Link.l2.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = "Ah, droga, não tenho tanto dinheiro comigo...";
					Link.l1.go = "exit";
				}
			}
		break;
		
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
			{
				dialog.text = "Tudo bem, "+GetSexPhrase("bonito","linda")+". "+sld.name+" estarei esperando por você em um quarto privado no segundo andar.";
				Link.l1 = ""+GetSexPhrase("Certo, estou indo, então","Tá bom, eu vou, então")+"...";
				Link.l1.go = "exit";
				// belamour legendary edition деньги только без ордена или адмиральского мундира
				if(IsEquipTalisman9())
				{
					if(npchar.nation != FRANCE) AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				else
				{
					AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				sld.dialog.currentnode = "Horse_ReadyFack";			
				//--> таймер на возврат, чтобы не вечно ждали
				str = npchar.city;
				pchar.quest.(str).win_condition.l1            = "Timer";
				pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition               = "Brothel_checkVisitTime";	
				pchar.quest.(str).HorseId = sld.id;
				pchar.quest.(str).locator = sld.location.locator;
				//<-- таймер на возврат, чтобы не вечно ждали
				ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto"+(rand(2)+1));
				LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //открываем комнату
				npchar.quest.selected = true; //флаг взял девку у хозяйки
				SetNPCQuestDate(npchar, "quest.date"); //дату взятия запишем
				for(int n=0; n<MAX_CHARACTERS; n++)
				{
					makeref(sld, Characters[n]);
					if (sld.location == npchar.city+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
					{
						sld.dialog.currentnode = "Horse_4";
					}
				}
				
				// генератор найденных бумаг
				
				// belamour legendary edition не давать квесты губернатору и адмиралу
				bool MCGovernon = CheckAttribute(pchar, "questTemp.Patria.GenGovernor");
				bool MCAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4;
				
				if ((rand(4) == 1) && (pchar.questTemp.different == "free") && (!CheckCharacterItem(pchar, "CaptainBook")) && GetNpcQuestPastDayWOInit(npchar, "questShipLetters") > 10 && !MCGovernon && !MCAdmiral ) 
				{					
					pchar.questTemp.different = "GiveShipLetters";
					pchar.questTemp.different.GiveShipLetters = "toBrothel";
					pchar.questTemp.different.GiveShipLetters.Id = GetFullName(npchar);
					pchar.questTemp.different.GiveShipLetters.city = npchar.city;	
					pchar.questTemp.different.GiveShipLetters.variant = rand(2);
					p1 = rand(20 - MOD_SKILL_ENEMY_RATE) + 1; // даем хотя бы один день
					s1 = rand(80 - pchar.rank - p1) * 50 + rand(100);
					s2 = s1 * 2;
					s3 = s1 * rand(GetCharacterSPECIAL(pchar, "Luck")) + s1;
					s4 = s2 + s3;
					s5 = s4 * GetCharacterSPECIAL(pchar, "Charisma");
					pchar.questTemp.different.GiveShipLetters.price1 = s1;
					pchar.questTemp.different.GiveShipLetters.price2 = s2;
					pchar.questTemp.different.GiveShipLetters.price3 = s3;
					pchar.questTemp.different.GiveShipLetters.price4 = s4;
					pchar.questTemp.different.GiveShipLetters.price5 = s5;
										
					sld = ItemsFromID("CaptainBook");
					sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
					//ложим бумаги в итем								
					sTemp = "_Brothel_room";	
					sTemp1 = "_town";					
					sld.shown = true;
					sld.startLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp;
					sld.startLocator = "item" + (rand(4)+1);
					sld.endLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp1;
					pchar.questTemp.different.GiveShipLetters.item = true; //флаг -  бумаги валяются в итемах
					Log_QuestInfo("The papers are in location " + sld.startLocation + ", in locator " + sld.startLocator + " p1 : " + p1);
					
					pchar.quest.CheckShipLetters.win_condition.l1 = "location";
					pchar.quest.CheckShipLetters.win_condition.l1.location = sld.endLocation;
					pchar.quest.CheckShipLetters.function = "CheckShipLetters";
					
					SetTimerFunction("GiveShipLetters_null", 0, 0, p1); //освобождаем разрешалку на миниквесты 
					SaveCurrentNpcQuestDateParam(npchar, "questShipLetters");					
				}
				// генератор - "Повод для спешки"
				if((rand(5) == 2) && !CheckAttribute(pchar, "questTemp.ReasonToFast") && GetNpcQuestPastDayWOInit(npchar, "questReasonToFast") > 20 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !MCGovernon && !MCAdmiral) // Addon-2016 Jason
				{
					iColony = FindColony(npchar.city);	
					if( sti(Colonies[iColony].HeroOwn) == false && npchar.city != "Panama" && npchar.city != "Charles")
					{
						pchar.questTemp.ReasonToFast = "Begin";
						pchar.questTemp.ReasonToFast.city = npchar.city;
						sTemp1 = "_town";					
						pchar.quest.CheckReasonToFast.win_condition.l1 = "location";
						pchar.quest.CheckReasonToFast.win_condition.l1.location = npchar.city + sTemp1;
						pchar.quest.CheckReasonToFast.function = "ReasonToFast_CheckHorse";
						SaveCurrentNpcQuestDateParam(npchar, "questReasonToFast");	
					}	
				}				
			}
			else
			{
				dialog.text = "Ah, veja, o problema é que "+sld.name+" não é uma garota barata, o preço dela é "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+". E eu vejo que você simplesmente não pode pagar por ela no momento. Volte quando estiver rico"+GetSexPhrase(", querido","")+"...";
				Link.l1 = "É a minha sorte...";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = "Fico sempre feliz quando garotas e clientes criam sentimentos calorosos um pelo outro... Diga-me o nome dela.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";	
		break;
		
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = "Hum... você deve estar enganado. Não tenho nenhuma moça assim no meu estabelecimento. Talvez você tenha confundido o nome dela.";
				Link.l1 = "Hum... mas eu acabei de falar com ela.";
				Link.l1.go = "Hostess_Choice_2";				
				Link.l2 = "Talvez. Seria melhor perguntar o nome dela de novo, só para ter certeza. Depois converso com você sobre isso.";
				Link.l2.go = "exit";	
			}
			else
			{
				dialog.text = GetFullName(sld)+", você está falando dela?";
				Link.l1 = "Sim, sobre ela.";
				Link.l1.go = "Hostess_NotChoice_agree";				
				Link.l2 = "Não, não é ela.";
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
		
        case "Hostess_Choice_2":
			dialog.text = "Então talvez você devesse me dizer o nome dela mais uma vez, e talvez eu perceba de quem você está falando.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = "Talvez. Seria melhor perguntar o nome dela de novo, só para ter certeza. Depois converso com você sobre isso.";
			Link.l2.go = "exit";	
		break;
		//==> команда
		case "ForCrew":
			dialog.text = "Hum... Quer ajudar seus homens a 'relaxar um pouco'? Veja, meu estabelecimento é respeitável, e tenho as melhores moças por aqui. Mas conheço algumas mulheres dos portos, e elas vão adorar agradar todos os seus marinheiros. Isso vai lhe custar "+FindRussianMoneyString(GetCrewQuantity(pchar)*crewWhoreCost)+".";			
			link.l1 = "Certo, eu concordo.";
			link.l1.go = "ForCrew_1";
			link.l2 = "Acho que eles conseguem se virar sem isso...";
			link.l2.go = "exit";
		break;
		
		case "ForCrew_1":
		    if (sti(Pchar.money) >= GetCrewQuantity(pchar)*crewWhoreCost && GetCrewQuantity(pchar)>0)
		    {
		        AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar)*crewWhoreCost));
	            AddCrewMorale(Pchar, 10);
				ChangeCharacterComplexReputation(pchar,"authority", 1);
	            LAi_Fade("", "");
                AddTimeToCurrent(5 + rand(1), rand(30));
			    DialogExit();
		    }
		    else
		    {
		        dialog.text = "Não é da minha conta, mas acho que primeiro você deveria juntar dinheiro suficiente para contratar uma tripulação, e só depois se preocupar com o espírito dela.";
			    link.l1 = "Você provavelmente está certo...";
			    link.l1.go = "exit";
		    }
		break;
		
		case "Woman_FackYou":
			dialog.text = "Querido, o que você pensa que está fazendo?! E eu achava que você era um capitão decente... Dessa vez você não vai 'voar' pra longe, bonitão. Os guardas vão cortar suas asas...";
			link.l1 = "Cala a boca, velha.";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		
		//поиски кольца губернатора
		case "TakeMayorsRing_H1":
			dialog.text = "Eu não encontrei nenhum anel.";
			link.l1 = "E as suas garotas?";
			link.l1.go = "TakeMayorsRing_H2";
		break;
		
		case "TakeMayorsRing_H2":
			dialog.text = "Eles também não. Se algum cliente esquece ou perde alguma coisa, minhas meninas trazem para mim. Mas ninguém me trouxe o anel do governador.";
			link.l1 = "Entendo... Mas será que eles decidiram ficar com isso para eles mesmos?";
			link.l1.go = "TakeMayorsRing_H3";
		break;
		
		case "TakeMayorsRing_H3":
			dialog.text = "Improvável. As garotas podem ficar com os presentes dos clientes, mas só isso.";
			link.l1 = "Entendi. Bem, obrigado, "+npchar.name+".";
			link.l1.go = "exit";
		break;
		
		case "Hostess_inSexRoom":
			dialog.text = "Ah, aí está você...";
			link.l1 = "Aqui estou, minha senhora!";
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //нулим таймер на не пришёл
			NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
			{
				sld = CharacterFromID(pchar.RomNaTroih_Shluha);
				dialog.text = ""+sld.name+"! Meu herói, vejo que você não perdeu tempo lá embaixo!";
				link.l1 = "Espero que me perdoe por essa fraqueza, minha rainha?";
				link.l1.go = "RomNaTroih_2";
			}
			AddDialogExitQuestFunction("SexWithHostess_fack");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.RomNaTroih");
            if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 10);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 5);
		break;
		
		// ================================== рядовой состав =======================================
        case "Horse_talk":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("É melhor você sair do estabelecimento!","Todos os guardas da cidade estão te procurando! É melhor você ir embora...","Você fez uma bagunça e agora aparece aqui?! Não, dessa vez não..."),LinkRandPhrase("Cai fora!","Assassino imundo, saia daqui! Guardas!","Eu não tenho medo de você,"+GetSexPhrase("canalha","rato")+"Em breve você será enforcado em nosso forte, não vai chegar muito longe..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, um alarme nunca é problema pra mim...","Eles nunca vão me pegar."),RandPhraseSimple("Heh, que tola você é...","Cala a boca, vadia, ou eu vou calar com outra coisa..."));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat("Olá, "+GetAddress_Form(NPChar)+""+GetSexPhrase("",", hee-hee...")+". Você precisa falar com a senhora e preencher o pedido.","Você de novo? Por favor, fale com a responsável. Ela está no escritório dela.","Olha, "+GetAddress_Form(NPChar)+""+GetSexPhrase(", espero mesmo que você seja tão teimoso em outras coisas quanto é ao falar... De novo","Mais uma vez")+" Peço que me leve até o proprietário do estabelecimento.","Oh, "+GetAddress_Form(NPChar)+""+GetSexPhrase(", você é teimoso mesmo!",", Hee-hee... Você é teimoso mesmo, não é?")+" Você precisa falar com a senhora e preencher o pedido.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Certo, "+GetSexPhrase("beleza, ","")+"Entendi"+GetSexPhrase("","")+".","É, tá bom...",""+GetSexPhrase("Não tenha dúvida, minha linda, sou teimoso e forte como um touro!","Tá, tá...")+"",""+GetSexPhrase("Ah, droga, devo ter deixado passar alguma coisa... Me desculpe, querida.","Tudo bem, está certo.")+"",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = "E onde ela está?";
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(""+GetSexPhrase("Oh, beleza, eu poderia me afogar nesses seus olhos...","Você está linda, querida!")+"",""+GetSexPhrase("Sabe, nunca conheci uma mulher tão linda antes!","Sabe, nunca conheci uma dama tão encantadora antes!")+"",""+GetSexPhrase("Querida, você está linda.","Por Deus, eu já estava cansada de toda aquela gente do interior... E você é tão encantador!")+"");
			if (!CheckAttribute(npchar, "quest.choice"))
			{
				Link.l3.go = "Horse_2";
			}
			else
			{
				Link.l3.go = "HorseChoice_" + npchar.quest.choice;
			}
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = LinkRandPhrase("Escute, "+GetSexPhrase("beleza","querida")+", por acaso você encontrou uma aliança de casamento por aqui? Parece que alguém a perdeu...","Querido, você viu uma aliança de casamento ou algo assim por aqui?","Escute, "+GetSexPhrase("meu gatinho","gata")+", você não viu uma aliança de casamento por aqui?");
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "santodomingo_brothel" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_1" && npchar.id == "HorseGen_"+reload_location_index+"_2")
			{
				link.l6 = "Oi, querida. Marcus Tyrex me mandou, dá uma olhada nesse colar de âmbar...";
				link.l6.go = "mtraxx";
			}
			NextDiag.TempNode = "Horse_talk";
		break;
		
        case "Horse_1":
			dialog.text = "Ela está no escritório dela. Você pode chegar lá por aqui, pela porta em frente à saída para a rua, ou pela rua, do outro lado da casa. O nome dela é "+characters[GetCharacterIndex(npchar.city+"_Hostess")].name+".";
			Link.l1 = "Entendi. "+GetSexPhrase("querida","querida")+", obrigado.";
			Link.l1.go = "exit";			
		break;
		
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase("Ah, que bom ouvir isso! Olha, estou livre agora, então se me escolher, não vai se arrepender...","Você acha mesmo? Olha, que gentileza sua... Escuta, estou livre agora, então pode me escolher."+GetSexPhrase(" Eu te prometo um mar de amor e um oceano de carícias... ","")+"",""+GetSexPhrase("Você acha mesmo? Ah, estou realmente lisonjeada. Sabe, raramente ouço elogios assim...","Ah, garota... se você soubesse o quanto estou de saco cheio desses caipiras...")+" Ei, olha, estou livre agora, então pode me escolher pra te fazer feliz. Não vou te decepcionar, prometo...");
				if (CheckAttribute(pchar, "questTemp.RomNaTroih") && !CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
				{
					link.l1 = "Minha querida, era exatamente isso que eu ia fazer! Que sorte que sua anfitriã já marcou um encontro particular comigo lá em cima. Quer se juntar?";
					Link.l1.go = "RomNaTroih_1";
					pchar.questTemp.RomNaTroih_Pogovoril = true;
					break;
				}
				link.l1 = "Então, vou escolher você, então!";
				Link.l1.go = "Horse_3";		
				Link.l2 = ""+GetSexPhrase("Não, isso foi só um elogio para uma dama encantadora","Foi só um elogio")+".";
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //был базар, но ГГ потом отказался
			}
			else
			{
				dialog.text = LinkRandPhrase(""+GetSexPhrase("Sabe o que eu digo, querido? Não preciso dessas conversinhas baratas. Faça negócio ou caia fora!","Era só o que me faltava! Elogios de mulheres!")+"",""+GetSexPhrase("Você é daqueles que acha que as mulheres se apaixonam pelo que ouvem? Olha, querido, isso não é verdade. Se me quer, pague à madame e poupe-me das suas palavras vazias.","Moça, não perca tempo com conversa fiada. Se quer algo de verdade – então pague...")+"",""+GetSexPhrase("Ah, mais um amante dos prazeres... É só pagar e eu sou sua. Simples assim, sem essa bobagem de gentileza!","O que há de errado com você, querido? Se quer se entregar aos prazeres, então pague logo e pare com essa bobagem!")+"");
				link.l1 = "Oh, que pegada!";
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //ГГ послали
			}
		break;
		
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city+"_Hostess")].name+" completa todas as formalidades no escritório dela. Vá falar com ela"+GetSexPhrase(", meu herói,","")+" e diga meu nome - "+npchar.name+". Estarei esperando por você...";
			Link.l1 = "Entendi, querida, volto já...";
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //она согласная
			SetNPCQuestDate(npchar, "quest.choice");
		break;
		
        case "Horse_4": 
			dialog.text = NPCStringReactionRepeat("Você já pagou.","Eu disse para você subir.","Lá em cima, rapaz.","Tem gente que pensa tão devagar...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sim, eu sei.","Eu me lembro.","Ah, não precisa repetir, eu me lembro.","Hum, o que você quer dizer?",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		
		//===>> реакция на попытки пофлиртовыть, если флирт уже был
        case "HorseChoice_0": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Eu só não entendo muito bem você."+GetSexPhrase(" Primeiro você faz elogios, e depois volta atrás com sua palavra. Que tipo estranho...","")+"","Elogios de novo?","A responsável está no escritório dela. Entendeu?","Não deveríamos insultar nossos clientes, mas você está realmente pedindo por isso"+GetSexPhrase("","")+"...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Aconteceu do jeito que aconteceu...","Certo, vou fazer isso.","Sim, entendi.","Me perdoe, meu amor.",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Obrigada pelo elogio. Se quiser me levar, é só falar com a madame. Negócios como sempre.";
				Link.l1 = "Entendi.";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Querido, nós já conversamos sobre tudo isso. ","")+"Não me faça esperar demais...",""+GetSexPhrase("Hmm... Escute, querido, eu","Eu")+" Eu acho suas palavras muito bonitas e tudo mais, mas será que podemos ir direto ao assunto... ","Talvez você queira discutir isso com a madame, não é?","Hmm... Eu nem sei o que dizer...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Eu nunca faria isso, espere por mim!","Com certeza!","Claro, como você diz!","Já estou correndo para ver sua senhora...",npchar,Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Eu estava esperando por você, mas você não veio me buscar... Não posso dizer que gostei disso...";
					Link.l1 = "Veja, simplesmente aconteceu assim...";
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //был базар, но ГГ потом отказался
				}
			}
			else
			{
				dialog.text = "Oh, é você de novo, meu "+GetSexPhrase("corsário glorioso","moça bonita")+"! Se quiser me ver de novo, procure a madame, você não vai se arrepender..."+GetSexPhrase(" Aliás, eu te reconheci, querido(a), mas nos disseram que devemos tratar todos os clientes da mesma forma. Não pode haver favoritos, me desculpe por isso...","")+"";
				Link.l1 = "Não se preocupe, querida. Só espere por mim mais um pouco, "+GetSexPhrase("fofa","fofa")+", e em breve nos encontraremos em particular novamente.";
				Link.l1.go = "exit";
				Link.l2 = "É muito gentil da sua parte lembrar de mim, mas não posso passar esta noite com você, desculpe.";
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
		
        case "HorseChoice_2": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Então,"+GetSexPhrase(" querido amigo,","")+" é melhor você se ocupar com algum trabalho. É mais útil do que ficar sem fazer nada.",""+GetSexPhrase("Hum, por que você ","Por que você está")+" dizendo as mesmas coisas repetidas vezes?","Ei, já não basta?!","Hm, que surpresa, nada de novo"+GetSexPhrase(", mais uma vez com essas tentativas tolas de charme! Se quer transar comigo, vá falar com a madame, seu cabeça de vento!","...")+"","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Sim, eu ouvi"+GetSexPhrase("","")+" você...","Hmm, então é assim que acaba...","Hum, talvez isso já baste, ou talvez não...","Cuidado com o que fala"+GetSexPhrase(", cabra","")+"...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Oh, é você de novo! "+GetSexPhrase("E mais uma vez, todos aqueles elogios idiotas. Nada nunca muda neste mundo... Se ","Só um lembrete: se ")+"você quer "+GetSexPhrase("divirta-se","aproveite")+" comigo, pague ao dono do estabelecimento. Não dou a mínima para suas palavras.";
				Link.l1 = "Isso não é nenhuma grande surpresa...";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1_Add":
			dialog.text = "Não posso dizer que isso me deixou feliz... Uma pena.";
			Link.l1 = "Me desculpe...";
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		
		//===>> секс
        case "Horse_ReadyFack":
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "SantoDomingo_Brothel_room" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_2" && npchar.name == "Gabriela")
			{
				dialog.text = "Ah, você finalmente chegou! Excelente! Podemos falar à vontade, ninguém está ouvindo...";
				Link.l1 = "Então, foi o espanhol que te deu o âmbar azul?";
				Link.l1.go = "mtraxx_2";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SantoDomingo");
				break;
			}
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple("Estou muito feliz em te ver. "+GetSexPhrase("E então, o que vamos fazer agora?","Que tal a gente se divertir?")+"","Não seja tímido"+GetSexPhrase(", fique à vontade por pelo menos duas horas.",". Vou conseguir te entreter, pode ter certeza.")+"");
					Link.l1 = RandPhraseSimple("Acho que não vai ser chato...",""+GetSexPhrase("Vamos aproveitar, meu bem!","Não vamos perder tempo!")+"");
				break;
				case "1":
					dialog.text = "Oh, é você de novo, meu "+GetSexPhrase("Glorioso corsário! Eu lhe prometi algo e estou pronto para cumprir minha palavra","Moça bonita! Você nunca vai esquecer as próximas duas horas")+"...";
					Link.l1 = "Isso soa tentador...";	
				break;
				case "2":
					dialog.text = "Ah, aí está você finalmente. Vamos perder tempo não!";
					Link.l1 = ""+GetSexPhrase("Nem pense nisso, covarde...","Agora me mostre do que você é capaz...")+"";
				break;
			}
			if (pchar.sex == "woman")
			{
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex";
				AddDialogExitQuest("PlaySex_1");
				// кач от борделя
				if (CheckNPCQuestDate(pchar, "BrothelSex"))
				{
					if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	AddCharacterHealth(pchar, 10);
					else 												AddCharacterHealth(pchar, 5);
					SetNPCQuestDate(pchar, "BrothelSex");
				}
				// изменение статусов
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "FencingS", -15);
				AddCharacterExpToSkill(pchar, "Pistol", -15);
			}
			else
			{
				pchar.horsekiss = npchar.id;
				Link.l1.go = "Horse_Kiss";
			}
			//--> кол-во посещений
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
		break;
		
		case "Horse_Kiss":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("Horse_Kiss", "");
		break;

        case "Horse_AfterSex":
			if (CheckAttribute(pchar, "questTemp.ReasonToFast") && pchar.questTemp.ReasonToFast == "Begin")
			{
				dialog.text = "Capitão, por que está tão calado?";
				link.l1 = LinkRandPhrase("Bem, sou eu.","Conversamos da próxima vez.",RandPhraseSimple("Não estou te pagando para conversar.","Mas você, "+GetSexPhrase("beleza","querido")+", não ficaram tão quietos esse tempo todo."));
				link.l1.go = "exit";
				link.l2 = ""+GetSexPhrase("Você foi simplesmente incrível, quase perdi a cabeça! É raro encontrar uma mulher tão bonita e encantadora","Ah, você realmente sabe como agradar uma mulher... Estou tão animada.")+".";
				link.l2.go = "Horse_ReasonToFast_1";
			}
			else
			{
				switch(npchar.quest.choice)
				{
					case "0":
						dialog.text = LinkRandPhrase("Você gostou?","E então, o que achou? Estava tudo certo?","Então,"+GetSexPhrase(" corsário, é, tudo"," tudo")+" Tudo bem?");
						Link.l1 = RandPhraseSimple(""+GetSexPhrase("Claro, está tudo bem","Você certamente conhece bem seus deveres")+".",""+GetSexPhrase("Está tudo bem, querido","Sabe, eu fiquei bastante satisfeito")+".");
						Link.l1.go = "exit";
					break;
					case "1":
						dialog.text = LinkRandPhrase("Então, cumpri minha promessa?","Então,"+GetSexPhrase(" você gostou de mim",", gostou")+"?","Espero que sim, "+GetSexPhrase("você ficou feliz, porque eu estou mu-u-u-uito feliz","Você ficou satisfeito, porque eu dei o meu melhor")+"...");
						Link.l1 = RandPhraseSimple("Sim, eu gostei muito.",""+GetSexPhrase("Tivemos uma noite maravilhosa, você estava deslumbrante!","Foi simplesmente maravilhoso!")+"");	
						Link.l1.go = "exit";
					break;
					
					case "2":
						dialog.text = RandPhraseSimple("Bem, é isso, você tem que ir.","Seu tempo acabou,"+GetSexPhrase(" Capitão,","")+".");
						Link.l1 = RandPhraseSimple("É, até mais...","Adeus e obrigado...");
						Link.l1.go = "exit";
					break;
				}
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
        case "Horse_AfterSex_2":
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
			{
				dialog.text = "E então, o que achou daqui?";
				link.l1 = "Me diga, bela, você não viu uma valise por aqui, não?";
				link.l1.go = "EncGirl_GetBag";
			}
			else
			{
				dialog.text = LinkRandPhrase("Volte aqui outra hora...","Adeus. Estaremos esperando por você a qualquer hora...","Vamos ficar felizes em te ver aqui de novo...");
				Link.l1 = "Certo...";
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
		case "EncGirl_GetBag":
			dialog.text = "Era aquele baú marrom com uma alça?";
			link.l1 = "É, algo assim...";
			link.l1.go = "EncGirl_GetBag1";	
		break;
		
		case "EncGirl_GetBag1":
			dialog.text = "Como o dono daquele baú não apareceu, a madame levou ele para o seu quarto.";
			link.l1 = "Obrigada, querido. Adeus.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		
		// --> генератор - "A reason to hurry"
		case "Horse_ReasonToFast_1":
			dialog.text = "Então apareça quando quiser, vou ficar sempre feliz em te ver. Você é tão "+GetSexPhrase("gentil, diferente dos outros","gentil, não como aqueles brutamontes")+" sem oi, sem adeus, e muitas vezes até tentam machucar...";
			link.l1 = "O que você quer dizer com isso?";
			link.l1.go = "Horse_ReasonToFast_2";
		break;
		
		case "Horse_ReasonToFast_2":
			pchar.questTemp.ReasonToFast.speakHorse = true;
			dialog.text = "Teve um sargento-mor aqui pouco antes de você. Normalmente ele não aparece por aqui, mas dessa vez algum diabo trouxe ele até nós. E ainda por cima, ele me escolheu... Ficou resmungando comigo por alguns minutos, depois me chamou de incompetente e saiu correndo pra alguma enseada. Foi tão rápido que quase esqueceu as calças lá embaixo, ha-ha-ha...";
			link.l1 = "Você não sabe, "+GetSexPhrase("beleza","querida")+", quem são os homens de verdade? Ele disse à esposa que ia ao bordel para uma 'inspeção', depois contou à amante que estava correndo de volta para a esposa, mas a única coisa que ele realmente queria era patrulhar aquela enseada. "+GetSexPhrase("Ha-ha-ah!..","Ha-ha-ha!")+"";
			link.l1.go = "Horse_ReasonToFast_3";
		break;
		
		case "Horse_ReasonToFast_3":
			NextDiag.TempNode = "Horse_AfterSex_2";			
			ReOpenQuestHeader("ReasonToFast");
			AddQuestRecord("ReasonToFast", "1");
			pchar.questTemp.ReasonToFast = "SpeakHorse";
			pchar.questTemp.ReasonToFast.GuardNation = npchar.nation;
			pchar.questTemp.ReasonToFast.cantSpeakOther = true;
			ReasonToFast_InitVariables();
			string TargetLocation = SelectQuestShoreLocation();
			if(TargetLocation != "")
			{ 
				Locations[FindLocation(TargetLocation)].DisableEncounters = true;
				LAi_LocationDisableOfficersGen(TargetLocation, true);
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1 = "location";
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1.location = TargetLocation;
				pchar.quest.ReasonToFast_MeetPatrol.function = "ReasonToFast_MeetPatrolShore";
				pchar.questTemp.ReasonToFast.PatrolLocation = TargetLocation;
			}	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		// <-- генератор "A reason to hurry"
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//поиски кольца мэра
		case "TakeMayorsRing_S1":
			if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) //если валяется в итемах
			{
				dialog.text = LinkRandPhrase("Não, querido, desculpe, mas não. Eu adoraria te ajudar, mas não posso.","Não, "+GetSexPhrase("bonito","moça")+", eu não vi nenhum anel...","Desculpe, mas não. Não vi nenhum anel.");
				link.l1 = "Que pena... Bem, obrigado mesmo assim.";
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_"+reload_location_index+"_1")
				{
					dialog.text = "Você está falando do anel do governador?";
					link.l1 = "Exatamente, querido!";
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = LinkRandPhrase("Não, querido, desculpe, mas não. Eu adoraria te ajudar – mas não posso.","Não, "+GetSexPhrase("bonito","moça")+", eu não vi nenhum anel...","Desculpe, mas não. Não vi nenhum anel.");
					link.l1 = "Pena... Bem, obrigado mesmo assim.";
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = "Sinto muito, mas o anel foi me dado de presente, então não sou obrigado a devolvê-lo.";
			link.l1 = "Um presente?! E quem foi que te deu?";
			link.l1.go = "TakeMayorsRing_S3";
		break;
		
		case "TakeMayorsRing_S3":
			dialog.text = "O próprio governador, é claro!";
			link.l1 = "Mas ele estava... digamos, meio bêbado. Não lembra de nada.";
			link.l1.go = "TakeMayorsRing_S4";
		break;
		
		case "TakeMayorsRing_S4":
			dialog.text = "E o que isso tem a ver comigo? Se ele estava bêbado, o problema é dele, não meu!";
			link.l1 = "Você realmente precisa brigar com ele? É uma aliança de casamento, e você sabe disso... Só devolva, uma coisa tão pequena não vale a pena causar confusão.";
			link.l1.go = "TakeMayorsRing_S5";
		break;
		
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money)>5000)
			{
				dialog.text = "Tá bom, eu devolvo o anel, mas você vai me pagar cinco mil pesos.";
				link.l1 = "Tá bom, pega seu dinheiro e me dá o anel.";
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = "Ah, tudo bem. Deixa ele ficar com isso!";
				link.l1 = "Com certeza, querido!";
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		
		case "TakeMayorsRing_S6":
			dialog.text = "Aqui está...";
			link.l1 = "Tudo bem, então. Obrigado pela ajuda, querida.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000);
			GiveItem2Character(pchar, "MayorsRing");
			pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
			AddQuestRecord("SeekMayorsRing", "2");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		break;
		
		//Jason --> Заносчивый аристократ
		case "Badboy":
			pchar.GenQuest.Badboy.Brothel.City = npchar.city; //город квестодателя
			//log_info(pchar.GenQuest.Badboy.Brothel.City); // patch-6
			pchar.GenQuest.Badboy.Brothel.nation = npchar.nation;
			pchar.GenQuest.Badboy.Brothel.Name = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "Veja, tem um cliente problemático que temos - "+pchar.GenQuest.Badboy.Brothel.Name+". E ele realmente nos irrita toda vez que aparece! Primeiro ele fica bêbado na taverna, depois vem aqui, arruma uma moça e causa a maior confusão violenta\nE o pior é que ele é de família nobre! É um parente distante do nosso governador, então somos obrigados a aguentar todas as loucuras dele. Talvez você pudesse fazer esse jovem atrevido... bem... se acalmar um pouco... para que ele pare de frequentar meu estabelecimento?";
			link.l1 = "Parente do governador, é? Hmmm... Prefiro não me meter em confusão com as autoridades. Me desculpe mesmo.";
			link.l1.go = "exit";
			link.l2 = "Acho que posso dar um jeito nisso. Diga, onde posso encontrar esse desordeiro?";
			link.l2.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "Nessa hora, ele geralmente já está na taverna. Ele bebe por lá e depois aparece para visitar.";
			link.l1 = "Entendi. Bem, provavelmente vou encontrá-lo lá.";
			link.l1.go = "exit";
			//создаем дебошира
			int iRank, iType, b;
			string sBlade, sPistol;
			if (sti(pchar.rank) < 6) iType = 0;
			if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 16) iType = 1;
			if (sti(pchar.rank) >= 16) iType = 2;
			switch (iType)
			{
				case 0:
					iRank = 6;
					sBlade = "blade_12";
					sPistol = "pistol1";
					b = 25;
				break;
				case 1:
					iRank = sti(pchar.rank)+10;
					sBlade = "blade_09";
					sPistol = "pistol1";
					b = 65;
				break;
				case 2:
					iRank = sti(pchar.rank)+5;
					sBlade = "blade_14";
					sPistol = "pistol1";
					b = 40;
				break;
			}
			sld = GetCharacter(NPC_GenerateCharacter("Badboy", "citiz_"+(7+rand(1)), "man", "man", iRank, HOLLAND, -1, true, "citizen"));
			FantomMakeCoolFighter(sld, iRank, b, b, sBlade, sPistol, "bullet", makeint(iRank*5));
			sld.name = pchar.GenQuest.Badboy.Brothel.Name;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Badboy";
			sld.greeting = "noble_male"; // patch-6
			LAi_SetLoginTime(sld, 15, 22);
			LAi_SetSitType(sld);
			FreeSitLocator(pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit", "sit1");
			pchar.GenQuest.Badboy.Brothel.Type = iType; //запомним тип
			pchar.GenQuest.Badboy.Brothel = "true";
		break;
		
		case "Badboy_complete":
			dialog.text = "Ah, você é mesmo um homem de verdade, não é? Sempre soube que podia contar com você.";
			link.l1 = "Sempre fico feliz em ajudar uma dama tão encantadora e seus... protegidos.";
			link.l1.go = "Badboy_complete_1";
		break;
		
		case "Badboy_complete_1":
			dialog.text = "Você não é apenas corajoso, mas também muito galante. Gostaria de te agradecer de um jeito especial – de um jeito que só uma mulher pode agradecer a um homem. Você nunca vai esquecer isso, eu prometo. Venha comigo lá para cima, bravo marinheiro...";
			link.l1 = "...";
			link.l1.go = "Badboy_complete_2";
		break;
		
		case "Badboy_complete_2":
			pchar.questTemp.different.HostessSex.city = pchar.GenQuest.Badboy.Brothel.City;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); 
			DialogExit();
			if (sti(pchar.GenQuest.Badboy.Brothel.Type) != 2)
			{
				DeleteAttribute(pchar, "GenQuest.Badboy");
			}
			else
			{
				pchar.quest.Badboy_Brothel.win_condition.l1 = "location";
				pchar.quest.Badboy_Brothel.win_condition.l1.location = pchar.GenQuest.Badboy.Brothel.City +"_town";
				pchar.quest.Badboy_Brothel.function = "Badboy_friends";
				DeleteAttribute(pchar, "GenQuest.Badboy.Continue"); // patch-6
			}
			SaveCurrentQuestDateParam("questTemp.Badboy");
			if (!CheckAttribute(pchar, "questTemp.RomNaTroih"))
			{
				pchar.questTemp.RomNaTroih = true;
			}
		break;
		// <-- Заносчивый аристократ
		
		//Португалец
		case "Portugal":
			dialog.text = "Tem um homem que me deve um dinheiro... Eu não sei como dizer...";
			link.l1 = "Nem precisa dizer nada! Vou encontrar esse sujeito e arrancar até o último peso dele, só para ter o privilégio de olhar nos seus olhos profundos! Só me diga o nome dele!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Não, não, você não me entendeu direito, Capitão! Esse homem... não faça nada de ruim com ele. Só lembre ele das dívidas. O nome dele é Hugo Avendell, e acho que você vai encontrá-lo onde venderem a bebida mais barata. Pelo amor de Deus, não use a força com ele!\nSó diga... lembre ele que prometeu pagar. Eu não quero envolver a guarda, mas tenho amigos entre os oficiais, então diga que estou esperando, e com todo respeito a ele, vou ser obrigado a agir até amanhã. Só lembre ele da promessa.";
			link.l1 = "Sua palavra é minha lei, senhora. Cumprirei seu pedido com prazer.";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			sld = InitHugo("Hugo","Avendell");
			FreeSitLocator("Marigo_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, "Marigo_tavern", "sit", "sit_front1");
			AddLandQuestMark(sld, "questmarkmain");
			SetFunctionTimerCondition("Portugal_BeginOver", 0, 0, 2, false);
			pchar.questTemp.Portugal = "begin";
		break;
		
		case "Portugal_exit":
			dialog.text = "Obrigada, capitão. Espero mesmo que ele tenha o devido juízo.";
			link.l1 = "Tenho certeza disso, senhora. Agora permita-me me retirar.";
			link.l1.go = "exit";
			sld = characterFromId("Avendel");
			sld.lifeday = 0;
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "Ah não! Não me diga que você fez algo terrível com ele... Ele não tinha dinheiro, eu sabia disso! Só crescemos juntos na mesma cidade pequena, eu nunca teria chamado os guardas! Só queria dar um susto nele... sacudi-lo um pouco antes que ele se afundasse de vez na bebida!";
			link.l1 = "Hum... De qualquer forma, aqui está seu dinheiro. E não se preocupe com o Hugo, ele está bem... Pelo menos vai estar, se conseguir ficar sóbrio.";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "Oh, Capitão, você não entende! Ele era um daqueles... bem, você sabe, caçadores de recompensas - mercenários, eles caçam piratas e ladrões e acabam com eles. Mas ele não foi dos mais sortudos, pra dizer o mínimo\nNão faz muito tempo, ele finalmente se empolgou e perdeu a tripulação e o navio, e desde então está afundando no fundo do copo, dia após dia. Por amizade antiga, deixo ele vir aqui de vez em quando. Ele está tão... tão lamentável agora. Ele já foi o homem mais bonito da nossa cidadezinha na costa da Mancha, e olha pra ele agora\nEu sei que ele te prometeu algo, e você pagou do seu próprio bolso! Eu te dou esse dinheiro, só não faça nada ruim com ele, por favor, capitão!";
			link.l1 = "Certo, tudo bem, senhora, entendi. Fique com o dinheiro, é seu. Quanto ao seu amigo, prometo que não vou machucá-lo. Agora, permita-me ir embora, tenho assuntos a tratar. E, além disso, foi um prazer ajudar uma dama tão bonita.";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_tavern_7";
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Portugal = "AvendelTavern";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "Shhh, fala mais baixo... Vai lá pedir pra Madame Lolita sair comigo. Depois sobe, aí a gente pode conversar à vontade. E nem uma palavra até lá... Ei, marinheiro, vai pagar a Madame antes de encostar em mim! (risos)";
			link.l1 = "Já estou indo, querida...";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
           DialogExit();
		   chrDisableReloadToLocation = false;
		   pchar.questTemp.Mtraxx = "jewelry_2";
		break;
		
		case "mtraxx_2":
			pchar.quest.Mtraxx_JewelrySDMOver.over = "yes"; //снять таймер
            dialog.text = "Não, eu não. Vou te contar toda a história, só não me interrompa.";
			link.l1 = "Estou ouvindo!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Certo então. Cerca de uma semana atrás, um navio militar chegou a Santo Domingo. Estava avariado, seja por uma tempestade ou uma briga, então os reparos começaram imediatamente e a tripulação foi para o forte. O capitão, no entanto, passou todo o tempo livre aqui mesmo. Dois dias seguidos bebendo e descansando, sempre acompanhado de uma das nossas garotas. Foi ela quem ganhou a pedra preciosa, e não só uma. Ficou se gabando disso sem parar – Lolita deixa a gente ficar com os presentes dos clientes.\nA tolinha nem sabia o verdadeiro valor do presente, mas eu percebi na hora. Quando ela me contou como o capitão bêbado se gabava de uma montanha cheia de âmbar, tratei logo de mandar uma carta para Tyrex...";
			link.l1 = "";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "Na próxima vez que o capitão apareceu, eu já tinha tudo preparado: a garota preferida dele estava ocupada com outro cliente, então fiquei com o 'serviço' para mim. Tentei arrancar as coordenadas dele, mas foi em vão. Ele só ficava se gabando de que ficaria tão rico quanto Crasso e voltaria para o Velho Mundo\nNão disse uma palavra sequer sobre o local. Só descobri que o navio dele tinha sido consertado e estava prestes a zarpar para Havana, onde tentaria conseguir uma missão na direção certa. Afinal, ele nem é o dono do navio.";
			link.l1 = "Então, ele está em Havana agora?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "Zarpou há dois dias ao amanhecer. Você é o marinheiro aqui, faça as contas.";
			link.l1 = "Nome do capitão, tipo e nome do navio, alguma coisa?";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            dialog.text = "O quê, você me acha um idiota? O nome dele é Esberdo Cabanas, capitão do Cantavro. Acho que os marinheiros chamavam de escuna.";
			link.l1 = "E é só isso que você sabe?";
			link.l1.go = "mtraxx_7";
		break;
		
		case "mtraxx_7":
            dialog.text = "O que mais você quer? Tenho certeza de que ainda dá tempo de alcançá-lo antes de Havana. Mas não perca tempo, não acho que ele vá descansar muito antes de sair de Cuba para pegar o tesouro, e aí já era. Pensando bem, pode ficar aqui por uma ou duas horas, afinal, você pagou por isso.";
			link.l1 = "Bem pensado, querida. Duas horas não vão fazer muita diferença...";
			// belamour legendary edition -->
			link.l1.go = "mtraxx_7S";
			link.l2 = "Outra hora, querido. Pense em tirar uma pausa para o almoço. Vá à igreja, ou faça outra coisa.";
			link.l2.go = "mtraxx_7NS";
			sTotalTemp = npchar.id;
			AddMapQuestMarkCity("Havana", false);
			AddLandQuestMark(characterFromId("Havana_PortMan"), "questmarkmain");
		break;
		
		case "mtraxx_7S":
            DialogExit();
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			AddDialogExitQuest("PlaySex_1");
			// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
				{
					AddCharacterHealth(pchar, 10);
					AddCharacterMaxHealth(pchar, 1.0);
				}
				else AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "FencingS", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;
		
		case "mtraxx_7NS":
            DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			AddQuestRecord("Roger_1", "3");
			pchar.questTemp.Mtraxx = "jewelry_3";
			SetFunctionTimerCondition("Mtraxx_JewelryHavanaOver", 0, 0, 7, false); // таймер
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			pchar.quest.mtr_jewelry_havana.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_havana.win_condition.l1.location = "Cuba2";
			pchar.quest.mtr_jewelry_havana.function = "Mtraxx_HavanaInfo";
			DeleteAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor");
			DeleteAttribute(pchar, "questTemp.ZA.Block");
		break;
		// <-- legendary edition
		case "mtraxx_R":
            dialog.text = "O-oh... Que pena. E eu pensei que você estivesse aqui de férias. Minhas meninas sentem tanta falta de corsários valentes. Muito bem, diga, qual é a tarefa?..";
			link.l1 = "Marcus me encarregou de fazer uma baita festa no seu estabelecimento por dois dias, beber todo o vinho e aproveitar com todas as garotas. Quando começamos?";
			link.l1.go = "mtraxx_R1";
		break;
		
		case "mtraxx_R1":
            dialog.text = "Ah, Charlie Prince, seu humor é tão afiado quanto seu sabre! Você quase conseguiu me irritar... Meninas! Temos uma visita, uma visita especial! Tragam vinho e comida!";
			if (sti(pchar.money) >= 31000)
			{
				link.l1 = "Chame todas as moças bonitas daqui! Vamos descansar e nos divertir! Yo-ho-ho!..";
				link.l1.go = "mtraxx_R2";
			}
			else
			{
				link.l1 = "Espere um pouco, Janette. Preciso buscar o ouro no meu navio para você e suas damas. Já volto!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.Retribution = "brothel_repeat";
				chrDisableReloadToLocation = false;
			}
		break;
		
		case "mtraxx_R2":
			AddMoneyToCharacter(pchar, -30000);
            dialog.text = "Queria que todos os nossos clientes fossem tão doces, bonitos e generosos quanto você... Vamos te dar um relaxamento perfeito. Meninas!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionInBrothel");
		break;
		// belamour ночной приключенец
		case "NA_Girl":
            dialog.text = "Oh, então temos um conhecedor aqui, hee hee ... Muito bem, eu tenho a garota certa. Mas ela não sai barato: "+makeint(pchar.GenQuest.NightAdventure_money)+" pesos."; 
			link.l1 = "Fechado.";
			link.l1.go = "NA_Girl_1";
		break;
		
		case "NA_Girl_1":
			AddMoneyToCharacter(pchar, -makeint(pchar.GenQuest.NightAdventure_money));
            dialog.text = "Que ótimo, querido. A Sacerdotisa do Amor estará te esperando lá em cima. Confie em mim, você não vai se arrepender."; 
			link.l1 = "Eu já não quero.";
			link.l1.go = "NA_Girl_2";
		break;
		
		case "NA_Girl_2":
			DialogExit();
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhore"; 
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_NobleWhore_7";
		break;
		// <-- приключенец
		
		case "chicken_god":
			dialog.text = "Para você e o senhor Agüeybana? Claro que sim. Isso vai custar dez mil, capitão.";
			if (sti(pchar.money) >= 10000) {
				link.l1 = "Espera, não assim!.. Droga! Tanto faz, aqui está o pagamento.";
				link.l1.go = "chicken_god_pay";
			} else {
				link.l2 = "Posso conseguir um empréstimo?";
				link.l2.go = "chicken_god_notpay";
			}
		break;
		
		case "chicken_god_pay":
			dialog.text = "Aproveite sua estadia, capitão. Volte sempre que estivermos abertos. Nosso estabelecimento oferece todo tipo de lazer para nobres cavalheiros e damas.";
			link.l1 = "...";
			link.l1.go = "chicken_god_pay_1";
		break;
		
		case "chicken_god_pay_1":
			dialog.text = "";
			link.l1 = "Madame "+npchar.name+", pelo menos pode me explicar o que está acontecendo aqui? O governador ao menos sabe que você deixou um nativo no comando por um mês? Nenhuma colônia sobrevive com o bordel fechado nem por um dia, pode acreditar!";
			link.l1.go = "chicken_god_pay_2";
		break;
		
		case "chicken_god_pay_2":
			dialog.text = "O quarto é seu, capitão. Agora, com licença.";
			link.l1 = "Encantadora. Adeus, senhora.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_PayForRoom");
		break;
		
		case "chicken_god_notpay":
			dialog.text = "Por quê, meu Deus, por quê? Sai daqui! Vai embora, vai embora, eu não aguento mais! Desgraçado!";
			link.l1 = "Isso correu bem.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotPayForRoom");
		break;
		
		//-->> Sinistra Ром на троих
		case "RomNaTroih_1":
			dialog.text = "Mhm... Eu não costumo fazer isso... mas estou disposto a arriscar por você. Hoje é seu dia de sorte, Capitão!";
			link.l1 = "Vamos!";
			link.l1.go = "exit";
			pchar.RomNaTroih_Shluha = npchar.id;
		break;
		
		case "RomNaTroih_2":
			dialog.text = "Estou irritado com você, Capitão... Mas vou mostrar misericórdia se você se esforçar o bastante para merecê-la.";
			link.l1 = "Ah, vou sim. Que tal abrirmos um vinho?";
			link.l1.go = "exit";
			Achievment_Set("ach_CL_105");
		break;
		//<<-- Sinistra Ром на троих
	}
}

ref GetFreeHorseRef(string City)
{
	ref rCharacter;
    int storeArray[8];
	int howStore = 0;
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse" && rCharacter.horse == "HorseStay")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return &NullCharacter;
	return &characters[storeArray[rand(howStore-1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;			
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
		}
	}
	return &NullCharacter;
}
