void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bug. Avise a gente.";
			link.l1 = "Claro!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "FalseTrace":
			DelMapQuestMarkCity(pchar.questTemp.FalseTrace.StartCity);
			dialog.text = "Boa tarde, capitão... ehm... kha-hahrm! Malditas minas... Deixe-me apresentar. Adam Rayner. Sou um homem simples e não gosto de rodeios, então vou direto ao ponto. Quer ganhar um bom dinheiro? Tenho um negócio para te propor, algo que nenhum de nós conseguiria sozinho.";
			link.l1 = "Hein! Dinheiro fácil? Interessante. Estou ouvindo, Adam.";
			link.l1.go = "FalseTrace_1";
			link.l2 = "Sabe, me desculpe, mas você não me parece confiável. Então não vou fazer negócio com você.";
			link.l2.go = "FalseTrace_exit";
		break;
		
		case "FalseTrace_exit":
			dialog.text = "Confiável? Ha-ha! Não se deve julgar um homem pela cara. Bom, deixa pra lá. Você acabou de perder uma boa chance de ganhar dinheiro fácil e rápido. Vou encontrar alguém mais disposto...";
			link.l1 = " Nossa conversa terminou, senhor. Adeus! ";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_exit_1":
			DialogExit();
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "questTemp.FalseTrace");
		break;
		
		case "FalseTrace_1":
			//выбираем целевой пункт
			switch (hrand(2))
			{
				case 0: 
					pchar.questTemp.FalseTrace.DayQty = 18;
					pchar.questTemp.FalseTrace.TargetCity = "Beliz";
					pchar.questTemp.FalseTrace.TargetShore = "Shore8";
				break;
				case 1: 
					pchar.questTemp.FalseTrace.DayQty = 22;
					pchar.questTemp.FalseTrace.TargetCity = "Marigo";
					pchar.questTemp.FalseTrace.TargetShore = "Shore41";
				break;
				case 2: 
					pchar.questTemp.FalseTrace.DayQty = 20;
					pchar.questTemp.FalseTrace.TargetCity = "Santodomingo";
					pchar.questTemp.FalseTrace.TargetShore = "Mayak8";
				break;
			}
			pchar.questTemp.FalseTrace.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.FalseTrace.Mation = sti(npchar.nation);
			dialog.text = "Kha! Prazer fazer negócios com alguém tão esperto quanto você, Capitão. Então, o serviço é simples: tem um fluyt carregado com uma boa quantidade de prata e ele logo vai zarpar de um dos portos daqui. Só um navio, sem escolta. Meio tolo, não acha? K-kha\n Moleza. Eu te digo onde e quando, você pega o prêmio e eu fico com a minha parte.";
			link.l1 = "E claro, você quer receber em dinheiro agora, não é?";
			link.l1.go = "FalseTrace_2";
		break;
		
		case "FalseTrace_2":
			dialog.text = "Eu pareço algum bandido patético, capitão? De jeito nenhum. Vou me juntar a você nessa invasão e vamos fazer isso juntos. Não vou ficar no porão durante a luta, muito pelo contrário – peço que me coloque no grupo de abordagem como seu oficial, temporariamente, é claro\nEu sei o que faço, sei esfaquear e atirar nas pessoas. Então vou arriscar meu pescoço como você... khe... kha! Você me paga minha parte depois que capturarmos o fluyt.";
			link.l1 = "Que parte do saque você quer para si?";
			link.l1.go = "FalseTrace_3";
		break;
		
		case "FalseTrace_3":
			dialog.text = "Não sou um homem ganancioso, capitão. Minha parte é só o que couber no porão do meu velho batel, e isso dá mais ou menos 200 fardos de prata. Pelo que sei, não vai ter menos de 2.000 fardos de prata no fluyt, então vou ficar com um décimo. É justo, não acha?";
			link.l1 = "Dez por cento do saque só por uma informação? Eu compro esse tipo de coisa de bêbado por um copo de rum na taverna do porto. Não, não vamos juntos, amigo!";
			link.l1.go = "FalseTrace_4";
			link.l2 = "Hm. Acho que concordo. Aceito sua proposta, Adam. Bem-vindo a bordo. Agora, sobre sua informação: de onde, para onde, quando, nome do navio?";
			link.l2.go = "FalseTrace_5";
		break;
		
		case "FalseTrace_4":
			dialog.text = "Que pão-duro você é, Capitão! Nesse caso, não vai ganhar nada! Até mais!";
			link.l1 = "Boa sorte! Procure outro tolo para o seu esquema suspeito!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_5":
			dialog.text = "O nome do fluyt é o "+pchar.questTemp.FalseTrace.ShipName+", ela parte de Cartagena e zarpa "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". Não temos muito tempo, porém. Duas semanas, três no máximo. Se não a encontrarmos em três semanas, acabou.";
			link.l1 = "Então não vamos perder tempo! A aventura nos chama!";
			link.l1.go = "FalseTrace_6";
		break;
		
		case "FalseTrace_6":
			DialogExit();
			NextDiag.CurrentNode = "FalseTrace_officer";
			DelLandQuestMark(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			AddQuestRecord("FalseTrace", "1");
			AddQuestUserData("FalseTrace", "sCity1", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen"));
			AddQuestUserData("FalseTrace", "sCity2", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity));
			AddQuestUserData("FalseTrace", "sShip", pchar.questTemp.FalseTrace.ShipName);
			//установим таймер на генерацию энкаунтера
			pchar.quest.False_Trace_2.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.False_Trace_2.function = "CreateFalseTraceGaleonOnMap";
			SetFunctionTimerCondition("FalseTraceGaleonOver", 0, 0, sti(pchar.questTemp.FalseTrace.DayQty)+2, false);//таймер
		break;
		
		case "FalseTrace_officer":
			dialog.text = "Queria alguma coisa, capitão?";
			link.l1 = "Nada, deixa pra lá.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FalseTrace_officer";
		break;
		
		case "FalseTrace_7":
			chrDisableReloadToLocation = true;
			dialog.text = "Queria falar comigo, Capitão?";
			link.l1 = "Acho que você já esperava por isso... Cadê a prata, droga? Onde está? Estou falando com você! O capitão do fluyt me disse que era um navio de abastecimento! Você mentiu pra mim!";
			link.l1.go = "FalseTrace_8";
		break;
		
		case "FalseTrace_8":
			dialog.text = "Calma, Capitão. Vou tentar explicar tudo.";
			link.l1 = "Claro que vai! Já me acalmei! A única razão de você não estar pendurado no mastro agora é porque ainda não entendi seus motivos. Você perseguiu esse fluyt comigo, sabendo o tempo todo que não havia prata. Então, por favor, se explique.";
			link.l1.go = "FalseTrace_9";
		break;
		
		case "FalseTrace_9":
			dialog.text = "Sim, eu realmente te enganei, Capitão. Mas era o único jeito de te convencer a fazer o que eu precisava, capturar... khe kha! Capturar esse maldito fluyt\nMas eu prometo que vou te pagar o que devo. Agora deixa eu te contar por que fiz isso. Você encontrou uma mulher no fluyt? Eu vi uns tripulantes levando ela para o seu navio...";
			link.l1 = "Hm... Então, você precisava da garota? E foi por isso que me obrigou a começar uma batalha naval e matar tanta gente!?";
			link.l1.go = "FalseTrace_10";
		break;
		
		case "FalseTrace_10":
			dialog.text = "É minha esposa. Katerine Rayner. Ela fugiu de mim há três meses com esse capitão patético. Fiz de tudo para encontrá-los, e consegui. Os dois estavam indo para "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". Eu não poderia imaginar uma maneira melhor de trazer Katerine de volta e lidar com aquele ladrão de esposas\nSe eu te dissesse a verdade, você teria ido embora. Então eu precisei te contar uma história suculenta sobre um fluyt carregado de prata.";
			link.l1 = "Hmpf... Sua esposa te deixou, não foi? Que interessante!";
			link.l1.go = "FalseTrace_11";
		break;
		
		case "FalseTrace_11":
			dialog.text = "Esta é minha esposa legítima, eu a amo e ninguém mais tem o direito de ficar com ela! Aquele canalha encheu a cabeça dela com lindas mentiras sobre romance e todas essas bobagens enquanto eu estava... longe. Você não conhece as mulheres? Ela acreditou nessas besteiras, coitada, e fugiu com ele.";
			link.l1 = "Certo, olha, eu não me importo com a sua vida de família, então resolva isso com a sua esposa. Mas você falou em cobrir meus custos, não foi? Eu entendi direito?";
			link.l1.go = "FalseTrace_12";
		break;
		
		case "FalseTrace_12":
			if (pchar.basenation == SPAIN || pchar.basenation == HOLLAND)
			{
				pchar.questTemp.FalseTrace.QuestCity = "Portobello";
				pchar.questTemp.FalseTrace.QuestShore = "Shore48";
			}
			else
			{
				pchar.questTemp.FalseTrace.QuestCity = "SantaCatalina";
				pchar.questTemp.FalseTrace.QuestShore = "Shore54";
			}
			dialog.text = "Sim, você me ouviu direito, capitão. Um favor por outro. Não tenho dinheiro agora, mas se você levar a Katerine e a mim para "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", eu vou te dar uma informação totalmente confiável sobre onde você pode conseguir um pouco de ouro sem nenhum esforço.";
			link.l1 = "Muito interessante. E por que você não pode me contar essa informação totalmente confiável agora?";
			link.l1.go = "FalseTrace_13";
		break;
		
		case "FalseTrace_13":
			dialog.text = "Porque eu ainda não tenho essa informação. Deixe-me explicar em detalhes. Um certo cavalheiro de fortuna chamado Solly Vesgo – já ouviu falar dele? – está planejando saquear algumas minas de ouro não muito longe de Blueweld\nPor causa de certos acontecimentos, ele vai ter que deixar todo o ouro escondido em algum lugar e colocar alguns guardas para proteger o tesouro. O próprio Solly vai seguir a pé até Belize ou Blueweld para arranjar um navio\nTenho um informante entre os homens do Solly, ele vai me esperar em "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+". Assim que lançarmos âncora lá, ele vai me contar onde o Solly esconde os tesouros dele\nVocê vai até lá, elimina os guardas e pega todo o ouro pra você. Eu mesmo faria isso, mas considerando a situação, vou deixar tudo nas suas mãos. Sem cobrar nada.";
			link.l1 = "Sua história parece muito com aquela sua fábula anterior sobre um fluyt carregado de prata. Você já me enganou uma vez. Como posso ter certeza de que não está mentindo de novo?";
			link.l1.go = "FalseTrace_14";
		break;
		
		case "FalseTrace_14":
			dialog.text = "Dou-lhe minha palavra. Não tenho nenhuma outra garantia. Mas é verdade, eu juro khe... kha... malditas minas!";
			link.l1 = "Certo. Agora vá, e eu vou pensar no que você disse.";
			link.l1.go = "FalseTrace_15";
		break;
		
		case "FalseTrace_15":
			dialog.text = "Não pense demais. Solly Vesgo vai voltar para pegar seus tesouros, como você deve saber. Pelas minhas contas, você só tem duas semanas para chegar até "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+".";
			link.l1 = "Vou me lembrar disso. Agora vá para os alojamentos da tripulação e junte-se aos marinheiros. Acho melhor você ficar separado da sua esposa até chegarmos ao nosso destino. Pode ir agora.";
			link.l1.go = "FalseTrace_16";
		break;
		
		case "FalseTrace_16":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.FalseTrace = "TalkCabinWoman";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "TalkSelf_Quest", 3.0);
			SetFunctionTimerCondition("FalseTraceSollyOver", 0, 0, 15, false);//таймер
			AddQuestRecord("FalseTrace", "5");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_17":
			dialog.text = "Chamou por mim, capitão?";
			link.l1 = "Sim. Adam Rayner, vou te prender e trancar. Você me enganou, e não me resta outra opção a não ser te isolar e entregar às autoridades.";
			link.l1.go = "FalseTrace_18";
		break;
		
		case "FalseTrace_18":
			dialog.text = "Sério? Eu já esperava isso de você, Capitão. Principalmente depois que foi até o porão conversar com aquele sujeito imundo que vive roubando as esposas dos outros. Então decidiu ficar do lado dele, não foi, Capitão?";
			link.l1 = "Isso não te diz respeito. Você me usou, me passou para trás, e agora está tentando me enganar de novo com essas histórias absurdas de tesouros! Contramestre, tire ele daqui!";
			link.l1.go = "FalseTrace_19";
		break;
		
		case "FalseTrace_19":
			dialog.text = "Kha, não tão rápido, Capitão... O contramestre e o resto da sua tripulação não vão conseguir entrar aqui tão cedo. Não percebeu que tranquei a porta? Agora estamos a sós aqui – só eu e você. Então me mostre, Capitão, do que você é capaz!";
			link.l1 = "Sério? Você realmente acha que tem alguma chance?! Você vai se arrepender disso, seu desgraçado!";
			link.l1.go = "FalseTrace_20";
		break;
		
		case "FalseTrace_20":
			DialogExit();
			NextDiag.currentnode = "FalseTrace_21";
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetHP(npchar, 100+MOD_SKILL_ENEMY_RATE*35, 100+MOD_SKILL_ENEMY_RATE*35); // belamour с 40 хп боец из него никудышный
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "FalseTrace_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_21":
			dialog.text = "";
			link.l1 = "Assim está melhor... Abaixe as armas, canalha! Contramestre! Prenda esse patife e jogue-o no porão!";
			link.l1.go = "FalseTrace_22";
		break;
		
		case "FalseTrace_22":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			bQuestDisableMapEnter = false;
			RemovePassenger(Pchar, npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.questTemp.FalseTrace.PrisonerAdamIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			LAi_SetPlayerType(pchar);
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, CIRASS_ITEM_TYPE);
			sld = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerIDX)];
			ReleasePrisoner(sld); //освободили пленника
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			DeleteAttribute(sld, "LifeDay") //постоянный персонаж
			GiveItem2Character(sld, "blade_10");
			EquipCharacterbyItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");//патроны не даю - все одно для антуражу
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			AddComplexSelfExpToScill(40, 40, 40, 40);
			AddQuestRecord("FalseTrace", "11");
			AddQuestUserData("FalseTrace", "sShore", XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen"));
			pchar.questTemp.FalseTrace = "AdamPrisoner";
		break;
		
		case "FalseTrace_23":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Obrigado, Capitão, por ajudar a trazer minha esposa de volta! Adam Rayner lhe deve uma, não vai esquecer disso, ha-ha, eu juro por... kha! Malditas minas! Agora, sobre o Solly Vesgo. Meu homem já me contou tudo. Solly deixou todo o saque numa gruta na baía de San Juan del Norte. O próprio está em Blueweld agora\nÉ melhor se apressar, você só tem cinco dias, segundo meu camarada. Leve seus homens com você, os bandidos do Solly são duros, vão te dar trabalho\nHora de me despedir. Obrigado de novo, Capitão, boa sorte!";
			link.l1 = "Boa sorte pra você, Adam. Não vá ofender sua esposa!";
			link.l1.go = "FalseTrace_Remove_exit";
			SetFunctionTimerCondition("FalseTraceBonanzaOver", 0, 0, 5, false);//таймер
			pchar.quest.False_Trace_4.win_condition.l1 = "location";
			pchar.quest.False_Trace_4.win_condition.l1.location = "Shore55";
			pchar.quest.False_Trace_4.function = "FalseTrace_SollyBonanza";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddQuestRecord("FalseTrace", "14");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_24":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Ha! Por que diabos, Capitão, viemos parar nesta baía? Eu te disse que meu homem estava me esperando no porto de "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"! Você está pensando em ir até lá a pé pela selva?";
			link.l1 = "Errou feio, Adam. Você achou mesmo que eu cairia nas suas mentiras de novo? Acha que sou idiota? Desta vez, eu fiz um acordo com a sua esposa.";
			link.l1.go = "FalseTrace_25";
		break;
		
		case "FalseTrace_25":
			dialog.text = "O quê?! Ha! Que tipo de acordo com a minha esposa? Do que você está falando, seu peixe podre?!";
			link.l1 = "Por causa das suas informações erradas, capturei um fluyt vazio e matei o capitão dele. Me arrependo disso, embora agora seja tarde demais para arrependimentos. Pelo que entendi, sua esposa era apaixonada por aquele marinheiro. Por isso ela me pediu para te matar. É por isso que estamos aqui nesta baía agora.";
			link.l1.go = "FalseTrace_26";
		break;
		
		case "FalseTrace_26":
			dialog.text = "Não acredito! Katerine... que desgraçada! Olha, ainda vai ter o que merece... E então, como ela prometeu te pagar, otário? Ela não tem um tostão, vendeu até as joias pra fugir com aquele capitão!";
			link.l1 = "Isso não é da sua conta, canalha. Mas está na hora de terminar nossa conversa. Vou te mandar para o inferno, onde você já devia estar faz tempo!";
			link.l1.go = "FalseTrace_27";
		break;
		
		case "FalseTrace_27":
			dialog.text = "Vamos ver do que você é capaz, seu peixe podre!";
			link.l1 = "...";
			link.l1.go = "FalseTrace_28";
		break;
		
		case "FalseTrace_28":
			DialogExit();
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_AdamDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_abordage":
			dialog.text = "Ah! Por que diabos você atacou meu navio, seu canalha? Eu não consigo entender...";
			link.l1 = "Não finja ser um cordeiro, capitão. Eu sei muito bem que tipo de carga você está transportando. Eu preciso dela.";
			link.l1.go = "FalseTrace_abordage_1";
		break;
		
		case "FalseTrace_abordage_1":
			dialog.text = "Carga? Ha-ha! Que tipo de carga você esperava encontrar aqui? Meus porões estão vazios!";
			link.l1 = "O que você disse, canalha! Repete isso!";
			link.l1.go = "FalseTrace_abordage_2";
		break;
		
		case "FalseTrace_abordage_2":
			dialog.text = "Eu repito - não tenho nenhuma carga a bordo. Este fluyt é um navio de abastecimento indo para "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+" levar uma carga de balas de canhão e mantimentos para as tropas.";
			link.l1 = "Você está tentando me enganar. Seus porões devem estar cheios de prata. E eu vou verificar, assim que terminarmos essa conversa...";
			link.l1.go = "FalseTrace_abordage_3";
		break;
		
		case "FalseTrace_abordage_3":
			dialog.text = "Eu não sei quem te contou sobre a prata. Mas isso é um completo absurdo... Eu perdi pra você, então estou desistindo. Aqui está minha espada. Agora pode ir e conferir os porões. Eles estão vazios.";
			link.l1 = "Desistir? Não! Não preciso de testemunhas. Pegue sua espada e lute, ou eu te abro como um carneiro.";
			link.l1.go = "FalseTrace_abordage_4";
			link.l2 = "Que bom que você mostrou juízo. Acho que vou conseguir um resgate por você... Ei, pessoal – joguem o capitão no porão!";
			link.l2.go = "FalseTrace_abordage_5";
		break;
		
		case "FalseTrace_abordage_4":
			DialogExit();
			pchar.questTemp.FalseTrace.KillCaptain = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "FalseTrace_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "FalseTrace_abordage_5":
			DialogExit();
			pchar.questTemp.FalseTrace.CapPrisoner = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FalseTrace_AfterFight", 3.0);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "FalseTrace_wife":
			dialog.text = "Você matou ele, seu canalha! Patife! Pobre "+pchar.questTemp.FalseTrace.CapName+"!";
			link.l1 = "O que é isso? De onde você veio, querido?";
			link.l1.go = "FalseTrace_wife_1";
		break;
		
		case "FalseTrace_wife_1":
			dialog.text = "Você vai queimar no inferno por tudo o que fez. Maldito seja!";
			link.l1 = "Calma, mocinha! Não force a sorte me xingando – ou te mando atrás do seu capitão!";
			link.l1.go = "FalseTrace_wife_2";
		break;
		
		case "FalseTrace_wife_2":
			dialog.text = "Você... você não teria coragem de levantar a mão contra uma mulher!";
			link.l1 = "Nem vou precisar disso. Posso atirar em você. Ou simplesmente te jogar ao mar, e os tubarões fazem o resto... Então, o que está esperando? Vá para o meu navio. Não tenha medo – não vou deixar ninguém te machucar, e eu mesmo não vou encostar em você se ficar quieto...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_3":
			DialogExit();
			pchar.quest.False_Trace_AfterBattle.over = "yes";
			pchar.quest.FalseTraceGaleonOver.over = "yes";
			if (CheckAttribute(pchar, "questTemp.FalseTrace.CapPrisoner")) AddQuestRecord("FalseTrace", "");
			else AddQuestRecord("FalseTrace", "");
			sld = characterFromId("Mugger");
			DeleteAttribute(sld, "HalfImmortal");
			RemovePassenger(Pchar, sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DoQuestCheckDelay("LAi_EnableReload", 4.0);
			bQuestDisableMapEnter = true;
			pchar.questTemp.FalseTrace = "TalkCabin";
			AddQuestRecord("FalseTrace", "4");
		break;
		
		case "FalseTrace_wife_4":
			dialog.text = "O que... o que você vai fazer com ele?";
			link.l1 = "O que é isso? De onde você veio, querido?";
			link.l1.go = "FalseTrace_wife_5";
		break;
		
		case "FalseTrace_wife_5":
			dialog.text = "Pobre "+pchar.questTemp.FalseTrace.CapName+"! Me diga - você vai matar ele? Não...";
			link.l1 = "Escute aqui, moça – se eu quisesse matá-lo, já teria feito isso. Ele vai ficar trancado no porão, e depois eu decido se solto ele ou peço resgate... a segunda opção é mais provável. Agora, seja boazinha e suba no meu navio. Não tenha medo – não vou deixar ninguém te machucar, e eu mesmo não vou encostar em você se ficar quieta...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_6":
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "O que você quer de mim? Vai me jogar pros tubarões, como disse que faria? Você acabou com a minha vida e eu...";
				link.l1 = "Vamos lá, querido. Ninguém vai te jogar em lugar nenhum. Só quero esclarecer a situação, já que ataquei esse fluyt por sua causa e não por outro motivo.";
				link.l1.go = "FalseTrace_wife_7";
			}
			else
			{
				dialog.text = "O que você quer de mim? Onde está "+pchar.questTemp.FalseTrace.CapName+"? Resgate? Você precisa de um resgate?";
				link.l1 = "Certo, moça, vamos acabar com essa enxurrada de perguntas inúteis. Não te chamei aqui pra isso. Um fato já ficou claro, e acho que você vai achar interessante.";
				link.l1.go = "FalseTrace_wife_20";
			}
		break;
		
		case "FalseTrace_wife_7":
			dialog.text = "Por minha causa? Você está dizendo que a culpa é minha por terem atacado nosso navio e matado meu amado? Coitado "+pchar.questTemp.FalseTrace.CapName+", o que ele fez com você? Você vai prestar contas a Deus por tudo o que fez...";
			link.l1 = "O mesmo ensopado de sempre! Vamos voltar à nossa conversa sobre tubarões?";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_8"://ноды пересечения - старт
			dialog.text = "";
			link.l1 = "Quieto agora? Ótimo. Agora me escuta! Ataquei o navio porque soube que ele carregava uma boa carga de prata. E essa informação veio do Adam Rayner.";
			link.l1.go = "FalseTrace_wife_9";
		break;
		
		case "FalseTrace_wife_9":
			dialog.text = "Ah! O quê?! Adam? Onde ele está? Ele está aqui?";
			link.l1 = "Vejo que você conhece o nome... Katerine. E, como pode perceber, já sei tudo sobre você. Imagino que Adam Rayner seja seu marido, não é?";
			link.l1.go = "FalseTrace_wife_10";
		break;
		
		case "FalseTrace_wife_10":
			dialog.text = "Sim. Eu sou a esposa desse monstro. Achei que esse pesadelo finalmente tinha acabado... Ele te contratou para me encontrar?";
			link.l1 = "De modo geral, foi assim mesmo. Adam mentiu pra mim sobre a prata, só pra eu capturar o fluyt '"+pchar.questTemp.FalseTrace.ShipName+"Com certeza, ele estava decidido a trazer você de volta. Há cerca de quinze minutos, ele me explicou todas as suas ações.";
			link.l1.go = "FalseTrace_wife_11";
		break;
		
		case "FalseTrace_wife_11":
			dialog.text = "E... o que ele quer? O que ele te disse?";
			link.l1 = "Ele quer que a esposa legítima volte para ele. Vai me dar informações sobre o ouro do Solly Vesgo como compensação por ter me enganado. E eu vou levar vocês dois para "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+".";
			link.l1.go = "FalseTrace_wife_12";
		break;
		
		case "FalseTrace_wife_12":
			dialog.text = "Não... (chorando) Eu não quero voltar praquele canalha! Fiz um esforço enorme pra fugir dele e apagar meus rastros, mas ele me achou mesmo assim... Patife! Bandido! Maldito ladrão!";
			link.l1 = "Calma, Katerine... Modere as palavras. Ele é seu marido, afinal. E ele disse que te ama.";
			link.l1.go = "FalseTrace_wife_13";
		break;
		
		case "FalseTrace_wife_13":
			dialog.text = "(chorando) Meu marido? Você sabe quem é meu marido? Ele é um ex-prisioneiro, um condenado, e agora o bandido mais cruel de "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen")+"! Ele é um animal asqueroso, imundo, e pra ele eu não passo de um buraco entre as pernas pra foder!";
			link.l1 = "Você já não tinha visto tudo isso antes de se casar com ele?";
			link.l1.go = "FalseTrace_wife_14";
		break;
		
		case "FalseTrace_wife_14":
			dialog.text = "No começo, ele era diferente... E o passado dele me parecia tão romântico... Mas com o tempo, tudo mudou. Eu nem quero mais ver esse homem, quanto mais viver com ele, você não entende? Eu não quero! Principalmente depois desse ataque ao fluyt, que foi ele quem planejou!";
			link.l1 = "Hm... O que eu faço com você, então, minha doce dama?";
			link.l1.go = "FalseTrace_wife_15";
		break;
		
		case "FalseTrace_wife_15"://ноды пересечения - конец
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "O que fazer? Eu sei o que fazer. Você é um instrumento do pecado, graças às ações do meu marido. Você matou um homem inocente, o único que já me tratou bem. Redima-se dos seus pecados, capitão. Mate o Adam. Bem na minha frente. Quero ver esse verme morrer, quero cuspir no cadáver dele\nQuando ele estiver morto, eu te conto onde ele esconde os tesouros dele. O idiota bêbado já me falou do esconderijo uma vez, haha, ele nem lembra disso!";
				link.l1 = "Heh! Você é uma mulher cruel, Katherine, pelo que vejo!";
				link.l1.go = "FalseTrace_wife_16";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.FalseTrace.CapName+"... O capitão do fluyt. Você o trancou. Fale com ele, por favor! Ele vai te oferecer algo pela nossa vida e liberdade! Ele vai pensar em alguma solução! Eu... Eu não quero voltar para Adam, daqui pra frente "+pchar.questTemp.FalseTrace.CapName+" é meu marido! Eu imploro – não me leve de volta para Adam, para aquele monstro!";
				link.l1 = "Hm. Interessante. E o que o meu prisioneiro poderia me oferecer? Posso conseguir um resgate por ele com as autoridades, e ainda vou ficar com o ouro do Solly Vesgo...";
				link.l1.go = "FalseTrace_wife_21";
			}
		break;
		
		case "FalseTrace_wife_16":
			dialog.text = "Olha só quem fala de crueldade. Navegue até "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", faça o que o Adam mandou, só não desembarque no porto, mas sim na baía mais próxima. Nós três vamos até lá e você mata aquele desgraçado\nQuando terminar, eu te conto sobre o esconderijo. Juro, não estou mentindo. Acho que você confia mais na minha palavra do que na do Adam—ele já te enganou uma vez, não foi? E então, capitão?";
			link.l1 = "É... Não é à toa que dizem que marido e mulher são mesmo farinha do mesmo saco. Olho pra você, Katerine, e vejo que você é a cara-metade perfeita pro Adam... Se você quer tanto a morte dele, podia muito bem enfiar uma faca nele enquanto dorme bêbado... Contramestre! Leve ela daqui!";
			link.l1.go = "FalseTrace_wife_17";
			link.l2 = "Eu odeio canalhas que tentam me enganar e me usar para seus próprios fins. Tudo bem, Katherine, aceito sua proposta, já que está claro pra mim que o Adam não é confiável. Mas se você também me trair, juro que te encontro até na Europa, e coloco uma bala na sua cabeça. Agora suma daqui. Contramestre! Leve ela embora!";
			link.l2.go = "FalseTrace_wife_19";
		break;
		
		case "FalseTrace_wife_17":
			dialog.text = "Você vai se arrepender disso... Eu juro, eu ...";
			link.l1 = "Contramestre! Vigie ela e não tire os olhos dela até chegarmos em "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
		break;
		
		case "FalseTrace_wife_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "6");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_19":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "7");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForKillAdam");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_20":
			dialog.text = "Que fato? O que você vai fazer com a gente? Por que capturou nosso navio?";
			link.l1 = "Vai me deixar falar ou quer que eu mande meu contramestre calar sua boca com uma mordaça?!";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_21":
			dialog.text = "O ouro do Solly? Você realmente confia nesse canalha? Ele vai te enganar de novo, é o que ele faz! Fale com seu prisioneiro!\n"+pchar.questTemp.FalseTrace.CapName+" é um verdadeiro cavalheiro, ele nunca quebra a palavra e jamais mentiria para você!";
			link.l1 = "Você não me convenceu, senhora. Não tenho nada para tratar com o seu capitão. Vou conseguir um resgate por ele, e vou pegar o ouro do Solly com o Adam. Se o Adam me enganar de novo, eu vou encontrá-lo até nos confins do mundo, e ele vai amaldiçoar o dia em que nasceu... Contramestre! Tire ela daqui!";
			link.l1.go = "FalseTrace_wife_23";
			link.l2 = "Para ser sincera, não confio no Adam... Odeio ser manipulada. Tudo bem, vou falar com seu capitão e ver o que ele tem a me dizer. Pode ir agora... Contramestre! Leve ela daqui!";
			link.l2.go = "FalseTrace_wife_24";
		break;
		
		case "FalseTrace_wife_23":
			dialog.text = "Você é um homem cruel e sem coração! Eu juro que eu...";
			link.l1 = "Contramestre! Vigie ela e não tire os olhos dela o tempo todo até chegarmos a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "8");
			chrDisableReloadToLocation = false;
			pchar.questTemp.FalseTrace.Prisoner = "true";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_25":
			dialog.text = "Acabou agora... Pobre "+pchar.questTemp.FalseTrace.CapName+" está vingado, e agora posso respirar aliviada e me chamar de viúva...";
			link.l1 = "Cumpri minha parte do acordo, Katerine. Agora é a sua vez.";
			link.l1.go = "FalseTrace_wife_26";
		break;
		
		case "FalseTrace_wife_26":
			dialog.text = "Claro, capitão. Meu marido—graças a Deus, agora ex-marido—era um bandido, como você já sabe. Temendo possíveis buscas, ele não guardava o saque em casa. Ele organizou um esconderijo—mas acabou deixando escapar algo sobre isso certa vez. Ainda assim, ele escondeu de um jeito muito esperto—não há acesso a esse lugar pela costa.";
			link.l1 = "Muito interessante... E onde está?";
			link.l1.go = "FalseTrace_wife_27";
		break;
		
		case "FalseTrace_wife_27":
			dialog.text = "Em uma pequena ilha perto de Hispaniola. No farol.";
			link.l1 = "Farol de Port-au-Prince! Fica na ilha!";
			link.l1.go = "FalseTrace_wife_28";
		break;
		
		case "FalseTrace_wife_28":
			dialog.text = "Provavelmente sim. Você vai encontrar o tesouro lá. Vai ver. É só isso. Adeus, Capitão.";
			link.l1 = "Espere... Me perdoe, Katerine, se puder. Espero que a morte de quem causou todos os seus sofrimentos traga algum alívio, pelo menos. Sinto muito de verdade...";
			link.l1.go = "FalseTrace_wife_29";
		break;
		
		case "FalseTrace_wife_29":
			dialog.text = "Não preciso da sua pena, Capitão. Você fez o que pedi – e eu contei tudo o que queria saber. Agora vá, me deixe sozinho com minha dor...";
			link.l1 = "Tchau, Katherine.";
			link.l1.go = "FalseTrace_wife_30";
		break;
		
		case "FalseTrace_wife_30":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15);
			LAi_LocationDisableOfficersGen(pchar.questTemp.FalseTrace.QuestShore, false);//офицеров пускать
			//LAi_LocationDisableOfficersGen("Mayak7", true);//офицеров не пускать
			locations[FindLocation("Mayak7")].DisableEncounters = true;//энкаунтеры закрыть
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.False_Trace_7.win_condition.l1 = "location";
			pchar.quest.False_Trace_7.win_condition.l1.location = "Mayak7";
			pchar.quest.False_Trace_7.function = "FalseTrace_AdamTreasure";
			AddQuestRecord("FalseTrace", "23");
		break;
		
		case "FalseTrace_wife_31":
			dialog.text = "Canalha imundo! Ele conseguiu matar todos os quatro! Inacreditável!";
			link.l1 = "Não esperava por essa, Katerine? Eu sou difícil de matar. Você joga dos dois lados muito bem, devo admitir!";
			link.l1.go = "FalseTrace_wife_32";
		break;
		
		case "FalseTrace_wife_32":
			dialog.text = "Você matou meu homem. Acha mesmo que eu ia deixar você continuar vivo?! Achou que a morte do Adam ia me satisfazer? Não! Você não vai sair daqui. Tem um navio não muito longe desta ilha, ele vai afundar seu barco velho junto com você!\nAgora, faça o que quiser comigo.";
			link.l1 = "Eu não te disse, querido, que você perderia a cabeça se me enganasse? Que diabo astuto! Morto, você vai ser bem menos perigoso. Essa cabecinha bonita vai levar uma bala agora mesmo...";
			link.l1.go = "FalseTrace_wife_33";
			link.l2 = "Sinto pena de você, Katerine. Esse seu desejo de vingança não te trouxe nada de bom no fim das contas. Vou te deixar aqui, entregue ao seu destino – você vai ficar nesta ilha. Acho que os pescadores locais logo vão te encontrar e levar para Hispaniola. E que o Senhor nos julgue por tudo o que fizemos...";
			link.l2.go = "FalseTrace_wife_35";
		break;
		
		case "FalseTrace_wife_33":
			dialog.text = "É você quem deveria rezar, monstro! Assassino! Socorro! Vai se f...";
			link.l1 = "Já ouvi o suficiente.";
			link.l1.go = "FalseTrace_wife_34";
		break;
		
		case "FalseTrace_wife_34":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
			LAi_ActorAnimation(pchar, "shot", "FalseTrace_CaterinaKilled", 1.0);
		break;
		
		case "FalseTrace_wife_35":
			dialog.text = "Que você se afogue! Que seu navio se quebre nas rochas! Que você...";
			link.l1 = "Tchau, Katherine.";
			link.l1.go = "FalseTrace_wife_36";
		break;
		
		case "FalseTrace_wife_36":
			DialogExit();
			sld = characterFromID("FalseTraceWife"); 
			sld.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "goto", "goto33", "none", "", "", "", -1);
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("Mayak7", false);//офицеров пускать
			locations[FindLocation("Mayak7")].DisableEncounters = false;//энкаунтеры открыть
			AddQuestRecord("FalseTrace", "25");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
		break;
		
		case "FalseTrace_Bandits":
			dialog.text = "A-ah, aqui está o assassino do Adam! Katherine estava certa, esse desgraçado veio roubar o esconderijo!";
			link.l1 = "O quê? Katherine? Quem é você?";
			link.l1.go = "FalseTrace_Bandits_1";
		break;
		
		case "FalseTrace_Bandits_1":
			dialog.text = "Quem somos nós? Somos amigos de Adam Rayner, que foi assassinado por você. Ele era o líder da nossa irmandade. Agora eu sou o líder, meu nome é "+GetFullName(npchar)+", e eu vou te punir por matar meu chefe e pela violência que você cometeu contra a esposa dele.";
			link.l1 = "Violência? Que diabos você está falando?";
			link.l1.go = "FalseTrace_Bandits_2";
		break;
		
		case "FalseTrace_Bandits_2":
			dialog.text = "Você apunhalou o Adam pelas costas, seu traidor imundo. Forçou a esposa dele a contar onde ele escondia o ouro, e depois largou a pobre mulher para morrer numa praia deserta.\nMas ela sobreviveu. Ela nos pediu ajuda, pediu justiça. Estamos esperando por você há dias. E aqui está você, seu desgraçado!";
			link.l1 = "Ha-ha! Isso é bem a cara da Katerine... Agora escuta, eu realmente matei o Adam, é verdade, mas fiz isso porque a própria esposa dele me pediu. Foi vingança pela morte do amante dela. Ela me contou onde estava o esconderijo como pagamento...";
			link.l1.go = "FalseTrace_Bandits_3";
		break;
		
		case "FalseTrace_Bandits_3":
			dialog.text = "Não fale mal da pobre viúva, seu lixo! Por que ela viria até nós, então? Ela mesma ofereceu que ficássemos com todo o ouro em troca da sua vida. Ela não quer moedas, ela quer a sua morte! Uma morte justa pela morte do marido dela!\nMas eu juro, ela não vai morrer na miséria, isso é tão certo quanto meu nome é "+GetFullName(npchar)+", e que chegou a sua hora de morrer, covarde!";
			link.l1 = "Santo inferno, que discurso glorioso. Ah, lá está ela, ansiosa pra assistir essa comédia de perto... Senhores?";
			link.l1.go = "FalseTrace_Bandits_4";
		break;
		
		case "FalseTrace_Bandits_4":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Adam_bandit_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_BanditsAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_Remove1":
			dialog.text = "Você é mesmo um desastrado, capitão! Perder um fluyt carregado de prata... Foi um erro confiar em você. Adeus!";
			link.l1 = "Adeus, Adam.";
			link.l1.go = "FalseTrace_Remove2";
		break;
		
		case "FalseTrace_Remove2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 15);
		break;
		
		case "FalseTrace_Remove_exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "FalseTraceWife_Remove", 15);
		break;
		
		case "FalseTrace_Remove2":
			dialog.text = "Eu te avisei, capitão, nós só tínhamos duas semanas! Agora, o Solly Vesgo já deve ter levado todo o saque. Não é culpa minha se você é tão enrolado. Adeus!";
			link.l1 = "É, foi culpa minha. Adeus, espero que a gente não se encontre de novo, você só me traz azar.";
			link.l1.go = "FalseTrace_Remove_exit";
		break;
		
		case "FalseTrace_Solly":
			dialog.text = "Hein! Finalmente! Já estamos cansados de esperar, e esses malditos mosquitos... Espera... Cadê o Solly? Não entendi...";
			link.l1 = "Solly não vai aparecer aqui. Eu ajo em nome dele... Então ou você me entrega o ouro, ou já pode se considerar morto.";
			link.l1.go = "FalseTrace_Solly_1";
		break;
		
		case "FalseTrace_Solly_1":
			dialog.text = "Argh! Vamos ver! Comigo, rapazes! Às armas!";
			link.l1 = "Que jeito idiota de morrer, venham logo, abutres!";
			link.l1.go = "FalseTrace_Solly_2";
			AddDialogExitQuestFunction("FalseTrace_SollyBonanzaAdd");
		break;
		
		case "FalseTrace_Solly_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("FTEnemy_crew_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_SollyAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_GoldShip":
			dialog.text = "Você cumpriu sua parte do acordo, capitão. Obrigado por confiar em mim. Não se preocupe com o Adam, eu vou levá-lo ao lugar certo. Ele vai receber o que merece.";
			link.l1 = "Não me importo com o Adam. E a sua promessa sobre aquele navio?";
			link.l1.go = "FalseTrace_GoldShip_1";
		break;
		
		case "FalseTrace_GoldShip_1":
			if (sti(pchar.basenation == HOLLAND) || sti(pchar.basenation == SPAIN))
			{
				pchar.questTemp.FalseTrace.ShipNation = ENGLAND;
				pchar.questTemp.FalseTrace.ShipCity = "PortRoyal";
			}
			else
			{
				pchar.questTemp.FalseTrace.ShipNation = SPAIN;
				pchar.questTemp.FalseTrace.ShipCity = "Maracaibo";
			}
			dialog.text = "Sim, sim, claro. Vamos ver, contando a partir de hoje... Isso... Daqui a 12-14 dias "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" um galeão pesado carregado de minério de ouro partirá para a Europa. Ele será escoltado apenas por uma fragata ou corveta\nEntão prepare-se, é um prêmio valioso, mas não é presa fácil. Ainda assim, tenho certeza de que você vai conseguir, afinal você me derrotou sem muita dificuldade... Você deve alcançar "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" em duas semanas e prepare uma emboscada\nLembre-se de que seu alvo é um galeão pesado acompanhado por um único navio de escolta. É só isso, eu acho. O resto está em suas mãos.";
			link.l1 = "Entendi... Bem, "+pchar.questTemp.FalseTrace.CapName+", adeus. Talvez eu devesse lhe desejar sorte e uma vida feliz com Katerine? Espero que vocês dois fiquem bem. É uma pena que tenhamos nos conhecido em circunstâncias tão tristes.";
			link.l1.go = "FalseTrace_GoldShip_2";
		break;
		
		case "FalseTrace_GoldShip_2":
			dialog.text = "Obrigado, capitão. Como já disse antes, você tem uma certa nobreza. Espero que perceba que agir com honestidade traz mais lucro do que atos desonrosos. Dedique-se a servir sua nação, e você se tornará um grande oficial naval.";
			link.l1 = "Vou pensar no que você disse. Bem, até logo por enquanto!";
			link.l1.go = "FalseTrace_GoldShip_3";
		break;
		
		case "FalseTrace_GoldShip_3":
			DialogExit();
			locations[FindLocation(pchar.questTemp.FalseTrace.TargetShore)].DisableEncounters = false; //энкаутеры открыть
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "FalseTraceDouble_Remove", -1);
			pchar.quest.False_Trace_6.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_6.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_6.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.False_Trace_6.function = "CreateFalseTraceGoldShipOnMap";
			AddQuestRecord("FalseTrace", "19");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen"));
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
