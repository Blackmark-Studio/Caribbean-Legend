// диалоги по квесту Цена чахотки
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Consumption == "final")
			{
				dialog.text = "Capitão! Ouvi dizer que você foi para o mar! O que aconteceu? Descobriu alguma coisa? Por favor, me conte, desembucha!";
				if (CheckAttribute(pchar, "questTemp.Consumption.TakeMoney"))
				{//взял деньги
					link.l1 = "Não, minha bela, esse ataque foi feito a pedido de Sua Graça, o governador. Sinto muito, mas Angelo morreu nas masmorras do forte – disso não resta dúvida agora. Seja forte! ";
					link.l1.go = "Waitress";
				}
				else
				{//убил Хуана
					if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
					{
						link.l1 = "Você estava certo. Seu irmão foi sequestrado. O Comandante estava vendendo prisioneiros como gado para um traficante de escravos conhecido como Consumo. Mas eu alcancei o navio dele, e agora ele está no fundo do mar, e seu irmão Angelo logo vai desembarcar. Infelizmente, não tenho botes suficientes para levar todos os passageiros à terra de uma vez só. ";
						link.l1.go = "Waitress_2";
					}
					else
					{//отпустил Хуана
						link.l1 = "You were right. Your brother was kidnapped. The Commandant had been selling prisoners like cattle to a slaver nicknamed Consumption. But I caught up with his ship; although I failed to kill that bastard, your brother Angelo will come ashore soon. Unfortunately, I do not have enough longboats to bring all the passengers ashore at once. ";
						link.l1.go = "Waitress_2";
					}
					sld = characterFromId("ConAndjelo");
					sld.lifeday = 0;
					RemovePassenger(Pchar, sld);
				}
			}
			else
			{
				dialog.text = "Conseguiu descobrir algo sobre o destino do Angelo, capitão?";
				link.l1 = "Ainda não. Mas acho que logo terei novidades. Só precisa esperar. ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		case "without_moneysss": // лесник  если Гг нажрался..сволочь:D:D:D
		    dialog.text = "Senhor, você prometeu encontrar meu irmão... Por que está perdendo tempo bebendo aqui?";
			link.l1 = "Ohh... É, claro... hic... Relaxa, moça... Jesus tá no comando... 'slurp'... Jesus tá no comando. Eu já fui... hic...";
			link.l1.go = "exit";
		break;
		
		case "Servant":
			dialog.text = "Boa tarde, senhor. Qual é o seu negócio aqui?";
			link.l1 = "Trouxe uma mensagem para o senhor comandante, mas preciso entregá-la pessoalmente.";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Então vá procurá-lo no forte.";
			link.l1 = "Esta mensagem é importante demais e não deve cair nos olhos ou ouvidos de soldados. Talvez eu tenha chegado cedo demais, mas posso esperar por ele aqui. Confie em mim, é realmente importante!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < 40)
			{
				notification("Skill Check Failed (40)", SKILL_SNEAK);
				dialog.text = "O Senhor Comandante geralmente me avisa sobre todos os assuntos importantes que exigem uma mudança na rotina... Sabe, na verdade, ele me avisou mesmo sobre este caso em particular.";
				link.l1 = "E o que ele disse?";
				link.l1.go = "Servant_3";
			}
			else
			{
				notification("Skill Check Passed", SKILL_SNEAK);
				dialog.text = "Certo, eu acredito em você. E vou acreditar ainda mais quando o senhor comandante chegar para confirmar suas palavras. Mas até lá, vou ficar de olho em você o tempo todo.";
				link.l1 = "Pode me observar o quanto quiser...";
				link.l1.go = "Servant_4";
			}
		break;
		
		case "Servant_3":
			dialog.text = "Ele me disse para chamar os guardas da guarnição nesses casos. Mas acho que damos conta sozinhos. Rapazes! Vamos acabar com ele!";
			link.l1 = "Merda!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Servant_4":
			DialogExit();
			NextDiag.CurrentNode = "Servant_repeat";
			LAi_SetOwnerType(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Servant_repeat":
			dialog.text = "O que mais você quer? Já decidiu me entregar a mensagem?";
			link.l1 = "Não, vou esperar pelo comandante...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Servant_repeat";
		break;
		
		case "Servant_fight":
			int iRank = sti(pchar.rank)+5;
			int iScl = 15 + 2*sti(pchar.rank);
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true;
			for (i=9; i<=11; i++)
			{	
				sld = GetCharacter(NPC_GenerateCharacter("Conservant_"+i, "citiz_"+i, "man", "man", iRank, SPAIN, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "goto", "goto5");
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Consumption_AfterHouseFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//попытка залезть в сундук
		case "Man_FackYou":
			dialog.text = "Você é um ladrão! Ou talvez um espião? Gente, lá embaixo, rápido!";
			link.l1 = "Ah, demônio!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Sergio":
			dialog.text = "Com licença, posso falar com você?";
			link.l1 = "Pra ser sincero, estou com pressa. O que você quer?";
			link.l1.go = "Sergio_1";
		break;
		
		case "Sergio_1":
			dialog.text = "Ouvi dizer que você anda perguntando sobre um tal de Juan e uma doença na nossa prisão...";
			link.l1 = "De fato, eu fiz... pode se explicar?";
			link.l1.go = "Sergio_2";
		break;
		
		case "Sergio_2":
			dialog.text = "Calma, calma! Fique tranquilo e não toque na sua espada! Estamos do mesmo lado aqui! Não sei por que você se importaria com os nossos problemas, mas isso precisa acabar! Não posso mais ficar calado!";
			link.l1 = "Ficar em silêncio? Sobre o quê? O que você sabe sobre tuberculose?";
			link.l1.go = "Sergio_3";
		break;
		
		case "Sergio_3":
			dialog.text = "Eu sei muita coisa, talvez tudo, e vou te explicar – mas não aqui. Vamos nos encontrar à noite, quando as luzes se apagarem. Sou assistente de médico, então tenho permissão para sair do forte. A gente se encontra além dos portões da cidade, e eu te conto tudo. Por favor – pare de fazer perguntas antes que chame a atenção deles, se é que já não chamou... Preciso ir agora. Lembre-se, à noite, além dos portões da cidade.";
			link.l1 = "Certo, eu vou estar lá. Ei! Espera...";
			link.l1.go = "Sergio_4";
		break;
		
		case "Sergio_4":
			DialogExit();
			AddQuestRecord("Consumption", "8");
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption3.win_condition.l1 = "location";
			pchar.quest.Consumption3.win_condition.l1.location = "PortSpein_Exittown";
			pchar.quest.Consumption3.win_condition.l2 = "Hour";
			pchar.quest.Consumption3.win_condition.l2.start.hour = 0;
			pchar.quest.Consumption3.win_condition.l2.finish.hour = 3;
			pchar.quest.Consumption3.function = "Consumption_MeetSergio";
			pchar.quest.Consumption4.win_condition.l1 = "Timer";
			pchar.quest.Consumption4.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Consumption4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Consumption4.function = "Consumption_FailSergio";
			locations[FindLocation("PortSpein_Exittown")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("PortSpein_Exittown", true);//офицеров не пускать
		break;
		
		case "Sergio_5":
			dialog.text = "Graças a Deus que você chegou... Espero que ninguém tenha te seguido?";
			link.l1 = "Por quê? Você é muito desconfiado, talvez até mais do que o senhor comandante, então é melhor ir direto ao ponto... O que você sabe sobre o Juan?";
			link.l1.go = "Sergio_6";
		break;
		
		case "Sergio_6":
			dialog.text = "Meu nome é Sergio Saldo. Trabalho como assistente médico no nosso forte e...";
			link.l1 = "";
			link.l1.go = "Sergio_6_1";
		break;
		
		case "Sergio_6_1":
			dialog.text = "";
			link.l1 = "Espere! Você ouviu isso?";
			link.l1.go = "Sergio_7";
			Play3DSound("lomanie_vetki", -33.25, 1.00, 3.73)
		break;
		
		case "Sergio_7":
			dialog.text = "O quê?! Onde?";
			link.l1 = "Merda, não estamos sozinhos aqui... Quem você trouxe com você, seu lixo?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Consumption_CreateBandits");
		break;
		
		case "Bandit":
			dialog.text = "Nos viram! Você pega o doutor, e eu cuido do outro!";
			link.l1 = "...";
			link.l1.go = "Bandit_1";
		break;
		
		case "Bandit_1":
			DialogExit();
			sld = characterFromId("Sergio");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=3; i++)
			{	
				sld = characterFromId("Conbandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Conbandit_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Sergio_8":
			dialog.text = "Guarde sua espada, acabou! Agora você viu com seus próprios olhos que eles também tentaram me matar!";
			link.l1 = "Bem, isso parece sofisticado demais para ser coisa suja – então, você não está com eles. Onde estávamos? Você é médico da prisão, não é?";
			link.l1.go = "Sergio_9";
		break;
		
		case "Sergio_9":
			dialog.text = "Sim. Eu sou o médico da prisão. Estudei medicina quando era jovem, e não há muitas pessoas instruídas por aqui. Por isso, sei melhor do que ninguém o que acontece na prisão!";
			link.l1 = "O que está acontecendo então? E os prisioneiros? Você sabe de alguma coisa sobre eles terem sumido de repente?";
			link.l1.go = "Sergio_10";
		break;
		
		case "Sergio_10":
			dialog.text = "O nosso comandante os vende... vende como gado para um traficante chamado Juan. Ele escolhe aqueles de quem ninguém vai sentir falta – miseráveis, marinheiros de navios aleatórios. E então, de repente, eles 'morrem de tuberculose' – você pode imaginar o resto...";
			link.l1 = "Afinal, esse Juan é humano! O que você sabe sobre ele?";
			link.l1.go = "Sergio_11";
		break;
		
		case "Sergio_11":
			dialog.text = "Um pouco. Ele costumava fazer seus negócios sujos no Marrocos junto com piratas berberes, e gosta de contar histórias daquela época quando aparece por aqui. Foi lá que ganhou o apelido de Consumo. Prefiro nem imaginar de onde veio esse nome\nEle aparece aqui todo mês e leva todos os prisioneiros para o navio dele.";
			link.l1 = "'Consumo!' E ainda me chamaram de cínico! Então é por isso... Esse tal de senhor comandante seu é mesmo um idiota!";
			link.l1.go = "Sergio_12";
		break;
		
		case "Sergio_12":
			dialog.text = "Pelo que entendi, você precisa de alguém entre os prisioneiros desaparecidos, senão como saberia dessa história, estou certo? Se for isso mesmo, é melhor se apressar: esta noite é a última deste mês. Já assinei os papéis declarando a morte de mais três pessoas, e o Juan vai levantar âncora amanhã antes do meio-dia, assim que recebê-los!";
			link.l1 = "O que você assinou? Não estou entendendo direito...";
			link.l1.go = "Sergio_13";
		break;
		
		case "Sergio_13":
			dialog.text = "Eu tive que fazer isso – como já vinha fazendo há vários meses! Foi por isso que vim aqui, para acabar com isso. Você sabe como o Doutor Pinero morreu? Aquele que tratava dos prisioneiros antes de mim?";
			link.l1 = "Acredito que me disseram que ele morreu de tuberculose, não foi? Então, você foi forçado a isso. Faz sentido – mas por que ninguém procurou as autoridades sobre esse assunto?";
			link.l1.go = "Sergio_14";
		break;
		
		case "Sergio_14":
			dialog.text = "E quem vai acreditar nisso? Eu não tenho nenhuma prova, e aqueles soldados que deveriam guardar os prisioneiros estão sendo bem pagos, então não se importariam nem se estivessem vendendo gente pros caribes como comida\nNinguém liga para os prisioneiros, e isso é uma carta na manga do comandante. Mas você pode acabar com isso, pelo menos por um tempo, se eliminar o Juan!";
			link.l1 = "Pelo que entendi, aqueles homens em terra eram dele, não eram? Como posso encontrá-lo?";
			link.l1.go = "Sergio_15";
		break;
		
		case "Sergio_15":
			dialog.text = "Você provavelmente chamou a atenção de alguém com suas perguntas... Eu te disse para ser mais cuidadoso! Mas isso não importa agora. Não sei nada sobre o navio do Juan, mas os prisioneiros sempre são levados para Galera Point, que fica na parte norte da ilha. Imagino que o navio do mercador de escravos deva estar por perto e talvez você consiga alcançá-lo. Os mensageiros dele comentaram hoje que ele vai zarpar amanhã ao meio-dia.";
			if (!CheckCharacterItem(pchar, "letter_consumption"))
			{
				link.l1 = "Obrigado, Sergio, você é um verdadeiro oficial e um homem de honra. Vou levantar âncora agora mesmo e encontrar esse navio imundo. Você precisa voltar para o forte antes que comecem a procurar por você.";
				link.l1.go = "Sergio_16";
			}
			else
			{
				link.l1 = "Bem, era só isso que eu precisava saber. Tenho que levantar âncora agora mesmo se não quiser sair procurando essa tal de 'Consunção' pelo Novo Mundo inteiro. Enquanto isso, você pode estudar isto.";
				link.l1.go = "Sergio_17";
			}
		break;
		
		case "Sergio_16":
			dialog.text = "Boa sorte, capitão! Não se preocupe comigo – o mais importante é impedir isso, pelo menos por um tempo. Te desejo sorte!";
			link.l1 = "Meus canhões são o melhor remédio contra doenças e maldade. Juro que todos os prisioneiros estarão em terra antes do amanhecer – e o navio do Juan vai repousar no fundo do mar!";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_17":
			RemoveItems(PChar, "letter_consumption", 1);
			Log_Info("You have given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "O que é isso? Aqui está o nome do coronel e um monograma 'J'? Incrível! Onde você conseguiu isso?";
			link.l1 = "É melhor você não saber disso, mas confio que vai usar essa informação da melhor forma possível.";
			link.l1.go = "Sergio_18";
		break;
		
		case "Sergio_18":
			dialog.text = "Eu juro por tudo que é sagrado! O coronel vai para a forca antes do fim do mês! Eu mesmo vou cuidar disso!";
			link.l1 = "Receio que isso acabe em uma punição disciplinar, que, pelo que vejo, não será a primeira na vida dele. Talvez fosse melhor atirar nesse canalha? É um remédio bem eficaz... Preciso ir agora – não quero deixar a 'Consumo' esperando.";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_19":
			DialogExit();
			AddQuestRecord("Consumption", "11");
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption5.win_condition.l1 = "location";
			pchar.quest.Consumption5.win_condition.l1.location = "Trinidad";
			pchar.quest.Consumption5.function = "Consumption_CreateJuan";
			pchar.quest.Consumption6.win_condition.l1 = "HardHour";
			pchar.quest.Consumption6.win_condition.l1.hour = 13;
			pchar.quest.Consumption6.function = "Consumption_FailJuan";
			// Сержио теперь наш друг и будет торговать смолами
			SetFunctionTimerCondition("Oil_PrepareSergio", 0, 0, 20, false); // таймер
		break;
		
		// генератор торговли смолами
		case "Sergio_20":
			dialog.text = "Oh, que encontro de sorte! Señor "+GetFullName(pchar)+"! Que bom te ver!";
			link.l1 = "Senhor Sergio! Não esperava te encontrar! Como vai? E o velho comandante, como está?";
			link.l1.go = "Sergio_21";
		break;
		
		case "Sergio_21":
			dialog.text = "Estou bem, e o senhor comandante foi para as minas de Los-Teques – suas trapaças imundas com Juan Consumption foram descobertas.";
			link.l1 = "Minas?! Santo Deus! Nunca imaginei que a justiça seria feita no caso dele...";
			link.l1.go = "Sergio_22";
		break;
		
		case "Sergio_22":
			dialog.text = "Ah, se ao menos fosse isso, capitão... Ele só foi transferido e rebaixado. Agora serve na guarnição, e nem sequer perdeu o posto de oficial. Bem, pelo menos San Jose se livrou desse canalha.";
			link.l1 = "Bem, até agora tudo certo. Mas eu esperava mais.";
			link.l1.go = "Sergio_23";
		break;
		
		case "Sergio_23":
			dialog.text = "Eu também... Mas vamos esquecer esse canalha – ele não merece nem ser mencionado. Señor, assim que soube que seu navio estava prestes a entrar no porto, corri até o cais o mais rápido que pude. Tenho uma proposta para você.";
			link.l1 = "Sério? Estou ouvindo.";
			link.l1.go = "Sergio_24";
		break;
		
		case "Sergio_24":
			dialog.text = "Capitão, você parece ser um homem de confiança. Outra coisa muito importante é que você é "+GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"")+" e você tem seu próprio navio. Sugiro que façamos um acordo comercial.";
			link.l1 = "Parece interessante! Que tipo de acordo?";
			link.l1.go = "Sergio_25";
		break;
		
		case "Sergio_25":
			dialog.text = "É melhor conversarmos sobre isso em outro lugar – no farol, na cabana do guardião. Ele é um velho amigo meu, confio nele. Venha ao farol de San Jose hoje ou amanhã. Estarei esperando por você lá. Tenho certeza de que vai achar minha proposta muito interessante!";
			link.l1 = "Está certo, senhor Sergio. Te vejo lá!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Oil_SergioRuntoMayak");
		break;
		
		case "Sergio_26":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Oil_SetSergioToMayakOver.over = "yes"; //снять прерывание
			dialog.text = "Bem-vindo novamente, senhor. Deixe-me lhe explicar essa situação. ";
			link.l1 = "Pode falar, estou ouvindo. ";
			link.l1.go = "Sergio_27";
		break;
		
		case "Sergio_27":
			dialog.text = "As you may already know, I am not only a soldier, but also a doctor. Why? Because I am a well-educated man. My education kept me from wasting my time here on women and drink. Instead, I have organised several expeditions and managed to find a deposit of resin not far from here\nThis is a resource of strategic importance; this island is the only place where you can find the special resin used to build solid and lasting vessels\nA governor and a commandant ordered me to sell all the resin to the Spanish navy\nThe problem is, they pay me only half its market price and I can't sell it anywhere else. Therefore, I offer you the chance to buy it from me. It is a very important commodity and very hard to come by.";
			link.l1 = "Quais são os termos do nosso acordo? ";
			link.l1.go = "Sergio_28";
		break;
		
		case "Sergio_28":
			dialog.text = "De acordo com meus cálculos, consigo coletar 60 barris por mês sem levantar suspeitas. Vamos fazer um trato – no quinto dia de cada mês, venho a este farol tomar um drink com meu amigo. Apareça se quiser comprar a resina. Dez dobrões de ouro por barril.\nVocê paga pelo lote inteiro e leva tudo de uma vez. Sem pressão, a decisão é sua. Então, temos um acordo?";
			link.l1 = "Parece um baita negócio pra mim! Claro, tá fechado!";
			link.l1.go = "Sergio_29";
		break;
		
		case "Sergio_29":
			dialog.text = "Maravilha. Então, no quinto dia de cada mês, vou beber uma garrafa de vinho das Canárias com meu velho amigo, o dono, e nós vamos esperar por você.";
			link.l1 = "Certo. Vamos fazer assim.";
			link.l1.go = "Sergio_30";
		break;
		
		case "Sergio_30":
			dialog.text = "Fico feliz que tenhamos chegado a um acordo. Até mais, capitão!";
			link.l1 = "Boa sorte no seu negócio de resina, señor!";
			link.l1.go = "Sergio_31";
		break;
		
		case "Sergio_31":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			pchar.questTemp.OilTrade = "true";
			pchar.quest.Oil_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.Oil_fail.win_condition.l1.character = "Sergio";
			pchar.quest.Oil_fail.function = "Oil_TradeFail";
			AddQuestRecordInfo("Unique_Goods", "4");
		break;
		
		case "oil_trade":
			dialog.text = "Olá, senhor capitão! Veio buscar um lote de resina, imagino.";
			link.l1 = "Isso mesmo, senhor Sergio. Está tudo pronto?";
			link.l1.go = "oil_trade_1";
			link.l2 = "Senhor Sergio, não estou com disposição para negociar. Talvez mais tarde.";
			link.l2.go = "oil_trade_exit";
		break;
		
		case "oil_trade_exit":
			DialogExit();
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "oil_trade_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeOil"))
			{
				dialog.text = "Sim. Você tem 2550 doblões com você?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Claro. Aqui está.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "Que azar! Deixei o dinheiro no meu navio. Vou trazer aqui imediatamente!";
					link.l1.go = "oil_trade_exit";
				}
			}
			else
			{
				dialog.text = "Sim. Você tem seiscentos doblões com você?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Claro. Aqui está.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "Que azar! Deixei o dinheiro no meu navio. Vou trazer aqui imediatamente!";
					link.l1.go = "oil_trade_exit";
				}
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && !CheckAttribute(pchar, "questTemp.SergioOilBlock")) // увеличить объём поставок смолами
			{
				link.l4 = "Senhor Sergio, quero comprar mais resina. Você poderia fornecer lotes, digamos, cinco vezes maiores?";
				link.l4.go = "UpgradeOil";
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && CheckAttribute(pchar, "questTemp.SergioOilPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок смолами, если в первый раз не принесли
			{
				link.l4 = "Aqui está, como prometido, Señor Sergio, três mil doblões, conforme pediu. Tenho certeza de que, com sua visão e meu investimento, este empreendimento trará um bom lucro para nós dois.";
				link.l4.go = "UpgradeOil_Agreed";
			}
		break;
		
		case "oil_trade_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) RemoveDublonsFromPCharTotal(2550);
			else RemoveDublonsFromPCharTotal(600);
			PlaySound("interface\important_item.wav");
			dialog.text = "É um prazer fazer negócio com você, capitão. Meus homens vão ajudar a carregar os barris no seu navio.";
			link.l1 = "Obrigado!";
			link.l1.go = "oil_trade_3";
		break;
		
		case "oil_trade_3":
			dialog.text = "O acordo ainda está de pé. Se precisar de outro lote, volte daqui a um mês.";
			link.l1 = "Certo, Sergio. Até mais.";
			link.l1.go = "oil_trade_4";
		break;
		
		case "oil_trade_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) AddCharacterGoods(pchar, GOOD_OIL, 300);
			else AddCharacterGoods(pchar, GOOD_OIL, 60);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.SergioOil = sti(pchar.questTemp.SergioOil) + 1; // счётчик покупок
		break;
		
		case "UpgradeOil":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Senhor"+GetSexPhrase("","ita")+", seu interesse em comprar mais resina realmente demonstra confiança no nosso negócio. No entanto, há uma complicação\nCom volumes maiores, aumenta o risco de chamar a atenção das autoridades da ilha, e controlar esses carregamentos exige pessoas e medidas de segurança, que, admito, não são baratas. Se você estiver disposto a acrescentar três mil dobrões ao preço, em um pagamento único, vou contratar gente de confiança para proteger a carga e evitar vazamentos de informação. Assim, nossa rota ficará mais segura e poderei lhe fornecer trezentos barris de resina por mês. Para compensar seu investimento, vou lhe oferecer, como comprador de atacado, um desconto de quinze por cento em todos os envios futuros.";
				link.l1 = "Três mil doblões para garantir as remessas? Señor Sergio, não vou esconder, esse preço me parece inacreditável – como se estivesse propondo uma conspiração no Escorial, e não apenas protegendo uma carga de piche!";
				link.l1.go = "UpgradeOil_1";
				Notification_Skill(true, 80, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Senhor"+GetSexPhrase("","ita")+", agradeço seu interesse, mas negócios desse porte exigem experiência e cautela. Para ser sincero, seu nível em assuntos de comércio ainda não é suficiente para lidar com esse volume. Recomendo que adquira um pouco mais de experiência e volte a me procurar quando estiver pronto para cargas maiores. Aí sim, talvez possamos discutir o assunto com mais profundidade.";
				link.l1 = "Muito bem. Voltaremos a essa questão depois.";
				link.l1.go = "oil_trade_exit";
				Notification_Skill(false, 80, SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeOil_1":
			dialog.text = "Senhor"+GetSexPhrase("","ita")+", Eu entendo sua preocupação. Mas você sabe que segurança nunca sai barato, ainda mais com mercadorias tão raras. Além disso, não estou apenas garantindo sigilo total, mas também oferecendo um desconto que vai compensar seu investimento com o tempo. Não é um acordo razoável?";
			link.l1 = "Eu admito: no nosso ramo, confiança e discrição têm seu preço, e o desconto torna nosso possível acordo um pouco mais atraente. Mas ainda assim, três mil dobrões é uma quantia exagerada. Será que você não pode baixar um pouco esse valor?";
			link.l1.go = "UpgradeOil_2";
		break;
		
		case "UpgradeOil_2":
			dialog.text = "Lamento, mas medidas pela metade são inaceitáveis em assuntos assim. Ou garantimos proteção total, ou arriscamos tudo. O valor continua o mesmo, e só assim posso garantir confiança e discrição. Você não gostaria que toda a frota real viesse atrás de mim, e depois de você, não é?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Muito bem, Señor Saldo, você me convenceu. Segurança e confiança valem o preço. Três mil dobrões. Aqui está.";
				link.l1.go = "UpgradeOil_Agreed";
			}
			link.l2 = "Senhor Saldo, você me convenceu da necessidade dessas medidas. No entanto, três mil dobrões é uma quantia considerável, e eu não tenho esse dinheiro agora. Vou ter que esperar até juntar o valor necessário.";
			link.l2.go = "UpgradeOil_4";
			link.l3 = "Por esse dinheiro, daria para subornar uma frota inteira e todos os soldados do continente, quanto mais contratar guardas para uma carga modesta de piche! Me desculpe, mas não posso aceitar essa proposta. Vamos deixar tudo como está, sem exageros nem gastos desnecessários.";
			link.l3.go = "UpgradeOil_3";
		break;
		
		case "UpgradeOil_Agreed":
			dialog.text = "Muito bem, senhor, vejo que nossa confiança é mútua. Fique tranquilo: tudo será providenciado direitinho. Agora, aos detalhes: 300 barris de resina, como de costume, estarão esperando por você aqui no farol de Trinidad todo dia 5 de cada mês. Você pode comprar o lote inteiro por 2550 doblões.";
			link.l1 = "Excelente, Señor Sergio. Não me decepcione.";
			link.l1.go = "UpgradeOil_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "4_1");
			pchar.questTemp.UpgradeOil = true;
			pchar.questTemp.SergioOilBlock = true;
			DeleteAttribute(pchar, "questTemp.SergioOilPotom");
		break;
		
		case "UpgradeOil_Agreed_1":
			dialog.text = "Não tenha dúvida, señor"+GetSexPhrase("","ita")+". Tudo será organizado no mais alto nível, e nosso esforço conjunto dará frutos.";
			link.l1 = "Até mais.";
			link.l1.go = "oil_trade_exit";
		break;
		
		case "UpgradeOil_3":
			DialogExit();
			pchar.questTemp.SergioOilBlock = true;
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "UpgradeOil_4":
			dialog.text = "Volte quando tiver o valor completo. Vou ficar feliz em fazer um novo acordo com você.";
			link.l1 = "Certo.";
			link.l1.go = "oil_trade_exit";
			pchar.questTemp.SergioOilBlock = true;
			pchar.questTemp.SergioOilPotom = true;
		break;
	// <-- генератор смол
		
		case "Juan_abordage":
			dialog.text = "Quem diabos é você!?";
			link.l1 = "Meu nome é "+GetFullName(pchar)+", quanto a você, Consumption, o diabo está te esperando – e logo vai levar sua alma!";
			link.l1.go = "Juan_abordage_1";
		break;
		
		case "Juan_abordage_1":
			if (CheckAttribute(pchar, "questTemp.Consumption.House"))
			{
				dialog.text = "Este navio está prestes a explodir – o estopim já está queimando no paiol – por que nós dois deveríamos morrer? Vamos baixar as espadas. Você vai ter tempo suficiente pra sair, e eu pulo no mar – Galera Point está logo ali, dá pra ir cuspindo. Se quiser ouro, pode pegar! Quinhentos dobrões, dinheiro na mão – e você esquece de mim, e eu esqueço de você! Fechado?";
				link.l1 = "Ouro? Eu não comecei tudo isso por dinheiro, Juan, mas para acabar com a escória, e você é o maior prêmio de todos.";
				link.l1.go = "Juan_abordage_2";
				link.l2 = "Quinhentos dobrões? Você tá tirando com a minha cara, Consumption. Aposto que você escondeu pelo menos o dobro disso aqui... Me dá mil agora mesmo e pode ir pro inferno, senão...";
				link.l2.go = "Juan_abordage_3";
			}
			else
			{
				dialog.text = "O navio está prestes a explodir, então terei uma boa companhia. O que acha?";
				link.l1 = "Você fala demais, Consumption, vai direto ao ponto!";
				link.l1.go = "Juan_abordage_5";
			}
		break;
		
		case "Juan_abordage_2":
			dialog.text = "Poderíamos ter chegado a um acordo... Ah, deixa pra lá!";
			link.l1 = "Você tirou essas pessoas pobres de suas celas, e elas não puderam nem resistir nem fugir. Você é um covarde, Consumption, e vai morrer como um covarde agora.";
			link.l1.go = "Juan_abordage_5";
		break;
		
		case "Juan_abordage_3":
			dialog.text = "Você tem um bom faro para negócios, amigo... Aqui - é tudo o que eu tenho. Não é grande coisa para uma vida, não é mesmo?";
			link.l1 = "Sua vida não vale nem uma bala, então parece que esse é o negócio mais lucrativo da minha vida. Agora suma daqui.";
			link.l1.go = "Juan_abordage_4";
			TakeNItems(pchar, "gold_dublon", 1000);
			Log_Info("You received 1000 doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			OfficersReaction("bad");
			pchar.questTemp.Consumption.TakeMoney = "true"; //атрибут для диалога
		break;
		
		case "Juan_abordage_4":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "ConJuan_AfterFight_1", 10.0);
		break;
		
		case "Juan_abordage_5":
			dialog.text = "É uma pena que você não vai ter tempo de salvar todo mundo e ainda me matar, não é? O pavio está queimando, e o tempo está acabando...";
			link.l1 = "Droga! Eu preciso tirar essas pessoas daqui... Cai fora, lixo – você vai receber o que merece mais cedo ou mais tarde!";
			link.l1.go = "Juan_abordage_4";
			link.l2 = "Vou tentar mesmo assim...";
			link.l2.go = "Juan_abordage_6";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
			sld = GetCharacter(NPC_GenerateCharacter("ConAndjelo", "citiz_9", "man", "man", 5, SPAIN, -1, true, "quest"));
			sld.name = "Angelo";
			sld.lastname = "";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
		break;
		
		case "Juan_abordage_6":
			//LAi_SetCurHPMax(NPChar);
			//LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("ConJuan_AfterFight_2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Consumption.KillJuan = "true"; //атрибут для диалога
		break;
		
		case "Waitress":
			dialog.text = "Ah... Estou sem palavras... Que pesadelo!";
			link.l1 = "Infelizmente, não pude fazer nada. Me desculpe, moça. Adeus.";
			link.l1.go = "Waitress_1";
		break;
		
		case "Waitress_1":
			DialogExit();
			AddQuestRecord("Consumption", "16");
			AddQuestUserData("Consumption", "sSex", GetSexPhrase("",""));
			Consumption_Close();
		break;
		
		case "Waitress_2":
			dialog.text = "Inacreditável! Você... você realmente salvou ele? Eu nem sei como te agradecer.";
			if (CheckAttribute(npchar, "quest.Consumption.sex"))
			{
				link.l1 = "Posso imaginar isso, beleza. Mas minha parte do acordo já está feita – só falta uma coisinha.";
				link.l1.go = "Waitress_3";
			}
			link.l2 = "O dever chamou – e eu agi. Só isso.";
			link.l2.go = "Waitress_5";
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan")) AddQuestRecord("Consumption", "18");
			else AddQuestRecord("Consumption", "17");
		break;
		
		case "Waitress_3":
			dialog.text = "Eu... ai meu Deus! Você está certo. Por ele, como prometi... Suba para o quarto – não temos muito tempo.";
			link.l1 = "Então vamos logo!";
			link.l1.go = "Waitress_4";
		break;
		
		case "Waitress_4"://благодарность натурой
			DialogExit();
			LocatorReloadEnterDisable("PortSpein_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("PortSpein_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "PortSpein_tavern_upstairs", "goto", "goto3", "ConsumptionSexWaitress", -1);
			pchar.questTemp.Consumption.Sex = "true";
		break;
		
		case "Waitress_sex":
			dialog.text = "Aqui estou eu, meu bravo caballero! E veja só o que eu trouxe comigo.";
			link.l1 = "Olha só, estou impressionada, vamos abrir aquele vinho de cereja! Depois a gente pode abrir outra coisa... Hoje é seu dia de sorte, afinal... Ha-ha!";
			link.l1.go = "Waitress_sex_1";
		break;
		
		case "Waitress_sex_1":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;
		
		case "Waitress_5":
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
			{
				dialog.text = "Você é um verdadeiro cavaleiro! Caballero! Aqui - não leve isso como ofensa, mas quero que fique com isto. Juntei esse dinheiro para resgatar Angelo, mas agora isso já não importa! Por favor, não recuse - aceite!";
				link.l1 = "Bem, vou me lembrar dos seus olhos, señorita – eles ficam muito mais bonitos quando brilham com lágrimas de felicidade, e não de dor. Aceito seu presente. Adeus, e boa sorte para você e para Angelo.";
				link.l1.go = "Waitress_6";
				AddMoneyToCharacter(pchar, 5000);
			}
			else
			{
				dialog.text = "Você é um verdadeiro cavaleiro! Caballero! Vou contar para todos! Sempre vou me lembrar de você!";
				link.l1 = "Bem, e eu vou me lembrar dos seus olhos, señorita – eles ficam muito mais bonitos quando brilham com lágrimas de felicidade, e não de dor. Que você seja sempre feliz. Adeus!";
				link.l1.go = "Waitress_6";
			}
		break;
		
		case "Waitress_6":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			Consumption_Close();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
