// пещерные энкаунтеры
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, sGroup;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	sTemp = "CaveBandos" + locations[FindLocation(npchar.location)].index + "_";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Você quer alguma coisa?";
			link.l1 = "Não, nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "CaveBanditosSit":
			if (hrand(2) == 1) 
			{
				dialog.text = NPCStringReactionRepeat("Opa, olha só quem apareceu! Pois é, hoje é seu dia de sorte, camarada. Somos gente boa, tá vendo, só preparando uma comida e tal... Não vou te convidar pro nosso jantar, mas é melhor você sumir enquanto ainda pode.","Vaza daqui agora e não enche. Volte amanhã – e não esqueça de trazer sua bolsa, ha-ha-ha!","Não me irrite, marinheiro! Ainda se lembra onde fica a entrada da caverna? É melhor ir pra lá agora, bem, bem rápido...","Pois é, agora você passou dos limites, camarada! Acho que vou ter que largar meus assuntos e cuidar de você, seu desgraçado!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Tão gentil da sua parte, camarada...","Vejo que você gosta de fazer piada...","Certo, continue fritando suas panquecas, então...","Agora sim, ha-ha!",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Opa, céus! Não precisa sair caçando presa - ela já está aqui... Ei, pessoal - vamos dar uma prensa nesse almofadinha, que tal?","Ninguém te convidou aqui, camarada... Mas que bom que você apareceu, mesmo assim. Agora vamos ver o quão pesada está a sua bolsa!","Ninguém te arrastou até aqui à força, heh-heh... Mas já que você está aqui, acho que vamos te dar uma cutucada pra ver o que cai dos seus bolsos...");
				link.l1 = LinkRandPhrase("Agora vou deixar sua língua um pouco mais curta...","Espero que sua habilidade com a espada esteja à altura da sua língua afiada, tagarela!","Bem, parece que chegou a hora de abrir mais alguns buracos nesse seu corpo perecível...");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveBanditosSit";
		break;
		
		case "CaveBanditosStay":
			dialog.text = LinkRandPhrase("Opa, santo Deus! Nem precisa sair caçando presa - ela já está aqui... Ei, pessoal - vamos dar uma prensa nesse almofadinha, que tal?","Ninguém te convidou pra cá, camarada... Mas até que é bom te ver aqui, de qualquer jeito. Vamos ver agora o quão pesada está a sua bolsa!","Ninguém te trouxe aqui à força, he-he... Mas já que você está aqui, acho que vamos te dar uma cutucada pra ver o que cai dos seus bolsos...");
			link.l1 = LinkRandPhrase("Agora vou encurtar um pouco a sua língua...","Espero que sua habilidade com a espada seja tão boa quanto sua língua afiada, tagarela!","Bem, parece que chegou a hora de abrir mais alguns buracos nesse seu corpo perecível...");
			link.l1.go = "fight";
		break;
		
		case "CaveBanditosTreasure":
			dialog.text = NPCStringReactionRepeat("Cai fora, camarada. Não tem nada pra você fazer aqui!","Olha, estou pedindo numa boa: cai fora. Nunca se sabe o que pode acontecer...","Último aviso: se você não sumir daqui agora, vai se arrepender de ter vindo.","É isso aí, camarada, você pediu por encrenca.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Não me diga o que fazer, tá bom?","E o que tem de tão especial lá embaixo? Só uma caverna, nada além disso...","Ah, qual é agora...","Ha! Então vamos ver quem é melhor, verme!",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "CaveBanditosTreasure";
		break;
		
		case "CaveCaribSit":
			if (hrand(2) == 2) 
			{
				dialog.text = NPCStringReactionRepeat("Cara-pálida, vá embora. Ele vai ficar feliz que "+npchar.name+"  bondoso. Os deuses têm piedade de você hoje.","Saia da minha caverna antes que meus irmãos e eu fiquemos bravos!","Fora daqui, cachorro de cara pálida!","Sua sorte e sua vida acabaram, cachorro branco!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Bem, obrigado, camarada, isso é muita gentileza da sua parte...","Esta caverna não é sua, e eu vou onde quiser.","Se acalma aí, criatura do pântano.","Agora vou enfiar essas palavras de volta na sua garganta, animal...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Olha só, um cara-pálida amaldiçoado apareceu na nossa fogueira! Que beleza! Você tá acabado!","Branquelo tolo, você veio parar na toca do jaguar. Vou fritar seu fígado!","Rostinho pálido insolente ousa entrar na minha caverna? Então nunca vai sair daqui com vida!");
				link.l1 = LinkRandPhrase("Agora eu vou arrancar sua língua...","Agora o mundo vai ter alguns canibais a menos...","Bem, parece que chegou a hora de abrir mais alguns buracos nesse seu corpo perecível, seu macaco de cara vermelha.");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveCaribSit";
		break;
		
		case "CaveCaribStay":
			dialog.text = LinkRandPhrase("Rosto-pálido nojento veio até nossa caverna! Whe-hee! Vou arrancar sua língua e fritá-la!","Branco idiota veio até a toca do jaguar. Irmãos, acabem com esse maldito cachorro branco!","Rostinho pálido insolente ousa entrar na minha caverna? Então nunca vai sair daqui com vida!");
			link.l1 = LinkRandPhrase("Eu vou cortar a sua cabeça maldita...","Agora o mundo vai ter alguns canibais a menos...","Então, prepare-se para encontrar seus ancestrais, pele-vermelha. Vá para o inferno!");
			link.l1.go = "fight";
		break;
		
		case "exit_talk":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
		break;
		
		case "fight":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "CaveEnc_RaidersAfrer");
			chrDisableReloadToLocation = true;
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
