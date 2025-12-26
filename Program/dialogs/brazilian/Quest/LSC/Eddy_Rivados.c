// лидер клана ривадос - Чёрный Эдди
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "O que você está fazendo no território dos Rivados, homem branco?";
			link.l1 = "Só estou conhecendo os moradores. Desculpe se incomodei você.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Friend":
			dialog.text = "Fico feliz em receber um amigo dos Rivados e um homem de valor! Chimiset me contou o que você fez por ele. Todos os Rivados, eu incluso, lhe devemos agora. Permita-me apresentar: Edward Black, também conhecido como Eddie Negro, líder da gangue Rivados.";
			link.l1 = ""+GetFullName(pchar)+"   Embora eu ache que Chimiset já tenha falado sobre mim. Ele prometeu que contaria... ";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			dialog.text = "E ele fez isso. Agora você pode visitar nossos navios livremente. Os guardas não vão te impedir e vamos ficar felizes em te ver. Tome cuidado com os Narvais, eles provavelmente já descobriram que você salvou Chimiset, e não vão gostar nada disso, já que somos inimigos.";
			link.l1 = "Vou pensar nisso. Obrigado pela recepção calorosa, Eddie! Agora, por favor, me deixe falar com Chimiset.";
			link.l1.go = "Friend_2";
		break;
		
		case "Friend_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			AddSimpleRumourCityTip("They say that you are a close friend of Black Eddie, the head of Rivados. How did you do this?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Rivados claim you as their friend. How'd you do it?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that the Narwhals have a price on your head. Are you scared?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		// --> информационный блок
		case "Total_info": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Irmão branco? Vivo? Que bom! Então, os Narvais mentiram quando disseram a todos que você tinha se afogado...";
				link.l1 = "Também fico feliz em te ver, Eddie. Os boatos sobre a minha morte foram muito exagerados.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "Que bom te ver, "+pchar.name+". Alguma novidade?";
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l1 = "Eddie, você conhece um homem chamado Nathaniel Hawk? Pelo que sei, ele deve estar aqui.";
				link.l1.go = "natan";
			}
			if (!CheckAttribute(npchar, "quest.rivados"))
			{
				link.l2 = "Me conte mais sobre a gangue dos Rivados.";
				link.l2.go = "rivados";
			}
			link.l9 = "Nada demais, na verdade. Só queria dizer oi.";
			link.l9.go = "exit";
		break;
		
		case "natan":
			dialog.text = "Nathaniel Hawk? No, I don't know this man. He is neither on the Rivados ships nor in neutral territory. I can't say the same about the Narwhal gang; we don't visit them.";
			link.l1 = "Entendi...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_info";
		break;
		
		case "rivados":
			dialog.text = "The Rivados gang was founded many years ago. It was the very first clan in this City of Abandoned Ships. More than fifty years ago, Admiral Betancourt's expedition sailed here from West Africa with several large slave ships. The holds of the Tartarus were filled with hundreds of black slaves bound for the Caribbean plantations. There was a man among those slaves named Pedro Rivados; some Portuguese priests had taught him how to read and write.\nHe managed to free a few dozen slaves from their shackles and raised a mutiny. Alas, the rest of the slaves failed to join him. The revolt was quelled. The slavers tied Rivados hand and foot and left him in the ship's hold to perish from hunger and thirst. A few days later the weather turned bad and Betancourt's squadron was swept up by a powerful storm.\nDays later, after fighting the weather, the 'San Augustine' and the 'Tartarus', the only two ships still intact, were stuck in the middle of this Island. A lot of men died during those events, black and white, but many more managed to survive. The ex-slaves started a new life together and called themselves the Rivados in honour of Pedro Rivados, the liberator.";
			link.l1 = "Uma história muito interessante... Obrigado!";
			link.l1.go = "exit";
			npchar.quest.rivados = "true";
			NextDiag.TempNode = "Total_info";
		break;
		// <-- информационный блок
		
		case "capper":
			dialog.text = "O que você quer no território dos Rivados, homem branco?";
			link.l1 = "Meu nome é "+GetFullName(pchar)+" e estou aqui a mando do Almirante Dodson. Preciso falar com o Eddie Negro. Pelo que entendi, esse é você.";
			link.l1.go = "capper_1";
		break;
		
		case "capper_1":
			dialog.text = "Sim, sou Edward Black, também conhecido como Eddie Negro. Diga, o que o almirante quer de mim.";
			link.l1 = "Há um homem no 'Tartarus' chamado Chimiset. O almirante está disposto a libertá-lo.";
			link.l1.go = "capper_2";
		break;
		
		case "capper_2":
			dialog.text = "Isso é uma ótima notícia. Chimiset é nosso líder espiritual, e todos os Rivados sentem falta dele. Mas entendo que o almirante quer algo em troca da liberdade dele, certo?";
			link.l1 = "Nada. Ele só quer libertá-lo como um gesto de boa vontade. Mas tem um problema...";
			link.l1.go = "capper_3";
		break;
		
		case "capper_3":
			dialog.text = "Vai em frente, homem branco.";
			link.l1 = "O antigo contramestre do almirante, agora carcereiro Chad Kapper, juntou-se aos Narvais, se rebelou e agora está fora do controle do almirante. Sabemos que Chad está planejando matar Chimiset. O almirante não quer que isso aconteça. Propomos uma operação conjunta para eliminar o traidor e libertar seu homem.";
			link.l1.go = "capper_4";
		break;
		
		case "capper_4":
			dialog.text = " Suas palavras soam um pouco estranhas, mas continue. Chimiset está em apuros? ";
			link.l1 = "Sim. Chad está planejando matá-lo. Kapper vai usar os Narvais para tomar o controle da Cidade. Temos que agir rápido se quisermos salvar Chimiset, já que Chad não desconfia de nada por enquanto. O Almirante levou todos os guardas do 'Tártaro', a passagem está livre. Aqui está a chave que abre a porta dentro da prisão. Pegue.";
			link.l1.go = "capper_5";
		break;
		
		case "capper_5":
			RemoveItems(pchar, "key_capper", 1);
			dialog.text = "";
			link.l1 = "Reúna seus homens, vá até Tártaro e liberte Chimiset. Todas as cartas estão nas suas mãos.";
			link.l1.go = "capper_6";
		break;
		
		case "capper_6":
			dialog.text = "Parece uma armadilha... E se for uma emboscada? E se o almirante decidir atacar os Rivados? Por que ele mesmo não resolve com o Kapper?";
			link.l1 = "Dodson disse que você se importa com a vida do Chimiset... Ele já fez o suficiente: aqui está a chave e os guardas se foram. Só falta você entrar, resolver com o Chad e libertar seu homem. Dou minha palavra de que não há armadilha. Ah, e mais uma coisa: o almirante quer a cabeça do Chad em troca da vida e liberdade do Chimiset. Temos um acordo?";
			link.l1.go = "capper_7";
		break;
		
		case "capper_7":
			dialog.text = "A vida de Chimiset é de valor inestimável para os Rivados. Vamos nos mover para o 'Tartarus' imediatamente. Mas você vai ficar aqui como nosso refém. E se houver uma emboscada, você vai enfrentar a fúria dos Rivados!\nZikomo! Fique perto da porta e vigie nosso convidado. Não o deixe sair. Eu mesmo vou liderar o ataque ao 'Tartarus'!";
			link.l1 = "Boa sorte, Eddie. E lembre-se: eu preciso da cabeça do Chad Kapper!";
			link.l1.go = "capper_8";
		break;
		
		case "capper_8":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_ZikomoNearDoor", 10.0);
			NextDiag.CurrentNode = "chimiset";
		break;
		
		case "chimiset":
			dialog.text = "Chimiset está livre! Você não mentiu, homem branco, estou pronto para te chamar de amigo dos Rivados!";
			link.l1 = "Fico feliz. Chad Kapper está morto?";
			link.l1.go = "chimiset_1";
		break;
		
		case "chimiset_1":
			dialog.text = "Preciso pedir seu perdão, amigo branco: você fez tudo o que pôde por nós, mas nós falhamos com você... Eu falhei com você! Aquele maldito Kapper escapou. Havia dois Narvais com ele. Nós os matamos, mas o carcereiro imundo fugiu nadando pela porta de baixo para os territórios dos Narvais.";
			link.l1 = "Merda... Você não sabia que havia duas saídas do 'Tártaro'?";
			link.l1.go = "chimiset_2";
		break;
		
		case "chimiset_2":
			dialog.text = "Não pensamos nisso. Atacamos pela entrada principal...";
			link.l1 = "Que pena. Eu estava contando com a cabeça dele. Uma lástima. Agora ele vai continuar agindo contra nós.";
			link.l1.go = "chimiset_3";
		break;
		
		case "chimiset_3":
			dialog.text = "I admit my guilt. But we couldn't follow him onto the hostile ships. You will have our friendship and respect instead of Chad's head. From now on, you are allowed to visit our territory freely. Chimiset's wisdom will serve you well too; talk to him if you need anything. Also, give the admiral my assurances that I appreciated his actions.";
			link.l1 = "Tudo bem.";
			link.l1.go = "chimiset_4";
		break;
		
		case "chimiset_4":
			dialog.text = "Espere! Perdemos o Chad, mas encontrei alguns papéis na mesa dele, que ele estava estudando quando chegamos. Aqui estão. Talvez eles lhe sejam úteis, irmão branco.";
			link.l1 = "Ha! Talvez... Chad confie demais em papéis...";
			link.l1.go = "chimiset_5";
		break;
		
		case "chimiset_5":
			dialog.text = "Você será sempre bem-vindo aqui, amigo branco. Todos os Rivados serão avisados disso. Boa sorte!";
			link.l1 = "O mesmo pra você, Eddie...";
			link.l1.go = "chimiset_6";
		break;
		
		case "chimiset_6":
			DialogExit();
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			sld = CharacterFromID("Zikomo");
            LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, true);
			GiveItem2Character(pchar, "letter_chad");
			ChangeItemDescribe("letter_chad", "itmdescr_letter_aeva");
			GiveItem2Character(pchar, "letter_chad_1");
			ChangeItemDescribe("letter_chad_1", "itmdescr_letter_axel");
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			// // ривадосы не будут останавливать где просят пароль
			pchar.questTemp.Saga.SharkHunt = "dodson_whiskey"; // к Акуле
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "Chad_escape"; // ноду Акуле
			AddQuestRecord("SharkHunt", "33");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true); // закрыть вход к Дональду Гринспи
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Have you heard the latest news? The Rivados' insolence is out of control, they have attacked the admiral's prison and released their wizard!", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("Just think about it - those uppity Rivados dared to attack the 'Tartarus'! They say that the jailer, Chad Kapper, has escaped to the Narwhals...", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("This is the height of impudence, isn't it? Attacking a military facility of the admiral! Aye, looks like Black Eddie is getting stronger...", "LostShipsCity", 3, 2, "LSC", "");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
