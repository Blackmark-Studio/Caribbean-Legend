void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "O que você quer?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		// Квест "Путеводная звезда"
		// Этап 0, ПРОЛОГ
		case "PZ_Alonso_1":
			dialog.text = "Peço desculpas por invadir seus aposentos, Senhor Capitão, mas isso é muito importante.";
			link.l1 = "Espero que sim, Alonso. Se cada um de vocês começar a entrar aqui como se fosse a própria casa, vamos ter um problema. Então, o que está acontecendo?";
			link.l1.go = "PZ_Alonso_2";
		break;
		
		case "PZ_Alonso_2":
			dialog.text = "Encontramos o seu armário todo revirado.";
			link.l1 = "O quê?! Espere aí... Como você descobriu isso? E o que todos vocês estavam fazendo na minha cabine?";
			link.l1.go = "PZ_Alonso_3";
		break;
		
		case "PZ_Alonso_3":
			dialog.text = "De vez em quando, a gente limpa seus aposentos quando você está fora – seja na cidade ou descansando nos beliches. Nunca percebeu? Ou só esqueceu mesmo?";
			link.l1 = "Ah, é verdade. Bem, você já pode ir.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Tichingitu_1":
			dialog.text = "Capitão Charles, olha! Alguém estava mexendo na sua gaveta grande.";
			link.l1 = "O quê? Quando você percebeu isso? Sabe quem foi?";
			link.l1.go = "PZ_Tichingitu_2";
		break;
		
		case "PZ_Tichingitu_2":
			dialog.text = "Não faz muito tempo, quando eu estava vindo te ver. Os espíritos não dizem quem pode ser.";
			link.l1 = "Foi um bom detalhe, Tichingitu. Agora, com licença, preciso verificar se está faltando alguma coisa.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Duran_1":
			dialog.text = "Ei, Capitão, o que você está olhando? Alguém mexeu nas suas coisas. Até eu percebi.";
			link.l1 = "Não foi você? Afinal, eu não te pago tão generosamente quanto o François.";
			link.l1.go = "PZ_Duran_2";
		break;
		
		case "PZ_Duran_2":
			dialog.text = "Heh, se eu fosse o ladrão, não ia te contar, ia? Eu pegaria os objetos de valor e sumiria sem deixar rastro. Essa bagunça não é do meu jeito.";
			link.l1 = "Odeio admitir, mas você está certo. Bem, Claude, guarde suas provocações para depois. Preciso ver o que o ladrão levou.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Folke_1":
			dialog.text = "Capitão, percebi hoje que alguém revirou seu armário. Não percebeu?";
			link.l1 = "O quê? Eu não fico checando o cofre o tempo todo, Folke, e nem estou sempre na cabine. Fala a verdade – foi você? Você aprontou de novo e pegou mais empréstimos no banco da última vez que a gente pisou em terra?";
			link.l1.go = "PZ_Folke_2";
		break;
		
		case "PZ_Folke_2":
			dialog.text = "De jeito nenhum, Capitão. Não tenho nada seu nos meus bolsos ou no meu armário. E nunca vou ter.";
			link.l1 = "Eu realmente espero que não. Pode ir - vou verificar o que está faltando.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_OsmatrivaemKautu":
			DialogExit();
			AddDialogExitQuestFunction("PZ_OsmatrivaemSunduk_0");
		break;
		
		case "PZ_LigaInJungle_1":
			dialog.text = "Charles de Maure, certo?";
			link.l1 = "Pela sua cara, eu diria que você já sabe a resposta. Então, o que você quer?";
			link.l1.go = "PZ_LigaInJungle_2";
		break;
		
		case "PZ_LigaInJungle_2":
			dialog.text = "Sua cabeça.";
			link.l1 = "Fascinante! Preciso dizer, gosto de como essa conversa está começando. Mas antes de irmos mais longe, poderia ao menos me dizer a quem eu ofendi? Talvez possamos negociar.";
			link.l1.go = "PZ_LigaInJungle_3";
		break;
		
		case "PZ_LigaInJungle_3":
			dialog.text = "Não somos amadores, Monsieur de Maure. Mesmo que contássemos, isso não ajudaria em nada – nosso contratante já deixou o Arquipélago. Você não pode feri-lo, nem pedir desculpas. Fomos pagos, e agora é hora de cumprir nossa parte do acordo.";
			link.l1 = "Se você já foi pago, por que derramar mais sangue?";
			link.l1.go = "PZ_LigaInJungle_4";
		break;
		
		case "PZ_LigaInJungle_4":
			dialog.text = "Não somos amadores. Valorizamos nossa reputação.";
			link.l1 = "Receio que desta vez você não vá conseguir corresponder a isso.";
			link.l1.go = "PZ_LigaInJungle_5";
		break;
		
		case "PZ_LigaInJungle_5":
			dialog.text = "Vamos ver isso depois. Revistem o corpo dele quando terminarmos! Queimem tudo o que encontrarem!";
			link.l1 = "Queimar o quê?..";
			link.l1.go = "PZ_LigaInJungle_6";
		break;
		
		case "PZ_LigaInJungle_6":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("LigaInJungle_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_LigaInJunglePosleBitvy");
			
			if (CharacterIsHere("Longway"))
			{
				sld = characterFromId("Longway");
				LAi_SetCheckMinHP(sld, 1, true, "");
			}
		break;
		
		case "PZ_Longway_1":
			dialog.text = "O que o homem mascarado disse... Será que pode ser...?";
			link.l1 = "O que foi, Longway? Não é a primeira vez que caçadores de recompensa vêm atrás de mim, mas você parece especialmente preocupado.";
			link.l1.go = "PZ_Longway_2";
		break;
		
		case "PZ_Longway_2":
			dialog.text = "Longway acha que sabe quem mandou esses homens atrás de você, Meu Senhor Capitão.";
			link.l1 = "Tem algo que eu deva saber?";
			link.l1.go = "PZ_Longway_3";
		break;
		
		case "PZ_Longway_3":
			dialog.text = "Esse é o jeito do Lorde Rodenburg – eliminar quem já o ajudou, mas sabe demais.";
			link.l1 = "Sério... Aquele homem mascarado disse mesmo que o patrão dele saiu do Arquipélago há pouco tempo. Era exatamente o que o Lucas estava planejando! Você acha que devemos esperar mais ataques?";
			link.l1.go = "PZ_Longway_4";
		break;
		
		case "PZ_Longway_4":
			dialog.text = "É sensato estar preparado para qualquer coisa, Meu Senhor Capitão.";
			link.l1 = "Palavras sábias. Seremos sim. Mas o que o Lucas queria? O que ele achava que eu tinha? Alguma ideia, Longway?";
			link.l1.go = "PZ_Longway_5";
		break;
		
		case "PZ_Longway_5":
			dialog.text = "Mm-mm, não, Longway não faz ideia do que pode ser.";
			link.l1 = "Que pena. Mas tudo bem, vamos sair daqui.";
			link.l1.go = "PZ_Longway_6";
		break;
		
		case "PZ_Longway_6":
			DialogExit();
			
			ReturnOfficer_Longway();
			
			chrDisableReloadToLocation = false;
			pchar.questTemp.PZ_RazgovorGerrits = true;
			pchar.questTemp.PZ_PodozrenieLucas = true;
		break;
		
		// Этап 1, ВЕРНЫЙ КЛЯТВЕ
		case "PZ_Longway_11":
			dialog.text = "Senhor Capitão, Longway deseja falar com você. É de grande importância.";
			if (CheckAttribute(pchar, "questTemp.PZ_PodozrenieLucas"))
			{
				link.l1 = "O que foi, Longway? Está preocupado com o jeito que o Lucas se despediu, ou descobriu alguma coisa nova?";
				link.l1.go = "PZ_Longway_12";
				AddCharacterExpToSkill(pchar, "Sneak", 100);
			}
			else
			{
				link.l1 = "Claro! O que você quer saber?";
				link.l1.go = "PZ_Longway_13";
			}
		break;
		
		case "PZ_Longway_12":
			dialog.text = "Infelizmente, não.";
			link.l1 = "Então o que é, Longway?";
			link.l1.go = "PZ_Longway_13";
		break;
		
		case "PZ_Longway_13":
			dialog.text = "Longway não pode dizer. Mas... ele gostaria de pedir permissão para partir.";
			link.l1 = "Sair? Tipo, de vez? Por quê, Longway? Como seu capitão, tenho o direito de saber o motivo.";
			link.l1.go = "PZ_Longway_14";
		break;
		
		case "PZ_Longway_14":
			dialog.text = "É verdade, Meu Senhor Capitão. Mas Longway não é nem trabalhador nem criado. Ele veio ajudar por vontade própria, e pode ir embora do mesmo jeito. Não será para sempre – há um assunto importante a tratar. Longway espera voltar quando tudo estiver resolvido.";
			link.l1 = "O que está acontecendo? Conte-me – se não como seu capitão, então como alguém que já passou por muita coisa ao seu lado.";
			link.l1.go = "PZ_Longway_15";
		break;
		
		case "PZ_Longway_15":
			dialog.text = "Tudo que Longway pode dizer é que fez um juramento – há muito tempo. Chegou a hora de cumpri-lo. Caso contrário... a vida de Longway não faz sentido.";
			link.l1 = "Você está certo, Longway – você não é um prisioneiro, e eu não sou um carcereiro. Você está livre para ir. Que Deus te acompanhe.";
			link.l1.go = "PZ_Longway_Otpustit_1";
			link.l2 = "Você pode ir, mas pelo menos me diga para onde está indo. Posso ajudar sem fazer muitas perguntas.";
			link.l2.go = "PZ_Longway_Pomoch_1";
			link.l3 = "Eu também tenho uma tarefa importante – salvar meu irmão. Para isso, preciso de cada homem, inclusive você, Longway. Não conseguiremos sem você.";
			link.l3.go = "PZ_Longway_NeOtpuskaem_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_1":
			dialog.text = "Não tente apelar para minha piedade ou senso de dever. Eu entendo perfeitamente. Já fez algum juramento, Meu Senhor Capitão?";
			link.l1 = "Claro que sim. Então me conte tudo como é, e meus homens e eu certamente vamos te ajudar.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_2";
		break;
		
		case "PZ_Longway_NeOtpuskaem_2":
			dialog.text = "Longway não pode. Só... não pode. É um grande mistério, e nem é meu para contar.";
			link.l1 = "Que pena. Achei que havia confiança entre nós. Você não vai sair do navio – agora tenho todos os oficiais do meu lado.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_3";
			link.l2 = "Você está certo, Longway – você não é um prisioneiro, e eu não sou um carcereiro. Você está livre para ir. Que Deus te acompanhe.";
			link.l2.go = "PZ_Longway_Otpustit_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_3":
			dialog.text = "Você não pode fazer isso!";
			link.l1 = "Infelizmente, posso sim, Longway. Agora volte ao seu trabalho.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_4";
		break;
		
		case "PZ_Longway_NeOtpuskaem_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition = "PZ_LongwayUhoditOtNasNavsegda";
		break;
		
		case "PZ_Longway_Otpustit_1":
			dialog.text = "Eu não achei que você me deixaria ir tão fácil assim. Obrigado, Senhor Capitão.";
			link.l1 = "Ah, não é nada. Mas me diga – onde posso te encontrar quando terminar seus assuntos?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
		break;
		
		case "PZ_Longway_Pomoch_1":
			dialog.text = "Longway realmente não pode dizer, por mais que quisesse. Mas ele aprecia a disposição do Meu Senhor Capitão em ajudar.";
			link.l1 = "Assim seja. Onde devo procurá-lo quando cumprir seu juramento?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
			pchar.questTemp.PZ_LongwayGood = true;
		break;
		
		case "PZ_Longway_GdeIskat_1":
			dialog.text = "Espero terminar meus negócios em um mês. Depois disso, Longway vai esperar por você por mais uma semana na taverna em Basse-Terre.";
			link.l1 = "Bem, como quiser, meu amigo. Isso não é um adeus. Nos vemos em Basse-Terre.";
			link.l1.go = "PZ_Longway_GdeIskat_2";
		break;
		
		case "PZ_Longway_GdeIskat_2":
			DialogExit();
			
			RemovePassenger(pchar, npchar);
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.location = "None";
			
			SetQuestHeader("PZ");
			AddQuestRecord("PZ", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			SetTimerCondition("PZ_IshemLongway", 0, 0, 30, false);
		break;
		
		case "PZ_SharliePlennik_BadFinal_1":
			dialog.text = "Bem, olá, Capitão.";
			link.l1 = "Não gosto desse seu sorriso, senhor.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_2";
		break;
		
		case "PZ_SharliePlennik_BadFinal_2":
			dialog.text = "Estou arrasado. Vim aqui para dizer que você está finalmente livre. Mas, se quiser ficar mais tempo nesta cabine luxuosa, fique à vontade.";
			link.l1 = "De jeito nenhum. Então, encontraram o Longway? Onde ele está? Em uma das celas?";
			link.l1.go = "PZ_SharliePlennik_BadFinal_3";
		break;
		
		case "PZ_SharliePlennik_BadFinal_3":
			dialog.text = "Em outro mundo parecido com esse - ele não falaria com nenhum de nós e iria direto para a batalha.";
			link.l1 = "Droga! Você podia simplesmente ter capturado ele.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_4";
		break;
		
		case "PZ_SharliePlennik_BadFinal_4":
			dialog.text = "Tem gente que é muito mais fácil matar do que capturar, sabia? Você devia agradecer que não estamos te culpando por nada – seu chinês causou outro massacre, e tivemos que trazer mais unidades com atiradores para dar conta dele.";
			link.l1 = "Sim, de fato. Obrigado por isso.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_5";
		break;
		
		case "PZ_SharliePlennik_BadFinal_5":
			dialog.text = "Falando nisso, já que ele era seu amigo, encontramos uns papéis com ele. Não entendemos o que eram – você provavelmente saberia melhor. Tinha umas coisas escritas que não conseguimos decifrar nas partes que não estavam cobertas de sangue.";
			link.l1 = "Isso é... Merda. Obrigado por devolvê-los. Adeus, oficial.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_6";
		break;
		
		case "PZ_SharliePlennik_BadFinal_6":
			DialogExit();
			
			LAi_ActorGoToLocator(npchar, "goto", "goto22", "", -1);
			DoQuestCheckDelay("PZ_SharliePlennik_BadFinal_2", 3.0);
		break;
		
		case "PZ_BasTerStop":
			dialog.text = "Venha conosco, o Comandante deseja falar com você.";
			link.l1 = "Imagino que isso tenha a ver com minha busca pelo chinês?";
			link.l1.go = "PZ_BasTerStop_2";
		break;
		
		case "PZ_BasTerStop_2":
			dialog.text = "Você vai ver com seus próprios olhos, monsieur.";
			link.l1 = "Estou sendo acusado de alguma coisa?";
			link.l1.go = "PZ_BasTerStop_3";
		break;
		
		case "PZ_BasTerStop_3":
			dialog.text = "De jeito nenhum. Ninguém está tentando prender ou deter você. Por enquanto. Quando eu disse que o Comandante deseja falar com você, foi exatamente isso que eu quis dizer.";
			link.l1 = "Ah, bem...";
			link.l1.go = "PZ_BasTerStop_4";
		break;
		
		case "PZ_BasTerStop_4":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_town")], false);
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto17", "PZ_BasTer_TurmaPriveli");
		break;
		
		case "PZ_BasTer_OtryadPeshera_1":
			dialog.text = "Tem alguma ideia? Esse homem de pele amarela é perigosíssimo. Não somos o primeiro grupo enviado aqui. Ordens são ordens, mas não quero morrer feito idiota entrando sem um plano decente.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				link.l1 = "Ele está sozinho lá dentro, e eu estou com você. Eu cuido dele – vocês se concentrem em me dar cobertura. Nós vamos conseguir.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "Eu tenho uma. Todos vocês vão morrer — bem aqui.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				link.l1 = "Não se preocupe, só vamos conversar com ele.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "Sinto muito, mas todos vocês vão morrer hoje. E não será pelas mãos de um chinês.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_1":
			pchar.questTemp.PZ_Podelnik = true;
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Então você não é um caçador de recompensas... Mas mesmo que seja, é amigo daquele maldito chinês!";
				link.l1 = "Isso mesmo. Eu teria que me livrar de você de qualquer jeito – não faz sentido adiar o inevitável.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "O que você quer dizer?! Você prometeu ajudar!";
				link.l1 = "Acho que você não nos daria uma saída pacífica de qualquer jeito. Não é nada pessoal.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_OtryadPeshera_Kill_3");
		break;
		
		case "PZ_BasTer_OtryadPeshera_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Eu gostaria de acreditar nisso.";
				link.l1 = "Já enfrentei coisa pior. Um chinês não vai ser o nosso fim. Vamos, rapazes!";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "E se a conversa não sair como planejado?";
				link.l1 = "Eu odiaria isso, mas então vou ter que me defender. Vamos.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_3":
			DialogExit();
			
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload2", "PZ_IshemLongway_OtryadUPeshery");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway":
			dialog.text = "Meu Senhor Capitão?! Longway não pode acreditar que você está com eles!";
			link.l1 = "Não, Longway, eu só vim conversar! Não é o que você está pensando!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_2":
			dialog.text = "Então você teria vindo sozinho. Está tentando me fazer baixar a guarda para me atacar com a ajuda desses soldados!";
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayGood"))
			{
				link.l1 = "Se eu pudesse, eu faria. Eu sou o único motivo pelo qual ainda não te atacaram. Fique calmo, vamos conversar, né?";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_3";
			}
			else
			{
				link.l1 = "Chega de conversa fiada! Se eu quisesse, já teria te matado. Abaixe as armas e vamos conversar. Isso é uma ordem do seu capitão.";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_3":
			dialog.text = "Sim. Longway confia em você, Meu Senhor Capitão.";
			link.l1 = "Pronto, assim está melhor. Agora, me diga...";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_4";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_4":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadom_DialogLongway_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_5":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Monsieur, o que está acontecendo? O que é essa... reunião emocionante? Você não deveria nos ajudar a eliminar aquele selvagem chinês?";
				link.l1 = "Sou eu. Vou levá-lo comigo, e toda essa matança vai acabar. Você vai dizer ao comandante que nós o matamos juntos. Combinado?";
				link.l1.go = "PZ_BasTer_SOtryadomOhotnik_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Muito bem, Capitão! Ele largou as armas. É bom ter você conosco. Agora vamos levá-lo ao comandante.";
				link.l1 = "Por que eu faria isso? Paguei uma multa em ouro pelas ações do Longway – e foi generosa. Seus colegas oficiais foram testemunhas – eles podem confirmar. O comandante me autorizou a levar meu homem comigo para o navio.";
				link.l1.go = "PZ_BasTer_SOtryadomDrug_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadomDrug_1":
			dialog.text = "O comandante pode até estar satisfeito com esse ouro manchado de sangue, mas eu não. Alguns dos homens que ele matou naquela maldita caverna eram meus amigos. Além disso, duvido que ele se importe se matarmos o chinês mesmo assim.";
			link.l1 = "Tem certeza que quer descobrir? E sobre seus amigos que foram mortos... já ouviu falar daquele bando ousado de bandidos? Deve ter sido eles.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_2";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_2":
			StartInstantDialog("Longway", "PZ_BasTer_SOtryadomDrug_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_3":
			dialog.text = "";
			link.l1 = "Longway, você não matou tantos soldados quanto dizem, matou?";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_4";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_4":
			dialog.text = "Isso mesmo, Senhor Capitão. Longway viu aquele bando. Eles se esconderam mais fundo na caverna para não serem notados por ele. E Longway ouviu sons de conversa, xingamentos e briga entre os bandidos e os soldados.";
			link.l1 = "";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_5";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_5":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadomDrug_6", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_6":
			dialog.text = "";
			link.l1 = "Viu? Tudo faz sentido. Longway pode ser explosivo, mas é um homem honesto. Estamos indo embora. Se encostarem na gente, vão manchar o uniforme de vocês. Adeus, senhores.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_7";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_7":
			DialogExit();
			
			AddQuestRecord("PZ", "13");
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_CharacterDisableDialog(sld);
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_1":
			dialog.text = "De jeito nenhum, monsieur! Ele matou um monte dos nossos homens, e agora você diz que ele vai sair impune?! Ou você ajuda a gente a matar esse desgraçado, ou pelo menos fica fora do nosso caminho!";
			link.l1 = "Receio que eu precise intervir. Me desculpe, de verdade.";
			link.l1.go = "PZ_BasTer_SOtryadomOhotnik_2";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_CharacterDisableDialog(sld);
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_1":
			dialog.text = "Se você só quisesse conversar, não teria me pedido para largar as armas. Mas um tigre continua sendo um tigre, mesmo com as garras recolhidas. Você já deve ter decidido trair Longway faz tempo—não precisa mentir. Defenda-se, Capitão!";
			link.l1 = "Merda!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_MyUbilLongway_BadFinal");
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Não acredito que conseguimos passar por ele! Mas me diga, por que ele te chamou de Capitão?";
				link.l1 = "É mais complicado do que parece, camarada. Eu precisava tranquilizar seu comandante. O que importa é o resultado, certo? E o resultado é que Longway está morto, e eu te ajudei com isso.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Nem a sua presença ajudou - ele ainda assim nos atacou. Maldito selvagem...";
				link.l1 = "Você não deveria falar dele assim. Ele nos atacou porque estava perturbado e achou que eu estava com você.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Talvez. Nesse caso, adeus, monsieur. Nós mesmos vamos avisar ao comandante que o chinês finalmente morreu.";
				link.l1 = "Muito bem, obrigado. Adeus, rapazes.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Bem, irritado ou não, selvagem ou não, isso não muda nada – ele matou muitos dos nossos antes, foi ele quem derramou sangue primeiro.";
				link.l1 = "Algo deve ter levado ele a esse estado. Mas não vamos nos prender a isso. Eu vou indo, e você pode voltar ao comandante quando achar melhor. Até logo.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_3":
			DialogExit();
			
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			ChangeCharacterNationReputation(pchar, FRANCE, 12);
			AddQuestRecord("PZ", "11");
			CloseQuestHeader("PZ");
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog":
			dialog.text = "Meu Senhor Capitão?";
			link.l1 = "Finalmente! Estive te procurando por toda parte, Longway. Você causou um alvoroço e tanto na cidade. Temos muito o que conversar, então vamos voltar pro navio imediatamente.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_2";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_2":
			dialog.text = "Ali!";
			link.l1 = "Vejo que temos companhia. Parece que vamos nos atrasar um pouco.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_3";
			locCameraFromToPos(-12.27, 1.29, -8.89, true, -3.23, -1.20, -4.77);
			DoQuestCheckDelay("PZ_IshemLongway_SorraKomendant_Dialog_Povernutsya", 1.3);
			
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				LAi_SetHP(sld, 60.0, 60.0);
			}
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_SorraKomendant_Pobeda1");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_4":
			dialog.text = "Tem mais vindo!";
			link.l1 = "Desgraçados teimosos – isso eu admito. Estamos muito expostos aqui. Vamos para a caverna – lá vai ser mais fácil nos defendermos.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_5";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_5":
			DialogExit();
			pchar.questTemp.PZ_IshemLongway_SorraKomendant = true;
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_6":
			dialog.text = "Não podemos ficar aqui para sempre.";
			link.l1 = "E isso é a primeira coisa que você quer dizer depois de tudo que aconteceu, Longway? Não acha que já está na hora de explicar o que está acontecendo?";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_7";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_7":
			dialog.text = "Meu Senhor Capitão, Longway...";
			link.l1 = "Mas você tem razão - não podemos ficar. Vamos embora antes que outra patrulha apareça. Conversamos no navio depois que zarparmos.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_8";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_8":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_1":
			dialog.text = "A astúcia e a maldade do homem branco não conhecem limites.";
			link.l1 = "Ei, eu também sou branco! Além disso, você matou os amigos e companheiros deles — eles têm todo direito de estarem furiosos.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_2";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_2":
			dialog.text = "Você os absolve, Meu Senhor Capitão?";
			link.l1 = "Eu te absolvo, Longway. E peço que não julgue as pessoas pela cor da pele. Você, mais do que ninguém, deveria entender isso. Fomos interrompidos – onde estávamos mesmo...?";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_3";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_3":
			dialog.text = "Capitão! Atrás de você!";
			link.l1 = "Ah, hoje eles não vão nos deixar ter uma conversa decente...";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_4";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_4":
			DialogExit();
			LAi_SetCurHPMax(pchar);
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			
			sld = CharacterFromID("Longway");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=6; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 60.0, 60.0);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya_5");
			
			AddDialogExitQuest("MainHeroFightModeOn"); // Rebbebion, fix
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_6":
			dialog.text = "Entendido, Meu Senhor Capitão.";
			link.l1 = "Isso é bom, mas não vamos ficar aqui. Você e eu temos muito o que conversar. Venha comigo – vamos voltar para o navio.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_7";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_7":
			DialogExit();
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
		
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			AddQuestRecord("PZ", "14");
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			DeleteQuestCondition("PZ_KorablBuhta_BadFinal");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_1":
			dialog.text = "Meu Senhor Capitão, é mesmo você...?";
			link.l1 = "Longway, você está bem?";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_2";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_2":
			dialog.text = "Longway está bem. Obrigado. Mas, Capitão! Olhe!";
			link.l1 = "Corra para a caverna, depressa! É um bom lugar para se defender!";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_3";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_3":
			DialogExit();
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SrazuNashli_4":
			dialog.text = "Longway vai verificar se os soldados ainda estão vindo.";
			link.l1 = "Vamos juntos – não conseguimos segurar a defesa contra toda a guarnição.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_5";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_5":
			dialog.text = "Sim, Meu Senhor Capitão?";
			link.l1 = "Temos muito o que conversar. Agora me siga – precisamos içar a âncora imediatamente.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_6";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_6":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		// Этап 2, СТРАНИЦЫ ИСТОРИИ
		case "PZ_LongwayRazgovorOProshlom":
			dialog.text = "Obrigado mais uma vez por me ajudar, Meu Senhor Capitão. Imagino que tenha muitas perguntas.";
			link.l1 = "Isso é pouco para o que foi. Por que você matou aqueles soldados? Você não mata por prazer — eu sei disso.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_LongwayRazgovorOProshlom_2":
			dialog.text = "Não, Longway não faz isso. Os soldados tentaram impedir Longway, e prisão não era uma opção. Eles não escutariam um chinês—só um homem branco recebe essa consideração.";
			link.l1 = "Eles também nem sempre ouvem outros brancos, mas entendi o seu ponto. Ainda assim, massacrá-los como gado na cidade? O que você estava fazendo em Basse-Terre?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_3":
			dialog.text = "Not only do white people often not listen to me; sometimes they won't even talk. And when they do, it's to call the guards. Longway didn't choose his skin or his eyes, but he's proud of who he is. When soldiers mock and threaten, Longway grows tired... and angry.";
			link.l1 = "De agora em diante, vamos trabalhar juntos. As pessoas falam comigo em vez de chamar os guardas... geralmente. Mas falando sério, me conte sobre sua missão. Deixe-me ajudar você.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_4";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_4":
			dialog.text = "Por favor, Meu Senhor Capitão, entenda Longway. Ele jurou fazer isso sozinho. Não o pressione. Você deve isso a Longway.";
			link.l1 = "Sou realmente grato, mas eu poderia ter lidado com van Merden sozinho naquela época. Porém, estávamos quites desde o começo — você disse que salvei sua pele, e você salvou minha vida. Agora fui eu quem te salvou de novo.";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) link.l1.go = "PZ_LongwayRazgovorOProshlom_5";
			else link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_5":
			dialog.text = "Hmm... você tem razão, Senhor Capitão. Longway acredita que você é seu verdadeiro amigo entre os homens brancos. Uma vez, ele já pensou assim antes, mas estava amargamente enganado. Você se lembra de John Murdock? Johan van Merden?";
			link.l1 = "Que estranho você mencionar van Merden. Recentemente, alguém arrancou algumas páginas do arquivo dele bem debaixo do meu nariz. Isso tem a ver com o seu caso? Você encontrou o ladrão?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_6";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_6":
			dialog.text = "Fui eu. O ladrão era... Longway. Ele sente muito, Senhor Capitão. Naquela época, ele não sabia se podia confiar totalmente em você.";
			if (sti(pchar.reputation.nobility) <= 60)
			{
				link.l1 = "Você fala de amizade, mas me rouba pelas costas? Esta é a primeira e última vez, Longway. Entendeu?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
				Notification_Reputation(false, 61, "low");
			}
			else
			{
				link.l1 = "E como você conseguiu fazer isso, Longway?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_1";
				Notification_Reputation(true, 61, "low");
			}
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_1":
			dialog.text = "Longway entende. Ele fala sério.";
			link.l1 = "Eu espero que sim. Agora me conte como você chegou a essa vida – que promessa fez, quando, e para quem.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_2";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) AddComplexSelfExpToScill(100, 100, 100, 100);
			Notification_Approve(false, "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_2":
			dialog.text = "Sim, Senhor Capitão\nLongway procura a pessoa viva mais importante que lhe resta - Chang Xing.";
			link.l1 = "Chang Xing - ele é seu melhor amigo?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_1":
			dialog.text = "Graças à sua bondade, o resto da tripulação logo se acostumou comigo e começou a confiar em mim.";
			link.l1 = "Entendi. Não é de elogios, mas bom trabalho, Longway... se você limpou a bagunça que sua intromissão deixou.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_2";
			AddComplexLandExpToScill(200, 200, 0);
			pchar.questTemp.PZ_FlagArhiv = true;
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_2":
			dialog.text = "Certo. Mas não temos tempo para isso.";
			link.l1 = "Acho que não. Mas tenta não fazer isso de novo, né? Se precisar de alguma coisa, é só pedir. Pode confiar em mim. Agora, me fala sobre o seu juramento.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_3":
			dialog.text = "É claro, Longway fica feliz em dividir esse fardo com você, Meu Senhor Capitão.\nLongway procura a pessoa viva mais importante que lhe resta — Chang Xing.";
			link.l1 = "Chang Xing - ele é seu melhor amigo?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_7":
			dialog.text = "Chang Xing é da minha família, minha irmã. Ela desapareceu há anos. Para encontrá-la, Longway procura quem possa saber onde ela está.";
			link.l1 = "O que isso tem a ver com o arquivo do van Merden? Tem ligação com o desaparecimento da sua irmã?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_8";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_8":
			dialog.text = "Isso mesmo. Está tudo conectado. Longway e Johan se conheceram há muitos anos, na terra que vocês chamam de Formosa, muito antes de eu chegar ao Arquipélago.";
			link.l1 = "Vocês se conhecem há tantos anos? E van Merden estava envolvido? Que história! Qual era a ligação dele com o desaparecimento da sua irmã?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_9";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_9":
			dialog.text = "Ele me ajudou na minha busca por pessoas muito más — até mesmo pelos padrões dos homens brancos. Oliveiro Fermentelos, Antoon van Diemen e Joep van der Vink.";
			link.l1 = "Pelo nome, um é português, e os outros dois são holandeses.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_10";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_10":
			dialog.text = "Sim, está certo. Mas a busca não teve sucesso. Longway esperou pacientemente pela orientação dos Céus. Então, quando você conseguiu o arquivo de van Merden, decidi estudá-lo. Quando encontrei as primeiras páginas mencionando Oliveiro, arranquei-as e fugi da cabine.";
			link.l1 = "Finalmente tudo faz sentido na história.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_11";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_11":
			dialog.text = "Mas a história em si está só começando. Meu Senhor Capitão, gostaria de ouvir sobre a busca de Longway desde o princípio? Está pronto para sentar e escutar?";
			link.l1 = "É exatamente por isso que eu te chamei para a cabine. Pode falar.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_12";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_12":
			DialogExit();
			
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			DoQuestReloadToLocation("Formosa", "patrol", "patrol1", "PZ_Formosa_Start");
		break;
		
		case "PZ_Formosa_Tavern_1":
			dialog.text = "Chineses não são permitidos aqui. Este é um estabelecimento respeitável, para pessoas respeitáveis — não para gente como você.";
			link.l1 = "Eu só tenho uma pergunta. Deixe-me perguntar, e eu vou embora.";
			link.l1.go = "PZ_Formosa_Tavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_Tavern_2":
			dialog.text = "Aprenda a falar direito primeiro! Eu já disse — gente como você não é bem-vinda aqui.";
			link.l1 = "Onde posso encontrar Oliveiro Fermentelos? Diga-me, e eu seguirei meu caminho.";
			link.l1.go = "PZ_Formosa_Tavern_3";
		break;
		
		case "PZ_Formosa_Tavern_3":
			dialog.text = "Você é surdo também? Não teste a minha paciência, ou logo este lugar inteiro vai feder a tripas amarelas.";
			link.l1 = "Meu povo vive aqui há milhares de anos. Esta é a nossa ilha, e nem podemos entrar numa simples taverna?";
			link.l1.go = "PZ_Formosa_Tavern_4";
		break;
		
		case "PZ_Formosa_Tavern_4":
			dialog.text = "Ah, se achando, é? Por isso aí você pode acabar enforcado. Cai fora!";
			link.l1 = "...";
			link.l1.go = "PZ_Formosa_Tavern_5";
		break;
		
		case "PZ_Formosa_Tavern_5":
			DialogExit();
			locCameraSleep(true);
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("PZ_Formosa_smuggler");
			LAi_CharacterEnableDialog(sld);
			//AddLandQuestMark(sld, "questmarkmain");
			LAi_Fade("PZ_Formosa1_9", "");
		break;
		
		case "PZ_Formosa_smuggler_1":
			dialog.text = "Ouvi falar do seu grande problema, meu pequeno amigo. Você não devia ter feito tanto barulho—nome errado, lugar errado.";
			link.l1 = "Você sabe algo sobre esse homem?! Me diga!";
			link.l1.go = "PZ_Formosa_smuggler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_2":
			dialog.text = "Calma, amigo.";
			link.l1 = "Meus pêsames.";
			link.l1.go = "PZ_Formosa_smuggler_3";
		break;
		
		case "PZ_Formosa_smuggler_3":
			dialog.text = "Eu não quero suas desculpas, mas quero o seu dinheiro. Talvez aí eu te ajude. Eu sou Marcelo Schulte. E você? Tem dinheiro, né?";
			link.l1 = "Meu nome é Chang Tu. Eu tenho dinheiro. Isso basta?";
			link.l1.go = "PZ_Formosa_smuggler_4";
		break;
		
		case "PZ_Formosa_smuggler_4":
			dialog.text = "(assobia) Escudos, pesos, florins, dobrões... e até algumas dessas moedas estranhas que vocês usam. Isso serve. Certo, Chung Chung, vou ver o que consigo descobrir sobre esse homem. Não se preocupe, estou aqui quase todo dia, então seu dinheiro está seguro. Volte sempre, e com certeza a gente se encontra.";
			link.l1 = "Eu espero. Não me resta mais dinheiro...";
			link.l1.go = "PZ_Formosa_smuggler_5";
		break;
		
		case "PZ_Formosa_smuggler_5":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A few days have passed,"+ NewStr() +"April 4, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_tavern", "goto", "goto1", "PZ_Formosa_Spustya4Dnya");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_11":
			dialog.text = "Ah, Chang-Chang! Você já está aqui.";
			link.l1 = "É Chang Tu.";
			link.l1.go = "PZ_Formosa_smuggler_12";
		break;
		
		case "PZ_Formosa_smuggler_12":
			dialog.text = "Não importa, camarada.";
			link.l1 = "Você descobriu onde está o Oliveiro?";
			link.l1.go = "PZ_Formosa_smuggler_13";
		break;
		
		case "PZ_Formosa_smuggler_13":
			dialog.text = "Não, nem faço ideia.";
			link.l1 = "Meu dinheiro!";
			link.l1.go = "PZ_Formosa_smuggler_14";
		break;
		
		case "PZ_Formosa_smuggler_14":
			dialog.text = "Não fique tão nervoso! Eu teria coragem de me aproximar de novo se não tivesse descoberto nada? Vou te apresentar a alguém que sabe das coisas. E olha só, você deu sorte: ele adora gente da Ásia. Tem até criados parecidos com você – até criadas, veja só. Está até aprendendo seu idioma sujo. O nome dele é Johan van Merden. Ele vai te esperar numa casa de dois andares perto da residência.";
			link.l1 = "Meu obrigado.";
			link.l1.go = "PZ_Formosa_smuggler_15";
		break;
		
		case "PZ_Formosa_smuggler_15":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1_back", "PZ_Formosa1_11", -1);
			LAi_ActorGoToLocation(npchar, "goto", "goto3", "", "", "", "", -1);
			npchar.location = "None";
			LocatorReloadEnterDisable("Formosa", "houseSp1", false);
		break;
		
		case "PZ_Formosa_JohanVanMerden_1":
			dialog.text = "Você é Chang Chang, pelo visto? Entre, não tenha vergonha.";
			link.l1 = "É Chang Tu.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2";
			DelLandQuestMark(npchar);
			locCameraFromToPos(-1.91, 2.06, -1.75, true, 2.23, -0.85, 0.85);
		break;
		
		case "PZ_Formosa_JohanVanMerden_2":
			dialog.text = "É mesmo? Me desculpe. Aquele Marcelo e o show de piadas dele... Uma pena que tão poucos se interessem pela sua cultura. E tudo isso só por causa de uma língua diferente, e do formato dos seus olhos. Mas você é inteligente. Diferente do povo negro, hehehe.";
			link.l1 = "(em mandarim) Então o contrabandista não mentiu — você realmente é um homem de cultura. E fala mesmo a nossa língua?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2a";
			link.l2 = "Meu agradecimento pelas palavras gentis sobre minha cultura. Você deve ser Johan van Merden?";
			link.l2.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_2a":
			dialog.text = "Oh... Eu entendi só algumas palavras. Ainda estou aprendendo, sabe. Poderia continuar em holandês?";
			link.l1 = "Como desejar. Você é Johan van Merden?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_3":
			dialog.text = "Sim, Chung Tu, sou eu. Ouvi dizer que você está procurando por Oliveiro Fermentelos. Eu sei onde encontrá-lo, mas antes me diga—por que você o procura? Sua resposta vai determinar a minha.";
			link.l1 = "Ele... sequestrou minha última e mais querida parente — minha irmã, Chang Xing.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_4";
		break;
		
		case "PZ_Formosa_JohanVanMerden_4":
			dialog.text = "Então devo decepcioná-lo, Chang Tu. Provavelmente não há mais esperança para ela agora. É bem provável que tenha sido vendida como escrava para algum fazendeiro rico ou para um bordel. De qualquer forma, você não vai conseguir salvá-la.";
			link.l1 = "Acredito que Chang Xing ainda está viva. Oliveiro pôs os olhos nela. Ela o rejeitou com orgulho. Ele a sequestrou quando eu não estava em casa. E... matou nossos pais.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_5";
		break;
		
		case "PZ_Formosa_JohanVanMerden_5":
			dialog.text = "Eu... sinto muito. Se for esse o caso, Chang Xing—certo?—talvez ainda esteja vivo. Aqui está o que vamos fazer: me dê um tempo para descobrir exatamente onde Oliveiro está agora. Digamos uma semana. Nos vemos de novo então. Me encontre fora dos portões da cidade—quem sabe que olhos estão te seguindo aqui. Não quero me envolver mais do que já estou acostumado, espero que entenda.";
			link.l1 = "Eu... Eu sou profundamente grato a você, Mynheer van Merden. Espero ansiosamente pelo nosso próximo encontro.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_6";
		break;
		
		case "PZ_Formosa_JohanVanMerden_6":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A week has passed,"+ NewStr() +"April 11, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_ExitTown", "goto", "goto3", "PZ_Formosa_Spustya7Dney");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_JohanVanMerden_11":
			dialog.text = "Olá, Chung Tu. Vejo o fogo nos seus olhos. Tenho notícias, mas não são boas.";
			link.l1 = "Qualquer notícia é de extrema importância para mim. Por favor, conte-me, Mynheer van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_12";
		break;
		
		case "PZ_Formosa_JohanVanMerden_12":
			dialog.text = "É... Fermentelos partiu para Batávia faz cerca de um mês. Essa é a única pista que tenho sobre ele. A boa notícia é que ele pretende ficar lá por um tempo, então se você for agora, vai encontrá-lo. A má notícia? Ele é amigo íntimo do Governador-Geral Anthony van Diemen. Você não vai conseguir chegar perto dele.";
			link.l1 = "Esta notícia basta. Meus humildes agradecimentos a você, senhor van Merden. Partirei imediatamente.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_13";
		break;
		
		case "PZ_Formosa_JohanVanMerden_13":
			dialog.text = "Algo me dizia que você diria isso, então decidi equilibrar um pouco as coisas para você e Chang Xing. Escrevi uma carta para um velho amigo meu, Oliver Trust. Ele tem uma loja em Batávia. Ele me deve um favor, então vai te ajudar.";
			link.l1 = "Eu... Eu não sei o que dizer...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_14";
			//Log_Info("Вы получили письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Formosa_JohanVanMerden_14":
			dialog.text = "Um simples “obrigado” basta. Se não conseguir encontrar Oliveiro na cidade, procure pela Estrela da Manhã. Você sempre pode rastreá-lo pelo navio dele. Boa sorte, meu amigo—você e sua irmã vão precisar.";
			link.l1 = "Muito obrigado do fundo do meu coração, Mynheer van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_15";
		break;
		
		case "PZ_Formosa_JohanVanMerden_15":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Batavia,"+ NewStr() +"May 29, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Batavia", "merchant", "mrcActive5", "PZ_Batavia_Puteshestvie");
			LaunchFrameForm();
		break;
		
		case "PZ_OliverTrust_1": //
			dialog.text = "Quem é você, e o que está fazendo aqui? Eu não faço negócios com gente como você.";
			link.l1 = "Tenho uma carta para você.";
			link.l1.go = "PZ_OliverTrust_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_OliverTrust_2":
			dialog.text = "Ah, o mensageiro! Embora eu não esperasse nenhuma carta hoje. Fique aqui! Vou dar uma olhada.";
			link.l1 = "Você é Oliver Trust? Van Merden me mandou até você.";
			link.l1.go = "PZ_OliverTrust_3";
			//Log_Info("Вы отдали письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_OliverTrust_3":
			dialog.text = "Eu sei ler, sabia? Normalmente, eu mandaria você embora, mas gente como van Merden não aceita um não como resposta. Finalmente chegou a hora de acertar as contas com van Diemen.";
			link.l1 = "Meu alvo é Fermentelos. E quanto a van Diemen?";
			link.l1.go = "PZ_OliverTrust_4";
		break;
		
		case "PZ_OliverTrust_4":
			dialog.text = "Isso não é da sua conta. Você devia agradecer por eu estar te ajudando, e olhe lá. Agora preste atenção, antes que eu decida que isso tudo é uma péssima ideia. Eu conheço o Fermentelos. Ele ficou aqui um tempo, mas já foi embora. O Morning Star partiu há algumas semanas. Só Deus sabe quando vai voltar. Então seu alvo mudou, e agora é um amigo do Fermentelos...";
			link.l1 = "... van Diemen.";
			link.l1.go = "PZ_OliverTrust_5";
		break;
		
		case "PZ_OliverTrust_5":
			dialog.text = "É mesmo. Você sabe disso também? Imagino que foi o Johan quem te contou? Ah, van Merden... você é um desgraçado ousado. Mas já que você sabe sobre o van Diemen, sabe também da posição dele, não é? Qual é o seu grande plano para chegar até o Governador-Geral? Não vai invadir a residência dele à força, imagino!";
			link.l1 = "Chang Tu é um guerreiro habilidoso.";
			link.l1.go = "PZ_OliverTrust_6";
		break;
		
		case "PZ_OliverTrust_6":
			dialog.text = "Um guerreiro habilidoso, hein? Você percebe que agora estamos todos encrencados? E o que acontece comigo se você for capturado? Vou ter que te ajudar, tanto pela sua segurança quanto pela minha. Além de morar na casa dele, Van Diemen faz visitas regulares à plantação fora da cidade e à amante dele, Vette.";
			link.l1 = "Você mencionou que iria me ajudar.";
			link.l1.go = "PZ_OliverTrust_12";
		break;
		
		case "PZ_OliverTrust_12":
			dialog.text = "Eu acredito que todo mundo deve ter uma paixão, um passatempo. Quanto a mim, eu coleciono armas raras e caras. Às vezes têm história, às vezes não, mas sempre são letais. Minha coleção pode ser útil para sua cruzada. Então, me diga, onde você planeja emboscar van Diemen?";
			link.l1 = "(Residência) Já que você tem tantas armas boas, vou pegar a melhor lâmina. Com ela, Chang Tu será imbatível entre os homens brancos.";
			link.l1.go = "PZ_OliverTrust_resedinsia_1";
			link.l2 = "(Plantação) Vou emboscá-los na estrada da plantação – não terão para onde fugir.";
			link.l2.go = "PZ_OliverTrust_Plantation1";
			link.l3 = "(Senhora) A senhora - não vai ter muita gente lá, então os guardas não vão reagir a tempo.";
			link.l3.go = "PZ_OliverTrust_lubovnitsa_1";
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			InterfaceStates.Buttons.Save.enable = false;
		break;
		
		// Rebbebion, ну, с Богом...
		case "PZ_OliverTrust_Plantation1":
			pchar.questTemp.PZ_Batavia_plantation_Go = true;
			
			dialog.text = "Boa escolha! Estou impressionado. Para tirar o melhor proveito disso, você vai precisar de uma boa arma de fogo. Me diga, até onde consegue mirar, Chang Tu?";
			link.l1 = "Para ser sincero... não muito longe, preciso garantir que não vou errar."link.l1.go ="PZ_OliverTrust_Plantation_MediumDistance1";
			link.l2 = "Vou atacar de longe – meu inimigo nem vai perceber de onde veio o golpe.";
			link.l2.go = "PZ_OliverTrust_Plantation_FarDistance1";
			notification(GetConvertStr("Sniper", "AbilityDescribe.txt")+" Unlocked", "Longway");
			SetCharacterPerk(pchar, "Sniper");
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket6"); 
			EquipCharacterByItem(pchar, "mushket6");
			//Log_Info("Вы получили башенный мушкетон");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "grapeshot", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "grapeshot");
			
			dialog.text = "Entendi. Nesse caso, fique com isto! Uma antiga bacamarte português de torre, dispara um cartucho de grosso calibre. Não fabricam mais dessas, nem mesmo no Velho Mundo.";
			link.l1 = "Eu vi um quando era criança...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance2";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance2":
			dialog.text = "Então, você sabe como usar isso?";
			link.l1 = "Não...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance3";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance3":
			dialog.text = "Lembre-se, o mecanismo intercambiável enferrujou com o tempo. Nenhum óleo vai resolver – está quebrado de vez. Carregá-lo é difícil, então vamos fazer isso agora. Preste atenção – use um pouco de força, assim. Mas não exagere, senão você quebra.";
			link.l1 = "Assim?";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance4";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance4":
			dialog.text = "Exatamente.";
			link.l1 = "Entendi. Muito obrigado!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_Plantation_FarDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket2x2"); 
			EquipCharacterByItem(pchar, "mushket2x2");
			//Log_Info("Вы получили двуствольный штуцер");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "bullet", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "bullet");
			
			dialog.text = "Um verdadeiro jaeger! Cuidado, foi um presente. É um daqueles raros casos em que uma arma é ao mesmo tempo decorativa e mortal. Uma espingarda de caça de dois canos! Pesada de segurar, fácil de usar. Já descobriu como atirar com ela?";
			link.l1 = "Entendido. Muito obrigado!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_lubovnitsa_1":
			dialog.text = "Você tem razão sobre os guardas, mas não subestime o perigo. Van Diemen nunca anda pela cidade sem seu braço direito, Joep van der Vink.";
			link.l1 = "Então, eles estão juntos com a Vette...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_2";
			pchar.questTemp.PZ_Batavia_lubovnitsa_Go = true;
			AddCharacterSkillDontClearExp(pchar, "Sailing", 10);
			AddCharacterSkillDontClearExp(pchar, "Commerce", 10);
			AddCharacterSkillDontClearExp(pchar, "Repair", 10);
			notification("Naval Skills +", "Longway");
			notification("Rat Wolf Unlocked", "Longway");
			SetCharacterPerk(pchar, "RatsWolf");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_2":
			dialog.text = "O quê? Ha! Você tem uma imaginação e tanto, chinês! Antoon é um covarde, e van der Vink está lá para protegê-lo caso alguém atrapalhe o 'tempo privado' deles.\nJoep sempre usa uma armadura pesada de trincheira – impenetrável para a maioria das armas brancas. Por isso você também vai precisar de algo especial. Pegue este florete. É longo, mais forte que a maioria das outras espadas, e pesa como uma boa lâmina.";
			link.l1 = "Uma rapieira para lutar contra inimigos de armadura...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_3";
			//Log_Info("Вы получили асоледу");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_26");
			EquipCharacterByItem(Pchar, "blade_26");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_3":
			dialog.text = "Não mire na armadura em si – isso aqui não é uma estocada. Acerte nas frestas e nos pontos vulneráveis, como a virilha, as axilas e a garganta. Vá cansando ele, imponha o ritmo. Joep também usa um machado pesado, então não tente aparar os golpes – desvie deles\nCaso não consiga achar uma brecha, leve esta bacamarte. Normalmente ela usa chumbo grosso, mas preparei um carregamento de setas de aço pra você.";
			link.l1 = "Flechas para um mosquete...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_4";
			//Log_Info("Вы получили бландербуз");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "pistol8");
			EquipCharacterByItem(Pchar, "pistol8");
			AddItems(Pchar, "harpoon", 30);
			AddItems(Pchar, "gunpowder", 30);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "harpoon");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_4":
			dialog.text = "Incomum, não é? Uma mistura de antigo e novo. Foi feita para atirar com uma mão só, mas se ficar pesada, use as duas. Muitos fazem isso\nE aqui, experimente esta armadura de vime. É mais leve que a couraça do Joep, mas ainda protege bem. Só não deixe o machado dele acertar direto – nem armadura milanesa aguentaria uma arma dessas. Entendeu?";
			link.l1 = "Sim, eu entendo. Obrigado, Sr. Trust!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили кожаный корсет");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "cirass5");
			EquipCharacterByItem(Pchar, "cirass5");
		break;
		
		case "PZ_OliverTrust_resedinsia_1":
			dialog.text = "Confiante demais, não é? Talvez eu tenha falado da minha coleção cedo demais. Mas... agora você já está comprometido. Atacar uma residência em plena luz do dia é ousado, ninguém esperaria por isso. Esta lâmina deve servir ao que você precisa. Não é a melhor do mundo, mas é perfeita para perfurar, cortar e decepar.";
			link.l1 = "Clewang! Eu reconheço essa lâmina. O pessoal das ilhas vizinhas costuma usar uma dessas.";
			link.l1.go = "PZ_OliverTrust_resedinsia_2";
			pchar.questTemp.PZ_Batavia_resedinsia_Go = true;
			notification(GetConvertStr("TannedLeather", "AbilityDescribe.txt") +" Unlocked", "Longway");
			SetCharacterPerk(pchar, "TannedLeather");
			SetCharacterPerk(pchar, "HT1");
		break;
		
		case "PZ_OliverTrust_resedinsia_2":
			dialog.text = "Have you used one before? Good. You'll have little time and many enemies to face. Here, take this as well - a handgun with three barrels, beautifully inlaid. Load it now in front of me; you won't have time for that later. And wear this dueling waistcoat. It's light, it will give you the speed you'll need, and some protection.";
			link.l1 = "Obrigado, Senhor Trust!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили клеванг");
			//Log_Info("Вы получили трёхствольный дробовик");
			//Log_Info("Вы получили жилет бретера");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_30");
			EquipCharacterByItem(Pchar, "blade_30");
			GiveItem2Character(PChar, "pistol2");
			EquipCharacterByItem(Pchar, "pistol2");
			GiveItem2Character(PChar, "cirass6");
			EquipCharacterByItem(Pchar, "cirass6");
			AddItems(Pchar, "grapeshot", 50);
			AddItems(Pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "grapeshot");
		break;
		
		case "PZ_OliverTrust_13":
			dialog.text = "Espere, ainda não terminamos. É do nosso interesse mútuo que você sobreviva. Pegue este remédio para curar seus ferimentos depois da batalha. \nE este elixir também. Tem um gosto e um cheiro horríveis, mas elimina qualquer veneno do seu corpo. Joep van der Vink, o guarda-costas de Van Diemen, passa essa porcaria nas armas dele. Bastardo convencido, assim você vai ter uma vantagem.";
			link.l1 = "Não sei se algum dia vou conseguir te agradecer o bastante, Meu Senhor Trust...";
			link.l1.go = "PZ_OliverTrust_14";
			//Log_Info("Вы получили 10 лечебных зелий");
			//Log_Info("Вы получили противоядие");
			PlaySound("interface\important_item.wav");
			AddItems(Pchar, "potion1", 10);
			AddItems(Pchar, "potion3", 1);
		break;
		
		case "PZ_OliverTrust_14":
			dialog.text = "O melhor agradecimento que você pode me dar é não me entregar se for pego. Embora, muito provavelmente, eles só vão te matar na hora. Mas se você sobreviver a isso, diga ao Van Diemen que ele deve a morte dele a mim. Consegue fazer isso?";
			link.l1 = "Sem problema. Mais uma vez, obrigado, senhor Trust. Adeus!";
			link.l1.go = "PZ_Batavia_NaOhotu";
		break;
		
		case "PZ_Batavia_NaOhotu":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				DoQuestReloadToLocation("Batavia", "reload", "reload1", "PZ_Batavia_BitvaSoStrazhnikami");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				DoQuestReloadToLocation("Batavia_HouseF3", "reload", "reload1", "PZ_Batavia_BitvaLubovnitsa");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				/*EndQuestMovie();
				sld = &Locations[FindLocation("Batavia_plantation")];
				sld.locators_radius.quest.detector4 = 3.0;
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1 = "locator";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.location = "Batavia_plantation";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator_group = "quest";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator = "detector4";
				PChar.quest.PZ_Batavia_plantation1.win_condition = "PZ_Batavia_plantation_selfdialog";*/
				DoQuestReloadToLocation("Batavia_plantation", "quest", "detector2", "PZ_Batavia_plantation_setguards");
			}
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_1":
			dialog.text = "Pare! Onde pensa que vai, chinês?";
			link.l1 = "Para a residência.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_2";
			locCameraFromToPos(-0.44, 7.45, 24.65, true, -1.90, 5.10, 18.50);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_2":
			dialog.text = "Essa era uma pergunta retórica, gênio. O que te faz pensar que alguém deixaria alguém como você entrar lá?";
			link.l1 = "Tenho assuntos com o senhor Van Diemen. Deixe-me passar, por favor.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_3";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_3":
			dialog.text = "Você sabe o nome do governador-geral? Bem... me diga qual é o seu assunto. Eu vou passar o recado e depois te dou uma resposta.";
			link.l1 = "Minha conversa é só com o senhor Van Diemen. Ele está me esperando. Saia da frente, ou vai se arrepender.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_4";
			locCameraSleep(true);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_4":
			dialog.text = "Olha só, não se ache, olhos apertados. Ou é do meu jeito ou não é de jeito nenhum.";
			link.l1 = "Então, do meu jeito.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_5";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_5":
			DialogExit();
			LAi_SetActorType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_SoldResid_1"));
			LAi_group_MoveCharacter(pchar, LAI_GROUP_PLAYER);
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			
			sld = CharacterFromID("PZ_SoldResid_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
				
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			DoQuestCheckDelay("PZ_Batavia_resedinsia_1", 0.9);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_1":
			dialog.text = "Maldito camponês! Quem te contratou? Eu te pago mais do que isso!";
			link.l1 = "Vocês, brancos, só se importam com ouro. Que os dragões amaldiçoem a sua raça. Eu vim atrás de informações, mas o seu povo não me deixa entrar.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2":
			dialog.text = "O que você quer?!";
			link.l1 = "Fermentelos. Onde ele está agora?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3":
			dialog.text = "Oliveiro? Mas por que diabos você quer ele? Não vou te contar nada!";
			link.l1 = "Ele matou minha família e sequestrou minha irmã. Meu conselho pra você é começar a falar. Para o seu próprio bem.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4":
			dialog.text = "O que você vai fazer comigo? Logo toda a guarnição vai estar aqui.";
			link.l1 = "Já ouviu falar de Lynchy? É um castigo na minha cultura. Significa 'Morte por Mil Cortes.'";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5":
			dialog.text = "Você não vai ter tempo de me cortar tantas vezes assim, seu imbecil!";
			link.l1 = "É uma figura de linguagem. O carrasco faz cortes, um por um. Ou corta pedaços do corpo. Fazemos o quanto der tempo – a menos que você comece a falar.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Sepp", "mercen_26", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
			sld.name = "Joep";
			sld.lastname = "van der Vink";
			GiveItem2Character(sld, "topor_04");
			EquipCharacterByItem(sld, "topor_04");
			GiveItem2Character(sld, "pistol3");
			EquipCharacterByItem(sld, "pistol3");
			sld.CantLoot = true;
			LAi_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Batavia_townhallRoom", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			
			LAi_SetStayType(pchar);
			locCameraFromToPos(-3.06, 1.64, -0.43, true, 1.87, -1.20, 2.39);
			DoQuestCheckDelay("PZ_Batavia_BitvaResidensia_7", 2.5);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_7":
			dialog.text = "A-A-A!!! Pare! Pare, seu bruto imundo. Eu conto, eu conto tudo. Só pare. Joep! Finalmente! Onde diabos você esteve esse tempo todo?!";
			link.l1 = "Que péssima hora...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9":
			dialog.text = "Antoon? Você precisa ver um médico imediatamente. Vou te ajudar a chegar lá assim que terminar aqui. Você! O que diabos está fazendo, seu açougueiro covarde?!";
			link.l1 = "Açougueiro Amarelo? Até que gostei disso. Só tem uma pergunta que preciso que me respondam, mas ninguém parece disposto a fazê-lo...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10":
			dialog.text = "Que pergunta?!";
			link.l1 = "Onde está Oliveiro Fermentelos? Não pode ao menos dizer isso?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11":
			dialog.text = "Eu não dou a mínima para Fermentelos! Quem te deu o dinheiro e as informações?!";
			link.l1 = "Oliver Trust. Aliás, ele pediu pra te dizer que você deve a morte a ele.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12";
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_ActorSetGroundSitMode(sld);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12":
			dialog.text = "Confiança?! Ha-ha-ha-ha-ha-ha-ha! Aquele sovina achou que podia se vingar só porque pegamos a plantação dele? Logo vamos pegar a loja e a vida dele também, assim que eu acabar com você.";
			link.l1 = "Você está desperdiçando meu tempo.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1.character = "PZ_Sepp";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition = "PZ_Batavia_BitvaResidensia_8";
		break;
		
		case "PZ_Batavia_PlantationSelfDialog":
			dialog.text = "(em mandarim) Então, vamos procurar um bom lugar para uma emboscada.";
			if (CheckCharacterItem(pchar, "mushket6"))
			{
				link.l1 = "(em mandarim) Com essa coisa enferrujada, vou ter que chegar perto. Um disparo rápido – preciso e implacável. O medo e o pânico farão o resto.";
				link.l1.go = "Exit";
			}
			else
			{
				link.l1 = "(em mandarim) Bem aqui. Eles nem vão me notar de início. As melhores batalhas são aquelas que nem começam... ou que acabam rápido, com pouco derramamento de sangue.";
				link.l1.go = "Exit";
			}
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_Batavia_PlantationFight");
		break;
		
		case "PZ_Batavia_PlantationDimen1":
			if (!CharacterIsAlive("PZ_SoldPlantation_1") && !CharacterIsAlive("PZ_SoldPlantation_2") &&  !CharacterIsAlive("PZ_SoldPlantation_3") && !CharacterIsAlive("PZ_SoldPlantation_4") && !CharacterIsAlive("PZ_SoldPlantation_5") && !CharacterIsAlive("PZ_SoldPlantation_6"))
			{
				dialog.text = "Brutamonte nojento... Você é um escravo fugitivo, não é? Como conseguiu uma arma dessas? Alguém te contratou...?";
				link.l1 = "Sem tempo! Diga onde está Oliveiro Fermentelos - agora!";
				link.l1.go = "PZ_Batavia_PlantationDimen2";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_PlantationDimenSit");
			}
		break;
		
		case "PZ_Batavia_PlantationDimen2":
			dialog.text = "Hehehe, engraçado... Não há tempo – o sangue está jorrando da minha barriga. Queime no inferno, pagão...";
			link.l1 = "(em mandarim) Não!!!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_Batavia_PlantationDimenDead1");
		break;
		
		case "PZ_Batavia_Plantation_DimenDeadSelfDialog":
			dialog.text = "(em mandarim) Por quê, por quê, por quê?! Como é que eu vou encontrar Fermentelos agora?!";
			link.l1 = "Mas primeiro, preciso me esconder – alguém já deve ter denunciado esse banho de sangue...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_1":
			dialog.text = "Hic! Um chinês! Não esperava ver alguém como você ser convidado aqui. Gosta de assistir, hein? Hehe.";
			link.l1 = "Por que tem tanta gente aqui...? E quem é você?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_2":
			dialog.text = "Você não me reconhece pelas minhas roupas? E cuidado com o tom ao falar com o Governador-Geral! Hic!";
			link.l1 = "Então, o senhor deve ser o Mynheer Van Diemen. Peço desculpas pela minha ignorância. Está acontecendo um carnaval aqui?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_3";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_3":
			dialog.text = "Isso mesmo, meu bom homem, não tem outro jeito! Um carnaval de travestidos! Ha-ha-ha! Nada mal, camponês! Aposto que o Luthers ia a-do-o-rar vestir o vestido da Vette, ha ha ha!";
			link.l1 = "Luthers?..";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4";
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4":
			dialog.text = "Aquele miserável de um marido, que adora espiar do armário enquanto a querida esposinha dele está sendo comida. E ela nem liga!";
			link.l1 = "";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4_1";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, sld);
			CharacterTurnByChr(pchar, sld);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), sld);
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_4", 2.5);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4_1":
			Event("QuestDelayExit","sl", "", 0);
			dialog.text = "Certo, Vette, minha querida? Heh-heh.";
			link.l1 = "(em mandarim) O que diabos está acontecendo aqui...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_5";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, CharacterFromID("PZ_Brigitta"));
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), npchar);
			locCameraFromToPos(-2.21, 1.90, 2.26, true, -0.81, -0.40, 4.36);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_5":
			dialog.text = "Hic! Eu não faço ideia do que você acabou de dizer, mas pelo seu olhar e pelo tom da sua voz, você concorda comigo! Van Haan é um maldito pervertido. Então, o que você é afinal? Um trabalhador? Foi a Vette que te chamou?";
			link.l1 = "Eu...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_6";
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), pchar);
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_7":
			dialog.text = "Trazer um trabalhador pra cá é demais, até mesmo pro Vette. Ele claramente está perdido e não devia estar aqui. Ei, você. Saia daqui e esqueça tudo o que viu. Quem é seu patrão? Vamos falar com ele, e vocês dois vão receber pra ficarem de boca fechada. Talvez até deixem você voltar pra sua família no continente. Responda e vá embora.";
			link.l1 = "Na verdade, estou aqui a negócios.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_8";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_8":
			dialog.text = "Heh, negócios. Só o senhor van Diemen faz “Negócios” aqui. Meu trabalho é protegê-lo de pessoas como você. E Luthers... é só o Luthers mesmo. Ou... foi a Vette que realmente te convidou pra cá?";
			link.l1 = " Não, eu estou aqui para...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_9";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_9":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Rubbe");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_10":
			dialog.text = "Será que minha querida Vette realmente traria um bunda-amarela pra cá?! Cai fora daqui!!!";
			link.l1 = "O miserável corno...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_11";
			link.l2 = "Ninguém está falando com você. Fique de boca fechada. Não finja ter coragem ou dignidade.";
			link.l2.go = "PZ_Batavia_BitvaLubovnitsa_12";
			GiveItem2Character(npchar, "blade_06");
			EquipCharacterByItem(npchar, "blade_06");
			LAi_SetActorType(npchar);
			npchar.model.animation = "man";
			Characters_RefreshModel(npchar);
			SetCameraDialogMode(npchar);
			locCameraToPos(-1.88, 1.72, 0.27, false);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_11":
			dialog.text = "Co-co-corno?! Não, eu amo ela mais do que a mim mesmo. Ha, um chinês burro como você nunca entenderia isso!";
			link.l1 = "(em mandarim) Desgraçado doente.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_12":
			dialog.text = "Pi-pi-pinto?! Tá tudo bem! Sim! Eu só sei que outros homens dão mais prazer pra minha querida Vette, só isso!";
			link.l1 = "Como dizemos na minha terra, um homem ainda é um homem até sobrar só um dedo. Se você fosse homem, entenderia isso.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_13":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Brigitta");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_14":
			dialog.text = "Eu não o convidei, claro, mas, sabe, ele é bem simpático. Pode ser que fique por aqui depois que vocês forem embora. Já tentei isso com o nosso cachorro, mas nunca fiz com...";
			link.l1 = "Cale a boca quando os homens estão falando, vadia! O único animal aqui é você. Estou aqui a negócios. Procuro por Oliveiro Fermentelos. Devem ser amigos dele. Pode me dizer onde ele está, senhor Van Diemen?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_15";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_15":
			dialog.text = "Antoon, ele me insultou! Me insultou! Você não vai deixar isso passar, vai?!";
			link.l1 = "...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_16";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_16":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_AntoniOneDimen");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_17":
			dialog.text = "Hehe, desculpa, camarada, mas a moça tá furiosa. Vou ter que te ensinar um pouco de respeito. Primeira lição.";
			link.l1 = "Mas você pode me ajudar na minha busca por Oliveiro?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_18";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_18":
			dialog.text = "Não vai ajudar um trabalhador morto.";
			link.l1 = "(em mandarim) Malditos sejam todos vocês...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_19";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_19":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			PlaySound("Voice\Russian\hambit\Longway-02.wav");
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Sepp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Rubbe");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Batavia_BitvaLubovnitsa_3");
			
			sld = CharacterFromID("PZ_Brigitta");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			PlaySound("People Fight\Peace_woman_death_05.wav");
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_5", 3.0);	//Нужно ещё раз, а то не бежит
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_21":
			dialog.text = "(em mandarim) Droga! Não aprendi nada!";
			link.l1 = "(em mandarim) Nunca vou esquecer este dia... Preciso sair daqui antes que os guardas cheguem. Não que eles se importem com os barulhos vindos deste manicômio...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_14":
			dialog.text = "(em mandarim) Os deuses amaldiçoaram este dia! Van Diemen sangrou até a morte enquanto eu lidava com o capanga dele...!";
			link.l1 = "(em mandarim) Os guardas estão vindo. Vou ter que lutar para sair daqui.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final":
			DialogExit();
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_30");
				TakeItemFromCharacter(pchar, "pistol2");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_26");
				TakeItemFromCharacter(pchar, "pistol8");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				TakeItemFromCharacter(pchar, "mushket6");
				TakeItemFromCharacter(pchar, "mushket2x2");
			}
			EquipCharacterByItem(Pchar, "blade_11");
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			
			
			SetCurrentTime(2, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Formosa,"+ NewStr() +"26 July 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa", "goto", "goto7", "PZ_Formosa2_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_21":
			dialog.text = "Oh, é o Chang Chang! Com o que você precisa de ajuda desta vez, meu pequeno amigo?";
			link.l1 = "É o Chang Tu... como assim?";
			link.l1.go = "PZ_Formosa_smuggler_22";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_22":
			dialog.text = "Você está transbordando desprezo por mim, não está? Só veio aqui porque precisa de alguma coisa.";
			link.l1 = "Você sabe onde está o van Merden? Ele está na cidade? Não está em casa. Preciso falar com ele.";
			link.l1.go = "PZ_Formosa_smuggler_23";
		break;
		
		case "PZ_Formosa_smuggler_23":
			dialog.text = "Um homem não pode ficar em casa o dia todo, esperando um único sujeito de pele amarela aparecer. Ele tem negócios na ilha. Vai voltar pra cidade hoje à noite, então não se preocupe, Chang Chang!";
			link.l1 = "Obrigado. Adeus.";
			link.l1.go = "PZ_Formosa_smuggler_24";
		break;
		
		case "PZ_Formosa_smuggler_24":
			SetCurrentTime(1, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestReloadToLocation("Formosa", "goto", "goto7", "PZ_Formosa2_IshemMerden_3");
		break;
		
		case "PZ_Formosa_bandit_1":
			dialog.text = "Ei, olhos apertados! Qual é a pressa a essa hora? Gente decente já está dormindo agora.";
			link.l1 = "E você?";
			link.l1.go = "PZ_Formosa_bandit_2";
		break;
		
		case "PZ_Formosa_bandit_2":
			dialog.text = "Muito bem dito! Estamos de patrulha! Dizem que tem um sujeito amarelo rondando a cidade, incomodando gente de bem.";
			link.l1 = "Quem poderia ser, diga-me por favor?";
			link.l1.go = "PZ_Formosa_bandit_3";
		break;
		
		case "PZ_Formosa_bandit_3":
			dialog.text = "Chega de conversa – está ficando tarde e estou começando a ficar com sono.";
			link.l1 = "Em breve, seu sono será eterno.";
			link.l1.go = "PZ_Formosa_bandit_4";
		break;
		
		case "PZ_Formosa_bandit_4":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_JohanVanMerden");
			ChangeCharacterAddressGroup(sld, PChar.location, "patrol", "patrol7");
			GiveItem2Character(sld, "blade_31");
			EquipCharacterByItem(sld, "blade_31");
			LAi_SetActorType(sld);
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_FormosaBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Formosa2_IshemMerden_7");
			
			DoQuestCheckDelay("PZ_Formosa2_IshemMerden_6", 10.0);
		break;
		
		case "PZ_Formosa_JohanVanMerden_21":
			dialog.text = "Chang Tu, você está bem?";
			link.l1 = "Mynheer van Merden! Estou, graças à sua intervenção. E você, está bem? Isso é o mais importante.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_22";
		break;
		
		case "PZ_Formosa_JohanVanMerden_22":
			dialog.text = "Sempre pensando nos outros, não é? Temos isso em comum. Eu não conseguiria ficar parado vendo eles te atacarem, mesmo sabendo que você daria conta. Respondendo à sua pergunta, estou bem, só um pouco cansado. Minhas pernas estão meio trêmulas. Vamos entrar, se não se importar. Podemos conversar lá dentro.";
			link.l1 = "Claro, senhor van Merden, afinal de contas esta é a sua casa.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_23";
		break;
		
		case "PZ_Formosa_JohanVanMerden_23":
			DoQuestReloadToLocation("Formosa_houseSp1", "goto", "goto1", "PZ_Formosa2_IshemMerden_8");
		break;
		
		case "PZ_Formosa_JohanVanMerden_24":
			dialog.text = "Agora podemos conversar sem pressa, em paz e tranquilidade. Diga-me, o que te traz até mim, Chang Tu?";
			link.l1 = "Tem razão, Mynheer van Merden. Acabei de voltar de Batávia, e...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_25";
		break;
		
		case "PZ_Formosa_JohanVanMerden_25":
			dialog.text = "Espere. É o pobre Chang Xing...?";
			link.l1 = "Não, de jeito nenhum! Espero que não. O destino dela ainda é um segredo que o céu me esconde. E quanto ao Fermentelos... ele não está em Batávia. Van Diemen não ajudou em nada.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_26";
		break;
		
		case "PZ_Formosa_JohanVanMerden_26":
			dialog.text = "Ele não seria, pois ele e Oliveiro são velhos amigos. Como dizem os ingleses, amigos e parceiros no crime. Eu ficaria surpreso se ele te desse algo útil.";
			link.l1 = "Sim, graças a você e ao Trust, consegui armas poderosas. Ataquei Van Diemen para interrogá-lo e descobrir onde estava Fermentelos. Mas ele morreu antes que eu pudesse saber de alguma coisa...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_28";
		break;
		
		case "PZ_Formosa_JohanVanMerden_28":
			dialog.text = "Impressionante. Você percebeu que as pessoas nem sempre querem compartilhar o que sabem. Então existem outros... métodos de persuasão, digamos assim. Achei que você tivesse descoberto sobre a morte da sua irmã, e por isso saiu descontrolado. Mas o que te traz aqui agora? Eu já disse que não sei para onde Fermentelos vai, além das visitas ocasionais a Batávia. Com Van Diemen fora, essa última pista se perdeu.";
			link.l1 = "Mas você conhece muitas coisas e muitas pessoas. Achei que talvez pudesse ajudar de novo, perguntar sobre Fermentelos, como fez antes. Você foi o primeiro homem branco a me tratar bem. O primeiro... amigo branco.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_29";
		break;
		
		case "PZ_Formosa_JohanVanMerden_29":
			dialog.text = "Isso é... comovente.";
			link.l1 = "Mynheer van Merden, por que está sorrindo...?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_30";
		break;
		
		case "PZ_Formosa_JohanVanMerden_30":
			dialog.text = "Hã? Ah, me desculpe, Chang Tu. Estou ficando velho, sentimental e melancólico com o tempo. Esse sorriso é sincero – não consegui esconder. Fico feliz que me considere um amigo. Já que somos amigos, também espero que me ajude de vez em quando. Em troca, vou te ajudar com Fermentelos, com certeza. Não se preocupe – você não está caindo numa armadilha.";
			link.l1 = "Hum, ajudar você como?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_31";
		break;
		
		case "PZ_Formosa_JohanVanMerden_31":
			dialog.text = "Desde a última vez que nos vimos, aprofundei meus estudos sobre sua língua e cultura, especialmente medicina. Gostaria que você me trouxesse algumas placas de relíquias de vez em quando. Vou pagar bem por elas, como em qualquer outro trabalho. E espero que possamos praticar nossas conversas em chinês de vez em quando. Tenho vergonha de pedir isso aos meus criados, mas a um amigo...";
			link.l1 = "Chang Tu fará o seu melhor, Senhor van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_32";
		break;
		
		case "PZ_Formosa_JohanVanMerden_32":
			dialog.text = "Ótimo. Você e eu temos um longo caminho pela frente, meu amigo. Um longo caminho. Ha! Acho que seria um bom nome de disfarce para você. Um uso útil do meu ofício. Em holandês, é “Lange Afstand.” Os ingleses dizem “Long Way.” Qual você prefere?";
			link.l1 = "Eu prefiro a versão em inglês. Long. Way. Longway. Fica bem apropriado no meu idioma. Obrigado por ouvir, Senhor van Merden. Longway vai aguardar sua palavra e estará pronto para ajudar e cumprir seus pedidos.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_33";
		break;
		
		case "PZ_Formosa_JohanVanMerden_33":
			DialogExit();
			
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			bQuestDisableMapEnter = true;
			pchar.GenQuest.CabinLock = true;
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_SegodnyaVremya_2", 5.0);
		break;
		
		// Этап 3, СЛЕД ЗВЕЗДЫ
		case "PZ_Longway_PosleRasskaza":
			dialog.text = "Falando do arquivo, Meu Senhor Capitão, está com você? É tudo o que preciso – conheço a cifra de cor.";
			if (CheckCharacterItem(pchar, "MerdokArchive"))
			{
				notification("All Skills +", "Longway");
				AddCharacterExpToSkill(npchar, "Leadership", 50);
				AddCharacterExpToSkill(npchar, "FencingL", 50);
				AddCharacterExpToSkill(npchar, "FencingS", 50);
				AddCharacterExpToSkill(npchar, "FencingH", 50);
				AddCharacterExpToSkill(npchar, "Pistol", 50);
				AddCharacterExpToSkill(npchar, "Fortune", 50);
				AddCharacterExpToSkill(npchar, "Sneak", 50);
				AddCharacterExpToSkill(npchar, "Sailing", 50);
				AddCharacterExpToSkill(npchar, "Accuracy", 50);
				AddCharacterExpToSkill(npchar, "Cannons", 50);
				AddCharacterExpToSkill(npchar, "Grappling", 50);
				AddCharacterExpToSkill(npchar, "Defence", 50);
				AddCharacterExpToSkill(npchar, "Repair", 50);
				AddCharacterExpToSkill(npchar, "Commerce", 50);	
				
				link.l1 = "Sim, eu guardei, achando que poderia ser útil algum dia.";
				link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_1";
			}
			else
			{
				link.l1 = "Infelizmente, não. Era sua última esperança de encontrar a irmã?";
				link.l1.go = "PZ_Longway_PosleRasskaza_2";
			}
		break;
		
		case "PZ_Longway_PosleRasskaza_2":
			dialog.text = "Longway fica muito satisfeito que o Senhor Capitão se preocupe. Por enquanto, ainda há esperança. Encontrei uma nova pista em Guadalupe.";
			link.l1 = "Certo, então. Me conte o que aconteceu com você lá.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_1":
			dialog.text = "Foi uma decisão sábia. Talvez encontremos algo lá dentro que possa nos ajudar na busca por Chang Xing.";
			link.l1 = "Seria o ideal. Vamos analisar isso agora mesmo.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_2";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_2":
			dialog.text = "Sim, vamos estudar isso juntos. O ano é... 1637. Antoon van Diemen vendeu... vendeu...";
			link.l1 = "Escravos, né?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_3";
			AddQuestRecordInfo("PZ_ArchiveOneMerden", "1");
			RemoveItems(PChar, "MerdokArchive", 1);
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_3":
			dialog.text = "Mulheres do meu povo, vendidas para homens brancos ricos.";
			link.l1 = "Isso é terrível.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_4":
			dialog.text = "Senhor Capitão, você não parece surpreso. Isso não te incomoda nem um pouco, o destino daquelas mulheres?";
			link.l1 = "Longway, of course it sincerely troubles me. I've seen this filth from the inside. But I've always been an advocate for women... and a bit of a ladies' man, to be honest. It's good you killed van Diemen; he deserved it. Is there anything else?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_5":
			dialog.text = "Van Diemen só trabalhava com quem ele confiava completamente - Joep van der Vink, seu braço direito, e aquele maldito Oliveiro Fermentelos. E... e...";
			link.l1 = "O que foi? Você ficou pálido, Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_6":
			dialog.text = "Johan van Merden...";
			link.l1 = "Me desculpe. Isso é horrível, mas por que você está tão surpreso? Antes você disse que arrancou todas as páginas que mencionavam Fermentelos. Não encontrou nenhuma menção a van Merden naquela hora?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_7";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_7":
			dialog.text = "Longway estava com pressa e deve ter deixado passar esse detalhe importante.";
			link.l1 = "Entendi. Quando estiver pronto, vamos continuar procurando e encontrar qualquer coisa que possamos usar agora.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_8";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_8":
			dialog.text = "Está escrito que Fermentelos mandava seus homens capturar mulheres, trocava elas e destruía os registros. Depois, Merden as enviava para Batávia, onde van der Vink e van Diemen vendiam nossas mulheres para homens brancos. Se ao menos eu tivesse descoberto isso antes...";
			link.l1 = "Então, no fim, todos trabalharam juntos. Não se culpe, Longway. Você não tinha como saber. O arquivo só chegou às suas mãos recentemente. Tem mais alguma coisa?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_9";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_9":
			dialog.text = "Sim. Eles fazem isso há quase dez anos. Tantas mulheres perderam suas famílias, sua honra, sua esperança... Mas então Fermentelos parou de trabalhar com van Merden. Essa foi a única razão pela qual ele me ajudou – tudo o que ele queria era se livrar do antigo parceiro.";
			link.l1 = "Que outros detalhes das sujeiras deles estão registrados aqui?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_10";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_10":
			dialog.text = "Mais pensamentos sombrios de van Merden. Ele descobriu que van Diemen estava roubando seu dinheiro. Então, me mandou para Batávia, esperando que eu morresse lá, mas também torcendo para que eu levasse van Diemen comigo.";
			link.l1 = "Frio. Mas também incrivelmente inteligente.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_11";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_11":
			dialog.text = "Poderia ter sido ainda pior. Foi o van Merden quem mandou aqueles brutamontes à casa dele para me matar. Só interveio para ajudar quando percebeu que eu poderia derrotá-los sozinho.";
			link.l1 = "Ele tinha pensado em tudo, sem dúvida.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_12";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_12":
			dialog.text = "Depois que voltei vivo, ele deve ter pensado que eu tinha descoberto o verdadeiro plano dele e vim buscar vingança. Quando conversamos, ele ficou com a arma apontada embaixo da mesa. Mas aí eu chamei ele de meu primeiro amigo branco... ele quase explodiu de tanto rir...";
			link.l1 = "Isso é horrível, Longway. É amargo perceber que aqueles que achávamos nossos amigos estavam rindo de nós pelas costas o tempo todo.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_13";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_13":
			dialog.text = "Longway aprendeu algo há muito tempo, pouco antes de chegar neste arquipélago. Fui capturado pelos portugueses e eles queriam me enforcar. Lorde Rodenburg salvou minha vida.";
			link.l1 = "Foi assim que você entrou ao serviço dele? Lucas também estava em Formosa?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_14";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_14":
			dialog.text = "Sim, é isso mesmo. E não só ele – Van Berg também. Van Merden me disse que foi ele quem aconselhou Rodenburg a me poupar. Mas algum tempo depois, Longway soube por uma fonte duvidosa que, na verdade, foi o Johan quem mandou os portugueses atrás de mim. Na época eu não acreditei... mas agora percebo que pode ser verdade...";
			link.l1 = "Nojento.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_15";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_15":
			dialog.text = "Ainda assim, naquele dia, dúvidas se instalaram no meu coração. Então, quando soube que o Senhor Capitão e van Merden haviam se enfrentado, Longway lembrou da sua bondade e ficou do seu lado.";
			link.l1 = "Essa foi a decisão certa, Longway. Heh, no fim das contas, seu primeiro amigo branco de verdade fui eu.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_16";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_16":
			dialog.text = "Então é isso, Senhor Capitão. Agora entendo. Van Merden me dizia que eu era seu amigo. Mas, na verdade, Longway não passava de mais um trabalhador para ele – só era mais útil que a maioria\nSó isso. As outras páginas tratam de contabilidade, além de detalhes dos negócios entre Van Berg e Rodenburg.";
			link.l1 = "Entendi. E agora está mais do que na hora de você me contar o que fez em Guadalupe.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_3":
			dialog.text = "Eu estava procurando pela Estrela da Manhã. Uma das páginas arrancadas do arquivo dizia que ela foi vista pela última vez perto de São Cristóvão.";
			link.l1 = "Por que lá? Combinamos de nos encontrar em Guadalupe, e foi lá que te encontrei.";
			link.l1.go = "PZ_Longway_PosleRasskaza_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_4":
			dialog.text = "Porque St. Christopher's é o lar de Georges Gravel, um dos informantes de van Merden. Georges acredita que ainda trabalho para Johan. Além disso, Gravel já cometeu uma ofensa grave contra van Merden. E Longway ajudou a encobrir isso.";
			link.l1 = "E qual foi a ofensa?";
			link.l1.go = "PZ_Longway_PosleRasskaza_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_5":
			dialog.text = "Isso não importa. O que importa é que Georges devia uma dívida ao Longway. Então, fui até a igreja onde Gravel trabalha como assistente de padre. Meu Senhor Capitão está pronto para ouvir o resto? Você parece um pouco distraído.";
			link.l1 = "Desculpe, me distraí. Sim, claro, pode falar, Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_6":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Capsterville,"+ NewStr() +"St. Christopher Island.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "patrol", "patrol12", "PZ_Kapstervil_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Zhorzh_1":
			dialog.text = "Que bom, você não se atrasou. Eu não gostaria de ficar aqui mais tempo do que o necessário, sabe! O que você precisa desta vez, Longway?";
			link.l1 = "Mude seu tom, Gravel. A organização precisa dos seus serviços.";
			link.l1.go = "PZ_Zhorzh_2";
		break;
		
		case "PZ_Zhorzh_2":
			dialog.text = "Preciso confessar, faz muito tempo que não tenho notícias deles. Será que me esqueceram?";
			link.l1 = "Posso lembrá-los. Talvez contando ao Lorde van Merden sobre o que você fez.";
			link.l1.go = "PZ_Zhorzh_3";
		break;
		
		case "PZ_Zhorzh_3":
			dialog.text = "Tudo bem, tudo bem, não precisa ficar tão bravo! O que posso fazer por você?";
			link.l1 = "Preciso de informações sobre a Morning Star. Tudo o que puder encontrar. Quanto mais, melhor.";
			link.l1.go = "PZ_Zhorzh_4";
		break;
		
		case "PZ_Zhorzh_4":
			dialog.text = "Claro, mas vai levar tempo! Dois dias! No mínimo.";
			link.l1 = "Por que demorou tanto?";
			link.l1.go = "PZ_Zhorzh_5";
		break;
		
		case "PZ_Zhorzh_5":
			dialog.text = "Normalmente, eu pegaria dinheiro da caixa de ofertas para soltar a língua dos meus informantes. Mas fomos roubados recentemente! O Padre vai anunciar uma nova coleta de doações, claro, mas ainda precisamos consertar o telhado – está vazando! Vai precisar de muita doação pra arrumar isso.";
			link.l1 = "Dois dias. Não posso ficar aqui para sempre. Não tenho esse tempo todo. Longway não é conhecido pela paciência. Lorde van Merden, menos ainda. Ou preciso te lembrar disso, Gravel?";
			link.l1.go = "PZ_Zhorzh_6";
		break;
		
		case "PZ_Zhorzh_6":
			dialog.text = "Eu não posso controlar o que está além do meu alcance! Vou fazer o que puder. Mas, olha, eu descobriria bem mais rápido se você encontrasse aqueles bandidos e trouxesse nossas doações de volta!";
			link.l1 = "Vou pensar nisso. Você começa a procurar. Dois dias. Não mais. Nos encontramos na mesma hora e lugar.";
			link.l1.go = "PZ_Zhorzh_7";
		break;
		
		case "PZ_Zhorzh_7":
			DialogExit(); 
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A Day Later..."+ NewStr() +"In Search of the Church Robbers.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil_Jungle", "goto", "goto1", "PZ_Kapstervil_Jungle");
			LaunchFrameForm();
		break;
		
		case "PZ_VorugaChurch_1":
			dialog.text = "Olha só! Um homem de olhos apertados na nossa ilha! Fugindo dos seus patrões, é? De quem você está se escondendo, se não se importa que eu pergunte?";
			link.l1 = "Sou um homem livre.";
			link.l1.go = "PZ_VorugaChurch_2";
		break;
		
		case "PZ_VorugaChurch_2":
			dialog.text = "Ha! Claro que sim. Mas você parece forte e esperto, mesmo com esses olhos meio puxados. Quer entrar pra nossa turma? Acho que você não tem outro lugar pra ir, de qualquer jeito.";
			link.l1 = "O Longway acha que você está mais interessado em roubá-lo do que em recrutá-lo.";
			link.l1.go = "PZ_VorugaChurch_3";
		break;
		
		case "PZ_VorugaChurch_3":
			dialog.text = "Heh, considere-se com sorte. Recentemente, roubamos uma igreja na cidade, acredita? Por quê? Porque roubar de ladrão não é roubo de verdade.";
			link.l1 = "Eu não estava planejando te caçar, mas fico feliz por ter te encontrado.";
			link.l1.go = "PZ_VorugaChurch_4";
		break;
		
		case "PZ_VorugaChurch_4":
			dialog.text = "Caçando a gente? Ah, então você é um mercenário, não um trabalhador fugitivo. Pior pra você, então.";
			link.l1 = "Exatamente.";
			link.l1.go = "PZ_VorugaChurch_5";
		break;
		
		case "PZ_VorugaChurch_5":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetCheckMinHP(npchar, 1, true, "PZ_VorugaChurch_win");
			for (i=11; i<=14; i++)
			{
				sld = CharacterFromID("PZ_KapstervilBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_VorugaChurch_6":
			if (!CharacterIsAlive("PZ_KapstervilBandit_11") && !CharacterIsAlive("PZ_KapstervilBandit_12") && !CharacterIsAlive("PZ_KapstervilBandit_13"))
			{
				dialog.text = "Merda... Por que não me matou logo de uma vez? O que você quer de mim? Vai me arrastar pra prisão?";
				link.l1 = "Não tenho interesse nisso. Só me diga onde você escondeu o ouro.";
				link.l1.go = "PZ_VorugaChurch_7";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_VorugaChurch_win");	
			}
		break;
		
		case "PZ_VorugaChurch_7":
			dialog.text = "Heh... Seu desgraçado de pele amarela...";
			link.l1 = "A paciência do Longway está se esgotando. De um jeito ou de outro, vou descobrir. A única dúvida é quanto tempo você ainda vai sofrer.";
			link.l1.go = "PZ_VorugaChurch_8";
			LAi_group_Delete("EnemyFight");
		break;
		
		case "PZ_VorugaChurch_8":
			dialog.text = "Certo, tudo bem... Está numa caverna. Tudo está lá. O dinheiro é seu. Só... só não me mate, tá bom?";
			link.l1 = "Eu não disse que não haveria sofrimento algum...";
			link.l1.go = "PZ_VorugaChurch_9";
		break;
		
		case "PZ_VorugaChurch_9":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_VorugaChurch_win_2", 0.9);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0":
			StartQuestMovie(true, false, true);
			locCameraFromToPos(2.48, 0.87, 9.26, true, 6.72, -0.85, 6.05);
			dialog.text = "(em mandarim) Aqui está o esconderijo dos bandidos.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_0_1";
			CharacterTurnToLoc(pchar, "box", "box1");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "PZ_Kapstervil_Grot_1", -1);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1":
			dialog.text = "(em mandarim) É muito!";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_1_1";
			CharacterTurnToLoc(pchar, "box", "box1");
			locCameraFromToPos(6.83, 2.65, 6.62, true, 2.83, -1.00, 7.67);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1_1":
			dialog.text = "(em mandarim) Estou ouvindo passos...";
			link.l1 = "(em mandarim) Tem mais alguém aqui...";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_2";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_2":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_1", "sold_fra_7", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.17, 0.65, -1.42, 0.00);
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_2", "sold_fra_5", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.10, 0.65, 0.30, 3.00);
			
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_Kapstervil_Grot_2", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_3":
			dialog.text = "O que diabos estamos fazendo aqui? Não sobrou ninguém – nós já cuidamos de todos os ladrões.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_4");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_5":
			dialog.text = "É isso mesmo, idiota! Eles vão voltar, e a gente vai recebê-los de braços abertos.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_1"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_5");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_7":
			dialog.text = "Vou dar uma olhada por aí, ver se não tem ninguém escondido. Estou entediado mesmo...";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_8";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_8":
			DialogExit();
			LAi_Fade("PZ_Kapstervil_Grot_5_1", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_9":
			dialog.text = "(em mandarim) Soldados! Que azar... O que eu faço agora?";
			link.l1 = "(em mandarim) Eu preciso desse dinheiro mais do que os soldados brancos! Não vou sair daqui sem ele!";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_10";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_10":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("PZ_Kapstervil_GrotSoldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyWithRadius");
				LAi_group_SetRelation("EnemyWithRadius", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_SetLookRadius("EnemyWithRadius", 6.0);
				LAi_group_SetHearRadius("EnemyWithRadius", 2.0);
				LAi_group_SetSayRadius("EnemyWithRadius", 12.0);
				LAi_group_SetCheck("EnemyWithRadius", "PZ_Kapstervil_Grot_6");
			}
		break;
		
		case "PZ_Zhorzh_11":
			dialog.text = "Ah, monsieur Longway, você voltou!";
			link.l1 = "Claro. Havia alguma dúvida? Descobriu algo sobre a Estrela da Manhã, Georges?";
			link.l1.go = "PZ_Zhorzh_12";
		break;
		
		case "PZ_Zhorzh_12":
			dialog.text = "Sim, monsieur. É um galeão pesado, comandado por um espanhol, ou pelo menos é o que dizem...";
			link.l1 = "Ele é português. Vocês, brancos, nem conseguem diferenciar uns aos outros.";
			link.l1.go = "PZ_Zhorzh_13";
		break;
		
		case "PZ_Zhorzh_13":
			dialog.text = "Ah, certo. Meu erro. De qualquer forma, descobri que ele modificou bastante a galé para tentar disfarçá-la de navio mercante, com canhões de pequeno calibre e uma tripulação reduzida. Mas ele ampliou o porão, enchendo até a borda – está tão pesada que mal consegue navegar.";
			link.l1 = "Então ele decidiu começar uma nova vida. Ótimo. Agora, onde posso encontrá-lo?";
			link.l1.go = "PZ_Zhorzh_14";
		break;
		
		case "PZ_Zhorzh_14":
			dialog.text = "Isso é mais complicado. Ele se move constantemente entre nossas colônias e as inglesas, mas só entre as Ilhas de Barlavento. No entanto, fiquei sabendo que ele está a caminho de Basse-Terre com uma grande carga de vinho neste momento.";
			link.l1 = "Preciso descobrir como chegar lá rápido.";
			link.l1.go = "PZ_Zhorzh_15";
		break;
		
		case "PZ_Zhorzh_15":
			dialog.text = "Isso é problema seu, monsieur Longway. Eu já tenho problemas demais... como consertar esse maldito telhado.";
			link.l1 = "Falando em preocupações, encontrei aqueles ladrões da igreja. Aqui está o dinheiro da doação de volta. Conserte o telhado – não é bom para o seu Deus ficar sem um.";
			link.l1.go = "PZ_Zhorzh_16";
		break;
		
		case "PZ_Zhorzh_16":
			dialog.text = "Muito obrigada, monsieur Longway! Nunca imaginei que seria você a fazer isso.";
			link.l1 = "Eu também não achei que fosse possível. Mas eu precisava fazer algo com aqueles dois dias.";
			link.l1.go = "PZ_Zhorzh_17";
		break;
		
		case "PZ_Zhorzh_17":
			dialog.text = "Então, você precisa ir para Guadalupe? Vou encontrar um navio indo pra lá pra você. Espere notícias minhas em breve!";
			link.l1 = "Isso seria útil. Obrigado, Georges.";
			link.l1.go = "PZ_Zhorzh_18";
		break;
		
		case "PZ_Zhorzh_18":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("The Next Morning..."+ NewStr() +"Capsterville", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "goto", "goto19", "PZ_Kapstervil_PoiskZvezda");
			LaunchFrameForm();
		break;
		
		case "PZ_Kapstervil_Kurier_1":
			dialog.text = "Você deve ser conhecido do Georges? Ele me pediu para te entregar isto.";
			link.l1 = "Um bilhete? Minha gratidão. Como soube que era para mim?";
			link.l1.go = "PZ_Kapstervil_Kurier_2";
		break;
		
		case "PZ_Kapstervil_Kurier_2":
			dialog.text = "Sério?";
			link.l1 = "Ah, certo.";
			link.l1.go = "PZ_Kapstervil_Kurier_3";
		break;
		
		case "PZ_Kapstervil_Kurier_3":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("PZ_Kapstervil_ChitaemPismo", 1.5);
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog":
			dialog.text = "(Lê a carta) Monsieur Longway, a chalupa ‘Provence’ parte para Basse-Terre amanhã de manhã. O capitão, Mathieu Terugny, pode ser encontrado na taverna. Envie minhas saudações ao monsieur van Merden. - Georges Gravel.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_ChitaemPismo_Dialog_2";
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog_2":
			DialogExit();
			LAi_RemoveCheckMinHP(pchar);
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			sld = characterFromId("PZ_Kapstervil_tavernkeeper");
			sld.dialog.currentnode = "PZ_TerunyiTavern1";
			LAi_SetBarmanType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_TerunyiTavern1":
			dialog.text = "Não servimos bebidas para gente como você aqui. E, a menos que eu queira ouvir reclamações sobre pulgas, também não vou alugar um quarto para você.";
			link.l1 = "Não preciso de uma bebida nem de um quarto. E... Longway não tem pulgas.";
			link.l1.go = "PZ_TerunyiTavern2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_TerunyiTavern2":
			dialog.text = "Como diabos eu vou saber? Tá, fala logo. O que você quer? Então cai fora.";
			link.l1 = "Eu vou. Estou procurando pelo Capitão Mathieu Terugny. Não consigo encontrá-lo. Você sabe onde ele está?";
			link.l1.go = "PZ_TerunyiTavern3";
		break;
		
		case "PZ_TerunyiTavern3":
			dialog.text = "Ele está ocupado preparando o navio dele para zarpar na loja local. Isso é muito mais importante do que conversar com um chinês como você, mas você claramente não entende isso.";
			link.l1 = "Na verdade, eu costumava ser... Deixa pra lá. Não importa agora.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateTerunyi");
		break;
		
		case "PZ_Terunyi1":
			dialog.text = "O que você quer, chinês? Não está vendo que estou ocupado? Preciso preparar meu navio.";
			link.l1 = "Capitão Mathieu Terugny?";
			link.l1.go = "PZ_Terunyi2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Terunyi2":
			dialog.text = "Bem, isso acabou de deixar de ser engraçado. Como alguém como você sabe quem eu sou? Foi alguém que te mandou?";
			link.l1 = "Não precisa se preocupar. Ouvi dizer que você vai para Basse-Terre. Pode me levar como passageiro? Eu pago.";
			link.l1.go = "PZ_Terunyi3";
		break;
		
		case "PZ_Terunyi3":
			dialog.text = "Isso só melhora. Estou indo para St. Pierre, não para Basse-Terre, mas é um desvio curto. Isso é bom, porque não vou precisar te manter no navio mais tempo do que o necessário. Cinco mil pesos. Partimos em três horas. Pague no cais. Mesmo sendo comerciante, não tem negociação. Entendeu?";
			link.l1 = "Sim. Obrigado. Vejo você no cais, Capitão Terugny.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToPier");
		break;
		
		case "PZ_Terunyi4":
			dialog.text = "Você apareceu mesmo assim, chinês. Achei que você não viria – ninguém nunca dá dinheiro de verdade para gente como você de bom grado.";
			link.l1 = "Cinco mil pesos, como você pediu. Está pronto para zarpar?";
			link.l1.go = "PZ_Terunyi5";
		break;
		
		case "PZ_Terunyi5":
			AddMoneyToCharacter(pchar, -5000);
			
			dialog.text = "Não, não! Eu é que deveria perguntar isso para você. Mas vejo que está pronto. Vamos. Você vai remar o bote. E nem pense em esperar uma cabine de verdade! Só estamos fazendo esse desvio por sua causa.";
			link.l1 = "Não preciso de consolo. Só me leve até lá.";
			link.l1.go = "PZ_Terunyi6";
		break;
		
		case "PZ_Terunyi6":
			DialogExit();
			
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			InterfaceStates.Buttons.Save.enable = true;
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_Flashback_Final_1", 3.5);
		break;
		
		case "PZ_Longway_PosleRasskaza21":
			dialog.text = "...então Longway não conseguiu descobrir exatamente para onde o Estrela da Manhã está indo.";
			link.l1 = "É, dá pra entender como você foi parar nessa confusão toda.";
			link.l1.go = "PZ_Longway_PosleRasskaza22";
		break;
		
		case "PZ_Longway_PosleRasskaza22":
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena")) sStr = "Helena";
			else sStr = "Alonso";
			dialog.text = "Eu vi uma brigue nas águas de Guadalupe. Talvez fosse o Banten. Vou tentar descobrir. Bem, pode ir agora, Longway. Traga-me "+sStr+".";
			link.l1.go = "PZ_Longway_PosleRasskaza23";
		break;
		
		case "PZ_Longway_PosleRasskaza23":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeLong("PZ_LongwayUhoditIzKauty", "PZ_HelenaOrAlonso");
		break;
		
		case "PZ_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Meu capitão, está tudo bem? Vim assim que o Longway disse que você precisava de mim.";
				link.l1 = "Estou só tentando juntar as peças. Você lembra o nome daquele brigue que vimos perto da ilha?";
				link.l1.go = "PZ_Helena_3";
			}
			else
			{
				dialog.text = "Queria me ver?";
				link.l1 = "Sim. Você se lembra da fragata que vimos recentemente? Descubra onde ela está e como se chama.";
				link.l1.go = "PZ_Helena_2";
			}
		break;
		
		case "PZ_Helena_2":
			dialog.text = "Eu me lembro, mas por que esse interesse repentino por uma brigue? Descobrir isso pode levar algum tempo.";
			link.l1 = "Helen, só faça isso, por favor. E sim, eu sei que pode demorar um pouco. Eu vou esperar.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Helena_3":
			dialog.text = "Não, eu não conferi. Por quê? É importante?";
			link.l1 = "Uhum. Consegue descobrir mais alguma coisa? Preciso saber onde eles estão ancorados agora, se ainda não saíram das águas de Guadalupe.";
			link.l1.go = "PZ_Helena_4";
		break;
		
		case "PZ_Helena_4":
			dialog.text = "Claro. Só pra avisar, pode demorar um pouco. Vou pegar um bote e levar uns caras pra ajudar, beleza, Charles?";
			link.l1 = "Claro, Helen, obrigado. Estarei esperando.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Alonso_11":
			dialog.text = "Senhor Capitão, chamou?";
			link.l1 = "Sim, Alonso. Passamos por uma brigue nas águas perto da ilha quando voltamos para buscar o Longway. Você chegou a ver o nome dela?";
			link.l1.go = "PZ_Alonso_12";
		break;
		
		case "PZ_Alonso_12":
			dialog.text = "Não, meu trabalho é ficar de olho nos recrutas novos e participar da linha de frente nos abordagens. Além disso, eu nem tenho luneta, e nós nem éramos tão próximos.";
			link.l1 = "É verdade. Mas eu preciso descobrir de qualquer jeito. Faça isso.";
			link.l1.go = "PZ_Alonso_13";
		break;
		
		case "PZ_Alonso_13":
			dialog.text = "Sim, Capitão. Acho que consigo fazer isso em meio dia.";
			link.l1 = "Anda logo. Vou estar esperando.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_PoiskBanten":
			DialogExit();
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			LAi_SetStayType(pchar);
			SetLaunchFrameFormParam("Five hours later...", "PZ_PoiskBanten_2", 0, 4.0);
			LaunchFrameForm();
			locCameraSleep(true);
		break;
		
		case "PZ_Helena_5":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Aprendi tudo. Estava tudo bem enquanto eu estava fora, meu capitão?";
				link.l1 = "Sim, estou bem, obrigado, Helen. Diga.";
				link.l1.go = "PZ_Helena_7";
			}
			else
			{
				dialog.text = "Ufa, voltei. Encontrei sua escuna.";
				link.l1 = "Bem-vindo de volta. Qual o nome dela e onde ela está?";
				link.l1.go = "PZ_Helena_6";
			}
		break;
		
		case "PZ_Helena_6":
			dialog.text = "O Banten. Esse nome significa algo pra você, não é? Ela está no farol agora, e alguns dos tripulantes já desembarcaram. Vamos atacar aquele navio?";
			link.l1 = "Não, precisamos descobrir exatamente quem desembarcou. Vamos até o farol por terra. Considerando que já nos atrasamos, já passou da hora de deixarmos o porto. Devíamos ancorar em algum lugar afastado. A Praia Capster seria uma boa escolha. Vamos depressa, Helen.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Helena_7":
			dialog.text = "Bem, a escuna se chama Banten, e está ancorada perto do farol. Parte da tripulação já desembarcou lá. O que você vai fazer?";
			link.l1 = "Para descobrir, teremos que chegar ao farol sem sermos vistos, e só podemos fazer isso a pé. Nosso navio precisa ancorar em um lugar seguro. Que tal a Praia Capster?";
			link.l1.go = "PZ_Helena_8";
		break;
		
		case "PZ_Helena_8":
			dialog.text = "Boa ideia. Charles, você quer que eu vá ao farol com você?";
			link.l1 = "Vou pensar nisso enquanto movemos o navio – você já está cansado o bastante.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Alonso_15":
			dialog.text = "Voltei assim que terminei, Senhor Capitão.";
			link.l1 = "Muito bem. Relate, Alonso.";
			link.l1.go = "PZ_Alonso_16";
		break;
		
		case "PZ_Alonso_16":
			dialog.text = "O brigue ainda está fora da ilha – no farol, para ser exato. O nome na popa é Banten. Alguns da tripulação deles já desembarcaram.";
			link.l1 = "Bom trabalho, Alonso. Prepare a tripulação para içar âncora imediatamente.";
			link.l1.go = "PZ_Alonso_17";
		break;
		
		case "PZ_Alonso_17":
			dialog.text = "Preparar-se para o abordo também?";
			link.l1 = "Ainda não. Se o capitão deles estiver indo para o farol, ele pode se esconder na cidade se atacarmos no mar. Vamos para a Praia Capster para garantir nosso navio, depois seguimos a pé até o farol.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_BasTerMayak":
			DialogExit();
			locCameraSleep(false);
			LAi_SetPlayerType(pchar);
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Guadeloupe", true);
			
			AddQuestRecord("PZ", "15");
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1 = "location";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1.location = "Shore29";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition = "PZ_Banten_PlyazhKapster";
			
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1 = "Timer";
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.hour = sti(GetTime() + 7);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition = "PZ_Banten_PlyazhKapster_Proval";
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, pchar, "", -1);
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Saga\Helena.c";
				npchar.Dialog.CurrentNode = "Helena_officer";
			}
		break;
		
		case "PZ_Longway_21":
			dialog.text = "Senhor Capitão, olhe! Tem alguém dentro do farol.";
			link.l1 = "Ótimo, chegamos a tempo! Vamos depressa pegá-los. Alonso vai ter muito trabalho hoje.";
			link.l1.go = "PZ_Longway_22";
		break;
		
		case "PZ_Longway_22":
			dialog.text = "Mas e se eles morrerem no processo?";
			link.l1 = "O que você sugere?";
			link.l1.go = "PZ_Longway_23";
		break;
		
		case "PZ_Longway_23":
			dialog.text = "Vamos entrar silenciosamente e ouvir a conversa deles primeiro.";
			link.l1 = "Duvido que consigamos fazer isso sem sermos vistos da janela. Mas vamos tentar assim mesmo.";
			link.l1.go = "PZ_Longway_24";
		break;
		
		case "PZ_Longway_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			LAi_SetCheckMinHP(npchar, 1, true, "HiddenImmortality");
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1 = "locator";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.location = "Mayak4";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator_group = "goto";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator = "goto31";
			PChar.quest.PZ_MayakPodslushivanie.win_condition = "PZ_MayakPodslushivanie";
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1":
			dialog.text = "Pense bem no que eu disse. Pense com atenção. Dinheiro não é problema – dentro de certos limites, claro. Mas até esse limite vai parecer uma montanha de ouro pra você – o chinês tem que morrer! Já mandei homens atrás dele antes, mas não adiantou. Desta vez, porém, se eles se juntarem aos seus homens...";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_1_1";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_BasTerJailOff_Clone"));
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1_1":
			StartInstantDialog("PZ_BasTerJailOff_Clone", "PZ_MayakPodslushivanie_Dialog_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_2":
			dialog.text = "Olha, estão nos vigiando! É ele! Ele e o maldito capitão dele!";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_3";
			CharacterTurnToLoc(npchar, "item", "flower5");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_3":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			locCameraToPos(1.52, 18.87, -9.55, true);
			DoQuestCheckDelay("CameraReset", 1.0);
			DeleteAttribute(pchar, "questTemp.NoFast");
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_Neznakomets");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = CharacterFromID("PZ_BasTerJailOff_Clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_MayakPodslushivanie_win");
			
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_Neznakomets_Bandit_"+i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_Mayak_KomendantSidit_1":
			if (!CharacterIsAlive("PZ_Neznakomets_Bandit_1") && !CharacterIsAlive("PZ_Neznakomets_Bandit_2") && !CharacterIsAlive("PZ_Neznakomets_Bandit_3")&& !CharacterIsAlive("PZ_Neznakomets_Bandit_4"))
			{
				dialog.text = "Maldito seja, seu asiático imundo... Tive que aguentar tanta coisa por sua causa. E agora, por tudo isso, estou prestes a morrer...";
				link.l1 = "Vamos levá-lo ao nosso médico, Senhor Comandante. Só nos diga com quem estava falando – é muito importante.";
				link.l1.go = "PZ_Mayak_KomendantSidit_2";
				LAi_group_Delete("EnemyFight");
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_MayakPodslushivanie_win");	
			}
		break;
		
		case "PZ_Mayak_KomendantSidit_2":
			dialog.text = "O nome dele... é Joep van der Vink, ele... kha...";
			link.l1 = "...";
			link.l1.go = "PZ_Mayak_KomendantSidit_3";
		break;
		
		case "PZ_Mayak_KomendantSidit_3":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			DoQuestCheckDelay("PZ_Mayak_Longway", 1.5);
		break;
		
		case "PZ_Longway_25":
			dialog.text = "";
			link.l1 = "Ele está morto... Bem, pelo menos sabemos o nome. Longway...?";
			link.l1.go = "PZ_Longway_26";
		break;
		
		case "PZ_Longway_26":
			dialog.text = "Isso não pode ser...";
			link.l1 = "Você está meio pálido, Longway.";
			link.l1.go = "PZ_Longway_27";
		break;
		
		case "PZ_Longway_27":
			dialog.text = "Longway tinha certeza de que matou van der Vink há dez anos\nEles estão fugindo! O navio deles é rápido!";
			link.l1 = "Sim, uma escuna maravilhosa... infelizmente para nós. Mesmo que consigamos chegar ao nosso navio a tempo, eles já terão partido quando içarmos as velas e pegarmos o vento.";
			link.l1.go = "PZ_Longway_28";
		break;
		
		case "PZ_Longway_28":
			dialog.text = "Isso pode ser o fim...";
			link.l1 = "Não, Longway. Me escuta. Se eles pretendem ficar no Arquipélago, mais cedo ou mais tarde vamos acabar cruzando com eles – o mundo é pequeno, e o Caribe então, nem se fala. Assim que encontrarmos o rastro deles de novo, largo tudo e vou atrás. Te prometo isso. Está ouvindo?";
			link.l1.go = "PZ_Longway_29";
		break;
		
		case "PZ_Longway_29":
			dialog.text = "Sim, Meu Senhor Capitão. Obrigado.";
			link.l1 = "Mantenha a cabeça erguida, Longway. Precisamos voltar rápido para o navio – a morte do Comandante logo vai ser notícia por toda parte.";
			link.l1.go = "PZ_Longway_30";
		break;
		
		case "PZ_Longway_30":
			DialogExit();
			
			ReturnOfficer_Longway();
			LAi_RemoveCheckMinHP(npchar);
			AddQuestRecord("PZ", "17");
			sld = &Locations[FindLocation("Mayak4")];
			sld.locators_radius.goto.goto31 = 0.5;
			
			chrDisableReloadToLocation = false;
			QuestOpenSeaExit();
			
			pchar.questTemp.PZ_Etap4_Start = true;
		break;
		
		// Этап 4, Обманчивая Звезда
		case "PZ_PoterpKrushenie_1":
			dialog.text = "Monsieur! Um momento! Você é capitão?";
			link.l1 = "Talvez. Como você adivinhou? E o que você quer?";
			link.l1.go = "PZ_PoterpKrushenie_2";
		break;
		
		case "PZ_PoterpKrushenie_2":
			dialog.text = "Bem, só tem montanhas e uma selva densa por aqui – nada de estradas para a cidade. Mesmo assim, você está aqui. Não veio só passear, certo?";
			link.l1 = "Boa observação. Mas você ainda não me disse o que quer.";
			link.l1.go = "PZ_PoterpKrushenie_3";
		break;
		
		case "PZ_PoterpKrushenie_3":
			dialog.text = "Ah, certo! Capitão, nosso navio bateu nas rochas logo ali perto desta enseada. Só nós conseguimos sobreviver...";
			link.l1 = "Me desculpe. Você quer que eu te leve a algum lugar, não é?";
			link.l1.go = "PZ_PoterpKrushenie_4";
		break;
		
		case "PZ_PoterpKrushenie_4":
			dialog.text = "Sim... Não vamos causar problemas, eu juro. Só nos deixe em Belize, e a partir daí a gente se vira.";
			link.l1 = "Não é longe, né? Nesse caso, seja bem-vindo a bordo.";
			link.l1.go = "PZ_PoterpKrushenie_5";
			link.l2 = "Desculpe, mas estou indo para o outro lado.";
			link.l2.go = "PZ_PoterpKrushenie_7";
		break;
		
		case "PZ_PoterpKrushenie_5":
			dialog.text = "Obrigado, Capitão! Quem sabe quanto tempo teríamos ficado presos sem você.";
			link.l1 = "De fato. Não vamos perder tempo!";
			link.l1.go = "PZ_PoterpKrushenie_6";
		break;
		
		case "PZ_PoterpKrushenie_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_PoterpKrushenie";
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_7":
			dialog.text = "Mas Belize é tão perto! Não vai demorar, com certeza?";
			link.l1 = "Estou com pressa. Não posso me dar ao luxo de desvios.";
			link.l1.go = "PZ_PoterpKrushenie_8";
		break;
		
		case "PZ_PoterpKrushenie_8":
			dialog.text = "Nem uma viagem curta? Só até Belize? Por favor, Capitão, não nos deixe aqui largados!";
			link.l1 = "Certo, espero não me arrepender disso. Todos a bordo!";
			link.l1.go = "PZ_PoterpKrushenie_6";
			link.l2 = "C'est la vie. Tenham um bom dia, meus amigos.";
			link.l2.go = "PZ_PoterpKrushenie_9";
		break;
		
		case "PZ_PoterpKrushenie_9":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", 10);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_QuestCitizenDialog";
			
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
			
			pchar.questTemp.PZ.Shipwreckers.Decline = true;
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_11":
			dialog.text = "Obrigado mais uma vez, Capitão! Somos apenas marinheiros simples, então não temos muito o que lhe oferecer.";
			link.l1 = "Bem, pelo menos não tivemos que desviar tanto do nosso caminho.";
			link.l1.go = "PZ_PoterpKrushenie_12";
		break;
		
		case "PZ_PoterpKrushenie_12":
			dialog.text = "Vamos levantar um copo à sua saúde e acender uma vela para você na igreja.";
			link.l1 = "Já é melhor do que nada. Saúde, pessoal!";
			link.l1.go = "PZ_PoterpKrushenie_13";
		break;
		
		case "PZ_PoterpKrushenie_13":
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetCitizenType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0;
				sld.location = "None";
			}
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BelizZhitelNovosti", "citiz_4", "man", "man", 1, ENGLAND, 0, false, "quest"));
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto5");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_BelizZhitelNovosti_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_BelizZhitelNovosti_1":
			dialog.text = "Você ouviu? Finalmente pegaram ele! Nossas águas estão seguras, enfim!";
			link.l1 = "Isso é... uma boa notícia? Mas quem eles pegaram?";
			link.l1.go = "PZ_BelizZhitelNovosti_2";
			DeleteQuestCondition("PZ_BelizFail");
		break;
		
		case "PZ_BelizZhitelNovosti_2":
			dialog.text = "Matthew Lutter, o próprio Tagarela!";
			link.l1 = "Não conheço - o que ele fez?";
			link.l1.go = "PZ_BelizZhitelNovosti_3";
		break;
		
		case "PZ_BelizZhitelNovosti_3":
			dialog.text = "Você não sabe?! Bom, dá pra ver que você não é inglês, isso eu percebo. Ele é um pirata que vem saqueando a gente e os espanhóis há anos no navio dele, o Gaivota.";
			link.l1 = "Saqueando tanto os ingleses quanto os espanhóis? Isso é incomum.";
			link.l1.go = "PZ_BelizZhitelNovosti_4";
		break;
		
		case "PZ_BelizZhitelNovosti_4":
			dialog.text = "De fato. A guarda costeira nunca conseguiu pegá-lo, mas no fim, ele quis voar alto demais e se deu mal — perdeu para um navio mercante estranho, se você acredita nisso.";
			link.l1 = "Que engraçado. O que havia de tão estranho nesse comerciante?";
			link.l1.go = "PZ_BelizZhitelNovosti_5";
		break;
		
		case "PZ_BelizZhitelNovosti_5":
			dialog.text = "Bem, era só um galeão enorme e desajeitado, sem escolta! Mas graças ao capitão maluco dela, Lutter vai cantar sua última canção hoje — está prestes a ser enforcado. Você devia ir ver!";
			link.l1 = "Talvez, mas por agora, tenho outros assuntos para resolver.";
			link.l1.go = "PZ_BelizZhitelNovosti_6";
		break;
		
		case "PZ_BelizZhitelNovosti_6":
			DialogExit();
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			
			sld = CharacterFromID("Longway");
			if (!CharacterIsHere("Longway"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			}
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_31";
		break;
		
		case "PZ_Longway_31":
			dialog.text = "Meu Senhor Capitão!";
			link.l1 = "Um mercador espanhol derrotando um pirata ousado... Você está pensando o mesmo que Longway, não está?";
			link.l1.go = "PZ_Longway_32";
		break;
		
		case "PZ_Longway_32":
			dialog.text = "A Estrela da Manhã...";
			link.l1 = "Provavelmente - não existe outro capitão mercante como ele em todo o arquipélago.";
			link.l1.go = "PZ_Longway_33";
		break;
		
		case "PZ_Longway_33":
			dialog.text = "Precisamos encontrá-lo imediatamente!";
			link.l1 = "Certo. Mas não vejo nenhum galeão pesado no porto. Vamos tentar falar com o Tagarela antes que ele seja enforcado. Vamos ver se ele fez por merecer esse apelido.";
			link.l1.go = "PZ_Longway_34";
		break;
		
		case "PZ_Longway_34":
			DialogExit();
			ReturnOfficer_Longway();
			if (!CheckAttribute(pchar, "questTemp.PZ.Shipwreckers.Decline")) AddQuestRecord("PZ", "18");
			else AddQuestRecord("PZ", "18_1");
			pchar.questTemp.PZ_Beliz_Komendant = true;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		break;
		
		case "PZ_Beliz_Komendant_8":
			dialog.text = "Ele ainda está vivo? Podemos falar com ele?";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_9";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_9":
			StartInstantDialogNoType("BelizJailOff", "PZ_Beliz_Komendant_10", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_10":
			dialog.text = "O quê? Ah, sim. Ele está vivo – a execução ainda não aconteceu. Você pode ir falar com ele – está mais falante do que nunca. Mas ultimamente, anda dizendo só bobagens, falando sozinho a maior parte do tempo. O Tagarela enlouqueceu... Mal posso esperar para enforcá-lo, antes que todos nós enlouqueçamos com o falatório dele.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_11";
		break;
		
		case "PZ_Beliz_Komendant_11":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_12":
			dialog.text = "Obrigado.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_13";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_13":
			DialogExit();
			pchar.questTemp.jailCanMove = true;
			
			ReturnOfficer_Longway();
			
			sld = CharacterFromID("BelizJailOff");
			LAi_SetHuberType(sld);
			sld.Dialog.Filename = "Common_Prison.c";
			sld.Dialog.CurrentNode = "First_officer";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MatthewLutter", "mercen_15", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Matthew";
			sld.lastname = "Lutter";
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_MatthewLutter1";
			ChangeCharacterAddressGroup(sld, "Beliz_prison", "goto", "goto9");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_MatthewLutter1":
			dialog.text = "Ele roubou meu tesouro!";
			link.l1 = "Matthew Lutter?";
			link.l1.go = "PZ_MatthewLutter2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MatthewLutter2":
			dialog.text = "O meu tesouro agora pertence a ele, você sabe, A ELE! Não há nada que possamos fazer! O que você quer?! Quer tirar mais alguma coisa de nós? Não sobrou nada! Ela vai morrer! Ou pior!";
			link.l1 = "Quem vai morrer? Que tesouro? Deixa pra lá, a culpa é sua mesmo – foi você quem atacou aquele galeão, não o contrário.";
			link.l1.go = "PZ_MatthewLutter3";
		break;
		
		case "PZ_MatthewLutter3":
			dialog.text = "Não! Foi o contrário! Maldito seja aquele hidalgo! É por causa dele que estamos nessa enrascada! Ele veio direto pra cima da gente e atirou à queima-roupa! Depois levou ela de nós!";
			link.l1 = "Sério? Isso não me surpreende. O que mais pode nos contar sobre ele? E... o que ele levou? Quem é 'ela'?";
			link.l1.go = "PZ_MatthewLutter5";
		break;
		
		case "PZ_MatthewLutter5":
			dialog.text = "Ah-ah-ah!!! A-A-A-A!!!";
			link.l1 = "Entendi, estou perdendo meu tempo...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonSoldierDialog");
		break;
		
		case "PZ_BelizPrisonQuestSoldier1":
			dialog.text = "Capitão, com sua permissão... Lutter! Fora! Fim da linha, camarada.";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongway_UvodyatNaKazn");
		break;
		
		case "PZ_Longway_35":
			dialog.text = "Capitão, precisamos descobrir mais sobre Sotta e Lutter. Vamos perguntar por aí.";
			link.l1 = "Boa ideia, Longway. Não conseguimos muita coisa com aquele homem gritando mesmo.";
			link.l1.go = "PZ_Longway_36";
		break;
		
		case "PZ_Longway_36":
			dialog.text = "Mas é melhor começar com Sotta.";
			link.l1 = "Certo, é ele que estamos procurando. Vamos.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongwayBack");
		break;
		
		case "PZ_Longway_37":
			dialog.text = "Eles não sabem de nada!";
			link.l1 = "Obviamente. Mas já temos o suficiente para começar a pensar por conta própria. Pelo que ouvi, Sotta provavelmente vai tentar vender aquelas mercadorias estratégicas que recebeu como recompensa, e logo.";
			link.l1.go = "PZ_Longway_38";
		break;
		
		case "PZ_Longway_38":
			dialog.text = "Exatamente!";
			link.l1 = "Devemos interceptá-lo no caminho, em Port Royal ou Capsterville. A única questão é para onde ele está indo e onde devemos enfrentá-lo. Ou talvez consigamos pegá-lo em alto-mar.";
			link.l1.go = "PZ_Longway_39";
		break;
		
		case "PZ_Longway_39":
			dialog.text = "Não! Longway quis dizer... Fermentelos é um capitão experiente. Uma luta em alto-mar pode dar em qualquer coisa. Teríamos mais chances de pegá-lo de surpresa no porto.";
			link.l1 = "Você tem razão, eu acho. Não importa o que realmente aconteceu entre Matt e ele, Sotta é perigoso e não pode ser subestimado.";
			link.l1.go = "PZ_Longway_40";
		break;
		
		case "PZ_Longway_40":
			dialog.text = "Também não vemos a hora!";
			link.l1 = "Certo de novo, Longway. Então vamos içar a âncora imediatamente, e depois planejamos nosso próximo passo.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayBelizDialogBack");
			DelMapQuestMarkCity("Beliz");
		break;
		
		case "PZ_Longway_41":
			dialog.text = "Meu Senhor Capitão, a Estrela da Manhã está no porto!";
			link.l1 = "Sim, eu já percebi.";
			link.l1.go = "PZ_Longway_42";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Longway_42":
			dialog.text = "Qual é o seu plano?";
			link.l1 = "Ainda não decidi. Tentar abordar eles sob os canhões do forte seria suicídio. E mesmo que a gente capture o galeão deles, não vamos conseguir fugir com ele. Tem alguma ideia, Longway?";
			link.l1.go = "PZ_Longway_43";
		break;
		
		case "PZ_Longway_43":
			dialog.text = "Sim. Podemos ancorar em uma enseada segura e nos aproximar do galeão de barco, sob a cobertura da noite.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				link.l1 = "E quanto à Baía da Meia Lua, Longway?";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				link.l1 = "Acho que Portland Cove seria uma boa escolha – perto o bastante e relativamente segura. O que acha?";
			}
			link.l1.go = "PZ_Longway_44";
		break;
		
		case "PZ_Longway_44":
			dialog.text = "Boa escolha.";
			link.l1 = "Ótimo, está decidido. Esquecemos de alguma coisa?";
			link.l1.go = "PZ_Longway_45";
		break;
		
		case "PZ_Longway_45":
			dialog.text = "Acho que não, Meu Senhor Capitão. Só precisamos estar bem preparados.";
			link.l1 = "Com certeza.";
			link.l1.go = "PZ_Longway_46";
		break;
		
		case "PZ_Longway_46":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CabinLock");
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			bQuestDisableMapEnter = false;
			AddQuestRecord("PZ", "21");
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				AddQuestUserData("PZ", "sText", "Half Moon Bay");
				Island_SetReloadEnableGlobal("Nevis", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore43";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				AddQuestUserData("PZ", "sText", "Portland Cove");
				Island_SetReloadEnableGlobal("Jamaica", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore36";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition = "PZ_ZvezdaUhodimNaGlobalkru_Proval";
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan":
			dialog.text = "Quem diabos é você, o que está acontecendo? Senhor Holmes!";
			link.l1 = "O senhor Holmes não trabalha mais aqui. E nós trancamos todas as escotilhas bem fechadas. Então, não seremos incomodados por um tempo, Mynheer Fermentelos.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_2":
			dialog.text = "O quê? Fermentelos? Meu nome é Edgardo Sotta!";
			link.l1 = "Ahã, já ouvi essa antes. Sabemos que esse não é seu nome de verdade, Oliveiro.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_3";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_3":
			dialog.text = "Fermentelos está morto!";
			link.l1 = "Pensando bem, você realmente parece jovem demais. Obviamente não poderia ter sido o capitão do Morning Star há dez anos. Então, o que aconteceu com Oliveiro?";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_4";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_4":
			dialog.text = "Nós nos livramos dele. Ele era só mais um problema que tivemos que resolver - assim como o que está aí do seu lado.";
			link.l1 = "Bem, já que você não é o Fermentelos, talvez ainda possa responder nossas perguntas. Estamos procurando alguém que ele tirou do meu amigo.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_5";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_5":
			dialog.text = "Eu não vou te contar nada! Ele nunca vai me perdoar por isso.";
			link.l1 = "Agora, é melhor você se preocupar se vamos te perdoar...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_SottaFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_AnabelleLutter1":
			dialog.text = "Ele finalmente morreu...";
			link.l1 = "That's right. And who are you, madam? Did he hold you against your will? I sympathize; you must have been through a terrible ordeal...";
			link.l1.go = "PZ_AnabelleLutter2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_AnabelleLutter2":
			dialog.text = "Eu sou Annabel Lutter. E graças a Deus, não precisei passar por muita coisa, mas agradeço sua preocupação, senhor...?";
			link.l1 = "Capitão Charles de Maure. Lutter, você disse...";
			link.l1.go = "PZ_AnabelleLutter3";
		break;
		
		case "PZ_AnabelleLutter3":
			dialog.text = "Ah, você já deve ter ouvido falar do Matt? Coitado... Eu fui a... consorte dele.";
			link.l1 = "Sinto muito pela sua perda, Sra. Lutter. Agora a senhora é viúva. Qual era seu nome de solteira, se não for segredo?";
			link.l1.go = "PZ_AnabelleLutter4";
		break;
		
		case "PZ_AnabelleLutter4":
			dialog.text = "Eu não tive um. Olhe bem para mim. Minha pobre mãe era uma escrava de pele escura dos piratas. Ninguém sabe quem era meu pai, então nem se preocuparam em me dar um nome de verdade.";
			link.l1 = "Por que ninguém encostou em você naquela época? Não me leve a mal – fico feliz que isso não tenha acontecido. Mas ainda assim, é... incomum.";
			link.l1.go = "PZ_AnabelleLutter5";
		break;
		
		case "PZ_AnabelleLutter5":
			dialog.text = "You're right. But let's call things by their proper names. I'm not a pampered noblewoman; I'm the daughter of a slave. I won't faint from a heavy conversation.";
			link.l1 = "Hum, eu também não sou de fazer agrados. Mas continue, por favor. Por que a tripulação não tocou na filha da escrava? Você não conhece seu pai, e ele não parecia se importar.";
			link.l1.go = "PZ_AnabelleLutter6";
		break;
		
		case "PZ_AnabelleLutter6":
			dialog.text = "Suponho que não. Já que você sabe sobre o Matt, sabe que ele trabalhou para o Levasseur por um tempo?";
			link.l1 = "Sim, ouvi falar disso enquanto procurava pela Estrela da Manhã. Mas o que isso tem a ver com o assunto? Me conte tudo, por favor.";
			link.l1.go = "PZ_AnabelleLutter7";
		break;
		
		case "PZ_AnabelleLutter7":
			dialog.text = "Você ainda não entendeu, não é? Pelo visto, você não ouviu falar das... preferências do Levasseur?";
			link.l1 = "Eu não vi, mas então, o que isso tem a ver com...?";
			link.l1.go = "PZ_AnabelleLutter8";
		break;
		
		case "PZ_AnabelleLutter8":
			dialog.text = "Ah, acho que vou ter que te contar tudo. Sente-se se for muito sensível, senhor. O negócio é que ele dorme com muitas mulheres, e...";
			if (pchar.questTemp.FMQT == "end")
			{
				link.l1 = "A esposa dele não está longe dele, e ela se deita com quase qualquer um.";
				link.l1.go = "PZ_AnabelleLutterKnow1";
			}
			else
			{
				link.l1 = "Oh não.";
				link.l1.go = "PZ_AnabelleLutterDontKnow1";
			}
		break;
		
		case "PZ_AnabelleLutterKnow1":
			dialog.text = " Bem, você sabe o que dizem... tal marido, tal esposa. Mas não, tenho certeza de que ele foi muito além disso.";
			link.l1 = "E até onde?";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutterDontKnow1":
			dialog.text = "Seu sarcasmo não cabe aqui, senhor. Você não faz ideia do que estamos falando.";
			link.l1 = "Tudo bem, tudo bem, me desculpe. Continue, por favor.";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutter9":
			dialog.text = "Não é só trair a esposa. Ele força mulheres contra a vontade delas. E não é um abuso isolado. Ele sequestra moças e as mantém em uma das adegas que possui.";
			link.l1 = "Então ele recebe escravas regularmente? E você deveria ser uma delas?";
			link.l1.go = "PZ_AnabelleLutter10";
		break;
		
		case "PZ_AnabelleLutter10":
			dialog.text = "Você está certo quanto ao último. Mas, infelizmente, não quanto ao primeiro. Ele não precisa de escravos. Levasseur é insano – do seu próprio jeito, não como meu Matt. François queria possuir uma mulher por completo, corpo e alma. E não era por amor, claro. Ele precisava de mulheres livres para quebrar a vontade delas. Ele gostava de ver como o olhar, o comportamento e o jeito de falar delas mudavam com o tempo...";
			link.l1 = "Nojento...";
			link.l1.go = "PZ_AnabelleLutter11";
		break;
		
		case "PZ_AnabelleLutter11":
			dialog.text = "Você já está se sentindo meio mal. Agora imagine como foi para aquelas mulheres. Ouvi falar de tudo isso, e não só pelo Matt. Levasseur já teve uma nobre portuguesa...";
			link.l1 = "Você desviou o olhar e ficou em silêncio. Conte-nos tudo. Já vi de tudo no Velho Mundo e também durante meu tempo no Arquipélago. Nada mais me surpreende.";
			link.l1.go = "PZ_AnabelleLutterWant1";
			link.l2 = "Pare, eu não quero saber o que aconteceu com ela. Espero que aquelas mulheres não tenham sofrido muito tempo nas mãos dele.";
			link.l2.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutterWant1":
			dialog.text = "Mas você nunca ouviu falar de algo assim. E espero que nunca veja. Ela foi levada até ele ainda orgulhosa, ainda não quebrada, mesmo tendo sido, como Matt me contou, estuprada pelos homens de Levasseur durante todo o caminho até Tortuga, depois que tomaram a fazenda do marido dela perto de Campeche – ele morreu de hemorragia depois que aqueles monstros atiraram nos dois joelhos dele...";
			link.l1 = "Uma mulher forte... Mas você disse que o Levasseur normalmente não tocava nas mulheres que ele queria para si.";
			link.l1.go = "PZ_AnabelleLutterWant2";
		break;
		
		case "PZ_AnabelleLutterWant2":
			dialog.text = "Aqueles que ele pediu especificamente foram deixados em paz. Mas Dona Leontina foi um presente. Um presente inesperado e agradável para todos eles. Então, eles se permitiram aproveitar...";
			link.l1 = "Entendi...";
			link.l1.go = "PZ_AnabelleLutterWant3";
		break;
		
		case "PZ_AnabelleLutterWant3":
			dialog.text = "Acho que... o Matt tinha se tornado um dos favoritos do François. Ele foi convidado para uma das festas secretas do Levasseur... Durante o banquete, um dos piratas reclamou que não havia mulheres suficientes. Levasseur riu e então...";
			link.l1 = "E depois? O que aconteceu?";
			link.l1.go = "PZ_AnabelleLutterWant4";
		break;
		
		case "PZ_AnabelleLutterWant4":
			dialog.text = "...então ela foi trazida. Com uma coleira! Espancada, as costas arranhadas, vendada e amordaçada. Quando tiraram a mordaça, tudo o que ela disse foi...";
			link.l1 = "Algo horrível, imagino. Ela o amaldiçoou com tudo o que tinha?";
			link.l1.go = "PZ_AnabelleLutterWant5";
		break;
		
		case "PZ_AnabelleLutterWant5":
			dialog.text = "Se ao menos... Dona Leontina apenas sussurrou: 'O que deseja meu senhor?'";
			link.l1 = "Acho que vou vomitar. Matt te contou o que aconteceu com ela depois?";
			link.l1.go = "PZ_AnabelleLutterWant6";
		break;
		
		case "PZ_AnabelleLutterWant6":
			dialog.text = "Assassinada, é claro. Mas não pelas mãos de Levasseur. Ele a descartou como um cão sem dono. Um dos capitães dele atirou nela. Antes de morrer, ela só disse uma palavra...";
			link.l1 = "Uma maldição? Uma oração?";
			link.l1.go = "PZ_AnabelleLutterWant7";
		break;
		
		case "PZ_AnabelleLutterWant7":
			dialog.text = "Não. 'Obrigado...'";
			link.l1 = "Ser grato pela morte depois de tanto tormento... O que ela deve ter suportado... e outros como ela naquele covil de monstro...";
			link.l1.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutter12":
			dialog.text = "Levasseur desprezava especialmente os escravizados e as mulheres de pele escura – dizia que não havia nada nelas que pudesse ser quebrado. Elas não duravam muito com ele, e os indígenas também não – só alguns poucos realmente teimosos. Mas selvageria e rebeldia também não eram resposta – ele matava tanto quem tentava agradá-lo cedo demais quanto quem permanecia desafiador por tempo demais.";
			link.l1 = "Isso é horrível... Diga-me, Levasseur já teve mulheres asiáticas?";
			link.l1.go = "PZ_AnabelleLutter13";
		break;
		
		case "PZ_AnabelleLutter13":
			dialog.text = "Não, pelo menos não que eu saiba. Quanto a mim... Já te contei que ele não gostava de mulheres de pele escura. Então, quando Matt trabalhava para o François, ele andava comigo abertamente pelas ruas de Tortuga. Chegou até a me levar à residência uma vez.";
			link.l1 = "Mas Levasseur queria te transformar em um dos escravos dele de qualquer jeito...";
			link.l1.go = "PZ_AnabelleLutter14";
		break;
		
		case "PZ_AnabelleLutter14":
			dialog.text = "Exatamente... Eu não sei por que ele gostava tanto de mim... Quando Matt descobriu, ele fugiu da ilha assim que soube. Nunca mais voltou para Tortuga. Talvez fosse um pouco louco, mas ele me amava. Ele me chamava de seu tesouro...";
			link.l1 = "Então era isso que ele queria dizer quando falou que Sotta tirou o tesouro dele!";
			link.l1.go = "PZ_AnabelleLutter15";
		break;
		
		case "PZ_AnabelleLutter15":
			dialog.text = "Heh, ele disse isso? Ah, Matt... Mas parece que nunca fomos feitos para envelhecer juntos. Se Levasseur colocava os olhos numa mulher, ele fazia qualquer coisa para tê-la, não importava quem fosse ou o preço. Sotta era um dos capitães dele, e fez o que mandaram.";
			link.l1 = "Entendi. E o que pretende fazer agora, Annabel?";
			link.l1.go = "PZ_AnabelleLutter16";
		break;
		
		case "PZ_AnabelleLutter16":
			dialog.text = "Correr. Para algum lugar onde os homens do Levasseur não possam me encontrar. Mudar meu nome. Me disfarçar...";
			link.l1 = "Espero que você consiga. Desejo tudo de melhor para você, Annabel.";
			link.l1.go = "PZ_AnabelleLutter17";
			if (sti(pchar.Money) >= 10000)
			{
				link.l2 = "Você vai precisar de dinheiro para conseguir uma passagem. Pegue isto. Aqui tem dez mil pesos.";
				link.l2.go = "PZ_AnabelleLutter17_Peso";
			}
			if (PCharDublonsTotal() >= 100)
			{
				link.l3 = "Você vai precisar de mais do que um pouco de dinheiro. Nem todos estão dispostos a ajudar uma garota de pele escura, mesmo que seja mestiça. Aqui, pegue cem dobrões – encontre um navio e se esconda.";
				link.l3.go = "PZ_AnabelleLutter17_Dublon";
			}
		break;
		
		case "PZ_AnabelleLutter17":
			dialog.text = "Você também! Adeus, Capitão.";
			link.l1 = "Adeus.";
			link.l1.go = "Exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Peso":
			dialog.text = "Eu... Eu não sei o que dizer. Ninguém além do Matt jamais foi tão gentil comigo.";
			link.l1 = "Talvez seja um sinal. Que você vai envelhecer feliz em algum lugar, afinal. Adeus.";
			link.l1.go = "Exit";
			AddMoneyToCharacter(pchar, -10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Dublon":
			dialog.text = "Você está certo. Muito obrigado por isso. Vou lembrar de você nas minhas orações pelo resto da minha vida.";
			link.l1 = "Obrigado. Boa sorte.";
			link.l1.go = "Exit";
			RemoveDublonsFromPCharTotal(100);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_Longway_47":
			dialog.text = "Aquele homem... Não, ele já não é mais um homem. É uma besta. Um monstro. Torturando mulheres daquele jeito...";
			link.l1 = "Eu sei o que você está pensando, Longway. Mas você ouviu – ele nunca teve uma mulher de pele amarela.";
			link.l1.go = "PZ_Longway_48";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Longway_48":
			dialog.text = "Mas ele conhecia o grupo todo! Van der Vink, Fermentelos, Sotta... Acabamos de ler sobre isso no diário dele. E se essa tal 'ela' for... ela mesma?";
			link.l1 = "Quem sabe... Uma mulher determinada a se vingar de Fermentelos – é fácil entender por que você pensaria isso. Mas poderia ser qualquer mulher cuja vida foi destruída por Oliveiro. Não precisa ser sua irmã. Nem precisa ser uma mulher de pele amarela.";
			link.l1.go = "PZ_Longway_49";
		break;
		
		case "PZ_Longway_49":
			dialog.text = "Você está... recusando tentar isso, Senhor Capitão? Bem na última hora...?";
			link.l1 = "Não, Longway. Mas como você imagina isso? É improvável que Levasseur responda a qualquer uma das nossas perguntas. E ficar farejando por Tortuga desse jeito é perigoso demais.";
			link.l1.go = "PZ_Longway_50";
		break;
		
		case "PZ_Longway_50":
			dialog.text = "E então, o que sugere?";
			link.l1 = "Vamos esperar. Sabemos que o Levasseur não gosta de mulheres como sua irmã. Então podemos poupar nossos recursos por enquanto. Paciência e força. François é um osso duro de roer, principalmente por causa da 'tartaruga' dele. Mas com a ajuda do Svenson, podemos falar com ele do nosso jeito. Eu prometi que ia te ajudar a encontrar sua irmã e pretendo cumprir isso. Você acredita em mim, Longway?";
			link.l1.go = "PZ_Longway_51";
		break;
		
		case "PZ_Longway_51":
			dialog.text = "Hmm... Sim, sim, Meu Senhor Capitão. Mas Longway tem mais um pedido para você.";
			link.l1 = "O que foi? Você não está pensando em sair sozinho de novo, está? Da última vez não acabou muito bem.";
			link.l1.go = "PZ_Longway_52";
		break;
		
		case "PZ_Longway_52":
			dialog.text = "De jeito nenhum, Senhor Capitão. Agora percebo que, infelizmente, um homem como eu não pode fazer nada sozinho num mundo governado por homens brancos. Longway pede que você atraque em Capsterville e entregue uma carta a Georges Gravel, pedindo que ele descubra qualquer coisa enquanto você se prepara.";
			link.l1 = "Uma ideia sensata, Longway. Vamos fazer isso.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToShore");
		break;
		
		case "PZ_Longway_53":
			dialog.text = "Senhor Capitão, Longway precisa lhe perguntar uma coisa...";
			link.l1 = "Você esqueceu de escrever a carta? Você pode simplesmente falar com o Gravel.";
			link.l1.go = "PZ_Longway_54";
		break;
		
		case "PZ_Longway_54":
			dialog.text = "Não, a carta já está pronta. Mas Longway achou melhor não andar sozinho pela cidade. Meu Senhor Capitão... poderia entregar a carta para o Georges por mim? Por favor?";
			link.l1 = "Eu pareço um mensageiro pra você? Ou é você quem manda aqui?";
			link.l1.go = "PZ_Longway_55";
		break;
		
		case "PZ_Longway_55":
			dialog.text = "Meu Senhor Capitão...";
			link.l1 = "Ha ha ha, estou só brincando, Longway! Me lembra onde encontro esse seu Gravel?";
			link.l1.go = "PZ_Longway_56";
		break;
		
		case "PZ_Longway_56":
			dialog.text = "Ele trabalha na igreja.";
			link.l1 = "Beleza, eu cuido disso.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToCapstervilleChurch");
			AddLandQuestMark(characterFromId("Charles_Priest"), "questmarkmain");
		break;
		
		// Этап 5
		case "PZ_Mary_Sharptown1":
			dialog.text = "Charles, meu querido Charles, aconteceu alguma coisa? Você parece preocupado e... cansado, né.";
			link.l1 = "Ah, não, não, Mary, estou bem. É só... essa minha busca em Tortuga. Parece que chegou a um beco sem saída... de novo. E aquele testamento do Sharp realmente me desgastou, pelo amor de Deus. Mas deixa pra lá.";
			link.l1.go = "PZ_Mary_Sharptown2";
		break;
		
		case "PZ_Mary_Sharptown2":
			dialog.text = "O quê? Que missão? E o que isso tem a ver com o Sharp? Eu não entendo nada!";
			link.l1 = "Perguntas demais, Mary. Aqui não é lugar pra esse tipo de conversa. Que tal falarmos sobre isso no quarto da taverna? Do jeitinho que você gosta, longe dos olhos e da cabeça. Vou te contar o que andei fazendo no último ano.";
			link.l1.go = "PZ_Mary_Sharptown3";
		break;
		
		case "PZ_Mary_Sharptown3":
			dialog.text = "Beleza! Mas fique avisado: se estiver escondendo alguma coisa...";
			link.l1 = "De jeito nenhum! Vamos, temos tempo de sobra mesmo...";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_Helena_Sharptown1":
			dialog.text = "Que estranho, não é, Charles? Era para eu ser dono desta ilha, mas não sinto que ela me pertença de verdade.";
			link.l1 = "Você acha?";
			link.l1.go = "PZ_Helena_Sharptown2";
		break;
		
		case "PZ_Helena_Sharptown2":
			dialog.text = "Ah, esse seu sorriso... Você sabe mesmo como tratar uma garota. Mas o que houve com você? Seu rosto está todo estranho!";
			link.l1 = "Por quê? É o meu rosto de sempre, muito bonito também.";
			link.l1.go = "PZ_Helena_Sharptown3";
		break;
		
		case "PZ_Helena_Sharptown3":
			dialog.text = "Charles, eu percebo pela sua voz – você anda abatido ultimamente.";
			link.l1 = "Tenho muita coisa pra resolver, especialmente com o Longway. Estou simplesmente exausta. Mas já é tarde demais pra desistir, ainda mais depois da promessa que fiz pra ele e pro meu pai.";
			link.l1.go = "PZ_Helena_Sharptown4";
		break;
		
		case "PZ_Helena_Sharptown4":
			dialog.text = "Eu não entendo... O que o Longway tem a ver com isso? E que promessas você fez?";
			link.l1 = "Se vamos conversar sobre isso, que seja na taverna, alugue um quarto. Longe dos outros.";
			link.l1.go = "PZ_Helena_Sharptown5";
		break;
		
		case "PZ_Helena_Sharptown5":
			dialog.text = "Certo, vamos. Não há mais nada a fazer mesmo, então pelo menos podemos passar um tempo juntos.";
			link.l1 = "Mostre o caminho, querido!";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_HelenaMary_Exit":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			WaitDate("", 0, 0, 0, 2, 0);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
			DoQuestReloadToLocation("Pirates_tavern_upstairs", "goto", "goto2", "PZ_Etap5_NaverhuTavernBandits");
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Olha como eles dormem docemente nos braços um do outro! Que lindo!";
				link.l1 = "Com ciúmes?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Acordem e animem-se! Dormiram bem, pombinhos?";
				link.l1 = "Bem, obrigado por perguntar. E vocês, dormiram bem?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_2";
			locCameraFromToPos(2.34, 1.92, 1.66, true, -1.66, -0.69, -0.02);
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Essa é uma pergunta boba, não acha?";
				link.l1 = "É sim. E foi uma estupidez da sua parte. Quer saber por quê?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Dizem que você tem uma língua afiada, Charles de Maure.";
				link.l1 = "E não só a minha língua. Quer descobrir? Mas me diga, por que não atacou enquanto dormíamos?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_3";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "E por que isso?";
				link.l1 = "Você não devia irritar a Mary de manhã. Logo vai descobrir o porquê.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Simples! Estava escuro, sabe, então não dava pra saber qual de vocês era a garota.";
				link.l1 = "Bastardo.";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_4";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Ao contrário de você, eu não tenho medo de mulher. Aliás, rapazes, levem ela inteira e sem um arranhão, ou o huguenote vai transformar a gente em mulher também!";
				link.l1 = "Hu... quem?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Pelo menos eu pareço um homem. Rapazes, peguem a loira viva – o huguenote está esperando por ela.";
				link.l1 = "Hu... quem?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_5";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_NaverhuTavernBandits_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "PZ_Etap5_NaverhuTavernBandits_Win");
			}
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_1":
			DelLandQuestMark(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Quem era aquele, Charles? Quem diabos é esse huguenote? Será que é mesmo...?";
				link.l1 = "Só tem uma, Mary. E é melhor a gente...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Charles... o que foi isso? Um huguenote? É esse o homem que estou pensando?";
				link.l1 = "Receio que sim, Helen. Precisamos...";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_2";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Está ouvindo isso? Alguém está vindo, né. Devem ser amigos desses homens mortos, provavelmente.";
				link.l1 = "Então veremos eles se juntar a eles. Prepare-se...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Está ouvindo isso? Passos.";
				link.l1 = "Sim, eu sei. Fique atrás de mim.";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_3";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_61";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_Longway_61":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Meu Senhor Capitão, senhora "+sStr+".";
			link.l1 = "Longway?! Você acha que pode entrar no nosso quarto assim, do nada? E se a gente estivesse...?";
			link.l1.go = "PZ_Longway_62";
			
			//заранее создаём заглушку для корабля
			sld = GetCharacter(NPC_GenerateCharacter("PZ_ShipStasis", "citiz_46", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			SetSPECIAL(sld, 1, 1, 1, 1, 1, 1, 1);
		break;
		
		case "PZ_Longway_62":
			dialog.text = "Hm, me perdoe, Senhor Capitão. Achei que teria fechado a porta se estivesse ocupado assim. Mas Longway a encontrou aberta.";
			link.l1 = "Quebrado, não aberto. Mas me diga, meu amigo, por que você está tão calmo assim? Tem corpos no chão, estamos armados, e você...";
			link.l1.go = "PZ_Longway_63";
		break;
		
		case "PZ_Longway_63":
			dialog.text = "Bem, já estou acostumado com isso.";
			link.l1 = "E você não pode discordar disso, pode? Mas falando sério, você não ouviu os sons da briga quando chegou aqui? Não viu esses brutamontes entrando na taverna e subindo as escadas bem na sua frente? ";
			link.l1.go = "PZ_Longway_64";
		break;
		
		case "PZ_Longway_64":
			dialog.text = "Não, Senhor Capitão. Não vi nenhum estranho no salão enquanto subia até aqui.";
			link.l1 = "Isso é uma coincidência absurda. Então, o que você quer, Longway?";
			link.l1.go = "PZ_Longway_65";
		break;
		
		case "PZ_Longway_65":
			dialog.text = "Eu preciso urgentemente de um navio e de uma tripulação, Meu Senhor Capitão.";
			link.l1 = "O quê? Por quê? Você finalmente conseguiu uma pista da Chang Xing? Nesse caso, vamos atrás dela agora mesmo, juntos.";
			link.l1.go = "PZ_Longway_66";
		break;
		
		case "PZ_Longway_66":
			dialog.text = "Não é o Chang Xing, infelizmente. É... Joep van der Vink. Georges Gravel mandou um recado e eu o recebi enquanto passeava pela vila, enquanto você... descansava com a senhora.";
			link.l1 = "Sim, descansei muito bem, posso te garantir isso. Mas por que deveríamos nos separar agora, Longway? Temos uma lista enorme de tarefas importantes para cumprir e pessoas perigosas para eliminar.";
			link.l1.go = "PZ_Longway_67";
		break;
		
		case "PZ_Longway_67":
			dialog.text = "Van der Vink não é tão perigoso quanto Levasseur. Além disso, já o derrotei uma vez. E vou derrotá-lo de novo. Desta vez, para garantir que ele esteja morto de verdade. Não quero que todos nós percamos tempo precioso com ele. Você deveria ir até Tortuga e perguntar às pessoas importantes sobre tudo o que precisamos. Eu mesmo vou capturar van der Vink. Meu Senhor Capitão, isso não vale o seu tempo e eu também já fui Capitão. Eu dou conta.";
			link.l1 = "Hmm, você tem razão, Longway. Van der Vink pode não ser tão perigoso, mas o 'Banten' é um dos navios mais rápidos do Arquipélago. Não é qualquer embarcação que consegue alcançá-lo. E quanto à tripulação? Como pretende reunir homens tão rápido e sozinho?";
			link.l1.go = "PZ_Longway_68";
		break;
		
		case "PZ_Longway_68":
			dialog.text = "Eu conheço o lugar certo e tenho prestígio com a Companhia lá. Ou pelo menos posso fingir que tenho, como fiz com Georges. A Companhia... O senhor Rodenburg usou os serviços deles quando precisava urgentemente de homens de luta, tripulações profissionais, que não fazem perguntas.";
			link.l1 = "Uma tripulação de navio para contratar, então... Faz sentido que algo assim exista. E quanto vai custar?";
			link.l1.go = "PZ_Longway_69";
		break;
		
		case "PZ_Longway_69":
			dialog.text = "Dois mil e quinhentos. Agora mesmo, na hora.";
			link.l1 = "É só isso? Normalmente é preciso bem mais do que isso pra contratar uma tripulação completa de marinheiros numa taverna, ainda mais pra um navio grande. Pelo visto, Rodenburg e os agentes dele têm preços especiais em lugares especiais.";
			link.l1.go = "PZ_Longway_70";
		break;
		
		case "PZ_Longway_70":
			dialog.text = "Quis dizer dobrões, Senhor Capitão.";
			link.l1 = "O QUÊ?!";
			link.l1.go = "PZ_Longway_70_4";
		break;
		
		case "PZ_Longway_70_4":
			dialog.text = "Ouviu bem, Meu Senhor Capitão. É importante. Eu não pediria uma quantia dessas por uma bobagem.";
			link.l1 = "Sim, eu ouvi você, mas ainda não consigo acreditar. Preços especiais, é mesmo. Eles aceitam pesos?";
			link.l1.go = "PZ_Longway_70_5";
		break;
		
		case "PZ_Longway_70_5":
			dialog.text = "Sim... de pessoas brancas. Longway pode ter problemas com isso, mas... acho que vou conseguir convencê-los se insistir o bastante. Sempre existe um jeito.";
			link.l1 = "Bom, isso já é alguma coisa. E isso é só para a tripulação... E ainda tem o navio para conseguir, né. Aposto que também está em algum 'lugar especial'? Tenho até medo de perguntar quanto isso vai nos custar...";
			link.l1.go = "PZ_Longway_70_6";
		break;
		
		case "PZ_Longway_70_6":
			dialog.text = "Não é bem assim, Meu Senhor Capitão. A tripulação já tem seu próprio navio.";
			link.l1 = "Mas?";
			link.l1.go = "PZ_Longway_70_7";
		break;
		
		case "PZ_Longway_70_7":
			dialog.text = "A 'Meifeng'. Ela pode se tornar um fator decisivo – nenhum navio no Arquipélago é mais rápido que ela. E ela é... era minha, então eu a conheço. Vai me emprestar ela, Meu Senhor Capitão?";
			if (PCharDublonsTotal() >= 2500)
			{
				link.l1 = "Aqui. Dois mil e quinhentos dobrões. Contanto que você me traga a cabeça do van der Vink numa bandeja de ouro maciço, ha ha ha ha!";
				link.l1.go = "PZ_Longway_Dublons_1";
			}
			if (sti(pchar.Money) >= 300000)
			{
				link.l2 = "Eu não ando por aí com tantos doblões, Longway. E duvido que eu tenha tudo isso nem mesmo no navio – você está falando de uma montanha de ouro. Mas pesos, tudo bem. Trezentos mil é exatamente o que você precisa.";
				link.l2.go = "PZ_Longway_Peso_1";
			}
			link.l3 = "Sabe de uma coisa, Longway... Você está mesmo sugerindo que eu gaste dinheiro suficiente para armar uma frota de cerco só para você lutar contra um bandido qualquer?!";
			link.l3.go = "PZ_Longway_Otkaz";
		break;
				
		case "PZ_Longway_Dublons_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "Oh... Longway agradece de todo o coração, Meu Senhor Capitão! Mas ainda assim, e quanto à 'Meifeng'?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "E o que tem ela? Meu amigo, você bateu a cabeça no caminho até aqui? Ela está na nossa frota agora mesmo!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Preciso pensar sobre isso, Longway.  Quanto tempo temos para alcançar van der Vink?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
			RemoveDublonsFromPCharTotal(2500);
			pchar.questTemp.PZ_FlagShipDublons = true;
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_Longway_Peso_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "Senhor Capitão, você cometeu um pequeno engano. Seriam duzentos e cinquenta mil pesos.";
			link.l1 = "I did not; it's Charles de Maure's special exchange rate when his friends need help, ha ha. I'm giving you extra so you'll have enough for everything.";
			link.l1.go = "PZ_Longway_Peso_2";
			AddMoneyToCharacter(pchar, -300000);
		break;
		
		case "PZ_Longway_Peso_2":
			dialog.text = "Muito obrigado, Senhor. Capitão... Mas, e quanto ao 'Meifeng'?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "E o que tem ela? Meu amigo, você bateu a cabeça no caminho pra cá? Ela está na nossa frota agora mesmo!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Preciso pensar sobre isso, Longway.  Quanto tempo temos para alcançar van der Vink?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
		break;
		
		case "PZ_Longway_Otkaz":
			dialog.text = "Não há outro jeito, Senhor Capitão, por favor, acalme-se...";
			link.l1 = "Ah, ainda não comecei. É o seguinte. Cinquenta mil pesos. Isso dá só o bastante pra comprar uma brigue no estaleiro, prepará-la pra batalha e até contratar uma tripulação.";
			link.l1.go = "PZ_Longway_Otkaz_2";
			AddMoneyToCharacter(pchar, -50000);
			
			pchar.questTemp.PZ.LongwayBrig = true; // Лонгвэй будет на бриге
			Notification_Approve(false, "Longway");
		break;
		
		case "PZ_Longway_Otkaz_2":
			dialog.text = "Mas, Meu Senhor Capitão. Isso pode bastar para um capitão branco! Nem todos vão querer negociar com Longway. Eles vão exigir muito antes de me vender qualquer coisa!";
			link.l1 = "Então, seja convincente! Você é bem habilidoso em negociar, pelo que vi da sua... proposta inicial. Ainda está aqui? Pegue esse dinheiro e vá, já que é tão urgente como você diz!";
			link.l1.go = "PZ_Longway_Otkaz_3";
		break;
		
		case "PZ_Longway_Otkaz_3":
			dialog.text = "Sim, sim, Meu Senhor Capitão...";
			link.l1 = "E não me olhe desse jeito. Te vejo depois em Tortuga. Boa sorte.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "58");
		break;
		
		case "PZ_Longway_Mayfang1":
			dialog.text = "Hum, não, Senhor Capitão. Claro que lembro. Longway só estava perguntando se você já está pronto para me deixar ficar com ela.";
			link.l1 = "Sou sim. Afinal, van der Vink está tão envolvido nas desgraças da sua irmã quanto as outras pessoas da nossa lista. Então, capturá-lo é realmente importante. Eu te dou o comando do Meifeng.";
			link.l1.go = "PZ_Longway_Mayfang2";
		break;
		
		case "PZ_Longway_Mayfang2":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "Eu não acredito... Obrigado, Meu Senhor Capitão!";
			link.l1 = "Ah, não é nada. Ela já foi seu navio, vou sempre me lembrar disso. Bem, vá em frente. Mate aquele filho da puta. Estou indo para Tortuga.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "59");
			Notification_Approve(true, "Longway");
		break;
		
		
		case "PZ_Longway_NoMayfang1":
			dialog.text = "O tempo é curto, Meu Senhor Capitão. Não devemos desperdiçá-lo – Chang Xing pode precisar da nossa ajuda...";
			link.l1 = "Eu sei disso, Longway. Mas afinal, quanto tempo exatamente nós temos para pegar o van der Vink?";
			link.l1.go = "PZ_Longway_NoMayfang2";
		break;
		
		case "PZ_Longway_NoMayfang2":
			dialog.text = "Alguns meses - ele segue a rota habitual por esse tempo antes de sumir por um tempo. É assim que ele faz, como Gravel me contou na carta.";
			link.l1 = "Certo. Vamos para o navio, então...";
			link.l1.go = "PZ_Longway_NoMayfang3";
		break;
		
		case "PZ_Longway_NoMayfang3":
			dialog.text = "Receio que minhas preparações precisem começar imediatamente, Meu Senhor Capitão. Assim poderemos partir assim que eu tiver a Meifeng. Preciso negociar com os homens com antecedência. ";
			link.l1 = "Onde a gente se encontra?";
			link.l1.go = "PZ_Longway_NoMayfang4";
		break;
		
		case "PZ_Longway_NoMayfang4":
			AddQuestRecord("PZ", "60");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			i = FindColony("Pirates");
			if (colonies[i].nation != ENGLAND)
			{
				dialog.text = "Bem aqui. Mas podemos nos encontrar no estaleiro, se for mais conveniente para você.";
				link.l1 = "E por que só eu não sabia que aqui dá pra contratar uma tripulação inteira de homens de luta pelo preço certo?";
				link.l1.go = "PZ_Longway_NoMayfangIslaTesoro1";
			}
			else
			{
				dialog.text = "Aqueles mercenários costumavam ter um lugar na Isla Tesoro, mas foram obrigados a se mudar para cá.";
				link.l1 = "Entendo o motivo. Então, onde devo te procurar em La Vega?";
				link.l1.go = "PZ_Longway_NoMayfangLaVega1";
			}
		break;
		
		case "PZ_Longway_NoMayfangIslaTesoro1":
			dialog.text = "Porque pouquíssimos sabem disso. E ainda menos podem pagar por isso. Mynheer Rodenburg foi o único cliente deles por muito tempo.";
			link.l1 = "Entendi. Tudo bem, Longway. Te vejo lá.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToPiratesShipyard");
		break;
		
		case "PZ_Longway_NoMayfangLaVega1":
			dialog.text = "A taverna, Senhor Capitão. Onde mais eu estaria?";
			link.l1 = "Isso mesmo. Até mais então, Longway! Se cuida.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToLaVegaTavern");
		break;
		
		case "PZ_Longway_WaitForShip1":
			dialog.text = "Meu Senhor Capitão, devo informar que a tripulação está pronta. Falta resolver apenas uma última questão. E quanto à 'Meifeng'?";
			link.l1 = "Até agora, ainda não escolhi um navio à sua altura, Longway.";
			link.l1.go = "PZ_Longway_WaitForShip2";
			if ((FindCompanionShips(SHIP_SCHOONER_W)) || (FindCompanionShips(SHIP_BRIG)) || (FindCompanionShips(SHIP_CORVETTE)) || (FindCompanionShips(SHIP_POLACRE)) || (FindCompanionShips(SHIP_XebekVML)) || (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				if (FindCompanionShips(SHIP_SCHOONER_W)) sStr = "War schooner";
				if (FindCompanionShips(SHIP_BRIG)) sStr = "Brig";
				if (FindCompanionShips(SHIP_CORVETTE)) sStr = "Corvette";
				if (FindCompanionShips(SHIP_POLACRE)) sStr = "Polacre";
				if (FindCompanionShips(SHIP_XebekVML)) sStr = "Xebek";
				if (FindCompanionShips(SHIP_BRIGANTINE)) sStr = "Brigantine";
				link.l2 = "'"+sStr+"' é seu.";
				link.l2.go = "PZ_Longway_NoQuestShip1";
			}
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l3 = "E quanto ao 'Meifeng'? Achou que eu ia deixá-la apodrecer?";
				link.l3.go = "PZ_Longway_Mayfang3";
			}
			if (FindCompanionShips(SHIP_CURSED_FDM))
			{
				link.l4 = "Tenho um... navio especial para você, Longway. É rápido. E ainda mais mortal que o Meifeng. É um galeão de guerra, o 'Coração Voador'.";
				link.l4.go = "PZ_Longway_Caleuche1";
			}
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				link.l5 = "Você gosta de xebecs, Longway. E quanto às polacras? Especialmente esta aqui, a 'Torero'. Não foi feita para regatas, claro, mas é bem poderosa.";
				link.l5.go = "PZ_Longway_Torero1";
			}
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				link.l6 = "Preciso confessar, nunca imaginei que um dia isso teria uma utilidade digna. O que acha deste galeão? O poderoso 'El Casador'!";
				link.l6.go = "PZ_Longway_ElCasador1";
			}
		break;
		
		case "PZ_Longway_NoQuestShip1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			
			// а теперь хором, дети: ненавижу костыли, ненавижу костыли, ненавижу костыли, нена... помогите!!!
			if ((FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_SCHOONER_W)
						{
							//pchar.questTemp.PZ.SchoonerW.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.SchoonerW.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwaySchoonerW = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIG)
						{
							//pchar.questTemp.PZ.Brig.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brig.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrig = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_CORVETTE)
						{
							//pchar.questTemp.PZ.Corvette.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Corvette.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayCorvette = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE)
						{
							//pchar.questTemp.PZ.Polacre.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.Polacre.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayPolacre = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_XebekVML)
						{
							//pchar.questTemp.PZ.Xebek.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Xebek.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayXebek = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIGANTINE)
						{
							//pchar.questTemp.PZ.Brigantine.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brigantine.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrigantine = true;
			}
			
			dialog.text = "Não é o 'Meifeng', Meu Senhor Capitão! O que aconteceu com o Meifeng?";
			link.l1 = "Longway! "+sStr+" está em perigo! E sua irmã também! E você está de mau humor porque não tem um navio como este?! Qualquer um ficaria feliz com um navio desses! Assuma o comando dela  e mostre ao van der Vink do que você é capaz.";
			link.l1.go = "PZ_Longway_NoQuestShip2";
		break;
		
		case "PZ_Longway_NoQuestShip2":
			dialog.text = "Está bem... Espero que o céu me traga boa sorte. E desejo o mesmo para você em Tortuga. Adeus, Senhor Capitão.";
			link.l1 = "Tenho certeza disso. Adeus, Longway.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			pchar.questTemp.PZ_NoQuestShip = true;
		break;
		
		case "PZ_Longway_Mayfang3":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "Ahm, não, Senhor Capitão. Claro que lembro. Longway só estava perguntando se já está pronto para me deixar compartilhar ela com você.";
			link.l1 = "Sou eu. Afinal, van der Vink está tão envolvido nas desgraças da sua irmã quanto as outras pessoas da nossa lista. Então, capturá-lo é realmente importante. Eu lhe entrego o comando do 'Meifeng'.";
			link.l1.go = "PZ_Longway_Mayfang4";
		break;
		
		case "PZ_Longway_Mayfang4":
			dialog.text = "Eu não acredito... Obrigado, Meu Senhor Capitão!";
			link.l1 = "Ah, não é nada. Ela já foi seu navio, sempre vou me lembrar disso. Bem, vá lá. Mate aquele filho da puta. Estou indo para Tortuga.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_Longway_Caleuche1":
			dialog.text = "Eu... Eu não posso comandar ISSO, Meu Senhor Capitão. Longway ainda se importa com sua vida, alma e sanidade.";
			link.l1 = "Ha ha ha, Longway! Ora, eu não sabia que você era tão supersticioso assim. Mas de qualquer forma, a maldição foi quebrada, então não há nada a temer.";
			link.l1.go = "PZ_Longway_Caleuche2";
		break;
		
		case "PZ_Longway_Caleuche2":
			dialog.text = "Ah... mas será que van der Vink sabe disso? Ele vai fugir feito um coelho assustado assim que vir aquele navio.";
			link.l1 = "Você tem razão quanto a isso. Tudo bem, vamos encontrar outra coisa para você.";
			link.l1.go = "PZ_Longway_WaitForShip2";
		break;
		
		case "PZ_Longway_Torero1":
			// если "Тореро" у ГГ
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE_QUEST)
						{
							//pchar.questTemp.PZ.Torero.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Torero.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayTorero = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				Notification_Approve(true, "Longway");
			}
			
			dialog.text = "Nunca comandei uma polaca quando naveguei sozinho. Ela é interessante, mas agora o mais importante é a velocidade, não a força.";
			link.l1 = "É verdade, mas é uma polaca, afinal. Talvez não seja tão rápida quanto o 'Banten', mas você consegue pegar o vento em ângulos que eles não conseguem. Até mais do que a própria 'Meifeng' jamais conseguiria. Então aproveite isso.";
			link.l1.go = "PZ_Longway_Torero2";
		break;
		
		case "PZ_Longway_Torero2":
			dialog.text = "Ainda assim... o 'Meifeng' era melhor... Pena que você deixou ela se perder, Meu Senhor Capitão. Boa sorte em Tortuga.";
			link.l1 = "O mesmo para você, Longway. Obrigado.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_ElCasador1":
			// если "Эль Касадор" у ГГ
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_ELCASADOR)
						{
							//pchar.questTemp.PZ.ElCasador.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.ElCasador.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayElCasador = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				Notification_Approve(true, "Longway");
			}
			
			dialog.text = "Pode ser o galeão mais incomum do Arquipélago, Meu Senhor Capitão. Eu consigo lidar com ele, mas é mais lento que o 'Banten'...";
			link.l1 = "Bem, você não está competindo com o Joep numa regata, está?";
			link.l1.go = "PZ_Longway_ElCasador2";
		break;
		
		case "PZ_Longway_ElCasador2":
			dialog.text = "Tanto faz. Mas o 'Meifeng' era melhor... Pena que você deixou ela se perder, Meu Senhor Capitão. Boa sorte em Tortuga.";
			link.l1 = "O mesmo pra você, Longway. Obrigado.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_WaitForShip2":
			NextDiag.TempNode = "PZ_Longway_WaitForShip1";
			
			dialog.text = "Agradeço sua preocupação, Meu Senhor Capitão, mas por favor, apresse-se – não temos muito tempo.";
			link.l1 = "Eu sei. Mas você não quer sair por aí correndo atrás do vento, quer? Tá bom, vou arrumar um navio de verdade pra você.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaTortugaCabin_1":
			dialog.text = "Estamos quase lá, Charles. Já decidiu por onde começar? Talvez faça sentido perguntarmos para as pessoas na rua...";
			link.l1 = "Talvez sim. Mas não para nós – para mim. Você vai ficar a bordo, Helen.";
			link.l1.go = "PZ_HelenaTortugaCabin_2";
		break;
		
		case "PZ_HelenaTortugaCabin_2":
			dialog.text = "Charles, é claro, ainda estou inquieto com aqueles canalhas e o que disseram, e faz sentido eu ficar sob a proteção da tripulação... Mas você ir sozinho para a toca da fera não me faz sentir mais seguro.";
			link.l1 = "Eu entendo. Mas se as coisas derem errado, é muito mais fácil fugir sozinho, sabendo que você está segura. É uma ordem, Helen. Espere por mim aqui e tente não se preocupar demais.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_MaryTortugaCabin_1":
			dialog.text = "Aqui está Tortuga, Charles, certo. Mal posso esperar para bater em algumas portas, perguntando o que aquele asno gordo queria de mim...";
			link.l1 = "É exatamente por isso que você vai ficar a bordo, minha querida.";
			link.l1.go = "PZ_MaryTortugaCabin_2";
			
			pchar.questTemp.MarySexBlock = true;
			pchar.quest.Mary_giveme_sex.over = "yes";
			pchar.quest.Mary_giveme_sex1.over = "yes";
		break;
		
		case "PZ_MaryTortugaCabin_2":
			dialog.text = "De jeito nenhum! Você acha mesmo que vou deixar você ir para terra sozinho?";
			link.l1 = "Acho que se Levasseur decidir terminar o que seus mercenários não conseguiram, não teremos chance de reagir. Não quero provocá-lo à toa, ainda mais porque meu alvo não é ele, mas sim Joep van der Vink.";
			link.l1.go = "PZ_MaryTortugaCabin_3";
		break;
		
		case "PZ_MaryTortugaCabin_3":
			dialog.text = "Então agora eu tô presa, né?";
			link.l1 = " Não estou te dando uma ordem, estou te pedindo, Mary.";
			link.l1.go = "PZ_MaryTortugaCabin_4";
		break;
		
		case "PZ_MaryTortugaCabin_4":
			dialog.text = "E se alguma coisa acontecer com você em algum beco daquela ilha maldita?";
			link.l1 = "Então eu prometo que não vou bancar o herói. E saber que você está em segurança vai me ajudar a correr mais rápido. Então me espere no navio e, pelo amor de Deus, não desembarque, aconteça o que acontecer.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_RobertMartin1":
			chrDisableReloadToLocation = true;
			
			dialog.text = "Quem é você? Duvido que tenha atravessado a praia só pra conversar.";
			link.l1 = "Isso mesmo. Charles de Maure. Rober Martene?";
			link.l1.go = "PZ_RobertMartin2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_RobertMartin2":
			dialog.text = "O Charles de Maure? Droga, só não me mete em encrenca. Sim, sou eu. Então, o que você quer?";
			link.l1 = "Me disseram que você é amigo do Joep van der Vink, e...";
			link.l1.go = "PZ_RobertMartin3";
		break;
		
		case "PZ_RobertMartin3":
			dialog.text = "Quem te contou isso? Vou arrancar as tripas dele. Bem, nós nos conhecemos, só isso. Não quero confusão porque ele te enfrentou.";
			link.l1 = "Heh, você desiste dos seus amigos tão fácil...";
			link.l1.go = "PZ_RobertMartin4";
		break;
		
		case "PZ_RobertMartin4":
			dialog.text = "Não pense assim. Não tenho medo de você. Mas por que se dar ao trabalho ou até mesmo criar problemas? Eu não conheço o Joep tão intimamente quanto te disseram. Você está procurando por ele?";
			link.l1 = "É, mais ou menos. Eu sei que ele já saiu de Tortuga, mas não custa nada saber mais sobre ele – por onde andou, com quem conversou. Você pode ajudar?";
			link.l1.go = "PZ_RobertMartin5";
		break;
		
		case "PZ_RobertMartin5":
			dialog.text = "Não ia te ajudar de qualquer jeito, então... por que não? Ele estava num bordel. O bordel. Acho que você pode pagar, então estou te contando.";
			link.l1 = "Um novo bordel? Um só já não basta pra você?";
			link.l1.go = "PZ_RobertMartin6";
		break;
		
		case "PZ_RobertMartin6":
			dialog.text = "Bem, não é novidade, mas pouca gente sabe disso. E só alguns podem pagar. Acho que chegou a sua vez. Mas fique avisado – só aceitamos dobrões. Se tentar passar prata, vai levar um chute no traseiro.";
			link.l1 = "Imaginei que sim. E onde você disse que fica esse bordel?";
			link.l1.go = "PZ_RobertMartin7";
		break;
		
		case "PZ_RobertMartin7":
			dialog.text = "Sabe aquele prédio com as colunas? É esse mesmo. E que anfitriã eles têm! Pele amarela, muito bonita! Hã, já vejo você babando, hein?";
			link.l1 = "Heh-heh, mais ou menos. Obrigado, Rober. Hoje você não terá problemas – você me ajudou muito.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LighthouseMartinGo");
		break;
		
		case "PZ_MaryTortugaCabin_11":
			dialog.text = "Você voltou finalmente, Charles! Eu não conseguia me achar em lugar nenhum, né!";
			link.l1 = "Não vou demorar, Mary. Tenho um pequeno assunto para resolver... Não vou te deixar curiosa – é coisa do Longway. Preciso visitar um bordel local.";
			link.l1.go = "PZ_MaryTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MaryTortugaCabin_12":
			dialog.text = "Eu sabia que não devia ter deixado você ir para terra sozinho. Ou esqueceu de pôr o chapéu e a cabeça esquentou... Ou bateu ela, né!";
			link.l1 = "Mary, me escuta. É possível que a dona deste lugar seja a irmã do Longway. Para ter certeza, eu precisaria vê-la, mas é só isso que vou fazer. Não posso fazer isso sem entrar. Mas não quero que você pense algo que não deve.";
			link.l1.go = "PZ_MaryTortugaCabin_13";
		break;
		
		case "PZ_MaryTortugaCabin_13":
			dialog.text = "Tem certeza de que não está mentindo pra mim, Charles?";
			link.l1 = "Mary, veja por esse lado... Você já ouviu falar de um homem avisando sua amada sobre...?";
			link.l1.go = "PZ_MaryTortugaCabin_14";
		break;
		
		case "PZ_MaryTortugaCabin_14":
			dialog.text = "Pare com isso agora mesmo, Charles, eu nem quero pensar nisso. Eu acredito e confio em você. E espero que você não fique lá mais tempo do que o necessário.";
			link.l1 = "Nem um minuto a mais, querida, eu prometo. Rapidinho, você vai ver.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_HelenaTortugaCabin_11":
			dialog.text = "Charles! Você voltou ainda mais rápido do que eu esperava. Mas o que aconteceu? Você não parece bem... Descobriu algo sobre Joep van der Vink?";
			link.l1 = "Ainda não. Descobri algumas coisas, mas para ir além... preciso ir a um... bordel. Não pelo motivo que você deve estar pensando, claro.";
			link.l1.go = "PZ_HelenaTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_HelenaTortugaCabin_12":
			dialog.text = "Um bordel? Eu não sabia que esses lugares ofereciam algo além do óbvio.";
			link.l1 = "Preciso conversar com o dono, só isso. E não é qualquer bordel. Dizem que é um lugar muito caro, só para gente da alta sociedade...";
			link.l1.go = "PZ_HelenaTortugaCabin_13";
		break;
				
		case "PZ_HelenaTortugaCabin_13":
			dialog.text = "Bem, então é perfeito pra você, querido. Ah, estou brincando. Ainda assim, não fico nada feliz que você vá lá. Mas...";
			link.l1 = "Eu prometo que estou indo estritamente por causa dos assuntos do Longway. É bem possível que a dona daquele lugar seja a irmã dele. Não vou demorar lá.";
			link.l1.go = "PZ_HelenaTortugaCabin_14";
		break;
		
		case "PZ_HelenaTortugaCabin_14":
			dialog.text = "Como quiser. Você não é obrigado a me contar essas coisas. Eu nunca prometi que não dormiria com outro homem. E mesmo assim, não faço isso. Porque é algo que considero natural.";
			link.l1 = "Em outras circunstâncias, eu teria levado você comigo, mas...";
			link.l1.go = "PZ_HelenaTortugaCabin_15";
		break;
		
		case "PZ_HelenaTortugaCabin_15":
			dialog.text = "Obrigada, mas não, obrigada. Charles, não se preocupe. Não sou uma garota ciumenta e idiota. Bom, talvez ciumenta, mas não idiota. E eu acredito em você. Boba sou eu!";
			link.l1 = "Obrigada, Helen. Eu já volto.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_PredupredilNashuDevushku":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.PZ_PredupredilNashuDevushku = true;
		break;
		
		case "PZ_ElitaShluha_1":
			dialog.text = "Oh, um rosto novo em nosso estabelecimento? Seja bem-vindo, monsieur. Comida, vinho envelhecido, um banho quente – tudo à sua espera, se puder pagar para passar um tempo com uma de nós.";
			link.l1 = "Obrigado pela recepção, mademoiselle. Mas não é por isso que estou aqui. Estou procurando por alguém...";
			link.l1.go = "PZ_ElitaShluha_2";
			
			// Убираем Мартэна с Маяка
			sld = characterFromID("PZ_RobertMartin");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			for (i=1; i<=3; i++)
			{
				sld = characterFromID("PZ_MayakPiraty_"+i);
				sld.lifeday = 0;
			}
			
			sld = characterFromID("PZ_RobertMartin_CloneMayakShip");
			sld.lifeday = 0;
			
			locations[FindLocation("Mayak6")].DisableEncounters = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak6")], false);
			RemoveGeometryFromLocation("Mayak6", "smg");
		break;
		
		case "PZ_ElitaShluha_2":
			dialog.text = "It is only with the heart that one can see rightly; what is essential is invisible to the eye.";
			link.l1 = "Lindo. Nunca ouvi essas palavras antes.";
			link.l1.go = "PZ_ElitaShluha_3";
		break;
		
		case "PZ_ElitaShluha_3":
			dialog.text = "Aqui somos instruídas, não apenas bonecas. A anfitriã acha que isso é essencial para o nosso estabelecimento.";
			link.l1 = "A dona da taverna! É ela que estou procurando. Ouvi dizer que ela tem a pele amarela. Me diga, é verdade? E qual é o nome dela, aliás?";
			link.l1.go = "PZ_ElitaShluha_4";
		break;
		
		case "PZ_ElitaShluha_4":
			dialog.text = "É verdade. Mas ela tem mais tino para negócios do que muitas mulheres brancas. O nome dela é Belle Etoile. Mas chega de conversa.";
			link.l1 = "Chega de conversa, você diz? Eu vim justamente para conversar. Vou fazer mais algumas perguntas e depois vou embora.";
			link.l1.go = "PZ_ElitaShluha_5";
		break;
		
		case "PZ_ElitaShluha_5":
			dialog.text = "E qual é o benefício disso para a casa? Aqui não se paga pelos corpos, mas pelo tempo. Quer conversar? Fique à vontade. Mas o dinheiro vem antes. E vamos sussurrar no quarto, longe de ouvidos curiosos. Não me importa o que fazemos lá dentro – não me importa se acendemos velas e rezamos. Um cliente já me pediu ajuda para escrever um poema. Outro só queria desabafar, me chamando de bom amigo. E um terceiro – só queria acender velas, para então...";
			link.l1 = "Bem, eu não quero saber – já ouvi algo desagradável recentemente. Quanto eu te devo?";
			link.l1.go = "PZ_ElitaShluha_6";
		break;
		
		case "PZ_ElitaShluha_6":
			dialog.text = "Duzentos e cinquenta doblões. Sem negociação. Se percebermos que estamos lidando com um farsante sem um tostão, jogamos ele pra fora sem nenhum remorso. E se for rico mas mão de vaca, aumentamos o preço – ele vai pagar do mesmo jeito.";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Aqui está, duzentas e cinquenta peças de ouro.";
				link.l1.go = "PZ_ElitaShluha_7";
			}
			link.l2 = "Eita, este lugar é mais caro do que aquele bordel na Jamaica. Posso voltar depois que conseguir o ouro?";
			link.l2.go = "PZ_ElitaShluha_Otkaz_1";
		break;
		
		case "PZ_ElitaShluha_7":
			dialog.text = "Ótimo. Por onde começamos? Jantar, com ou sem velas, banho, conversa?";
			link.l1 = "Não tenho muito tempo, então vamos direto às minhas perguntas. Mostre o caminho.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Otkaz_1":
			dialog.text = "Claro que pode. Paciência é uma das virtudes de uma cortesã. Expulsar um mendigo é uma coisa. Deixar um cavalheiro rico como o senhor ir buscar seu dinheiro, ou até mesmo pedir emprestado, é bem diferente.";
			link.l1 = "As virtudes de uma cortesã... Irônico. Já volto.";
			link.l1.go = "PZ_ElitaShluha_Otkaz_2";
		break;
		
		case "PZ_ElitaShluha_Otkaz_2":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
			npchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
			npchar.dialog.currentnode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again":
			dialog.text = "Bem-vindo de volta, monsieur! Então, quem é você? Um cavalheiro rico ou só está bancando um?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Claro, sou um cavalheiro rico, mademoiselle. Aqui está o seu ouro – duzentos e cinquenta dobrões, exatamente. Não precisa contar.";
				link.l1.go = "PZ_ElitaShluha_Again_1";
			}
			link.l2 = "Ainda estou sem dinheiro, só tenha um pouco de paciência comigo.";
			link.l2.go = "exit";
			NextDiag.TempNode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again_1":
			dialog.text = "Aqui a gente não conta. Hmm, algumas dessas moedas estão amassadas e quebradas – a patroa não vai gostar muito disso, mas pelo menos é ouro de verdade.";
			link.l1 = "Que pessoa... graciosa ela é.";
			link.l1.go = "PZ_ElitaShluha_Again_2";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Again_2":
			dialog.text = "Isso mesmo. Madame Etoile pode ser gentil e carinhosa, pode ser rígida, e pode ser implacável. Por isso, aliás, nós não contamos. A patroa nem sempre recebe na hora, mas sempre recebe o que lhe é devido. Se não for em ouro, é em sangue. Toda casa de tolerância precisa de protetores e patronos. E os nossos estão à altura do prestígio do lugar.";
			link.l1 = "Já paguei, então mostre o caminho.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
		break;
		
		case "PZ_ElitaShluha_IdemVKomnatu":
			DialogExit();
			pchar.PZ_ElitaShluha = npchar.id;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload3", "PZ_ElitaShluha_VKomnate", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			bDisableCharacterMenu = true;
		break;
		
		case "PZ_ElitaShluha_8":
			dialog.text = "Então, que perguntas você tem, monsieur? Vou tentar satisfazer sua... curiosidade.";
			link.l1 = "Sabe o que me interessa, mademoiselle – sua patroa, Madame Etoile.";
			link.l1.go = "PZ_ElitaShluha_9";
		break;
		
		case "PZ_ElitaShluha_9":
			dialog.text = "O que posso dizer sobre ela? Ela continua sendo um mistério, até para nós. Embora se preocupe com nosso bem-estar, saúde e segurança, ela não socializa nem se aproxima de nenhum de nós.";
			link.l1 = "Talvez ela não goste de conversas longas. Diga-me, ela fala com sotaque?";
			link.l1.go = "PZ_ElitaShluha_10";
		break;
		
		case "PZ_ElitaShluha_10":
			dialog.text = "Não, por que você acha isso? Só porque ela tem a pele amarela? Ela fala francês perfeito e mais várias línguas. E consegue conversar por horas sobre qualquer assunto com convidados e possíveis investidores.";
			link.l1 = "É mesmo? Interessante... Ela está aqui agora? Se estiver, vou entrar e falar com ela, assim não desperdiço mais do seu tempo tão... valioso, e você pode voltar ao trabalho.";
			link.l1.go = "PZ_ElitaShluha_11";
		break;
		
		case "PZ_ElitaShluha_11":
			dialog.text = "Não há muito para onde voltar - embora o objetivo da nossa anfitriã seja fazer deste lugar o melhor do Arquipélago. Um lugar elitista, onde nenhum comerciante, nobre ou mesmo uma pessoa instruída teria vergonha de vir - porque oferecemos muito mais do que apenas nossos corpos.";
			link.l1 = "Mas ela não tem muito sucesso nisso, tem?";
			link.l1.go = "PZ_ElitaShluha_12";
		break;
		
		case "PZ_ElitaShluha_12":
			dialog.text = "Como posso dizer... Ela não nos vê apenas como mercadoria, como em outros estabelecimentos mais simples, mas como um projeto. Roupas caras, remédios, educação – ela investe em cada um de nós. E se estivéssemos numa grande cidade do Velho Mundo, ela teria conseguido! Mas aqui... Mesmo um comerciante talentoso não ganha nada se as mercadorias são tão caras que quase ninguém pode comprar. Mesmo baixando os preços, ainda estamos destinados a quebrar algum dia.";
			link.l1 = "Sinto muito ouvir isso. Então, onde está sua senhora agora?";
			link.l1.go = "PZ_ElitaShluha_13";
		break;
		
		case "PZ_ElitaShluha_13":
			dialog.text = "Estamos levando uma boa vida aqui até agora, posso te garantir. Mas tem o preço de conquistar isso e manter o padrão dela... Quanto à senhora, ela foi para Espanhola, discutir a possibilidade de levar todos nós para Porto Príncipe – afinal, mais rotas de comércio se cruzam lá, e nosso negócio não vai ficar parado nem sofrer perdas quase constantes por lá.";
			link.l1 = "É mesmo? Levasseur não investiu neste lugar para garantir a estabilidade dele?";
			link.l1.go = "PZ_ElitaShluha_14";
		break;
		
		case "PZ_ElitaShluha_14":
			dialog.text = "Não muito. Ele veio até nós e disse que só investiria de verdade se fôssemos à casa dele de vez em quando. Mas a senhora recusou na hora, sem rodeios. Tanto que Sua Graça ficou até sem reação por um instante. Nunca vi ela ou ele daquele jeito.";
			link.l1 = "Heh-heh, olha só. Parece que ela sabe... Corajosa, muito corajosa da parte dela.";
			link.l1.go = "PZ_ElitaShluha_15";
		break;
		
		case "PZ_ElitaShluha_15":
			dialog.text = "Sabe de uma coisa? Já que estamos conversando tão bem, vou te contar outra coisa, mas é um grande segredo, então não fale disso com ninguém!";
			link.l1 = "Ah não, mademoiselle. Garanto que não pretendo fazer mal algum à sua senhora. Por favor, continue.";
			link.l1.go = "PZ_ElitaShluha_16";
		break;
		
		case "PZ_ElitaShluha_16":
			dialog.text = "Eu nem sei se você conseguiria machucá-la, porque Belle Etoile pratica esgrima todos os dias, e não tem adversário à altura em toda a cidade. Além de Port-au-Prince, ela está planejando convencer o próprio Marcus Tyrex a investir! Ou melhor, a conseguir um empréstimo com ele. Consegue imaginar?";
			link.l1 = "Sim, e sinto que hoje vou ter uma conversa bem difícil com outra mulher que também pratica esgrima regularmente... Bem, obrigada por compartilhar, mademoiselle. Tenha um bom dia e clientes generosos.";
			link.l1.go = "PZ_ElitaShluha_17";
		break;
		
		case "PZ_ElitaShluha_17":
			dialog.text = "Obrigada. Mas por que tanta pressa? Você já pagou tudo, e nem conversamos tanto assim. Além disso, há algo refinado em você, monsieur. Algo muito além dos raros homens ricos que vêm à nossa casa. Que tal aproveitarmos de verdade a companhia um do outro?";
			link.l1 = "Sabe... que se dane? Por que estou fingindo e mentindo pra mim mesmo como se eu não quisesse isso? Uma chance com uma mulher como você é muito rara.";
			link.l1.go = "PZ_ElitaShluha_YesSex";
			link.l2 = "Ah, lamento dizer que não, mademoiselle. Só vim aqui para conversar. Além disso... tenho alguém me esperando.";
			link.l2.go = "PZ_ElitaShluha_NoSex";
		break;
		
		case "PZ_ElitaShluha_NoSex":
			dialog.text = "Como se isso já tivesse impedido alguém. Nesse caso, você merece respeito, monsieur. Fico muito feliz pelo seu 'alguém'.";
			link.l1 = "Muito obrigado mais uma vez, mademoiselle. Adeus.";
			link.l1.go = "PZ_ElitaShluha_NoSex_2";
		break;
		
		case "PZ_ElitaShluha_NoSex_2":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_ElitaShluha_YesSex":
			dialog.text = "Obrigada. Que tal começarmos com um banho quente juntos?";
			link.l1 = "Ambas as mãos a favor.";
			link.l1.go = "PZ_ElitaShluha_YesSex_2";
		break;
		
		case "PZ_ElitaShluha_YesSex_2":
			DialogExit();
			LAi_SetStayType(pchar);
			DoQuestCheckDelay("PlaySex_1", 1.0);
			DoQuestCheckDelay("PZ_ElitaShluha_Fuck", 1.0);
		break;
		
		case "PZ_ElitaShluha_After":
			dialog.text = "Foi uma experiência mágica, monsieur. Eu não achava que um homem pudesse me surpreender assim. Você realmente sabe como dar prazer a uma mulher...";
			link.l1 = "Depende da mulher.";
			link.l1.go = "PZ_ElitaShluha_After_2";
		break;
		
		case "PZ_ElitaShluha_After_2":
			dialog.text = "Você se arrepende?";
			link.l1 = "Agora não, com certeza. Adeus, mademoiselle.";
			link.l1.go = "PZ_ElitaShluha_After_3";
		break;
		
		case "PZ_ElitaShluha_After_3":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			LAi_SetPlayerType(pchar);
			pchar.questTemp.PZ.EliteWhoreFucked = true; // флаг того, что секс был (понадобится для диалога с Тираксом)
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_KlemanLebren_1":
			dialog.text = "Olha por onde anda, impostor!";
			link.l1 = "Cuidado com o que fala!";
			link.l1.go = "PZ_KlemanLebren_2";
		break;
		
		case "PZ_KlemanLebren_2":
			dialog.text = "Eu estava prestando atenção no caminho enquanto você contava corvos.";
			link.l1 = "Você poderia ter dado a volta se estivesse prestando atenção, não poderia?";
			link.l1.go = "PZ_KlemanLebren_3";
		break;
		
		case "PZ_KlemanLebren_3":
			dialog.text = "Por que eu deveria dar a volta em você?!";
			link.l1 = "Eu sugiro que a gente descubra fora da cidade quem deve o quê e pra quem.";
			link.l1.go = "PZ_KlemanLebren_4";
		break;
		
		case "PZ_KlemanLebren_4":
			dialog.text = "Mm-mm, não. Eu não sabia que Vossa Senhoria ficava tão enojado com o toque acidental de um simples homem.";
			link.l1 = "Pode repetir?";
			link.l1.go = "PZ_KlemanLebren_5";
		break;
		
		case "PZ_KlemanLebren_5":
			dialog.text = "Hum, desculpe. Não era minha intenção te pressionar.";
			link.l1 = "Assim está melhor.";
			link.l1.go = "PZ_KlemanLebren_6";
		break;
		
		case "PZ_KlemanLebren_6":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "", "", "", "", -1);
			npchar.location = "None";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				DelLandQuestMark(sld);
				if (CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
				{
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
				}
				else
				{
					ChangeCharacterAddressGroup(sld, "Tortuga_town", "rld", "loc0");
					sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
					sld.dialog.currentnode = "PZ_MaryRazgovorOBordeli_Bad_1";
					LAi_SetStayType(sld);
					CharacterTurnToLoc(sld, "quest", "quest1");
					sld.talker = 5;
					chrDisableReloadToLocation = true;
					LAi_LocationFightDisable(loadedLocation, true);
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				DelLandQuestMark(sld);
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_1":
			dialog.text = "Se você tivesse chegado meia hora mais tarde, Charles, eu já teria mandado nossas balas de canhão destruir esse antro imundo, né! Achou o que procurava? É ela, a irmã do Longway? Você viu ela?";
			link.l1 = "Shh, Mary, não fale assim. Não, eu não cheguei a conhecer Chang Xing...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_2";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_2":
			dialog.text = "Então por que diabos você demorou tanto?! O que estava fazendo lá?";
			link.l1 = "Não há motivo para preocupação. Assim que descobri tudo o que pude, fui embora daquele lugar, como prometi a você.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_3":
			dialog.text = "Fala logo, né!";
			link.l1 = "O dono não está em Tortuga no momento. A procura pelos serviços dela é baixa aqui, já que ela emprega moças bem-educadas, vestidas com roupas caras, e só aceitam ouro como pagamento...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_4":
			dialog.text = "Você também pagou eles?!";
			link.l1 = "Eles nem teriam falado comigo de outra forma. Com esse tipo de atitude, não é de se admirar que não tenham muitos clientes. A madame decidiu levar o negócio para Port-au-Prince, na esperança de atrair uma clientela mais rica. Mas está claro que ela está sem dinheiro, já que resolveu pedir um empréstimo ao Marcus Tyrex...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_5":
			dialog.text = "Ele conhece ela?";
			link.l1 = "Vamos descobrir quando chegarmos a La Vega. E se nos apressarmos e pararmos de perder tempo com conversa fiada, vamos pegar essa mulher asiática, seja lá quem for.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_6":
			dialog.text = "Não era necessário ir até aquele bordel, Charles. Tenho certeza de que poderíamos ter descoberto tudo isso na taverna ou nas ruas se tivéssemos nos esforçado um pouco mais, né.";
			link.l1 = "Da próxima vez eu te levo comigo pra você não encher essa sua cabecinha ruiva de besteira, né? Agora, vamos ao que interessa.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_1":
			dialog.text = "Ah, entendi que cheguei um pouco atrasada, né! Mas espera aí, seu canalha...";
			link.l1 = "Mary, o que diabos você está fazendo aqui?! Eu te disse pra ficar no barco!";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_2":
			dialog.text = "Então eu não ia te impedir de se divertir com prostitutas?! Nem pense em negar, Charles! A tripulação te viu lá, né! Como você pôde?!";
			link.l1 = "Era o que eu imaginava. Acho que devia ter levado eles comigo, assim veriam o que eu estava fazendo – ou melhor, o que eu não estava fazendo – e não fariam tanto alarde por causa disso...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_3":
			dialog.text = "Você está acusando nossos rapazes de mentir? Depois do que você mesmo fez, seu bruto?";
			link.l1 = "Eu só os acuso de uma estupidez sem igual. Sem entender a situação, você...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_4":
			dialog.text = "Oh-oh, Charles, acho que você e suas putas não iam gostar nada do que eu teria feito se tivesse chegado naquele buraco a tempo. Mas você deu sorte – tive que remar essa porra de barco sozinho...";
			link.l1 = "Dizem que o trabalho físico pesado limpa a cabeça de pensamentos desnecessários. Mas você ainda tem muitos deles, então vai remar de volta também.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_5":
			dialog.text = "Eu não vou me mexer, né!";
			link.l1 = "Mary, não vou ter essa conversa aqui na frente dos homens do Levasseur. Se acalme, olhe ao redor e pense bem. Não é hora nem lugar para isso.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_6":
			dialog.text = "Vá para o inferno. Ainda tenho minhas coisas na cabine... Mas não pense que vou remar de novo, né! Deve ter sobrado alguma coisa de nobre em você!";
			link.l1 = "Sou um canalha e um bruto, lembra? Vou provar isso no navio, mas preciso chegar lá primeiro. Então, seus pedidos são inúteis.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "rld", "loc1", "OpenTheDoors", -1);
			
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_8":
			dialog.text = "Você fez a tripulação inteira rir de você, né!";
			link.l1 = "Bem, talvez também por sua causa. Eles não viam um espetáculo assim fazia tempo. Agora que seu ânimo acalmou um pouco, deixe-me contar o que aconteceu.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_9";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_9":
			dialog.text = "Charles, já ouvi tudo o que tinha pra ouvir. Só tenho uma pergunta: eu não fui boa o bastante pra você? Faltou alguma coisa em mim?";
			link.l1 = "É falta de educação, mas vou responder com uma pergunta: já te dei algum bom motivo pra não confiar em mim? Hein? Não me lembro de nada assim. Então respira fundo e me escuta. Não consegui descobrir muita coisa sobre o Joep van der Vink, só que ele tinha ido a um bordel. Não aquele perto do 'Corvo Cantante', mas outro, perto do cais. Eu não conhecia esse lugar antes... diferente, ao que parece, dos nossos marinheiros, que te contaram tudo. Embora eles nem pudessem ter ido lá...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_10";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_10":
			dialog.text = "Que tipo de bordel não deixa marinheiro entrar, né?";
			link.l1 = "Um bordel onde trabalham damas vestidas de seda, que têm mais do que vento na cabeça. E seus serviços são pagos exclusivamente em dobrões de ouro. Não é um capricho qualquer, mas uma ordem de sua misteriosa dona, Belle Etoile.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_11";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_11":
			dialog.text = "Misterioso, né?";
			link.l1 = "Não é só isso. Ela é asiática.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_12";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_12":
			dialog.text = "Asiática? A dona do bordel em Tortuga?";
			link.l1 = "Pode ser a Chang Xing. Foi por isso que fui lá – queria vê-la com meus próprios olhos. Só isso.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_13";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_13":
			dialog.text = "Como ela é?";
			link.l1 = "Eu não faço ideia. Ela não estava lá, então tive que conversar com outra... estrela.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_14";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_14":
			dialog.text = "Ela também era asiática, né?";
			link.l1 = "Não, ela era branca. Ela me disse que a Belle Etoile não anda indo muito bem ultimamente, então decidiu se mudar para Port-au-Prince. Faz sentido, já que lá o povo é mais rico. A madame deve estar apertada de dinheiro, pois precisa de um empréstimo para abrir um negócio em Espanhola, que ela pretende conseguir com o Tyrex. Então, se corrermos para La Vega, podemos interceptá-la antes que o Marcus a encontre.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_15";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_15":
			dialog.text = "Eu não dou a mínima pra ela, pro Marcus ou pra qualquer um, tá bom. Charles, só me diz uma coisa – você já ficou com alguma das garotas no bordel dela?";
			link.l1 = "Eu não preciso disso, Mary. Eu tenho você, a melhor garota do mundo. Não entendo por que você não percebe isso.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_16";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_16":
			dialog.text = "Na verdade, é bem fácil descobrir a verdade, né, hee hee. Se você não ficou com ninguém, deve estar cheio de energia agora. É isso que vamos conferir agora, né!";
			link.l1 = "Mary, por favor...";
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			pchar.questTemp.PZ_MaryRazgovorOBordeli = true;
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_17":
			DeleteAttribute(pchar, "questTemp.PZ_MaryRazgovorOBordeli");
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				if (IsCharacterPerkOn(pchar, "Medic"))
				{
					Notification_Perk(true, "Medic");
					dialog.text = "(Excelente saúde) Ugh... Parece que você não estava mentindo, Charles, né...";
					link.l1 = "Não preciso enganar você, meu caro...";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
				}
				else
				{
					Notification_Perk(false, "Medic");
					dialog.text = "Charles, você... você está falando sério?! O que foi aquilo?";
					link.l1 = "Ah, esse calor não está me fazendo bem. Ahem.";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_19";
				}
			}
			else
			{
				dialog.text = "Ugh... Parece que você não estava mentindo, Charles, né...";
				link.l1 = "Não tenho motivo para enganar você, meu caro...";
				link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_18":
			dialog.text = "Mas aquele passeio de bote eu não vou esquecer tão cedo!";
			link.l1 = "Ha!";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_19":
			dialog.text = "Você nunca reclamou disso antes, não é?";
			link.l1 = "Tenta correr por essa ilha maldita...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_20";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_20":
			dialog.text = "E os bordéis, né! Você realmente...";
			link.l1 = "Mary, me desculpe.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_21";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_21":
			dialog.text = "O quê?! Então você é...";
			link.l1 = "Eu não me arrependo disso. Droga. Quero dizer, eu não estava com ninguém além de você, eu te disse. Eu só... não conseguia acalmar minha cabeça, só isso. É difícil fazer isso, sabe, com os canhões de La Roche apontados pra você.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_22";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_22":
			dialog.text = "Essa é uma bela desculpa, Charles. Tudo bem, vou acreditar em você. Desta vez... Mas saiba que ainda estou puta com você, tá bom!";
			link.l1 = "Eu vou conquistar seu perdão, eu prometo.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_1":
			dialog.text = "Então, galã, me conta o que descobriu. Valeu a pena arriscar o meu favor?";
			link.l1 = "Eu realmente não sei se você está brincando ou falando sério. Valeu a pena – mesmo que eu não tenha visto a anfitriã com meus próprios olhos. Ela é asiática e se chama Belle Etoile – uma estrela maravilhosa. Não é o nome verdadeiro dela, claro...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_2":
			dialog.text = "E para isso, você teve que ir a um bordel? Não dava pra descobrir isso na estalagem?";
			link.l1 = "Não falam muito sobre este lugar na cidade. Por quê? Boa pergunta. Pode perguntar para a própria Belle Etoile – ela foi para Espanhola.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_3":
			dialog.text = "Tortuga não foi suficiente para ela?";
			link.l1 = "O comércio, ao que parece, não vai bem aqui. Ela não emprega moças comuns do porto, mas sim senhoras bem vestidas e instruídas.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_4":
			dialog.text = "E por que fariam isso?";
			link.l1 = "Essa é outra boa pergunta. De qualquer forma, nosso passarinho resolveu voar para Port-au-Prince, o feudo de de Mussac. Mas o empréstimo para essa empreitada seria conseguido com ninguém menos que Tyrex.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_5":
			dialog.text = "Quero que essa história acabe logo. Vamos parar de perder tempo e traçar um rumo para La Vega.";
			link.l1 = "É isso que vamos fazer.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_1":
			dialog.text = "Você é um homem corajoso, Charles, isso eu reconheço. Aparecer assim, tão tranquilo, com essa cara limpa, como se nada tivesse acontecido.";
			link.l1 = "Imagino que algum dos tripulantes abriu o bico? Sem dar nenhum contexto, claro. Porque na verdade não aconteceu nada — pelo menos, não o que você está pensando.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_2":
			dialog.text = "Fico feliz que você não tenha negado, Charles.";
			link.l1 = "Eu ia te contar tudo, Helen.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_3":
			dialog.text = "Não faça isso, Charles. Os detalhes não me interessam muito. Mas os motivos, sim. Me diga, tem algo de errado comigo?";
			link.l1 = "Vamos começar pelos motivos. Descobri que há dois bordéis em Tortuga. Um é bem conhecido. O outro – as pessoas sabem que existe, mas poucos querem falar sobre ele. É de uma mulher asiática...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_4":
			dialog.text = "Você está inventando isso agora?";
			link.l1 = "Por que diabos eu faria isso, Helen?! Se você não acredita em mim, eles vão confirmar lá no lugar!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_5":
			dialog.text = "Primeiro, você me disse para não ir à terra, então não tem como eu chegar lá. Segundo, quem diabos você pensa que eu sou?! Eu não vou chegar nem perto de um lugar desses! Terceiro... só continua.";
			link.l1 = "Ótimo. Eu decidi ir lá para ver Madame Étoile com meus próprios olhos. Essa era minha única intenção, droga!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_6":
			dialog.text = "Suponho que sim. Você chegou a conhecê-la?";
			link.l1 = "Não. Ela foi para Espanhola. As coisas não estavam indo bem para ela aqui, então decidiu tentar a sorte em Port-au-Prince. Lá, as moças bem vestidas e instruídas que trabalham para ela podem lhe render mais lucro do que em Tortuga...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_7":
			dialog.text = "Arrumada e instruída? Nossa, a vida pode surpreender mesmo. Mas você devia gostar delas do jeito que são.";
			link.l1 = "Helen, pare com isso. Eu não fiz nada para merecer sua desconfiança.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_8";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_8":
			dialog.text = "Verdade. Se tivesse tentado me enganar, não estaria tão calmo. Mas deveria ter me avisado dos seus planos, Charles.";
			link.l1 = "Você tem razão, querido. Mas eu decidi economizar um pouco de tempo. Foi meu erro.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_9";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_9":
			dialog.text = "Certo. E agora, traçamos um rumo para Port-au-Prince?";
			link.l1 = "La Vega. Não se assuste, Helen. Madame Belle Etoile não está bem. Ela precisou de um empréstimo para levar o negócio dela para Port-au-Prince, então decidiu pegar o dinheiro com o Marcus. Se formos rápido, ainda pegamos ela lá. Então não vamos perder tempo.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_NaLaVega":
			DialogExit();
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) 
			{
				AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
				QuestSetCurrentNode("Terrax", "PZ_1");
			}
			else 
			{
				AddLandQuestMark(characterFromId("Vensan"), "questmarkmain");
				QuestSetCurrentNode("Vensan", "PZ_1");
			}
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			Island_SetReloadEnableGlobal("Tortuga", true);
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				AddPassenger(pchar, sld, false);
				ReturnOfficer_Mary();
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				AddPassenger(pchar, sld, false);
				ReturnOfficer_Helena();
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku")) AddQuestRecord("PZ", "31");
		break;
		
		case "PZ_KlemanLebren_7":
			dialog.text = "Não acredito que um desgraçado como você e sua corja conseguiu nos derrotar!";
			link.l1 = "Você...";
			link.l1.go = "PZ_KlemanLebren_8";
		break;
		
		case "PZ_KlemanLebren_8":
			dialog.text = "Oh, você me reconhece?";
			link.l1 = "Já nos conhecemos?";
			link.l1.go = "PZ_KlemanLebren_9";
		break;
		
		case "PZ_KlemanLebren_9":
			dialog.text = "O quê?! Você tá de sacanagem comigo?!";
			link.l1 = "Não lembro de toda escória selvagem que encontro. É melhor você dizer quem mandou você nos matar. Ou talvez só quisessem se livrar de você?";
			link.l1.go = "PZ_KlemanLebren_10";
		break;
		
		case "PZ_KlemanLebren_10":
			dialog.text = "Não vou dizer nada para alguém como você. Se acha tão importante, não é? Vamos ver se vai continuar assim depois do nosso pequeno descanso aqui.";
			link.l1 = "Que pena. Você é nojento, mas eu poderia simplesmente ter te deixado em outra ilha. Agora tudo que posso fazer é te mandar para o outro lado.";
			link.l1.go = "PZ_KlemanLebren_11";
		break;
		
		case "PZ_KlemanLebren_11":
			pchar.questTemp.PZ.HeavyFrigateAbordage = true; // флаг - абордаж был
			
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_Tichingitu_11":
			dialog.text = "Chamou por mim, Capitão?";
			link.l1 = "Sim, camarada. Informe os danos.";
			link.l1.go = "PZ_Tichingitu_12";
		break;
		
		case "PZ_Tichingitu_12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "There's a violent storm. The ship is creaking and cracking; it's wobbling badly.";
			link.l1 = "Sim, eu percebi. Tichingitu, meu amigo. Eu e o "+sStr+" vou desembarcar. Você fica no comando. Comece os reparos imediatamente – até a tempestade passar, não adianta ir ao estaleiro. Além disso, não vamos ficar aqui por muito tempo.";
			link.l1.go = "PZ_Tichingitu_13";
		break;
		
		case "PZ_Tichingitu_13":
			dialog.text = "Vou deixar tudo com uma cara melhor.";
			link.l1 = "Ótimo, obrigado. Então vamos para a cidade sem nenhuma preocupação.";
			link.l1.go = "PZ_Tichingitu_14";
		break;
		
		case "PZ_Tichingitu_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_Matros_1":
			dialog.text = "Monsieur le Capitaine? É uma honra. Mas normalmente nessas horas o senhor chama o Alonso. Está tudo bem, se me permite perguntar?";
			link.l1 = "Sim, está tudo certo. Mas o nosso Alonso é mais de destruir do que consertar qualquer coisa. Em todos os sentidos da palavra. O navio está muito danificado?";
			link.l1.go = "PZ_Matros_2";
		break;
		
		case "PZ_Matros_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "O Alonso diria que está uma porcaria, mesmo que não estejamos afundando. Você falou em consertos – começamos agora?";
			link.l1 = "Sim, faça o que puder. Mas não conte com trabalho grande ou de longo prazo – logo vamos içar âncora, assim que eu terminar meus assuntos na cidade. Eu e "+sStr+" não estarei lá, então, caso aconteça qualquer coisa, tome todas as decisões sozinho. Ouça o Alonso em tudo.";
			link.l1.go = "PZ_Matros_3";
		break;
		
		case "PZ_Matros_3":
			dialog.text = "A suas ordens, Monsieur le Capitaine.";
			link.l1 = "À vontade.";
			link.l1.go = "PZ_Matros_4";
		break;
		
		case "PZ_Matros_4":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			bQuestDisableMapEnter = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_AnriTibo_1":
			dialog.text = "Saudações, monsieur! Bem-vindo a Port-au-Prince.";
			link.l1 = "E um bom dia para você também, monsieur. Quem é você, e a que devo esta recepção? Não diria que estou com disposição para uma longa conversa nessa chuva e depois de uma tempestade.";
			link.l1.go = "PZ_AnriTibo_2";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_ChangShin", "Mei_Shin", "woman", "towngirl2", 30, FRANCE, 0, false, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_41", "", "", 0);
			sld.name = "Чанг";
			sld.lastname = "Шин";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto16");
			EquipCharacterByItem(sld, "blade_41");
			GiveItem2Character(sld, "cirass8");
			EquipCharacterByItem(sld, "cirass8");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload8_back", "none", "", "", "", -1);
		break;
		
		case "PZ_AnriTibo_2":
			dialog.text = "Oh, não vou tomar muito do seu tempo, Monsieur de Maure.";
			link.l1 = "Eu te conheço?";
			link.l1.go = "PZ_AnriTibo_3";
		break;
		
		case "PZ_AnriTibo_3":
			dialog.text = "Oh, não, mas todo o arquipélago sabe quem você é. Ah, onde estão meus modos! Henri Thibaut, ao seu dispor. Sou o mensageiro de Sua Senhoria, Monsieur de Mussac. Assim que ele avistou seu navio, ordenou que eu lhe desse as boas-vindas mais calorosas possíveis, monsieur.";
			link.l1 = "Bem, isso explica muita coisa. Prazer em conhecê-lo, Monsieur Thibaut.";
			link.l1.go = "PZ_AnriTibo_4";
		break;
		
		case "PZ_AnriTibo_4":
			dialog.text = "E o prazer é todo meu, Monsieur de Maure! Por favor, me acompanhe. Não é certo que um homem da sua posição e sua bela acompanhante fiquem presos nesta taverna fedorenta. Sua Senhoria lhe designou uma casa na cidade e me instruiu a ajudá-lo em tudo que precisar. Por favor, não se esqueça de transmitir seus melhores cumprimentos a Sua Excelência Poincy depois.";
			link.l1 = "Na verdade, meu assunto é discreto. Sabe, Monsieur Thibaut, eu acho que...";
			link.l1.go = "PZ_AnriTibo_5";
		break;
		
		case "PZ_AnriTibo_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_HelenaPortPax1", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_MaryPortPax1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_HelenaPortPax1":
			dialog.text = "Charles. Eu quase nunca te peço nada, muito menos te interrompo, mas podemos aceitar a oferta deles? Estou cansado de me molhar na chuva. Também estou enjoado e tonto.";
			link.l1 = "Heh-heh, tem certeza que é só a chuva?";
			link.l1.go = "PZ_HelenaPortPax2";
		break;
		
		case "PZ_HelenaPortPax2":
			dialog.text = "Morda a língua, Charles! De qualquer forma, quero descansar. Numa cama grande e sem ondas.";
			link.l1 = "Tudo bem. Vamos nos secar, descansar um pouco e depois voltar direto ao trabalho.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_MaryPortPax1":
			dialog.text = "Podemos descansar um pouco nesta casa? Não estou me sentindo bem, e também estou... cansado, Charles. Né?";
			link.l1 = "Mary, querida, eu entendo, mas talvez devêssemos ir até a taverna. Isso tudo está com um cheiro ruim, não acha?";
			link.l1.go = "PZ_MaryPortPax2";
		break;
		
		case "PZ_MaryPortPax2":
			dialog.text = "O que poderia me acontecer? Aqui nem é Tortuga.";
			link.l1 = "É isso que me assusta.";
			link.l1.go = "PZ_MaryPortPax3";
		break;
		
		case "PZ_MaryPortPax3":
			dialog.text = "Por favor? Se for preciso, eu monto uma defesa no quarto—igual... daquela vez, né. Você me conhece melhor que ninguém, Charles, então sabe que eu dou conta.";
			link.l1 = "Tudo bem, tudo bem. Tomara que isso não seja como daquela vez.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_AnriTibo_6":
			StartInstantDialog("Tibo", "PZ_AnriTibo_7", "Quest\CompanionQuests\Longway.c");
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
		break;
		
		case "PZ_AnriTibo_7":
			dialog.text = "Eu sabia que mudaria de ideia, monsieur! Quanto às suas preocupações, entendo perfeitamente. Mas veja, Sua Excelência Poincy e o governador são velhos amigos, então você é um hóspede bem-vindo em nossa cidade, Monsieur de Maure!";
			link.l1 = "Ah, bem... Então, leve a gente até a casa, então.";
			link.l1.go = "PZ_AnriTibo_8";
		break;
		
		case "PZ_AnriTibo_8":
			dialog.text = "Certamente, monsieur! Por favor, siga-me.";
			link.l1 = "Obrigado.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_GoToTiboHouse");
		break;
		
		case "PZ_AnriTibo_9":
			dialog.text = "Monsieur, o governador está esperando por você. Ele pediu que você vá até ele assim que puder - gostaria de falar com você em particular.";
			link.l1 = "Ele já sabe disso?";
			link.l1.go = "PZ_AnriTibo_10";
		break;
		
		case "PZ_AnriTibo_10":
			pchar.questTemp.PZ.PortPaxMayorTalk = true; // флаг для разговора с губернатором
			
			dialog.text = "Claro que ele sabe! Por isso mesmo está te esperando. Deixe sua amada dormir tranquila enquanto você vai falar com monsieur de Mussac. Uma tempestadezinha não vai parar o famoso Charles de Maure, vai? Mas Sua Senhoria, como você percebe, não tem muito tempo livre entre os compromissos...";
			link.l1 = "Bem, isso é verdade, Monsieur Thibaut.";
			link.l1.go = "PZ_AnriTibo_11";
			
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_Escort_"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, -1, true, "soldier"));
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
		break;
		
		case "PZ_AnriTibo_11":
			StartInstantDialog("PZ_PoP_Escort_1", "PZ_AnriTibo_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_AnriTibo_12":
			dialog.text = "Vamos te mostrar o caminho, Capitão.";
			link.l1 = "Oh, então eu tenho até uma escolta de honra... Muito bem, mostre o caminho.";
			link.l1.go = "PZ_AnriTibo_13";
		break;
		
		case "PZ_AnriTibo_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "PZ_PoP_EscortToGuber");
		break;
		
		case "PZ_Longway_71":
			dialog.text = "Meu Senhor Capitão!";
			link.l1 = "Longway! Para o navio! Agora!";
			link.l1.go = "PZ_Longway_72";
		break;
		
		case "PZ_Longway_72":
			dialog.text = "Mas eu vi Chang Xing!";
			link.l1 = "O quê?! Onde? Quando? Ela está no seu navio?";
			link.l1.go = "PZ_Longway_73";
		break;
		
		case "PZ_Longway_73":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Não! Aqui na cidade, Longway a viu de longe. Não deu tempo de alcançar - ela está embarcando num galeão que acabou de zarpar!";
			link.l1 = "Vamos alcançar o galeão! Mas me diga – você viu "+sStr+" em algum lugar?";
			link.l1.go = "PZ_Longway_74";
		break;
		
		case "PZ_Longway_74":
			dialog.text = "Não! Aconteceu alguma coisa?";
			link.l1 = "Sim, aconteceu alguma coisa! Ela está em perigo! Você viu o sobrinho do Levasseur? O nome dele é Henri Thibaut! Um sujeito desagradável, magro, de cabelo comprido e um bigodinho engraçado!";
			link.l1.go = "PZ_Longway_75";
		break;
		
		case "PZ_Longway_75":
			dialog.text = "(em mandarim) Não precisa falar de bigodes engraçados, Capitão... (em francês ruim) Eu vi ele! Ele e os mercenários também embarcaram no mesmo galeão.";
			link.l1 = "Vamos perseguir imediatamente!";
			link.l1.go = "PZ_Longway_76";
		break;
		
		case "PZ_Longway_76":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Seu navio está muito desgastado, Meu Senhor Capitão!";
			link.l1 = "Eu não me importo! "+sStr+"A vida de [[[VARx]]] está em jogo!";
			link.l1.go = "PZ_Longway_77";
		break;
		
		case "PZ_Longway_77":
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang"))
			{
				dialog.text = "Minha... 'Sua Meifeng' vai nos tirar dessa!";
				link.l1 = "Oh, ela vai! Depressa!";
				link.l1.go = "PZ_Longway_78";
			}
			else
			{
				dialog.text = "Não nos jogue num ataque suicida. Use o navio que você me forneceu antes!";
				link.l1 = "Boa ideia, Longway! Vamos depressa!";
				link.l1.go = "PZ_Longway_78";
			}
		break;
		
		case "PZ_Longway_78":
			DialogExit();
			AddDialogExitQuestFunction("PZ_Longway_78");
		break;
		
		case "PZ_RobertMartin_8":
			dialog.text = "Você de novo... Eu sabia que devia ter recusado e deixado outra pessoa ficar com sua garota.";
			link.l1 = "Onde ela está?! Fala! Não... Cala a boca. Você só vai falar no porão, acorrentado! Tá ouvindo?!";
			link.l1.go = "PZ_RobertMartin_9";
		break;
		
		case "PZ_RobertMartin_9":
			dialog.text = "...";
			link.l1 = "A lâmina dela. Se não começar a cantar agora mesmo, eu te corto em pedaços com ela.";
			link.l1.go = "PZ_RobertMartin_10";
			/*RemoveAllCharacterItems(npchar, true);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) GiveItem2Character(pchar, "blade_31");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) GiveItem2Character(pchar, "pirate_cutlass");*/
		break;
		
		case "PZ_RobertMartin_10":
			dialog.text = "Você... você perdeu completamente o juízo!..";
			link.l1 = "Agora você vai conhecer meu lado desagradável...";
			link.l1.go = "PZ_RobertMartin_11";
		break;
		
		case "PZ_RobertMartin_11":
			DialogExit();
			LAi_ReloadBoarding();
		break;
		
		case "PZ_RobertMartin_13":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "É só isso?";
			link.l1 = "Eu pergunto de novo! Onde está "+sStr+"?! Onde está a chinesa?! Onde está Henri Thibaut?!";
			link.l1.go = "PZ_RobertMartin_14";
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_14":
			dialog.text = "(cospe sangue) Você bate como uma mocinha.";
			link.l1 = "Sua desgraçada! Vou arrancar cada palavra de você na porrada!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_6");
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_16":
			dialog.text = "Patético. Embora... vou dizer. Por que não, ha ha. Estão todos no outro navio, indo direto para Tortuga. Você chegou tarde demais.";
			link.l1 = "Se ao menos um fio de cabelo cair da cabeça dela...";
			link.l1.go = "PZ_RobertMartin_17";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_2", "", 0.3);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 1.00, 5.13, 7.23);
		break;
		
		case "PZ_RobertMartin_17":
			dialog.text = "E de quem é a culpa disso?! Você matou Edgardo Sotta! Pela primeira vez na vida, Levasseur quis provar uma garota e não conseguiu na hora! Primeira vez que nossa tripulação falhou com uma ordem direta dele! Esse homem pode ser tão assustador quanto o próprio diabo...";
			link.l1 = "Então eu vou ser mais assustador que o próprio diabo e te fazer viver um inferno pessoal se não me contar o que quero saber, está me ouvindo?!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) link.l1.go = "PZ_RobertMartin_Mary_1";
			else link.l1.go = "PZ_RobertMartin_Helena_1";
			//if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) link.l1.go = "PZ_RobertMartin_Helena_1";
		break;
		
		case "PZ_RobertMartin_Mary_1":
			dialog.text = "Eu não dou a mínima pros seus lamentos – de qualquer jeito, já estou morto mesmo, pelo jeito desses seus olhos malucos. Mas vou te dar algum crédito, de Maure.";
			link.l1 = "Do que diabos você está falando?";
			link.l1.go = "PZ_RobertMartin_Mary_2";
		break;
		
		case "PZ_RobertMartin_Mary_2":
			dialog.text = "Levasseur prefere as loiras. Mas eu sempre gostei mais das ruivas, igualzinha a você, hehehe... Que pimenta você tem!";
			link.l1 = "Você tem razão, você não vai sobreviver até o fim do dia...";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_Helena_1":
			dialog.text = "Eu não dou a mínima pro que você quer. Mas deixa eu te contar o que o Levasseur quer – garotas loiras e bonitas, ha ha ha ha ha ha ha ha ha! Primeiro, ele pega ela...";
			link.l1 = "A-AH!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_19":
			dialog.text = "Espancar e humilhar um homem desarmado — patético. É só isso que você sabe fazer. Você perdeu, de Maure! Quer saber quando foi que você realmente perdeu, seu cretino patético?";
			link.l1 = "Me esclareça. Mas se eu não ficar impressionado, você vai perder um dedo. Ou uma orelha. Ou esses dentes podres dessa boca fedorenta. Ou talvez outra coisa. A escolha é sua...";
			link.l1.go = "PZ_RobertMartin_20";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_3", "", 0.3);
			//locCameraFromToPos(-1.75, 14.14, -0.31, true, 1.26, 11.00, -4.00);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 0.66, 5.00, 8.26);
		break;
		
		case "PZ_RobertMartin_20":
			dialog.text = "Heh-heh, eu tenho algo que você não tem. Acha mesmo que o Levasseur não sabia o que aquele velho raposa do Poincy tramava contra ele? François sabe de tudo, tudo! Até os barões da Irmandade não ousam enfrentá-lo. E você, espertinho, ousou. Mas...";
			link.l1 = "Mas o quê?! Nem pense em enrolar comigo, porra!! Começa a falar, ou eu quebro seus dedos um por um!";
			link.l1.go = "PZ_RobertMartin_21";
		break;
		
		case "PZ_RobertMartin_21":
			dialog.text = "Ha-ha, bravo Capitão de Maure! Mas tudo bem. Eu, Henri e a mulher de pele amarela achamos melhor acabar com você aqui mesmo. E colocar a culpa no Tyrex, assim os velhos tolos da Irmandade começariam outra guerra entre si! Ou talvez no de Mussac – ele anda enfiando o nariz onde não deve... Sabe, todos riram de mim por navegar num galeão, mas ele enfrentou a tempestade sem esforço, ao contrário do seu pedaço de lixo.";
			link.l1 = "Chega! Onde o Levasseur mantém as vítimas dele?";
			link.l1.go = "PZ_RobertMartin_22";
		break;
		
		case "PZ_RobertMartin_22":
			dialog.text = "Então você sabe sobre o lugar secreto dele, a masmorra? Ah, sim, ele é o verdadeiro mestre da masmorra, ha-ha-ha! Mas será que você consegue mesmo enfrentá-lo? Eu duvido. Quer derrotar o monstro? Então vire o monstro você também. Vamos ver se consegue me quebrar como o François quebra aquelas garotas. Como ele logo vai quebrar a sua...";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "Alo-o-on-s-o-o!!!";
				link.l1.go = "PZ_RobertMartin_23";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "PZ_LongwayKaznDialog_1";
			}
		break;
		
		case "PZ_RobertMartin_23":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_Fade("PZ_AlonsoKazn", "");
		break;
		
		case "PZ_LongwayKaznDialog_1":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			DoQuestCheckDelay("PZ_LongwayKazn_1", 1.0);
		break;
		
		case "PZ_LongwayKaznDialog_2":
			dialog.text = "";
			link.l1 = "Eu te disse para não se meter, droga!..";
			link.l1.go = "PZ_LongwayKaznDialog_3";
		break;
		
		case "PZ_LongwayKaznDialog_3":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_LongwayKazn_3", "");
		break;
		
		case "PZ_LongwayKaznDialog_4":
			dialog.text = "Permita-me, Senhor Capitão.";
			link.l1 = "Longway? Permitir o quê?";
			link.l1.go = "PZ_LongwayKaznDialog_5";
		break;
		
		case "PZ_LongwayKaznDialog_5":
			dialog.text = "Os homens brancos torturam o corpo. Meu povo sabe que é preciso torturar primeiro a alma miserável, enlouquecer com uma dor constante e sutil. Não se pode simplesmente pegar e torturar sem preparação. Sempre exige um jeito especial. Aqui você precisa de... Lynchy.";
			link.l1 = "Lynchy?";
			link.l1.go = "PZ_LongwayKaznDialog_6";
		break;
		
		case "PZ_LongwayKaznDialog_6":
			dialog.text = "Sim, Senhor Capitão. Morte por mil cortes.";
			link.l1 = "Você ficou louco?! Bateu com a cabeça? Que morte é essa que você tá falando?! Primeiro eu preciso fazer ele falar!";
			link.l1.go = "PZ_LongwayKaznDialog_7";
		break;
		
		case "PZ_LongwayKaznDialog_7":
			dialog.text = "Longway sabe, Senhor Capitão. Ele sabe o que fazer. Esse desgraçado vai me contar tudo. Me dê um tempo...";
			link.l1 = "Tempo? Tempo?! Tá bom... Faça isso. Só por favor, eu imploro, tire tudo dele, tudo!";
			link.l1.go = "PZ_LongwayKaznDialog_8";
		break;
		
		case "PZ_LongwayKaznDialog_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_LongwayKazn_3_1", -1);
		break;
		
		case "PZ_LongwayKaznDialog_9":
			dialog.text = "Me mate, só me mate, por favor... O que mais você quer de mim?!";
			link.l1 = "Nada mais. Cala a boca e morra.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayKazn_11");
		break;//
		
		case "PZ_LongwayKaznDialog_9_1":
			DialogExit();
			sld = CharacterFromID("PZ_RobertMartinPlennik")
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_11":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Tiro limpo, Meu Senhor Capitão. Eu disse que ia funcionar.";
			link.l1 = "É. Bom trabalho. Então, para o calabouço. Içar todas as velas! Rumo a Tortuga. E que Deus tenha piedade dessa cidade maldita se um único fio de cabelo cair da cabeça dela "+sStr+" cabeça...";
			link.l1.go = "PZ_LongwayKaznDialog_12";
		break;
		
		case "PZ_LongwayKaznDialog_12":
			DialogExit();
			AddQuestRecord("PZ", "39");
			pchar.questTemp.PZ_FlagMartinInfo = true;
			AddDialogExitQuestFunction("PZ_FinalKaznOnShip_DlgExit");
		break;
		
		case "PZ_AlonsoKaznDialog_1":
			dialog.text = "Dios mio... Nunca vi ou ouvi você... assim, senhor Capitão.";
			link.l1 = "Ele é todo seu, Alonso! Vá em frente, me mostre o que a Santa Inquisição faz com os huguenotes e seus lacaios... E eu vou assistir... Depois, pode fazer o que quiser com ele.";
			link.l1.go = "PZ_AlonsoKaznDialog_2";
		break;
		
		case "PZ_AlonsoKaznDialog_2":
			dialog.text = "Sim, sim, senhor Capitão...";
			link.l1 = "";
			link.l1.go = "PZ_AlonsoKaznDialog_3";
		break;
		
		case "PZ_AlonsoKaznDialog_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_AlonsoKazn_2", -1);
		break;
		
		case "PZ_AlonsoKaznDialog_4":
			dialog.text = "Não vai demorar, senhor Capitão...";
			link.l1 = "Faça isso, pelo amor de Deus!";
			link.l1.go = "PZ_AlonsoKaznDialog_5";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			//LAi_ActorAnimation(npchar, "Barman_idle", "1", 5);
		break;
		
		case "PZ_AlonsoKaznDialog_5":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_AlonsoKazn_3", 1.5);
		break;
		
		case "PZ_AlonsoKaznDialog_6":
			dialog.text = "Levanta, seu desgraçado. Levanta, eu disse!";
			link.l1 = "Ele está morto? Morto?!";
			link.l1.go = "PZ_AlonsoKaznDialog_7";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
		break;
		
		case "PZ_AlonsoKaznDialog_7":
			dialog.text = "Parece que sim, capitão...";
			link.l1 = "O que diabos você fez?!";
			link.l1.go = "PZ_AlonsoKaznDialog_8";
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
		break;
		
		case "PZ_AlonsoKaznDialog_8":
			dialog.text = "Quem diria que esse brutamontes seria tão covarde! Ainda mijou nas calças, o desgraçado imundo! Que droga, o fogo foi desnecessário...";
			link.l1 = "Você... Bem, jogue ele aos peixes. Rumo a Tortuga. Se for preciso, eu vou desmontar aquele lugar tijolo por tijolo – primeiro La Roche, depois... Depois que Deus me ajude se eu não encontrá-la viva...";
			link.l1.go = "PZ_AlonsoKaznDialog_9";
		break;
		
		case "PZ_AlonsoKaznDialog_9":
			DialogExit();
			AddQuestRecord("PZ", "38");
			AddDialogExitQuestFunction("PZ_FinalKaznOnShip_DlgExit");
		break;
		
		case "PZ_Norman1":
			dialog.text = "Finalmente. Este trono agora é meu. Sobre esta rocha eu vou construir...";
			link.l1 = "Mas que porra... Sério?";
			link.l1.go = "PZ_Norman2";
		break;
		
		case "PZ_Norman2":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Shark";
			
			dialog.text = "... minha Igreja. Agora sou o Papa de Roma. Não blasfeme na Casa de Deus!";
			link.l1 = "E aqui eu pensei... Bem, Sua Santidade, poderia dizer aos seus fiéis onde está o "+sTemp+" é agora?";
			link.l1.go = "PZ_Norman3";
		break;
		
		case "PZ_Norman3":
			dialog.text = "Ele partiu numa missão sagrada. Uma nova cruzada, por assim dizer. Vai tirar o dinheiro dos perversos e trazer pra mim.";
			link.l1 = "Para você, certo. Ele disse quando voltaria?";
			link.l1.go = "PZ_Norman4";
		break;
		
		case "PZ_Norman4":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "Daqui a um mês. Talvez um pouco mais. Estou esperando o retorno dele, junto com o resto do nosso grupo.";
			link.l1 = "Então ele está mesmo no mar. Melhor eu ir embora antes que pegue o que você tem.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_NormanBlock":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "Eu vou purificá-los todos nas chamas sagradas...";
			link.l1 = "Sua cabeça precisa de uma boa limpeza...";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoro1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				// ох, какой же костыль, м-м-мать...
				sld = characterFromId("Mary");
				if (sld.location != "Pirates_townhall")
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "with Marcus";
					else sTemp = "with Steve";
					
					dialog.text = "Charles! O que posso fazer por você?";
					link.l1 = "Olá, Helen! Quero conversar com "+sTemp+". Ele está lá em cima? Ou está na taverna?";
					link.l1.go = "PZ_HelenaIslaTesoroGood1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
					else sTemp = "Steve";
					
					dialog.text = "Charles! E... Ah, que surpresa agradável. O que posso fazer por vocês dois?";
					link.l1 = "Oi, Helen. Onde está "+sTemp+"?";
					link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
				else sTemp = "Shark";
				
				dialog.text = TimeGreeting()+", Charles. O que te traz aqui?";
				link.l1 = TimeGreeting()+", Helen. Estou procurando pelo "+sTemp+". Você sabe onde ele está?";
				link.l1.go = "PZ_HelenaIslaTesoroBad1";
			}
		break;
		
		case "PZ_HelenaIslaTesoroGood1":
			dialog.text = "Ele saiu, mas receio que vá demorar para voltar – está no mar, para ser exato.";
			link.l1 = "Droga.   Aconteceu alguma coisa?   Ele disse quando volta?";
			link.l1.go = "PZ_HelenaIslaTesoroGood2";
		break;
		
		case "PZ_HelenaIslaTesoroGood2":
			dialog.text = "Ele não voltou, mas não é nada grave – ele tem uma boa pista, como sempre. Normalmente ele retorna em um mês, dois no máximo. Eu entendo como é, às vezes eu também sinto falta do convés do navio...";
			link.l1 = "Você sempre pode ir para o mar. Seria bom fazermos isso juntos algum dia – você no 'Arco-Íris', eu no...";
			link.l1.go = "PZ_HelenaIslaTesoroGood3";
		break;
		
		case "PZ_HelenaIslaTesoroGood3":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			dialog.text = "Seria bom. Mas sua... namorada talvez não goste. E eu não quero ser o vela.";
			link.l1 = "Hum, desculpe, Helen, não quis te ofender. Obrigado pela conversa. Até mais.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steve";
			
			dialog.text = "Charles, você voltou. Posso ajudar em mais alguma coisa?";
			link.l1 = "Não, obrigado, Helen. Só queria ver se "+sTemp+" apareceu.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroBad1":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			else sTemp = "Steven";
			
			dialog.text = "Eu ficaria surpreso se você viesse me procurar. Quanto a "+sTemp+", ele está no mar.";
			link.l1 = "Sério? Ele disse quando vai voltar?";
			link.l1.go = "PZ_HelenaIslaTesoroBad2";
		break;
		
		case "PZ_HelenaIslaTesoroBad2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			dialog.text = "Aparentemente, ele está cansado de comandar esse esgoto e precisa se lembrar de que ainda é capitão de um navio. Não é a primeira vez. Normalmente, ele volta em um mês, talvez um mês e meio.";
			link.l1 = "Droga, então os barões nem sempre ficam parados assim? Obrigado, Helen. Adeus.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroBadBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steven";
			
			dialog.text = ""+sTemp+" ainda não voltou, Charles";
			link.l1 = "Entendi, só estava conferindo.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere1":
			dialog.text = "Ele é um homem livre, não é? Pode ir para o mar quando quiser.";
			link.l1 = "Claro que pode. Então, onde ele está?";
			link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere2";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "the Shark";
			
			dialog.text = "Mas Charles, se ele não está na ilha, então foi saquear os espanhóis. Agora, com licença, tenho muito o que fazer. Passe aqui de vez em quando – normalmente, o "+sTemp+" volta em cerca de um mês, às vezes um pouco depois.";
			link.l1 = "Tudo bem, Helen, obrigado. Vamos nos manter ocupados.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodMaryHereBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			dialog.text = "Não estou com cabeça para isso agora. Talvez volte outra hora, Charles?";
			link.l1 = "Claro, Helen. Desculpe incomodar. Se cuida.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_Longway_81":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				dialog.text = "Estamos em posição, Meu Senhor Capitão. Lembra-se do caminho?";
				link.l1 = "Claro, Longway. Só espero que a gente não perca isso naquela masmorra maldita...";
				link.l1.go = "PZ_Longway_FlagMartinInfo_1";		//Sinistra
			}
			else
			{
				dialog.text = "Estamos em posição, Meu Senhor Capitão. Você tem um plano?";
				link.l1 = "Ainda estou trabalhando nisso... Por quê, você tem alguma ideia?";
				link.l1.go = "PZ_Longway_NotMartinInfo_1";		//Rebbebion
			}
			DelLandQuestMark(npchar);
			LAi_SetCheckMinHP(npchar, 1, true, "");		//На 6 эпизод даём Лонгвею бессмертие
			
			LocatorReloadEnterDisable("Tortuga_town", "houseS4", false);
		break;
		
		case "PZ_Longway_NotMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Bem, acho que se corrermos até Chang Xing...";
			link.l1 = "Longway... Eu entendo o quanto você quer ver sua irmã, mas "+sStr+" está em perigo de morte agora, e isso não é só força de expressão! Você precisa entender que salvá-la é a prioridade máxima!";
			link.l1.go = "PZ_Longway_NotMartinInfo_2";
		break;
		
		case "PZ_Longway_NotMartinInfo_2":
			dialog.text = "Meu Senhor Capitão, duvido que compreenda de verdade o que tenho passado nesses dez anos. O que estou passando agora.";
			link.l1 = "Sabe, de certa forma, sim. Meu irmão está preso. E embora ainda não tenham feito mal a ele, a qualquer momento podem fazer o que quiserem com ele.";
			link.l1.go = "PZ_Longway_NotMartinInfo_3";
		break;
		
		case "PZ_Longway_NotMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Mas para onde você iria se fosse só a moça "+sStr+" quem precisava ser resgatado?";
			if (CheckAttribute(pchar, "questTemp.FMQT.GiveDiamonds") && !CheckAttribute(pchar, "questTemp.FMQT_ObchistilSunduk"))
			{
				link.l1 = "Há um lugar... uma pessoa... Mas não se preocupe com isso, Longway – eu mesmo preciso lidar com isso.";
				link.l1.go = "PZ_GoMarceline1";
			}
			link.l2 = "Na verdade, nem sei pra onde ir. Se eu sair bisbilhotando por aí sem cuidado, vou chamar atenção, e então "+sStr+" está definitivamente acabado. Então... Eu simplesmente não sei.";
			link.l2.go = "PZ_GoTogether1";
		break;
		
		case "PZ_GoMarceline1":
			dialog.text = "O quê? Por quê?";
			link.l1 = "Não vão simplesmente deixar você entrar lá – é alta sociedade, droga. Então, eu vou sozinho. Enquanto isso, vá até sua irmã. Eu me junto a você assim que puder. Boa sorte, Longway!";
			link.l1.go = "PZ_GoMarceline2";
			RemovePassenger(pchar, npchar);
		break;
		
		case "PZ_GoMarceline2":
			dialog.text = "Sim! Obrigado, Meu Senhor Capitão. E boa sorte para você também!";
			link.l1 = "Ah, obrigado – hoje estou mesmo precisando. Todos nós estamos.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineLongwayGo");
		break;
		
		case "PZ_GoTogether1":
			dialog.text = "Meu Senhor Capitão...";
			link.l1 = "Deixa pra lá. Vamos até sua irmã, Longway. Se nos separarmos agora – estamos mortos. Vamos logo ver sua irmã e descobrir onde fica o covil do Levasseur. Depois seguimos juntos de novo – preciso de toda ajuda possível agora. Espero que não seja tarde demais.";
			link.l1.go = "PZ_GoTogether2";
		break;
		
		case "PZ_GoTogether2":
			dialog.text = "Não vamos nos atrasar, Senhor Capitão. Não vamos perder mais tempo discutindo ou adiando. Vamos até Chang Xing!";
			link.l1 = "Você tem razão, vamos depressa.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_FrenchSoldier1":
			dialog.text = "Pra onde diabos você tá indo? Você ao menos sabe pra onde leva essa porta?";
			link.l1 = "Eu sei muito bem. Estou indo lá a negócios, não por curiosidade ou para roubar.";
			link.l1.go = "PZ_FrenchSoldier2";
		break;
		
		case "PZ_FrenchSoldier2":
			dialog.text = "Que assunto? Madame Levasseur não está disponível no momento. Além disso, ela é uma mulher casada – não é certo as pessoas ficarem rondando a casa dela.";
			link.l1 = "Casada, né. Mas ela recebe visitas de vez em quando, né? Inclusive particulares. Esta é uma dessas vezes. Ela está me esperando, e estou com pressa.";
			link.l1.go = "PZ_FrenchSoldier3";
		break;
		
		case "PZ_FrenchSoldier3":
			dialog.text = "Ela teria me avisado se fosse esse o caso.";
			link.l1 = "Sou um tipo especial de convidado – daquele que não precisa ser anunciado.";
			link.l1.go = "PZ_FrenchSoldier4";
		break;
		
		case "PZ_FrenchSoldier4":
			dialog.text = "Sim, do tipo de convidado que faz Sua Senhoria mandar me fuzilar. Ou a própria Senhora vai querer arrancar minha pele.";
			link.l1 = "Já fui hóspede da Madame Marceline antes. Garanto que nada vai lhe acontecer depois, soldado.";
			link.l1.go = "PZ_FrenchSoldier5";
		break;
		
		case "PZ_FrenchSoldier5":
			dialog.text = "Mas é claro, ficar de olhos fechados e deixar todo mundo entrar – esse é o trabalho da guarda da cidade.";
			link.l1 = "Eu não tenho tempo pra isso, seu burro teimoso...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_FrenchSoldierFight");
		break;
		
		case "PZ_Marceline1":
			dialog.text = "Você...";
			// начинаем проверять результат прохождения "Почти как дома"
			switch (pchar.questTemp.FMQT.Marceline)
			{
				// поделили алмазы и "охладили трахание, углепластики" (с)
				case "Fuck":
					link.l1 = "Oh sim, senhora. Seu cavaleiro está feliz em vê-la novamente. Vejo que ficou surpresa ao me ver. A alegria deste encontro... não é mútua?";
					link.l1.go = "PZ_MarcelineFuck1";
				break;
				
				// поделили алмазы, без трахания и углепластиков
				case "NoFuck":
					link.l1 = "Sim, eu disse. Sei que talvez eu não seja o homem mais bonito ou digno desta ilha, como a senhora mencionou no nosso último encontro, mas pelo menos sabe que sou um homem honesto. Por favor, me escute, senhora – não vou tomar muito do seu... precioso tempo.";
					link.l1.go = "PZ_MarcelineNoFuck1";
				break;
				
				// "сошлись вот где-то посередине" (с)
				case "Deception":
					link.l1 = "Por amor de Deus, faça silêncio, senhora, pare de gritar. Não estou aqui para me vingar porque enganou seu cavaleiro e fugiu com o tesouro do dragão. E lhe garanto, se eu quisesse matá-la, já teria atirado e fugido para salvar minha pele. Isto é Tortuga, afinal! Mas acho que a senhora já sabe que isso seria indigno de mim.";
					link.l1.go = "PZ_MarcelineDeception1";
				break;
			}
		break;
		
		case "PZ_MarcelineFuck1":
			dialog.text = "Ah, não! Eu só pensei que... Bem, não importa! Veja, línguas maldosas andam espalhando boatos sujos sobre mim – uma pobre mulher que, mesmo se quisesse, não teria como fazer mal a ninguém, nem se defender dos inimigos. Além disso, já faz tanto tempo... Achei que você tinha vindo até mim com más intenções, e não com boas. Fico feliz por estar enganada. É difícil viver cercada de gente que só deseja o mal.";
			link.l1 = "Como eu poderia? Mesmo que eu ouvisse algo assim, não acreditaria em uma só palavra. Mas você tem razão – não vim aqui só para te ver. Embora eu esteja feliz por ter vindo. Sei que isso vai soar estranho, mas... desta vez, seu cavaleiro precisa da sua ajuda, senhora.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineNoFuck1":
			dialog.text = "E você é muito mais sensível do que eu imaginava. No entanto, você também não está isento de falhas, Monsieur de Maure – eu esperava que fosse mais... refinado. Na verdade... ou você sempre foi assim, ou o Arquipélago já te corrompeu. Você deveria reaprender a falar com uma dama. Mas você tem razão – é um homem honesto, embora... simples.";
			link.l1 = "E você é uma mulher orgulhosa e vingativa. Seus olhos, suas palavras e... suas ações mostram isso. Então, se alguém pode me entender, é você. Assim como um dia eu entendi você. Então, vamos deixar o passado para trás. Pode me ajudar, senhora?";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineDeception1":
			dialog.text = "Oh... Eu admito que fui injusta com você naquela época. Mas foi só porque eu não tinha certeza de quem você era, nada mais! Você teria levado todos os diamantes embora de mim? Ou traria meu marido até lá, dizendo que soube pelos nossos criados que eu tinha roubado dele, negando sua própria participação? Afinal, todos buscam o favor dele, não de uma mulher pobre como eu... Agora vejo que estava errada sobre você. Por favor, aceite minhas desculpas... meu cavaleiro.";
			link.l1 = "Eu já não sei se eles são sinceros ou não. Mas isso não importa. Preciso da sua ajuda, Madame Marceline. É uma questão de vida ou morte. Por favor, não recuse.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_Marceline2":
			dialog.text = "Minha ajuda...? Certamente não sou a última mulher desta cidade, mas minha influência não é tão grande quanto todos pensam. Sou uma rainha que reina, não que governa. Mas vou ouvir você. O que minha humilde pessoa pode fazer por você?";
			link.l1 = "Eu entendo que este assunto é desagradável para a senhora, mas estou procurando seu marido, madame, e com certa urgência. O fato é...";
			link.l1.go = "PZ_Marceline3";
		break;
		
		case "PZ_Marceline3":
			dialog.text = "Isso é uma piada? Ele não está na residência no momento? Então deve estar viajando a negócios. Não posso ajudá-lo, Monsieur de Maure.";
			link.l1 = "Você desviou o olhar. Você sabe. Eu também sei. Só preciso chegar lá. Por favor, não finja que é a primeira vez que ouve falar do calabouço – você é inteligente demais para não saber.";
			link.l1.go = "PZ_Marceline4";
		break;
		
		case "PZ_Marceline4":
			dialog.text = "Ah, sinto que essa conversa vai me dar mais um fio de cabelo branco. Como se eu já não tivesse rugas o bastante. O que você está fazendo com a gente, Francois...";
			link.l1 = "Um fio grisalho só vai aumentar sua nobreza e não vai tirar sua beleza. Mas uma boa moça, inocente, caiu nas mãos do seu marido. E agora ela corre o risco de perder a beleza, a saúde, até a vida!...! Você sabe o que acontece com quem fica preso lá. Por favor, madame. Marceline... Ajude seu cavaleiro.";
			link.l1.go = "PZ_Marceline5";
		break;
		
		case "PZ_Marceline5":
			dialog.text = "Não sou mais o seu cavaleiro, né? Vai, eu não sou burra. Mas... eu vou te ajudar, de Maure. Afinal, isso não podia durar pra sempre. E um dia ia acabar vindo à tona. O que importa pra mim agora é sair na hora certa, do jeito certo. E... eu não posso te condenar a um sofrimento eterno por causa do que o meu ‘marido’ vai fazer com a sua... conhecida.";
			link.l1 = "Talvez eu já não seja mais o seu cavaleiro, senhora. Mas você também nunca foi minha dama desde o começo. Ainda assim, serei grato a você pelo resto da minha vida. Então, onde é este lugar?";
			link.l1.go = "PZ_Marceline6";
		break;
		
		case "PZ_Marceline6":
			dialog.text = "Bem, vou confiar na sua palavra, Charles. Nas masmorras da cidade. Em um dos becos sem saída há um grande barril, e ao lado dele começa um corredor que leva até o covil desse monstro. Eu não olhei lá dentro. Só o segui uma vez, faz muito tempo. E fiquei assustado quando ouvi os gritos desumanos daquelas pobres criaturas.";
			link.l1 = "Hoje você salvou muitas vidas, senhora. Não só a da minha querida, mas também de todos que poderiam ter caído nas mãos do seu marido no futuro. Obrigado.";
			link.l1.go = "PZ_Marceline7";
		break;
		
		case "PZ_Marceline7":
			dialog.text = "Ah, poupe-me dessas palavras vazias, monsieur. Você me pediu muito. E eu corri um grande risco. Agora tente fazer com que sua nova missão na toca do dragão seja um sucesso... meu cavaleiro.";
			link.l1 = "Vou fazer o meu melhor. Adeus, Marceline.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineOver");
		break;
		
		case "PZ_ElitaShluha_18":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "So, you're a bandit, monsieur...? We don't hire new girls like this; we all came here voluntarily. I'm going to have to ask you and your... accomplice to step out. And I'll make sure this girl gets treatment - otherwise, I'll report you to the authorities!";
				link.l1 = "Não somos bandidos. Mas essa moça não fica atrás de nenhum deles. Ela não carrega uma lâmina só para se exibir. Só está ferida. Este homem é meu amigo e também irmão da sua patroa. Então, deixe-nos vê-la.";
				link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl1";
			}
			else
			{
				dialog.text = "Que bom ver você de novo, monsieur! Mas você sabe que não aceitamos hóspedes... de classe baixa aqui. Mesmo que tenham referências e estejam pagos. Principalmente trabalhadores de pele amarela ou escravos negros. Receio que seu amigo terá que sair.";
				link.l1 = "Não diga isso na frente da sua patroa. Ela também tem a pele amarela. E esse não é um trabalhador, mas o irmão dela. Você não atrapalharia um reencontro de família, não é?";
				link.l1.go = "PZ_ElitaShluha_WithLongway1";
			}
		break;
		
		case "PZ_ElitaShluha_18_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "It's getting worse by the hour. First the mad yellow laborer and now you. No, monsieur, we don't pay for the girls who are brought to us by force; they are all here of their own free will.";
				link.l1 = "Eu salvei essa moça, e ela nunca mais vai trabalhar em um lugar que não esteja à altura dela . Uma trabalhadora braçal, você disse?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl1";
			}
			else
			{
				dialog.text = "Oh monsieur, que péssima hora! Não estamos aceitando mais hóspedes hoje – você pode ver por si mesmo o que aconteceu aqui.";
				link.l1 = "É por isso que estou aqui. Foi um homem de pele amarela que organizou tudo isso, não foi?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl1";
			}
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl1":
			dialog.text = "Sim, monsieur, um trabalhador! Mal conseguíamos entender o que ele dizia! Esse miserável entrou de repente e exigiu ver a senhora. Garantiu que era irmão dela. Chamamos os homens, mas...";
			link.l1 = "Isso não é obstáculo pra ele. O que aconteceu depois?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl2":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "Como acabou se revelando, ele não estava mentindo. A senhora veio até nós e o reconheceu. Na verdade, eles ainda estão conversando no lugar luxuoso dela.";
			link.l1 = "Quem sabe o que se passa na cabeça dele, né. Vamos entrar lá – vamos salvá-la, se for preciso. Não cause confusão – isso acabaria com a reputação do lugar.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl1":
			dialog.text = "Isso mesmo, monsieur. Ele disse que era irmão da moça.";
			link.l1 = "E você não deixou ele entrar...";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl2":
			dialog.text = "Claro que não! A senhora está vestida com muita elegância e fala sem sotaque, diferente daquele trabalhador. Tentamos expulsá-lo, e ele derrubou todos os guardas, dá pra acreditar?!";
			link.l1 = "Consigo imaginar perfeitamente. E onde ele está agora?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl3";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl3":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "Ele e a moça ainda estão conversando sobre alguma coisa, mas não conseguimos entender o que é – provavelmente estão falando na língua deles.";
			link.l1 = "Vou até eles. Talvez sua senhora precise de ajuda. Não chame os guardas – se isso se espalhar, ninguém mais vai bater à sua porta.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_WithLongway1":
			dialog.text = "Um irmão? A senhora é digna, o que é mais do que posso dizer desse ‘irmão’ dela. Não precisa mexer com a cabeça dela ou tentar enganá-la com esse peão. Leve-o daqui.";
			link.l1 = "Eu já disse que eles se perderam há muito tempo. Ele só teve menos sorte. Nós mesmos vamos pagar ao estabelecimento pelo nosso tempo. Avise a dona agora.";
			link.l1.go = "PZ_ElitaShluha_WithLongway2";
		break;
		
		case "PZ_ElitaShluha_WithLongway2":
			dialog.text = "Ela não tem motivo nenhum pra se preocupar com você. E não gosto dessa sua insistência. Rapazes! Expulsem esse trabalhador! E o patrão dele, que não vale nada, também!";
			link.l1 = "Droga! Quanta arrogância para uma cortesã!";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl1":
			dialog.text = "De jeito nenhum! Deixar a senhorita sozinha com toda essa sua companhia estranha? Só se o senhor for sozinho, monsieur. E seus... amigos vão esperar do lado de fora – aqui é um estabelecimento decente.";
			link.l1 = "Por que está preocupado com ela? Todo mundo sabe que ela é uma das melhores espadachins de Tortuga. E meus amigos são mais decentes do que a maioria das pessoas desta cidade.";
			link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl2";
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl2":
			dialog.text = "Rapazes! Tem um bandido ferido e um trabalhador imundo aqui dentro! Eles querem alguma coisa da nossa senhora! Acabem com eles!";
			link.l1 = "Que dedicação, caramba...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ChangShin1":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			
			// итак, снова проверка по результатам прохождения. Лонгвэй с нами, тян ещё в пыточной
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Imagino que você seja Charles de Maure? E isso... Ah.";
				link.l1 = "E você deve ser Belle Etoile. Ou devo dizer Chang Xing? Sim, este é seu irmão. Ele está procurando por você há mais de uma década. Ele e eu temos muitas, muitas perguntas para você. E não temos muito tempo.";
				link.l1.go = "PZ_ChangShin_WithLongway1";
			}
			// пришли с Лонгвэем и тян
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				dialog.text = "Meu Deus, você sobreviveu. Tem um bom defensor, mesmo que tenha chegado um pouco tarde. Melhor do que aquele que aparentemente me considera sua protetora e agora está aí do seu lado. O céu está do seu lado, minha querida.";
				link.l1 = "Vejo que você já sabe. Melhor ainda – não preciso explicar. Mas me diga, do que está sorrindo, Chang Xing? Você gosta de ver outras garotas sofrerem, não é? Afinal, é você quem as vende.";
				link.l1.go = "PZ_ChangShin_WithLongwayAndGirl1";
			}
			// Лонгвэй с нами, тян на небесах
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
				dialog.text = "Charles de Maure, certo? Ouvi dizer que queria falar comigo. Então, o que te preocupa? Não gostou do serviço do nosso estabelecimento da última vez que esteve aqui?";
				link.l1 = "Acabei de sair de outro estabelecimento seu, Chang Xing. "+sStr+", meu amor, está morto. E eu sei que você também teve parte nisso.";
				link.l1.go = "PZ_ChangShin_GirlDied1";
			}
		break;
		
		case "PZ_ChangShin_WithLongway1":
			dialog.text = "Chang Xing... Faz muito tempo que não ouço esse nome. Faz muito tempo. Brancos... vocês estão sempre com pressa. Que tal uma reunião de família sem pressa? Mas tanto faz pra mim. Parei de depender dos outros há anos. Por que não diz nada, meu irmão? Não está feliz em ver sua própria irmã? Você me procurou com tanta insistência, afinal.";
			link.l1 = "Temos outros assuntos urgentes e mais importantes para resolver. Fale com sua irmã, Longway. Mas lembre-se de onde ainda precisamos ir. Precisamos nos apressar. E eu também tenho perguntas para ela.";
			link.l1.go = "PZ_Longway_SisterDialog1";
		break;
		
		case "PZ_Longway_SisterDialog1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "(Em mandarim) Longway, hein? Bem, tirando o nome, você não mudou muito... Chang Tu.";
			link.l1 = "(Em mandarim) Mas você mudou muito, irmã. O que aconteceu? Seu olhar costumava ser tão quente quanto o sol do meio-dia. Agora está frio e só expressa desprezo. E sua voz? Eu adorava te fazer rir e ouvir aqueles sinos de prata tocando... Agora é mais fria que um Goango no inverno. E você usa as roupas deles. E vende as mulheres com suas próprias mãos, mesmo tendo sido sequestrada pelos Fermentelos.";
			link.l1.go = "PZ_Longway_SisterDialog2";
		break;
		
		case "PZ_Longway_SisterDialog2":
			dialog.text = "Você vem me dar lição de moral, mesmo tendo trabalhado para Rodenburg, um dos maiores canalhas do arquipélago? Acha que eu não sabia de você? Sempre soube. Não cabe a você julgar no que me tornei e por quê, meu irmão mais velho perdido.";
			link.l1 = "Então me deixe descobrir, Xing! E me conte. Se você sabia que eu estava no Arquipélago, por que não quis me encontrar depois de todos esses anos? Eu dediquei minha vida inteira a te procurar...";
			link.l1.go = "PZ_Longway_SisterDialog3";
		break;
		
		case "PZ_Longway_SisterDialog3":
			dialog.text = "Porque nem você, nem o Céu me protegeram do pior dos destinos. Então percebi que ninguém neste mundo precisa de mais ninguém. Só podemos contar conosco mesmos. Bem, eu conto se quiser saber. Mas vou falar na língua dele. Tenho certeza de que ele também gostaria de ouvir. Você entende francês, não é, Tu?";
			link.l1 = "(em francês ruim): Sim, eu falo essa língua.";
			link.l1.go = "PZ_Longway_SisterDialog4";
		break;
		
		case "PZ_Longway_SisterDialog4":
			dialog.text = "Ha ha ha, ai, Céus! Seu sotaque é terrível. Mas não é culpa sua – a pronúncia e a escrita do francês são mesmo difíceis.";
			link.l1 = "Você ri diferente agora, irmã...";
			link.l1.go = "PZ_ChangShin_WithLongway3";
		break;
		
		/*case "PZ_Longway_SisterDialog5":
			ReturnOfficer_Longway();
			
			StartInstantDialog("PZ_ChangShin", "PZ_ChangShin_WithLongway3", "Quest\CompanionQuests\Longway.c");
		break;*/
		
		case "PZ_ChangShin_WithLongway3":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			dialog.text = "Meu querido irmão quer saber o que aconteceu comigo ao longo dos anos. Acho que seria bom você ouvir também – como disse, você tem perguntas. Então não se preocupe – vou contar tudo em francês.";
			link.l1 = "Me conte só o essencial – quando Longway me contou a história da vida dele, levou boas horas. E agora estou com pressa.";
			link.l1.go = "PZ_ChangShin_WithLongway4";
		break;
		
		case "PZ_ChangShin_WithLongway4":
			dialog.text = "Você vai ter paciência. Guardei tudo só pra mim por mais de um ano. E se me interromper, não vou responder nenhuma das suas perguntas.";
			link.l1 = "Tudo bem... Então vá em frente.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl1":
			dialog.text = "Onde estão os seus modos, Charles de Maure? Disseram-me que você era um homem de excelentes maneiras e um verdadeiro cavalheiro com as damas. Só rumores, mas na verdade... um fracasso? Era o que eu pensava. E você está enganado – eu odeio todos os homens e mulheres igualmente. Na verdade, não confio em ninguém, não me surpreendo, não espero nada. Eu esmagaria suas bolas com prazer se pudesse pôr as mãos em você. Mas ouvir meu nome verdadeiro depois de tantos anos foi um pouco... revigorante.";
			link.l1 = "Eu sou um homem para as damas, não para bruxas como você. E de qualquer forma, o que você esperava, considerando que está envolvida em torturar a pessoa de quem mais gosto? Mal consigo me segurar para não fazer algo com você também. E não é só por causa dele. Longway é meu amigo. E você é da família dele. Ele está procurando por você há mais de uma década. E ele merece falar com você.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl2":
			dialog.text = "Que sentimental. E que triste que eu não me importo. Mas agora você não vai escapar tão fácil assim, vai, Tu? Não por te matar, nem por vocês todos terem se atrasado uma vez. Mas saber... Acho que você merece saber. Você me conheceu quando eu não era assim, irmão.";
			link.l1 = "Não importa o que tenha acontecido com você... você sempre teve uma escolha, Chang Xing.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl3";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl3":
			dialog.text = "Você ainda é jovem e não sabe como o mundo funciona, Charles de Maure. Só existe uma escolha de verdade na vida: viver ou morrer. Acho que seria bom pra você saber de tudo também. Então vou contar minha história em francês. Você fala, não fala, Tu?";
			link.l1 = "Com sotaque. Mas ele entende muito bem. Pode começar.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_GirlDied1":
			dialog.text = "E onde você esteve todo esse tempo? Espanhola fica a um ou dois dias daqui. A morte dela também é culpa sua. E você. Chegou mais de uma década atrasado. Nossos salvadores, nossos protetores. Quanto mais cedo uma mulher aprende a se defender, melhor. Algumas conseguem a tempo, outras não. E tem gente que não tem inteligência suficiente pra perceber isso.";
			link.l1 = "Tome cuidado com cada palavra que disser agora. Só ainda não te despedaçei por causa do meu amigo, seu irmão. Você não faz ideia do que ele passou por você.";
			link.l1.go = "PZ_ChangShin_GirlDied2";
		break;
		
		case "PZ_ChangShin_GirlDied2":
			dialog.text = "Duvido muito que ele tenha passado por algo remotamente parecido com o que eu passei.";
			link.l1 = "Então nos conte.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin2":
			dialog.text = "Bem, o que posso dizer, eu era jovem, burro e ingênuo naquela época. E intolerante. Tu já te contou sobre como fui sequestrado por Oliverio Fermentelos depois que ele matou meus pais e a mim?";
			link.l1 = "Isso mesmo.";
			link.l1.go = "PZ_ChangShin3";
		break;
		
		case "PZ_ChangShin3":
			dialog.text = "Ele me cortejou e confessou seus sentimentos, mas eu o rejeitei. E foi então que ele massacrou nossa família e me levou. E depois...";
			link.l1 = "Posso imaginar.";
			link.l1.go = "PZ_ChangShin4";
		break;
		
		case "PZ_ChangShin4":
			dialog.text = "Eu queria que você pudesse. Depois ele me confessou seus sentimentos de novo, fervendo e chorando, dizendo que era o único jeito, porque minha família nunca me deixaria ir com ele.";
			link.l1 = "Loucura...";
			link.l1.go = "PZ_ChangShin5";
		break;
		
		case "PZ_ChangShin5":
			dialog.text = "Heh, uma palavra para descrever toda a minha vida desde então. Eu o rejeitei de novo. E continuou assim por um tempo. Mas, obviamente, isso não podia durar para sempre, porque eu estava completamente à mercê dele.";
			link.l1 = "Então aconteceu mesmo?";
			link.l1.go = "PZ_ChangShin6";
		break;
		
		case "PZ_ChangShin6":
			dialog.text = "Claro. Ele me tomou à força, de forma bruta e sem piedade. Não que isso incomode estupradores, mas ele não tinha me confessado antes, chorando, o seu grande amor? Pff! O amor sumiu, pelo visto. E tudo isso continuava, dia após dia, como se fosse rotina. No começo, eu gritava e resistia, mas depois parei – qual era o sentido mesmo...?";
			link.l1 = "Mas Fermentelos teve o que merecia, e você acabou aqui. Como isso aconteceu?";
			link.l1.go = "PZ_ChangShin7";
		break;
		
		case "PZ_ChangShin7":
			dialog.text = "Bem, não demorou muito para ele se cansar de mim. Engraçado, não é? Ele matou meus pais e os de Tu, me roubou, me violentava sempre, só para me descartar no final. Veio para este Arquipélago e me vendeu como escrava para o Levasseur.";
			link.l1 = "Eu não desejaria isso nem ao meu pior inimigo. Então, como você sobreviveu? E como acabou livre, afinal? Pelo que ouvi, Levasseur nunca deixava mulheres saírem do seu esconderijo. Ele sempre dava um jeito de se livrar delas.";
			link.l1.go = "PZ_ChangShin8";
		break;
		
		case "PZ_ChangShin8":
			dialog.text = "É assim que as coisas são agora. Levasseur era diferente naquela época. Não, ele sempre foi uma fera. Mas no começo, ele às vezes sequestrava jovens colonos locais, estuprava-os no porão dele e se livrava deles quase imediatamente para não ter que pagar pelo silêncio. Só raramente ele mantinha alguém por mais de alguns dias, naqueles anos. Comigo, por outro lado, foi diferente desde o início.";
			link.l1 = "Porque você era um escravo, certo?";
			link.l1.go = "PZ_ChangShin9";
		break;
		
		case "PZ_ChangShin9":
			dialog.text = "Exatamente. O maior desejo de Levasseur não era só o prazer físico. Nem mesmo aquela sensação passageira de poder sobre as vítimas — afinal, ele já manda em toda a ilha. Mas...";
			link.l1 = "... o prazer de vê-los quebrar - a vontade, o olhar, a voz, o comportamento.";
			link.l1.go = "PZ_ChangShin10";
		break;
		
		case "PZ_ChangShin10":
			dialog.text = "Sim. Vejo que você fez sua lição de casa, Capitão. Mas, nesse sentido, eu não fui diversão pra ele – Fermentelos já me entregou quebrada. E Levasseur não me achava bonita – ele não gosta de mulheres asiáticas. Sabe, por algum motivo isso me marcou tanto – eu sei que sou atraente, mas não acho que sou realmente bonita. E não acredito quando me dizem isso. Mesmo agora, quando faço exercícios, uso sedas e me perfumo com fragrâncias finas. Não que eu precise da aprovação do meu carrasco, mas...";
			link.l1 = "Então vou repetir minha pergunta – como você sobreviveu? Assim que ele se cansa de uma mulher, ele se livra dela. Com você, pelo que diz, ele já estava entediado desde o começo.";
			link.l1.go = "PZ_ChangShin11";
		break;
		
		case "PZ_ChangShin11":
			dialog.text = "Acho que o fato de eu tê-lo entediado desde o começo teve seu peso. E o fato de eu ser uma escrava – eu não podia ir a lugar nenhum, nem dizer nada. Meninas escravizadas são tratadas assim há milhares de anos. Ele começou a pensar em como tornar o tempo que passava comigo ‘divertido’ para ele.";
			link.l1 = "Acho que foi assim que nasceram os vícios dele, do jeito que são hoje.";
			link.l1.go = "PZ_ChangShin12";
		break;
		
		case "PZ_ChangShin12":
			dialog.text = "Exatamente. No começo, eram surras, cusparadas e outras humilhações. E zombarias – tanto da minha aparência quanto da minha origem, do meu sangue. Depois vieram as primeiras torturas – facas, tenazes, uma frigideira... Por isso uso roupas tão fechadas – meu corpo inteiro está marcado, queimado, mutilado. E é por isso que nunca mais pretendo me despir na frente de um homem. Nunca mais. Foi então que finalmente entendi o que já devia ter percebido quando Fermentelos me sequestrou.";
			link.l1 = "O que foi isso?";
			link.l1.go = "PZ_ChangShin13";
		break;
		
		case "PZ_ChangShin13":
			dialog.text = "Que eu não deveria mais ser uma marionete indefesa. Pelo contrário, eu deveria tomar as rédeas da minha vida. No meu caso, uma mulher só consegue mudar alguma coisa em sua vida se conseguir controlar os homens ao seu redor.";
			link.l1 = "Eu não diria que Levasseur pode ser controlado.";
			link.l1.go = "PZ_ChangShin14";
		break;
		
		case "PZ_ChangShin14":
			dialog.text = "E você não estaria errado. Mas é possível influenciá-lo com cuidado. Levasseur odeia tanto a obediência cega desde o início quanto discussões ou súplicas. O mesmo vale para bajulação – ele percebe muito bem o porco que é. Isso eu entendi logo, a um preço bem doloroso. Mas, quando ele ficava satisfeito com tudo depois de mais uma noite de tortura e violência, dava para conversar com ele com calma. Talvez eu não tenha sangue nobre, mas inteligência não me falta.";
			link.l1 = "E sobre o que vocês conversaram?";
			link.l1.go = "PZ_ChangShin15";
		break;
		
		case "PZ_ChangShin15":
			dialog.text = "Consegui chamar a atenção dele. Sugeri ideias de tortura, aconselhei quais instrumentos era melhor evitar e com quais valia a pena começar. No início, é claro, ele testou tudo em mim. Mas depois... passou a me respeitar, do jeito distorcido dele. O que se passa na cabeça desse homem? Tentei descobrir como ele ficou assim, mas ele me espancou de novo, quase até a morte. Depois trouxe um médico particular.";
			link.l1 = "Isso é ainda mais estranho e repugnante do que tudo que já ouvi sobre ele.";
			link.l1.go = "PZ_ChangShin16";
		break;
		
		case "PZ_ChangShin16":
			dialog.text = "Ele não exigia mais que eu me entregasse a ele. Passou a me chamar de pupila. Mas sempre dizia que, como seu projeto, eu era uma completa decepção. Acho que era pra me manter alerta. Então começou a me ensinar esgrima e idiomas. Apesar de me manter no porão, era eu, e não a esposa dele, quem ganhava todos os vestidos caros.";
			link.l1 = "Um projeto, de fato. Dá pra ver claramente o paralelo com o jeito que você comanda este lugar.";
			link.l1.go = "PZ_ChangShin17";
		break;
		
		case "PZ_ChangShin17":
			dialog.text = "Eu não tinha pensado nisso, hmmm. E não gosto da sua comparação, porque eu não torturo minhas funcionárias. E não deixo meus clientes fazerem isso. Mesmo odiando aquelas vadias e invejando a beleza delas. E eu não tenho nada em comum com aquele porco, lembre-se disso.";
			link.l1 = "Então, como você conseguiu este bordel?";
			link.l1.go = "PZ_ChangShin18";
		break;
		
		case "PZ_ChangShin18":
			dialog.text = "Do Levasseur, é claro. Por um tempo, ele me manteve em sua casa. De vez em quando, até me pedia conselhos sobre como quebrar essa ou aquela garota. Afinal, eu era especial para ele, mesmo que nunca admitisse. Eu fui a primeira. Eu vi tudo.";
			link.l1 = "Quem aprendeu com quem, mesmo?";
			link.l1.go = "PZ_ChangShin19";
		break;
		
		case "PZ_ChangShin19":
			dialog.text = "Eu não sou assim! Eu odeio, com toda a minha alma, quem teve tudo servido de bandeja! Isso não é justo! Este bordel foi ideia minha! Minhas trabalhadoras são filhas de mercadores, oficiais e nobres que, às vezes, se envolveram com o Levasseur. Eu pedi para ele entregá-las para mim. Tortura e humilhação num porão secreto é uma coisa. Mas a vida pública de cortesã para gente como elas é outra bem diferente!";
			link.l1 = "Eu não diria que suas funcionárias parecem tão humilhadas, miseráveis e destruídas.";
			link.l1.go = "PZ_ChangShin20";
		break;
		
		case "PZ_ChangShin20":
			dialog.text = "Porque eles sabem o que Levasseur ou até mesmo eu faríamos com eles se ousassem abrir a boca. Mas você está certo em parte, claro. O vinho, a comida, as sedas, a ausência de tortura diária – muitos começaram a me ver como um salvador. Idiotas! Só alguns poucos não estão felizes aqui. Alguns deles ele entregou com o coração pesado. E ele ria, dizendo que eu sempre poderia devolver qualquer um deles para ele em troca de resolver os problemas de dinheiro do meu lugar. Mas eu sempre disse não. Pelo menos assim eles trariam o ouro de volta em vez de morrerem no porão à toa. Seria uma saída fácil demais para eles.";
			link.l1 = "Que pena que nem todos se sentiram humilhados, trocando claustros piores que a Santa Inquisição por uma gaiola dourada como o seu bordel...";
			link.l1.go = "PZ_ChangShin21";
		break;
		
		case "PZ_ChangShin21":
			dialog.text = "Você me julga? Eu não queria só sobreviver, queria construir um comércio de verdade. Mesmo sem perceber, Levasseur me devia gratidão. Mesmo eu não sendo mais escrava, ele não podia me deixar ir. Continuava me forçando a trabalhar pra ele e ajudar os capangas dele. Principalmente aquele sobrinho magricela, que babava toda vez que me via. Mas não tinha coragem de me atacar ou falar comigo de forma desrespeitosa. Nojento. Sabe, mesmo me chamando de decepção, eu era mais útil que Thibaut e Martene juntos. Eu acompanhava eles com frequência por ordem dele, como naquela vez em Port-au-Prince.";
			link.l1 = "Isso explica muita coisa...";
			link.l1.go = "PZ_ChangShin22";
		break;
		
		case "PZ_ChangShin22":
			dialog.text = "Isso mesmo. Escute. Eu não torturei sua amada. Assim como nunca torturei nenhuma moça com estas mãos, mesmo que às vezes tenha dado conselhos ao Levasseur. Mas já que tocamos no assunto...";
			link.l1 = "O quê?";
			link.l1.go = "PZ_ChangShin23";
		break;
		
		case "PZ_ChangShin23":
			dialog.text = "Como talvez saiba, Levasseur às vezes exige que tragam para ele uma certa moça que foi vista em Tortuga e depois deixou a ilha. Ou então alguém o surpreende trazendo uma desconhecida para ganhar seu favor, como aconteceu comigo. Sequestrar sua amada foi ideia minha.";
			link.l1 = "O que você acabou de dizer...?";
			link.l1.go = "PZ_ChangShin24";
		break;
		
		case "PZ_ChangShin24":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "At first, we were considering capturing that blonde who used be so close to you. But since she is untouchable now, and because we have already promised him a girl, you redhead had to do.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "I heard rumors about your gorgeous companion who never leaves your side. Considering Levausser's love for blondes, I had very little trouble selling him this idea.";
			dialog.text = "Sotta, o cachorro dele, era pra trazer pra ele a mulata, a mulher do Lutter. Mas você matou o Sotta, então - nada de mulata pro chefão. Levasseur ficou furioso. Todo mundo apanhou - Thibaut, Martene, até eu. Não sei quem me deixou mais irritado: ele, porque me bateu de novo, ou você, que causou tudo isso... "+sStr+"";
			link.l1 = "Então nem foi por causa dele... Foi você quem fez isso.";
			link.l1.go = "PZ_ChangShin25";
		break;
		
		case "PZ_ChangShin25":
			dialog.text = "Eu nem espero pelo seu perdão, e, além disso, não preciso dele. Se você quer sangue, vai ter sangue. E vai se arrepender amargamente. Mas não vou recusar compreensão. Pela primeira vez em dez longos anos, eu aceitaria isso. Tudo o que fiz foi tentar, do meu jeito, sair de Tortuga um dia. Tem alguma pergunta para mim, Charles de Maure?";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "Mas você participou do rapto. E sabe onde o Levasseur mantém as vítimas dele. Me diga onde é. E se o pior ainda não aconteceu – vou pensar seriamente em não me vingar de você.";
				link.l1.go = "PZ_ChangShinDontKnow1";
			}
			else
			{
				link.l1 = "Bem, finalmente tudo está se encaixando...";
				link.l1.go = "PZ_ChangShin26";
			}
		break;
		
		case "PZ_ChangShinDontKnow1":
			dialog.text = "Eu sei porque eu estava lá. E se você acha que eu sou apegado a ele de forma doentia e recíproca – está muito enganado. Eu ficaria feliz em ver alguém enfiar aquele porco num espeto.";
			link.l1 = "Não tenho tempo, Chang Xing. Onde está?";
			link.l1.go = "PZ_ChangShinDontKnow2";
		break;
		
		case "PZ_ChangShinDontKnow2":
			dialog.text = "Você conhece o calabouço local sob as ruas da cidade? É pra lá que você vai. Em um dos becos sem saída tem um grande barril de vinho, e ao lado dele começa uma passagem secreta para o quarto de prazeres dele, como ele às vezes chama.";
			link.l1 = "Bem, finalmente tudo está se encaixando...";
			link.l1.go = "PZ_ChangShin26";
		break;
		
		case "PZ_ChangShin26":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip")) StartInstantDialog("Longway", "PZ_Longway_SisterDialog6", "Quest\CompanionQuests\Longway.c");
			else
			{
				dialog.text = "Que bom pra você. Agora suma daqui. Por mais que eu quisesse falar depois de tantos anos, saber que você conhece todos os meus segredos, sabe o que fizeram comigo – isso me enoja. Só de olhar pra você agora eu sinto raiva. Ah, e o Tu fica comigo.";
				link.l1 = "Por quê?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet1";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet1":
			dialog.text = "Talvez porque eu sou da família dele? E porque eu vejo como ele fica com você – um sujeito derrotado, infeliz, que mal teve tempo de aprender direito a língua e falar como gente. Mesmo assim, ele me disse que vocês eram amigos. Dá pra ver como você influenciou ele. Pelo menos eu vou fazer dele um homem de verdade.";
			link.l1 = "E você está mesmo feliz consigo? No que você vai transformá-lo? Numa criatura cruel e amarga que negocia vidas?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet2";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet2":
			StartInstantDialog("Longway", "PZ_Longway_SisterDialog_Ubezhdaet3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet3":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				dialog.text = "Meu Senhor Capitão, por favor, pare. Eu peço que deixe minha irmã em paz. E... eu vou ficar com ela.";
				link.l1 = "Você... o quê? Longway... mas por quê? Você não vê no que ela se tornou?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet4";
			}
			else
			{
				dialog.text = "Você é diferente? Você mudou com o tempo. Para pior. No começo, você era educado e compreensivo. Mas depois ficou grosseiro, até mais do que Rodenburg. E quando eu precisei de um bom navio para pegar Van der Vink, você me deu uma sucata!";
				link.l1 = "Longway...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet8";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Um dia, eu parti para o mar e passei todos esses anos só para encontrar e salvar minha irmã. E agora ela está aqui, a salvo. Minha missão está cumprida. E... Meu nome é Chang Tu. Longway é o nome que o traidor Van Merden me deu, caso tenha esquecido. Mas Chang Tu é um homem livre. A longa jornada de Chang Tu finalmente chegou ao fim.";
			link.l1 = "Ela vai te transformar em um servo, como Rodenburg fez comigo. Vai te pressionar porque vocês são família. E você vai mesmo ficar do lado de quem causou tudo isso comigo e "+sStr+" tanta dor?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet5";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Neste momento, é você quem está pressionando Chang Tu. Por favor, me deixe ir. Estou muito cansado. Você é um homem bom, Capitão – o Céu pode atestar isso. Mas você não é minha família. Ela é. Se eu não ficar, todos esses anos terão sido em vão. Agora serei a estrela que a guia e reacenderei o fogo que nela se apagou – quente e acolhedor, não algo que destrua tudo ao redor.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				link.l1 = "Hum, você tem razão. Talvez eu esteja forçando demais agora. Bem, sempre te respeitei. Desejo que você finalmente reencontre sua irmã. Mas aviso: você não vai encontrar paz ao lado dela.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva")) 
				{
					pchar.questTemp.PZ_LongwayHochetMira = true;
					link.l1.go = "PZ_Longway_SisterDialog_ReactiaDevushek";
				}
				
			}
			else
			{
				link.l1 = "Você não pode me deixar agora! Ainda preciso salvar "+sStr+" do Levasseur! Quer que eu vá lá sozinho? Me ajuda, Longway. E depois eu te deixo ir. Eu te prometo.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet6":
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Eu posso lidar com isso. Não precisa mais se preocupar comigo. Obrigado.";
				link.l1 = "Parece que sua irmã está irritada porque decidimos nos separar em paz.";
			}
			else
			{
				dialog.text = "Você vai descobrir, Senhor Capitão. O senhor é o homem mais inteligente que já vi. Pode lidar facilmente com esse verme que só sabe atormentar mulheres. Só peço, não me obrigue a isso. Minha irmã tem tanto para me contar! E... meu nome é Chang Tu.";
				link.l1 = "Você percebe que, se me deixar agora, estará me traindo?! Principalmente ficando com ela – a mulher que começou tudo isso!";
			}
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet7";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Não tema, Capitão. Embora ela fale de mim com desrespeito,  sou o irmão mais velho e o último parente homem dela. Pode ir. Não vou deixar que ela te mate. Adeus.";
				link.l1 = "Adeus... Chang Tu.";
				DeleteAttribute(pchar, "questTemp.PZ_LongwayRyadom");
				AddDialogExitQuest("PZ_BrothelTeleportVZal");	//Мирно разошлись
			}
			else
			{
				dialog.text = "Já disse tudo o que tinha pra dizer. Adeus, Capitão. E boa sorte pra você. Chang Tu sempre será um homem livre. Não se esqueça disso.";
				link.l1 = "E é isso que eu recebo depois de ter deixado tudo para trás e te ajudado na sua busca?! Depois do que estão fazendo com "+sStr+" agora?! Você é um traidor, Chang Tu. E vai morrer como tal, vocês dois, suas cobras malditas!";
				link.l1.go = "exit";
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				AddDialogExitQuest("MainHeroFightModeOn");
				AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8":
			dialog.text = "Meu nome é Chang Tu. Longway está morto. Você o matou. Você não é mais meu Capitão. E agora você vai morrer. Minha família finalmente encontrará paz, e nossa estrela vai brilhar forte no céu da noite.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
			{
				link.l1 = "(Confiável) (Liderança) Longway... Chang Tu. Pare. Eu sei que não fui o capitão perfeito para você. Mas você realmente quer tanto me matar por causa disso? Depois de tudo que passamos juntos? Primeiro Rodenburg, agora a busca pela sua irmã.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet9";
				Notification_Perk(true, "Trustworthy");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
			}
			else
			{
				link.l1 = "Longway, eu sou seu Capitão. Não sou sua família e nem babá. Eu dou ordens, não fico pensando se te ofendi sem querer. Você faz exigências como se fôssemos um velho casal, pelo amor de Deus...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet15";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
			}
			link.l2 = "É. Agora eu vejo. Você é tão podre quanto qualquer canalha egoísta... Longway. Igualzinha à sua irmã. Minha família vai sobreviver a este dia. A sua – não vai. Vai pro inferno!";
			link.l2.go = "PZ_Longway_SisterDialog_Ubezhdaet8_1";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetFightMode(pchar, true);
			DoQuestCheckDelay("PZ_ChangShinAndLongwayFightMe", 0.5);
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet9":
			dialog.text = "Se eu tiver que escolher entre você e minha família – ainda escolho minha família, mesmo que seja uma escolha difícil.";
			link.l1 = "Uma família que não moveu um dedo enquanto você procurava por ela todos esses anos? Ah, mas aí, de repente, chegou a hora certa! Eu, por outro lado, larguei tudo pra te ajudar. Você, bem aqui na minha frente, é o resultado disso. Olha, eu sou mais família pra você do que ela, meu amigo!";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet10";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet10":
			dialog.text = "Você está certo. Como sempre, você está certo. Vai me perdoar, Meu Senhor Capitão?";
			link.l1 = "Não há nada para perdoar! Você está certo sobre uma coisa – eu nem sempre fui o Capitão que você merece. Acho que agora estamos quites. Aliás, como prefere que eu te chame daqui pra frente? Longway? Ou é Chang Tu?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet11";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet11":
			dialog.text = "Pode me chamar de Longway. Já me acostumei com você me chamando assim.";
			link.l1 = "Então vamos esquecer todas as desavenças, e seja bem-vindo de volta a bordo, Longway.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet12";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet12":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_Ubezhdaet13", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet13":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			dialog.text = "Você! O que está dizendo?! Por que parou?! Mata ele! Pra ele, você sempre vai ser só um serviçal! Sua família sou eu, só eu!";
			link.l1 = "Ela está tão furiosa, não está, Longway? Você não é mais da família dele, Xing. Isso acabou quando soube da chegada do Longway ao Arquipélago e escolheu ignorar. Vamos embora.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet14";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet14":
			dialog.text = "Acho que nunca tive uma chance real de arrancar essa mentalidade de escravo dele. Não posso salvá-lo. Então vou matar vocês dois eu mesmo.";
			link.l1 = "Você é quem não pode ser salvo aqui. Sabe, eu fui compreensiva e até perdoei você demais. Mas isso aqui é ainda melhor. Acho que até o Longway já percebeu que você é uma cobra. Ele não vai lamentar muito a sua perda.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet15":
			dialog.text = "Piadas não são apropriadas agora! Você esconde seu medo e fracasso atrás delas! Isso só me convence ainda mais. Defenda-se, de Maure! Pois Chang Tu não tem intenção de poupar você.";
			link.l1 = "Sinto muito que tenha terminado assim. Mas se é isso que você quer, que seja. Nesse caso, você também não vai ter nenhuma piedade da minha parte.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaDevushek":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_Longway_SisterDialog_ReactiaMary", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Charles, escute...";
				link.l1 = "Helen?";
			}
			else
			{
				dialog.text = "Charles, Longway, pare...";
				link.l1 = "Helen, é melhor você ficar atrás de mim agora. Eu me sentiria mais seguro assim, caso eles nos ataquem.";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena2":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "I'm so tired; I can hardly stand. I just want to get out of here. We're not going to drag Longway back to the ship if he doesn't want to come, are we? I'll be your navigator and first mate, my Captain. Hopefully, your most trusted and beloved too. Besides, he's got a point - we're not his family. She is, for better or worse.";
				link.l1 = "But what about her? She's the reason you were tortured; it was all her idea. And she's the one who kidnapped you.";
			}
			else
			{
				dialog.text = "Mas eles não vão, né? Vamos embora agora, é só isso. Se é assim que ele pensa da gente depois de tudo que fizemos por ele, não adianta tentar mudar a cabeça dele. As ações falam mais alto que palavras. Se ele quer ficar com a irmã dele, deixa.";
				link.l1 = "Helen, você sofreu tanto por causa dela...";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena3":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Deixe essa demônia sozinha com seus próprios demônios. Logo eles vão devorar a alma dela. E as nossas merecem um bom descanso. Vamos.";
				link.l1 = "É. Acho que devemos. Vamos sair daqui, meu anjo. E você – Longway, ou Chang Tu – adeus.";
			}
			else
			{
				dialog.text = "Mas eu não morri. E o pior não aconteceu. Estou aqui, com você, e é isso que importa. E Levasseur está morto. Sem ele, ela não é nada. O lugar dela está afundando e logo vai acabar. E eles vão junto. Vamos, meu capitão. Não temos mais nada pra fazer aqui.";
				link.l1 = "Não vou discutir, Helen.";
			}
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena4":
			StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena5":
			dialog.text = "Onde você está indo?";
			link.l1 = "O quê, surpreso que não estamos ansiosos pra abrir você e sua irmã no meio, Longway? Essa é a diferença entre nós. E ainda assim você acha que eu sou o vilão... Mas tudo bem, olha só. Se quiser me matar, vai ter que matar a Helen também. Ela está ferida, machucada. Você realmente quer fazer isso?";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena6":
			dialog.text = "Uhum.";
			link.l1 = "Eu vejo a dúvida nos seus olhos, mesmo com todos os rancores que guarda de mim. Mas vamos seguir o exemplo da Helen, certo? Ninguém na nossa tripulação é mais bondoso ou mais capaz de perdoar do que ela. Estamos indo embora. E se ainda restar alguma bondade ou juízo em você, não vai tentar nos impedir.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena7";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena7":
			dialog.text = "Seja assim. Peço desculpas. Mas você não é mais o meu Capitão.";
			link.l1 = "Eu vou superar isso de algum jeito. Desejo tudo de bom para você e sua irmã, apesar do que ela fez. Adeus, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary":
			dialog.text = "Vamos, Charles, está na hora de acabar com este motim.";
			link.l1 = "Deus sabe que eu não queria fazer isso... e ainda não quero.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary2":
			dialog.text = "Você não?! Charles, me escuta. Você fez tanto por ele, e o que recebeu em troca? Traição e palavras cruéis, né! Você vai mesmo deixar isso passar?";
			link.l1 = "Eu não quero derramar o sangue do Longway. Não esqueci que já fomos amigos um dia.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary3":
			dialog.text = "Amigos assim não valem nada – são piores que inimigos, né! Charles, olha pra mim. Olha o que aconteceu comigo – por causa da irmã dele, que zombou, me insultou e me humilhou a caminho desta ilha maldita!";
			link.l1 = "Mary, eu entendo – você está muito, muito brava agora...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary4";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary4":
			dialog.text = "Ah não, Charles, eu não estou só com raiva, não... Eu estou furiosa! E não é só pelo que aquele desgraçado miserável te disse! Olhe pra mim de novo, Charles—e imagine quantas meninas ainda vão passar por isso se a gente não acabar com isso. Aqui e agora.";
			link.l1 = "Eles não vão machucar mais ninguém. Levasseur está morto.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary5";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary5":
			dialog.text = "Charles, você realmente ouviu as heresias que ela estava dizendo? Ela é tão responsável pelo que aconteceu naquele porão quanto aquele porco imundo. Agora olhe para o Longway – ou seja lá qual for o nome dele agora. Viu como ela conseguiu colocar ele do lado dela num piscar de olhos, né! Quem sabe que outras ideias doentias ela vai enfiar na cabeça desse traidor? Você acha mesmo que essa demônia vai ter dificuldade em empurrar ele para o caminho do Levasseur? Não pense no que ele é agora, Charles. Pense no tipo de monstro que ele pode virar em um ano... ou até em um mês. Você sabe que eu estou certo, não sabe?";
			link.l1 = "Por mais que me custe admitir, não tenho nada para te contradizer, Mary...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary6":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_ReactiaMary7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary7":
			dialog.text = "Ha-ha-ha! Fascinante, que espetáculo. Faz tempo que não rio assim de verdade. E ela tem coragem, isso eu admito.";
			link.l1 = "Cala a boca, sua vadia.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary8";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary8":
			dialog.text = "Engraçado isso, não é, de Maure? Eu adoraria ver Tu te derrubar pessoalmente. E olha só, sua mulher é tão sanguinária quanto eu. Muito bom. Não vou ficar parado — treinei com Levasseur e alguns dos melhores de Tortuga. Vamos ver qual dupla sai por cima.";
			link.l1 = "Você não teve um bom professor. E ainda irritou a Mary. Acabou pra você. Mesmo se eu não estivesse aqui, sua dupla não teria chance contra ela.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog6":
			dialog.text = "Sim. Finalmente. Longway pode falar com minha irmã de novo, Senhor Capitão? Não vai demorar.";
			link.l1 = "Claro. Só seja rápido - não temos muito tempo.";
			link.l1.go = "PZ_Longway_SisterDialog7";
		break;
		
		case "PZ_Longway_SisterDialog7":
			dialog.text = "Longway, faça isso rápido.";
			link.l1 = "Bom.";
			link.l1.go = "PZ_Longway_SisterDialog7_1";
		break;
		
		case "PZ_ChangShin26":
			StartInstantDialog("СhangShin", "PZ_Longway_SisterDialog7_1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog7_1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "E o que você queria me contar, meu irmão?";
			link.l1 = "O Longway está muito decepcionado com você, Xing.";
			link.l1.go = "PZ_Longway_SisterDialog8";
		break;
		
		case "PZ_Longway_SisterDialog8":
			dialog.text = "(Em mandarim) Por que você não fala nossa língua já que quis conversar de novo, Tu? Está com vergonha dele? Se eu fosse você, teria mais vergonha do seu sotaque.";
			link.l1 = "Não. Longway não tem mais segredos para o Senhor Capitão. Não mais.";
			link.l1.go = "PZ_Longway_SisterDialog9";
		break;
		
		case "PZ_Longway_SisterDialog9":
			dialog.text = "(em francês) Primeiro Rodenburg, agora de Maure. Você sempre precisa de um ‘monsieur’. Em mais de uma dúzia de anos aqui, não conseguiu nada. Nem sequer aprendeu uma das línguas deles. E são tão mais simples que a nossa! Se alguém aqui é uma decepção, esse alguém é você.";
			link.l1 = "Mas eu não negocio mulheres. Não participo do sequestro e da tortura delas.";
			link.l1.go = "PZ_Longway_SisterDialog10";
		break;
		
		case "PZ_Longway_SisterDialog10":
			dialog.text = "Você está falando sério? Quer que eu faça uma lista do que você já fez pelo Rodenburg? O que eu tenho feito seria brincadeira de criança perto disso.";
			link.l1 = "Eu tinha um propósito – encontrar você. Mas você nem queria me ver. E quando finalmente te encontrei, encontrei um monstro, não aquela estrela quente e guia que um dia iluminou o meu caminho.";
			link.l1.go = "PZ_Longway_SisterDialog11";
		break;
		
		case "PZ_Longway_SisterDialog11":
			dialog.text = "Um monstro? Bem, talvez você tenha razão. Não sou mais a garota alegre que você conheceu. Se eu tivesse continuado assim, a vida teria me devorado e cuspido fora. Precisei criar meus próprios dentes. Minha estrela já se apagou faz tempo. Mas ainda sou sua irmã, Tu.";
			link.l1 = "Não. Você não é mais minha irmã.";
			link.l1.go = "PZ_Longway_SisterDialog12";
		break;
		
		case "PZ_Longway_SisterDialog12":
			dialog.text = "Desistir de mim assim tão fácil depois de todos esses anos? Heh... E quem sabe, talvez eu ainda fosse o mesmo se você tivesse chegado a tempo de matar o Fermentelos naquele dia?";
			link.l1 = "Você está certo. Em parte, a culpa também é minha. É minha responsabilidade. E eu vou acabar com isso. Vou te libertar desse sofrimento. Dar fim a essa existência miserável.";
			link.l1.go = "PZ_Longway_SisterDialog13";
		break;
		
		case "PZ_Longway_SisterDialog13":
			dialog.text = "Você vai mesmo matar a própria irmã, Chung Tu? Não que você vá conseguir, mas o fato é...";
			link.l1 = "Você não é mais minha irmã. Xing morreu há dez anos. E hoje é o dia em que Chung Tu finalmente morre. De agora em diante, e para sempre, meu nome é... Longway.";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_FlagMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Primeiro, resgatamos Chang Xing.";
			link.l1 = "O quê?! Você não está entendendo, meu amigo. Sua irmã não corre perigo imediato, mas "+sStr+" é. E preciso lembrar que Chang Xing tem tanta culpa nisso quanto Martene e Thibaut?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Isso não é verdade! Ela está...";
			link.l1 = "Você faz ideia do que Levasseur pode estar fazendo com "+sStr+" enquanto estamos aqui discutindo?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_3";
		break;
		
		case "PZ_Longway_FlagMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Mas Chang Xing é tudo o que me resta, Capitão... Sua família ainda está inteira...";
			link.l1 = +sStr+" pode não ser minha esposa, mas é tão querida para mim quanto minha própria família.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_4";
		break;
		
		case "PZ_Longway_FlagMartinInfo_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing é minha última estrela-guia, Meu Senhor Capitão. Além disso, você me deve por ter arrancado aquela confissão do Robert Marten.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "Vamos atrás da sua irmã, eu prometo. Mas Levasseur não encostou nela esse tempo todo. "+sStr+" está em perigo muito maior do que Chang Xing. Me ajude a salvá-la primeiro, e vou ficar te devendo uma grande.";
				link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
				{
					if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
					{
						link.l1 = "(Confiável) (Liderança) Vamos atrás da sua irmã, eu prometo. Mas Levasseur não encostou nela esse tempo todo. "+sStr+" está em perigo muito maior do que Chang Xing. Ajude-me a salvá-la primeiro, e vou ficar te devendo uma enorme.";
						link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
						Notification_Perk(true, "Trustworthy");
						notification("Skill Check Passed", SKILL_LEADERSHIP);
					}
					else
					{
						link.l1 = "Me escute! Sua irmã está a salvo. Mas "+sStr+" está agora nas mãos de um pervertido, que pode estar torturando ela neste exato momento – ou coisa pior! Você acha mesmo que Levasseur deixaria sua irmã comandar um lugar tão refinado se a tratasse como as outras pobres garotas no calabouço dele?!";
						link.l1.go = "PZ_Longway_FlagMartinInfo_netVD1";
						if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
						if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
					}
				}
			}
			link.l2 = "Não vou perder tempo com discussões inúteis. Cada um de nós tem suas próprias prioridades. Vamos nos separar de novo. Que o meu Deus me ajude, e o seu ajude você.";
			link.l2.go = "PZ_Longway_FlagMartinInfo_Razdelimsya";
			link.l3 = "Você tem razão. Te devo essa. Tudo bem, vai do seu jeito. Além disso, sem você, talvez eu não consiga lidar com Levasseur e os homens dele. Mas se algo acontecer com "+sStr+" enquanto lidamos com sua irmã... ";
			link.l3.go = "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya";
		break;
		
		case "PZ_Longway_FlagMartinInfo_Razdelimsya":
			dialog.text = "Obrigado por compreender, Meu Senhor Capitão. Boa sorte para você!";
			link.l1 = "E para você, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya":
			dialog.text = "Ameaças vazias não assustam ninguém, Meu Senhor Capitão. Precisamos nos apressar, para chegarmos a tempo de tudo.";
			link.l1 = "Espero que o seu Deus ouça isso. Vamos!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_Longway_FlagMartinInfo_netVD1":
			dialog.text = "Vou relevar isso por respeito, Senhor Capitão. Só desta vez. Da próxima, eu vou te acertar. Agora vou atrás da minha irmã, com ou sem sua aprovação.";
			link.l1 = "Não vou perder mais tempo discutindo com você, Longway. No fim das contas, todos nós temos algo que valorizamos acima de tudo.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie":
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD1":
			dialog.text = "Uhum, tá bom, Senhor Capitão. Mas então precisamos nos apressar.";
			link.l1 = "Certo. Obrigado, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_VD2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD2":
			pchar.questTemp.PZ_LongwayRyadom = true;
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_TortureRoom_Levasser_1":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Ora, ora, quem diabos temos aqui... Merda. Charles de Maure e o vira-lata de olhos puxados dele.";
				link.l1 = "Só tem um vira-lata aqui. Se quiser ver, olha no espelho, seu bastardo huguenote. Ou então dá uma olhada no seu sobrinho. Embora, ele parece mais um rato sarnento.";
				link.l1.go = "PZ_TortureRoom_Levasser_2";
			}
			else
			{
				dialog.text = "Eu disse para não me incomodar! Ah, Charles de Maure, hehehe. Que inseto insistente você é.";
				link.l1 = "Eu sou assim mesmo. Agora cala essa boca e...";
				link.l1.go = "PZ_TortureRoom_Levasser_1_1";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne") || CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo") || CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal")) Achievment_Set("ach_CL_130");
			}
			locCameraSleep(true);
			sld = CharacterFromID("Tibo");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_1_1":
			dialog.text = "Você não está no seu próprio navio, filhote! Só tem um homem nesta ilha, e esse sou eu!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
		break;
		
		case "PZ_TortureRoom_Levasser_2":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_3":
			dialog.text = "Como você ousa, seu verme!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_4";
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_4":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_5":
			dialog.text = "Calma, sobrinho! Monsieur de Maure está prestes a aprender boas maneiras.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_6":
			if (!CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Eu te dei permissão pra chiar?!";
			}
			else
			{
				dialog.text = "Onde foi parar todo aquele fogo, hein, coisa bonita? Ah, acho que entendi...";
			}
			link.l1 = "Deixe ela em paz, seu desgraçado!";
			link.l1.go = "PZ_TortureRoom_Levasser_7";
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Mary"));
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Helena"));
		break;
		
		case "PZ_TortureRoom_Levasser_7":
			dialog.text = "Heh-heh-heh... Pode gritar e me xingar o quanto quiser, mas eu vejo você tremendo como uma folha ao vento. Vejo o medo nos seus olhos. Você e Henri têm isso em comum. Sem ofensa, sobrinho.";
			link.l1 = "Você está certo, é medo. Mas não de você, verme.";
			link.l1.go = "PZ_TortureRoom_Levasser_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_7_1":
			dialog.text = "Claro, claro. Já ouvi tudo isso antes – que você não teme ninguém, de Maure. Ela me disse isso. 'A-ah, Charles vai vir, Charles vai me salvar... Charles isso, Charles aquilo...' Pois bem, Charles está aqui. Charles tem um lugar na primeira fila. Henri, faça nosso convidado se sentir à vontade.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_8";
		break;
		
		case "PZ_TortureRoom_Levasser_8":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_9", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_9":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Não precisa disso, tio. Acho que desta vez você passou um pouco dos limites...";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Tio, vou precisar da sua ajuda com essa...";
				}
				else
				{
					dialog.text = "Devo acabar logo com ele, tio, ou deixo ele assistir primeiro?";
				}
			}
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_10";
			LAi_SetActorType(npchar);
			//LAi_ActorTurnToCharacter(npchar, CharacterFromID("Levasser"));
			LAi_ActorTurnToLocator(npchar, "goto", "goto8");
			locCameraFromToPos(-15.67, 2.57, -1.23, true, -17.49, 1.42, -3.26);
		break;
		
		case "PZ_TortureRoom_Levasser_10":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_11", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_11":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Não fui eu, foi o Monsieur Cavaleiro Branco aqui que demorou demais pra vir ao resgate. Parece que o espetáculo acabou, ha-ha-ha-ha!";
				link.l1 = "Deus, não...";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Eu imaginei. Como conseguiu sobreviver até essa idade? Aliás, mesma pergunta pra você, de Maure.";
					link.l1 = "Você não faz ideia de quantas perguntas eu tenho pra você, açougueiro!";
				}
				else
				{
					dialog.text = "Eu queria que a nossa pequena apresentação tivesse uma plateia... Mas acho que o Monsieur Teimoso aqui não vai nos dar esse prazer.";
					link.l1 = "O único prazer aqui vai ser meu - te abrir no meio, açougueiro!";
				}
				link.l1.go = "PZ_TortureRoom_Levasser_14";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				locCameraFromToPos(-16.74, 2.58, -0.51, true, -13.13, -0.72, 2.49);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
			{
				locCameraFromToPos(-18.38, 1.77, 2.73, true, -20.53, 0.01, 0.32);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
			{
				locCameraFromToPos(-16.97, 2.09, 3.98, true, -20.02, -0.17, 2.28);
			}
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_12":
			dialog.text = "Vai lá, pega ela! Ha-ha-ha!";
			link.l1 = "Malditos animais, vou fazer vocês se arrependerem de terem nascido!";
			link.l1.go = "PZ_TortureRoom_Levasser_13";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_13":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				ReturnOfficer_Longway();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PZ_TortureRoom_Levasser_DevushkaMertva5");
		break;
		
		case "PZ_TortureRoom_Levasser_14":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Açougueiro? Eu me vejo mais como um artista, um pintor – será que você ao menos tentaria enxergar isso como arte... Observe.\nGosta do meu trabalho? É realmente uma das minhas obras-primas. Para ser totalmente honesto, prefiro as loiras, mas ela... No fim, perdoei esse cabelo feio. Não era só o cabelo – a garota era puro fogo! Quase me queimei. Lutou, mordeu, rosnou como um animal selvagem! Me lembrou uma selvagem de pele vermelha, com quem me diverti bastante, mesmo que por pouco tempo...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Açougueiro? Eu me vejo mais como um artista, um pintor – será que você ao menos tentaria enxergar isso como arte... Observe.\nVeja, ainda não terminei com ela – ainda há muito espaço vazio nesta tela. Além de bela, ela é dura como pedra e fria como gelo. Precisei até suar um pouco para fazê-la gritar. Ela aguentou até o fim, só para não me dar o prazer de ouvir sua linda voz.";
			}
			link.l1 = "Solte ela agora, seu degenerado.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya13");
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_15":
			dialog.text = "Onde você pensa que vai? Esse pedaço de carne agora é minha propriedade. Assim como tudo ao redor — esta cidade, esta fortaleza... Eu sou Tortuga. E você e Poincy, aquele velho peru fedorento, nunca vão mudar isso.";
			link.l1 = "Levasseur, você...";
			link.l1.go = "PZ_TortureRoom_Levasser_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_16":
			dialog.text = "É o Signor de René de Buaduflé de Lettre para você.";
			link.l1 = "Não dou a mínima. Saque sua espada e me mostre do que é capaz numa luta – com um homem, não com uma garota indefesa.";
			link.l1.go = "PZ_TortureRoom_Levasser_17";
		break;
		
		case "PZ_TortureRoom_Levasser_17":
			dialog.text = "E que homem você é! Mas tem razão, eu mesmo já cansei dessa conversa toda. Quero voltar para... minha dama. Mas vou te fazer uma última pergunta. Como você chegou aqui? Quem revelou onde fica este lugar? Só um punhado de pessoas sabe disso.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "Seu amigo em comum, Martene, cantou como um rouxinol. Na verdade, gritou mais como um porco no matadouro mesmo...";
				link.l1.go = "PZ_TortureRoom_Levasser_FlagMartinInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo"))
			{
				link.l2 = "Talvez seja melhor manter isso em segredo de você. Tenho receio que possa ferir seu ego, Signor de René... alguma coisa.";
				link.l2.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l3 = "Uma das suas vítimas, Levasseur.";
				link.l3.go = "PZ_TortureRoom_Levasser_FlagShinInfo_1";
			}
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_1":
			dialog.text = "Mentiroso, seu canalha! Ninguém sai destas paredes!";
			link.l1 = "Use sua memória, vamos lá. Tinha um. Chang Xing.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagShinInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_2":
			dialog.text = "De jeito nenhum. Não ela. Algumas das minhas ideias nasceram por causa daquela diabinha. Ah, a gente aprendeu muita coisa um com o outro, hehe. Resolveu limpar a consciência no fim das contas? Duvido muito. Afinal, eu já arranquei tudo isso dela faz tempo!";
			link.l1 = "Agora vou te esgotar até o último pingo. Uma gota de cada vez.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMartinInfo_1":
			dialog.text = "E você me chama de carniceiro, seu hipócrita miserável! Heh-heh... Mas enquanto ele estiver queimando no Inferno, não tenho nada a temer.";
			link.l1 = "Ele está esperando por você lá. E o seu sobrinho canalha também. Vamos não decepcioná-lo.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1":
			dialog.text = "Que tal eu machucar mais um pouco esse brinquedinho? Cortar a barriga ou a garganta dela, e ver ela sangrar até a morte enquanto você tenta chegar até ela...";
			link.l1 = "Tanto faz, Levasseur, tanto faz... Sua esposa manda lembranças. E junto delas, uma última saudação.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2":
			dialog.text = "O QUÊ?! Kha-kha... Maldita Marceline... Sua desgraçada, vadia, vadia, vadia!";
			link.l1 = "Isso ela é. Vocês se merecem. Mas ela tem a cabeça um pouco mais no lugar. Pelo menos à primeira vista.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3":
			dialog.text = "Eu vou colocar a cabeça de galinha dela numa estaca. Mas antes disso... ah, muita, muita coisa vai acontecer com essa vadia.... Vou até dar um descanso pro meu novo brinquedo. Espera! Tive uma ideia melhor. Vou emprestar ela pro Henri. Só por um tempo, claro.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5":
			dialog.text = "Sério? Obrigada, tio!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6";
			CharacterTurnByChr(npchar, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7":
			dialog.text = "Mereça primeiro - me dá uma força com essa aqui, hein?";
			link.l1 = "Ele está prestes a perder o controle.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
			CharacterTurnByChr(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_Bitva":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				ReturnOfficer_Longway();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
			LAi_SetImmortal(sld, true);
			
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_Etap6TortugaPytochnaya19");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		
		case "PZ_TortureRoom_Longway_1":
			dialog.text = "Senhor Capitão... Longway oferece suas condolências. Fizemos tudo o que podíamos.";
			link.l1 = "Nem tudo, nem de longe o suficiente.";
			link.l1.go = "PZ_TortureRoom_Longway_2";
		break;
		
		case "PZ_TortureRoom_Longway_2":
			dialog.text = "Longway vai procurar Chang Xing. Você vem comigo?";
			link.l1 = "Sim, eu vou com você, Longway. Mas lembre-se – sua irmã também teve um papel muito ativo nesse espetáculo sangrento. Ela vai ter que se esforçar muito para me convencer a poupá-la. E você não vai ajudá-la. Agora vamos, está na hora de acabar com isso.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Longway_3":
			DialogExit();
			ReturnOfficer_Longway();
			chrDisableReloadToLocation = false;
		break;
		
		case "PZ_TortureRoom_Devushka_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Charles, eu sabia, né? Eu sabia que você viria! Você sempre vem, não é?";
					link.l1 = "Eu não gostaria de testar isso uma quarta vez, Mary... Aqueles canalhas, eles...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Oh, meu capitão, você não faz ideia de como chegou na hora certa. Aqueles... aqueles monstros...";
					link.l1 = "Acabou agora, Helen. Está tudo bem, acabou. Meu Deus, o que fizeram com você...";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Charles, você está aqui! Eu sabia, eu sabia, né!";
					link.l1 = "Eu estava fugindo a todo pano, correndo pela minha vida, Mary. Você... eles fizeram algo?.. ";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Meu capitão... Você está aqui... Eu quase tinha perdido a esperança...";
					link.l1 = "Vim o mais rápido que pude, Helen. Desculpe ter demorado tanto.";
				}
				locCameraFromToPos(-15.32, 1.24, 1.31, true, -14.25, -1.00, -1.50);
			}
			link.l1.go = "PZ_TortureRoom_Devushka_2";
		break;
		
		case "PZ_TortureRoom_Devushka_2":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Não, Charles, não. Eles tentaram, mas eu lutei com todas as minhas forças. Por isso me espancaram tanto... Por favor, Charles, vamos sair daqui... tá bom?";
					link.l1 = "Já vou, meu caro. Só falta uma última coisa.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Eles não fizeram isso, Charles! Não fizeram. O resto vai sarar. Por favor, me tira daqui.";
					link.l1 = "É claro, meu querido. Só falta uma coisa para fazermos aqui.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Não, Charles, não. Eles tentaram, mas você chegou bem na hora. Como daquela vez. Quantas vezes já foi assim?";
					link.l1 = "Eu não contei, Mary. E nunca vou contar.";
					link.l1.go = "PZ_TortureRoom_Devushka_2_1";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Você chegou... bem na hora. O pior não aconteceu. Agora, por favor, vamos sair daqui. Para qualquer lugar.";
					link.l1 = "Levante-se, Helen. Suba. Tenho que lidar com esse canalha primeiro.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
		break;
		
		case "PZ_TortureRoom_Devushka_2_1":
			dialog.text = "E eu não vou parar de contar. Agora vamos sair daqui, por favor.";
			link.l1 = "Claro, meu querido. Não há mais nada para fazermos aqui. Exceto uma coisa.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Devushka_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) AddPassenger(pchar, npchar, false);
			LAi_SetPlayerType(pchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
		break;
		
		case "PZ_TortureRoom_Levasser_18":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "E então, kha-kha, você não tem coragem, bundão? Pede pro seu porco covarde te ajudar...  Ou faz você mesmo, aí vai ter motivo pra contar pro Poincy o quanto você é valente.";
				link.l1 = "Eu prefiro contar pra todo mundo que você era um covarde de merda.";
			}
			else
			{
				dialog.text = "O quê, você quer mesmo me ver sangrar até morrer? Tá gostando disso, né? Vai contar pra sua mulher que é um herói. Tá vendo aquele esqueleto ali na parede? Era a esposa do banqueiro de Santiago... O marido dela também achava que era herói, mas só serviu pra gritar bem alto – quando eu botei ele naquela roda...";
				link.l1 = "Eu poderia rolar sua carcaça nisso, canalha, mas receio que não aguentaria o peso da sua bunda.";
			}
			link.l1.go = "PZ_TortureRoom_Levasser_19";
		break;
		
		case "PZ_TortureRoom_Levasser_19":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Covarde? Oh, kha-kha, vamos lá...";
				link.l1 = "Crueldade não é o oposto de covardia. Mas alguém como você não saberia a diferença.";
				link.l1.go = "PZ_TortureRoom_Levasser_20";
			}
			else
			{
				dialog.text = "Isso é muito esperto. Lembre-se do que eu digo, de Maure: você vai morrer igual aquele figurão, rouco de tanto gritar e surdo pelos gritos dos seus...";
				link.l1 = "Queime no Inferno, verme.";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
			}
		break;
		
		case "PZ_TortureRoom_Levasser_20":
			dialog.text = "Olha, não sou nenhum filósofo, admito. Tá vendo aquele esqueleto na parede, de Maure? É tudo que sobrou da esposa do banqueiro de Santiago. Ele também gostava de falar bonito, mas tudo isso acabou quando comecei a enrolar o corpo dele naquela roda. O que restou foram só os gritos, que quase me deixaram surdo...";
			link.l1 = "Vamos acabar logo com isso.";
			link.l1.go = "PZ_TortureRoom_Levasser_21";
		break;
		
		case "PZ_TortureRoom_Levasser_21":
			StartInstantDialog("Longway", "PZ_TortureRoom_Levasser_22", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_22":
			dialog.text = "Espere um pouco, Senhor Capitão... Não tenha tanta pressa.";
			link.l1 = "O que foi, Longway?";
			link.l1.go = "PZ_TortureRoom_Levasser_23";
		break;
		
		case "PZ_TortureRoom_Levasser_23":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Não o mate. Simples demais. Ele merece coisa pior.";
			link.l1 = "Você está furioso por causa da sua irmã, meu amigo. E eu estou indignado com o que ele fez com "+sStr+"... e o que ele poderia ter feito com ela. Mas eu não sou um animal como ele. Eu poderia queimar ele com as brasas daquele braseiro, quebrar os ossos dele naquela roda... Eu poderia acorrentá-lo e deixar ele morrer de hemorragia. Mas não posso arriscar que algum capanga dele venha salvá-lo. Não posso correr esse risco.";
			link.l1.go = "PZ_TortureRoom_Levasser_24";
		break;
		
		case "PZ_TortureRoom_Levasser_24":
			dialog.text = "Espere, Meu Senhor Capitão. Não foi isso que eu quis dizer. Estou falando do Poincy.";
			link.l1 = "E sobre ele?";
			link.l1.go = "PZ_TortureRoom_Levasser_25";
		break;
		
		case "PZ_TortureRoom_Levasser_25":
			dialog.text = "Pense em como ele te recompensaria se você levasse esse animal vivo pra ele. Ele te cobriria de dobrões. E aquele verme prefere morrer aqui do que apodrecer numa masmorra em Capsterville.";
			link.l1 = "Talvez você tenha razão, Longway. Mas eu não sei exatamente o que aconteceu entre esse canalha e o Chevalier. Acredite, eu conheço esse tipo de gente melhor do que você. Se for só por dinheiro, como dizem, esses dois podem chegar a um acordo. Poincy pode deixá-lo ir, e outro lugar como este pode aparecer em alguma outra ilha ou em uma das cidades do Velho Mundo.";
			link.l1.go = "PZ_TortureRoom_Levasser_26";
			link.l2 = "Não é uma má ideia, Longway. Mas duvido que o Chevalier vá ser tão generoso assim... Não faz parte da natureza dele, de verdade. Mas pra mim, não é pelo dinheiro mesmo. Levantem ele! E cuidem dos ferimentos dele pra que não morra antes da hora.";
			link.l2.go = "PZ_TortureRoom_Levasser_28";
		break;
		
		case "PZ_TortureRoom_Levasser_26":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_27", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_27":
			dialog.text = "Mas primeiro, eu vou atrás de você. E do seu companheiro. Não vou encostar em você, homem de olhos apertados — você não vale o meu tempo.";
			link.l1 = "Está vendo, Longway? Tudo isso tem que acabar agora. Aqui e agora.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
		break;
		
		case "PZ_TortureRoom_Levasser_28":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_29", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_29":
			dialog.text = "Espere um pouco, Capitão, espere um pouco, kha-kha.";
			link.l1 = "O que foi, Monsieur ex-governador?";
			link.l1.go = "PZ_TortureRoom_Levasser_30";
		break;
		
		case "PZ_TortureRoom_Levasser_30":
			dialog.text = "A minha chave está em algum lugar deste quarto. Ela abre um baú no meu escritório. Lá tem duzentos mil em prata e uma bela lâmina. Se isso não for suficiente, no quarto da minha esposa, na cômoda, tem uma coleção de pedras preciosas caras.";
			link.l1 = "Hmm, e o que você quer em troca?";
			link.l1.go = "PZ_TortureRoom_Levasser_31";
		break;
		
		case "PZ_TortureRoom_Levasser_31":
			dialog.text = "Uma bala. Acabe logo comigo. Aqui e agora.";
			link.l1 = "E quanto ao Chevalier de Poincy? Ouvi dizer que são velhos amigos... Não quer vê-lo?";
			link.l1.go = "PZ_TortureRoom_Levasser_32";
		break;
		
		case "PZ_TortureRoom_Levasser_32":
			dialog.text = "Que Poincy vá para o inferno! Então, você concorda ou não?";
			link.l1 = "Na verdade, não, Monsieur de... Eu não quero dizer seu nome completo.";
			link.l1.go = "PZ_TortureRoom_Levasser_33";
		break;
		
		case "PZ_TortureRoom_Levasser_33":
			dialog.text = "Isso não basta pra você? Tudo bem, tem mais...";
			link.l1 = "Os gritos das suas vítimas devem ter te deixado surdo, Levasseur. Eu te disse, não é pelo dinheiro. Você teme o Poincy por algum motivo, não é? Nem quero saber o que ele vai fazer com você. Mas se isso servir como um pouco de justiça pela sua... arte, que assim seja.";
			link.l1.go = "PZ_TortureRoom_Levasser_34";
			pchar.questTemp.PZ_LevasserPlenen = true;
			pchar.questTemp.PZ_LevasserPobezhden = true;
		break;
		
		case "PZ_TortureRoom_Levasser_34":
			dialog.text = "Então é isso que você realmente é, kha-kha... Não é melhor do que eu.";
			link.l1 = "Chega. Longway - levante ele!";
			link.l1.go = "PZ_TortureRoom_Levasser_35";
		break;
		
		case "PZ_TortureRoom_Levasser_35":
			DialogExit();
			
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1 = "locator";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.location = "Tortuga_Torture_room";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator_group = "reload";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator = "reload1";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition = "PZ_TortureRoom_Levasser_ObratnoNaBereg";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) ReturnOfficer_Longway();
			sld = CharacterFromID("Levasser");
			sld.location = "None";
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "Nosso navio... Nunca pensei que ficaria tão feliz em vê-lo... certo. Finalmente, esse pesadelo acabou.";
				}
				else
				{
					dialog.text = "Finalmente acabou. E agora, Charles?";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "Eu não acredito que acabou tudo... O que fazemos agora, meu capitão?";
				}
				else
				{
					dialog.text = "Bem, é isso, meu Capitão. O que fazemos agora?";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l1 = "Infelizmente, ainda não acabou. Chang Xing... Essa história só termina de verdade quando eu conseguir minhas respostas dela.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Rume para Capsterville. Está na hora do Monsieur Levasseur virar história.";
				}
				else
				{
					link.l1 = "A missão do Chevalier está cumprida. Preciso informar a ele. Vou omitir alguns detalhes, porém. Só espero que ele cumpra a palavra e Michel seja libertado...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Eu também, né. Então eu vou com você. E nem tente discutir comigo, Charles.";
				link.l1 = "Mary, querida, você precisa descansar. Você está quase desmaiando...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Eu vou com você.";
				link.l1 = "Helen, você quase morreu nas mãos daquele demônio. Mal consegue ficar de pé...";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Eu preciso de você, Charles. E você precisa de mim. E se alguém for desmaiar esta noite, vai ser a Chang Xing. No chão do bordel dela, com uma bala entre os olhos!";
				link.l1 = "É, Levasseur não conseguiu arrancar seu espírito de luta. Eu até mandaria você de volta pro navio, mas sei que você me seguiria de qualquer jeito...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mas ainda posso empunhar uma lâmina. Charles, eu preciso estar lá. Preciso entender o que a levou a fazer isso. Você entende por que isso é tão importante para mim?";
				link.l1 = "Eu entendo que você precisa descansar e se recuperar. E vai precisar de bastante tempo para isso.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Você me conhece bem demais, Charles, né. Então vamos deixar a conversa de lado e acabar logo com isso.";
				link.l1 = "Como quiser. Mas fique atento. Ninguém sabe que surpresas nos aguardam lá fora.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Pode esperar. Você veio por mim, e agora eu vou com você. Quer você queira ou não.";
				link.l1 = "Vejo que você ainda tem coragem, Helen. Ótimo. Fique atrás de mim e, pelo amor de Deus, tome cuidado.";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SDevushkoyKShin");
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_1":
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Nosso navio... Não acredito que vou embarcar nela de novo, né...";
					link.l1 = "Ela está esperando por você, Mary. Uma boa refeição e uma cama macia também...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ugh... Eu não achei que conseguiria chegar até o barco com as minhas próprias pernas.";
					link.l1 = "Você é a pessoa mais forte que já conheci, Helen. Agora entra e vai direto pra cama...";
				}
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Nosso navio... Não acredito que vou embarcar nela de novo, né...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ugh... Eu não achei que conseguiria chegar ao barco com as minhas próprias pernas.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Rume para Capsterville. Está na hora do Monsieur Levasseur virar parte da história.";
				}
				else
				{
					link.l1 = "A missão do Cavalheiro está concluída. Preciso informar a ele. Mas vou omitir alguns detalhes. Só espero que ele cumpra a palavra e Michel seja libertado...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "E você, Charles... Por que essa cara? Está aprontando de novo, não está?";
				link.l1 = "Chang Xing. Eu preciso chegar até ela também.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "E você? Para onde está indo?";
				link.l1 = "Para ver Chang Xing. Ela é o último capítulo deste pesadelo.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Então eu vou com você! Ela me deve uma enorme, né?";
				link.l1 = "Mary, querida, você mal conseguiu chegar até o barco. E agora não consegue nem segurar uma lâmina. Eu juro por Deus que vou fazer ela pagar pelo que fez com você. Mas vou me sentir muito melhor se você ficar no navio, sabendo que está segura.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Meu capitão, eu queria tanto ir com você... Por favor, tome cuidado. Quem sabe do que mais ela é capaz? Ela me segurou enquanto aquele cachorro do Thibaut...";
				link.l1 = "O pior já passou, Helen. Logo tudo isso vai acabar, eu prometo.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Bem, pelo menos o Longway vai cuidar de você na minha ausência. Mas se acontecer alguma coisa com você, eu mesma enterro ele e o Chang Xing!";
					link.l1 = "Vai ficar tudo bem. Agora vá descansar. Eu volto antes que você perceba.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "Onde Longway foi, Charles?";
					link.l1 = "Ele foi atrás do Chang Xing sem mim. Eu não consegui impedir, mas o que eu podia fazer?";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Bem, pelo menos o Longway vai com você. Isso já é algum consolo, pelo menos.";
					link.l1 = "Viu? Não precisa se preocupar. Não vou demorar.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "Onde está o Longway? Acabei de perceber que ele não está aqui.";
					link.l1 = "Ele foi até a irmã dele sem mim. Não o culpo. Ele esperou tempo demais por esse momento.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
					
				}
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, estou com um mau pressentimento sobre isso...";
				link.l1 = "Eu sei. Esse pesadelo já dura tempo demais, e o fim está próximo. O pior já passou.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Quem sabe o que se passa na cabeça dele, Charles? Fique de olho aberto, né?";
				link.l1 = "Eu vou sim. Volto logo, Helen."link.l1.go ="PZ_Etap6_NaBeregu_DevaBolnaya_7";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_6":
			dialog.text = "Prometa que você estará pronto para qualquer coisa.";
			link.l1 = "Eu sou, e continuarei sendo. Eu volto logo, Mary.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_7":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) StartInstantDialog("Longway", "PZ_Etap6_NaBeregu_DevaBolnaya_8", "Quest\CompanionQuests\Longway.c");
			else
			{
				DialogExit();
				LAi_SetPlayerType(pchar);
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
				AddQuestRecord("PZ", "51");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", "Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", "Helen");
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1 = "location";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1.location = "Tortuga_brothelElite";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition = "PZ_Etap6_BrothelPoiskSestry";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_8":
			dialog.text = "Longway ajudou você, Capitão. Agora é sua vez de cumprir a palavra.";
			link.l1 = "Você ouviu tudo, Longway. Vamos ver sua irmã.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_9";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_9":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Senhor Capitão, Longway tem um último pedido: deixe Chang Xing se explicar. Ouça o que ela tem a dizer antes de tomar qualquer decisão.";
			link.l1 = "O que aconteceu com "+sStr+" está com ela. Mas vou dar a ela uma chance de se explicar primeiro.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_10";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_10":
			dialog.text = "Longway confia na sua palavra, no seu julgamento e na sua bondade.";
			link.l1 = "Meu camarada, não há espaço para razão ou gentileza nessa confusão sangrenta. E já passou da hora de acabar com isso.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SLongwayKShin");
		break;
		
		case "PZ_LongwayPrishelOdin":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "Meu Senhor Capitão...";
				link.l1 = +sStr+" está morto.";
				link.l1.go = "PZ_LongwayPrishelOdin2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Capitão, senhora "+sStr+", é um prazer vê-lo. Este é... Chang Xing.";
					link.l1 = "Eu já imaginei, Longway. Fique para trás. Você já teve tempo de sobra para falar com sua irmã. Agora ela precisa responder para "+sStr+" por ajudar os capangas do Levasseur a sequestrá-la.";
					link.l1.go = "PZ_LongwayPrishelOdin7";
				}
				else
				{
					dialog.text = "Você veio... Onde está a senhora "+sStr+"? Ela está...?";
					link.l1 = "Não, Longway. Graças a Deus, não. Eu a levei para o navio. Caso contrário, eu nem estaria tendo esta conversa agora. Mas ainda assim, não vai ser fácil nem agradável.";
					link.l1.go = "PZ_LongwayPrishelOdin12";
				}
			}
		break;
		
		case "PZ_LongwayPrishelOdin2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing e eu oferecemos nossas condolências...";
			link.l1 = "Condolências de Chang Xing?! Você bem que podia oferecer condolências em nome do Levasseur também, Longway! Você sabe muito bem que ela participou do sequestro da "+sStr+" junto com os outros capangas dele! E agora ela se foi...!";
			link.l1.go = "PZ_LongwayPrishelOdin3";
		break;
		
		case "PZ_LongwayPrishelOdin3":
			dialog.text = "Eu... Eu entendo o que você está sentindo agora, Meu Senhor Capitão.";
			link.l1 = "Ah, é mesmo?";
			link.l1.go = "PZ_LongwayPrishelOdin4";
		break;
		
		case "PZ_LongwayPrishelOdin4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Eu perdi meus pais, como você deve lembrar. Se é que lembra. Além disso, não foi o Chang Xing quem torturou e matou "+sStr+". Eu entendo sua dor, sua raiva. Mas a culpa da minha irmã não é tão grande quanto a sua para ser levada em conta. Por favor, me escute.";
			link.l1 = "Eu me lembro. Vou ouvir sua história. Mas seja rápido! E saiba que não posso deixar algo assim sem punição!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin5":
			dialog.text = "Então é melhor eu contar tudo de novo, Monsieur de Maure. O francês do nosso Tu é tão ruim que você quase partiu pra cima dele.";
			link.l1 = "Você devia ter ficado de boca fechada. Eu não ia atacar o Longway, mas você... Você é o responsável pela morte dela.";
			link.l1.go = "PZ_LongwayPrishelOdin6";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin6":
			dialog.text = "Eu até discutiria com isso, mas percebo que prefiro não fazê-lo. Tu falaste de você como uma pessoa de respeito e compreensão. Mas será mesmo verdade? Faz sentido eu sequer começar a falar? Ou já tomou sua decisão?";
			link.l1 = "Você sabe como entrar na cabeça de alguém, mademoiselle. Agora realmente não vale a pena discutir. Mas se quiser tentar se justificar... Bem, vá em frente. Por Longway, vou te ouvir.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ela pode explicar tudo, Meu Senhor Capitão... Não é o que você pensa... Não de verdade...";
			link.l1 = "Então explique. Mas não para mim. "+sStr+". Olhe nos olhos dela. Veja os hematomas e feridas. E diga a ela que não foi assim.";
			link.l1.go = "PZ_LongwayPrishelOdin8";
		break;
		
		case "PZ_LongwayPrishelOdin8":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Peço desculpas em nome de Xing, Capitão...";
			link.l1 = "Pelo sorriso debochado dela, você está perdendo seu tempo. Ela não merece seu pedido de desculpas.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin9":
			dialog.text = "Está sendo duro demais com ele, Monsieur de Maure. Mas talvez já esteja acostumado a tratá-lo assim – como um trabalhador de pele amarela qualquer.";
			link.l1 = "Está tentando virar o Longway contra mim? Não vai funcionar. Sempre tratei ele com respeito, e ele sabe disso. É isso que importa. Eu entendo que agora só te resta brincar de joguinhos.";
			link.l1.go = "PZ_LongwayPrishelOdin10";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin10":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "O que você quer fazer? Levar o pobre Tu para longe da família dele? Agora que ele finalmente os encontrou de novo depois de dez anos?";
			link.l1 = "Sangue nem sempre faz uma família. Mas o que você sugere que façamos? Deixar o que você fez para "+sStr+" sair impune? E deixar o Longway visitar de vez em quando uma mulher que negocia outras garotas sem nem pensar duas vezes?";
			link.l1.go = "PZ_LongwayPrishelOdin11";
		break;
		
		case "PZ_LongwayPrishelOdin11":
			dialog.text = "Bom, pra começar, escute. Ao contrário dele, eu posso repetir o que acabei de contar pra ele em francês perfeito. Minha história. Olhando direto nos seus olhos, ou até nos dela. E tudo isso sem o sotaque do qual você provavelmente já está de saco cheio. Afinal, o que todos nós temos a perder?";
			link.l1 = "I'm used to Longway's accent; it's part of who he is to me. I'll listen to you, but only for the sake of my friend. Go on.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Por que não, Meu Senhor Capitão...?";
			link.l1 = "Você realmente precisa perguntar? Ela estava envolvida no sequestro de "+sStr+", não era?";
			link.l1.go = "PZ_LongwayPrishelOdin13";
		break;
		
		case "PZ_LongwayPrishelOdin13":
			dialog.text = "Eu... peço desculpas de verdade. Também é culpa minha, por não ter conseguido salvar minha irmã há dez anos, por não ter conseguido protegê-la de tudo isso.";
			link.l1 = "Você não deveria pedir desculpas por quem não sente o menor remorso, Longway. Terminou aqui? Agora é minha vez de falar com ela.";
			link.l1.go = "PZ_LongwayPrishelOdin14";
		break;
		
		case "PZ_LongwayPrishelOdin14":
			dialog.text = "Senhor Capitão, espere! Chang Xing não é como Levasseur. Não completamente. Ela vai me contar sobre a vida dela nesses dez anos. Deixe-me contar para você também.";
			link.l1 = "Certo, Longway. Estou ouvindo. Muita coisa depende do que você vai me contar.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin15":
			dialog.text = "Se for você contando, todos nós vamos acabar com dor de cabeça. Permita-me, Tu. Charles de Maure, presumo?";
			link.l1 = "Certo. E você é Belle Etoile, também conhecida como Chang Xing. Você participou do sequestro do meu amor, junto com Thibaut e Martene. E ainda sorri quando menciono isso. Boas lembranças?";
			link.l1.go = "PZ_LongwayPrishelOdin16";
		break;
		
		case "PZ_LongwayPrishelOdin16":
			dialog.text = "É estupidez negar isso. Mas e agora? Vai me torturar na frente do meu irmão? Ou até pedir pra ele te ajudar a me torturar? Ou vai só me matar? Você faria mesmo isso com ele?";
			link.l1 = "Como eu disse, apesar de tudo que eu gostaria de fazer agora, ainda estou falando com você. Não force a barra. Diga o que você disse pra ele antes. E aí veremos pra onde isso vai nos levar.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_Longway_91":
			if (!CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Eu ainda não consigo acreditar que Chang Xing se tornaria... isso.";
				link.l1 = "As pessoas mudam, Longway. Qualquer um pode ser quebrado ou ter as últimas gotas de bondade e fé arrancadas de si.";
				link.l1.go = "PZ_Longway_ToGirl1";
			}
			else
			{
				dialog.text = "Longway ainda não consegue acreditar que minha irmã se tornou... isso. Por quê... por quê? Se ao menos eu tivesse estado em casa naquele dia...";
				link.l1 = "Não se torture com os 'e se'. Além disso, você não ficou parado todos esses anos – você se esforçou tanto pra consertar as coisas.";
				link.l1.go = "PZ_Longway_ToShore1";
			}
		break;
		
		case "PZ_Longway_ToGirl1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "É... Acho que é assim mesmo, Meu Senhor Capitão.";
			link.l1 = "Vamos sair daqui. Ainda precisamos limpar a bagunça que ela deixou para trás e salvar a "+sStr+" o mais rápido possível.";
			link.l1.go = "PZ_Longway_ToGirl2";
		break;
		
		case "PZ_Longway_ToGirl2":
			dialog.text = "Sim. Precisamos nos apressar - já demorou demais por minha causa.";
			link.l1 = "Não é sua culpa, Longway. Vamos depressa!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Longway_ToShore1":
			dialog.text = "Certo. Obrigado pelo seu apoio, Meu Senhor Capitão.";
			link.l1 = "Não precisa agradecer. Ela não merecia sua dedicação mesmo – não foi ela quem te procurou, mesmo quando podia. Sua estrela já se apagou faz tempo, e ela deixou de ser sua família há muito. Agora somos sua família, Longway.";
			link.l1.go = "PZ_Longway_ToShore2";
		break;
		
		case "PZ_Longway_ToShore2":
			dialog.text = "É... Então você é mesmo. E eu fui cego demais pra enxergar isso esse tempo todo.";
			link.l1 = "Antes tarde do que nunca. Agora vamos para casa – nosso navio está nos esperando.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Mary_91":
			dialog.text = "Tá certo. Você não faz ideia do quanto eu queria isso.";
			link.l1 = "Acredito que sim. Como você está se sentindo, Mary? O motivo pelo qual eu queria evitar derramamento de sangue era porque eu não tinha certeza se você conseguiria segurar sua lâmina com a mesma firmeza de sempre – um deles poderia ter levado vantagem enquanto eu estava ocupado com outro.";
			link.l1.go = "PZ_Mary_92";
		break;
		
		case "PZ_Mary_92":
			dialog.text = "Você me subestima. Além disso, a raiva é um remédio e tanto. Eu não tinha dúvida de que você viria correndo me salvar – como sempre faz, né. Sabe, Charles... Mesmo que você me chame de seu Talismã Vermelho, e se você for o meu também? Sempre acontece algo incrível quando estamos juntos.";
			link.l1 = "Sou seu talismã? Ora, gostei dessa ideia.";
			link.l1.go = "PZ_Mary_93";
		break;
		
		case "PZ_Mary_93":
			dialog.text = "Aí está, você já está sorrindo! Agora vamos sair desse lugar nojento – anda logo, depressa, né.";
			link.l1 = "Eh-heh, isso tudo me pegou de jeito. Queria que pudesse ter terminado de outro jeito.";
			link.l1.go = "PZ_Mary_94";
		break;
		
		case "PZ_Mary_94":
			dialog.text = "Eu não. Não havia como salvá-la, Charles. E ela arrastou o Longway com ela. Ele fez sua escolha, e não nos deixou alternativa. Pense em todas as pessoas que ajudamos hoje.";
			link.l1 = "Mais uma vez, não tenho nada para discordar de você, Mary. E desta vez, nem quero. Venha, meu Talismã Ruivo...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_ElitaShluha_Final1":
			if (CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva"))
			{
				dialog.text = "O que aconteceu lá, monsieur? Ouvimos xingamentos e gritos. Mas não tivemos coragem de pedir ajuda até tudo acabar.";
				link.l1 = "E com razão. Sua anfitriã está morta. Vocês estão livres para ir. Se eu fosse vocês, pegaria o dinheiro do bordel, dividiria entre si e fugiria da ilha o quanto antes. Sei que são mulheres honradas, não simples prostitutas, então terão um futuro além deste lugar miserável.";
				link.l1.go = "PZ_ElitaShluha_Final2";
			}
			else
			{
				dialog.text = "Ah, é você, monsieur. Sabe quando a anfitriã vai descer?";
				link.l1 = "Não tão cedo. E eu me afastaria da porta se fosse você. E nunca fale com ela sobre esta noite – ela não vai contar nada, e gatos curiosos perdem todas as suas vidas de uma vez. Parece que sua madame não gosta de ninguém se metendo nos segredos dela.";
				link.l1.go = "PZ_ElitaShluha_Final3";
			}
		break;
		
		case "PZ_ElitaShluha_Final2":
			dialog.text = "Você matou ela?!";
			link.l1 = "Eu fiz. E se você demorar ou tentar chamar os guardas, esse será seu maior erro. Ela nunca foi uma santa protetora para vocês – por mais seda e educação que tenha lhes dado, vocês estavam presas aqui, obrigadas a se entregar para qualquer canalha que ela apontasse. Desejo toda a sorte do mundo para conseguirem sair daqui. Adeus, senhoras.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_ElitaShluha_Final3":
			dialog.text = "Ela está mesmo bem? Podemos entrar? Precisamos chamar os guardas?";
			link.l1 = "Ela nunca vai ficar bem. Você pode tentar perguntar a ela mesma... por sua conta e risco. Ela ainda está conversando com o irmão. E não acho que eles vão gostar de ser incomodados.";
			link.l1.go = "PZ_ElitaShluha_Final4";
		break;
		
		case "PZ_ElitaShluha_Final4":
			dialog.text = "Entendo... Bem, volte para nos ver outra hora, monsieur.";
			link.l1 = "Jamais. Adeus, senhoritas.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_TortugaSoldier1":
			dialog.text = "Pare! Disseram que ouviram gritos e briga vindo da casa da senhorita Etoile. A guarda acredita que você está envolvido nisso. Entregue suas armas e venha conosco, monsieur.";
			if (!CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				link.l1 = "É verdade, mas não fomos nós que começamos a briga, nós é que terminamos. Os capangas contratados se revoltaram por causa de pagamentos atrasados e atacaram a Madame Etoile para roubá-la. Confiar em mercenários, né? Ganhamos a luta, mas infelizmente ela não sobreviveu.";
				link.l1.go = "PZ_TortugaSoldier2";
			}
			else
			{
				link.l1 = "Hoje perdi o amor da minha vida, então me deixe passar, oficial.";
				link.l1.go = "PZ_TortugaSoldierGirlDied1";
			}
		break;
		
		case "PZ_TortugaSoldier2":
			dialog.text = "Você entende que não podemos simplesmente acreditar na sua palavra, não é? Precisamos te deter. E você vai precisar de testemunhas entre as funcionárias. Vamos ver o que elas têm a dizer.";
			link.l1 = "A pessoa que amo está gravemente ferida. Eu também estou exausto. Não pode simplesmente nos deixar ir, por favor?";
			link.l1.go = "PZ_TortugaSoldier3";
		break;
		
		case "PZ_TortugaSoldier3":
			dialog.text = "Vamos tentar resolver isso o quanto antes. Agora, siga-nos.";
			link.l1 = "Vá para o inferno...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_TortugaSoldierGirlDied1":
			dialog.text = "Meus pêsames, monsieur. E eu ainda não sou oficial, mas... enfim, deixa pra lá. Pode vir conosco e nos contar o que aconteceu lá?";
			link.l1 = "Eu vou te contar. O bordel estava dando prejuízo, e não havia mais dinheiro para pagar os mercenários que faziam a segurança. Eles decidiram pegar o que restava, bem na hora em que eu estava lá. Madame Etoile e eu lutamos contra eles, mas ela morreu dos ferimentos. Agora, me deixe passar, finalmente.";
			link.l1.go = "PZ_TortugaSoldierGirlDied2";
		break;
		
		case "PZ_TortugaSoldierGirlDied2":
			dialog.text = "Eu adoraria, mas há muita papelada para preencher. E preciso entrevistar as moças que trabalham lá. Receio que você terá que ficar na cidade por pelo menos um dia, mesmo que esteja dizendo a verdade, monsieur.";
			link.l1 = "Vá para o inferno...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_Longway_101":
			dialog.text = "Longway tem algo para você, Senhor Capitão.";
			link.l1 = "Que coisa linda e curiosa. Nunca vi nada assim. O que é isso?";
			link.l1.go = "PZ_Longway_102";
			GiveItem2Character(PChar, "talisman14");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Longway_102":
			dialog.text = "É o amuleto do Capitão da minha terra natal. E, já que Longway não é mais Capitão, eu dou ele para você.";
			link.l1 = "Obrigado, Longway. Com a morte do van der Vink, você conseguiu sua vingança contra todos que queria. Fico feliz que tudo tenha terminado assim.";
			link.l1.go = "PZ_Longway_103";
		break;
		
		case "PZ_Longway_103":
			dialog.text = "Se ao menos eu pudesse convencer Xing a ser uma pessoa boa de novo...";
			link.l1 = "Ela não queria mais ouvir ninguém, nem mesmo o próprio irmão. Você fez o melhor que pôde. Todos nós fizemos.";
			link.l1.go = "PZ_Longway_104";
		break;
		
		case "PZ_Longway_104":
			dialog.text = "Sim... Muito obrigado, Senhor Capitão. Longway está livre, e tem um lar e amigos de novo.";
			link.l1 = "De nada, meu amigo. Agora, por que você não vem comigo visitar meu irmão? Ah, que ironia!";
			link.l1.go = "PZ_Longway_105";
		break;
		
		case "PZ_Longway_105":
			DialogExit();
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			chrDisableReloadToLocation = false;
			ReturnOfficer_Longway();
		break;
		
		case "PZ_PuansieDialogWithLevasser_1":
			dialog.text = "Aqui estamos de novo, François. Vejo que a vida não foi fácil pra você, hehe.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_1_1";
			LAi_SetHuberType(npchar);
		break;
		case "PZ_PuansieDialogWithLevasser_1_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_2":
			dialog.text = "Poincy, seu desgraçado ganancioso... Quase se engasgou com o ouro que já entope seus cofres, e ainda assim nunca é o bastante, não é?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_2_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_2_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_3":
			//LAi_SetActorType(npchar);
			//LAi_ActorSetHuberMode(npchar);
			dialog.text = "Vou dividir um pouco com você, François. Vai ser o suficiente, pode acreditar.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_3_1";
			//LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		case "PZ_PuansieDialogWithLevasser_3_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_4", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_4":
			dialog.text = "O que... o que você quer dizer?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_4_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_4_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_5":
			dialog.text = "";
			link.l1 = "Governador-Geral, o senhor vai...";
			link.l1.go = "PZ_PuansieDialogWithLevasser_6";
		break;
		
		case "PZ_PuansieDialogWithLevasser_6":
			dialog.text = "Charles, meu amigo, você fez o seu trabalho e fez brilhantemente! O que vai acontecer com esse homem não deve te preocupar... No entanto, é bom que saiba, Capitão, caso sua cabeça brilhante tenha alguma ideia idiota algum dia. Nosso amigo em comum vai sofrer uma bela indigestão, por assim dizer. Ouvi dizer que ouro não faz bem ao estômago... Espero não precisar explicar mais do que isso.";
			link.l1 = "Não, Governador-Geral.";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7";
		break;
		
		case "PZ_PuansieDialogWithLevasser_7":
			dialog.text = "Ao contrário do Monsieur François, você tem um grande futuro pela frente, Charles. Rapazes, levem esse porco para a cadeia!";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7_1";
		break;
		case "PZ_PuansieDialogWithLevasser_7_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_8", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_8":
			dialog.text = "Tirem as mãos de mim, seus desgraçados! Está satisfeito agora, de Maure?! Vai se foder! Vocês dois vão queimar no Inferno, na mesma frigideira que eu!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie3");
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
			sld = characterFromID("PZ_SoldFra_1");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
			sld = characterFromID("PZ_SoldFra_2");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_Baker_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Kasper";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Sharp";
			dialog.text = "Bem, senhor. Eu examinei a senhorita "+sStr+"...";
			link.l1 = "Quão grave é, Raymond?";
			link.l1.go = "PZ_Baker_2";
		break;
		
		case "PZ_Baker_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Nada com que se preocupar, Capitão. A Mary se machucou feio, claro, mas, no geral, tudo vai ficar bem. Ela deve ficar de cama por alguns dias, e acredito que em duas semanas já estará de volta à ativa.";
					link.l1 = "Entendi. Obrigado, Raymond. Pode se retirar.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "A Mary levou uma surra daquelas, Capitão. Hematomas, cortes... e o choque de tudo isso, claro – embora ela tente não demonstrar.";
					link.l1 = "Ela está mantendo uma cara firme, como sempre. Mas acho que ela percebe que agora é melhor ficar de repouso. Mas até quando, hein?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Nem um soldado profissional conseguiria sobreviver ao que ela passou, Capitão. Entorses, distensões, hematomas – tivemos sorte daqueles desgraçados não terem quebrado os ossos dela. Mas os tendões estão lesionados, então ela não vai conseguir empunhar uma lâmina por pelo menos um mês.";
					link.l1 = "Que se dane a lâmina. Quando é que ela vai conseguir ficar de pé?";
					link.l1.go = "PZ_Baker_3";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Não se preocupe, Capitão. Hellen está ferida, mas não gravemente. Ela vai precisar ficar de cama por enquanto, mas acredito que em algumas semanas estará totalmente recuperada.";
					link.l1 = "Entendi. Obrigado, Raymond. Dispensado.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Ela apanhou bastante, capitão. E os ferimentos físicos são só uma parte do diagnóstico... Estar naquele lugar horrível fez ela reviver o pesadelo que passou no Arbutus.";
					link.l1 = "Claro... droga! Quando é que ela vai se recuperar?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Helen caminhou na corda bamba, Senhor Capitão. Estou surpreso que ela tenha sobrevivido a tudo o que passou. Nenhuma laceração interna ou fratura, mas muitos entorses e distensões.";
					link.l1 = "Pobrezinha. Quanto tempo vai durar a recuperação dela?";
					link.l1.go = "PZ_Baker_3";
				}
			}
		break;
		
		case "PZ_Baker_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Pelo menos uma semana, senhor. Se ela seguir minhas recomendações, deve estar pronta para voltar à ativa em cerca de um mês.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Não antes de quinze dias, senhor. Depois disso, vou permitir que ela dê pequenas voltas no convés. A recuperação completa vai levar pelo menos dois meses.";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Não incomode ela por pelo menos uma semana, pode acreditar, senhor. A recuperação completa vai levar cerca de um mês.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "She should stay in bed for a fortnight; after that, she may be able to walk around the deck. But don't expect to see her back in action for at least two months.";
				}
			}
			link.l1 = "Entendi. Obrigado, Raymond. Dispensado.";
			link.l1.go = "PZ_Baker_4";
		break;
		
		case "PZ_Baker_4":
			DialogExit();
			sld = CharacterFromID("Baker");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_RazgovorSVrachom_4", -1);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "É mais difícil do que eu pensei ficar de pé depois de tanto tempo deitada, né!";
				link.l1 = "Talvez você não devesse interromper o repouso tão de repente, meu bem.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Oh-h, minha cabeça...";
				link.l1 = "Helen! Você não acordou cedo demais? Mal consegue ficar de pé!";
			}
			link.l1.go = "PZ_DevushkaVstalaSKrovati_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Prefiro queimar essa maldita cama do que deitar nela de novo – pelo menos até eu andar do convés à popa e voltar!";
				link.l1 = "É uma cama confortável, bem aconchegante. E o navio também não é ruim. Então, não vou te impedir. Mas vou estar lá para garantir que você não faça nenhuma besteira.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Estou bem, Capitão, embora não completamente. Ainda não estou pronto para brandir uma lâmina, mas odeio esta cama com toda a minha alma.";
				link.l1 = "Bem, uma caminhada curta no convés provavelmente não vai te fazer mal. Mas nem pense em chegar perto dos cabos!";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaStoitVosstanovlenie");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, você não acha que já se esqueceu completamente de mim? Me diz quando foi a última vez que dormimos juntos, né!";
				link.l1 = "Antes... Melhor não falarmos sobre isso, né, Mary?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Meu capitão, deixei de interessar você como mulher?";
				link.l1 = "Isso é inesperado, Helen. Normalmente sou eu quem fala disso... mas eu não tinha certeza se você estava pronta depois...";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Sex2";
			DelLandQuestMark(npchar);
			pchar.questTemp.PZ_DevushkaSnovaOfficer = true;
			DeleteQuestCondition("PZ_DevushkaSnovaOfficer2");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Então fale de mim pelo menos, né. Ou eu fiquei desagradável pra você depois que aqueles dois desgraçados me espancaram?";
				link.l1 = "Isso é a coisa mais idiota que já ouvi. Eu só não queria te incomodar até você estar pronto. E já que está...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Sex3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Está tudo bem, Charles, de verdade. Eu só tento não pensar nisso. E além do mais, você me salvou do pior. Então vamos parar de falar e só... colocar a conversa em dia.";
				link.l1 = "Essa é uma ideia muito boa, Helen.";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex3":
				dialog.text = "Charles, eu não quero, eu exijo, né!";
				link.l1 = "Eu não ousaria recusar você...";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, precisamos conversar, né.";
				link.l1 = "Aconteceu alguma coisa, Mary? Você parece meio ansiosa, e isso geralmente não é um bom sinal.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Meu capitão, tem algo que preciso lhe contar.";
				link.l1 = "É mesmo, Helen? Estou ouvindo.";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "É justamente isso! Não é bom que eu esteja pronto para voltar aos meus deveres como oficial?";
				link.l1 = "Então é isso. Bem, se você se sente forte o bastante, não é só bom, é maravilhoso.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Estou cansada da tripulação ficar me olhando como se eu fosse uma velha frágil. Quero voltar ao leme e esticar os braços praticando com a espada...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Se você estiver disposto, não vou me opor, querido. Vou pegar seu equipamento. E vou deixar você assumir o leme com prazer. Mas tome cuidado numa briga, né?";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2_1";
				}
				else
				{
					link.l1 = "Sentimos sua falta na ponte, Helen. Quanto à lâmina, acho que está na hora de devolvê-la para você.";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
				}
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2_1":
			dialog.text = "Claro, Meu Capitão, como quiser.";
			link.l1 = "Bom.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Maravilha, né? Mal posso esperar para treinar com a espada...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Fico feliz em ouvir isso, Mary. Mas não se jogue de cabeça logo de cara... Mas quem sou eu pra te dizer isso?";
					link.l1.go = "exit";
					AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
				}
				else
				{
					link.l1 = "Acho que vai ficar feliz em ver esse palash de volta à bainha...";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Eu... Eu não sei o que dizer, Charles. Só agora percebi o quanto esse sabre significa para mim...";
				link.l1 = "Eu já sabia disso há muito tempo, por isso ela ficou esperando por você, sã e salva.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				notification("Gave Cutlass of Blaze", "None");
				PlaySound("interface\important_item.wav");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Meu narval, né!!! Charles, você salvou ele! Eu não tô só feliz, tô radiante! Obrigada, obrigada! Eu tava morrendo de medo que tivesse ficado no navio do Martin...";
				link.l1 = "Esta lâmina pertence à sua mão, meu Talismã Vermelho. Confio que você não vai perdê-la de novo... Bem, não vou atrapalhar o seu reencontro, ha-ha!";
				notification("Gave Narwhal", "None");
				PlaySound("interface\important_item.wav");
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Obrigada, Charles. Sabe, talvez seja por isso que eu te amo...";
				link.l1 = "Por trazer de volta coisas perdidas? Ha ha ha ha...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog5";
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog5":
			dialog.text = "Você está rindo, mas eu estou falando sério.";
			link.l1 = "Eu sei, Helen. Também te amo, embora eu ainda não saiba direito o porquê.";
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog6";
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog6":
			dialog.text = "Talvez porque ainda não usei este sabre em você.";
			link.l1 = "Vou me salvar disso indo para os barcos. Vou te esperar lá, Helen.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
	}
} 