// колдун ривадос - Чимисет
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
			link.l1 = "Não, deixa pra lá.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-------------------------------------в тюрьме на Тартарусе-----------------------------
		// вариант R
		case "KillChad":
			dialog.text = "Espere, pare! Por favor, me escute antes de cometer um erro terrível.";
			link.l1 = "Estou ouvindo...";
			link.l1.go = "KillChad_1";
			LAi_RemoveCheckMinHP(npchar); //убираем проверяльщик, если ещё есть
		break;
		
		case "KillChad_1":
			dialog.text = "Te mandaram me matar, não foi? Ouvi você conversando com o Chad lá em cima. Não te culpo – ele não te deixou escolha – mas você está enganado se acha que o Chad vai te deixar ir embora depois que eu morrer.";
			link.l1 = "Hm... e por que ele não faria isso? Só sei que meu futuro vai ser sombrio se eu não te matar.";
			link.l1.go = "KillChad_2";
		break;
		
		case "KillChad_2":
			dialog.text = "Você não vai ter futuro nenhum se me matar. Escuta, os Narvais e o Chad querem que eu suma, mas têm medo demais de mim para fazer isso eles mesmos – quem me matar vai ser amaldiçoado para sempre. Por isso querem que alguém faça o serviço por eles.\nChad sabe que você não é Rivados. Ele está te enganando. Assim que me matar, eles vão fazer o mesmo com você e usar seu corpo para enganar o Tubarão.";
			link.l1 = "Tubarão?! Tubarão Dodson? Ele está aqui? E pelo amor de Deus, me diz, quem diabos são esses Rivados?";
			link.l1.go = "KillChad_3";
		break;
		
		case "KillChad_3":
			dialog.text = "Você não estava mentindo... você é novo aqui... hmm... Mas agora não é hora de explicações! Temos que fugir. Eu tenho um plano, vai me ouvir?";
			link.l1 = "Não. Sabe de uma coisa, feiticeiro? Acabei de atravessar um portal místico e sobrevivi, então suas maldições não me assustam. Me desculpe – vou tentar fazer isso sem dor.";
			link.l1.go = "KillChad_fightfail";
			link.l2 = "Certo, vou ouvir. Qual é o seu plano?";
			link.l2.go = "KillChad_4";
		break;
		
		case "KillChad_fightfail":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "afraid", "", -1);
			LAi_SetImmortal(npchar, false);
			pchar.quest.LSC_fightfail.win_condition.l1 = "NPC_Death";
			pchar.quest.LSC_fightfail.win_condition.l1.character = "Chimiset";
			pchar.quest.LSC_fightfail.function = "LSC_Fightfail_Final";
		break;
		
		case "KillChad_4":
			dialog.text = "There is a chest over there. It contains decent weapons and potions. It is locked, but the lock is old and damaged, so find a crowbar and break it.\nTake everything from the chest, arm yourself, and go to the stairs. It is a good defensive position; they will be forced to fight you one at a time - just watch out for the musketeers.\nI hope that you are good with a blade, I am too old to help you fight. If you manage to kill them all and survive, I guarantee you the protection of the Rivados - my family.";
			link.l1 = "Very well... pray to your gods for me; this fight will not be easy. Those lads upstairs don't look soft.";
			link.l1.go = "KillChad_5";
		break;
		
		case "KillChad_5":
			DialogExit();
			pchar.quest.LSC_fightfail.over = "yes"; //снять прерывание
			LAi_SetImmortal(npchar, true);
			ref location = &Locations[FindLocation(pchar.location)];
			location.private1.key = "crowbar";
			location.private1.key.delItem = true;
			NextDiag.CurrentNode = "KillChad_6";
		break;
		
		case "KillChad_6":
			dialog.text = "Não perca tempo! Arrombe a fechadura, rápido!";
			link.l1 = "Sim, sim, estou fazendo isso!";
			link.l1.go = "exit";
			NextDiag.TempNode = "KillChad_6";
		break;
		
		case "Chad_die":
			dialog.text = "Muito bem! Você é realmente um mestre guerreiro. Minha vida está em dívida com você, forasteiro. Diga-me, qual é o seu nome?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+". E o seu?";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "Eu sou Chimiset, xamã dos Rivados e conselheiro do nosso chefe, Black Eddie. Ele vai ficar feliz em saber que você me libertou e salvou minha vida. Você é um amigo para mim, para Black Eddie e para todos os Rivados. De agora em diante, você será sempre um convidado bem-vindo no Protetor...";
			link.l1 = "Espere... Chimiset, caso ainda não tenha entendido, faz só algumas horas que cheguei aqui! Pode me explicar onde estou, quem são esses Rivados, e onde posso encontrar o Tubarão Dodson?";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "This place is called the City of Abandoned Ships - though that name is a mockery; it is not much of a city.\nThis place is an island formed out of hundreds of dead ships. The central wrecks form our dwelling space. The island's inhabitants are people who survived the shipwrecks caused by the storms and currents that circle the island.\nMy Rivados are a clan, a group of free blacks who have been living together for a long time. There are three other groups who live here: the Narwhal clan, descended from the men who brought our African ancestors here; Shark Dodson's pirates; and the commoners, who keep to themselves.\nShark may be considered chief of the island, calls himself 'Admiral.' He arrived quite recently and seized power violently. He captured the San Augustine, where the island stores its provisions. Now, we have to buy our own food back at the prices named by Shark. Based on what I overheard between you and Chad, it seems that you have already been in the pirate warehouse.\nChad Kapper was Shark's boatswain and prison warden. Together with Layton Dexter, Shark's first mate, these men and their pirates formed one of the three controlling powers on the island, together with my Rivados and the Narwhals.";
			link.l1 = "Por que o Chad Kapper queria que eu te matasse?";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "Chad struck a bargain with the Narwhals, the sworn enemies of the Rivados. With their help, he was going to kill Shark and take his place.\nThe Narwhals hold a grudge against the Admiral for the murder of their leader, Alan Milrow. They believe that Shark is responsible, but they are wrong. Chad murdered Alan; I am the sole witness to this crime.\nThat is why Chad wished me dead, yet he feared to do it himself. Pirates are fearless in battle, but they respect big magic. So he tried to use you.\nChad and the Narwhals would have killed Shark and blamed the Rivados.";
			link.l1 = "Por que te culpar?";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = ""+pchar.name+", vamos conversar depois. Precisamos nos apressar, antes que os piratas do Tubarão apareçam. Revire o corpo do Chad e pegue as chaves dele. E dê uma olhada na mesa dele, pode ser que tenha papéis importantes lá.\nVá até o Tubarão Dodson, você vai encontrá-lo no San Augustine, um navio grande no extremo norte da ilha. Tem uma ponte de corda que liga ele ao Pluto. Diga a ele que Chad estava tramando traí-lo, que os Narvais estão por trás de tudo isso, que nós, os Rivados, não temos nada a ver com isso.\nTerei prazer em te contar tudo o que quiser saber assim que vier me ver no Protector. Vamos embora!";
			link.l1 = "Certo, Chimiset. Eu te encontro depois na... na Protetora. Vamos!";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "Mais uma coisa: nossos navios, inclusive o Protetor, são proibidos para estranhos. Você precisa ser Rivados ou saber nossa senha para entrar. Eu até te diria, mas ela muda toda semana, e já estou aqui faz tempo demais, então não sei a senha atual.  Visite primeiro o San Augustine. Vou avisar nosso pessoal quem você é, enquanto você conversa com o Tubarão. Estaremos esperando por você. Fique longe do Protetor até falar com o Tubarão!";
			link.l1 = "Entendi. Vou para San Augustine. Até logo!";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.LSC_LetterChad.win_condition.l1 = "item";
			pchar.quest.LSC_LetterChad.win_condition.l1.item = "letter_chad";
			pchar.quest.LSC_LetterChad.function = "LSC_LetterChad_Find";
			sld = characterFromId("SharkMush_17");
			sld.lifeday = 0;
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("SharkSold_1"+(i+3));
				sld.lifeday = 0;
			}
			AddSimpleRumourCityTip("They say that you are a friend of clan Rivados. Interesting... congratulations.", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that you saved the Rivados wizard Chimiset from Tartarus. Now, you are a welcome guest on their ships.", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("So, it was you who set Chimiset free! Interesting. Now you are a friend of Rivados but an enemy of Narwhals. I'm not sure whether to congratulate or pity you...", "LostShipsCity", 5, 1, "LSC", "");
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "O que você quer de mim, estranho?";
			link.l1 = "Seu nome é Chimiset, certo?";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "Sim, sou eu. Você tem algum assunto comigo?";
			link.l1 = "Sim. Vim a mando do Almirante, Tubarão Dodson, com uma ordem para te libertar, mas com uma condição: você precisa responder às minhas perguntas.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Dodson decidiu me libertar? Fico feliz em saber disso – isto é, se não for uma armadilha.";
			link.l1 = "Não é truque, mas preciso da sua ajuda. Me diga, Chimiset, existe algum ídolo indígena nesta ilha, que é de pedra durante o dia e se transforma em ouro à meia-noite? Não pense que estou louco...";
			link.l1.go = "Friend_2";
		break;
		
		case "prisoner_3":
			dialog.text = "Mais alguma pergunta?";
			link.l1 = "Sim. Você conhece um homem chamado 'Garoto Branco'?";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "Garoto Branco? Claro, eu conheço ele. É o Ole Christiansen. Já está crescido, não parece mais um menino, embora a cabeça ainda seja de criança.";
			link.l1 = "É mesmo? Me diga, onde posso encontrá-lo?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "Você pode encontrá-lo com frequência na loja do Axel Yost, na taverna do Carpentero ou simplesmente andando pelas ruas. Ele é pálido, tem cabelos brancos e um jeito simples. Você vai reconhecê-lo.";
			link.l1 = "Excelente! Mais uma pergunta: você chegou a conhecer um homem chamado Nathaniel Hawk por aqui? Ele deve ter aparecido por aqui há algum tempo e pode estar gravemente doente.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			dialog.text = "Não conheço nenhum homem com esse nome. Posso te garantir que ele não está nos navios dos Rivados, e também não o vi nas áreas comuns.\nAgora, sobre os territórios dos Narvais, não posso dizer nada. Os Rivados não vão até lá.";
			link.l1 = "Entendi. Bem, obrigado pela ajuda, Chimiset!";
			link.l1.go = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "E o Tubarão vai me libertar agora?";
			link.l1 = "Sim. Não tenho mais nada a lhe perguntar. Chad Kapper vai libertar você. Bem, preciso ir...";
			link.l1.go = "prisoner_8";
		break;
		
		case "prisoner_8":
			dialog.text = "Pare! Volte.";
			link.l1 = "Sim? Pensou em mais alguma coisa?";
			link.l1.go = "prisoner_9";
		break;
		
		case "prisoner_9":
			dialog.text = "Não exatamente... (abaixando a voz) Vejo que você não é um dos homens do Kapper. Não confie nele. Ele é um assassino.\nHá pouco tempo, ele matou Alan Milrow, desarmado, a sangue frio. Ele era o líder do clã Narval. Eu vi da minha cela: Chad simplesmente entrou e esfaqueou ele.\Ouvi rumores de que alguns dos próprios homens do Almirante planejam assassiná-lo. Avise o Tubarão – e diga que eu contarei mais quando ele e eu conversarmos cara a cara.";
			link.l1 = "Hum. Tudo bem, vou contar isso ao Dodson. Até mais!";
			link.l1.go = "prisoner_10";
		break;
		
		case "prisoner_10":
			DialogExit();
			sld = characterFromId("Capper");
			sld.quest.chimiset_talk = "true"; // разговор с Чимисетом состоялся
			if (!CheckAttribute(npchar, "quest.capper_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_10"; // ноду Акуле
			LSC_SetWhiteBoy(); // поставим белого мальчика
			NextDiag.CurrentNode = "prisoner_11";
			AddQuestRecord("SharkHunt", "20");
		break;
		
		case "prisoner_11":
			dialog.text = "Vá até o Tubarão e conte tudo o que eu te disse. Espero que me tirem desta jaula em breve...";
			link.l1 = "Estou a caminho.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_11";
		break;
		
		//------------------------беседа на Протекторе, если был старт через Тартарус-----------------
		case "Friend":
			dialog.text = "Aí está você, meu amigo! Mais uma vez, obrigado por me salvar e por confiar em mim em vez do Kapper.\nPegue estes amuletos como recompensa pelo seu esforço. Tenho certeza de que serão úteis para você.";
			link.l1 = "Obrigado! Eu não esperava por isso...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			GiveItem2Character(pchar, "indian_1");
			GiveItem2Character(pchar, "indian_11");
			GiveItem2Character(pchar, "amulet_1");
			PlaySound("interface\important_item.wav");
			dialog.text = "E agora podemos conversar. Você tinha perguntas para mim, não é?";
			link.l1 = "Certo. Preciso da sua ajuda. Chimiset, não pense que enlouqueci... mas existe um ídolo indígena nesta ilha, que é de pedra durante o dia, mas que se transforma em ouro à meia-noite?";
			link.l1.go = "Friend_2";
		break;
		
		// нода пересечения
		case "Friend_2":
			dialog.text = "I do not think you mad; there was such an idol.\nThough, it turns to gold under the morning sun's rays, and remains stone the rest of the day and night...\nMany times we brought wicked Narwhals to the idol, and it devoured each and every one. But no longer.";
			link.l1 = "Não mais... você está dizendo que o ídolo sumiu?";
			link.l1.go = "Friend_3";
		break;
		
		case "Friend_3":
			dialog.text = "O ídolo estava a bordo do San Geronimo. Esse navio afundou, levando o ídolo junto, há alguns anos.";
			link.l1 = "Merda! Eu estava contando com o ídolo pra sair desta ilha... E onde aquele navio estava?";
			link.l1.go = "Friend_4";
		break;
		
		case "Friend_4":
			dialog.text = "Não muito longe do território dos Narvais, perto dos destroços do Fênix. Em dias claros, dá pra ver o San Geronimo repousando no fundo do mar.";
			link.l1 = "Ah! Então está encalhado no banco de areia? Posso nadar até lá, então--";
			link.l1.go = "Friend_5";
		break;
		
		case "Friend_5":
			dialog.text = "Você não pode, meu amigo. Primeiro, é fundo demais. Segundo, há muitos caranguejos gigantes. Eles vão te despedaçar antes que você chegue ao San Geronimo.";
			link.l1 = "Argh... muito bem, vou ter que pensar sobre isso. Pelo menos agora sei que a estátua existe, e onde ela está.";
			if (CheckAttribute(npchar, "quest.chimiset_die")) link.l1.go = "prisoner_3";
			else
			{	
				if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_1";
				else link.l1.go = "Friend_6";
			}
			AddQuestRecord("LSC", "4");
		break;
		// нода пересечения
		
		case "Friend_6":
			dialog.text = "Vejo que você tem mais perguntas. Pergunte, meu amigo.";
			link.l1 = "O Shark Dodson me pediu para encontrar os cúmplices do Chad. Achei uma carta no baú do Chad. Fala sobre um atirador e um rifle. Parece que querem assassinar o Shark de longe. O que você acha, Chimiset?";
			link.l1.go = "Friend_7";
		break;
		
		case "Friend_7":
			dialog.text = "They are going to shoot the Admiral? Hmm, let me think... Thing is, the Admiral almost never leaves his residence, and when he does, he is protected by half a dozen pirates.\nBut... he likes to walk around the stern gallery late in the evening; it's his habit.\nThere are two places that provide an angle on the Admiral's residence: the bow of the Santa Florentina and the mast of the Fury. Even so, no marksman I know of could make such a shot.\nHe would have to be eagle-eyed indeed, and he would need an excellent rifle. You should ask around the island for people who have access to such firearms.";
			link.l1 = "A carta mencionava um... um stutzen. Você viu alguém com uma arma dessas?";
			link.l1.go = "Friend_8";
		break;
		
		case "Friend_8":
			dialog.text = "Não. Nunca ouvi falar de uma arma dessas. Pergunte por aí – talvez alguém saiba de algo que nós não sabemos.";
			link.l1 = "Certo. Suas informações foram valiosas, obrigado. Ah, uma última pergunta... você conhece alguém chamado 'White Boy'?";
			link.l1.go = "Friend_9";
		break;
		
		case "Friend_9":
			dialog.text = "Garoto Branco? Sim, esse é o apelido do Ole Christiansen. Ele já é adulto agora e não parece mais um garoto, embora sua cabeça ainda seja de uma criança.";
			link.l1 = "Então, ele é um tolo? Me diga, onde posso encontrá-lo?";
			link.l1.go = "Friend_10";
		break;
		
		case "Friend_10":
			dialog.text = "Você pode encontrá-lo com frequência na loja do Axel Yost, na taverna do Carpentero ou andando pelas ruas. Ele é pálido, tem cabelos brancos e um jeito simples. Você vai reconhecê-lo.";
			link.l1 = "Ótimo. Obrigado, Chimiset, você foi de uma ajuda enorme!";
			link.l1.go = "Friend_11";
		break;
		
		case "Friend_11":
			dialog.text = "Sempre fico feliz em ajudar um amigo dos Rivados. Venha me procurar se tiver mais perguntas.";
			link.l1 = "Eu vou - por agora, preciso ir. Adeus!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_2";
			else link.l1.go = "Friend_12";
		break;
		
		case "Friend_12":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
			pchar.questTemp.Saga.SharkHunt = "search_mush_1"; // флаг на магазин - поиск мушкета
			AddQuestRecord("SharkHunt", "11");
		break;
		
		case "freedom":
			dialog.text = "E aqui está quem devo minha liberdade e minha vida. Obrigado por ajudar meus irmãos a me salvar daquele assassino, Kapper.\nPegue estes amuletos como uma forma de agradecimento pelo que fez. Tenho certeza de que serão úteis para você.";
			link.l1 = "Obrigado! Eu não esperava por isso...";
			link.l1.go = "Friend_1";
		break;
		
		case "freedom_1":
			dialog.text = "O que mais posso fazer por você hoje?";
			link.l1 = "Me diga, Chimiset, você conhece alguém chamado 'Garoto Branco'?";
			link.l1.go = "Friend_9";
		break;
		
		case "freedom_2":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
		break;
		
		//--> информационный блок
		case "Chimiset_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Oh! Meu amigo "+pchar.name+"! Disseram que você tinha se afogado! Parece que os loa simpatizaram com você...";
				link.l1 = "Estou vivo e bem, Chimiset. Obrigado pela sua preocupação. Quanto aos seus loa, talvez você tenha razão – eles certamente cuidaram de mim quando passei por Kukulcan...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "O que te traz aqui, meu amigo?";
			/*if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l1 = "Me conte como o líder dos Narvais morreu. Só você viu o que aconteceu.";
				link.l1.go = "story";
			}*/
			if (!CheckAttribute(npchar, "quest.crab"))
			{
				link.l2 = "Você mencionou caranguejos lá embaixo perto do San Geronimo. O que são eles?";
				link.l2.go = "crab";
			}
			link.l9 = "Nada, Chimiset. Só queria te ver, meu amigo.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "story":
			dialog.text = "Vou escrever tudo como testemunhei.";
			link.l1 = "Obrigado.";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "crab":
			dialog.text = "No one knows where they came from, or why they have reached such gigantic size. In fact we know little about these beasts.\nGroups of them can be found among the shipwrecks, living in shallow water, but most of them stalk the bottom of the sea, eating fish and any garbage we toss overboard.\nThey are a menace; their pincers can sever limbs and their jaws contain a dangerous poison, similar to that which saturates the bodies of barracuda. If left untreated, crab bites are lethal. Fortunately, the toxin can be counteracted by any common antidote or mixture.\nThere once was a crab hunter among us - a brave man who dove to the bottom to kill crabs in their own domain. He used to bring us their meat, which makes a delicious dish. He also brought me their poison, which formed a key ingredient in some of my potions.\nIt's a great pity he went to his creator - he was loved and envied by all.";
			link.l1 = "Como ele morreu?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "Comido pelos próprios caranguejos que caçava. Eu te aviso: tome cuidado com essas criaturas.";
			link.l1 = "Eu vou.";
			link.l1.go = "exit";
			npchar.quest.crab = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		//<-- информационный блок
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
