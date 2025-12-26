// Чад Каппер - боцман Акулы и тюремщик
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
			dialog.text = "Quer alguma coisa?";
			link.l1 = "Não, nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// вариант R
		case "Chimiset":
			dialog.text = "Então, então... Então você é o ladrão misterioso? Hmm... você não parece um ladrão qualquer.";
			link.l1 = "Senhor, o senhor está enganado. Acabei de chegar aqui, então como eu poderia saber que o porão onde seus homens me pegaram era propriedade sua?";
			link.l1.go = "Chimiset_1";
		break;
		
		case "Chimiset_1":
			dialog.text = "Ah é? Boa tentativa, camarada... Então, de onde você veio?";
			link.l1 = "Vim das Índias Ocidentais, por causa de um ídolo indígena... Não sei bem como explicar...";
			link.l1.go = "Chimiset_2";
		break;
		
		case "Chimiset_2":
			dialog.text = "Estátua? Ha-ha! Você é um sujeito engraçado, não é...? Deixa eu adivinhar: você nadou pelo buraco no casco do navio pra se esgueirar até nosso depósito. Mas por que será que não reconheço seu rosto? Eu conheço todos os Rivados...";
			link.l1 = "Rivados? Não faço ideia do que você está falando! Olha, cheguei aqui faz mais ou menos uma hora--";
			link.l1.go = "Chimiset_3";
		break;
		
		case "Chimiset_3":
			dialog.text = "Não grite, não sou surdo. Não, por mais engraçado que você ache que é, acho que vou te deixar aí um pouco. Quem sabe você muda de ideia depois que os ratos roerem seus dedos dos pés.";
			link.l1 = "Eu não sei nada sobre esses Rivados! Meu nome é Charles de Maure!";
			link.l1.go = "Chimiset_4";
		break;
		
		case "Chimiset_4":
			dialog.text = "Hm... talvez você esteja dizendo a verdade... os Rivados não costumam trabalhar com homens brancos. Me responda sem rodeios... você é um deles?";
			link.l1 = "Eu juro pra você, nunca ouvi esse nome antes! Não estou trabalhando com ninguém!";
			link.l1.go = "Chimiset_5";
		break;
		
		case "Chimiset_5":
			dialog.text = "Sério? Tudo bem. Prove. Desça as escadas, tem um Rivados sentado numa cela. Ele é um feiticeiro perigoso. Mate-o, e eu vou acreditar em você. \nTambém vou esquecer sua pequena invasão ao nosso depósito. E então, o que vai ser? Não tenha medo, o feiticeiro está desarmado e fraco. Bem... talvez ele te transforme em pó com um feitiço, he-he...";
			link.l1 = "Se você tivesse visto o que eu vi, não estaria brincando--";
			link.l1.go = "Chimiset_6";
		break;
		
		case "Chimiset_6":
			dialog.text = "Tudo bem, chega! Vai fazer isso ou não? Se sim, então pegue esse facão e derrube o feiticeiro. Caso contrário, vai morrer nas profundezas do Tártaro. Entendeu?";
			link.l1 = "... me dê o facão.";
			link.l1.go = "Chimiset_7";
		break;
		
		case "Chimiset_7":
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "slave_02");
			EquipCharacterbyItem(pchar, "slave_02");
			dialog.text = "Bom garoto. Agora, vá e mate o feiticeiro negro do vodu. A cela dele está destrancada. Não tente nada estúpido agora — não vamos hesitar em acabar com você se sequer pensar em fugir. Agora vá!";
			link.l1 = "Com medo que eu abra vocês com esse pedaço de ferro enferrujado?";
			link.l1.go = "Chimiset_8";
		break;
		
		case "Chimiset_8":
			dialog.text = "A minha paciência está se esgotando, camarada. Vai para o porão de carga e faz o que te mandaram!";
			link.l1 = "Tudo bem, tudo bem, já estou indo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//разлочим Ф2
		break;
		
		case "Chimiset_9":
			dialog.text = "Você está testando a minha paciência, idiota! É melhor não me irritar...";
			link.l1 = "T-tá, calma.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
		break;
		
		case "Fightfail_Final":
			dialog.text = "Você matou o negro? Ótimo... Fico feliz. Você provou que não é dos Rivados.";
			link.l1 = "Será que finalmente vou sair desta maldita lata? Preciso ver o Tubarão Dodson imediatamente.";
			link.l1.go = "Fightfail_Final_1";
		break;
		
		case "Fightfail_Final_1":
			dialog.text = "Você vai vê-lo... no caminho para o inferno.";
			link.l1 = "... merda.";
			link.l1.go = "Fightfail_Final_2";
		break;
		
		case "Fightfail_Final_2":
			DialogExit();
			DoQuestCheckDelay("LSC_ChadGuardAttack_Fail", 0.1);
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "Ha! Olha só. O que você está fazendo na minha prisão?";
			link.l1 = "Seu nome é Chad Kapper, certo? Eu sou "+GetFullName(pchar)+", estou aqui a mando do Tubarão Dodson. Ele me deu as chaves.";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "O Almirante te mandou? Hmph. Agora você é o novo faz-tudo dele?";
			link.l1 = "Cuide da sua língua, senhor... ou vai acabar perdendo ela. Não sou criado de ninguém.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Ha-ha! Gostei de você, camarada. Esquece o que eu disse... Então, o que te traz aqui?";
			link.l1 = "O Tubarão ordenou que Chimiset fosse libertado.";
			link.l1.go = "prisoner_3";
		break;
		
		case "prisoner_3":
			dialog.text = "O feiticeiro vodu dos Rivados? Hm, que estranho... Estou mesmo surpreso em ouvir isso...";
			link.l1 = "Tubarão quer fazer as pazes com os Rivados.";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "A-ah, I see... Fine. I'll send a man to Rivados; they can come and collect their wizard.";
			link.l1 = "Por que você simplesmente não pode soltá-lo?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "Claro que eu poderia... se quisesse ver ele morto. Chimiset é conhecido por aqui. A vida dele não vale nada assim que pisar no convés do Esmeralda — território dos inimigos dele, os Narvais. Não tem outro jeito de sair do Tártaro, e não dá pra fazer o velho nadar em volta da ilha! E se acontecer alguma coisa com ele, os Rivados vão culpar a gente — especialmente a mim! Não quero esse tipo de problema, então só libero ele se o próprio clã dele assumir a responsabilidade pela segurança dele. Quer falar com o Chimiset pessoalmente? Ele é uma figura e tanto...";
			if (CheckAttribute(npchar, "quest.chimiset_talk")) link.l1 = "Já conversei com ele. Ele é mesmo estranho... Bem, preciso ir. Adeus, Chad.";
			else link.l1 = "É o que pretendo. Vou vê-lo agora.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			DialogExit();
			sld = characterFromId("Chimiset");
			sld.quest.capper_talk = "true"; // разговор с Каппером состоялся
			if (!CheckAttribute(npchar, "quest.chimiset_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "Vou mandar um mensageiro para os Rivados e eles vão vir buscar o feiticeiro deles. Fica tranquilo, amigo, pode ir.";
			link.l1 = "Tudo bem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_7";
		break;
		
		// вариант M
		case "Aeva_attack":
			dialog.text = "... já deve ter aberto o barril, tenho certeza. É o uísque favorito dele: Bushmills. Logo tudo vai acabar, coloquei arsênico suficiente naquele tonel pra matar um elefante...";
			link.l1 = "";
			link.l1.go = "Aeva_attack_1";
			CharacterTurnToLoc(npchar, "quest", "quest2");
		break;
		
		case "Aeva_attack_1":
			dialog.text = "Hmm? Droga, o que você está fazendo aqui?! Cai fora!";
			link.l1 = "Estava procurando por você, envenenador. Estranho, não vejo o Ciclope... Você queria tomar o lugar do Tubarão, não é?";
			link.l1.go = "Aeva_attack_2";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Aeva_attack_2":
			dialog.text = "Ha-ha, o Tubarão provavelmente já está morto! E logo você vai se juntar a ele, espião!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Aeva_attack_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("ChadNarval_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CapperDieAeva");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Aeva_attack_2":
			dialog.text = "... this is going to be a hell of a drink. Shark's been dreaming of this whiskey so long, he'll down it in a single draught. Where's the arsenic? We'll use two bottles, just to be sure... then our friend Fazio can deliver this barrel to the Admiral as a present from tje Narwhals, ha-ha!\nAm I right, dear Giuseppe? Chin up, lad; you do this right, and you've got nothing to worry abou-- Ah! We have company, boys! What do you want, jackass? This is a private get-together.";
			link.l1 = "Seu plano fracassou, Kapper. Eu sei o que você e seu amigo Marcello estão tramando. Joguem fora o arsênico! Vocês não vão envenenar o Tubarão!";
			link.l1.go = "Aeva_attack_3";
		break;
		
		case "Aeva_attack_3":
			dialog.text = "Ah, merda. Tudo bem... você morre primeiro, depois o Tubarão! Às armas, rapazes!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
