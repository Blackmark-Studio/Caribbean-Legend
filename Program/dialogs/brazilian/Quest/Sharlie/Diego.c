// Диего де Монтойя
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
			dialog.text = "Você quer alguma coisa?";
			link.l1 = "Não, nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "patrol":
			dialog.text = TimeGreeting()+", "+GetFullName(npchar)+", Chefe da patrulha de San Jose. Recebemos uma mensagem sobre um comportamento suspeito nos arredores desta cidade. Poderia nos dizer quem é e o que está fazendo aqui?";
			link.l1 = "Capitão "+GetFullName(pchar)+", senhor oficial. Estou aqui sob a autoridade e instruções diretas do Inquisidor Padre Vincento. Aqui está um documento que confirma minha autorização.";
			link.l1.go = "patrol_1";
		break;
		
		case "patrol_1":
			dialog.text = "Tudo certo... Está tudo em ordem. O documento está preenchido corretamente e assinado pelo inquisidor. Me desculpe pela desconfiança. O que você está fazendo no farol?";
			link.l1 = "I'm not authorised to answer such questions. If you are genuinely interested in the purpose of my work for the inquisitor, I would recommend referring directly to him in Santiago for clarification. You are an officer; surely you have knowledge of military and service secrets. The only thing I can tell you is that I am investigating the circumstances of a wrecked Spanish ship.";
			link.l1.go = "patrol_2";
		break;
		
		case "patrol_2":
			dialog.text = "Me desculpe mais uma vez, Monsieur. Não vou ousar atrasá-lo ainda mais... ah, só um instante! Eu vi mesmo o brilho de uma lâmina fria ou foi só imaginação minha? Que adaga interessante você tem! Pode me mostrar?";
			link.l1 = "Não se esqueça de devolver, por favor. Isso é muito importante para mim.";
			link.l1.go = "patrol_3";
		break;
		
		case "patrol_3":
			dialog.text = "Dios mio! Eu conheço essa adaga, vi ela ilustrada em um dos livros da biblioteca! É a adaga do próprio Cortés! Tem a marca bem aqui... Monsieur, por favor, não recuse. Deixe-me ficar com essa adaga! Eu coleciono armas antigas e personalizadas, e essa é simplesmente um exemplar incrível. Pago muito bem por ela.";
			link.l1 = "Senhor, esta adaga não está à venda. Ganhei de presente e não pretendo vendê-la para ninguém. Devolva, por favor.";
			link.l1.go = "patrol_4";
		break;
		
		case "patrol_4":
			dialog.text = "Nem com quinhentos dobrões de ouro você ficaria satisfeito? Isso é uma fortuna. Dá pra comprar um navio com esse dinheiro!";
			link.l1 = "Não. Eu já tenho um navio, e essa adaga é única. Não vou vendê-la.";
			link.l1.go = "patrol_5";
		break;
		
		case "patrol_5":
			dialog.text = "Ah, que pena... Tudo bem, pegue seus pertences. Não vou mais incomodar você. Boa sorte!";
			link.l1 = "Tudo de bom, oficial.";
			link.l1.go = "patrol_6";
		break;
		
		case "patrol_6":
			DialogExit();
			AddQuestRecord("Guardoftruth", "42");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "GuardOT_ClearMayakPatrol", 12.0);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("GOT_spamayaksold_"+i);
				sld.lifeday = 0;
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 10.0);
			}
		break;
		
		case "shore":
			PlaySound("Voice\English\Sharlie\Diego De Montoya.wav");
			dialog.text = "Chega! Quero falar com ele...";
			link.l1 = "Então, vejo Diego de Montoya bem na minha frente... Mas me perdoe, señor. Já nos encontramos antes, não foi? Ah, sim, é verdade. Em Trinidad, no farol local. Mas tenho certeza de que lá você usava outro nome...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			dialog.text = "Sua memória não falha, senhor. Pois saiba que você não é o único capaz de criar intrigas e travar guerras nos bastidores. Estou bem ciente do seu desejo incessante de me ver. Pois bem, parece que seu desejo foi realizado.";
			link.l1 = "Não era exatamente esse tipo de encontro que eu esperava, señor.";
			link.l1.go = "shore_2";
		break;
		
		case "shore_2":
			dialog.text = "Bem, é o que é. Mas vou te dar uma chance de sair daqui vivo se me der sua adaga.";
			link.l1 = "A sua paixão por colecionar raridades te levou tão longe assim, caballero, a ponto de preparar uma armadilha tão bem planejada para mim?  Ah, não acredito nisso. O Guardião da Verdade está te deixando alerta ou estou enganado?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "Eu não faço ideia do que você está falando. A adaga precisa voltar para onde pertence e é só isso que você precisa saber. Você não quis entregá-la por ouro, então agora vai entregá-la para salvar a própria vida.";
			link.l1 = "Você realmente acha, senhor, que eu vou acreditar no que acabou de me contar? Você já decidiu que eu não vou sair desta baía, não é mesmo?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			dialog.text = "E se eu te der minha palavra?";
			link.l1 = "A palavra para um 'comedores de rã'? Hm...";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "Monsieur, I'm giving you one last chance. Either you hand over the dagger I'm interested in, or I'll be looting your dead body in a few minutes. Resistance is futile; we've got an overwhelming advantage in numbers.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio")) link.l1 = "Você realmente me surpreendeu, señor, disso não tenho dúvida. Acha mesmo que sou um imbecil tão cabeça-dura a ponto de enfiar a cabeça na boca de um tubarão sem antes pegar meu arpão? Rapazes, matem eles!";
			else link.l1 = "O verdadeiro poder não está nos números, mas sim na habilidade, señor!";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto5", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio"))
			{
				PlaySound("interface\abordage_wining.wav");
				PlaySound("interface\abordage_wining.wav");
				for(i=1; i<=10; i++)
				{
					sld = characterFromId("GuardOT_Oursoldier_"+i);
					LAi_SetWarriorType(sld);
					ChangeCharacterAddressGroup(sld, "Shore15", "reload", "reload1_back");
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			sld = CharacterFromID("spa_baseprisoner");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=1; i<=13; i++)
			{
				sld = characterFromId("GOT_spashore_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_DiegoShoreGuardDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
