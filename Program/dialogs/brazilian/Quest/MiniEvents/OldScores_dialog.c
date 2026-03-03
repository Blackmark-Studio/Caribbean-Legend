void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
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

		case "OS_Matros_sluh":
			bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			if (bOk1 || bOk2)
			{
				dialog.text = "Dizem que teve uma briga na taverna ontem à noite... Mas quem estava brigando — não faço ideia. Meu rosto ainda está inteiro. Acho.";
				link.l1 = "Parece que rolou uma bela farra por aqui, hein?";
				link.l1.go = "OS_Matros_sluh_2";
			}
			else
			{
				switch (rand(2))
				{
					case 0:
						dialog.text = "Oi, "+GetSexPhrase("companheiro","moça")+", viu minha bota por aí? Algum ladrão miserável levou enquanto eu estava desmaiado debaixo da mesa da taverna.";
						link.l1 = "Fique mais atento, ou o outro olho vai acabar do mesmo jeito.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 1:
						dialog.text = "Dizem que houve uma briga na taverna ontem... Mas ninguém sabe direito quem estava brigando. Meu rosto parece inteiro. Acho que sim.";
						link.l1 = "Talvez acharam que o seu rosto já tinha apanhado o suficiente.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 2:
						dialog.text = "Por todos os demônios do fundo do mar, ontem eu tinha uma bolsa cheia de ouro! Onde diabos ela foi parar agora?!";
						link.l1 = "Para um verdadeiro pirata, o ouro não é o prêmio mais importante. A liberdade vale muito mais.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;
				}
			}
		break;
		
		case "OS_Matros_sluh_2":
			dialog.text = "Ah, com certeza! O estalajadeiro estava atolado de trabalho... hic... E além disso... alguém roubou o gin dele! Não foi só uma garrafa, mas um barril inteiro! E não era qualquer barril — desse tipo você não acha em nenhum outro lugar do Caribe! Dizem que veio direto da Europa. Ele não fala pra quem era, mas uma coisa é certa: se não encontrarem logo, o coitado vai passar por maus bocados!";
			link.l1 = "Isso é engraçado. Então, se cuida, seu velho bêbado.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OS_Matros_sluh";
			OS_Start();
		break;

		case "OS_Matros_again":
			switch (rand(2))
			{
				case 0:
					dialog.text = "O que mais você quer? Não está vendo que minha cabeça vai explodir? Cai fora.";
					link.l1 = "Talvez bebendo menos você até pareça um homem de verdade, e não um trapo encharcado.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Me deixe em paz... Minha cabeça vai explodir!";
					link.l1 = "É impressionante que ainda esteja grudada nos seus ombros.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 2:
					dialog.text = "Maldição sobre você... Me deixe em paz, não está vendo que não estou em condições de conversar!";
					link.l1 = "...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
		break;
		
		case "OS_Matros":
			dialog.text = "Saia daqui! Não tá vendo que já cheguei no meu limite? Estou doido pra descarregar meus punhos na cara de alguém.";
			link.l1 = "Calma, marinheiro. Só quero saber o que aconteceu na taverna ontem.";
			link.l1.go = "OS_Matros_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Matros_2":
			dialog.text = "Maldição e desgraça! Você está "+GetSexPhrase("mais um dos amantes daquela criada maluca","um parente")+"? O que você quer, que seja jogado ao mar numa tempestade? Vai me desafiar para um duelo, é isso? Ou vai sacar a espada aqui e agora?";
			if (pchar.sex == "woman")
			{
				link.l1 = "Parente? Nem de longe. Mas você, camarada, não parece ter muita consideração por ela?";
				link.l1.go = "OS_Matros_3_scrit";
			}
			else
			{
				link.l1 = "Amante? Duvido muito. Aquela moça parece preferir quantidade à qualidade nas suas conquistas, não acha?";
				link.l1.go = "OS_Matros_3_scrit";
				link.l2 = "Os assuntos dela não me dizem respeito. Só me conte o que aconteceu, e eu te deixo em paz. Foi você que a deixou tão furiosa, não foi?";
				link.l2.go = "OS_Matros_3_fortuna";
			}
		break;
		
		case "OS_Matros_3_scrit":
			dialog.text = "Aquela diaba é tão exigente quanto um marinheiro faminto depois de meses no mar – pega o que está mais perto e resolve depois! Ela ficou me lançando olhares a noite toda, flertando como uma gata de taverna atrás de restos. Mas na hora que tentei ancorar no porto dela – gritou tão alto que até os peixes da baía mergulharam pro fundo!";
			link.l1 = "Talvez você tenha bebido rum demais e tenha sido direto demais na sua abordagem?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "OS_Matros_3_fortuna":
			dialog.text = "Aquela diaba é tão exigente quanto um marinheiro faminto depois de meses no mar – pega o que estiver mais perto e resolve depois! Ela ficou me lançando olhares a noite toda, flertando como gata de taverna atrás de restos. Mas na hora que tentei atracar no porto dela – gritou tão alto que até os peixes da baía mergulharam fundo!";
			link.l1 = "Talvez você tenha bebido rum demais e tenha sido direto demais na sua abordagem?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "OS_Matros_4":
			dialog.text = "Talvez eu estivesse meio alto, mas lembro tão claramente quanto um mar calmo do que aconteceu lá. Não fui eu que fui atrás dela – ela é que ficou me rondando como tubarão sentindo cheiro de sangue. Ela passou o dia inteiro me cercando, aquela desgraçada!";
			if (pchar.sex == "woman")
			{
				link.l1 = "E por uma questão tão insignificante você está pronto para brigar com o primeiro que aparecer? Ou aconteceu outra coisa naquela noite?";
			}
			else
			{
				link.l1 = "Escuta aqui, você disse 'outro amante.' Sabe de alguma coisa sobre os casos dela?";
			}
			link.l1.go = "OS_Matros_5";
		break;

		case "OS_Matros_5":
			dialog.text = "Depois que os gritos dela cessaram, meus companheiros de bordo disseram que eu estava perdendo meu tempo tentando jogar charme pra cima dela. Disseram que ela já tem um pretendente na cidade, que é unha e carne com o nosso capitão.";
			link.l1 = "Interessante. Você percebeu mais alguma coisa estranha? Talvez alguém se aproximando do balcão durante a confusão?";
			link.l1.go = "OS_Matros_6";
		break;

		case "OS_Matros_6":
			dialog.text = "Que o diabo leve tudo... Minha cabeça está rachando como um casco no recife, e você aparece com essas perguntas infernais. Não vi nem ouvi porcaria nenhuma. Era melhor me dar uns pesos do que atormentar um marinheiro experiente com esse interrogatório.";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Aqui estão cem pesos. Não vá se embriagar e cair de novo no feitiço daquela garçonete, hein?";
				link.l1.go = "OS_Matros_7_harizma";
			}
			link.l2 = "Você vai se virar sem o meu dinheiro. Caso contrário, só vai acabar bêbado e enchendo o saco daquela garçonete de novo.";
			link.l2.go = "OS_Matros_7_fortuna";
		break;
		
		case "OS_Matros_7_harizma":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddQuestRecord("OS", "3");
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Matros_7_fortuna":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddQuestRecord("OS", "3");
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Dialog_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Ei, Jack! Tem uma rameira do cais nos seus aposentos! Ha-ha! Dá só uma olhada nela – que diabinha atraente! Fico pensando, será que ela já revirou todos os nossos baús, ou será que a pegamos bem na melhor parte?";
				link.l1 = "...";
			}
			else
			{
				dialog.text = "Ei, Jack! Olha só o que temos aqui – um rato ladrão! Ha-ha! Dá só uma olhada nesse canalha! Já andou fuçando nos nossos baús, não foi, esse safado sorrateiro?";
				link.l1 = "...";
			}
			link.l1.go = "OS_Dialog_2";
		break;

		case "OS_Dialog_2":
			StartInstantDialog("OS_Jack", "OS_Dialog_3", "Quest\\MiniEvents\\OldScores_dialog.c");
		break;

		case "OS_Dialog_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "Uma galinha ousada, hein. Invadindo o covil do Jack Veils — poucos teriam coragem pra isso. Então, o que te traz aqui, querida? Veio achando que ia nos divertir, foi isso?";
				link.l1 = "Entreter vocês? Ha! Vocês são mesmo sonhadores, senhores. Estou aqui para recuperar o que roubaram. Sério que acharam que essa encenação ridícula ia passar despercebida?";
			}
			else
			{
				dialog.text = "Um verme ousado, de fato. Invadir a casa do Jack Veils não é algo que muitos teriam coragem de tentar. Muito bem, o que você veio fazer aqui?";
				link.l1 = "Digamos apenas que estou recuperando uma propriedade roubada. Ou vocês realmente achavam que essa encenação patética ia passar despercebida?";
			}
			link.l1.go = "OS_Dialog_4";
		break;

		case "OS_Dialog_4":
			StartInstantDialog("OS_capWolf", "OS_Dialog_5", "Quest\MiniEvents\OldScores_dialog.c");
		break;

		case "OS_Dialog_5":
			if (pchar.sex == "woman")
			{
				dialog.text = "Desempenho patético?! Que o diabo me carregue, vou arrancar sua pele e usá-la como vela! Ha-ha! Mas talvez antes a gente... se divirta um pouco com você, hein?";
				link.l1 = "Vejo que está ansioso para encontrar seu criador? Muito bem, não vou te fazer esperar – venham, seus desgraçados imundos!";
			}
			else
			{
				dialog.text = "Charada patética? Que o diabo me leve, vou arrancar o couro das suas costas e usá-lo como lona de vela! Chega de conversa – sua hora chegou, seu cachorro miserável!";
				link.l1 = "Se é assim que você quer, então venha, canalhas!";
			}
			link.l1.go = "OS_Dialog_bitva";
		break;
		
		case "OS_Dialog_bitva":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("OS_Jack");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("OS_capWolf");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "OS_VernuliBochonok");
		break;
		
		case "Zaharia_1":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = ""+sld.name+", cadê meu gim?! Se você não tiver, eu mesmo vou te mandar alimentar os peixes no fundo do porto!";
			link.l1 = "...";
			link.l1.go = "Zaharia_2";
			CharacterTurnByChr(npchar, sld);
			//locCameraFromToPos(-2.53, 2.00, 1.26, false, 0.03, 0.00, -1.11);
		break;

		case "Zaharia_2":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "...";
			link.l1 = "Acabei de entregar eu mesmo. Aqui está.";
			link.l1.go = "Zaharia_3";
			CharacterTurnByChr(npchar, pchar);
			TakeItemFromCharacter(pchar, "cask_gin");
			notification("You gave the barrel of gin", "NONE");
		break;

		case "Zaharia_3":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "Bom ver que minha confiança em você não foi em vão, "+sld.name+". Passe nos meus aposentos amanhã para pegar seus dobrões.";
			link.l1 = "...";
			link.l1.go = "Zaharia_4";
			CharacterTurnByChr(npchar, sld);
		break;
		
		case "Zaharia_4":
			DialogExit();
			
			//ChangeShowIntarface();
			LAi_SetStayType(pchar);
			
			sld = CharacterFromID("OS_Zaharia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.lifeday = 0;
			sld.location = "None";
			
			DoQuestFunctionDelay("OS_RazgovorTavern", 1.5);
		break;
		
		case "Tavern_1":
			dialog.text = "Capitão, sobre aquela placa...";
			link.l1 = "Que placa? Ah, aquela... Sinceramente, não preciso dessas honrarias. Não se preocupe comigo.";
			link.l1.go = "Tavern_2";
		break;

		case "Tavern_2":
			dialog.text = "Posso oferecer algo muito melhor! De hoje em diante, você sempre terá hospedagem e bebidas de graça na minha taverna! Uma pessoa do seu calibre certamente merece isso!";
			link.l1 = "Agora sim, isso me agrada! Privilégios assim eu aprecio de verdade! Até que nossos caminhos se cruzem de novo, "+npchar.name+".";
			link.l1.go = "Tavern_3";
		break;
		
		case "Tavern_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			AddQuestRecord("OS", "5");
			AddQuestUserData("OS", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.OS_Tavern_FreeBuhlo = true;
			ChangeShowIntarface();
			
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			sld.dialog.filename = "Common_Tavern.c";
			sld.dialog.currentnode = "First Time";
			LAi_SetBarmanType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			
			PChar.quest.OS_AttackSea.win_condition.l1 = "location";
			PChar.quest.OS_AttackSea.win_condition.l1.location = "Cuba1";
			PChar.quest.OS_AttackSea.function = "OS_AttackSea";
			
			// вражеский корабль атакует в море
			sld = CharacterFromID("OS_Pirate");
			DeleteAttribute(sld, "AlwaysFriend");
			DeleteAttribute(sld, "ShipEnemyDisable");
			sld.AlwaysEnemy = true;
			LAi_SetImmortal(sld, false);
			
			PChar.quest.TPZ_Potopil.win_condition.l1 = "NPC_Death";
			PChar.quest.TPZ_Potopil.win_condition.l1.character = "OS_Pirate";
			PChar.quest.TPZ_Potopil.function = "OS_Pobeda";
		break;
		
		
		
		
		
		
		
	}
}