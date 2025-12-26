// НПС офиса ГВИК
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
		case "First time":
			dialog.text = "Quer alguma coisa?";
			link.l1 = "Não.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// офицер
		case "HWIC_officer":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarme! O inimigo está aqui! Às armas!";
				link.l1 = "Droga!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Ei você, pare! Seu rosto me é familiar... claro! Você está sendo procurado pelos seus crimes! Rapazes, peguem ele!";
				link.l1 = "Droga!";
				link.l1.go = "fight";
				break;
			}
			chrDisableReloadToLocation = true;
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				dialog.text = "Bem-vindo à Companhia Holandesa das Índias Ocidentais. Fale rápido, tempo é dinheiro.";
				link.l1 = "Estou aqui a negócios. Licenças, instrumentos de navegação, essas coisas...";
				link.l1.go = "HWIC_officer_3";
				link.l2 = "Quero oferecer meus serviços à Companhia. Em troca de ouro, é claro. Estão contratando?";
				link.l2.go = "HWIC_officer_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "Bem-vindo à Companhia Holandesa das Índias Ocidentais. Fale rápido, tempo é dinheiro.";
				link.l1 = "Me desculpe, parece que eu estava enganado. Estou indo embora.";
				link.l1.go = "HWIC_officer_exit";
				link.l2 = "Estou aqui a negócios de comércio. Licenças, instrumentos de navegação, e por aí vai...";
				link.l2.go = "HWIC_officer_3";
				break;
			}
			dialog.text = "Fale logo, tempo é dinheiro.";
			link.l1 = "Estou aqui a negócios. Licenças, instrumentos de navegação, essas coisas...";
			link.l1.go = "HWIC_officer_3";
			link.l2 = "Quero oferecer meus serviços à Companhia. Em troca de ouro, é claro. Estão contratando?";
			link.l2.go = "HWIC_officer_2";
		break;
		
		case "HWIC_officer_1":
			dialog.text = "Então suba até o escritório do senhor Rodenburg.";
			link.l1 = "Obrigado, estou a caminho.";
			link.l1.go = "HWIC_officer_exit";
			// belamour legendary edition переехали по другому адресу
			LocatorReloadEnterDisable("GVIK", "reload2", false);//кабинет откроем
		break;
		
		case "HWIC_officer_2":
			dialog.text = "A Companhia não está contratando no momento.";
			link.l1 = "Que pena. Desculpe incomodar você.";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_3":
			dialog.text = "Fale com o senhor Gerritz. A mesa dele fica à sua esquerda quando você entra. Ele faz negócios com capitães contratados.";
			link.l1 = "Obrigado, oficial...";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_exit":
			DialogExit();
			// belamour legendary edition переехали
			LAi_ActorGoToLocation(npchar, "soldiers", "soldier3", "GVIK", "soldiers", "soldier3", "", 5);
			DoQuestCheckDelay("ReturnTalkerToOfficer", 5.0); // 140313
			NextDiag.TempNode = "HWIC_officer";
		break;
		
		// солдаты
		case "HWIC_soldier":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarme! O inimigo está aqui! Às armas!";
				link.l1 = "Droga!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Aha! Acho que já sei quem você é... Mas é claro! Você está sendo procurado pelos seus crimes! Rapazes, peguem ele!";
				link.l1 = "Droga!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Fale com nossos oficiais ou com o senhor Gerritz. Não tenho nada a dizer a você. Estou de serviço.";
			link.l1 = "Sua disciplina é admirável.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_soldier";
		break;
		
		// клерки
		case "HWIC_clerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarme! O inimigo está aqui! Soldados!";
				link.l1 = "Droga!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Fale com o senhor Gerritz.";
			link.l1 = "Certo, entendi.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_clerk";
		break;
		
		// главный клерк - минхер Герритц
		case "HWIC_headclerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarme! O inimigo está aqui! Soldados, prendam-no!";
				link.l1 = "Droga!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Hum. Acho que tem algo estranho em você... Mas é claro! Você é procurado pelos seus inúmeros crimes contra a Holanda! Soldados, prendam-no!";
				link.l1 = "Droga!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Quer alguma coisa, senhor?";
			if (!CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				link.l1 = "Quero comprar uma licença de comércio da Companhia Holandesa das Índias Ocidentais.";
				link.l1.go = "licence";	
			}
			if (!CheckAttribute(npchar, "quest.trade"))
			{
				link.l2 = "Ouvi dizer que é possível comprar instrumentos de navegação e outros itens úteis aqui. É verdade?";
				link.l2.go = "trade";	
			}
			else
			{
				link.l2 = "O que você está vendendo hoje?";
				link.l2.go = "trade_1";	
			}
			if (CheckCharacterItem(pchar, "Cromvel_depeshe"))
			{
				link.l3 = "Tenho um documento interessante para você, mynheer. Dê uma olhada nas primeiras linhas. Trata-se da sobrevivência da República e dos lucros da Companhia. As coordenadas de uma certa reunião também estão aí. Eu posso vendê-las para você, se estiver interessado. Por um preço generoso, é claro.";
				link.l3.go = "depeshe";	
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Garpiya") && pchar.questTemp.Caleuche.Garpiya == "gwik")
			{
				link.l4 = "Um capitão chamado Reginald Jackson deve estar trabalhando para você. Ele navega em um xebec chamado 'Harpy'. Pode me dizer como posso encontrá-lo? Tenho assuntos importantes a tratar com ele.";
				link.l4.go = "caleuche";	
			}
			// Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_RazgovorGerrits"))
			{
				link.l4 = "Preciso ver o senhor Rodenburg com urgência. É de extrema importância. Onde ele está?";
				link.l4.go = "PZ_RazgovorGerrits_1";
			}
			link.l9 = "Não, não é nada.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "HWIC_headclerk";
		break;
		
		// торговые лицензии
		case "licence":
			if (!CheckAttribute(npchar, "quest.licence"))
			{
				dialog.text = "Bem, você está livre para comprá-la. Mas devo avisar que a Companhia preza muito sua reputação de absoluta neutralidade, portanto é proibido atacar navios mercantes de qualquer nação enquanto estiver com esta licença.\nSe descobrirmos que tal ato foi cometido, sua licença será anulada. Além disso, se você entrar em conflito com os holandeses ou com a Companhia por qualquer motivo, sua licença também será cancelada. Estamos entendidos?";
				link.l1 = "Claro como cristal. Vou me lembrar disso.";
				link.l1.go = "licence_0";
				npchar.quest.licence = true;
			}
			else
			{
				dialog.text = "Você pode comprar uma licença, se quiser. Então, por quantos dias?";
				link.l1.edit = 6;
				link.l1 = "";	
				link.l1.go = "licence_1";
			}
		break;
		
		case "licence_0":
			dialog.text = "A licença garante passagem livre para qualquer porto de qualquer nação, mostra suas intenções pacíficas e explica seu propósito – negociar. Mas não vai te ajudar se você tiver problemas com a lei. Nesse caso, eles simplesmente vão tomá-la de você. Lembre-se,  Não esqueça de hastear uma bandeira amiga antes de entrar em qualquer porto. As patrulhas e os artilheiros das fortalezas preferem atirar primeiro e perguntar depois A duração mínima da licença é de vinte dias e a máxima é de seis meses ou 180 dias Certo, quase me esqueci... Segundo nossas estimadas tradições, todos os acordos envolvendo licenças são pagos em dobrões. Agora vamos discutir os termos. Por quanto tempo você quer que a licença dure?";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "Desculpe, mas preciso pensar um pouco mais sobre isso. Até mais.";	
			link.l2.go = "exit";
		break;
		
		case "licence_1":
			float fQty = stf(dialogEditStrings[6]);
			npchar.quest.lcc_summ = makeint(sqrt(fQty)*10)*7;
			if (fQty < 1)
			{
				dialog.text = "Senhor, por favor, fale mais alto. Não ouvi direito. Então, por quanto tempo?";
				link.l1 = "Deixe-me pensar...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 0 && fQty < 20)
			{
				dialog.text = "O prazo mínimo para a licença é de vinte dias. E aí? Vinte dias ou mais?";
				link.l1 = "Deixe-me pensar...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 180)
			{
				dialog.text = "O prazo máximo da licença é de meio ano. Cento e oitenta dias ou menos?";
				link.l1 = "Deixe-me pensar...";
				link.l1.go = "licence_r";
				break;
			}
			dialog.text = "Por "+FindRussianDaysString(sti(fQty))+"? Muito bem. Vai te custar "+FindRussianDublonString(sti(npchar.quest.lcc_summ))+". Esses termos são aceitáveis?";
			if (PCharDublonsTotal() >= sti(npchar.quest.lcc_summ))
			{
				link.l1 = "Sim, sou eu.";
				link.l1.go = "licence_2";
			}
			link.l2 = "Infelizmente, não tenho tanto dinheiro comigo agora. Vou voltar depois para pegar a licença.";
			link.l2.go = "exit";
		break;
		
		case "licence_r":
			dialog.text = "";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "Desculpe, mas ainda preciso pensar nisso. Nos vemos depois.";	
			link.l2.go = "exit";
		break;
		
		case "licence_2":
			int iQty = sti(dialogEditStrings[6]);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.lcc_summ));
			GiveNationLicence(HOLLAND, iQty);
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "start")
			{
				if(iQty < 180) 
				{
					Log_info("Quest: 'Together with the Shark' - your license is less than 180 days");
				}
				else 
				{
					pchar.questTemp.SharkGoldFleet.LicenceOk = true;
					AddQuestRecord("SharkGoldFleet", "2");
				}
				pchar.questTemp.SharkGoldFleet = "afterGvik";
			}
			dialog.text = "Espere um instante... Deixe-me colocar um selo e carimbar aqui... pronto, está feito. Pegue seu documento.";
			link.l1 = "Obrigado! Adeus, mynheer.";
			link.l1.go = "exit";
		break;
		
		case "trade":
			dialog.text = "De fato, temos sim. Aqui você pode comprar instrumentos de navegação como bússolas, astrolábios, cronômetros e ampulhetas. Mas nem sempre temos todos em estoque, exceto talvez as ampulhetas. Nossos fornecedores e capitães costumam comprar os outros instrumentos bem rápido. Então, se não encontrar o que procura, volte daqui a uma semana, quando reabastecemos.\nTambém vendemos mapas e lunetas. Gostaria de ver o que temos?";
			link.l1 = "Sim, por favor.";
			link.l1.go = "trade_1";
			npchar.quest.trade = "true";
		break;
		
		case "trade_1":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 7)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// депеша Кромвеля
		case "depeshe":
			dialog.text = "Hm, mostre-me...(lendo) Ora, ora... O apetite de Cromwell está crescendo. Kanker! Esses cães puritanos já não derramaram sangue suficiente na própria ilha, que agora querem trazer sua sujeira pra cá!? Onde conseguiu esse despacho?";
			link.l1 = "Eu peguei isso de um mensageiro inglês. Então, quer comprar?";
			link.l1.go = "depeshe_1";
		break;
		
		case "depeshe_1":
			dialog.text = "Sim. Peter Stuyvesant vai ficar realmente satisfeito ao ler isso, tenho certeza. E ele vai tomar providências para acabar com isso... Posso pagar em dobrões de ouro ou posso emitir uma licença para você por seis meses. O que prefere?";
			link.l1 = "Eu escolho o ouro.";
			link.l1.go = "depeshe_dublon";
			link.l2 = "Eu quero a licença.";
			link.l2.go = "depeshe_licence";
		break;
		
		case "depeshe_dublon":
			TakeNItems(pchar, "gold_dublon", 700);
			Log_Info("You have received 700 doubloons");
			dialog.text = "Muito bem. Aqui estão seus setecentos dobrões. Uma bela recompensa por um serviço bem feito.";
			link.l1 = "Aqui está sua mensagem.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_licence":
			GiveNationLicence(HOLLAND, 180);
			dialog.text = "Ótimo. Aqui está sua licença válida por seis meses.";
			link.l1 = "Obrigado! E aqui está o seu despacho.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_exit":
			RemoveItems(pchar, "Cromvel_depeshe", 1);
			pchar.quest.Terrapin_CromvelScuadron.over = "yes"; //снять прерывание
			ChangeCharacterNationReputation(pchar, HOLLAND, 15);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			dialog.text = "Obrigado. É bom ver que você demonstrou consciência e lealdade à República. Vou contar a Matthias Beck e Peter Stuyvesant sobre o seu bom feito.";
			link.l1 = "Bom saber. Até logo!";
			link.l1.go = "exit";
		break;
		
		// Sinistra Путеводная звезда
		case "PZ_RazgovorGerrits_1":
			dialog.text = "Receio que ele já tenha partido para o Velho Mundo com a família Schneur. Acho que ele comentou isso com você.";
			link.l1 = "Isso mesmo, ele fez. Mas eu esperava que ele pudesse ter se atrasado por algum assunto recente no Arquipélago. Diga-me, Gerritz, alguém da Companhia mantém contato com o senhor Rodenburg? Talvez por meio dos navios de correio?";
			link.l1.go = "PZ_RazgovorGerrits_2";
		break;
		
		case "PZ_RazgovorGerrits_2":
			dialog.text = "De jeito nenhum - antes de partir, ele nos pediu para nunca incomodá-lo - disse que estava começando uma vida nova, melhor.";
			link.l1 = "Vamos torcer para que nossas vidas também melhorem. Adeus.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PZ_RazgovorGerrits");
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Deixe-me verificar os registros do manifesto... Ikema, Immerzeel, Jacobs... Jackson, achei. Hmm, o Kapitein Reginald Jackson está atualmente fazendo operações regulares de transporte entre Port Royal e Philipsburg. Procure por ele nessa rota. Agora, kapitein, preciso avisar de antemão—se estiver planejando alguma travessura, é melhor desistir, porque esse Kapitein Jackson está sob nossa proteção. Estamos entendidos, mynheer?";
			link.l1 = "Eu só tenho negócios com ele. Apenas uma troca simples. Não quero prejudicá-lo de forma alguma.";
			link.l1.go = "caleuche_1";
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
		break;
		
		case "caleuche_1":
			dialog.text = "Excelente. O Kapitein Jackson normalmente não fica muito tempo em Port Royal ou em Philipsburg. Tempo é dinheiro, afinal. Assim que o navio dele é descarregado e carregado de novo, ele costuma zarpar imediatamente. Você terá mais sorte encontrando-o pelas rotas marítimas.";
			link.l1 = "Obrigado!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			AddDialogExitQuestFunction("Caleuche_PrepareCreateGarpiya");
		break;
		
		// новый босс ГВИК
		case "HWIC_Boss":
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if (!CheckAttribute(npchar, "quest.silk_info"))
				{
					if (sti(pchar.reputation.nobility) > 60)
					{
						dialog.text = "Aha, Kapitão "+GetFullName(pchar)+"! Que bom que você veio. Tenho uma proposta de negócio para você.";
						link.l1 = "Interessante! Estou ouvindo você, mynheer.";
						link.l1.go = "silk_info";
						break;
					}
					else Notification_Reputation(false, 61, "low");
				}
			}
			dialog.text = "Bom dia, Kapitein "+GetFullName(pchar)+"! Como posso ajudar?";
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if(CheckAttribute(npchar, "quest.silk")) // торговля шелком
				{
					if (GetDataDay() == 1 || GetDataDay() == 15)
					{
						link.l1 = "Sobre aquela seda do navio...";
						link.l1.go = "trade_silk";
					}
				}
			}
			link.l2 = "Bom dia. Não, não preciso de nada, só queria cumprimentar mesmo.";
			link.l2.go = "exit";			
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "silk_info":
			dialog.text = "Recentemente estabeleci conexões comerciais com um mercador de Lyon para fornecer seda de navio ao Caribe. Você já ouviu falar disso? As melhores velas do mundo são feitas dessa seda, então imagino que você esteja interessado.";
			link.l1 = "Por todos os santos, isso é música para os meus ouvidos. Quais são suas condições?";
			link.l1.go = "silk_info_1";
		break;
		
		case "silk_info_1":
			dialog.text = "Remessas pequenas, mas regulares. Posso separar trinta rolos para você a cada duas semanas. O preço de cada rolo é vinte doblões. Vamos fazer assim: reservo trinta rolos para você no primeiro e no décimo quinto dia de cada mês. Se você não vier buscá-los nessas datas, vendo os rolos para outro cliente.";
			link.l1 = "Então, sem obrigações?";
			link.l1.go = "silk_info_2";
		break;
		
		case "silk_info_2":
			dialog.text = "Exatamente, kapitein. Compre a seda se quiser. Você paga pelo lote inteiro – seiscentos doblões. Espero que se torne um cliente regular.";
			link.l1 = "Obrigado pela oferta, senhor. Fechado.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			npchar.quest.silk_info = "true";
			npchar.quest.silk = "true";
			AddQuestRecordInfo("Unique_Goods", "3");
		break;
		
		// торговля шелком
		case "trade_silk":
			if (CheckAttribute(pchar, "questTemp.UpgradeSilk"))
			{
				dialog.text = "Claro, kapitein. Sua seda está esperando por você. Está pronto para pagar por ela?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Claro! Aqui, pegue 2.550 doblões.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Droga, deixei o dinheiro no meu navio. Vou buscar agora mesmo!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Claro, kapitein. Sua seda está esperando por você. Está pronto para pagar por ela?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Claro! Aqui, pegue seiscentos doblões.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Droga, deixei o dinheiro no meu navio. Já volto com ele!";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && !CheckAttribute(pchar, "questTemp.GVIKSilkBlock")) // увеличить объём поставок шёлка
			{
				link.l4 = "Mijnheer "+npchar.name+", eu gostaria de discutir a possibilidade de aumentar o fornecimento de seda.";
				link.l4.go = "UpgradeSilk";
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && CheckAttribute(pchar, "questTemp.GVIKSilkPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок шёлка, если в первый раз не принесли
			{
				link.l4 = "Trouxe seus dobrões, Mijnheer "+npchar.name+". Por favor, aceite-os.";
				link.l4.go = "UpgradeSilk_Agreed";
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "trade_silk_1":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You have given 600 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Foi um prazer fazer negócios com você, kapitein. Sua seda será entregue ao seu navio por escaler.";
			link.l1 = "Obrigado!";
			link.l1.go = "trade_silk_2";
		break;
		
		case "trade_silk_2":
			dialog.text = "Espero te ver em breve. Volte sempre.";
			link.l1 = "Certo. Até mais!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 30);
			DeleteAttribute(npchar, "quest.silk");
			SetFunctionTimerCondition("Silk_TraderAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk": //
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Eu aprecio sua abordagem de negócios e estou disposto a considerar seu pedido. Talvez possamos aumentar o volume, digamos, cinco vezes. No entanto, organizar esse fornecimento vai exigir recursos consideráveis. Teremos que ampliar o espaço de armazenamento, reforçar a segurança e garantir rotas de entrega confiáveis. Como isso também é do seu interesse, sugiro que dividamos essas despesas entre nós.";
				link.l1 = "Tudo isso faz sentido. Qual valor você considera necessário para cobrir essas despesas?";
				link.l1.go = "UpgradeSilk_1";
				Notification_Skill(true, 80, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Entendo seu interesse em aumentar os suprimentos, porém, neste momento é difícil para mim concordar com tais mudanças. Não duvido da sua ambição de crescer, mas esse tipo de negociação exige muito mais experiência em comércio e mais segurança nas suas próprias decisões. Sugiro que você aprofunde seus conhecimentos na arte da negociação e depois volte a me procurar com uma proposta mais concreta. Quando estiver pronto, terei prazer em fortalecer nossa parceria.";
				link.l1 = "Hmm... Tudo bem. Vou voltar a essa conversa depois.";
				link.l1.go = "exit";
				Notification_Skill(false, 80, SKILL_COMMERCE);
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_1":
			dialog.text = "Levando em conta todos os detalhes, sua parte das despesas será de três mil dobrões de ouro. Esse valor nos permitirá organizar as medidas necessárias sem demora.";
			link.l1 = "Mijnheer "+npchar.name+", três mil doblões? Isso é uma piada? Vim até você com uma proposta honesta, e você espera que eu pague uma quantia absurda dessas só para organizar os suprimentos?";
			link.l1.go = "UpgradeSilk_2";
		break;
		
		case "UpgradeSilk_2":
			dialog.text = "Peço que me entenda corretamente. Não estou tentando enganar você. Este dinheiro é o valor necessário para garantirmos a devida organização no fornecimento. Não se trata apenas de ampliar armazéns e reforçar a segurança, mas também de assegurar a entrega das mercadorias sem atrasos ou perdas, apesar de toda a imprevisibilidade desse negócio. São despesas normais para volumes desse porte. No fim, seu investimento será recompensado, e você receberá as mercadorias em perfeito estado e no prazo.";
			link.l1 = "Suas explicações são um tanto reconfortantes, mijnheer. Mas ainda assim, esse valor continua alto demais. Estou disposto a aceitar seus termos se você reduzir o preço para pelo menos dois mil e quinhentos dobrões. Tenho certeza de que isso será suficiente para organizar os suprimentos e garantir todas as medidas de segurança.";
			link.l1.go = "UpgradeSilk_3";
		break;
		
		case "UpgradeSilk_3":
			dialog.text = "Eu entendo, o valor é alto, mas como já disse, é necessário para que o trabalho seja feito direito. Não posso reduzir, pois isso colocaria todo nosso esforço em risco. No entanto, para que você não se sinta enganado, estou disposto a oferecer um desconto de quinze por cento em todos os próximos fornecimentos. Espero que assim você consiga compensar as despesas.";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Hum, um desconto de quinze por cento é, claro, um avanço. Tudo bem. Estou pronto para aceitar sua oferta, mesmo achando o preço extremamente alto. Espero que nossa parceria esteja à altura das minhas expectativas. Aqui está o seu dinheiro.";
				link.l1.go = "UpgradeSilk_Agreed";
			}
			link.l2 = "Mijnheer "+npchar.name+", sua oferta não me deixa escolha. Que sejam três mil dobrões, embora seja uma quantia considerável. Mas não posso pagar tudo de uma vez agora. Voltarei assim que tiver o dinheiro.";
			link.l2.go = "UpgradeSilk_5";
			link.l3 = "Um desconto de quinze por cento? Mijnheer "+npchar.name+", isso não era o que eu esperava. Esse valor não são só despesas, é um roubo descarado! Mas não pretendo romper nossos negócios. Vamos voltar aos termos anteriores – 30 rolos de seda por 20 dobrões cada.";
			link.l3.go = "UpgradeSilk_4";
		break;
		
		case "UpgradeSilk_Agreed":
			dialog.text = "Fico feliz que você aceitou, "+pchar.name+". Agora, sobre os detalhes: 150 rolos de seda a 17 doblões cada. Total - 2550 doblões pelo lote inteiro. Você pode retirar a mercadoria como de costume - nos dias 1 e 15 de cada mês. Acho que esse negócio vai trazer um bom lucro para ambos os lados.";
			link.l1 = "Excelente! Agora sim, isso é do jeito que eu gosto. Até logo, mijnheer. Nos vemos em breve.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "3_1");
			pchar.questTemp.UpgradeSilk = true;
			pchar.questTemp.GVIKSilkBlock = true;
			DeleteAttribute(pchar, "questTemp.GVIKSilkPotom");
		break;
		
		case "UpgradeSilk_4":
			dialog.text = "This is simply a business arrangement, not robbery, as it may have seemed to you. But, as you wish. Come as usual, on the 1st and 15th, for a batch of silk; I will be glad to strike a new deal.";
			link.l1 = "Certamente, senhor. Adeus.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_5":
			dialog.text = "Fico feliz que tenha tomado a decisão certa. Assim que trouxer o dinheiro, vamos discutir todos os detalhes do acordo e dar andamento à sua execução.";
			link.l1 = "Adeus, Mijnheer "+npchar.name+". Até logo, assim que eu juntar a quantia necessária.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			pchar.questTemp.GVIKSilkPotom = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "fight":
			DialogExit();
			sld = characterFromId("HWIC_officer");
			LAi_SetGuardianTypeNoGroup(sld);
			LAi_group_Attack(sld, Pchar);
			for (i=1; i<=6; i++)
			{	
				sld = characterFromId("HWIC_sold_"+i);
				LAi_group_Attack(sld, Pchar);
			}
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
