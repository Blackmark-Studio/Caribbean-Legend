// диалог коменданта форта
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
   /*NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}*/
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "First time":
			location = &Locations[FindLocation(pchar.location)];
			if (rand(4) == 4 && GetNpcQuestPastDayParam(location, "gun_date") > 365 && !CheckAttribute(pchar, "questTemp.PrisonGun"))
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Escute, tenho um assunto importante para tratar com você. Espero mesmo que possa me ajudar.","Capitão, posso lhe interessar com uma oferta bastante lucrativa?"),RandPhraseSimple("Acho que você poderia nos ajudar com um assunto importante.","Capitão, tenho uma proposta delicada para você, que pode ser bastante lucrativa para nós dois."));					
				link.l1 = "Bem, diga o que pensa, e veremos...";
				link.l1.go = "GiveTaskGun";
				location.quest.PrisonGun = "Target"; 
				SaveCurrentNpcQuestDateParam(location, "gun_date");
				break;
			}
		
			dialog.text = RandPhraseSimple("Eu sou o comandante do forte. O que você precisa aqui?","O que você precisa? Por que veio aqui?");
			link.l1 = "Ah, nada não, só estou dando uma olhada pela cidade e arredores. Vim parar aqui totalmente por acaso.";
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "Bem-vindo ao forte, capitão. Precisa de alguma coisa?";
				link.l1 = "Não, nada, só passei aqui por acaso.";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Saudações, Vice-Almirante! Tem alguma ordem?";
				link.l1 = "Não, oficial, nenhuma ordem. Só vim ver o forte.";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Governador Geral, Vossa Graça! O forte está em perfeita ordem. Tem alguma ordem?";
				link.l1 = "Que bom que você está bem, oficial. Não vim com ordens, só passei para ver como está o forte.";
			}
			// <-- legendary edition
			link.l1.go = "exit";
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_ammo" && GetQuestPastDayParam("questTemp.Wine_bottle") < 5)
			{
				link.l11 = "Tenho uma informação interessante para você, oficial. Um dos seus soldados, "+pchar.questTemp.Wine.SName+" me pediu para comprar vinho na cidade através da minha mediação. Considerando suas ordens...";
				link.l11.go = "Wine_prison";
			}
			// <-- мини-квест Дефицитный товар
			// Карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "fraht" && NPChar.location == "portpax_ammo")
			{
				link.l11 = "Olá, oficial. Venho da colônia de Basse-Terre, a mando de um homem chamado Gerard LeCroix. Tenho um carregamento de pólvora e bombas para você no meu porão...";
				link.l11.go = "trial";
			}
			// Опасный груз -->
			if (pchar.location == "Cumana_Ammo")
			{
				if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
				{
					link.l2 = "Você parece preocupado, oficial. Como posso ajudar?";
					link.l2.go = "zpq_prs1";
				}
				if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 15000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
				{
					link.l3 = "Estou pronto para informar que toda a carga de pólvora foi entregue. Meu navio está pronto para o descarregamento.";
					link.l3.go = "zpq_ex";
				}
				if (pchar.questTemp.zpq == "begin")
				{
					link.l4 = "Quero cancelar nosso acordo de pólvora. Isso está dando trabalho demais.";
					link.l4.go = "zpq_fld2";
				}
			}
			// <-- Опасный груз
			NextDiag.TempNode = "First time";
		break;

		// --> Орудия для форта
		case "GiveTaskGun":
			dialog.Text = LinkRandPhrase("Veja, os canhões do forte estão bem desgastados. O tesouro destinou verbas para substituí-los, mas eu simplesmente não faço ideia de onde comprar novos: não há como encontrá-los em nossa colônia na quantidade necessária. Então, pensei que os canhões dos navios que você abordou poderiam ser muito úteis para nós aqui.","Preciso substituir a bateria de canhões do forte. Os fundos já foram destinados, mas, sabe como é... É simplesmente impossível comprar a quantidade necessária aqui na nossa colônia.","Me deram a tarefa de substituir os canhões gastos do forte, mas simplesmente não consigo encontrar o suficiente em lugar nenhum.");
			Link.l1 = "Hum... Você poderia entrar em mais detalhes? Calibre, quantidade, preço?";
			Link.l1.go = "GiveTaskGun_1";
			pchar.questTemp.PrisonGun = true;
			SaveCurrentQuestDateParam("pchar.questTemp.PrisonGun");
		break;
			
		case "GiveTaskGun_1":
			GetGunType();
			pchar.questTemp.PrisonGun.Sum = makeint(sti(pchar.questTemp.PrisonGun.Price)*sti(pchar.questTemp.PrisonGun.Qty));
			pchar.questTemp.PrisonGun.Luck = rand(4);
			pchar.questTemp.PrisonGun.Id = npchar.location;
			dialog.Text = "Eu preciso "+pchar.questTemp.PrisonGun.Text+", no valor de "+sti(pchar.questTemp.PrisonGun.Qty)+"  unidades exatamente. Vou pagar em dobrões de ouro, "+sti(pchar.questTemp.PrisonGun.Price)+" por peça. Isso vai dar "+FindRussianDublonString(sti(pchar.questTemp.PrisonGun.Sum))+" no total. O que me diz? Ah, e mais uma coisa – eu vou ficar com todo o lote, mas só depois de um mês – o dinheiro ainda não chegou.";
			Link.l1 = RandPhraseSimple("Não, oficial, sua oferta não me interessa nem um pouco... Me desculpe.","É tentador, mas acho que vou recusar. Permita-me guardar meus motivos para mim mesmo.");
			Link.l1.go = "exit_gun";
			Link.l2 = RandPhraseSimple("Bem, essa proposta é realmente interessante. Considere fechado o acordo.","Acho que vou aceitar. Não parece tão difícil e claramente é lucrativo.");
			Link.l2.go = "GiveTaskGun_2";
		break;
			
		case "exit_gun":
			dialog.Text = "Que pena, capitão, eu estava contando com você. E... espero mesmo que esta conversa fique só entre nós, dentro do forte?";
			Link.l1 = "Não precisa me lembrar disso. Um abraço.";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
			
		case "GiveTaskGun_2":
			dialog.Text = "Então, está combinado! Não vou impor condições específicas, mas, por favor, tente não estender isso por mais de meio ano. E espero que entenda que isso é absolutamente confidencial?";
			Link.l1 = "Claro que sim. Até mais, Comandante.";
			Link.l1.go = "exit";
			ReOpenQuestHeader("PrisonGun");
			AddQuestRecord("PrisonGun", "1");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			AddQuestUserData("PrisonGun", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("PrisonGun", "sQty", makeint(pchar.questTemp.PrisonGun.Qty));
			AddQuestUserData("PrisonGun", "sSum", makeint(pchar.questTemp.PrisonGun.Sum));
			AddQuestUserData("PrisonGun", "sText", pchar.questTemp.PrisonGun.Text);
			NextDiag.TempNode = "First time";
		break;	
		
		case "CheckGun":
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") < 30)
			{
				dialog.Text = "Eu te disse para não voltar antes de passar um mês!";
				Link.l1 = "Droga! Eu estava tão ocupado"+GetSexPhrase("","")+", que eu perdi um "+GetSexPhrase("","")+" perdi a noção do tempo ... Desculpe, volto mais tarde, como combinado.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				break;
			}
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") > 180)
			{
				dialog.Text = "Hum... Sabe, já faz mais de meio ano desde o dia em que fechamos nosso 'acordo'. Eu já comprei os canhões. Você achou mesmo que eu ia ficar esperando por você para sempre?";
				Link.l1 = "Droga! E o que eu faço com eles agora?";
				Link.l1.go = "TakeGun_late";
				break;
			}
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = GetSquadronGoods(Pchar, iGunGoods) - sti(pchar.questTemp.PrisonGun.Qty);
			sTemp = sti(pchar.questTemp.PrisonGun.Qty);
			iTest = FindColony(NPChar.City); // город
			
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.Text = "Sim, você está pronto para me ajudar?";
				if (amount < 0)
				{
					Link.l1 = "Não, ainda estou trabalhando nisso. Só queria ter certeza de que nosso acordo continua de pé.";
					Link.l1.go = "exit";
				}
				else
				{
					Link.l1 = "Sou eu. Todo o carregamento está no porão - "+sTemp+" unidades, conforme combinado.";
					Link.l1.go = "TakeGun";
				}
			}
			else 
			{
				dialog.text = "Não vejo seu navio no porto. Você está sugerindo que arrastemos esses canhões pela selva? Vá logo até o nosso porto e volte.";
				link.l1 = "Meu navio está do outro lado da ilha. Vou trazê-lo para o porto.";
				link.l1.go = "exit";
			}
		break;
		
		case "TakeGun":
			if (pchar.questTemp.PrisonGun.Luck == 4)
			{
				dialog.Text = RandPhraseSimple("Sabe, é meio constrangedor, mas vou ter que desistir do nosso acordo. Acabamos de passar por uma inspeção financeira, e você sabe como eles são rigorosos com essas coisas. Não posso fazer nada. Desculpe.","Capitão, sabe... Bem, mandaram canhões pra cá da metrópole, e eu fui obrigado a comprá-los, claro. Preços absurdos, mas... Sinto muito mesmo por ter te decepcionado... Também não me sinto bem com isso.");
				Link.l1 = "Droga! E o que eu faço com eles agora?";
				Link.l1.go = "TakeGun_no";
			}
			else
			{
				dialog.Text = RandPhraseSimple("Excelente. Vou enviar um grupo da guarnição para descarregá-los.","Excelente. Meus soldados vão te ajudar a descarregar os canhões.");
				Link.l1 = "Você preparou o pagamento?";
				Link.l1.go = "TakeGun_1";
			}
		break;
		
		case "TakeGun_no":
			dialog.Text = "Eu não sei. Venda no estaleiro, equipe um navio mercante, afunde tudo... Sinceramente, não faço ideia. E por favor, não conte a ninguém sobre esse acordo.";
			Link.l1 = "Ah, é mesmo! Fiquei até sem palavras!";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "3");
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_late":
			dialog.Text = "Não faço ideia. O problema é seu. Venda, jogue fora, afunde – tanto faz pra mim.";
			Link.l1 = "Ah, isso foi simplesmente uma perda de tempo...";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "4");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_1":
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = sti(pchar.questTemp.PrisonGun.Qty);
			iTemp = sti(pchar.questTemp.PrisonGun.Sum);
			dialog.Text = "Claro. Aqui está seu ouro - fique à vontade.";
			Link.l1 = "Muito obrigado! Foi um prazer fazer negócios com você!";
            Link.l1.go = "TakeGun_2";
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(sti(pchar.questTemp.WPU.Escort.Money))+"");
			PlaySound("interface\important_item.wav");
			RemoveCharacterGoods(Pchar, iGunGoods, amount);
		break;
		
		case "TakeGun_2":
			dialog.Text = "O sentimento é mútuo. Você foi de grande ajuda. E, por favor, mantenha este acordo entre estas quatro paredes.";
			Link.l1 = "Claro. Tudo de bom pra você.";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "2");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		// <-- орудия для форта

		//Jason --> мини-квест Дефицитный товар
		case "Wine_prison":
			dialog.text = "O quê?! Eu proibi terminantemente qualquer bebida dentro do forte! Pois bem, ele vai ter que pagar por isso. Vou descontar 1000 pesos do pagamento dele e entregar para você como recompensa pela sua vigilância. E esse homem vai passar três dias detido.";
			link.l1 = "Obrigado, "+GetAddress_FormToNPC(NPChar)+". Impedir tais violações é nosso dever compartilhado.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 1000);
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			pchar.quest.Wine_Exchange.over = "yes";//снять прерывание
			pchar.quest.WineTraderQM.over = "yes";//снять прерывание
			WineTraderQMDel();
			sld = characterFromId(pchar.questTemp.Wine.id);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			NextDiag.TempNode = "First time";
		break;
		// <-- мини-квест Дефицитный товар
		
		// Карибские нравы
		case "trial":
			iTest = FindColony(NPChar.City); // город
			QuestPointerDelLoc("portpax_town", "reload", "gate_back");
			QuestPointerDelLoc("portpax_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("portpax_fort", "reload", "reload2");
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetSquadronGoods(pchar, GOOD_BOMBS) < 2500 || GetSquadronGoods(pchar, GOOD_POWDER) < 2500)
				{
					dialog.text = "Hum. Mas este lote não está cheio! Como isso aconteceu?";
					link.l1 = "Droga! Por favor, me perdoe, a culpa foi minha. Vou imediatamente comprar o que falta e entregar todo o lote para você, como combinamos.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Então você é o nosso mensageiro? Certo. Vamos resolver as coisas com a carga, e depois você receberá mais instruções.";
					link.l1 = "Certo.";
					link.l1.go = "trial_1";
				}
			}
			else
			{
				dialog.text = "Não vejo seu navio no porto. Você está sugerindo que arrastemos a carga pela selva? Vá logo até o nosso porto e volte.";
				link.l1 = "Meu navio está do outro lado da ilha. Vou trazê-lo para o porto.";
				link.l1.go = "exit";
			}
		break;
		
		case "trial_1":
			if(!bImCasual) pchar.quest.Trial_FrahtFail.over = "yes"; // belamour legendary edition если был - снять таймер
			dialog.text = "Certo, bombas e pólvora, 2.500 unidades de cada... Muito bem. Os soldados vão descarregar a carga, seus homens podem descansar um pouco. Aqui está o pagamento pelo frete – cinco mil pesos.";
			link.l1 = "Obrigado! O que devo fazer agora? O Monsieur LeCroix disse...";
			link.l1.go = "trial_2";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_2":
			AddMoneyToCharacter(pchar, 5000);
			RemoveCharacterGoods(pchar, GOOD_BOMBS, 2500);
			RemoveCharacterGoods(pchar, GOOD_POWDER, 2500);
			dialog.text = "Sim, sim, você vai receber suas instruções agora. Está pronto para prestar atenção?";
			link.l1 = "Claro, oficial.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "So, our military ship 'Warlike' is cruising near the Spanish colony Porto Bello, in the southern part of the Spanish Main. This vessel is under the command of Florian Shoke, who is preparing an ambush of a Spanish heavy galleon set to leave Porto Bello in two weeks.\nThe problem is that our frigate's cannons are suffering from a casting defect, and we need to replace fifteen cannons to save the mission; otherwise, the galleon will outnumber 'Warlike' in both guns and men. \nWithout the replacement, Florian Shoke will be forced to sail away with no result. Such a sequence of events is highly undesirable. Your task is to save the mission by delivering fifteen cannons within fourteen days.";
			link.l1 = "Então, preciso embarcar quinze canhões, seguir para Portobello, procurar a fragata 'Militant' e entregar os canhões ao capitão Florian Shoke?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "Exatamente. Você entendeu direitinho. Está pronto para assumir essa missão?";
			link.l1 = "E quanto ao pagamento?";
			link.l1.go = "trial_5";
			link.l2 = "Me desculpe, oficial, mas eu realmente não quero me envolver. Por favor, me desculpe.";
			link.l2.go = "trial_exit";
		break;
		
		case "trial_exit":
			dialog.text = "Você está no seu direito, mas eu contava com o seu acordo. Agora vou ter que encontrar outro mensageiro, embora eu não tenha muito tempo... Bem, não vou tomar mais do seu tempo, capitão.";
			link.l1 = "Atenciosamente.";
			link.l1.go = "trial_exit_1";
		break;
		
		case "trial_exit_1":
			DialogExit();
			AddQuestRecord("Trial", "6");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "trial_5":
			dialog.text = "Não se preocupe com isso. Florian Shoke vai te pagar duzentos dobrões de ouro do tesouro do navio. Além disso, tenho certeza de que ele vai querer usar você e seu navio para os próprios objetivos dele — com o seu consentimento, é claro.";
			link.l1 = "Beleza, estou nessa missão! Onde estão os canhões?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "Vou dar ordens aos soldados para carregarem eles no seu navio imediatamente. Zarpe assim que puder, monsieur! Boa sorte!";
			link.l1 = "Obrigado. Sorte nunca é demais, e um vento favorável também não...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			DialogExit();
			AddQuestRecord("Trial", "7");
			pchar.questTemp.Trial = "cannon";
			// belamour legendary edition
			if(!bImCasual) SetFunctionTimerCondition("Trial_CannonFail", 0, 0, 21, false); 
			else NewGameTip("Exploration mode: timer is disabled.");
			SetCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24)+15);
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				EnemyNationHunterOnMap(true);//запуск перехватчиков
			}
			pchar.quest.Trial_cannon.win_condition.l1 = "location";
			pchar.quest.Trial_cannon.win_condition.l1.location = "Portobello";
			pchar.quest.Trial_cannon.function = "Trial_CreateFlorianFrigate";
			// Sinistra - квест "Встреча с Диего"
			bDisableFastReload = true;
			PChar.quest.VsD_GiumDyubua.win_condition.l1 = "location";
			PChar.quest.VsD_GiumDyubua.win_condition.l1.location = "PortPax_Fort";
			PChar.quest.VsD_GiumDyubua.win_condition = "VsD_GiumDyubua";
			AddMapQuestMarkShore("Shore47", false);
		break;
		
		// Опасный груз -->
		case "zpq_prs1":
			if(!isBadReputation(pchar, 70))
			{
				dialog.text = "Hm, talvez. Bem, por causa da sua boa reputação, vou arriscar e confiar em você. Caso contrário, eu nem discutiria isso com você. A questão é que precisamos de uma carga especial bem grande, então você vai precisar de um navio de porte e disposição para correr riscos. Além disso, preciso que me prometa não contar isso a ninguém.\nSe isso te incomodar, diga agora. Acho que fui claro...";
				link.l1 = "Parece interessante. Estou dentro se o pagamento for justo, embora eu não faça ideia de que carga você está falando. De qualquer forma, dou minha palavra.";
				link.l1.go = "zpq_prs2";
				link.l2 = "Eu diria que não, acho eu... Se eu te desse minha palavra, teria que trabalhar, e isso parece bem incômodo. Não vou fazer isso.";
				link.l2.go = "zpq_fld";
				Notification_Reputation(true, 71, "low");
			}
			else
			{
				dialog.text = "Sua reputação é inaceitável para mim. Peço que saia da sala. Nós somos capazes de resolver nossos problemas sozinhos.";
				link.l1 = "Tanto faz, então resolva-os...";
				link.l1.go = "exit";
				Notification_Reputation(false, 71, "low");
			}		
		break;
		
		case "zpq_fld":
			dialog.text = "Bem, pelo menos você me rejeitou de um jeito honesto... Não vou te prender aqui por mais tempo.";
			link.l1 = "Adeus.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "failed";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_fld2":
			dialog.text = "Hum, na verdade eu não esperava isso de você. Vou ter que pedir que se retire... E lembre-se da sua promessa de não divulgar nenhuma informação.";
			link.l1 = "Me desculpe...";
			link.l1.go = "exit";
    		ChangeCharacterComplexReputation(pchar,"nobility", -3);
			if (pchar.questTemp.zpq == "begin")
			{
				AddQuestRecord("zpq", "6");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
			}
			pchar.questTemp.zpq = "failed";
		break;
		
		case "zpq_prs2":
			dialog.text = "Excelente. Excelente. O problema é que a tempestade recente danificou nosso estoque de pólvora no arsenal do forte. Espero não precisar explicar que estamos com um problema delicado aqui. Em caso de um cerco prolongado, o forte não vai conseguir fazer nada. Não vamos aguentar por muito tempo.";
			link.l1 = "Agora entendi. Que carga você precisa – e em que quantidade?";
			link.l1.go = "zpq_prs3";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_prs3":
			dialog.text = "Precisamos de 15.000 barris de pólvora. Vou te pagar 100.000 pesos... Você deve entender que é um preço muito bom. Nossa situação atual me obriga a aceitar esses custos, embora tenha sido difícil convencer o tesoureiro do governador... A temporada de tempestades não nos permite usar nossas próprias rotas de abastecimento, e não queremos que todos fiquem sabendo desse problema...";
			link.l1 = "Entendi... o preço está realmente bom. Você mencionou riscos...";
			link.l1.go = "zpq_prs4";
		break;
		
		case "zpq_prs4":
			dialog.text = "I meant that such a large amount of gunpowder can be very dangerous during transportation. I have seen a few explosions with my own eyes; sometimes a single spark is enough. But if you face a storm... Whole convoys usually keep their distance from a potential brander. If it explodes, then everyone is dead!";
			link.l1 = "Entendi... Mas eu sempre cumpro minha palavra, pode considerar feito.";
			link.l1.go = "zpq_prs5";
			link.l2 = "Bem, señor... Você me contou coisas tão terríveis, que perdi qualquer vontade de fazer esse trabalho.";
			link.l2.go = "zpq_fld2";
		break;
		
		case "zpq_prs5":
			dialog.text = "Ótimo, fico muito feliz que tenhamos fechado um acordo. Vou te pagar assim que trouxer a carga.\nTerei o dinheiro em uma semana, não antes, então não precisa ter pressa, mas peço que não demore demais.";
			link.l1 = "Entendi, señor. Vou cuidar disso.";
			link.l1.go = "zpq_prs5_ok";
		break;
		
		case "zpq_prs5_ok":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.zpq = "begin";
			pchar.questTemp.zpq.time = 20;
			AddQuestRecord("zpq", "1");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			SaveCurrentQuestDateParam("pchar.questTemp.zpq");
		break;
		
		case "zpq_ex":
			dialog.text = "Até que enfim! Achei que você já tinha esquecido do nosso acordo. Vou mandar meus soldados descarregarem seu navio imediatamente. Trabalhar com pólvora é um negócio bem delicado, ha-ha!";
			link.l1 = "Está ótimo, señor, mas preciso lembrar do pagamento.";
			link.l1.go = "zpq_ex2";
			RemoveCharacterGoods(pchar, GOOD_POWDER, 15000);
			AddCharacterExpToSkill(pchar, "Sailing", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 500);

            pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
            pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
            pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;
		
		case "zpq_ex2":
			dialog.text = "Sim, claro. Você receberá 50.000 pesos, como combinamos.";
			link.l1 = "Você só pode estar brincando comigo, señor?! Nós tínhamos um acordo de 100.000 pesos!";
			link.l1.go = "zpq_ex3";
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "(Confiável) Estou começando a achar que você vai me passar a perna, então não vou sair daqui até receber meus 125.000 pesos!";
				link.l2.go = "zpq_ex4";
			}
			link.l3 = "Hm... Vejo que as coisas mudaram. Bom, é melhor eu pegar o dinheiro e ir embora...";
			link.l3.go = "zpq_ex5";
		break;
		
		case "zpq_ex3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 35)
			{
				Notification_Skill(true, 36, SKILL_LEADERSHIP);
				dialog.text = "Ah, sim... Exatamente! 100.000 pesos. Eu tinha me esquecido, me perdoe. É a idade, sabe como é... esclerose... Claro, aqui estão suas moedas. Foi um prazer fazer negócios com você, capitão. Agora, me desculpe, mas tenho muito trabalho a fazer...";
				link.l1 = "O mesmo pra você, señor. Até mais.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
				AddQuestRecord("zpq", "2");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 100000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				Notification_Skill(false, 36, SKILL_LEADERSHIP);
				dialog.text = "O quê?! Pegue seu dinheiro e suma daqui, ou vai apodrecer nesta masmorra!";
				link.l1 = "Você é um grande mentiroso, señor! Aconselho que devolva meu dinheiro de boa vontade, ou vou confiscar a carga!";
				link.l1.go = "zpq_ex_agry";
				link.l2 = "Com licença... Tudo bem, aceito o valor que você oferece e encerramos por aqui.";
				link.l2.go = "zpq_ex5";
			}
		break;
		
		case "zpq_ex4":
				dialog.text = "Que grosseria! Eu não sou louco, e lembro muito bem de ter oferecido 100.000 pesos.\n Droga! Não vou entrar no seu joguinho!";
				link.l1 = "Calma. Pense no navio incendiário carregado de pólvora bem na frente do seu forte. Se eu disser uma palavra, seu forte vai virar ruínas.";
				link.l1.go = "zpq_ex6";
		break;
		
		case "zpq_ex6":
			dialog.text = "Hm-Hm... argumento convincente. 125.000 pesos, você disse? Aqui, pode pegar, e me desculpe agora, mas tenho trabalho a fazer...";
			link.l1 = "Adeus, señor. Até logo.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "5");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 125000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			/*else
			{
				dialog.text = "O quê?! Eu sou um oficial militar! Acha que pode me assustar, garoto?! Guardas, peguem "+GetSexPhrase("ele","ela")+"!";
				link.l1 = "Boa sorte tentando, ratos das casamatas...";
				link.l1.go = "zpq_ex_war";
			}*/
		break;
		
		case "zpq_ex5":
			dialog.text = "Excelente! Você fez a escolha certa. Pegue suas moedas e adeus. Foi um prazer!";
			link.l1 = "Adeus...";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "3");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 50000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		break;
		
		case "zpq_ex_agry":
			dialog.text = "Ah, seu desgraçado! Guardas, prendam "+GetSexPhrase("ele","ela")+"!";
			link.l1 = "Argh! Parece que vou ter que pegar meu dinheiro do seu corpo sem vida...";
			link.l1.go = "zpq_ex_war";
		break;
		
        case "zpq_ex_war":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			pchar.questTemp.zpq = "failed";
            AddQuestRecord("zpq", "4");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 100000;
			AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum)*2 + rand(5000)));
			GiveItem2Character(npchar, "blade_21");
			EquipCharacterbyItem(npchar, "blade_21");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			npchar.cirassId = Items_FindItemIdx("cirass3");
			chrDisableReloadToLocation = true;
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_group_SetCheck(slai_group, "OpenTheDoors");
			AddSimpleRumour("Such terrible things happen here! They say that some prisoner has escaped from the casemates! He slaughtered all the guards, stole the treasury, and just went away! Shiver me timbers!", SPAIN, 5, 1);
		break;
		// <-- Опасный груз
	}
}

void GetGunType()
{
	int iGunType;
	if(makeint(pchar.rank) < 6) iGunType = rand(1);	//18&&24
	if(makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 15) iGunType = rand(2); //24&&32	
	if(makeint(pchar.rank) >= 15 && makeint(pchar.rank) < 24) iGunType = rand(2)+2; //32&&36&&42
	if(makeint(pchar.rank) >= 24) iGunType = 5-rand(1); //36clv&&42
	int iAdd = makeint(GetSummonSkillFromName(pchar, SKILL_COMMERCE)/20);
	
	switch (iGunType)
	{
		case 0:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_24;     					
			pchar.questTemp.PrisonGun.Price = 28 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "24 calibre cannons";
		break; 
		case 1:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_18;     					
			pchar.questTemp.PrisonGun.Price = 25 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "couleuvrines";
		break; 
		case 2:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_32;     					
			pchar.questTemp.PrisonGun.Price = 32 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "32 calibre cannons";
		break; 
		case 3:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_36;     					
			pchar.questTemp.PrisonGun.Price = 36 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "36 calibre cannons";
		break;
		case 4:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_36;     					
			pchar.questTemp.PrisonGun.Price = 49 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "full couleuvrines";
		break; 
		case 5:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_42;     					
			pchar.questTemp.PrisonGun.Price = 40 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+20+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "42 calibre cannons";
		break; 
	}
}
