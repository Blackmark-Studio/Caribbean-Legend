void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
	string sTemp;
	
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
		
		// =================================================================
		// ================== ЭТАП 1. «ЛОЩИНА ВЛЮБЛЁННЫХ» ==================
		// =================================================================
		case "Mary_1":
			dialog.text = ""+pchar.name+"Ei, olha aqui!";
			link.l1 = "Quiet, "+npchar.name+", a gente pode não estar sozinhos aqui.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_2":
			dialog.text = ""+pchar.name+"!";
			link.l1 = ""+npchar.name+"? Você me seguiu até aqui, sabe?";
			link.l1.go = "Mary_3";
		break;
		
		case "Mary_3":
			dialog.text = "E parece que eu estava certa em fazer isso, sabe? O que aconteceu aqui?";
			link.l1 = "Se eu soubesse, "+npchar.name+", se ao menos eu soubesse...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_4":
			dialog.text = "Meu Deus...";
			link.l1 = "Sim, parece que a pobrezinha sofreu antes de morrer. Ninguém merece um fim assim...";
			link.l1.go = "Mary_5";
		break;
		
		case "Mary_5":
			dialog.text = "E aquele é o marido dela ali? O que diabos eles estavam fazendo na selva?! Não ouviram falar dos escravos fugitivos?";
			link.l1 = "Acho que eles não vão mais poder responder essa pergunta...";
			link.l1.go = "Mary_6";
		break;
		
		case "Mary_6":
			dialog.text = "Você acha que quem fez isso ainda está por aqui, sabe?";
			link.l1 = "Bem possível. Então, é melhor falarmos baixo – precisamos vê-los antes que nos vejam.";
			link.l1.go = "Mary_7";
		break;
		
		case "Mary_7":
			dialog.text = "Tarde demais, "+pchar.name+". Parece que já fomos vistos. Olha ali.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "Olha só, rapazes, vejam isso. Parece até um cantinho de namorados, né, heh-heh. Mal dois pombinhos batem as botas, já aparece outro casal pra ocupar o lugar deles...";
			if (GetOfficersQuantity(pchar) >= 2)
			{
				link.l1 = "Muito esperta. Mas você não sabe contar, não? Ao contrário daqueles coitados, a gente não está sozinha aqui.";
				link.l1.go = "Naemnik_2";
			}
			else
			{
				link.l1 = "Olha, lidar com a gente vai ser um pouco mais complicado, pode confiar em mim nisso...";
				link.l1.go = "Naemnik_4";
			}
		break;
		
		case "Naemnik_2":
			dialog.text = "Eu até queria dizer que você é mais esperto que eles – mas isso seria uma mentira descarada, sabe? Mesmo com seus homens, você não teria vencido aqueles desgraçados. E sua garota bonita teria acabado igualzinha à que está caída aí aos seus pés...";
			link.l1 = "Você está falando dos escravizados fugitivos? Essa pessoa aqui é um deles? Então, vocês são do grupo do Bishop?";
			link.l1.go = "Naemnik_3";
		break;
		
		case "Naemnik_3":
			dialog.text = "Sim, pra todas as suas perguntas. Por mais de dois dias, a gente perseguiu eles pela ilha inteira com os soldados. Aí, aqueles desgraçados se separaram. Uns recuaram pra caverna, com os guardas indo atrás, e o resto correu pra baía. Eles armaram uma emboscada pra gente a uns oitocentos metros daqui, e perdemos alguns homens. Enquanto a gente se reorganizava e tentava entender o que estava acontecendo, eles... fizeram o que quiseram com aquela garota tola...";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		
		case "Naemnik_4":
			dialog.text = "Guarde seu palito pra você, almofadinha—não vem me encher, nem aos caras. Queria ver se ia te ajudar em alguma coisa se você estivesse cercado por uma dúzia daqueles desgraçados que a gente derrubou na baía. Só um deles teve sorte—mas não por muito tempo... Assim que aquele infeliz cair nas mãos do Bishop...";
			link.l1 = "Então vocês são os mercenários dele?";
			link.l1.go = "Naemnik_5";
		break;
		
		case "Naemnik_5":
			dialog.text = "Bom, com certeza não foram os soldados da guarnição. Se não fosse por aqueles preguiçosos, a gente teria pegado os canalhas ontem—e aquele idiota e a esposa dele ainda estariam vivos...";
			link.l1 = "Então, isso não é coisa sua...";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Quem você pensa que a gente é, hein? Olha, a gente não é santo, mas quando bate vontade, a gente vai num bordel, não...";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		case "Naemnik_6_add":
			StartInstantDialog("WildRose_Naemnik_Rab", "Naemnik_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_7":
			dialog.text = "Ele está mentindo, mentindo descaradamente – esse canalha imundo! Não escuta ele, "+GetAddress_Form(NPChar)+"! Nós não encostamos um dedo nessas pobres almas!";
			link.l1 = "Ah, é mesmo? E por que a gente deveria acreditar em você e não nele?";
			link.l1.go = "Naemnik_8";
			link.l2 = "Sabe? Ou talvez seja você quem está mentindo, afinal? Você não me parece nenhum santo.";
			link.l2.go = "Naemnik_9";
		break;
		
		case "Naemnik_8":
			dialog.text = "Ah, pensa um pouco, pelo amor de Deus! A gente tava fugindo daquele monstro do Bishop, dois dias vagando pela selva, apagando nossos rastros – pra quê? Pra agora atacar uma pobre mulher e deixar aqueles sanguessugas alcançarem a gente?! Meus amigos mal conseguiram chegar naquela praia, "+GetAddress_Form(NPChar)+"! A gente nem teve forças pra disparar nossos mosquetes, sabe? Se não, nunca teríamos deixado aqueles canalhas fazerem o que fizeram... Foram eles, a gente viu tudo!.. ";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Naemnik_9":
			dialog.text = "Poxa, pensa um pouco, pelo amor de Deus! A gente tava fugindo daquele monstro do Bispo, passou dois dias na mata, apagando nossos rastros – pra quê? Pra agora envergonhar uma pobre senhora e deixar aqueles sanguessugas alcançarem a gente?! Meus amigos mal conseguiram chegar naquela praia, "+GetAddress_Form(NPChar)+"! A gente nem tinha forças pra atirar com nossos mosquetes, sabe? Senão nunca teríamos deixado aqueles canalhas fazerem o que fizeram... Foram eles, a gente viu tudo!.. ";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		case "Naemnik_9_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_10":
			dialog.text = "Cala a boca, Casper, seu vira-lata sarnento!";
			link.l1 = "...";
			link.l1.go = "Naemnik_10_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab"));
		break;
		case "Naemnik_10_add":
			StartInstantDialog("Mary", "Naemnik_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_11":
			dialog.text = "O que você disse?!";
			link.l1 = "...";
			link.l1.go = "Naemnik_11_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_11_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_12":
			dialog.text = "Você é surda, moça? Eu mandei ele calar a boca. O nosso Jerry consegue inventar histórias por horas – ele tem um talento de verdade pra isso! O Bishop queria arrancar a língua dele e fazer ele engolir, mas acabou ficando com pena. Uma pena, se quer saber!";
			link.l1 = "...";
			link.l1.go = "Naemnik_12_add";
			CharacterTurnByChr(npchar, CharacterFromID("Mary"));
		break;
		case "Naemnik_12_add":
			StartInstantDialog("Mary", "Naemnik_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_13":
			dialog.text = "Mas... Você chamou ele de Casper, sabe...";
			link.l1 = "...";
			link.l1.go = "Naemnik_13_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_13_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_14":
			dialog.text = "Escuta aqui, camarada, explica pra sua namorada que as pessoas, até canalhas como esse fedelho, têm mais do que só um primeiro nome. Já ouvi dizer que mulher bonita pode ser burra feito uma porta, mas aí já é demais...";
			link.l1 = "...";
			link.l1.go = "Naemnik_14_add";
			CharacterTurnByChr(npchar, pchar);
		break;
		case "Naemnik_14_add":
			StartInstantDialog("Mary", "Naemnik_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_15":
			dialog.text = "Ah, você vai pagar por essas palavras, sabe!";
			link.l1 = "Mary, espera! Eu resolvo isso sozinha. Guarda sua arma. Agora.";
			link.l1.go = "Naemnik_15_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "normal to fight", "1", 2.5);
			DoQuestFunctionDelay("WildRose_Etap1_EscapeSlaves_6_1", 3.0);
		break;
		case "Naemnik_15_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_16":
			dialog.text = "Ah, então temos um verdadeiro cavalheiro aqui. Olha, seus modos são bem mais decentes do que os gritos daquele verme. Ele berrava mais alto que a pobre esposa dele – dava pra ouvir até atrás daquela colina, sabe? Pra falar a verdade, ele até ajudou a gente um pouco – foi assim que rastreamos aqueles desgraçados...";
			link.l1 = "Aqui no Caribe, nobreza é coisa rara. Agora, vamos respirar fundo—não tem nada de nobre em encontrar seu criador bem aqui e agora.";
			link.l1.go = "Naemnik_17";
			link.l2 = "Os únicos canalhas aqui são vocês. Peçam desculpas para a Mary agora, e talvez a gente consiga evitar qualquer derramamento de sangue.";
			link.l2.go = "Naemnik_22";
		break;
		
		case "Naemnik_17":
			dialog.text = "É difícil discordar disso. Mas antes, acalma seu...";
			link.l1 = "O nome dela é Mary Casper. Acho que isso já diz muita coisa.";
			link.l1.go = "Naemnik_18";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Naemnik_18":
			dialog.text = "Casper? Ela é filha dele ou algo assim, sabe? Ha-ha!";
			link.l1 = "Duvido muito disso. Mas espero que agora você entenda e retire o que disse.";
			link.l1.go = "Naemnik_19";
		break;
		
		case "Naemnik_19":
			dialog.text = "Voltou? Ou o quê? Vai me desafiar pra um duelo? Vai lá... Se não tiver medo de deixar sua preciosidade sozinha no meio da selva, hehe. Eu e os rapazes íamos ficar beeem felizes com isso.";
			link.l1 = "Aí está, mostrando quem você realmente é. A fachada não durou muito, né?";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_22":
			dialog.text = "Você, moço, é mesmo uma contradição – tão tranquilo, e ao mesmo tempo tão grosseiro. E por que, me diga, eu deveria estar pedindo perdão pra essa ruiva maluca aqui?";
			link.l1 = "O nome dela é Mary Casper, e...";
			link.l1.go = "Naemnik_23";
		break;
		
		case "Naemnik_23":
			dialog.text = "Casper? Ora, não é possível! Jerry, por acaso essa é sua filhinha, hein? Ha-ha-ha-ha! Não acredito no que estou ouvindo! Quem diria!";
			link.l1 = "Pode rir enquanto pode. Homens como você – só sabem falar grosso, mas não têm educação – tratam as mulheres como lixo e acham que isso é diversão. Deve ter nascido num celeiro e sido criado por chacais – isso explica seus modos. Mas, sabe, quando a cabeça é cheia de palha, não sobra muito espaço pra decência.";
			link.l1.go = "Naemnik_24";
		break;
		
		case "Naemnik_24":
			dialog.text = "Olha só... Que verme atrevido. Me diz, camarada, sua garota é boa numa rede?  Embora, pensando bem, tenho minhas dúvidas... mas eu adoraria descobrir por conta própria.";
			link.l1 = "Aí está, mostrando quem você realmente é. A fachada não durou muito, né?";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_7");
		break;
		
		case "Djerry_1":
			dialog.text = "Você realmente deu uma surra neles, "+GetAddress_Form(NPChar)+", - esses canalhas. Que queimem no inferno! Pena que não consegui te ajudar a tempo. O mosquete que vi no caminho estava longe demais. Parece que algum dos nossos deixou cair quando a gente fugia pra salvar a pele. Queria eu mesma ter dado um tiro naquele desgraçado do Primer.";
			link.l1 = "Parece que o Primer estava mesmo pegando no seu pé pra você decidir voltar, sabe?";
			link.l1.go = "Djerry_2";
		break;
		
		case "Djerry_2":
			dialog.text = "Isso é pouco, sabe? Aquele desgraçado é o motivo dessas cicatrizes nas minhas costas. O pior é que ele podia negar água pra gente quando bem quisesse.";
			link.l1 = "Que pena que nenhum daqueles desgraçados sobreviveu. A gente podia ter entregado ele pros soldados, que, tenho certeza, vão chegar logo.";
			link.l1.go = "Djerry_3_1";
		break;
		
		case "Djerry_3_1":
			dialog.text = "Eu não tenho muita certeza do porquê, sabe, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "Olha, sabe... O comandante teria arrancado uma confissão dele, limpando seu nome — e o nome dos seus amigos que morreram.";
			link.l1.go = "Djerry_4";
		break;
		
		case "Djerry_4":
			dialog.text = "Uhum, sei, haha. E aí o William Bishop arrancaria minha pele, sabe? Ouvi tudo isso de um cara negro lá na plantação... O Bishop não quer saber se você é preto ou branco – ele resolve rapidinho com qualquer um que tenta fugir, igualzinho.";
			link.l1 = "Receio que você vai ter que voltar para a plantação de um jeito ou de outro...";
			link.l1.go = "Djerry_5";
			link.l2 = "Então você não vai voltar para a plantação?";
			link.l2.go = "Djerry_6";
		break;
		
		case "Djerry_5":
			dialog.text = "Você é bem engraçado – já te disseram isso alguma vez, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Sem brincadeiras, "+npchar.name+". Você acha que eu vim parar aqui por acaso? Entrei na mata pra caçar sua turminha, arrastar todos vocês de volta pra plantação e ganhar umas moedas. Mas só sobrou você. Sozinho, você não vale quase nada, então talvez eu te deixe ir. Mas me diz, o que você tinha na cabeça? Você tá sozinho. O resto já era. O que você espera conseguir, hein, desgraçado? Vai ficar se escondendo nos morros e no mato até levar um tiro, morrer de febre ou virar comida de onça?";
			link.l1.go = "Djerry_8";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Djerry_6":
			dialog.text = "Você é bem engraçado – já te disseram isso alguma vez, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Sem piadas, "+npchar.name+". Você acha que eu vim parar aqui por acaso? Entrei na mata pra caçar a sua turminha, arrastar todo mundo de volta pra plantação e ganhar um troco. Mas só sobrou você. Sozinho, você não vale quase nada, então talvez eu te deixe ir. Mas me diz, o que você tinha na cabeça? Você tá sozinho. O resto já era. O que você espera conseguir, hein, desgraçado? Vai ficar se escondendo no mato até levar um tiro, morrer de febre ou virar comida de onça?";
			link.l1.go = "Djerry_8";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Djerry_8":
			dialog.text = "Melhor assim, Deus sabe, "+GetAddress_Form(NPChar)+" - Se quer saber, acho que esse é um destino bem melhor do que morrer com as torturas que o Bispo tinha preparado pra mim. Mas, sinceramente, nem é tão ruim assim – tem um barco com vela escondido perto do Pontal Esfarrapado.";
			link.l1 = "As terras mais próximas de Barbados são Dominica, com seus nativos, e Tobago, com os espanhóis. Nem sei dizer o que seria pior pra você...";
			link.l1.go = "Djerry_9";
		break;
		
		case "Djerry_9":
			dialog.text = "Acho que vou arriscar com os espanhóis – contrabandistas e piratas costumam ancorar em Tobago. Ah, já vi esse olhar de reprovação, "+GetAddress_Form(NPChar)+". Mas eu servi meu país fielmente. O que eu deveria fazer quando ele me jogou nas pedreiras?";
			link.l1 = "Não estou julgando, "+npchar.name+"Todo mundo tem seu próprio caminho. Agora pega mais pólvora e balas, e vai. Antes que os soldados apareçam.";
			link.l1.go = "Djerry_10";
		break;
		
		case "Djerry_10":
			dialog.text = "Obrigada, "+GetAddress_Form(NPChar)+". E você, mocinha, ah, Mary. (faz uma reverência). Claro, não somos parentes, mas encontrar alguém com o mesmo sobrenome numa, ah, situação dessas... é bem inesperado e...";
			link.l1 = "...";
			link.l1.go = "Djerry_10_add";
		break;
		case "Djerry_10_add":
			StartInstantDialog("Mary", "Djerry_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Djerry_11":
			dialog.text = "Acho que sim, sabe? E agora, adeus, Jerry.";
			link.l1 = "...";
			link.l1.go = "Djerry_12";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab_mushketer"));
		break;
		
		case "Djerry_12":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_9");
		break;
		
		case "Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", tem alguma coisa te incomodando? Você se despediu da sua xará rápido demais, sabe?";
			link.l1.go = "Mary_12";
		break;
		
		case "Mary_12":
			dialog.text = "Eu só queria me livrar da companhia daquele homem o mais rápido possível... A história dele é cheia de buracos, sabe.";
			link.l1 = "O que você está falando, querido?";
			link.l1.go = "Mary_13";
		break;
		
		case "Mary_13":
			dialog.text = "Depois do que ouvimos do capanga do Bispo, não tenho dúvida de que aquelas pobres almas morreram por causa dele. Mas antes disso... Casper – você estava prestando atenção no que ele dizia?";
			link.l1 = "E o que te incomodou, querido?";
			link.l1.go = "Mary_14";
		break;
		
		case "Mary_14":
			dialog.text = "Ele diz que tem um barco escondido na praia. Mas mais de vinte pessoas fugiram da plantação. Então o barco deve ser bem grande, né? O Jerry é um desertor da marinha, ele sabe muito bem que não é fácil cuidar de um barco grande sozinho, sabe...";
			link.l1 = "Tudo o que ele precisa fazer é içar a vela e manter o rumo – o vento faz o resto. Claro, ele está se arriscando de verdade, mas talvez morrer no mar seja mesmo melhor do que nas mãos de um carrasco de fazenda.";
			link.l1.go = "Mary_15";
		break;
		
		case "Mary_15":
			dialog.text = "Talvez. Mas agora percebo que tem outra coisa que não faz sentido... Segundo ele, ele e os amigos ficaram olhando de longe enquanto os mercenários abusavam daquela pobre garota...";
			link.l1 = "Em vez de correrem feito loucos pro barco deles... Sabe, já entendi onde você quer chegar com isso, "+npchar.name+". Talvez a gente devesse fazer mais algumas perguntas para o Sr. Casper...";
			link.l1.go = "Mary_15_add";
		break;
		case "Mary_15_add":
			StartInstantDialog("WildRose_Naemnik_Rab_mushketer", "Mary_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Mary_16":
			dialog.text = "...";
			link.l1 = " Ei, "+npchar.name+", velho amigo! Espera um minuto...";
			link.l1.go = "Mary_17";
		break;
		
		case "Mary_17":
			dialog.text = "...";
			link.l1 = " Droga!!! Mary, cuidado!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_11");
		break;
		
		case "Mary_21":
			dialog.text = "Canalha miserável! Salvamos a vida dele, e ele! Então o que isso significa, "+pchar.name+"? Então, acontece que...";
			link.l1 = "Ai, "+npchar.name+", não tem mais ninguém vivo que saiba a verdade sobre o que aconteceu aqui...";
			link.l1.go = "Mary_22";
		break;
		
		case "Mary_22":
			dialog.text = "A gente devia sair daqui, "+pchar.name+". Se os soldados nos encontrarem aqui, vamos ter problemas.";
			link.l1 = "Você tem razão, Mary. Vamos...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_15");
		break;
		
		case "Mary_23":
			dialog.text = "Sabe, "+pchar.name+", depois de tudo isso, eu bem que preciso de uma boa bebida, sabe.";
			link.l1 = "Não vou discordar, querido. Eu mesma preciso de uma bebida. Vamos passar no ‘Cornudo Irlandês’.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_2");
		break;
		
		case "Barmen_1":
			dialog.text = "Desculpa te acordar, Capitão...";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Bom, pelo menos você bateu na porta, então já é alguma coisa. Agora fala logo—o que você quer de mim?";
				link.l1.go = "Barmen_2";
			}
			else
			{
				link.l1 = "Ainda bem que você pensou em bater, né? Se tivesse entrado sem avisar, já estaria rolando escada abaixo.\nTá olhando o quê? Fala logo—por que veio até aqui desse jeito?";
				link.l1.go = "Barmen_2";
			}
		break;
		
		case "Barmen_2":
			dialog.text = "Um dos moradores quer falar com você – Lewis Gernon. Ele disse que tem algo importante para conversar com você.";
			link.l1 = "Nunca ouvi esse nome antes. Espero que ele tenha mesmo algo importante, pra me tirar de... um trabalho desses. Deixa ele entrar...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_5");
		break;
		
		case "Lewis_1":
			dialog.text = "Oi, moço "+pchar.lastname+". Senhorita... Casper.";
			link.l1 = ""+TimeGreeting()+", moço "+npchar.lastname+". Eu não me lembro da gente ter se encontrado antes. Então, como você conhece a gente?";
			link.l1.go = "Lewis_2";
		break;
		
		case "Lewis_2":
			dialog.text = "Não lembra? Ah, entendi... Meu rosto estava coberto de sangue e poeira, eu mesma me assustei quando vi meu reflexo no espelho há poucas horas...";
			link.l1 = "...";
			link.l1.go = "Lewis_2_add";
		break;
		case "Lewis_2_add":
			StartInstantDialog("Mary", "Lewis_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_3":
			dialog.text = "Você... você é aquele homem, sabe, a gente te encontrou e...";
			link.l1 = "...";
			link.l1.go = "Lewis_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_3_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_4":
			dialog.text = "E a minha Susan. Minha pobre Suzie...";
			link.l1 = "...";
			link.l1.go = "Lewis_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_4_add":
			StartInstantDialog("Mary", "Lewis_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_5":
			dialog.text = "A gente achou que você tinha morrido. E... Ela era sua esposa, sabe?";
			link.l1 = "...";
			link.l1.go = "Lewis_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_5_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_6":
			dialog.text = "Sim, senhora. Ela era minha esposa, e eu fiquei paralisado de medo... e não consegui fazer nada. Meu Deus, meu Deus...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_8");
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		
		case "Lewis_7":
			dialog.text = "(chorando) Eles me bateram e me obrigaram a assistir...";
			link.l1 = "Levante-se, "+GetAddress_Form(NPChar)+". Você não tem culpa. Ninguém conseguiria enfrentar tantos canalhas sozinho, sabe?";
			link.l1.go = "Lewis_8";
		break;
		
		case "Lewis_8":
			dialog.text = "Eram tantos, tantos... Mas mesmo assim, eu...";
			link.l1 = "Mas ainda assim, você sobreviveu, e os assassinos da sua esposa estão queimando no inferno. É um consolo pequeno, mas é alguma coisa, senhor "+npchar.lastname+". Mas, sabe, tem uma coisa que eu queria te perguntar...";
			link.l1.go = "Lewis_9";
			LAi_ActorAnimation(npchar, "ground_standup", "WildRose_Etap1_City_8_1", 7);
		break;
		
		case "Lewis_9":
			dialog.text = "Sabe, moço "+pchar.lastname+"?";
			link.l1 = "Quem eram eles? Mercenários do Bispo ou escravizados fugitivos?";
			link.l1.go = "Lewis_10";
		break;
		
		case "Lewis_10":
			dialog.text = "Foi o Jeremy Casper e os outros fugitivos. Você estava enganado sobre o Bruce Primer e os homens dele.";
			link.l1 = "Mercenários do Bispo?";
			link.l1.go = "Lewis_11";
		break;
		
		case "Lewis_11":
			dialog.text = "Sim. O Bruce era mesmo um canalha e fazia muita coisa suja pro Bispo, mas ele não era estuprador";
			link.l1 = "Não foi assim que eu vi na hora. Mas não vou discutir com você, "+npchar.name+". Mas, já que você estava consciente e viu tudo, podia ter se levantado e...";
			link.l1.go = "Lewis_12";
		break;
		
		case "Lewis_12":
			dialog.text = "Me perdoa, "+GetAddress_Form(NPChar)+". Pode me chamar de covarde miserável – mas eu simplesmente não consegui me mexer, fiquei apavorada. Quando aqueles canalhas fecharam o caminho pra mim e pra Suzie, no começo eu só consegui gritar o mais alto que pude, torcendo pra alguém aparecer e ajudar.";
			link.l1 = "Eles te bateram.";
			link.l1.go = "Lewis_13";
		break;
		
		case "Lewis_13":
			dialog.text = "Jerry me acertou com a coronha do mosquete, depois disse que ia me cortar em pedaços bem na frente da Susan. Eu... tenho vergonha de admitir, mas acho que até apaguei por uns segundos de puro terror. E enquanto tudo isso acontecia...";
			link.l1 = "Eu entendo você, moço "+npchar.lastname+". Não há nada de vergonhoso no que você fez. Nem todo mundo teria suportado o que você passou. É uma pena que você não tenha interferido – mas o que está feito, está feito. Ainda assim, fico feliz que conseguimos mandar pelo menos um dos assassinos da sua esposa para o outro mundo – mesmo que ele quase tenha conseguido nos enganar.";
			link.l1.go = "Lewis_14";
			link.l2 = "Então a gente quase morreu lutando contra os mercenários do Bispo – só porque você ficou com medo, é isso? Que desculpa maravilhosa, "+npchar.name+". Ainda bem que conseguimos resolver as coisas no final, mesmo que tenha sido um pouco tarde...";
			link.l2.go = "Lewis_15";
		break;
		
		case "Lewis_14":
			dialog.text = "Sabe, "+GetAddress_Form(NPChar)+". Eu vim te agradecer por isso. Mesmo que no começo você tenha acreditado nele...";
			link.l1 = "Bruce Primer fez de tudo pra isso acontecer, sabe? Maldito. Se ao menos ele tivesse segurado a língua dele...";
			link.l1.go = "Lewis_16";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Lewis_15":
			dialog.text = "Sabe, "+GetAddress_Form(NPChar)+". Eu vim te agradecer por isso. Mesmo que no começo você tenha acreditado nele...";
			link.l1 = "Bruce Primer fez de tudo pra que isso acontecesse, sabe? Maldito seja. Se ao menos ele tivesse ficado de boca fechada...";
			link.l1.go = "Lewis_16";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Lewis_16":
			dialog.text = "Pois é, todos nós cometemos erros naquele dia... Eu e Susan não devíamos ter ido passear em Ragged Point, Bruce devia ter ficado calado... E você não devia ter confiado no Jeremy. Mas graças à senhorita Casper, a justiça foi feita.";
			link.l1 = "...";
			link.l1.go = "Lewis_16_add";
		break;
		case "Lewis_16_add":
			StartInstantDialog("Mary", "Lewis_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_17":
			sld = CharacterFromID("WildRose_Lewis");
			dialog.text = "Acho que sei o que você quer me perguntar, moço "+sld.lastname+". Mas eu não tenho nada a ver com esse homem.";
			link.l1 = "...";
			link.l1.go = "Lewis_17_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_17_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_18":
			dialog.text = "Eu sei, moça. Percebi assim que entrei nesta sala. Não há a menor semelhança entre você e ele. E mesmo assim, Susan... ela tinha certeza de que nada neste mundo acontece por acaso.";
			link.l1 = "...";
			link.l1.go = "Lewis_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_18_add":
			StartInstantDialog("Mary", "Lewis_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_19":
			dialog.text = "Sua esposa estava certa. Eu mesma já vi isso mais de uma vez, sabe. E também "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "Lewis_19_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_19_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_20":
			dialog.text = "...";
			link.l1 = "Tudo verdade. Mas, sabe?, acho que agora não é hora pra conversa filosófica. Duvido que isso vá te ajudar, "+npchar.name+". Só o tempo pode ajudar com algo assim.";
			link.l1.go = "Lewis_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), pchar);
			CharacterTurnByChr(CharacterFromID("Mary"), pchar);
		break;
		
		case "Lewis_21":
			dialog.text = "Talvez você tenha razão, moço "+pchar.lastname+". Bem, obrigada mais uma vez, e adeus. Vou rezar por você e pela senhorita Casper.";
			link.l1 = "Se cuida, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_10");
		break;
		
		case "Mary_31":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Eu sei, meu bem, eu quase deixei aquele desgraçado escapar...";
			link.l1.go = "Mary_32";
		break;
		
		case "Mary_32":
			dialog.text = "Um bastardo chamado Jerry Casper.";
			link.l1 = "Isso mesmo... Espera... você não tá querendo dizer que acha que ele...";
			link.l1.go = "Mary_33";
		break;
		
		case "Mary_33":
			dialog.text = "Eu sei que parece muito bobo...";
			link.l1 = "Com certeza! E se seu sobrenome fosse Smith ou Jones? Tem um monte de gente com esses nomes andando por aí – e alguns deles vão acabar fazendo alguma coisa ruim... E aquele Jerry, que ele apodreça no inferno – vai ver ele nem é um Casper de verdade...";
			link.l1.go = "Mary_34";
			link.l2 = "Isso mesmo, querido. Vai saber, ele nem era o tal do Jerry – podia muito bem ter usado um nome falso.";
			link.l2.go = "Mary_35";
		break;
		
		case "Mary_34":
			dialog.text = "E ainda assim... Eu sei que você não me entende, mas só imagina o que você pensaria se ele tivesse o seu sobrenome "+pchar.lastname+".";
			link.l1 = "Não é a mesma coisa, Mary. "+pchar.lastname+" – é um sobrenome nobre, e...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Mary_35":
			dialog.text = "E mesmo assim... Eu sei que você não me entende, mas só imagina o que você pensaria se ele tivesse o seu sobrenome "+pchar.lastname+".";
			link.l1 = "Não é a mesma coisa, Mary. "+pchar.lastname+" - um sobrenome nobre, e...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Mary_36":
			dialog.text = "E os Caspers, bem, a gente é só um bando de pessoas sem nome, sem família, sabe? Acho que eu devia agradecer a Deus todo dia por você ter reparado em mim, e não em alguma metida...";
			link.l1 = ""+npchar.name+", não foi isso que eu quis dizer – você entende, né? Membros de uma família nobre são ligados pelo sangue – e isso não tem nada a ver com só compartilhar um sobrenome com alguém. Porque, como eu disse, alguém pode simplesmente pegar esse nome pra si...";
			link.l1.go = "Mary_37";
		break;
		
		case "Mary_37":
			dialog.text = "Não é só sobre isso, "+pchar.name+"...";
			link.l1 = "Amor, a gente teve um dia longo e difícil. Andamos quilômetros pela selva, quase morremos... e mal conseguimos dormir. Não é de se estranhar que sua cabeça esteja cheia de pensamentos estranhos. Nós dois só precisamos de uma boa noite de sono, sabe?";
			link.l1.go = "Mary_38";
		break;
		
		case "Mary_38":
			dialog.text = "Eu não acho nada estranho, sabe... mas tudo bem, vamos conversar amanhã.";
			link.l1 = "De cabeça fria, a gente resolve tudo bem mais rápido. Deita aqui, meu bem, precisamos deixar esse dia pra trás.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_1");
		break;
		
		case "Waitress_1":
			dialog.text = "Você está bem, "+GetAddress_Form(NPChar)+"? Você está com uma cara estranha, como se tivesse visto um fantasma. Quer um pouco de rum? Ou vinho? Temos uma seleção excelente, sabe? E você bem que podia relaxar um pouco.";
			link.l1 = "Dane-se a bebida. Estou procurando uma garota...";
			link.l1.go = "Waitress_2";
		break;
		
		case "Waitress_2":
			dialog.text = "Então você veio ao lugar errado, Capitão. Aqui é uma taverna, não um bordel. É só sair lá fora que você vai ver, fica bem ali do outro lado da rua...";
			link.l1 = "Olha, não tô com paciência pra piada agora. Tô procurando uma garota ruiva, de gibão vermelho, tá armada. O nome dela é Mary Casper.";
			link.l1.go = "Waitress_3";
		break;
		
		case "Waitress_3":
			dialog.text = "Olha, se não é pra brincar, então não tenho nada pra te contar. Meu turno começou faz uma hora, e não vi nenhuma ruiva de casaco vermelho por aqui.";
			link.l1 = "Então ela foi embora à noite... Mas pra onde será que ela foi, sabe?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_4");
		break;
		
		case "Mary_41":
			dialog.text = "Bom dia, meu amor! Você dormiu bastante, sabe...";
			link.l2 = "Você realmente me deixou preocupada, "+npchar.name+". Não suma assim de novo, sem avisar...";
			link.l2.go = "Mary_43";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_43":
			dialog.text = "Eu não queria te acordar. E além disso, às vezes você também some assim, sem dizer nada...";
			link.l1 = "E você decidiu me pagar na mesma moeda?";
			link.l1.go = "Mary_44";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;
		
		case "Mary_44":
			dialog.text = "Pra ser sincera, eu só precisava de um tempo sozinha com meus pensamentos, sabe? Não queria que você se preocupasse.";
			link.l1 = "Tem alguma coisa te incomodando?";
			link.l1.go = "Mary_46";
		break;
		
		case "Mary_46":
			dialog.text = "Nossa conversa de ontem. Sobre sobrenomes, laços de sangue...";
			link.l1 = "Então, você está mesmo chateado comigo, né...";
			link.l1.go = "Mary_47";
		break;
		
		case "Mary_47":
			dialog.text = "De jeito nenhum, querido, não foi isso que eu quis dizer. É só que, de repente, percebi que não sei nada sobre a minha própria família. Você, por exemplo – é filho de uma casa nobre. Os rapazes do navio, de vez em quando, contam alguma história sobre as famílias deles. Mas eu – não tenho nada pra contar. Nunca conheci meus pais. Sabe, eu nem sei onde nasci...";
			link.l1 = "Não foi na Ilha da Justiça?";
			link.l1.go = "Mary_48";
		break;
		
		case "Mary_48":
			dialog.text = "Eric, o homem que me criou, sempre dizia isso. Mas se isso é verdade, por que ninguém na Ilha da Justiça nunca falou dos meus pais? Nem uma palavra, nem sequer uma menção de passagem. Uma vez perguntei ao Donald Greenspen sobre isso, mas ele não conseguiu me dar uma resposta clara.";
			link.l1 = "Ou talvez não quisesse.";
			link.l1.go = "Mary_49";
		break;
		
		case "Mary_49":
			dialog.text = "Exatamente! Eu pensei a mesma coisa, sabe? Olha, eu costumava só viver a vida, sem pensar muito nessas coisas. Mas ontem, quando a gente esbarrou naquele canalha do Jerry... eu me perguntei—quem era meu pai? Minha mãe? Por que nunca ninguém me falou deles, como se nunca tivessem existido? E se meu pai fosse tão canalha quanto aquele Jerry?";
			link.l1 = "Isso não importa nem um pouco, "+npchar.name+". Você foi criada por outras pessoas – e elas fizeram um ótimo trabalho.";
			link.l1.go = "Mary_50";
			link.l1 = "Duvido muito que seja isso. E não vejo por que isso importa, já que você nunca pareceu se importar com isso antes.";
			link.l1.go = "Mary_51";
		break;
		
		case "Mary_50":
			dialog.text = "Mas isso importa pra mim, "+pchar.name+", sabe? Eu quero, eu tenho o direito de saber quem foram meus pais. Você não acha?";
			link.l1 = "Claro que eu concordo, sem dúvida. Mas se a gente quiser descobrir qualquer coisa sobre seu pai e sua mãe, vai ter que ser na Ilha da Justiça. Afinal, você nem sabe o nome deles, né?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "Mary_51":
			dialog.text = "Mas isso importa pra mim, "+pchar.name+"Sim, sabe? Eu quero saber, eu tenho o direito de saber quem foram meus pais. Você não concorda?";
			link.l1 = "Claro, eu concordo, sem dúvida. Mas se a gente quiser descobrir alguma coisa sobre seu pai e sua mãe, vai ter que ser lá na Ilha da Justiça. Afinal, você nem sabe o nome deles, né?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Mary_52":
			dialog.text = "Eu não sei, querido. Não me lembro de já ter ouvido os nomes deles, sabe.";
			link.l1 = "Então ainda é cedo pra ir aos arquivos coloniais. Primeiro, a gente vai ter que voltar àquele cemitério de navios e tentar encontrar algum vestígio dos seus antepassados por lá.";
			link.l1.go = "Mary_53";
		break;
		
		case "Mary_53":
			dialog.text = "Fico feliz que você me entende, "+pchar.name+". Obrigada.";
			link.l1 = ""+npchar.name+", você realmente me surpreende, sabe. Isso é o mínimo que posso fazer por você, meu amor.";
			link.l1.go = "Mary_54";
		break;
		
		case "Mary_54":
			dialog.text = "De algum jeito, consegui viver quase vinte anos sem saber nada sobre eles...";
			// dialog.text = "Afinal, isso não me incomodou por mais de vinte anos...";
			link.l1 = "...";
			link.l1.go = "Mary_55";
		break;
		
		case "Mary_55":
			dialog.text = "Então, eu posso esperar mais um pouco.";
			link.l1 = "Eu vejo que isso é importante pra você, "+npchar.name+". Então, vou tentar não te fazer esperar, querido. Agora vamos, precisamos voltar para o navio. Vou me sentir melhor sabendo que você está lá, pelo menos.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_6");
		break;
		
		// ============================================================
		// ================== ЭТАП 2. «ДИТЯ ОСТРОВА» ==================
		// ============================================================
		case "Mary_61":
			dialog.text = "Costas de casa... Sabe, "+pchar.name+", Sabe, eu sinto que se a gente voltasse aqui daqui a dez anos, tudo estaria exatamente igual ao que está agora, né.";
			link.l1 = "Talvez, "+npchar.name+", talvez. Os navios do anel interno vão continuar flutuando, mas as pessoas que vivem aqui vão ser diferentes.";
			link.l1.go = "Mary_62";
			link.l2 = "Duvido muito, sabe? Aqui já está tudo por um fio. Graças ao gênio de um certo mecânico.";
			link.l2.go = "Mary_63";
		break;
		
		case "Mary_62":
			dialog.text = "E eu mal consigo lembrar das pessoas que viviam nesses destroços há dez ou quinze anos. Só das que eram mais próximas de mim—Alan, Eric...";
			link.l1 = "Acho que é assim mesmo, sabe? Não dá pra lembrar de tudo e de todos. Nomes e rostos também somem da minha memória – dos meus tempos em Paris, então, nem se fala de Gasconha. E eu achava que isso só acontecia com gente velha.";
			link.l1.go = "Mary_64";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Mary_63":
			dialog.text = "E eu mal consigo me lembrar de quem vivia nesses destroços há dez ou quinze anos. Só dos que eram mais queridos pra mim – Alan, Eric...";
			link.l1 = "Acho que é assim mesmo, sabe? Não dá pra lembrar de tudo e de todos. Até eu esqueço nomes e rostos dos meus tempos em Paris—quem dirá de Gasconha. E eu achava que isso só acontecia com gente velha.";
			link.l1.go = "Mary_64";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Mary_64":
			dialog.text = "Mas este lugar... É como se fosse outro mundo, né? Você acredita que alguns que chegaram aqui há pouco tempo dizem que o tempo aqui passa quase três vezes mais rápido do que no Continente...";
			link.l1 = "Ha-ha, então quantos anos isso te faz ter, sabe?";
			link.l1.go = "Mary_65";
		break;
		
		case "Mary_65":
			dialog.text = "Eu estava falando sério, "+pchar.name+", sabe!";
			link.l1 = "Bom, se é pra falar sério, então vamos ao que interessa. Tem alguém entre os Narvais mais velho que o Greenspen?";
			link.l1.go = "Mary_66";
		break;
		
		case "Mary_66":
			dialog.text = "Mmm, não, acho que não. Mas eu já te disse que ele não falou nada quando perguntei sobre isso, sabe?";
			link.l1 = "Mesmo assim, não tenho outra ideia de quem possa nos ajudar a entender o que aconteceu há vinte anos. Pelo menos, por enquanto. Então, vamos seguir rumo à 'Esmeralda'.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_2");
		break;
		
		case "Schmidt_1":
			dialog.text = "Ah, "+pchar.name+" e Mary, que surpresa! Que bom ver vocês dois... vivos e inteiros, heh-heh. Dois ou três navios naufragaram no anel externo só no mês passado – o mar anda bem agitado ultimamente. E olha, não vai arrombando porta trancada, senão quebra a droga da fechadura e sobra pra mim consertar. Vieram ver o Donald, né?";
			link.l1 = "E um bom dia pra você, amigo. Viemos aqui pra vê-lo pessoalmente. Mas, pelo jeito da porta trancada, ou ele mudou pra outro navio ou não quer ver velhos amigos, sabe?";
			link.l1.go = "Schmidt_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Schmidt_2":
			dialog.text = "Nem um, nem outro, haha. O Greenspen está no anel externo agora, treinando.";
			link.l1 = "Treinos? Sério? Ele está se preparando pra uma nova guerra com os Rivados?";
			link.l1.go = "Schmidt_3";
		break;
		
		case "Schmidt_3":
			dialog.text = "A guerra nunca acabou de verdade, "+pchar.name+". Não tem tido tantas brigas ultimamente como antigamente. Mas ainda assim, na taverna do Sancho, de vez em quando alguém acaba levando um soco na cara... e às vezes até uma faca aparece, sabe?";
			link.l1 = "Hmm, parece que os membros do clã não costumavam aparecer na taverna antes.";
			link.l1.go = "Schmidt_4";
		break;
		
		case "Schmidt_4":
			dialog.text = "Olha, algumas coisas mudaram desde que você saiu da Ilha da Justiça. O Donald e o Eddie estão conseguindo manter o pessoal sob controle. Por enquanto. Mas quem sabe o que o amanhã traz, né? É por isso que o velho Donny começou com tudo isso...";
			link.l1 = "Eu passei por tudo aquilo pra impedir um massacre na Ilha da Justiça, só pra você brincar de soldado aqui de novo? E faz quanto tempo que ele tá rondando o anel externo?";
			link.l1.go = "Schmidt_5";
			link.l2 = "Treinos são bons e tudo mais, mas será que isso não vai colocar em risco a trégua, que já tá por um fio? E faz quanto tempo que o Greenspen tá treinando os caras, sabe?";
			link.l2.go = "Schmidt_6";
		break;
		
		case "Schmidt_5":
			dialog.text = "Já faz três dias. Ele devia voltar até o meio-dia de amanhã. Do jeito que eles estão esfregando aqueles mosquetes ali, não vai sobrar nada pra atirar até de manhã! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Schmidt_6":
			dialog.text = "Já faz três dias. Ele deve voltar até o meio-dia de amanhã. Do jeito que eles estão esfregando aqueles mosquetes ali, amanhã não vai sobrar nada pra atirar! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Schmidt_5_add":
			StartInstantDialog("Mary", "Schmidt_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_7":
			dialog.text = "A minha cabine no 'Ceres Smithy' ainda está livre? Ou alguém já ocupou?";
			link.l1 = "...";
			link.l1.go = "Schmidt_7_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_7_add":
			StartInstantDialog("Schmidt_Clone", "Schmidt_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_8":
			dialog.text = "Está tudo igualzinho da última vez que você esteve lá. Nem chegamos a destrancar a porta. Pra ser sincera, também não limpamos nem lubrificamos a fechadura esse tempo todo. Então, se precisar arrombar, é só falar, sabe?";
			link.l1 = "...";
			link.l1.go = "Schmidt_8_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_8_add":
			StartInstantDialog("Mary", "Schmidt_9", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_9":
			dialog.text = "Claro. Obrigada, Jurgen.";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_3");
			
			//доп
		break;
		
		case "Mary_71":
			dialog.text = "E, de verdade, tudo está exatamente como era. Todas as minhas coisas estão no lugar onde deixei – como se eu nunca tivesse ido embora... Foi aqui que a gente se conheceu, "+pchar.name+". Lembra?";
			link.l1 = "Claro! Você lidou tão bem com aqueles dois, você lidou tão bem com aqueles dois, eu até fiquei com medo de acabar picada também.";
			link.l1.go = "Mary_72";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_72":
			dialog.text = "Não foi nada disso, sabe! Você literalmente me tirou das garras da morte!";
			link.l1 = "Parece que o destino me trouxe até aqui, até você.";
			link.l1.go = "Mary_73";
		break;
		
		case "Mary_73":
			dialog.text = "Você acha mesmo isso, querido?";
			link.l1 = "Claro, meu amor. E desde então, agradeço todos os dias por ter me trazido direto para a 'Ferraria Ceres'.";
			link.l1.go = "Mary_74";
		break;
		
		case "Mary_74":
			dialog.text = ""+pchar.name+"... Me diz, o que você pensou quando me viu pela primeira vez?";
			link.l1 = "Bem... Tudo o que eu lembro é que, quando aconteceu, parecia que meu coração ia saltar do peito. Você estava tão...";
			link.l1.go = "Mary_75";
		break;
		
		case "Mary_75":
			dialog.text = "O quê?";
			link.l1 = "Diferente de qualquer pessoa que já conheci. Sua graça, sua voz... e aquele gibão vermelho. Eu nunca tive chance contra você. Sabe, sempre fiquei curiosa: por que um gibão vermelho, e não um vestido ou um espartilho?";
			link.l1.go = "Mary_76";
		break;
		
		case "Mary_76":
			dialog.text = "Eu encontrei quando tinha nove anos, lá no anel externo. Naquela época, eu adorava me perder por lá—explorar tudo de novo, achar coisas que não dava pra conseguir na ilha, principalmente livros. Eu estava louca pra experimentar, mas naquela época, ia me engolir inteira. Então escondi junto com meus outros tesouros—num dos mastros de vigia que ficam pra fora d'água.";
			link.l1 = "E quando você cresceu, foi lá e pegou de volta?";
			link.l1.go = "Mary_77";
		break;
		
		case "Mary_77":
			dialog.text = "Alguns anos atrás, eu encontrei um livro sobre um capitão do mar destemido, de casaco vermelho. Ele não tinha medo de nada — enfrentou centenas de inimigos por amor à mulher da vida dele. Foi aí que eu experimentei o gibão pela primeira vez. Me faz sentir corajosa.";
			link.l1 = "E esse charme irresistível, meu bem! Mas sabe de uma coisa? Agora, só tem uma coisa que eu quero... tirar isso de você...";
			link.l1.go = "Mary_78";
		break;
		
		case "Mary_78":
			dialog.text = "O que você está esperando, meu capitão corajoso?";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_5");
		break;
		
		case "Mary_81":
			dialog.text = "Bom dia, querido. Os Narvais acabaram de voltar para a 'Esmeralda' e a 'San Gabriel', e o Donald está com eles. Eu vi ele em um dos barcos, sabe?";
			link.l1 = "Bom dia, bom dia... Sabe, depois de uma noite daquelas eu dormiria até meio-dia, mas você já está de pé, toda animada por aí.";
			link.l1.go = "Mary_82";
		break;
		
		case "Mary_82":
			dialog.text = "Ontem a gente falou sobre o gibão e o ninho do corvo, onde eu costumava esconder aquilo... E de repente bateu uma saudade enorme daqueles dias, quando eu me escondia lá em cima de todo mundo, só pra ler meus livros sobre o mundo lá fora em paz... Não resisti e fui até lá. Eu passava horas lá em cima, mas hoje... só fiquei vendo o sol nascer. E aí eu percebi: mais do que qualquer coisa nesse mundo, eu quero estar do seu lado.";
			link.l1 = "E eu pela sua, "+npchar.name+". Então, vamos até o Donald? Vamos ter muito o que conversar, sabe?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_7");
		break;
		
		case "Grinspy_1":
			dialog.text = ""+pchar.name+", Mary, que bom te ver! Já me contaram sobre a sua visita ontem. Eu até pensei em passar na ‘Ferraria Ceres’, mas você se adiantou a este velho aqui. Ah, se eu tivesse a sua idade...";
			link.l1 = "Bom, energia você tem de sobra, como a gente já viu. E os treinos, como foram?";
			link.l1.go = "Grinspy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_2":
			dialog.text = "Melhor do que eu esperava. Treinamos abordar navios inimigos, invadir as cabines... No geral, mandamos muito bem. Sabe?, eu peguei pesado com os rapazes, mas foi bom pra eles. Faz tempo que eles não se mexiam de verdade, nossa, já fazia uma eternidade, haha.";
			link.l1 = "E o que, posso perguntar, te inspirou a tais feitos? A Ilha ficou quieta demais pro seu gosto, né?";
			link.l1.go = "Grinspy_3";
		break;
		
		case "Grinspy_3":
			dialog.text = "Hum, consigo ouvir um tom de desaprovação na sua voz, "+pchar.name+". Suponho que você tem todo direito de estar...";
			link.l1 = "Sério, "+npchar.name+"?";
			link.l1.go = "Grinspy_4";
		break;
		
		case "Grinspy_4":
			dialog.text = "Você teve que correr bastante por esses destroços podres pra gente não acabar cortando a garganta um do outro – não esqueci disso. Ninguém esqueceu.";
			link.l1 = "E é assim que você retribui meus esforços? Acho que é verdade o que dizem – um verdadeiro guerreiro se sente sobrecarregado pela paz.";
			link.l1.go = "Grinspy_5";
			link.l2 = "E tenho que dizer, eu confiava muito mais no seu bom senso do que no dos piratas ou dos Rivados, sabe?";
			link.l2.go = "Grinspy_6";
		break;
		
		case "Grinspy_5":
			dialog.text = "Deixa eu terminar. Sim, a gente conseguiu manter a paz, mas nossas diferenças continuam aí. Pelo menos com aqueles pagãos de pele escura. Só na semana passada, um dos Narvais foi morto numa briga de taverna. Mas a gente fez questão de retribuir...";
			link.l1 = "Sim, sim - é sempre assim que tudo começa, sabe?";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_6":
			dialog.text = " Deixa eu terminar. Sabe, conseguimos manter a paz, mas nossas diferenças continuam aí. Pelo menos com aqueles pagãos de pele escura. Só na semana passada, um dos Narvais foi morto numa briga de taverna. Mas tratamos de retribuir à altura...";
			link.l1 = "Sabe, é sempre assim que tudo começa.";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_7":
			dialog.text = "Você está errando em duas coisas, "+pchar.name+". Primeiro de tudo, isso não está começando, está continuando. Se você achou ingenuamente que tinha colocado um fim nisso, estava enganado. E segundo, eu não sou santa pra virar a outra face. Os negros perderam a linha de novo, e eu não gosto disso. Nem o Dexter, aliás, mas ele resolveu que é um grande político e prefere ficar acima da confusão. Então, depois de pensar um pouco, escolhi o que acho ser a forma mais... indolor de manter uma paz frágil.";
			link.l1 = " Resolveu assustar os Rivados com seus treininhos, sabe?";
			link.l1.go = "Grinspy_8";
		break;
		
		case "Grinspy_8":
			dialog.text = "Algumas semanas atrás, um galeão inglês com uma carga militar apareceu na parte externa da Ilha da Justiça – você não vai acreditar no que tinha a bordo... Mas o principal eram cinquenta mosquetes novinhos em folha e uma pólvora de primeira. E os barcos também... A tinta deles nem tinha secado ainda! Os antigos estavam caindo aos pedaços, e depois das tempestades, quase não sobrou nenhum inteiro, sabe...";
			link.l1 = "E tudo isso virou propriedade dos Narvais?";
			link.l1.go = "Grinspy_9";
		break;
		
		case "Grinspy_9":
			dialog.text = "Talvez eu tivesse contado pro Almirante, mas como ele acha que é o mais esperto de todos, também não quero parecer uma boba, sabe? E olha, no fim das contas, meu plano funcionou.";
			link.l1 = "O Black Eddie te mandou uma carta prometendo que ia parar de abrir seus homens no meio?";
			link.l1.go = "Grinspy_10";
		break;
		
		case "Grinspy_10":
			dialog.text = "O Eddie Preto mandou os rapazes dele ficarem na deles. Eu achei que, na minha ausência, eles iam ficar ainda mais ousados—mas aconteceu o contrário: os Rivados estão quietos, mantendo distância tanto da minha tripulação quanto do povo da cidade, que eles costumavam incomodar de vez em quando. Negro é negro—só respeita força. Era o que o Alan sempre dizia, e que este navio afunde agora mesmo se ele estivesse errado!";
			link.l1 = "E se depois de um tempo eles começarem a aprontar de novo, você vai despejar chumbo das suas novas mosquetes na Fúria e no Protetor, só pra botar medo neles, sabe?";
			link.l1.go = "Grinspy_11";
		break;
		
		case "Grinspy_11":
			dialog.text = "A ideia é ousada e imprudente, sabe? Mas não acho que vai chegar a esse ponto. Talvez a gente só finja que está planejando atacar os navios deles – e aí o Layton finalmente cria coragem e entra em cena. Ele anda meio convencido, claro, mas não é burro. Destruir nosso clã ou os pretos não interessa pra ele – três centros de poder mais ou menos iguais mantêm as coisas pelo menos um pouco equilibradas. Se um deles cair, tudo vai pro inferno rapidinho. Tenho certeza que ele entende isso – mas por algum motivo, sou eu que tenho que fazer o trabalho dele por ele.";
			link.l1 = "Talvez eu passe lá pra ver ele enquanto a gente estiver aqui— a não ser, claro, que ele resolva começar um dos treinamentos dele em troca, né, haha.";
			link.l1.go = "Grinspy_12";
			link.l2 = "Vou tentar passar lá e conversar com ele sobre isso quando tiver uma chance. Vai saber, talvez ele me escute.";
			link.l2.go = "Grinspy_13";
		break;
		
		case "Grinspy_12":
			dialog.text = "Se alguém pode convencê-lo a manter os negros sob controle, é você, "+pchar.name+". Mas, pelo jeito de vocês, não vieram aqui pra falar de política. Então, fala logo, o que vocês querem?";
			link.l1 = "...";
			link.l1.go = "Grinspy_12_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Grinspy_12_add":
			StartInstantDialog("Mary", "Grinspy_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_13":
			dialog.text = "Meus pais, Donald.";
			link.l1 = "...";
			link.l1.go = "Grinspy_13_add";
		break;
		case "Grinspy_13_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_14":
			dialog.text = "Eu não entendo muito bem o que você quer de mim, Mary.";
			link.l1 = "...";
			link.l1.go = "Grinspy_14_add";
		break;
		case "Grinspy_14_add":
			StartInstantDialog("Mary", "Grinspy_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_15":
			dialog.text = "Me conta sobre eles, por favor. Você conheceu eles! Eu já te perguntei sobre eles uma vez, e você não quis me responder...";
			link.l1 = "...";
			link.l1.go = "Grinspy_15_add";
		break;
		case "Grinspy_15_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_16":
			dialog.text = "E é por isso que você decidiu arrastar o Charles pra cá, hahaha! Você é demais, garota, pode me fulminar se eu estiver mentindo! Se eu nunca te falei sobre seu pai e sua mãe, é só porque eu nunca conheci eles, só isso!";
			link.l1 = "...";
			link.l1.go = "Grinspy_16_add";
		break;
		case "Grinspy_16_add":
			StartInstantDialog("Mary", "Grinspy_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_17":
			dialog.text = "Mas você é o membro mais velho do nosso clã, sabe! Você está aqui desde que eu me entendo por gente...";
			link.l1 = "...";
			link.l1.go = "Grinspy_17_add";
		break;
		case "Grinspy_17_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_18":
			dialog.text = "Cheguei na Ilha da Justiça faz quase vinte anos, já depois de você ter nascido. Você era só uma coisinha, correndo e engatinhando debaixo das mesas e bancos, não dava um minuto de sossego pro pobre Eric Udette... Claro que perguntei pra ele de onde tinha vindo uma criatura tão inquieta – e ele me disse que você tinha nascido na Ilha alguns anos antes. Nunca falou nada sobre seu pai ou sua mãe. E se falou – olha, ou eu nem prestei atenção, ou simplesmente esqueci mesmo...";
			link.l1 = "...";
			link.l1.go = "Grinspy_18_add";
		break;
		case "Grinspy_18_add":
			StartInstantDialog("Mary", "Grinspy_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_19":
			dialog.text = " Já faz tantos anos... Eu entendo, Donald, de verdade.";
			link.l1 = "...";
			link.l1.go = "Grinspy_19_add";
		break;
		case "Grinspy_19_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_20":
			dialog.text = " É uma pena que o Eric não esteja mais entre nós – ele chegou aqui muito antes de mim. Sabe, quando ele falava das suas últimas aventuras, ele sempre mencionava a Orelie Bertine. Aquela velhinha te adorava, disso eu lembro bem... Pensando bem, acho que ela já morava na Ilha da Justiça quando você nasceu. Talvez ela possa te ajudar?";
			link.l1 = "...";
			link.l1.go = "Grinspy_20_add";
		break;
		case "Grinspy_20_add":
			StartInstantDialog("Mary", "Grinspy_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_21":
			dialog.text = " Talvez. É um motivo pra visitar ela. Faz tempo que não a vejo. Que falta de consideração minha, sabe!";
			link.l1 = "...";
			link.l1.go = "Grinspy_21_add";
		break;
		case "Grinspy_21_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_22":
			dialog.text = "Acho que ela não está chateada com você. Mas não força muito, ouvi dizer que ela não está bem. Não queremos que aconteça nada pior...";
			link.l1 = "...";
			link.l1.go = "Grinspy_22_add";
		break;
		case "Grinspy_22_add":
			StartInstantDialog("Mary", "Grinspy_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_23":
			dialog.text = "Quieto, Donald, você vai arrumar problema pra gente! A Orelie vai enterrar todos nós, sabe.";
			link.l1 = "...";
			link.l1.go = "Grinspy_24";
		break;
		
		case "Grinspy_24":
			dialog.text = "Vamos, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "Grinspy_24_add";
		break;
		case "Grinspy_24_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_25":
			dialog.text = "...";
			link.l1 = "Adeus, "+npchar.name+". Até logo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_9");
		break;
		
		//
		case "Jillian_1":
			dialog.text = "Senhor misericordioso, meu coração quase pulou do peito. Você não pode sair por aí assustando as pessoas assim, sabe?";
			link.l1 = "...";
			link.l1.go = "Jillian_1_add";
			DelLandQuestMark(npchar);
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_1_add":
			StartInstantDialog("Mary", "Jillian_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_2":
			dialog.text = "Jillian! Não esperava te ver aqui, sabe? O que você está fazendo aqui? E onde está a Orelie?";
			link.l1 = "...";
			link.l1.go = "Jillian_2_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_2_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_3":
			dialog.text = "E oi pra você também, Mary. E pra você, "+pchar.name+". A Orelie está doente, sabia? Estou cuidando dela a pedido do Irmão Julian. Ele me manda umas poções, e eu dou pra ela, mas... parece que não estão ajudando muito. Agora ela está na cabine, lá na popa, dormindo. Levei ela pra lá pra poder arrumar as coisas aqui.";
			link.l1 = "...";
			link.l1.go = "Jillian_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_3_add":
			StartInstantDialog("Mary", "Jillian_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_4":
			dialog.text = "Só ficamos sabendo hoje, sabe? O Donald contou pra gente. Como ela está?";
			link.l1 = "...";
			link.l1.go = "Jillian_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_4_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_5":
			dialog.text = "Não está bem. Ela reclama de fraqueza, mal sai da cama. Às vezes murmura umas coisas sem sentido, umas bobagens... Já ouvi tantas histórias de tempos que já se foram que até perdi a conta.";
			link.l1 = "...";
			link.l1.go = "Jillian_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_5_add":
			StartInstantDialog("Mary", "Jillian_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_6":
			dialog.text = "Hum, é exatamente esse tipo de história que viemos buscar. Espero que ela não se recuse a conversar com a gente...";
			link.l1 = "...";
			link.l1.go = "Jillian_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_6_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_7":
			dialog.text = "Isso é mesmo necessário, Mary? Acho que não deveríamos incomodá-la quando ela está assim.";
			link.l1 = "...";
			link.l1.go = "Jillian_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_7_add":
			StartInstantDialog("Mary", "Jillian_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_8":
			dialog.text = "Isto é sobre meus pais. A Orelie talvez tenha conhecido eles. Isso é muito importante pra mim, Jillian, sabe.";
			link.l1 = "...";
			link.l1.go = "Jillian_9";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "Jillian_9":
			dialog.text = "Não tem nenhum remédio na ilha que possa ajudar ela a melhorar?";
			link.l1 = "...";
			link.l1.go = "Jillian_9_add";
		break;
		case "Jillian_9_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_10":
			dialog.text = "Irmão Julian prepara as tinturas dela. Mas elas só ajudam por um tempo. E mesmo assim, ela se recusa a tomar, e eu praticamente tenho que forçar ela a engolir. Às vezes eu fico com medo dela engasgar – preciso fazer ela engolir tudo...";
			link.l1 = "...";
			link.l1.go = "Jillian_10_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_10_add":
			StartInstantDialog("Mary", "Jillian_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_11":
			dialog.text = "Pobre Orelie! Será que não tem mesmo ninguém na Ilha da Justiça que possa ajudar ela?";
			link.l1 = "...";
			link.l1.go = "Jillian_11_add";
		break;
		case "Jillian_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_12":
			dialog.text = " Você sabe tão bem quanto eu que não tem médico de verdade aqui. E o que poderia ser feito, sabe? A velhice não poupa ninguém... ";
			link.l1 = "...";
			link.l1.go = "Jillian_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_12_add":
			StartInstantDialog("Mary", "Jillian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_13":
			dialog.text = ""+pchar.name+", talvez a gente possa trazer alguém do nosso navio?";
			link.l1 = "Eu estou com medo, "+npchar.name+", o que a gente precisa aqui não é de um cirurgião de navio, mas de um médico de verdade, sabe?";
			link.l1.go = "Jillian_14";
		break;
		
		case "Jillian_14":
			dialog.text = "Eu tô pronta pra acreditar em magia agora se isso ajudar, sabe.";
			link.l1 = "Hmm... Magia? Talvez eu deva falar com a Chimiset...";
			link.l1.go = "Jillian_14_add";
		break;
		case "Jillian_14_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_15":
			dialog.text = "Chimiset? O feiticeiro negro? "+pchar.name+", você tá falando sério?";
			link.l1 = "Mais do que nunca. Se ele é negro ou branco é a última coisa que me importa agora. Não sei quem mais poderia ajudar a Orelie, e duvido que você saiba também. Então sai da frente, e nem pense em atrapalhar.";
			link.l1.go = "Jillian_16";
			link.l2 = "Com certeza. A medicina não ajudou em nada. Nem as orações do Irmão Julian. Chimiset é nossa última esperança.";
			link.l2.go = "Jillian_17";
		break;
		
		case "Jillian_16":
			dialog.text = "Eu não acredito no que estou ouvindo! Mas ele é... um homem sem Deus!";
			link.l1 = "E ela está morrendo – a um suspiro de esquecer o próprio nome. Sabe, ele é um feiticeiro, mas ouvi dizer que eles são capazes de muitas coisas. Coisas incríveis. E se ele pode trazer de volta a mente dela, importa mesmo qual deus ele adora?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_17":
			dialog.text = "Eu não acredito no que estou ouvindo! Mas ele é... um homem sem Deus!";
			link.l1 = " E ela está morrendo – a um suspiro de esquecer o próprio nome. Sabe, ele é um feiticeiro, mas ouvi dizer que eles são capazes de muita coisa. Coisas incríveis. E se ele pode devolver a mente dela, importa mesmo qual deus ele adora?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Jillian_18":
			dialog.text = ""+pchar.name+", escuta, eu também me importo com a Orelie... Deus é minha testemunha – estou fazendo tudo que posso pra aliviar o sofrimento dela! Mas você vai mesmo deixar aquele herege negro fazer o ritual dele aqui na cabine? E se ele botar fogo no navio, ou resolver sacrificar alguém durante isso?";
			link.l1 = "Não vamos deixar isso acontecer, "+npchar.name+", eu te garanto.";
			link.l1.go = "Jillian_19";
		break;
		
		case "Jillian_19":
			dialog.text = "E eu garanto pra vocês dois, se alguém descobrir isso... Vocês têm ideia do que pode acontecer aqui? O resto do pessoal não vai gostar nada, principalmente os Narvais!";
			link.l1 = "Você tem razão sobre isso. Não devemos trazer Chimiset aqui, temos que levar Orelie até ele.";
			link.l1.go = "Jillian_20";
		break;
		
		case "Jillian_20":
			dialog.text = "Você não viu ela – a velha mal consegue ficar de pé. Vai ser um milagre se ela não cair no mar!";
			link.l1 = "Bem, às vezes tudo que podemos fazer é esperar por um milagre. E, Jillian...";
			link.l1.go = "Jillian_21";
		break;
		
		case "Jillian_21":
			dialog.text = "O que mais?";
			link.l1 = "Espero que você guarde isso pra você. Você é uma mulher esperta, e entendeu tudo direitinho... A confusão na Ilha da Justiça pode facilmente virar um banho de sangue, e ninguém quer isso, né?";
			link.l1.go = "Jillian_22";
			link.l2 = "Nem uma palavra para ninguém. Entendeu? Confiamos em você – não nos faça nos arrepender disso. Acho que você sabe tão bem quanto eu que, se isso vazar, a Ilha da Justiça vai ver um massacre como nunca antes.";
			link.l2.go = "Jillian_23";
		break;
		
		case "Jillian_22":
			dialog.text = "Sabe? Mas então se certifique de que ninguém veja você arrastando ela para o 'Protetor'... Senão eu vou ter que responder umas perguntas bem complicadas.";
			link.l1 = "Vamos poupar você do constrangimento de dar respostas embaraçosas. Vamos fazer isso hoje à noite.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Jillian_23":
			dialog.text = "Sabe? Mas então, faz o favor de não deixar ninguém te ver arrastando ela pro 'Protetor'... Senão eu é que vou ter que responder umas perguntas bem chatas.";
			link.l1 = "Não vamos deixar isso acontecer. Vamos fazer isso à noite.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_24":
			dialog.text = "Vem depois da meia-noite. Ela vai estar aqui. E, pelo amor de Deus, toma cuidado.";
			link.l1 = "Você não precisa se preocupar, "+npchar.name+", eu prometo que nós seremos, sabe?";
			link.l1.go = "Jillian_25";
		break;
		
		case "Jillian_25":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10");
		break;
		
		case "Jillian_26":
			if (GetHour() >= 3 && GetHour() <= 24)
			{
				dialog.text = "Venha depois da meia-noite. Ela vai estar aqui...";
				link.l1 = "Sabe?";
				link.l1.go = "exit";
				NextDiag.TempNode = "Jillian_26";
			}
			else
			{
				dialog.text = "A Orelie está pronta. Você pode levá-la.";
				link.l1 = "Sabe? Então vamos.";
				link.l1.go = "exit";
				DelLandQuestMark(npchar);
				AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10_2");
			}
		break;
		
		case "Oreli_1":
			dialog.text = "Jovens, onde... onde estamos indo?! Este é um navio Rivados! Onde está o Eric?!";
			link.l1 = "O Eric ficou amigo do Eddie Black, sabia?";
			link.l1.go = "Oreli_2";
		break;
		
		case "Oreli_2":
			dialog.text = "O que você tá dizendo, garoto! O Eric não suporta gente preta!";
			link.l1 = "Olha só, quem diria! Sabe? Então vamos lá perguntar pra ele que diabos ele tá fazendo aqui!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_11");
		break;
		
		case "Eddy_1":
			dialog.text = "Olha só quem veio nos visitar! "+GetFullName(pchar)+" Em carne e osso! Que bom ver meu irmão branco, haha! Então, o que te traz aqui?";
			link.l1 = "E oi pra você, "+npchar.name+" . Queria poder passar aqui só pra tomar um gole de rum, sabe? Mas receio que tenho um assunto urgente com você—ou melhor, com Chimiset.";
			link.l1.go = "Eddy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Eddy_2":
			dialog.text = "Estamos para sempre em dívida com você, meu amigo. Vamos fazer tudo o que pudermos para ajudar.";
			link.l1 = "Que bom ouvir isso. Porque eu não tenho mais ninguém a quem recorrer.";
			link.l1.go = "Eddy_3";
		break;
		
		case "Eddy_3":
			dialog.text = "Com qual dessas moças você precisa de ajuda, "+pchar.name+"?";
			link.l1 = "Eu não sei se você está falando sério ou só brincando, "+npchar.name+", mas eu não tô com cabeça pra piada agora. Quem precisa de ajuda é a Orelie, claro.";
			link.l1.go = "Eddy_3_add";
		break;
		case "Eddy_3_add":
			StartInstantDialog("LSC_Oreli", "Eddy_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_4":
			dialog.text = "Eric! ERIC! Apareça, seu preguiçoso! Que história é essa?! Traga essa bunda magrela aqui agora mesmo!";
			link.l1 = "...";
			link.l1.go = "Eddy_4_add";
		break;
		case "Eddy_4_add":
			StartInstantDialog("Eddy", "Eddy_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_5":
			dialog.text = "Então é verdade, né... O pessoal me disse que esse lugar aqui tem um parafuso a menos. Agora vejo que não era mentira. Mas ainda não entendi direito o que você quer dos Rivados...";
			link.l1 = "Deixa eu falar com o Chimiset, e você vai entender tudo...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_12");
		break;
		
		case "Chimset_1":
			dialog.text = "Fala, meu querido amigo. Estou pronta pra te ouvir com atenção.";
			link.l1 = "Vou ser breve, Chimiset. A Orelie tem as informações que eu e a Mary precisamos. Mas, pela condição dela, que, se entendi direito, é simplesmente por causa da idade, a gente... não consegue tirar esse conhecimento dela, nem pode ter certeza de que seria confiável. Já ouvi falar das maravilhas que xamãs indianos e africanos conseguem fazer – por isso vim pedir sua ajuda, Chimiset.";
			link.l1.go = "Chimset_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Chimset_2":
			dialog.text = "Eu entendo você, meu amigo. Os xamãs têm poderes misteriosos e místicos, muitas vezes além da compreensão dos outros, até mesmo dos próprios parentes, quanto mais dos brancos. Uns chamam de feitiçaria, outros de milagre. A gente realmente é capaz de muita coisa – mas ninguém pode fazer um rio correr ao contrário... Nem pode pará-lo, também.";
			link.l1 = "O que você quer dizer com isso, Chimiset?";
			link.l1.go = "Chimset_3";
		break;
		
		case "Chimset_3":
			dialog.text = "Estou falando do rio do tempo, meu amigo. Ou do rio da vida—como preferir. Veja, você está absolutamente certo—a raiz da doença dessa pobre alma está nos seus anos, e em nada mais.";
			link.l1 = "Já ouvi um pouco sobre isso. Só sei que não é um problema tão raro assim.";
			link.l1.go = "Chimset_4";
		break;
		
		case "Chimset_4":
			dialog.text = "Você tem razão. Pessoas da idade dela costumam se perder em vales de sonhos, e às vezes de pesadelos. Elas voltam, só para partir de novo—não tanto por vontade própria, mas por forças misteriosas que as puxam. Com o tempo, a doença fica mais forte—até que a pessoa já não lembra mais de si mesma, nem dos amigos.";
			link.l1 = "Então, não tem nada que você possa fazer sobre isso, sabe?";
			link.l1.go = "Chimset_5";
		break;
		
		case "Chimset_5":
			dialog.text = "Expulsar a doença – não. Isso está além de mim. Mas tem outra coisa que eu posso fazer...";
			link.l1 = "O quê exatamente?";
			link.l1.go = "Chimset_6";
		break;
		
		case "Chimset_6":
			dialog.text = "No momento em que essa mulher acordar, vou fazer um ritual rápido, para o qual já vou me preparar antes.";
			link.l1 = "Isso pelo menos vai retardar a doença, se não conseguir parar de vez?";
			link.l1.go = "Chimset_7";
		break;
		
		case "Chimset_7":
			dialog.text = "Não exatamente. Isso vai obrigá-la a reunir toda a força que tem só para manter a sanidade pelo maior tempo possível.";
			link.l1 = "Quanto tempo é ‘o máximo possível’, exatamente?";
			link.l1.go = "Chimset_8";
		break;
		
		case "Chimset_8":
			dialog.text = "Não depende do ritual, mas da pessoa. Alguns aguentam uma semana, outros um mês... Ouvi falar de um homem que manteve a sanidade e a memória por quase um ano, talvez até mais... E bem quando todos achavam que ele estava curado, a doença voltou—e levou ele naquela mesma noite.";
			link.l1 = "Uma hora vai ser suficiente pra gente descobrir o que precisa. Quando você pode fazer o ritual, Chimiset?";
			link.l1.go = "Chimset_9";
		break;
		
		case "Chimset_9":
			dialog.text = "Vou levar a mulher agora mesmo, descer com ela até o porão—tem um lugar reservado lá... só pra situações assim. Depois disso, tudo depende de quando ela voltar a si... Mas acho que até de manhã já teremos terminado.";
			link.l1 = "Então eu não vou atrapalhar você. E que seu... Deus, Chimiset, te ajude.";
			link.l1.go = "Chimset_10";
		break;
		
		case "Chimset_10":
			dialog.text = "Zikomo! Me ajuda a levar a mulher branca para o porão.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_13");
		break;
		
		case "Chimset_11":
			dialog.text = "Deu certo, irmão branco. Conseguimos...";
			link.l1 = "...";
			link.l1.go = "Chimset_11_add";
			DelLandQuestMark(npchar);
		break;
		case "Chimset_11_add":
			StartInstantDialog("LSC_Oreli", "Chimset_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_12":
			dialog.text = "Oh, "+GetFullName(pchar)+"! Eu não fazia ideia de que você e a Mary tinham voltado pra Ilha! Que surpresa maravilhosa!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_14_1");
		break;
		
		case "Chimset_13":
			dialog.text = "...";
			link.l1 = "Chimiset, obrigada! Eu nem sei como te agradecer...";
			link.l1.go = "Chimset_14";
			link.l2 = "Olha só, Chimiset conseguiu mesmo! Eu nunca duvidei de você, sabe?...";
			link.l2.go = "Chimset_15";
		break;
		
		case "Chimset_14":
			dialog.text = "Todos os Rivados estão para sempre em dívida com você, meu amigo! As portas do 'Protetor' estarão sempre abertas para você.";
			link.l1 = "Espero não precisar incomodar você mais... Mary, Orelie, precisamos voltar para o 'Pluto'.";
			link.l1.go = "Chimset_15_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Chimset_15":
			dialog.text = "Todos os Rivados estão eternamente em dívida com você, meu amigo! As portas do 'Protetor' estarão sempre abertas para você.";
			link.l1 = "Espero não ter que incomodar vocês mais... Mary, Orelie, precisamos voltar para o 'Pluto'.";
			link.l1.go = "Chimset_15_add";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		case "Chimset_15_add":
			StartInstantDialog("LSC_Oreli", "Chimset_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_16":
			dialog.text = "Nem lembro como saí da minha cabine... Ah, essa velhice – minha memória foi pro inferno, sabe? ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_15");
		break;
		
		case "Oreli_11":
			dialog.text = "Ora, ora, mocinha, o que te traz à minha cabine?";
			link.l1 = "...";
			link.l1.go = "Oreli_11_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_12":
			dialog.text = "Orelie, eu...";
			link.l1 = "...";
			link.l1.go = "Oreli_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_12_add":
			StartInstantDialog("Mary", "Oreli_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_13":
			dialog.text = "Orelie, pedi pra ela dar uma arrumada aqui enquanto você estava fora. Não precisa você se esforçar com esses joelhos ruins...";
			link.l1 = "...";
			link.l1.go = "Oreli_13_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
			
		break;
		case "Oreli_13_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_14":
			dialog.text = "Limpar tudo?! Você...";
			link.l1 = "Jillian, obrigada pelo seu trabalho. (sussurrando) Conseguimos. Chimiset conseguiu mesmo.";
			link.l1.go = "Oreli_15";
		break;
		
		case "Oreli_15":
			dialog.text = "Não pode ser...";
			link.l1 = "Como você pode ver. Agora, por favor, vamos conversar.";
			link.l1.go = "Oreli_15_add";
		break;
		case "Oreli_15_add":
			StartInstantDialog("LSC_Oreli", "Oreli_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_16":
			dialog.text = "Bem, jovens, obrigada por acompanharem uma velha senhora. Acho que logo nem vou conseguir sair de casa. Minhas pernas, minhas pobres pernas...";
			link.l1 = "Se não se importar, "+npchar.name+", nós vamos ficar com você só mais um pouquinho. Eu e a Mary temos um assunto muito importante pra tratar com você.";
			link.l1.go = "Oreli_17";
		break;
		
		case "Oreli_17":
			dialog.text = "Se eu não tiver que me arrastar pra outro navio de novo, eu ajudo no que puder. Tô ouvindo.";
			link.l1 = "...";
			link.l1.go = "Oreli_17_add";
		break;
		case "Oreli_17_add":
			StartInstantDialog("Mary", "Oreli_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_18":
			dialog.text = "Orelie, eu quero que você me conte sobre meus pais. E sobre o dia em que nasci. Foi aqui, na Ilha, né? O Donald diz que foi, mas ele nem estava aqui naquela época, então ele não pode saber de verdade. Mas você mora aqui há muito mais tempo que ele, sabe! Mais de vinte anos, não é?";
			link.l1 = "...";
			link.l1.go = "Oreli_18_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_18_add":
			StartInstantDialog("LSC_Oreli", "Oreli_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_19":
			dialog.text = "Calma, calma, garota, não fala tão rápido, por favor! Eu não consigo te acompanhar...";
			link.l1 = "...";
			link.l1.go = "Oreli_19_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_19_add":
			StartInstantDialog("Mary", "Oreli_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_20":
			dialog.text = "Sabe, eu entendi. Tá bom, vamos revisar isso mais uma vez...";
			link.l1 = "...";
			link.l1.go = "Oreli_20_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_20_add":
			StartInstantDialog("LSC_Oreli", "Oreli_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_21":
			dialog.text = "Não se preocupe, Mary, ainda não estou tão velho assim, haha... Ouvi o que você disse. Mas como realmente vivi na Ilha da Justiça mais tempo do que qualquer um, espero que trate minha idade com um pouco de respeito e compreensão...";
			link.l1 = "...";
			link.l1.go = "Oreli_21_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_21_add":
			StartInstantDialog("Mary", "Oreli_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_22":
			dialog.text = "Claro, Orelie! Como você poderia pensar diferente, sabe?";
			link.l1 = "...";
			link.l1.go = "Oreli_22_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_22_add":
			StartInstantDialog("LSC_Oreli", "Oreli_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_23":
			dialog.text = "Ah, é que quando eu olho pra essa juventude de hoje em dia... não, não, a gente não era assim com os mais velhos. Mas você também não é assim, claro. Só quis dizer que vai ser mais fácil pra nós se eu responder suas perguntas uma de cada vez, e não tudo misturado...";
			link.l1 = "...";
			link.l1.go = "Oreli_23_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_23_add":
			StartInstantDialog("Mary", "Oreli_24", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_24":
			dialog.text = "Entendi, Orelie. O que for mais fácil pra você, sabe? Então, você estava na Ilha quando eu nasci? Quer dizer, se é que eu nasci aqui...";
			link.l1 = "...";
			link.l1.go = "Oreli_24_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_24_add":
			StartInstantDialog("LSC_Oreli", "Oreli_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_25":
			dialog.text = "Cheguei à Ilha da Justiça em 1633, e às vezes aquele dia ainda assombra meus pesadelos. A tempestade, nosso 'Reprisal'—o navio em que meu marido e eu estávamos indo para a Flórida—era jogado de um lado para o outro pelas ondas, pronto para virar a qualquer momento, e a gente rezava todas as orações que conhecia e inventava outras na hora... E então, um estrondo e...";
			link.l1 = "...";
			link.l1.go = "Oreli_25_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_25_add":
			StartInstantDialog("Mary", "Oreli_26", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_26":
			dialog.text = "Então você acabou vindo parar aqui cinco anos antes de eu nascer, sabe.";
			link.l1 = "...";
			link.l1.go = "Oreli_26_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_26_add":
			StartInstantDialog("LSC_Oreli", "Oreli_27", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_27":
			dialog.text = "Mais ou menos. As coisas eram diferentes naquela época. San Jeronimo ainda estava de pé, o anel externo de navios era metade do tamanho que é hoje, talvez até menos... E isso sem contar os que não sobreviveram! Vou te dizer uma coisa, jovens — em um dia claro, se você olhar para a água, dá até medo ver quantos destroços tem lá embaixo...";
			link.l1 = "...";
			link.l1.go = "Oreli_27_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_27_add":
			StartInstantDialog("Mary", "Oreli_28", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_28":
			dialog.text = "A gente quer saber sobre o navio em que meus pais chegaram aqui. Comigo... ou sem mim?";
			link.l1 = "...";
			link.l1.go = "Oreli_28_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_28_add":
			StartInstantDialog("LSC_Oreli", "Oreli_29", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_29":
			dialog.text = "Com você, garota, com você.";
			link.l1 = "...";
			link.l1.go = "Oreli_29_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_29_add":
			StartInstantDialog("Mary", "Oreli_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_30":
			dialog.text = "Então, eu nasci no Continente, afinal?";
			link.l1 = "...";
			link.l1.go = "Oreli_30_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_30_add":
			StartInstantDialog("LSC_Oreli", "Oreli_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_31":
			dialog.text = "Não, eu quis dizer 'com você' de um jeito um pouco diferente. Você estava na barriga da sua mãe e nasceu uma semana depois.";
			link.l1 = "Você acha isso engraçado, Orelie?";
			link.l1.go = "Oreli_32";
			link.l2 = "E você não perdeu o senso de humor com o passar dos anos, Orelie.";
			link.l2.go = "Oreli_33";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_32":
			dialog.text = "Bom, eu rio de mim mesma muito mais do que dos outros. Desculpa, Mary, não quis magoar seus sentimentos.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_33":
			dialog.text = "Bem, eu rio de mim mesma muito mais do que dos outros. Desculpa, Mary, não quis magoar seus sentimentos.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		case "Oreli_33_add":
			StartInstantDialog("Mary", "Oreli_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_34":
			dialog.text = "Tá tudo bem, Orelie. Pode falar, por favor. O que aconteceu com meus pais depois que eu nasci?";
			link.l1 = "...";
			link.l1.go = "Oreli_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_34_add":
			StartInstantDialog("LSC_Oreli", "Oreli_35", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_35":
			dialog.text = "Depois? Ah, minha querida, o fato de os dois terem sobrevivido até então já foi um milagre! Que tempestade terrível foi aquela noite de junho! Quando, ao amanhecer, o barco trouxe sua mãe para o anel interno, quase ninguém acreditou no que via—uma mulher prestes a dar à luz ter sobrevivido a um naufrágio tão horrível. Pobre Teresa, lembro como se fosse ontem...";
			link.l1 = "...";
			link.l1.go = "Oreli_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_35_add":
			StartInstantDialog("Mary", "Oreli_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_36":
			dialog.text = "Teresa? Era esse o nome dela?";
			link.l1 = "...";
			link.l1.go = "Oreli_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_36_add":
			StartInstantDialog("LSC_Oreli", "Oreli_37", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_37":
			dialog.text = "Sim, foi assim que ela se apresentou – e isso foi quase tudo o que ela disse. No final do dia, ela caiu de cama com febre e ficou assim até o parto. Ninguém tinha certeza se ela ia sobreviver, e muito menos se o bebê nasceria vivo – depois de tudo o que ela passou. Mas Teresa conseguiu. Ela conseguiu – e então partiu. Que Deus a tenha...";
			link.l1 = "...";
			link.l1.go = "Oreli_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_37_add":
			StartInstantDialog("Mary", "Oreli_38", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_38":
			dialog.text = "Minha mãe morreu, e eu fiquei só com meu pai? Mas então por que todo mundo dizia que fui criada pelo Eric Udette? E...";
			link.l1 = "...";
			link.l1.go = "Oreli_38_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_38_add":
			StartInstantDialog("LSC_Oreli", "Oreli_39", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_39":
			dialog.text = "Mary, querida, eu te pedi... Não me bombardeia com tantas perguntas assim...";
			link.l1 = "...";
			link.l1.go = "Oreli_39_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_39_add":
			StartInstantDialog("Mary", "Oreli_40", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_40":
			dialog.text = "Desculpa, Orelie, me empolguei, sabe? Meu pai também sobreviveu a um naufrágio, não foi?";
			link.l1 = "...";
			link.l1.go = "Oreli_40_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_40_add":
			StartInstantDialog("LSC_Oreli", "Oreli_41", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_41":
			dialog.text = "Seu pai... Sabe, não tem muito o que eu possa dizer sobre ele — só que eu não desejaria um pai como o seu nem pro meu pior inimigo. Só alguns dias depois que você nasceu, ele sumiu, te deixando pra se virar sozinha. Você teve sorte do Eric ter um coração tão bom e gentil — macio feito um biscoito molhado numa caneca de grogue...";
			link.l1 = "...";
			link.l1.go = "Oreli_41_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_41_add":
			StartInstantDialog("Mary", "Oreli_42", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_42":
			dialog.text = "Pelo menos me diz o nome dele!";
			link.l1 = "...";
			link.l1.go = "Oreli_42_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_42_add":
			StartInstantDialog("LSC_Oreli", "Oreli_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_43":
			dialog.text = "Ah... Era Jeffrey ou John, se ao menos eu conseguisse lembrar...";
			link.l1 = "Então, você realmente não se lembra, né? "+npchar.name+"?";
			link.l1.go = "Oreli_44";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_44":
			dialog.text = "Você está duvidando das minhas palavras, rapaz?!";
			link.l1 = "Quiet, "+npchar.name+", calma aí. Não quis te ofender. Só achei que você lembrava bem daqueles dias, só isso.";
			link.l1.go = "Oreli_45";
			link.l2 = "Não tenho dúvidas, "+npchar.name+". Eu só estou tentando lembrar de todos os detalhes direitinho – só isso. Mas toda essa confusão realmente deixa as coisas um pouco mais complicadas.";
			link.l2.go = "Oreli_46";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_45":
			dialog.text = "A memória é uma dama caprichosa, "+pchar.name+", bastante seletiva. Principalmente depois de todos esses anos. Teresa é difícil de esquecer – eu vi o quanto ela sofreu a semana inteira! Nossa, como eu fiquei com pena dela!";
			link.l1 = "E o marido dela, não estava com ela?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Oreli_46":
			dialog.text = "A memória é uma dama caprichosa, "+pchar.name+", bem seletiva. Principalmente depois de todos esses anos. É difícil esquecer a Teresa – eu vi o quanto ela sofreu a semana inteira! Nossa, como eu fiquei com pena dela!";
			link.l1 = "E o marido dela, ele não estava com ela?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_47":
			dialog.text = "Muito raramente. Ele passava a maior parte da semana fora – procurando remédios e poções, que eram bem difíceis de encontrar na Ilha naquela época...";
			link.l1 = "Então, ele devia ser um bom marido – se tentou ajudar a esposa dele.";
			link.l1.go = "Oreli_48";
		break;
		
		case "Oreli_48":
			dialog.text = "Ele poderia ter sido um bom marido. Nunca disse o contrário, sabe? Não tente me confundir, rapaz!";
			link.l1 = "E eu nunca nem pensei numa coisa dessas, juro, "+npchar.name+". É óbvio que você não tem uma opinião muito boa sobre ele. E o fato de nem lembrar o nome dele...";
			link.l1.go = "Oreli_49";
		break;
		
		case "Oreli_49":
			dialog.text = "Eu vi aquele homem de relance, quase só uma sombra, na escuridão da cabana da 'Ferraria Ceres'—onde o Herr Jürgen mora agora. Ele só aparecia à noite, e mal lembro do rosto dele. Quanto ao nome—ninguém nunca o chamava pelo primeiro nome, só pelo sobrenome. Casper pra cá, Casper pra lá...";
			link.l1 = "Eu entendo você, "+npchar.name+". Então a Mary nasceu, e alguns dias depois ele sumiu sem deixar rastro. Será que mataram ele?";
			link.l1.go = "Oreli_50";
		break;
		
		case "Oreli_50":
			dialog.text = "Essa é uma pergunta complicada, rapaz. Sabe, é bem difícil manter qualquer coisa em segredo aqui—todo mundo está sempre de olho. Sempre que tem outra briga—mesmo dentro dos navios—no dia seguinte a Ilha toda já ficou sabendo.";
			link.l1 = "Não me surpreende.";
			link.l1.go = "Oreli_51";
		break;
		
		case "Oreli_51":
			dialog.text = "Os corpos dos mortos nem sempre são encontrados – bandidos experientes afundam os cadáveres, amarrando mãos e pés com balas encadeadas ou prendendo pesos como balas de canhão ou pedras. E os caranguejos no fundo terminam o serviço. Mas os pertences pessoais dos mortos acabam vindo à tona.";
			link.l1 = "Do fundo?!";
			link.l1.go = "Oreli_52";
		break;
		
		case "Oreli_52":
			dialog.text = "Claro que não! Eu quis dizer que essas coisas só chamam a atenção—um anel, uma pistola com uma gravação, um sabre cerimonial... Quase ninguém faz perguntas sobre isso. Não dá pra trazer a pessoa de volta, e ninguém quer mais problemas do que já tem.";
			link.l1 = "O Geoffrey ou o John Casper tinham algum pertence marcante?";
			link.l1.go = "Oreli_53";
		break;
		
		case "Oreli_53":
			dialog.text = ""+pchar.name+" Deus te abençoe – eu nem lembro o nome dele, e você me faz umas perguntas dessas! Se aconteceu alguma coisa, nunca ouvi ninguém dizer que aquilo foi parar com outra pessoa na Ilha da Justiça. Naquela época eu trabalhava como garçonete na taverna, e quase nenhum boato escapava de mim. Mas isso não quer dizer que eu soubesse absolutamente de tudo.";
			link.l1 = "Quando as pessoas dizem que alguém desapareceu sem deixar vestígios, geralmente querem dizer que foi morto. Mas no caso do Sr. Casper, dá pra ver que você não tem tanta certeza disso...";
			link.l1.go = "Oreli_54";
		break;
		
		case "Oreli_54":
			dialog.text = "Olha, só estou dizendo que 'desaparecido' não quer dizer necessariamente 'morto'. Principalmente naquela época, quando tartanas cheias de contrabandistas e receptadores navegavam direto entre a Ilha e Cuba... Sabe, não consigo lembrar do rosto dele, mas os olhos... Era o olhar de um homem que nunca se perderia em lugar nenhum. Ou pelo menos, ele realmente acreditava nisso.";
			link.l1 = "Tartanas, tartanas... Nada impossível nisso. Se soubéssemos o nome dele, poderíamos consultar os arquivos coloniais daqueles anos. Mas seria muito mais fácil se tivéssemos o tipo e o nome do navio em que ele serviu.";
			link.l1.go = "Oreli_55";
		break;
		
		case "Oreli_55":
			dialog.text = "E por que você está me olhando, rapaz? Acha que eu vou lembrar disso?";
			link.l1 = "Esperamos que sim, "+npchar.name+" - considerando tudo o que você já contou pra gente.";
			link.l1.go = "Oreli_56";
			link.l2 = "Hum... Tenho sérias dúvidas sobre isso.";
			link.l2.go = "Oreli_57";
		break;
		
		case "Oreli_56":
			dialog.text = "Talvez você queira saber quantos canhões ela tinha e de que calibre eram? Meu querido, você faz ideia de quantos navios já afundaram aqui ao longo dos anos? E você acha mesmo que eu lembro de todos eles? Além disso, só meia dúzia de pessoas sobreviveu daquele navio – ele mal durou um dia na superfície, sabe...";
			link.l1 = "Entendi... Bom, faz sentido, já se passaram vinte anos. Obrigada por pelo menos lembrar do que nos disseram.";
			link.l1.go = "Oreli_58";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Oreli_57":
			dialog.text = "Talvez você queira saber quantos canhões ela tinha e de que calibre eram? Meu querido, você faz ideia de quantos navios já naufragaram aqui ao longo dos anos? E acha mesmo que eu lembro de todos eles? Além disso, só meia dúzia sobreviveu daquele navio – ele mal ficou um dia inteiro flutuando, se é que ficou...";
			link.l1 = "Entendi... Bem, faz sentido, já se passaram vinte anos. Obrigada por pelo menos lembrar do que nos disseram.";
			link.l1.go = "Oreli_58";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_58":
			dialog.text = "Espero que você não esteja brincando e nem tentando zombar de uma velha cuja memória está cheia de buracos.";
			link.l1 = "De jeito nenhum, "+npchar.name+". Você realmente nos ajudou muito. Melhoras pra você. Bem, vamos indo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_16");
		break;
		
		case "Mary_91":
			dialog.text = "Então, Teresa... Esse era o nome dela. Minha pobre mãe, sabe...";
			link.l1 = "Bom, pelo menos agora a gente sabe de onde vem toda essa força e teimosia sua. Uma mulher grávida em um navio afundando... Só de pensar nisso já me dá um arrepio, sabe?";
			link.l1.go = "Mary_92";
		break;
		
		case "Mary_92":
			dialog.text = "Mas o que ela estava fazendo nesse estado nesse navio, "+pchar.name+"?! Você teria que ser louco pra sequer pensar em fazer uma coisa dessas!";
			link.l1 = "Só seu pai pode responder essa pergunta – John, Jack, Jacob, Jasper, Jordan...";
			link.l1.go = "Mary_94";
		break;
		
		case "Mary_94":
			dialog.text = "Você está tentando lembrar de todos os nomes em inglês que começam com ‘J’? A Orelie só falou do Geoffrey e do John, sabe.";
			link.l1 = "Talvez ela só não lembrasse do resto, como eu? Sabe, idade e essas coisas...";
			link.l1.go = "Mary_95";
		break;
		
		case "Mary_95":
			dialog.text = ""+pchar.name+", você acha...";
			link.l1 = "Eu não confiaria totalmente na memória dela agora, sabe? Mas mesmo assim, vamos ter que vasculhar não só os arquivos coloniais, mas também os da Marinha de 1638, e isso é bem mais difícil: esses registros são confidenciais, principalmente quando envolvem oficiais. E duvido muito que algum marinheiro comum teria permissão pra embarcar a esposa escondido.";
			link.l1.go = "Mary_96";
		break;
		
		case "Mary_96":
			dialog.text = "Por outro lado, é muito mais fácil encontrar informações sobre um oficial do que sobre um marinheiro comum.";
			link.l1 = "Se você souber o nome do navio. Ou o nome completo, sabe? E não só 'Geoffrey ou John ou, na pior das hipóteses, Jack...'. Isso se tivermos sorte e o navio for da marinha. Os mercantes cuidam muito pior das listas de tripulação.";
			link.l1.go = "Mary_97";
		break;
		
		case "Mary_97":
			dialog.text = "Mas o que a gente faz então, "+pchar.name+"? Falar com a Orelie de novo? Já tiramos tudo o que podíamos dela, não acha?";
			link.l1 = "Não com a Orelie. Com o Donald.";
			link.l1.go = "Mary_98";
		break;
		
		case "Mary_98":
			dialog.text = "E como é que ele vai ajudar a gente? Ele mesmo disse que em 1638 ele nem chegou perto da Ilha da Justiça, sabe.";
			link.l1 = "Mas havia outros Narvais aqui, não havia?";
			link.l1.go = "Mary_99";
		break;
		
		case "Mary_99":
			dialog.text = "Eu não entendo muito bem o que você quer dizer.";
			link.l1 = "Você vai ver, querido, você vai ver. Ainda tem mais um fio que a gente pode puxar. Vamos lá.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_17");
		break;
		
		case "Grinspy_31":
			dialog.text = "Ah, é você de novo! E aí, como vão as suas buscas?";
			link.l1 = "Oi, "+npchar.name+". As coisas podiam estar melhores. Agora estamos vagando como se estivéssemos numa caverna cheia de mistérios e enigmas. Mas sentimos que a saída está perto.";
			link.l1.go = "Grinspy_32";
			link.l2 = "E oi pra você, "+npchar.name+"Melhor do que eu poderia imaginar no começo. A situação... não é tão sem esperança assim, sabe?";
			link.l2.go = "Grinspy_33";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_32":
			dialog.text = "Fico feliz em ouvir isso. De verdade. Mas vocês dois precisam de mim de novo, né? O que conseguiram descobrir?";
			link.l1 = "Mary nasceu aqui, na Ilha da Justiça, em junho de 1638. A mãe dela, Teresa, morreu logo depois do parto. O pai dela—um homem chamado Casper—sumiu sem deixar rastro poucos dias depois que Mary nasceu. Tudo que sabemos sobre ele é que o nome dele começa com 'J.' Alguns dizem que ele não virou comida de caranguejo nas águas rasas daqui, mas foi embora da Ilha em uma das tartanas dos contrabandistas...";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_33":
			dialog.text = "Que bom saber disso. De verdade. Mas vocês dois precisam de mim de novo, sabe? Então, o que descobriram?";
			link.l1 = "Mary nasceu aqui, na Ilha da Justiça, em junho de 1638. A mãe dela, Teresa, morreu logo depois do parto. O pai — um homem chamado Casper — sumiu sem deixar rastro poucos dias depois que Mary nasceu. Não sabemos nada sobre ele, só que o nome dele começa com 'J'. Alguns dizem que ele não virou comida de caranguejo nas águas rasas daqui, mas foi embora da Ilha em uma das tartanas dos contrabandistas...";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_34":
			dialog.text = "E deixou a própria filha para trás? Isso é uma coisa estranha de se fazer.";
			link.l1 = "Com certeza é. Mas ninguém além desse tal Sr. J. pode explicar isso.";
			link.l1.go = "Grinspy_35";
		break;
		
		case "Grinspy_35":
			dialog.text = "E você acha que ele ainda está vivo? É por isso que você está procurando por ele?";
			link.l1 = "Não é só por isso. A gente quer saber quem ele era, como ele viveu. Isso é muito importante pra Mary.";
			link.l1.go = "Grinspy_36";
		break;
		
		case "Grinspy_36":
			dialog.text = "Hum, entendi. E desculpa, mas acho que não posso te ajudar com nada mesmo...";
			link.l1 = "Na verdade, você pode. Me diz, os Narvais mantêm algum tipo de registro dos navios que se perderam na Ilha, não é?";
			link.l1.go = "Grinspy_37";
		break;
		
		case "Grinspy_37":
			dialog.text = "Eu não tenho muita certeza do que você quer dizer, "+pchar.name+".";
			link.l1 = "Greenspen, Greenspen... Não esquece que você só está esquentando essa cadeira por minha causa. Então me faz um favor – não testa a minha paciência.";
			link.l1.go = "Grinspy_38";
			link.l2 = "Tenho certeza de que você entende, Donald. E, pela nossa amizade, você não vai tentar fugir da pergunta.";
			link.l2.go = "Grinspy_39";
		break;
		
		case "Grinspy_38":
			dialog.text = "Hmm...";
			link.l1 = "De vez em quando, alguns navios acabam encalhando no anel externo. Uns afundam logo, outros ficam boiando por um tempo—daí o pessoal entra, vasculha e leva tudo que presta. Sobre os Rivados eu não sei, mas duvido que os Narvais briguem por cada bugiganga que acham a bordo—provavelmente, tudo vai pra um monte comum, depois fazem as contas do saque, e só então dividem o que encontraram.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Grinspy_39":
			dialog.text = "Hmm...";
			link.l1 = "De vez em quando, alguns navios aparecem no anel externo. Uns afundam logo, outros ficam boiando por um tempo—eles são vasculhados, e tudo de valor é tirado de lá. Não sei como é com os Rivados, mas duvido que os Narvais briguem por cada bugiganga que encontram a bordo—provavelmente, tudo vai pra um monte comum, depois fazem um inventário completo, e só então dividem o saque.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "Grinspy_40":
			dialog.text = "You’re no fool, +pchar.name+. Unlike many around here. Yes, that’s more or less how it works. Personally, I find all that paperwork tiresome, but it’s been that way since the time of Alan Milroe and those who led the Narwhal clan before him. We keep such records - and more than that: we even log ships that were reached first by the Rivados or pirates. In those cases, of course, we don’t know who or what was on board...";
			link.l1 = "Se os pais da Mary foram levados para a Ferraria Ceres depois do naufrágio, então foram os Narvais que encontraram o navio deles. Isso quer dizer que deve haver um registro disso.";
			link.l1.go = "Grinspy_41";
		break;
		
		case "Grinspy_41":
			dialog.text = "Pode ser. Não posso afirmar com certeza. E também não vou conseguir.";
			link.l1 = "Agora eu não entendo o que você quer dizer, "+npchar.name+".";
			link.l1.go = "Grinspy_42";
		break;
		
		case "Grinspy_42":
			dialog.text = "Os registros dos naufrágios. Quando Leighton Dexter virou almirante depois que o Dodson saiu, ele pegou esses documentos da gente.";
			link.l1 = "Assim, do nada – ele levou eles? E você não disse nada, sabe?";
			link.l1.go = "Grinspy_43";
		break;
		
		case "Grinspy_43":
			dialog.text = "Bom, antes de tudo, ele foi educado o bastante. Depois, prometeu devolver logo. E, por último... por que diabos eu me importaria com esses papéis?";
			link.l1 = "Não são exatamente registros inúteis, sabe?";
			link.l1.go = "Grinspy_44";
		break;
		
		case "Grinspy_44":
			dialog.text = "Como eu disse, é só uma tradição, principalmente pra evitar que o nosso clã se mate por causa do saque dos navios. Quando um navio encalha, a gente tira tudo o que pode, faz uma lista, divide uma parte, guarda o resto nos porões – é só isso. Pra que encher a gaveta? Agora tem até um pouco mais de espaço nelas – acho que eu devia até agradecer ao Almirante por isso.";
			link.l1 = "Sabe, entendido. Então vamos seguir para 'San Augustin'. Mas talvez a gente passe aqui pra te ver de novo, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_18");
		break;
		
		case "WildRose_Dexter_1":
            dialog.text = "Ah, "+pchar.name+"Entra, entra. Você veio a negócios, meu amigo, ou só passou aqui pra dar um oi?";
            link.l1 = "Dessa vez, é negócio. Digamos que, é pessoal.";
            link.l1.go = "WildRose_Dexter_2";
			DelLandQuestMark(npchar);
        break;

        case "WildRose_Dexter_2":
            dialog.text = "E claramente importante pra você, pelo jeito que você tá agitada, sabe?";
            link.l1 = "Sério? Eu diria mais cansada, se quer saber. Tive que andar pelo seu território um bocado nesses últimos dias. Minhas juntas já estão reclamando—e eu achando, toda boba, que só velhos como você tinham que lidar com isso.";
            link.l1.go = "WildRose_Dexter_3_1";
            link.l2 = "Só estou um pouco sem fôlego, só isso. Sabe, eu não fico sentada numa cadeira o dia todo. Diferente de você, pelo visto – parece que suas pernas já desistiram de você faz tempo, ha-ha-ha!";
            link.l2.go = "WildRose_Dexter_3_2";
        break;

        case "WildRose_Dexter_3_1":
            dialog.text = "E você já se perguntou por que eu fico grudada nessa cadeira, sabe? Olha, tudo muda quando você percebe que saúde não se compra, nem com toda a riqueza dessa Ilha da Justiça.";
            link.l1 = "Engraçado, sabe – era exatamente sobre isso que eu vim falar.";
            link.l1.go = "WildRose_Dexter_4";
			AddCharacterExpToSkill(pchar, "Defence", 100);
        break;
		
		case "WildRose_Dexter_3_2":
            dialog.text = "E já se perguntou por que eu fico grudada nessa cadeira, sabe? Olha, tudo muda quando você percebe que saúde não se compra, nem com toda a riqueza dessa Ilha.";
            link.l1 = "Engraçado, é exatamente sobre isso que eu vim falar, sabe?";
            link.l1.go = "WildRose_Dexter_4";
			AddComplexSelfExpToScill(100, 100, 100, 100);
        break;

        case "WildRose_Dexter_4":
            dialog.text = "Sobre a minha saúde?";
            link.l1 = "Não, sobre as riquezas da Ilha da Justiça. Ou, pra ser mais exata, sobre o inventário delas. E pra ser totalmente precisa, sobre os livros onde esses inventários estão anotados.";
            link.l1.go = "WildRose_Dexter_5";
        break;

        case "WildRose_Dexter_5":
            dialog.text = "Ahm... pode explicar de um jeito mais simples, "+pchar.name+"?";
            link.l1 = "Não faz muito tempo, você pegou os diários dos navios encalhados na Ilha da Justiça dos Narvais...";
            link.l1.go = "WildRose_Dexter_6";
        break;

        case "WildRose_Dexter_6":
            dialog.text = "Então, aquele idiota do Greenspen realmente te mandou atrás deles? Que ousadia.";
            link.l1 = "De jeito nenhum, "+npchar.name+", Donald não tem nada a ver com isso. Fui até ele com essa pergunta, e ele me mandou falar com você. Mas a sua reação, tenho que admitir, me divertiu. Quer me contar por que precisava dos registros do Narwhal?";
            link.l1.go = "WildRose_Dexter_7";
        break;

        case "WildRose_Dexter_7":
            dialog.text = "Por que não? Sabe, acho que você já percebeu, eu mesma não dou a mínima pros navios em si. E os tesouros escondidos nos porões? Mesma coisa. Tem o bastante pra todo mundo aqui, se o povo não ficar ganancioso demais. Pelo menos, é assim que eu vejo. O que eu realmente quero são armas: mosquetes, sabres... até canhões, se duvidar. Sim, aqueles espertinhos às vezes conseguem resgatar até isso. Os idiotas dos pretos nem sonham em conseguir, mas os Narvais...";
            link.l1 = "E você decidiu ver até que ponto o povo de Greenspen está pronto para uma nova rodada de conflitos?";
            link.l1.go = "WildRose_Dexter_8";
        break;

        case "WildRose_Dexter_8":
            dialog.text = "E manda um recado de que eu e meus rapazes estamos de olho bem aberto. É um sinal bem óbvio, mas considerando o teatrinho que o Donald fez com aqueles exercícios, não me surpreenderia se ele achasse que eu estou atrás do dinheiro dele.";
            link.l1 = "É, dá pra ver que as coisas não estão indo exatamente como você esperava. E os Rivados? O tal do Black Eddie tá dando trabalho, sabe?";
            link.l1.go = "WildRose_Dexter_9";
        break;

        case "WildRose_Dexter_9":
            dialog.text = "Rivados, Eddie... Negros vis, sabe? Não é de se estranhar que o Tubarão odiava tanto eles.";
            link.l1 = "Então ele ESTÁ causando problemas.";
            link.l1.go = "WildRose_Dexter_10";
        break;

        case "WildRose_Dexter_10":
            dialog.text = "É isso mesmo, não é? Que eu seja amaldiçoada se estiver mentindo! Aqueles desgraçados sumiram, se esconderam nos navios deles...";
            link.l1 = "Então o que diabos está te incomodando, hein? "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_11";
        break;

        case "WildRose_Dexter_11":
            dialog.text = "Como é que eu vou te explicar isso, sabe? "+pchar.name+"... Sabe, é como o vento em alto-mar. Às vezes é suave, às vezes é forte, e às vezes vira uma tempestade de verdade. Mas de um jeito ou de outro, o vento empurra o navio pra frente, e um bom capitão sabe como aproveitar isso.";
            link.l1 = "Uma brisa suave é sempre melhor do que uma tempestade furiosa.";
            link.l1.go = "WildRose_Dexter_12";
        break;

        case "WildRose_Dexter_12":
            dialog.text = "Certo. Mas às vezes, simplesmente não tem vento nenhum. Calmaria total – e não há nada que nenhum capitão possa fazer. Você só senta lá no tombadilho, fica olhando pra água e se perguntando que diabos vai acontecer depois. É igual com o Eddie e o amigo dele, o Chimiset – eles estão tramando alguma coisa, eu sinto isso até os ossos, e não é coisa boa, juro por tudo!";
            link.l1 = "Talvez você devesse levantar dessa cadeira e conversar cara a cara com o Edward. Ou melhor ainda, juntar vocês três, chamar o Donald também, e terem uma conversa de verdade. Isso é muito melhor do que afogar a Ilha da Justiça em sangue de novo. Mas, sabe... Vamos voltar ao motivo de eu ter vindo aqui.";
            link.l1.go = "WildRose_Dexter_13";
        break;

        case "WildRose_Dexter_13":
            dialog.text = "Então você está interessado nos tesouros dos narvais, né? O que você espera encontrar lá?";
            link.l1 = "Estou interessado nas listas de navios perdidos aqui. Especificamente, do ano de 1638. O lance é que estamos tentando encontrar informações sobre os pais da Mary. A mãe dela está mais ou menos registrada, mas o mesmo não dá pra dizer do pai. Os detalhes sobre ele são bem vagos — a gente nem sabe o nome dele, e a única pista que temos é o nome do navio que naufragou no anel externo em junho de 1638...";
            link.l1.go = "WildRose_Dexter_14";
        break;

        case "WildRose_Dexter_14":
            dialog.text = "Um nobre. Já me torturei pensando em quem era meu próprio pai. Mas acho que não posso te ajudar, sabe?";
            link.l1 = "E por que isso, se não se importa de eu perguntar?";
            link.l1.go = "WildRose_Dexter_15";
        break;

        case "WildRose_Dexter_15":
            dialog.text = "Sem segredos pra você, "+npchar.name+". Não fui eu, foi o Donald. Ele só entregou documentos a partir do ano de 1651. Perguntei sobre registros mais antigos, pelo menos da década anterior, mas ele disse que era tudo o que tinha herdado do Alan Milroe. Foi isso que ele me falou.";
            link.l1 = "Eu não acho que ele tinha motivo pra mentir, sabe?";
            link.l1.go = "WildRose_Dexter_16";
        break;

        case "WildRose_Dexter_16":
            dialog.text = "Eu também não sei, amigo. Ele me entregou os novos registros sem fazer uma única pergunta. Na verdade, até me pareceu que ele ficou meio aliviado de se livrar daquela papelada... Vai saber, talvez o Milroew só tenha se livrado de documentos de décadas atrás... Queimou tudo, ou talvez...";
            link.l1 = "Não, isso não pode ser.";
            link.l1.go = "WildRose_Dexter_16_Add";
        break;

        case "WildRose_Dexter_16_Add":
            StartInstantDialog("Mary", "WildRose_Dexter_17", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_17":
            dialog.text = "Não, isso não pode ser. O Alan nunca faria uma coisa dessas.";
            link.l1 = "Por que você tem tanta certeza disso, "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_17_1";
            link.l2 = "Eu achava que ele era mais do tipo faca e machado do que alguém metido com toda essa papelada. Surpresa que ele saiba até ler, sabe?";
            link.l2.go = "WildRose_Dexter_17_2";
        break;

        case "WildRose_Dexter_17_1":
            dialog.text = "Ele tratava cada registro sobre a Ilha da Justiça com muito cuidado. Via tudo como parte da história dela. E história— não só deste lugar— era a verdadeira paixão do Alan, sabe? Ele estudava todo documento antigo e livro que conseguia encontrar... Às vezes eu pensava que ele teria sido um estudioso muito melhor do que um lutador— cheguei até a dizer isso pra ele uma vez.";
            link.l1 = "...";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_17_2":
            dialog.text = "Ele tratava cada registro sobre a Ilha da Justiça com muito cuidado. Via tudo isso como parte da história do lugar. E história—não só daqui—era a verdadeira paixão do Alan, sabe? Ele estudava todo documento antigo e livro que conseguia encontrar... Às vezes eu achava que ele daria um estudioso muito melhor do que um lutador—cheguei até a dizer isso pra ele uma vez.";
            link.l1 = "Talvez ele devesse mesmo ter escolhido óculos, papel e uma pena em vez de espada e pistola — vai saber, talvez ainda estivesse andando de um lado pro outro nos conveses podres desses navios. Mas se o Milroe gostava tanto de arquivos assim, então onde ele colocou esses registros? Tudo bem, pode ter derrubado tinta em uma folha sem querer — mas eram dezenas, se não centenas delas, né?";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_18":
            dialog.text = "Eu só sei que ele guardava esses papéis com mais cuidado do que a própria vida. Talvez alguém tenha roubado, ou quem sabe ele mesmo entregou pra alguém...";
            link.l1 = "Roubado? Quem iria querer informações sobre navios que foram destruídos de proa a popa há séculos? Deve ter sido entregue—isso é bem mais provável, mas pra quem, e pra quê?";
            link.l1.go = "WildRose_Dexter_19_Add";
        break;

        case "WildRose_Dexter_19_Add":
            StartInstantDialogNoType("Dexter", "WildRose_Dexter_20", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_20":
            dialog.text = "Para algum outro fã de história, haha! Concordo com o Charles – não faço ideia de quem mais poderia querer esses rabiscos antigos.";
            link.l1 = "Alguém precisava deles, sabe? Vou ter que pensar nisso. Né? "+npchar.name+", não vamos te segurar mais. A gente se vê de novo.";
            link.l1.go = "Exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19");
        break;
		
		case "WildRose_Betancur_1":
			dialog.text = ""+pchar.name+", bom te ver de novo. Como vão as coisas com a Mary?";
			link.l1 = "E estamos felizes em te ver, "+npchar.name+". Mas como as coisas vão acabar pra gente – isso vai depender de você.";
			link.l1.go = "WildRose_Betancur_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Betancur_2":
			dialog.text = "Uma maneira intrigante de começar uma conversa, tenho que admitir. E um pouco desconcertante, pelo jeito que vocês estão me olhando.";
			link.l1 = "Não precisa se alarmar, "+npchar.name+", não é culpa sua. A gente só está meio cansado de correr por esses navios velhos sem parar. E o ar está pesado hoje, né?";
			link.l1.go = "WildRose_Betancur_3_1";
			link.l2 = "A gente ficou rodando a Ilha da Justiça inteira atrás de você, pra ver se conseguia uma ajudinha sua. Ufa, esse calor tá de matar, sabe?...";
			link.l2.go = "WildRose_Betancur_3_2";
		break;

		case "WildRose_Betancur_3_1":
			dialog.text = "Hum, sim, uma brisa leve cairia muito bem agora, sabe? Mas imagino que não seja só o tempo que te deixou assim. Então, o que posso fazer por você?";
			link.l1 = "Veja, eu e a Mary começamos uma investigação para esclarecer o que aconteceu há vinte anos.";
			link.l1.go = "WildRose_Betancur_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Betancur_3_2":
			dialog.text = "Hum, sabe, uma brisa leve cairia muito bem agora. Mas acho que não é só o tempo que te deixou assim, né? Então, o que posso fazer por você?";
			link.l1 = "Veja, eu e a Mary começamos uma investigação para esclarecer o que aconteceu há vinte anos.";
			link.l1.go = "WildRose_Betancur_4";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Betancur_4":
			dialog.text = "Parece interessante. E sobre o que é, exatamente?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_4_add";
		break;
		
		case "WildRose_Betancur_4_add":
			StartInstantDialog("Mary", "WildRose_Betancur_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_5":
			dialog.text = "Meus pais, Antonio. Eu e o Charles estamos tentando descobrir quem eles eram. E o que aconteceu com eles. Minha mãe morreu no parto, isso a gente já descobriu. Mas as coisas com meu pai não são tão simples assim...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_5_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_6":
			dialog.text = "Em que ano você nasceu, me lembra...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_6_add":
			StartInstantDialog("Mary", "WildRose_Betancur_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_7":
			dialog.text = "Em 1638. Em junho.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_7_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_8":
			dialog.text = "Eu tinha só doze anos naquela época, Mary. Não lembro muito bem daqueles dias. Algumas lembranças até passam pela minha cabeça agora, claro, mas sinceramente, é meio difícil juntar tudo. Me desculpa, mas duvido que eu consiga te ajudar...";
			link.l1 = "Não precisamos exatamente disso de você, Antonio. Mas se você lembrar de qualquer coisa sobre o dia em que a Mary nasceu, ficaríamos muito agradecidos.";
			link.l1.go = "WildRose_Betancur_9";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_9":
			dialog.text = "Então, como posso te ajudar, "+pchar.name+"?";
			link.l1 = "Você me disse que se interessa por história. Não só a história do mundo, mas especialmente a da Ilha da Justiça.";
			link.l1.go = "WildRose_Betancur_10";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;

		case "WildRose_Betancur_10":
			dialog.text = "É verdade. Eu li todos os livros que consegui encontrar, estudei cada manuscrito que consegui pôr as mãos...";
			link.l1 = "São os manuscritos de que estamos falando. Além de você, só havia mais uma pessoa na Ilha da Justiça que era tão apaixonada por história quanto você...";
			link.l1.go = "WildRose_Betancur_12";
		break;

		case "WildRose_Betancur_12":
			dialog.text = "Alan Milroe. Sabe, a gente conversou sobre isso quando ele ainda não estava ocupado fazendo planos pra acabar com os Rivados, e depois com os piratas também. Ele era um cara esperto, com uns talentos impressionantes.";
			link.l1 = "Sem dúvida – aquele garoto era diferente. Ele tinha algo que podia nos ajudar. E isso não serve pra nada pra ninguém na Ilha da Justiça, só pra vocês dois. Diários de bordo de navios naufragados perto da Ilha, com descrições da carga e dos tesouros recuperados, e talvez até os nomes dos passageiros...";
			link.l1.go = "WildRose_Betancur_13";
		break;

		case "WildRose_Betancur_13":
			dialog.text = "Isso mesmo.";
			link.l1 = "Então, você viu eles?";
			link.l1.go = "WildRose_Betancur_14";
		break;

		case "WildRose_Betancur_14":
			dialog.text = "Eu não só vi esses diários – eu copiei as informações deles nas minhas próprias anotações. Durante uma das nossas conversas, ele acabou mencionando a existência desses cadernos, e eu pedi pra estudar – tô tentando montar algo tipo as Crônicas da Ilha da Justiça, sabe? Esses registros me ajudaram demais.\nO Alan ficou super animado com a minha ideia – escrever a história desse lugar. É verdade que ele não me deu todos os registros, ficou com os dos anos 1650 pra ele, mas na época, o resto já era suficiente pra mim.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_14_add";
		break;
		
		case "WildRose_Betancur_14_add":
			StartInstantDialog("Mary", "WildRose_Betancur_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_15":
			dialog.text = " Esses registros... eles incluem o ano de 1638, não incluem? Por favor, diz que sim!";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_15_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_15_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_16":
			dialog.text = "Eu tenho uma pilha dessas anotações – começando lá em 1620. Foi quando, segundo o Alan, eles começaram a registrar tudo isso. E sim, 1638 também está lá, Mary.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_16_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_16_add":
			StartInstantDialog("Mary", "WildRose_Betancur_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_17":
			dialog.text = "Você deixa a gente dar uma olhada neles?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_17_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_17_add":
			if (PChar.location == "PlutoStoreSmall") StartInstantDialog("LSC_Betancur", "WildRose_Betancur_18", "Quest\CompanionQuests\WildRose.c");
			else StartInstantDialog("LSC_Betancur", "WildRose_Betancur_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_18":
			dialog.text = "Parece que eu não tenho escolha, né? Ha-ha-ha! Espera aí. Estão todos aqui, na gaveta de baixo desse armário.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19_1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_19":
			dialog.text = " Por favor, fiquem à vontade, pesquisem o quanto quiserem...";
			link.l1 = "É exatamente isso que vamos fazer.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_20");
			AddQuestRecordInfo("WildRose_Records", "1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;
		
		case "WildRose_Mary_101":
			dialog.text = "Aqui, "+pchar.name+", olha! Joshua e Teresa Casper! Eu não acredito – conseguimos, de verdade, sabe? E o nome do navio é 'Wrangler'! Agora a gente pode descobrir tudo sobre o meu pai – quem ele era, como ele veio parar aqui...";
			link.l1 = "Eu estou com medo, "+npchar.name+", você tá apressando as coisas... Pode não ser tão simples quanto parece. O navio de Sua Majestade... A gente vai ter que pensar em quem pode ajudar a conseguir informações nos arquivos da Marinha Real...";
			link.l1.go = "WildRose_Mary_102";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Mary_102":
			dialog.text = "Vamos pensar! Vamos pensar e a gente consegue, "+pchar.name+"! O mais difícil já ficou pra trás, sabe!";
			link.l1 = "Talvez também faça sentido conversar com o senhor Young e o senhor Friddick. Mas eu não me lembro de ninguém com esses nomes na Ilha da Justiça.";
			link.l1.go = "WildRose_Betancur_20_add";
		break;
		
		case "WildRose_Betancur_20_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Porque eles não estão aqui, "+pchar.name+". Esses dois morreram na noite seguinte, logo depois de serem resgatados junto com os Caspers.";
			link.l1 = "Curioso. A mulher grávida sobreviveu por mais uma semana, enquanto dois marinheiros da Marinha Real morreram de repente...";
			link.l1.go = "WildRose_Betancur_22";
		break;

		case "WildRose_Betancur_22":
			dialog.text = " Eles já não estavam bem para começo de conversa, se não me engano. Agora estou lembrando, "+pchar.name+" – Eu estava perto da Ferraria Ceres quando eles foram trazidos a bordo... Sabe, eu estava na Esmeralda com a Orelie Bertine, acho. E também estava lá o Chimiset, aquele xamã dos pagãos negros, que apareceu na loja por algum motivo. No começo, achei que os dois marinheiros já estavam mortos, mas eles só morreram no dia seguinte...";
			link.l1 = "Bem, não tem muito o que a gente possa fazer. Mas já aprendemos bastante coisa. Obrigada pela sua ajuda, Antonio.";
			link.l1.go = "WildRose_Betancur_23";
		break;

		case "WildRose_Betancur_23":
			dialog.text = " Não precisa agradecer, "+pchar.name+". Tudo isso foi graças ao Alan – dificilmente algum daqueles couraceiros teria percebido o verdadeiro valor desses registros. Mas é por meio de documentos assim que a história é resgatada!";
			link.l1 = "Espero que um dia a Mary e eu possamos ler suas Crônicas, sabe? Aqui está seu diário—não perca, hein. Bem, está na hora de irmos. Quem sabe a gente se encontre de novo, meu amigo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_21");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Porque eles não estão aqui, "+pchar.name+". Esses dois morreram na noite seguinte, logo depois de serem resgatados junto com os Caspers.";
			link.l1 = "Curioso. A mulher grávida sobreviveu mais uma semana, mas dois marinheiros da Marinha Real morreram de repente...";
			link.l1.go = "WildRose_Betancur_22";
		break;
		
		case "WildRose_Chimiset_21":
			dialog.text = "Que bom te ver de novo, meu amigo. O que te traz aqui?";
			link.l1 = " A request, +npchar.name+... Or rather, a question.";
			link.l1.go = "WildRose_Chimiset_22";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_22":
			dialog.text = "Faça sua pergunta. Ou peça o que quiser. Vou fazer tudo que puder pra te ajudar.";
			link.l1 = "Sabe? Há quanto tempo você mora na Ilha da Justiça?";
			link.l1.go = "WildRose_Chimiset_23";
		break;

		case "WildRose_Chimiset_23":
			dialog.text = "Décadas e décadas, meu amigo. Vim parar aqui ainda criança, mas já era esperta – a bordo de um navio negreiro. Minha história não é muito diferente das tantas que você já ouviu por aqui. Uma tempestade, um naufrágio... O galeão inglês onde eu estava presa nem chegou ao anel externo, partiu-se ao meio depois de bater num dos recifes para onde as ondas o lançaram.";
			link.l1 = "Como você sobreviveu? Os recifes ficam bem longe do anel externo, e chegar aqui enfrentando ondas e tempestades não é nada fácil, né...";
			link.l1.go = "WildRose_Chimiset_24";
		break;

		case "WildRose_Chimiset_24":
			dialog.text = "Os deuses estavam do meu lado naquela noite. Consegui me soltar das correntes e agarrei um pedaço do que já foi um barco. Tinha um nativo comigo, Asana – juntos lutamos contra as ondas até desmaiar de exaustão.";
			link.l1 = "Você apareceu em um dos navios, né?";
			link.l1.go = "WildRose_Chimiset_25";
		break;

		case "WildRose_Chimiset_25":
			dialog.text = "Sim, a gente se escondeu num buraco no porão... Foi lá que eu apaguei de novo, eu estava tão fraca. Só acordei quando o Asana começou a gritar – ele estava sendo despedaçado por um caranguejo gigante que tinha subido no mesmo navio em que a gente tinha dado à praia. E eu só fiquei lá parada olhando, sabendo que seria a próxima – paralisada de medo e impotência, não consegui me mexer nem um centímetro.";
			link.l1 = "Você podia ter tentado ajudar seu amigo. Mas aí a gente não estaria conversando agora, né? Então, como você conseguiu escapar?";
			link.l1.go = "WildRose_Chimiset_26_1";
			link.l2 = "Você teve sorte que ele não começou por você, "+npchar.name+". Então como você escapou – pulou de volta na água e saiu nadando, sabe?";
			link.l2.go = "WildRose_Chimiset_26_2";
		break;

		case "WildRose_Chimiset_26_1":
			dialog.text = "Alguns Rivados ouviram os gritos da Asana, eles tinham saído para vasculhar os porões dos navios depois do último furacão. Cercaram a criatura e mataram ela. Não havia nada que alguém pudesse fazer pela Asana, mas eu tive bem mais sorte. Foi assim que vim parar aqui. Mas agora é a sua vez, meu amigo – por que você queria saber de tudo isso?";
			link.l1 = "Na verdade, "+npchar.name+", eu ia perguntar não como você veio parar aqui, mas quando isso aconteceu.";
			link.l1.go = "WildRose_Chimiset_27";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_26_2":
			dialog.text = "Os gritos da Asana foram ouvidos por vários Rivados, que tinham saído para caçar cargas de navios depois do último furacão. Eles cercaram a criatura e a mataram. Não havia mais nada a ser feito pela Asana, mas eu tive muito mais sorte. Foi assim que vim parar aqui. Mas agora é a sua vez de responder, meu amigo – por que você quis saber de tudo isso?";
			link.l1 = "Na verdade, "+npchar.name+", eu ia perguntar não como você veio parar aqui, mas quando isso aconteceu.";
			link.l1.go = "WildRose_Chimiset_27";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Chimiset_27":
			dialog.text = "Hum, pelo seu calendário era o ano de 1623, fim do verão – não consigo ser mais precisa do que isso...";
			link.l1 = "Não precisa disso. Então, em 1638, você já estava na Ilha da Justiça há quinze anos.";
			link.l1.go = "WildRose_Chimiset_28";
		break;

		case "WildRose_Chimiset_28":
			dialog.text = "Parece que sim, meu amigo.";
			link.l1 = "Em junho daquele ano, o furacão lançou a brigue 'Wrangler' contra o anel externo — um navio da frota de Sua Majestade, o Rei Carlos I. Só quatro tripulantes sobreviveram — entre eles, os pais da Mary: Joshua e Teresa Casper.";
			link.l1.go = "WildRose_Chimiset_29";
		break;

		case "WildRose_Chimiset_29":
			dialog.text = "Sabe, eu lembro disso, meu amigo. Meio vago, como se fosse através de uma névoa, mas eu lembro...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_29_add";
		break;
		
		case "WildRose_Chimiset_29_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_30":
			dialog.text = "Você lembra mesmo? Então me conta, vai!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_30_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_30_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_31":
			dialog.text = "Não posso dizer muito. Quatro pessoas: um oficial, a esposa dele e dois marinheiros. A mulher estava grávida, e quem os resgatou achou que ela não sobreviveria até de manhã – mas ela era forte como uma leoa, enquanto os dois marinheiros deixaram este mundo em menos de um dia... Eu vi eles: estavam fracos, mas ainda tinham um restinho de vida...";
			link.l1 = "Você está sugerindo que eles foram mortos?";
			link.l1.go = "WildRose_Chimiset_32";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_32":
			dialog.text = "Se é assim, então não havia testemunhas disso, nem ferimentos nos corpos deles, meu amigo...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_32_add";
		break;
		
		case "WildRose_Chimiset_32_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_33", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_33":
			dialog.text = "Você disse 'oficial', sabe... Meu pai era mesmo um oficial?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_33_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_33_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_34":
			dialog.text = "Ele estava usando um uniforme de oficial – acho que é a única coisa que consigo lembrar quando tento recordar como ele era.";
			link.l1 = "Se ele era um oficial, então não podia usar outra coisa – duvido que o guarda-roupa dele fosse muito variado... Talvez você lembre de algum outro detalhe, "+npchar.name+"? Alguma característica marcante... Tipo, uma cicatriz no rosto, ou talvez algum outro machucado...";
			link.l1.go = "WildRose_Chimiset_35";
		break;
		
		case "WildRose_Chimiset_35":
			dialog.text = "Não me lembro de muita coisa, sabe? O rosto dele quase sumiu da minha memória – já faz vinte anos... Mas o olhar dele – disso eu me lembro perfeitamente. Falei com esse homem só uma vez, mas aquele olhar nos olhos cinzentos – igualzinho aos da Mary – isso eu nunca vou esquecer. Havia desespero ali, um medo de animal acuado, e ao mesmo tempo – uma fúria e uma determinação dignas de um leão...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_35_add";
		break;
		
		case "WildRose_Chimiset_35_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_36":
			dialog.text = "Você falou com ele, sabe? Sobre o quê?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_36_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_36_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_37":
			dialog.text = "Aconteceu algumas horas antes de você nascer. Ele veio aqui, ao 'Protetor', e exigiu me ver. O líder dos Rivados, Mogedi, ficou surpreso com a ousadia dele – mas, de repente, eu me vi intrigada por esse homem. Quando ele ficou diante de mim, caiu de joelhos e implorou para que eu salvasse a esposa dele... Alguém, no pouco tempo em que estiveram aqui, conseguiu contar para ele sobre mim. Eu aceitei, mesmo com a objeção do Mogedi...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_37_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_37_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_38":
			dialog.text = " Então isso quer dizer que eu te devo a minha vida?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_38_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_38_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_39", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_39":
			dialog.text = "Não adianta mentir – conseguimos chegar até sua mãe, mas já era tarde: os Narvais não me deixaram entrar no ‘Ceres Smithy’. Seu pai conseguiu... convencê-los, mas eu só vi a pobre Teresa quando ela estava dando seu último suspiro. Ela te deu à luz, e se eu tivesse chegado antes, talvez eu pudesse ter salvado ela, mas...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_39_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_39_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_40", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_40":
			dialog.text = "Minha mãe morreu.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_40_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_40_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_41", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_41":
			dialog.text = "Ela olhou pra você e deu seu último suspiro, sabe? Mas antes disso, como se juntasse todas as forças, ela chamou alguém chamado Rupert. Gritou o nome dele o mais alto que pôde, como se pedisse socorro – e aí morreu.";
			link.l1 = "Rupert? Não era Joshua?";
			link.l1.go = "WildRose_Chimiset_42";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_42":
			dialog.text = "Enquanto eu te contava isso, meu amigo, parecia que eu estava revivendo aquele momento de novo. Nunca vou esquecer – nem o grito de morte dela, nem o rosto dela contorcido de dor. E sabe, a última coisa que saiu dos lábios dela foi 'Rupert'.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_42_add";
		break;
		
		case "WildRose_Chimiset_42_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_43":
			dialog.text = "Ela era bonita, minha mãe? Você pode descrever como ela era, Chimiset?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_43_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_43_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_44", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_44":
			dialog.text = " Não precisa disso, Mary. Olhe no espelho – você é a cara dela. Só esse olhar penetrante veio do seu pai.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_44_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_44_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_45", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_45":
			dialog.text = "E o que aconteceu com ele, hein? Conseguimos descobrir que só alguns dias depois que eu nasci, ele sumiu sem deixar rastro, sabe? Mas ele não foi morto, foi?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_45_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_45_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_46", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_46":
			dialog.text = "Assim que disseram que a Teresa estava morrendo, o Joshua ficou completamente furioso – juro, nem mesmo os leões na savana atacam suas presas com a fúria que seu pai mostrou quando foi atrás daqueles narvais que não me deixavam tocar flauta... Foram necessários uns seis homens pra segurar ele – e isso depois de ele já ter jogado dois guerreiros do clã na água, com armadura e tudo.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_46_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_46_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_47", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_47":
			dialog.text = "E o que fizeram com ele - me conta, vai!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_47_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_47_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_48", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_48":
			dialog.text = "Jogaram ele numa das celas do 'Tártaro'. Ninguém teve coragem de julgá-lo—queriam que a história esfriasse primeiro... Quase todo mundo sentiu pena dele, mas poucos queriam viver ao lado de um homem assim. Joshua sumiu alguns dias depois—mais ou menos na mesma época, vários barcos de contrabandistas deixaram a Ilha da Justiça. Ninguém viu ele nos barcos, e foi aí que começaram os boatos sobre a morte dele.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_48_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_48_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_49", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_49":
			dialog.text = "Então você acha que ele está vivo, sabe?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_49_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_49_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_50", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_50":
			dialog.text = "Vou dizer o que todo mundo vai te contar também, sabe – nunca encontraram o corpo dele. Vai ver ele se escondeu no fundo de algum dos barcos, ou talvez cortaram a garganta dele naquela cela e jogaram pros caranguejos...";
			link.l1 = "O fato de ele ter desaparecido justamente quando aqueles mercadores zarparam aponta mais para a primeira opção – não existem coincidências assim. E talvez ele tenha deixado escapar alguma coisa sobre seus planos para alguém? Se ele fugiu, então fugiu, deixando a filha recém-nascida aqui, o que, de certo modo, faz sentido – um bebê talvez não sobrevivesse à viagem até Cuba num barquinho frágil... Mas com certeza ele pretendia voltar para buscá-la.";
			link.l1.go = "WildRose_Chimiset_51";
		break;
		
		case "WildRose_Chimiset_51":
			dialog.text = "Eu não saberia dizer, meu amigo. Se Joshua Casper conversou com alguém naquela época, só poderia ter sido com seus carcereiros – mas todos eles já deixaram este mundo pecaminoso faz tempo. Ah, e sim, um dia o Padre Domingo veio vê-lo – ele era o padre dos brancos antes do Irmão Julian...";
			link.l1 = "Será que ele queria se declarar ou algo assim? Acho que ele tinha medo de morrer durante a fuga.";
			link.l1.go = "WildRose_Chimiset_52";
		break;

		case "WildRose_Chimiset_52":
			dialog.text = "Não posso esclarecer o que não sei, meu amigo. E o Domingo também não vai te contar nada – ele está morto faz uns quinze anos já, sabe? Vai ver alguém deu uma pancada na cabeça dele, vai ver ele só bebeu até morrer – ele gostava bastante disso...";
			link.l1 = "Mas talvez o Domingo tenha mantido um diário... ou contado ao irmão dele, o Julian, sobre aquela conversa com o Joshua?";
			link.l1.go = "WildRose_Chimiset_52_add";
		break;
		
		case "WildRose_Chimiset_52_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_53", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_53":
			dialog.text = "Precisamos falar com ele, "+pchar.name+", sabe? E quanto antes, melhor. Nem quero pensar em voltar pro navio até a gente resolver isso.";
			link.l1 = "Se é que ainda tem algo pra descobrir. Talvez o Julian nem saiba disso – mas a gente vai chegar ao fundo dessa história. Obrigada, Chimiset.";
			link.l1.go = "WildRose_Chimiset_53_add";
		break;
		
		case "WildRose_Chimiset_53_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_54", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_54":
			dialog.text = "Sempre estou ao seu dispor, meu amigo. Mas deixa eu te dar um conselho, sabe?";
			link.l1 = " E o que é isso?";
			link.l1.go = "WildRose_Chimiset_55";
		break;
		
		case "WildRose_Chimiset_55":
			dialog.text = "Quando você sair para caçar, não se aventure muito fundo nos matagais — pode ser que nunca encontre o caminho de volta.";
			link.l1 = "Vamos lembrar disso, xamã. E agora – adeus.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_22");
		break;
		
		case "WildRose_Julian_1":
			dialog.text = "Sejam bem-vindos ao abrigo da casa de Deus, meus filhos. Vieram se confessar, ou só querem rezar?";
			link.l1 = "Saudações, Irmão Julian. Acho que listar nossos pecados levaria tempo demais, que infelizmente não temos. Mas pode ficar tranquilo, como bons católicos, a gente vai à igreja em todo porto.";
			link.l1.go = "WildRose_Julian_2_1";
			link.l2 = "Saudações, Irmão Julian. Como católicos devotos, começamos nosso dia com uma oração ao nosso Senhor e terminamos do mesmo jeito.";
			link.l2.go = "WildRose_Julian_2_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Julian_2_1":
			dialog.text = " Bons católicos vivendo juntos sem serem casados, sob o mesmo teto... Isso beira a blasfêmia, meu filho. E isso, lembro você, é um pecado mortal!";
			link.l1 = "E as Escrituras não dizem que o amor cobre todos os pecados?";
			link.l1.go = "WildRose_Julian_3";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Julian_2_2":
			dialog.text = " Bons católicos vivendo juntos, sem serem casados, sob o mesmo teto... Isso beira a blasfêmia, meu filho. E isso, lembro você, é um pecado mortal!";
			link.l1 = "E as Escrituras não dizem que o amor cobre todos os pecados?";
			link.l1.go = "WildRose_Julian_3";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_3":
			dialog.text = "O amor é viver segundo os mandamentos Dele – preciso te lembrar quais são, meu filho?";
			link.l1 = "Outra hora. Estamos aqui por outros motivos.";
			link.l1.go = "WildRose_Julian_4";
		break;

		case "WildRose_Julian_4":
			dialog.text = "Nunca é tarde demais para almas perdidas encontrarem o caminho de volta para a estrada certa... Mas estou ouvindo vocês, meus filhos.";
			link.l1 = "A gente realmente se perdeu um pouco, Irmão Julian. Perdidos nos espinhos do passado. E esperamos que você possa nos ajudar a encontrar o caminho de volta pra luz.";
			link.l1.go = "WildRose_Julian_5";
		break;

		case "WildRose_Julian_5":
			dialog.text = "Muito espirituoso, meu filho. Mas lembre-se de que não é o homem que conduz à luz, e sim o Senhor – e ao segui-Lo, lembre-se de que Seus caminhos são misteriosos.";
			link.l1 = "Vou ser breve, Irmão Julian. Estamos tentando descobrir tudo o que pudermos sobre os pais da Mary. Sobre a mãe dela, Teresa, as coisas estão mais ou menos claras—ela chegou na Ilha da Justiça com o marido e morreu de parto uma semana depois. Mas o pai dela... Ele sumiu poucos dias depois que a Mary nasceu, fugindo do 'Tártaro'. Dizem que a última pessoa com quem ele falou aqui foi o Padre Domingo—seu antecessor.";
			link.l1.go = "WildRose_Julian_6";
		break;

		case "WildRose_Julian_6":
			dialog.text = "Então vocês chegaram mais de quinze anos tarde demais, meus filhos.";
			link.l1 = "Sim, a gente sabe que o padre morreu faz bastante tempo. E naquela época, Irmão Julian, você ainda era jovem demais pra ter chegado à Ilha com o posto certo, não é?";
			link.l1.go = "WildRose_Julian_7";
		break;

		case "WildRose_Julian_7":
			dialog.text = "Eu vim parar aqui alguns anos depois da morte dele. Deu muito trabalho pra colocar tudo em ordem aqui, neste navio, mas com a ajuda de Deus eu consegui, meu filho.";
			link.l1 = "Enquanto você resolvia as coisas aqui, por acaso encontrou algum registro do Padre Domingo?";
			link.l1.go = "WildRose_Julian_8";
		break;

		case "WildRose_Julian_8":
			dialog.text = "Você está falando de algo específico, meu filho?";
			link.l1 = "Estamos procurando diários ou algum tipo de registro... Não temos muita esperança de um milagre, mas talvez o padre tenha anotado o que foi dito naquela conversa em algum dos seus cadernos. Acreditamos que o pai da Mary deixou a ilha em um dos barcos dos contrabandistas—talvez ele tenha dado alguma pista ao padre sobre para onde ia e quando voltaria para buscar a filha?";
			link.l1.go = "WildRose_Julian_9";
		break;

		case "WildRose_Julian_9":
			dialog.text = "Eu nunca encontrei diários nem nada desse tipo, isso é certo, mas havia todo tipo de registros... Quando se tratava de assuntos da igreja, ele era bem meticuloso — nem todo servo do Senhor é abençoado com tanta minúcia. Mas os papéis dele só tinham números e nomes secos — nada além disso.";
			link.l1 = "Pelo que conseguimos descobrir, Joshua Casper – esse era o nome dele – num acesso de fúria após a morte da esposa, matou dois membros do clã Narval que se recusaram a deixar o feiticeiro rivado Chimiseta ver a mãe da Mary...";
			link.l1.go = "WildRose_Julian_10";
		break;

		case "WildRose_Julian_10":
			dialog.text = "Eles agiram como verdadeiros filhos da Igreja! As masmorras da Inquisição estão só esperando por esse servo do Diabo!";
			link.l1 = "Deus, acho que Ele ficaria horrorizado se soubesse quantas pessoas já foram torturadas em nome d’Ele. O Casper teve mais sorte – só jogaram ele numa cela no ‘Tártaro’, mas ele nunca chegou a ser julgado.";
			link.l1.go = "WildRose_Julian_11_1";
			link.l2 = "Sim, sim, sem dúvida. Casper foi jogado em uma das celas do 'Tártaro', mas não houve sentença — nem todos condenaram as ações de um marido que perdeu a esposa.";
			link.l2.go = "WildRose_Julian_11_2";
		break;

		case "WildRose_Julian_11_1":
			dialog.text = "O que aconteceu depois – aquele herege conseguiu fugir?";
			link.l1 = "Menos de uma semana depois, Joshua sumiu. E na noite anterior, o Padre Domingo foi visitá-lo. Então a pergunta é—por quê? Não parece provável que um protestante, como o Casper certamente era, fosse se confessar com um padre católico—não acha?";
			link.l1.go = "WildRose_Julian_12";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_11_2":
			dialog.text = "O que aconteceu depois – aquele herege conseguiu fugir?";
			link.l1 = "Menos de uma semana depois, Joshua desapareceu. E na noite anterior, o Padre Domingo foi vê-lo. Então a pergunta é – por quê? É difícil acreditar que um protestante, como o Casper certamente era, fosse se confessar com um padre católico – o que você acha?";
			link.l1.go = "WildRose_Julian_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Julian_12":
			dialog.text = "Nunca é tarde demais para se voltar à verdadeira fé, meu filho. Mas seu raciocínio faz sentido. Se ele não precisava de confissão, talvez estivesse conversando com o padre sobre o funeral da esposa — se, é claro, ela fosse católica. Ou talvez sobre o batismo da filha, ou melhor, a recusa dele, já que os protestantes não batizam bebês, acreditando que a pessoa deve decidir ser batizada de forma independente e consciente.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_12_add";
		break;
		
		case "WildRose_Julian_12_add":
			StartInstantDialog("Mary", "WildRose_Julian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_13":
			dialog.text = "Mas eu fui batizada, Irmão Julian. O Eric Udette me contou sobre isso.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_13_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_13_add":
			StartInstantDialog("Julian", "WildRose_Julian_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_14":
			dialog.text = "Essas são apenas as minhas suposições, minha filha. A verdade me é desconhecida. O Senhor nos revela apenas o que é realmente importante e necessário.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_14_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_14_add":
			StartInstantDialog("Mary", "WildRose_Julian_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_15":
			dialog.text = "E é exatamente assim pra mim, sabe? Talvez ainda tenha alguma coisa nas páginas dos registros do Padre Domingo que você não percebeu, Irmão Julian. Afinal, você só deu uma olhada rápida, não foi?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_15_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_15_add":
			StartInstantDialog("Julian", "WildRose_Julian_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_16":
			dialog.text = "I had no business there, my child. I can see you've been working on this for a long time, and with great care – the Lord is guiding you down this thorny path. If you are meant to find what you seek, then it is His will, and it is not for me to stand in its way. I can give you Domingo's records from the year you were born; perhaps you'll find something useful in them.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_16_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_16_add":
			StartInstantDialog("Mary", "WildRose_Julian_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_17":
			dialog.text = "Isso seria muito generoso da sua parte, Irmão Julian. Você ainda tem os registros de 1638?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_17_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;
		
		case "WildRose_Julian_17_add":
			StartInstantDialog("Julian", "WildRose_Julian_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_18":
			dialog.text = "Então, então... (assopra a poeira). Parece que é isso. O livro-caixa do ano de 1638, Ano Domini.";
			link.l1 = "Permita-me, Irmão Julian...";
			link.l1.go = "exit";
			AddQuestRecordInfo("WildRose_Records_2", "1");
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_23");
		break;
		
		case "WildRose_Mary_111":
			dialog.text = "Olha, "+pchar.name+": 3 de agosto. Esse é o dia em que Fabian e eu fomos batizados. Eu nasci em 22 de junho. Mas nem uma palavra sobre meu pai, sabe.";
			link.l1 = "Assim como o Irmão Julian disse – nada além de números frios e nomes. O curioso é que o Padre Domingo era tão dedicado ao seu dever que chegou a dar a extrema-unção até para protestantes – duvido que van Ekkus, Young e Friddicks fossem católicos.";
			link.l1.go = "WildRose_Mary_111_add";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Mary_111_add":
			StartInstantDialog("Julian", "WildRose_Mary_112", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_112":
			dialog.text = "Podiam muito bem ter se voltado para a verdadeira fé bem na porta de entrar no Reino dos Céus, meu filho.";
			link.l1 = "Claro, irmão Julian—o que mais eles fariam? Principalmente se morreram como Soren e Rojas—acho que são justamente esses Narvais que impediram o caminho de Chimiset.";
			link.l1.go = "WildRose_Mary_112_add";
		break;
		
		case "WildRose_Mary_112_add":
			StartInstantDialog("Mary", "WildRose_Mary_113", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_113":
			dialog.text = "Seria melhor se o Padre Domingo escrevesse os nomes do meio completos, sabe? O que esses ‘V.’ e ‘J.’ depois do nome da minha mãe e do meu querem dizer mesmo?";
			link.l1 = "E quem é esse Fabian, aquele que foi batizado no mesmo dia que você?";
			link.l1.go = "WildRose_Mary_114";
		break;
		
		case "WildRose_Mary_114":
			dialog.text = "Filho da Cecille Halard. Ah, acabei de lembrar! Ela me criou, mas nunca foi muito carinhosa. Provavelmente porque eu sobrevivi e o Fabian não. Ele morreu alguns meses depois de nascer, sabe.";
			link.l1 = "Talvez a gente devesse falar com ela, já que quase não descobrimos nada de útil nesse livrinho—a não ser, claro, se você considerar as datas do seu nascimento e batismo.";
			link.l1.go = "WildRose_Mary_115";
		break;

		case "WildRose_Mary_115":
			dialog.text = "Ela não é muito mais nova que a Orelie, "+pchar.name+"   Tudo que podemos fazer é torcer para que pelo menos ela tenha juízo, sabe? Mas o que você pretende perguntar pra ela?";
			link.l1 = "Bem, já que ela era sua ama, talvez soubesse de alguns detalhes pelo Padre Domingo sobre a conversa dele com Joshua. Quem mais ele contaria, se não pra ela? Talvez pra Orelie ou pro Eric também. Mas acho que já tiramos tudo que podíamos da primeira, e o segundo não vai contar mais nada pra ninguém.";
			link.l1.go = "WildRose_Mary_115_add";
		break;
		
		case "WildRose_Mary_115_add":
			StartInstantDialog("Julian", "WildRose_Mary_116", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_116":
			dialog.text = "Essa boa mulher é uma devota desta casa de Deus. Nunca perde uma missa e se confessa regularmente. Acredito que ela realmente pode ajudar vocês, meus filhos.";
			link.l1 = "Obrigada, pai. Adeus.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_24");
		break;
		
		case "WildRose_Sesil_1":
			dialog.text = ""+GetFullName(pchar)+" e Mary Casper. Que surpresa agradável!";
			link.l1 = "Da mesma forma, "+npchar.name+". Na verdade, viemos te ver. Tem algo que gostaríamos de conversar com você.";
			link.l1.go = "WildRose_Sesil_2";
			DelLandQuestMark(npchar);
			LAi_SetStayType(npchar);
		break;
		
		case "WildRose_Sesil_2":
			dialog.text = "Ah, é mesmo? Então, você tem toda a minha atenção.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_2_add";
		break;
		
		case "WildRose_Sesil_2_add":
			StartInstantDialog("Mary", "WildRose_Sesil_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Sesil_3":
			dialog.text = "Isso é sobre meus pais, Cecille. Já descobrimos tudo que podíamos sobre minha mãe... Ela morreu logo depois que eu nasci. Mas meu pai... ele sumiu sem deixar rastro só alguns dias depois. A gente costuma pensar que ele não morreu, sabe?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_3_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_4":
			dialog.text = " De fato, teria sido preciso um bom esforço pra mandar um homem como ele pro outro mundo...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_4_add":
			StartInstantDialog("Mary", "WildRose_Sesil_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_5":
			dialog.text = "Você viu ele?! Você falou com ele?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_5_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_6":
			dialog.text = "Minha garota, eu vi ele derrubar dois Narvais só com as próprias mãos, quase...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_6_add":
			StartInstantDialog("Mary", "WildRose_Sesil_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_7":
			dialog.text = "Sorreno e Rojas?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_7_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_8":
			dialog.text = "Naquela época eu estava cheia de coisa pra fazer, sabe? Nem dava pra lembrar o nome daqueles canalhas – e agora não me lembro de jeito nenhum.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_8_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_8_add":
			StartInstantDialog("Mary", "WildRose_Sesil_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_9":
			dialog.text = "Sabe, não importa. Por favor, continue, Cecille.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_9_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_9_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_10", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_10":
			dialog.text = "E o que mais tinha pra continuar, sabe? Ele jogou aqueles dois no mar, afundaram feito pedra, aí amarraram ele e levaram pro 'Tártaro'. E fizeram muito bem – vai saber quem mais aquele desgraçado ia querer afogar...";
			link.l1 = "Cruel? Isso é um pouco pesado, não acha, dona Halard? Estamos falando de um homem aqui, um oficial que acabou de perder a esposa...";
			link.l1.go = "WildRose_Sesil_11_1";
			link.l2 = "Vejo que você não tem lá muita consideração por ele – nem todo oficial é comentado desse jeito, sabe?";
			link.l2.go = "WildRose_Sesil_11_2";
		break;

		case "WildRose_Sesil_11_1":
			dialog.text = "Oficial, olha só. O uniforme dele era realmente impressionante, lembro perfeitamente. Praticamente novo em folha. Mas já vi muitos oficiais na minha vida, rapaz. E todos eles se comportaram de forma muito mais decente do que aquele... cavalheiro.";
			link.l1 = "Ele fez mais alguma coisa? Além de matar aqueles dois?";
			link.l1.go = "WildRose_Sesil_12";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;

		case "WildRose_Sesil_11_2":
			dialog.text = "Oficial, olha só. O uniforme dele era realmente impressionante, lembro perfeitamente. Quase novo em folha, parecia ter saído direto das mãos do alfaiate. Mas já vi muitos oficiais na minha vida, sabe? E todos eles se comportaram de maneira muito mais decente do que esse... cavalheiro.";
			link.l1 = "Ele fez mais alguma coisa? Além de matar aqueles dois?";
			link.l1.go = "WildRose_Sesil_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Sesil_12":
			dialog.text = "Ele exigiu ver um padre na cela – o Padre De la Cruz...";
			link.l1 = "Olha só! Era exatamente sobre isso que a gente queria falar com você. Você sabe dos detalhes dessa conversa?";
			link.l1.go = "WildRose_Sesil_13";
		break;

		case "WildRose_Sesil_13":
			dialog.text = "Claro, rapaz! Aquele canalha protestante exigiu que o padre não batizasse a filha dele — mesmo a mãe sendo irlandesa, e portanto católica.";
			link.l1 = "É quase a primeira vez que ouço uma inglesa falar assim de um protestante... Hã, me desculpe por interromper, senhora. "+npchar.lastname+".";
			link.l1.go = "WildRose_Sesil_14";
		break;

		case "WildRose_Sesil_14":
			dialog.text = "Eu mesma já fui protestante, não adianta esconder. Mas o Irmão Julian conseguiu me colocar no caminho certo.";
			link.l1 = "Então é assim... Realmente um servo devoto do Senhor. Mas nos desviamos do assunto. Então, Casper queria que a filha fosse criada na fé protestante.";
			link.l1.go = "WildRose_Sesil_15";
		break;

		case "WildRose_Sesil_15":
			dialog.text = "Foi exatamente isso que ele contou para o nosso padre De la Cruz. E também mandou que dessem o nome de Julia para a menina...";
			link.l1 = "Então é isso que o 'J.' significa. Mary Julia Casper... Mas então por que chamavam ela de Mary?";
			link.l1.go = "WildRose_Sesil_16";
		break;

		case "WildRose_Sesil_16":
			dialog.text = "Porque era isso que a mãe dela queria, sabe? Quando tiraram a menina do ventre dela, ela sussurrou um nome – Mary. Eu não estava lá pra ver, mas a Orelie Bertine estava no parto. Se quiser, pode perguntar pra ela...";
			link.l1 = "Então você fez o que sua mãe queria, né?";
			link.l1.go = "WildRose_Sesil_17";
		break;

		case "WildRose_Sesil_17":
			dialog.text = " E como poderia ser diferente, quando o pai sumiu do nada, como se tivesse evaporado no ar?";
			link.l1 = "Considerando... os talentos do Padre De la Cruz, duvido que a opinião do pai teria feito diferença, mesmo se ele tivesse ficado no Tartarus. O Domingo não te contou—ele não sabia dos planos do Casper de fugir e talvez voltar pra buscar a garota?";
			link.l1.go = "WildRose_Sesil_18_1";
			link.l2 = "Talvez você tenha razão. Mas voltando à conversa do Padre Domingo com o Sr. Casper — o padre comentou se o Joshua falou com ele sobre fugir, ou quando ele poderia voltar para buscar a filha?";
			link.l2.go = "WildRose_Sesil_18_2";
		break;

		case "WildRose_Sesil_18_1":
			dialog.text = " Ele não falou nada disso. E pensa bem, "+npchar.name+", se você estivesse planejando fugir da prisão, sairia contando pra qualquer um que passasse? Aquele cara com certeza não faria isso, pode apostar.";
			link.l1 = "Então, essa pista também não nos levou a lugar nenhum. Bem, obrigada pelo seu tempo, senhora. "+npchar.lastname+". Até mais, sabe?";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", -1);
			AddCharacterExpToSkill(pchar, "charisma", 100);
		break;

		case "WildRose_Sesil_18_2":
			dialog.text = " Ele não falou nada disso. E pensa bem, "+npchar.name+", se você estivesse planejando fugir da prisão, sairia contando pra qualquer um que passasse? Aquele cara com certeza não faria isso, pode apostar.";
			link.l1 = "Então, essa pista não levou a lugar nenhum. Bom, obrigada pelo seu tempo, senhora. "+npchar.lastname+". Até mais, sabe?";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;
		
		case "WildRose_Sesil_19":
			StartInstantDialog("Mary", "WildRose_Mary_121", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_121":
			dialog.text = "Descobrimos algumas coisas bem interessantes, "+pchar.name+". Mas a gente mal fez algum progresso, sabe.";
			link.l1 = "E a gente até se enrolou um pouco. Quem será esse tal de Rupert que sua mãe chamou antes de morrer, hein?";
			link.l1.go = "WildRose_Mary_122";
		break;

		case "WildRose_Mary_122":
			dialog.text = "Talvez um irmão, ou... um amigo próximo?";
			link.l1 = "Amigo, você diz, né... Será que o Joshua sabia dele...";
			link.l1.go = "WildRose_Mary_123";
		break;

		case "WildRose_Mary_123":
			dialog.text = "O que você quer dizer, "+pchar.name+"?";
			link.l1 = "A gente precisa pensar em tudo isso direito, sabe? Ainda bem que vamos ter bastante tempo pra isso enquanto procuramos alguém que possa ajudar a gente nessa busca. Já fizemos muita coisa. Mas ainda não terminamos. Não conseguimos entrar no escritório da Marinha Real sozinhos, e ele fica lá do outro lado do oceano, em Londres... Tem alguma ideia de quem poderia ajudar a gente com isso?";
			link.l1.go = "WildRose_Mary_127";
		break;
		
		case "WildRose_Mary_127":
			dialog.text = "E o Serge Benoit, Charles?";
			link.l1 = "Abade? Ele tem boas conexões, isso é verdade, mas duvido que consiga entrar nos arquivos da Marinha Real.";
			link.l1.go = "WildRose_Mary_128";
		break;
		
		case "WildRose_Mary_128":
			dialog.text = "Se ele não conseguir fazer isso sozinho, talvez ele nos coloque em contato com alguém que consiga, sabe.";
			link.l1 = "Acho que sim. Então, estamos indo para Saint-Pierre.";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_25");
		break;
		
		// =================================================================
		// =================== ЭТАП 3. «БУМАЖНАЯ РАБОТА» ===================
		// =================================================================
		
		case "WildRose_Mary_131":
			dialog.text = "Bom, agora tudo que a gente pode fazer é esperar, sabe.";
			link.l1 = "Tenho certeza de que ele vai descobrir tudo, "+npchar.name+" O tempo vai passar voando, você nem vai perceber. E por enquanto – temos coisas pra fazer.";
			link.l1.go = "WildRose_Mary_132";
		break;

		case "WildRose_Mary_132":
			dialog.text = "Você está insinuando alguma coisa em especial, querido?";
			link.l1 = "A gente tem muita coisa pra fazer, mas que tal voltar pro navio, trancar a porta e passar um tempo juntos? O que você acha, sabe?";
			link.l1.go = "WildRose_Mary_133";
		break;

		case "WildRose_Mary_133":
			dialog.text = "E eu sabia que você ia sugerir isso, sabe! Então, olha só: vamos direto ao ponto, sem perder tempo!";
			link.l1 = "Vem cá, meu amor.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_3");
		break;
		
		case "WildRose_Mary_134":
			dialog.text = "Oh, "+pchar.name+", você não faz ideia, você simplesmente não faz ideia do peso que acabou de sair da minha alma, sabe!";
			link.l1 = "Eu posso imaginar, querido – você está praticamente brilhando, sabe? Ha-ha! Como pode ver, valeu a pena.";
			link.l1.go = "WildRose_Mary_135";
		break;

		case "WildRose_Mary_135":
			dialog.text = "Meu pai foi um oficial famoso, acredita? Mas é uma pena que a gente nunca tenha se encontrado. E nem sabemos se ele chegou ao continente, sabe...";
			link.l1 = "Se isso tivesse acontecido, ele com certeza teria voltado ao serviço, e alguém, em algum lugar, teria ouvido algo sobre ele, sabe? Um homem desses nunca conseguiria ficar parado – senão, de onde você teria tirado isso?";
			link.l1.go = "WildRose_Mary_136";
		break;

		case "WildRose_Mary_136":
			dialog.text = "Você acha mesmo que ele morreu? Que acabou nas mãos dos espanhóis em Cuba, ou foi morto na Ilha da Justiça?";
			link.l1 = "Eu tento ver as coisas de forma realista, "+npchar.name+". Naquela época, ainda havia algum movimento com a Ilha da Justiça. Contrabandistas levavam suas tartanas pra lá com frequência. Se ele tivesse conseguido sair, não tenho dúvida de que teria voltado pra te buscar, sabe?";
			link.l1.go = "WildRose_Mary_137";
		break;

		case "WildRose_Mary_137":
			dialog.text = "Para me tirar de lá. Mas aí a gente não teria se conhecido, sabe.";
			link.l1 = "É assim que a vida é, querido. Você nunca sabe onde vai encontrar alguma coisa, ou onde vai perdê-la. Espero que você não se arrependa de estar aqui comigo, agora.";
			link.l1.go = "WildRose_Mary_138";
		break;

		case "WildRose_Mary_138":
			dialog.text = "Eu nunca ouvi nada mais ridículo na minha vida, sabe! "+pchar.name+", você é incrível, é maravilhoso! Obrigada por se esforçar tanto pra me ajudar a entender tudo isso. Isso significa muito pra mim, sabe! Mas vamos dar uma olhada nos documentos—vai que a gente acha alguma coisa lá que nosso amigo não contou pra gente...";
			link.l1 = "Boa ideia. Vamos começar agora mesmo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_7");
		break;
		
		case "WildRose_Mary_139":
			dialog.text = "Bem, "+pchar.name+", percebeu algo interessante?";
			link.l1 = "Sabe, "+npchar.name+". Tem alguma coisa...";
			link.l1.go = "WildRose_Mary_140";
		break;

		case "WildRose_Mary_140":
			dialog.text = "Você está com uma cara de quem viu fantasma, sabe.";
			link.l1 = "Menciona um tal de Rupert Northwood.";
			link.l1.go = "WildRose_Mary_141";
		break;

		case "WildRose_Mary_141":
			dialog.text = "Rupert Northwood?! É mesmo ele?";
			link.l1 = "Quiet, "+npchar.name+" - não grita assim. Hmm... Acho que sim, sabe – é dessa pessoa que a Chimiset estava falando. Não pode ser outra – essas coincidências não existem.";
			link.l1.go = "WildRose_Mary_142";
		break;

		case "WildRose_Mary_142":
			dialog.text = "E o que você acha de tudo isso, "+pchar.name+"?";
			link.l1 = "Essa história está ficando cada vez mais enrolada. Então... o 'Cornwall' partiu de Plymouth, o 'Cornwall' também chegou em Antígua, mas foi o 'Wrangler' que naufragou nos recifes da Ilha da Justiça – com o mesmo Joshua Casper no comando, que de algum jeito conseguiu se casar às escondidas com uma mulher sem que a Marinha soubesse, uma mulher que, em seu último suspiro, chamava por alguém chamado Rupert.";
			link.l1.go = "WildRose_Mary_143";
		break;

		case "WildRose_Mary_143":
			dialog.text = "Eu não entendo nada disso. Nem sei quem mais poderia esclarecer alguma coisa. Quanto mais tentamos descobrir sobre meu pai, mais afundamos nesse pântano de segredos e mistérios, sabe.";
			link.l1 = "Se alguém pode esclarecer isso, é o Joshua Casper ou o Rupert Northwood.";
			link.l1.go = "WildRose_Mary_144";
		break;

		case "WildRose_Mary_144":
			dialog.text = "Northwood? Mas ele está morto, sabe? Você não acha mesmo que o relatório entregue quando o 'Cornwall' chegou em St. John’s foi falsificado?";
			link.l1 = "Ah, essa sua ingenuidade, "+npchar.name+"... Estou começando a achar que essa história toda está mergulhada em mentiras. Pensa comigo: Joshua Casper era um oficial exemplar – cheio de medalhas e sem uma única advertência. Isso não bate com o que a gente descobriu sobre ele na Ilha da Justiça, onde ele mandou dois homens pra cova sem nem hesitar, sabe?";
			link.l1.go = "WildRose_Mary_145";
		break;

		case "WildRose_Mary_145":
			dialog.text = "Ele lutou pela vida da esposa dele, minha mãe, "+pchar.name+"!";
			link.l1 = "Claro, mas então de onde ela veio afinal? E mais importante, por que ele escondeu o casamento da Almirantado? Um homem de carreira, sempre fiel ao dever e às regras, senão o histórico dele não seria tão impecável, e de repente faz uma dessas.";
			link.l1.go = "WildRose_Mary_146";
		break;

		case "WildRose_Mary_146":
			dialog.text = "E se por trás de tudo isso tiver uma história linda, cheia de romance? Às vezes acontece, mesmo que seja raro, sabe?";
			link.l1 = "Não me leve a mal, Mary, mas isso não parece nada com uma história de amor. Parece mais uma encenação, e até agora não entendi qual era o objetivo de tudo isso. Por que mudar o nome do navio a caminho de Providence? É um navio de guerra—essas coisas podem te colocar diante de um tribunal.";
			link.l1.go = "WildRose_Mary_147";
		break;

		case "WildRose_Mary_147":
			dialog.text = "Concordo – boa pergunta.";
			link.l1 = "E tem algo muito estranho com esse tal de Rupert Northwood. Quase metade da tripulação morreu naquela batalha, mas, curiosamente, nenhum oficial morreu, só ele ficou. E por que a Teresa chamou pelo Rupert no leito de morte, e não pelo marido dela, o Joshua?";
			link.l1.go = "WildRose_Mary_148";
		break;

		case "WildRose_Mary_148":
			dialog.text = "Então, você tem mesmo certeza de que o imediato não morreu lutando contra os espanhóis, né? E eu não sou filha do Joshua Casper coisa nenhuma, mas sim do Rupert Northwood – é isso que você está dizendo?";
			link.l1 = "Como eu já disse – só uma pessoa sabe a verdade. Ou Joshua Casper, que por algum motivo chamava Teresa de esposa, ou Rupert Northwood, que, por razões tão misteriosas quanto, assumiu o nome do capitão.";
			link.l1.go = "WildRose_Mary_149";
		break;

		case "WildRose_Mary_149":
			dialog.text = "Que bagunça dos diabos, sabe? E agora, o que a gente faz, "+pchar.name+"? Agora eu quero descobrir a verdade ainda mais, mas já tiramos tudo o que podíamos de todo mundo, sabe?";
			link.l1 = "Se as respostas estiverem em algum lugar, é na Ilha da Justiça – não sobrou mais ninguém, pelo menos deste lado do oceano, que tenha conhecido seus pais, mesmo que por pouco tempo. Acho que deveríamos falar com a Orelie Bertine mais uma vez – talvez ela lembre de algo que deixamos passar.";
			link.l1.go = "WildRose_Mary_150";
		break;

		case "WildRose_Mary_150":
			dialog.text = "Mas o que você quer descobrir com ela? Parece que ela já contou tudo o que sabia pra gente.";
			link.l1 = "Ela contou o que a gente perguntou, e podia muito bem ter deixado passar algo importante. Vai ver seu pai tinha uma cicatriz no rosto, ou faltava um dedo na mão... Duvido que alguém que inventou todas aquelas artimanhas—mudando o nome do navio e talvez até o próprio nome—simplesmente morreria sem glória numa ilha qualquer ou numa masmorra castelhana.";
			link.l1.go = "WildRose_Mary_151";
		break;

		case "WildRose_Mary_151":
			dialog.text = "Talvez você esteja certo...";
			link.l1 = "E se a gente decidir continuar procurando – não nas prateleiras empoeiradas do Almirantado, mas aqui, no Arquipélago – vamos precisar de mais do que só um nome, ainda mais se for falso.";
			link.l1.go = "WildRose_Mary_152";
		break;

		case "WildRose_Mary_152":
			dialog.text = "Sabe, tudo isso me dá arrepios, né. Talvez seja porque é tudo tão... emocionante, ou talvez seja a ideia de que meu pai não fosse tão diferente daquele canalha da plantação do Bishop.";
			link.l1 = "De qualquer jeito, eu prometo que vamos fazer de tudo pra descobrir a verdade sobre isso. Então, nada de perder tempo. Vamos!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_9");
		break;
		
		// =================================================================
		// ==================== ЭТАП 4. «ПУТЬ К СВЕТУ» =====================
		// =================================================================
		case "WildRose_Mary_161":
			dialog.text = "Vamos, "+pchar.name+", vamos parar de perder tempo, sabe.";
			link.l1 = "Espero que a Orelie esteja na cabine dela, e que a gente não precise procurar por toda a Ilha da Justiça atrás dela...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_2");
		break;
		
		case "WildRose_Mary_162":
			dialog.text = "Parece que ficamos sem sorte de novo, sabe? Onde será que ela foi parar dessa vez?";
			link.l1 = "Espero que a doença não tenha tomado conta da cabeça dela de novo...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_4");
		break;
		
		case "WildRose_Jillian_31":
			dialog.text = "Ah, você está aqui de novo. Oi... O que foi, precisa da Orelie de novo?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_31_add";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_31_add":
			StartInstantDialog("Mary", "WildRose_Jillian_32", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_32":
			dialog.text = "Não dá pra negar que você é esperta, Jillian. Não sabe onde ela está, sabe?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_32_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_32_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_33", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_33":
			dialog.text = "Na igreja, ela estava prestes a se confessar. Se você correr, ainda a encontra lá.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_33_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_33_add":
			StartInstantDialog("Mary", "WildRose_Jillian_34", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_34":
			dialog.text = "Bom, se ela está confessando, então ela está bem lúcida e lembra de tudo, sabe?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_34_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_35", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_35":
			dialog.text = " Difícil dizer... Nos últimos três dias, ela não tem sido ela mesma, não consegue se acalmar. Sabe, por algum motivo ela ficou muito agitada quando viu os mastros do seu navio além do anel externo.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_35_add":
			StartInstantDialog("Mary", "WildRose_Jillian_36", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_36":
			dialog.text = "O que será que deu nisso, sabe?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_36_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_37":
			dialog.text = "Bem, acho que a ideia de ser questionada por você de novo deixa ela desconfortável. Mas desde quando você se importa com os problemas dos outros?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_37_add":
			StartInstantDialog("Mary", "WildRose_Jillian_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_38":
			dialog.text = "Não ouse falar comigo desse jeito, Jillian. Vou te perdoar dessa vez, mas tenta falar assim de novo pra ver o que acontece...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_5");
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "WildRose_Jillian_41":
			dialog.text = "Uma mulher tão temperamental – sempre fica nervosa quando algo não é do jeito que ela gosta, né?";
			link.l1 = "Melhor não provocar ela sem motivo, "+npchar.name+". Sabe, ela não carrega aquela lâmina só pra se exibir.";
			link.l1.go = "WildRose_Jillian_42";
		break;
		
		case "WildRose_Jillian_42":
			dialog.text = "E você teria deixado isso acontecer, "+pchar.name+"?";
			link.l1 = "Você simplesmente nunca viu a Mary em uma briga, "+npchar.name+". Caso contrário, você não teria ilusões – nada e ninguém pode pará-la. Até logo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_7");
		break;
		
		case "WildRose_Mary_163":
			dialog.text = "Você provavelmente quer me perguntar alguma coisa, "+pchar.name+", sabe...";
			link.l1 = "Pra ser sincera, não me importo muito com o que aconteceu entre vocês dois, sabe? Mas eu aposto que foi por causa de alguém em especial. Você quer mesmo falar sobre isso?";
			link.l1.go = "WildRose_Mary_164_1";
			link.l2 = "Você e a Jillian brigaram por alguma coisa? Ou melhor, por alguém?";
			link.l2.go = "WildRose_Mary_164_2";
		break;

		case "WildRose_Mary_164_1":
			dialog.text = "Hum, na verdade não, sabe?";
			link.l1 = "Tanto faz, sabe? Agora vamos procurar a Orelie.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Mary_164_2":
			dialog.text = "Aquela sanguessuga nunca vai me perdoar por o Alan ter me escolhido em vez dela. Embora ela pudesse, já que ele se foi agora... Pra ser sincera, "+pchar.name+", eu prefiro não falar sobre isso, sabe.";
			link.l1 = "Como você quiser, querido. Então vamos procurar a Orelie.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Mary_165":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_9");
		break;
		
		case "WildRose_Oreli_61":
			dialog.text = ""+pchar.name+", Mary! Você voltou pra Ilha da Justiça, que alegria!";
			link.l1 = "Fico feliz em ver que você está bem, "+npchar.name+". Na verdade, viemos até a Ilha só pra falar com você de novo. Mas fica tranquila, não vai demorar, sabe?";
			link.l1.go = "WildRose_Oreli_62";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Oreli_62":
			dialog.text = "Ô, ô, jovens, vocês realmente não têm piedade de uma velha senhora. Mas eu senti que vocês viriam. Isso é sobre seus pais de novo, não é, Mary?";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_62_add";
		break;

		case "WildRose_Oreli_62_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_63", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_63":
			dialog.text = "Por favor, Orelie. Eu sei que é difícil pra você lembrar depois de tanto tempo, mas tenta só mais uma vez por mim, sabe.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_63_add";
		break;

		case "WildRose_Oreli_63_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_64", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_64":
			dialog.text = "Já te contei tudo o que lembro. Não faço ideia do que mais você quer arrancar de mim.";
			link.l1 = "Temos algumas perguntas pra você, "+npchar.name+". Por favor, tenta lembrar de alguma coisa—qualquer detalhe, qualquer coisa mesmo. A gente não vai te pressionar, sabe...";
			link.l1.go = "WildRose_Oreli_65";
		break;

		case "WildRose_Oreli_65":
			dialog.text = "E não é exatamente isso que você está fazendo agora, sabe?";
			link.l1 = "Você já fez tanto por nós, "+npchar.name+"... Só esperamos que, em algum lugar nos labirintos da sua memória, exista algo mais que possa nos ajudar muito.";
			link.l1.go = "WildRose_Oreli_66_1";
			link.l2 = "Já chegamos tão longe, "+npchar.name+". Você não faz ideia de quanto esforço e tempo isso nos custou. Mas nos perdemos pelo caminho, e só você e sua memória podem nos guiar de volta ao caminho da verdade.";
			link.l2.go = "WildRose_Oreli_66_2";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;

		case "WildRose_Oreli_66_1":
			dialog.text = "Lembranças... O que restou delas, mesmo. Tem manhãs que eu nem lembro meu próprio nome, e você quer detalhes de mim—sobre coisas que aconteceram há vinte anos. Mas sabe, pode perguntar.";
			link.l1 = "Estamos interessados no Sr. Casper, o pai da Mary. Você lembra de algo marcante na aparência dele? Talvez ele tivesse uma cicatriz no rosto, ou mancasse bastante...";
			link.l1.go = "WildRose_Oreli_67";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "WildRose_Oreli_66_2":
			dialog.text = "Lembranças... O que restou delas, de verdade. Tem manhãs que eu nem lembro onde fica a privada, e você quer detalhes de mim—sobre o que aconteceu nesses destroços vinte anos atrás. Mas beleza, pode perguntar, vai.";
			link.l1 = "A gente está interessado no Sr. Casper, o pai da Mary. Você lembra de algo marcante na aparência dele? Talvez ele tivesse uma cicatriz no rosto, ou mancasse bastante...";
			link.l1.go = "WildRose_Oreli_67";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Oreli_67":
			dialog.text = "Ah... Acho que já falei que só vi ele na escuridão total, no porão do 'Ceres Smitty', onde arrumaram uma cama pra pobre Teresa. Ele com certeza não mancava—pelo contrário, era um homem bem ágil.";
			link.l1 = "E a idade dele? Ele era jovem ou já estava ficando mais velho?";
			link.l1.go = "WildRose_Oreli_68";
		break;

		case "WildRose_Oreli_68":
			dialog.text = "Eu não diria que ele era um velho, sabe... Mas eu nem prestei muita atenção nele – eu estava mais preocupada com a Teresa. Ele parecia bem acabado, tipo um fantasma mesmo. Mas olha, ele mal dormiu a semana inteira enquanto a esposa dele estava pra dar à luz... Ele corria pra lá e pra cá na Ilha, sem parar um minuto.";
			link.l1 = "Então, ele devia amar muito a esposa dele. E você passou bastante tempo com ela, né? Ela chegou a falar do marido?";
			link.l1.go = "WildRose_Oreli_69";
		break;

		case "WildRose_Oreli_69":
			dialog.text = "Teresa não parava de perguntar por ele. Dormia muito, às vezes delirava, mas sempre que voltava a si, a primeira coisa que fazia era perguntar onde ele estava. E a coitada esperou tanto, tanto por ele. Mas, na hora mais importante – ele nunca apareceu.";
			link.l1 = "Entendi. Pelo visto, o amor deles era mesmo recíproco... Bom, obrigada, Orelie. Você nos ajudou muito.";
			link.l1.go = "WildRose_Oreli_70";
		break;

		case "WildRose_Oreli_70":
			dialog.text = "E só isso? Achei que nossa conversa fosse durar pelo menos uma ou duas horas.";
			link.l1 = "Nós prometemos não te incomodar por muito tempo. Se cuida, "+npchar.name+". Tudo de bom.";
			link.l1.go = "WildRose_Oreli_71";
		break;

		case "WildRose_Oreli_71":
			dialog.text = "Esperem, jovens! Tenho mais uma coisa para vocês... Ou melhor, para você, Mary.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_a";
			NPCsLookEachOther("LSC_Oreli", "Mary");
		break;
		
		case "WildRose_Oreli_72_a": //
			dialog.text = "Aqui está, minha menina, pega... Assim que vi as velas do seu navio, peguei este chapéu comigo pra não esquecer. Mas descer até o cais... Eu simplesmente não consegui, sabe?";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_add";
		break;

		case "WildRose_Oreli_72_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_73", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_73":
			dialog.text = "O que foi, Orelie? Um chapéu?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_73_add";
		break;

		case "WildRose_Oreli_73_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_74", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_74":
			dialog.text = "O chapéu da sua mãe, o da Teresa. Ela estava com ele quando os sobreviventes do naufrágio foram trazidos pra ‘Ferraria Ceres’. Quando a Teresa morreu, eu peguei aquele chapéu do chão, do lado da cama dela—sabe, e depois simplesmente esqueci dele... Só lembrei hoje, enquanto a gente conversava.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_74_add";
		break;

		case "WildRose_Oreli_74_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_75", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_75":
			dialog.text = "Orelie... Você guardou isso todos esses anos! E... e não jogou fora, não vendeu... Obrigada, obrigada! Você não faz ideia do quanto isso significa pra mim, sabe!";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_75_add";
		break;

		case "WildRose_Oreli_75_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_76", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_76":
			dialog.text = "Desculpa, Mary — eu devia ter te dado isso há muito tempo... Mas minha memória anda pior que uma peneira velha esses dias — por isso...";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_76_add";
		break;

		case "WildRose_Oreli_76_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_77", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_77":
			dialog.text = "Não tem momento melhor, Orelie! Vou experimentar agora mesmo, sabe!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_hat_1");
		break;
		
		case "WildRose_Mary_166":
			dialog.text = "Então, querido, o que acha de mim?..";
			link.l1 = "Você é linda. E o chapéu... ainda não saiu de moda, então também fica maravilhoso.";
			link.l1.go = "WildRose_Mary_167";
		break;
		
		case "WildRose_Mary_167":
			dialog.text = "Sério? Fico tão feliz que você gostou!";
			link.l1 = "Poderia ser de outro jeito?";
			link.l1.go = "WildRose_Mary_167_add";
		break;
		
		case "WildRose_Mary_167_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Mary_168", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;
		
		case "WildRose_Mary_168":
			dialog.text = "...";
			link.l1 = "Obrigada mais uma vez, Orelie – você deixou meu dia um pouco mais alegre! Tudo de bom, descanse bem.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_10");
		break;
		
		case "WildRose_Mary_171":
			dialog.text = "Então era mesmo o Rupert. Rupert Northwood, sabe?";
			link.l1 = "Obviamente, sim, querido. Ele fez de tudo pra salvar a esposa... ou a amada, sei lá. No fim das contas, isso nem importa tanto, sabe? O importante é que agora a gente sabe quem estamos procurando.";
			link.l1.go = "WildRose_Mary_172";
		break;

		case "WildRose_Mary_172":
			dialog.text = "Mas o que aconteceu com o verdadeiro Joshua Casper, capitão do 'Cornwall'?";
			link.l1 = "Boa pergunta, mas não é a principal agora. Por que o Rupert não voltou pra te buscar se amava tanto a Teresa – isso sim é bem mais interessante. E é a primeira coisa que vamos perguntar pra ele. Se ele ainda estiver vivo, e se a gente encontrar ele. Uma coisa é certa – ele nunca voltou pra frota. Não tinha motivo pra se arriscar assim.";
			link.l1.go = "WildRose_Mary_174";
		break;

		case "WildRose_Mary_174":
			dialog.text = "O que poderia ter feito ele assumir o nome Joshua Casper? O que aconteceu a bordo do 'Cornwall', que virou o 'Wrangler'? Será que meu pai pode mesmo ser um criminoso, "+pchar.name+"?";
			link.l1 = "Receio que também não possamos descartar essa possibilidade, "+npchar.name+". A gente tem que estar pronta pra qualquer coisa, sabe?";
			link.l1.go = "WildRose_Mary_175";
		break;

		case "WildRose_Mary_175":
			dialog.text = "Eu nem quero pensar nisso...";
			link.l1 = "Por enquanto, precisamos pensar em outra coisa – onde procurar por ele. Ele pode ter se juntado aos piratas ou contrabandistas. Ou talvez tenha se estabelecido em alguma cidade e esteja mantendo o perfil baixo. Tudo é possível.";
			link.l1.go = "WildRose_Mary_176";
		break;
		
		case "WildRose_Mary_176":
			dialog.text = "E o que você sugere que a gente faça? Como é que vamos encontrar ele? Entrar em cada colônia, falar o nome dele e torcer pra alguém já ter ouvido falar de Rupert Northwood?";
			link.l1 = "Ou Joshua Casper. Ele poderia muito bem ter continuado vivendo sob a identidade do antigo capitão dele — provavelmente já morto. Mas isso trazia certos riscos, já que alguém podia começar a procurar pelo brigue desaparecido. Ainda mais porque havia um baú de prata a bordo, destinado à guarnição de Providence.";
			link.l1.go = "WildRose_Mary_177";
		break;

		case "WildRose_Mary_177":
			dialog.text = "Você tem razão, sabe.";
			link.l1 = "E mesmo assim, Rupert Northwood, supostamente desaparecido perto dos Açores, dificilmente chamaria a atenção de alguém. Ainda assim, tem algo aqui que vale a pena pensar, sabe?";
			link.l1.go = "WildRose_Mary_178";
		break;

		case "WildRose_Mary_178":
			dialog.text = "Quanto mais tempo a gente vai ter que gastar com isso, "+pchar.name+"?! Ele pode estar em qualquer lugar, em qualquer colônia, sabe!";
			link.l1 = "Se ele sobreviveu, claro. Mas eu discordo. É improvável que ele falasse espanhol fluentemente, então isso descarta Cuba e Hispaniola. Se ele soubesse um pouco de francês, talvez tivesse ido para Tortuga ou alguma das Pequenas Antilhas. Ou pode ter acabado no Litoral Oeste, sob a proteção de outros ingleses. Podemos passar meses procurando por ele e ainda assim não encontrar nada.";
			link.l1.go = "WildRose_Mary_179";
		break;

		case "WildRose_Mary_179":
			dialog.text = "Mas eu não quero desistir, "+pchar.name+". Só não agora, quando a gente já descobriu tanta coisa, sabe!";
			link.l1 = "Não estou sugerindo que a gente desista, "+npchar.name+". Mas a gente não precisa procurar por ele sozinhos – podemos pedir ajuda pra quem tem os contatos certos. Já funcionou uma vez. Por que não tentar de novo?";
			link.l1.go = "WildRose_Mary_180";
		break;

		case "WildRose_Mary_180":
			dialog.text = "Você está sugerindo que a gente peça ajuda ao abade de novo? Achei que ele deixou bem claro que não deveríamos contar com mais nenhum apoio dele nessa história, sabe.";
			link.l1 = "Isso seria um pouco ousado demais com o velho, sabe? Você tem razão.";
			link.l1.go = "WildRose_Mary_181";
		break;

		case "WildRose_Mary_181":
			dialog.text = "Mas então, pra quem a gente deve recorrer? Quem teria dinheiro e contatos pra uma coisa dessas?";
			link.l1 = "Bom, vamos ter que bancar essa busca por conta própria, sabe? Quanto às conexões... Acho que o Fadey Moskovit pode dar uma força pra gente. Ele deve conhecer umas pessoas competentes que a gente pode mandar pelas colônias. Ou talvez ele indique alguém que possa ajudar.";
			link.l1.go = "WildRose_Mary_182";
		break;

		case "WildRose_Mary_182":
			dialog.text = "Então, a gente vai pra Basse-Terre?";
			link.l1 = "Sabe, vamos fazer uma visita ao nosso amigo. Isso não parece ser uma tarefa muito difícil pra ele, se quer saber.";
			link.l1.go = "WildRose_Mary_183";
		break;

		case "WildRose_Mary_183":
			dialog.text = "Vamos levantar âncora amanhã, o que acha? Eu queria passar o resto do dia e a noite com você, só nós dois, no 'Ceres Smitty'.";
			link.l1 = "Ninguém recusa uma proposta dessas, querido. Nós com certeza merecemos um descanso, sabe?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_12");
		break;
		
		case "WildRose_Jillian_51":
			dialog.text = "Como assim, já vai embora da Ilha? Nem vai ficar pro funeral, sabe?";
			link.l1 = "Funeral?..";
			link.l1.go = "WildRose_Jillian_52";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_52":
			dialog.text = "Ah, então você não ficou sabendo. Entendi... Orelie Bertine faleceu ontem à noite.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_52_add";
		break;

		case "WildRose_Jillian_52_add":
			StartInstantDialog("Mary", "WildRose_Jillian_53", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_53":
			dialog.text = "O quê?! Não pode ser – a gente falou com ela ontem, e ela estava perfeitamente bem. Ou será que alguém...";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_53_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_53_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_54", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_54":
			dialog.text = "Não, Mary. Orelie morreu enquanto dormia. Fui visitá-la hoje, levar uns ungüentos para as juntas dela, que o Irmão Julian preparou – e foi aí que a encontrei. Ela estava deitada na cama, com um sorriso estranho no rosto. Mas já estava pálida e fria.  Essa última semana, a velha não era mais a mesma, até pensei que a doença que o feiticeiro negro tinha expulsado tinha voltado. Mas a cabeça dela estava boa, e parecia que não estava delirando.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_54_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_54_add":
			StartInstantDialog("Mary", "WildRose_Jillian_55", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_55":
			dialog.text = "Pelo menos ela não sofreu, sabe.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_55_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_55_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_56", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_56":
			dialog.text = "Então, você vai ficar para o funeral? Vai ser amanhã, no recife mais distante – lá é fundo o bastante, e os caranguejos não chegam tão longe.";
			link.l1 = "Vamos ficar, Jillian. Orelie fez tanto pela Mary, não podemos agir de outra forma. Se ninguém se opuser, faremos a procissão no nosso navio. Vamos enterrá-la no mar, com todas as honras que merece.";
			link.l1.go = "WildRose_Jillian_57";
		break;
		
		case "WildRose_Jillian_57":
			dialog.text = "Ninguém vai reclamar. É mais prático e, no fim das contas, mais seguro do que escalar os destroços.";
			link.l1 = "Então cuide dos preparativos do funeral – a Mary vai te ajudar. Quanto a mim, preciso conversar com alguém...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_14");
		break;
		
		case "WildRose_Chimiset_61":
			dialog.text = "E olha só quem apareceu de novo, meu querido amigo! O que posso fazer por você desta vez?";
			link.l1 = "Oi, "+npchar.name+". Você ficou sabendo o que aconteceu ontem à noite?";
			link.l1.go = "WildRose_Chimiset_62";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_62":
			dialog.text = "Você está falando da morte da Orelie? Dá pra ver que sim. Claro que eu fiquei sabendo. Ela morava no ‘Pluto’, que é praticamente território do Rivados. E o pessoal dos outros navios não fala de outra coisa, sabe?";
			link.l1 = "Vimos ela ontem mesmo, e ela estava bem de saúde—tirando, claro, que passou a semana toda preocupada com alguma coisa. E quando avistou nosso navio, ficou ainda mais nervosa.";
			link.l1.go = "WildRose_Chimiset_63";
		break;

		case "WildRose_Chimiset_63":
			dialog.text = "Uma pessoa consegue sentir quando o rio da sua vida está secando. Alguns mostram isso para todo mundo ao redor, outros guardam bem lá dentro, mas todo mundo percebe, de um jeito ou de outro—principalmente quem sabe ouvir o próprio coração.";
			link.l1 = "Parecia pra mim que ela estava saudável, quase como uma jovem corça, "+npchar.name+". E tem algo aqui que simplesmente não faz sentido...";
			link.l1.go = "WildRose_Chimiset_64_1";
			link.l2 = "E ainda assim, dava pra ver que ela estava longe do fim, "+npchar.name+".";
			link.l2.go = "WildRose_Chimiset_64_2";
		break;

		case "WildRose_Chimiset_64_1":
			dialog.text = "Meu amigo, a mente e o corpo são coisas de ordens completamente diferentes. A mente governa o corpo, e às vezes o corpo tenta assumir o controle da mente. Eles estão intimamente ligados, mas não são realmente uma coisa só. Uma pessoa pode parecer perfeitamente saudável por fora, mas sua alma já pode estar trilhando o caminho da morte.";
			link.l1 = "Você é esperto, meu amigo, muito esperto. Se sentir que a verdade está perto, vai atrás dela como um leão atrás de uma zebra – e não vai parar até conseguir. Percebi isso na hora, no exato momento em que te conheci.";
			link.l1.go = "WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Chimiset_64_2":
			dialog.text = "Meu amigo, mente e corpo são coisas de ordens completamente diferentes. A mente comanda o corpo, e às vezes o corpo tenta tomar conta da mente. Eles estão profundamente ligados, mas não são exatamente a mesma coisa. Uma pessoa pode parecer perfeitamente saudável por fora, mas sua alma já pode estar trilhando o caminho da morte.";
			link.l1 = "Sabe, me ocorreu que a Orelie parecia estar esperando por nós, como se soubesse que a gente ia procurá-la. A velha podia ter morrido um dia antes ou depois, mas aconteceu quase logo depois que ela contou algo importante sobre o pai da Mary."link.l1.go ="WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Chimiset_65":
			dialog.text = "Você é esperto, meu amigo, muito esperto. Se sentir que a verdade está perto, vai atrás dela como um leão atrás de uma zebra – e não vai parar até conseguir. Percebi isso no exato momento em que te vi pela primeira vez.";
			link.l1 = "Eu não... Espera um pouco. Aquele ritual que você fez no porão do 'Protetor'... não serviu pra desacelerar a doença da Orelie, né? Então o que você fez de verdade?";
			link.l1.go = "WildRose_Chimiset_66";
		break;

		case "WildRose_Chimiset_66":
			dialog.text = "Você pode encher um rio de pedras, mas isso não vai parar o seu fluxo. Eu sabia que você precisava de algo importante da Orelie – e que não conseguiria logo de cara. Mas quanto tempo sua jornada levaria, eu não podia prever. Então eu construí uma represa, usando toda a força vital dela para conter a doença até que ela cumprisse seu propósito. E no instante em que isso aconteceu, a barreira desabou...";
			link.l1 = " Então, Orelie... no momento da morte dela, ela não era ela mesma, não estava alheia, como a gente pensava? ";
			link.l1.go = "WildRose_Chimiset_67";
		break;

		case "WildRose_Chimiset_67":
			dialog.text = "Ela usou todas as forças só pra manter a cabeça no lugar e a memória viva, e quando não precisou mais disso, a doença veio como uma onda gigante e levou ela pro vale da morte. Se ela partiu em paz, ou se foi pro seu Deus atormentada pelos fantasmas do passado e pesadelos terríveis—não posso dizer, porque eu não sei.";
			link.l1 = "Você sabia exatamente onde isso ia dar, sabe? Por que diabos você não me avisou das consequências?! Então, fala!";
			link.l1.go = "WildRose_Chimiset_68_1";
			link.l2 = "Você sabia exatamente o que estava fazendo, "+npchar.name+". Por que você não me avisou aonde isso podia levar?";
			link.l2.go = "WildRose_Chimiset_68_2";
		break;

		case "WildRose_Chimiset_68_1":
			dialog.text = "Porque eu decidi te ajudar, meu amigo, te ensinar o que você precisava e deixar ela cumprir o destino dela. Se eu tivesse contado o que esperava por ela, talvez você não tivesse seguido adiante — e Orelie teria levado seus segredos para o túmulo. Que bem isso teria feito? Ela teria morrido à toa. Como uma gazela abatida por um leão, mas deixada de lado, largada para os abutres.";
			link.l1 = "Propósito, utilidade... Você é mesmo um mestre dos destinos, "+npchar.name+". Deus em forma humana.";
			link.l1.go = "WildRose_Chimiset_69";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_68_2":
			dialog.text = "Porque eu decidi te ajudar, meu amigo, pra você descobrir o que precisava, e pra deixar ela cumprir o destino dela. Se eu tivesse contado o que esperava por ela, talvez você nem tivesse continuado—e Orelie teria levado seus segredos pro túmulo. Que bem isso teria feito? Ela teria morrido à toa. Como uma gazela abatida por um leão, mas deixada lá, sem ser comida, só pra ser devorada pelos abutres depois.";
			link.l1 = "Propósito, utilidade... Você é mesmo um mestre dos destinos, "+npchar.name+". Deus em forma humana.";
			link.l1.go = "WildRose_Chimiset_69";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Chimiset_69":
			dialog.text = "Eu percebo um tom de insatisfação na sua voz, meu amigo. Mas não, eu não me considero um deus de jeito nenhum—e acredite, nem ele é todo-poderoso. Nem aquele em quem você acredita, nem aqueles que nós adoramos. Deuses não podem dar a uma pessoa mais força do que aquela com que ela nasceu. Nós, xamãs, só podemos direcionar essa força para um lado ou para outro—nada além disso.";
			link.l1 = "E você colocou eles num caminho que condenou ela à morte...";
			link.l1.go = "WildRose_Chimiset_70";
		break;

		case "WildRose_Chimiset_70":
			dialog.text = "Eu só mostrei o caminho para Orelie, e ao segui-lo, ela ajudou Mary — alguém com quem ela tinha uma ligação forte desde o dia em que Mary nasceu. Afinal, sua companheira chegou a este mundo bem diante dos olhos dela. Por favor, não me olhe como se eu tivesse enlouquecido. Você não vai dizer que me vê como um feiticeiro bondoso, capaz de fazer o rio do tempo voltar com um aceno de mão, né?";
			link.l1 = "Eu não sei o que te dizer, "+npchar.name+". Talvez realmente não tenha sido tudo em vão. Mas não era pra ter acontecido desse jeito. Você devia ter me contado, e eu é que devia ter escolhido. Mas, o que está feito, está feito. Então, adeus, meu amigo.";
			link.l1.go = "WildRose_Chimiset_71";
		break;

		case "WildRose_Chimiset_71":
			dialog.text = "Ah, não era assim que eu imaginava nosso último encontro, meu amigo...";
			link.l1 = "O que te faz pensar que ela é a última, sabe?";
			link.l1.go = "WildRose_Chimiset_72";
		break;

		case "WildRose_Chimiset_72":
			dialog.text = "Alguns rios deságuam em outros, tornando-se parte deles, outros secam, e alguns—como o nosso—terminam em uma grande cachoeira...";
			link.l1 = "Mais enigmas, Chimiset? Acho que já chega por hoje. Tenho certeza de que a gente vai se encontrar de novo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_15");
		break;
		
		case "WildRose_Mary_191":
			dialog.text = "Imaginei que ia te encontrar aqui, sabe? O que você queria do Chimiset, "+pchar.name+"? O que ele te disse?";
			link.l1 = "Não era exatamente o que eu esperava—ou queria—ouvir. Mas era algo que eu já suspeitava, mesmo que vagamente.";
			link.l1.go = "WildRose_Mary_192";
		break;

		case "WildRose_Mary_192":
			dialog.text = "Você vai me contar, né?";
			link.l1 = "Não, "+npchar.name+". Dessa vez não. Tudo o que é dito na cabine do Protetor fica lá, só entre eu e Chimiset.";
			link.l1.go = "WildRose_Mary_193";
		break;

		case "WildRose_Mary_193":
			dialog.text = "Faz tempo que não ouço tanta determinação na sua voz, "+pchar.name+". Mas sabe, temos outras coisas com que nos preocupar. O funeral vai ser amanhã, ao pôr do sol, às sete horas.";
			link.l1 = "Vem, deixa eu te ajudar a preparar tudo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_17");
		break;
		
		case "WildRose_Mary_201":
			dialog.text = "Parece que todo mundo que queria vir já chegou, sabe.";
			link.l1 = "Eu achei que teria mais gente. Pelo menos algumas pessoas tranquilas.";
			link.l1.go = "WildRose_Mary_202";
			CharacterTurnToLoc(npchar, "quest", "quest1");
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;

		case "WildRose_Mary_202":
			dialog.text = "Bem, ninguém convidou o Kurana nem o Rivados. O Abbott, aquele pavão nojento e arrogante, disse que tinha coisas mais importantes pra fazer do que enterrar uma mulher católica, e o Lauderdale e o Musket resmungaram algo parecido. O Cassel, aquele brutamontes, só disse que não vinha. Mas todo o resto está aqui.";
			link.l1 = "Tem coisas que eu nunca vou entender, sabe? Bom, que Deus julgue tudo isso. E lá vem o Irmão Julian... Agora é que tudo começa.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_2");
		break;
		
		case "WildRose_funeral_1":
			dialog.text = "Embora nossos corações estejam pesados de tristeza, vamos agradecer a Deus por todas as bênçãos que Ele concedeu à falecida Orelie, e proclamar: Agradecemos a Ti, Deus, nosso Pai\n"+"Por todos os anos e dias que Orelie passou  com a gente\n"+"Pelo grande dom do santo batismo, pelo qual Orelie se tornou Sua filha\n"+"Por todos os dons e conhecimentos que Você concedeu a ela\n"+"Por seu serviço pelo bem da sua família e dos outros\n"+"Por sua paciência com nossos erros\n"+"Vamos rezar a Deus, para que Ele receba nossa irmã Orelie em Sua glória, e vamos clamar: Nós Te pedimos, Senhor\n"+"Que as boas ações de Orelie deem frutos em abundância\n"+"Que o que ela começou continue sendo levado adiante\n"+"Perdoe os pecados que ela cometeu\n"+"Que a memória dela viva para sempre em nossos corações\n"+"Vamos rezar a Deus para fortalecer a fé e a esperança daqueles que sofrem, e vamos clamar a Ele: Senhor, aumenta a nossa fé\n"+"Por meio do Teu Filho, que se fez homem\n"+"Por meio do Teu Filho, Jesus Cristo, que nos amou além de qualquer medida\n"+"Por meio do Teu Filho, que aceitou a morte pelos nossos pecados e ressuscitou para a nossa salvação\n"+"Por meio do Teu Filho, que abriu o caminho para o céu para nós\n"+"Junto com todos os fiéis que já partiram para a morada celestial, vamos rezar como o Salvador nos ensinou.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_7");
			
			WildRose_Etap4_PathToLight_18_funeral_6_1();
		break;
		
		case "WildRose_funeral_2":
			dialog.text = "Deus Todo-Poderoso, ouve nossas preces, feitas com fé em Teu Filho Ressuscitado, e fortalece nossa esperança de que, junto com Teu servo falecido, também possamos alcançar a ressurreição. Por nosso Senhor Jesus Cristo, Teu Filho, que vive e reina Contigo na unidade do Espírito Santo, Deus para sempre. Amém.";
			link.l1 = "God, Almighty Father, the mystery of the cross is our strength, and the Resurrection of Your Son is the foundation of our hope; free Your departed handmaid from the bonds of death and join her to the company of the saved. Through Christ our Lord. Amen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_8");
			WildRose_Etap4_PathToLight_18_funeral_7_1();
		break;
		
		case "WildRose_funeral_3":
			dialog.text = ""+pchar.name+", vamos pra cabine rápido, sabe? Tô quase chorando... Não quero que ninguém me veja assim.";
			link.l1 = "Claro, "+npchar.name+". Vamos.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_13");
		break;
		
		case "WildRose_Mary_211":
			dialog.text = "A gente só começa a valorizar alguém de verdade depois que essa pessoa vai embora – já ouviu isso, "+pchar.name+"?";
			link.l1 = "Sim, mais de uma vez. .";
			link.l1.go = "WildRose_Mary_212";
		break;

		case "WildRose_Mary_212":
			dialog.text = "O Eric falava muito isso, sabe? Acho que ele se referia à família dele. Nunca perguntei sobre eles—sempre achei que teria tempo pra isso. E aí ele morreu, né. Agora a Orelie também se foi—e só agora percebo como dei tão pouco tempo e atenção pra ela. Muito menos do que ela merecia.";
			link.l1 = "Você não tem culpa de nada. Nunca sabemos quando o Senhor vai chamar quem a gente ama pra perto d’Ele. E nunca é tempo suficiente ao lado deles. Nunca.";
			link.l1.go = "WildRose_Mary_213";
		break;

		case "WildRose_Mary_213":
			dialog.text = "Talvez seja, sabe? E o Eric sempre dizia – e a Orelie concordava com ele – que qualquer lugar é, antes de tudo, o seu povo. Não as casas, nem as árvores, nem as estradas – mas as pessoas. Quando você pensa em algum ponto no mapa, a primeira coisa que vem à cabeça são as pessoas que moram lá. Ou que já moraram.";
			link.l1 = "Eu nunca parei pra pensar nisso. Mas talvez o Eric estivesse certo—afinal, de que vale um lar se, ao entrar, você nunca mais vai ver seu pai ou seu irmão, sabe?";
			link.l1.go = "WildRose_Mary_214_1";
			link.l2 = " Eu discordo, sabe? Quando penso, sei lá, em Paris, o que me vem à cabeça são as ruas, os cheiros... Só algumas pessoas ficaram na minha memória – o resto quase sumiu, mesmo tendo passado só alguns anos. ";
			link.l2.go = "WildRose_Mary_214_2";
		break;

		case "WildRose_Mary_214_1":
			dialog.text = "Acho que o Eric e a Orelie falaram sobre a Ilha, sabe? E sobre as pessoas que moravam aqui—há muito, muito tempo. Eu era só uma criança e não entendia nada disso, mas agora—consigo ver tudo claramente. Afinal, o Antonio, a Cecille... e alguns Rivados como o Chimiset estão aqui há mais tempo do que eu—mas nunca fui próxima de nenhum deles. Quanto ao resto: Eric, Orelie, Alan e tantos outros—todos já morreram.";
			link.l1 = "Entendi. O mundo ficou... só um pouco menor, não ficou?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "WildRose_Mary_214_2":
			dialog.text = "Acho que o Eric e a Orelie falaram sobre a Ilha, sabe? E sobre as pessoas que moravam aqui—há muito, muito tempo. Eu era só uma criança e não entendia nada disso, mas agora vejo tudo tão claramente. Afinal, Antonio, Cecille... e alguns dos Rivados, como o Chimiset, estão aqui há mais tempo do que eu—mas nunca fui próxima de nenhum deles. Quanto ao resto: Eric, Orelie, Alan e tantos outros—todos já se foram.";
			link.l1 = "Entendi. O mundo ficou... só um pouquinho menor, sabe?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Mary_215":
			dialog.text = "É mais como se tivesse esvaziado. Este mundo—aqui dentro do anel externo. Agora está vazio, sabe? E logo—pode simplesmente desaparecer de vez.";
			link.l1 = "Do que você está falando, Mary?.";
			link.l1.go = "WildRose_Mary_216";
		break;

		case "WildRose_Mary_216":
			dialog.text = "Você não sentiu, "+pchar.name+"? Agora há pouco, quando a gente estava parada perto do túmulo da Orelie.";
			link.l1 = "O quê exatamente?";
			link.l1.go = "WildRose_Mary_217";
		break;

		case "WildRose_Mary_217":
			dialog.text = "Eu não sei como explicar. Sabe aquele cheiro no ar antes de uma tempestade? Lembra—quando você chegou aqui pela primeira vez, tinha uma tensão no ar... Todo mundo parecia pronto pra se atacar, muita gente dizia que sentia cheiro de pólvora e sangue. Depois que você matou o Chad, tudo mudou—parecia até mais fácil respirar... Mas agora—essa sensação voltou de novo.";
			link.l1 = "Acho que eu também senti algo assim, sabe? Mas talvez seja só o clima? Digo, afinal de contas, é um funeral...";
			link.l1.go = "WildRose_Mary_218_1";
			link.l2 = "Você está exausta, "+npchar.name+"   Vai descansar um pouco – tudo vai parecer mais fácil. E, sinceramente, alguém consegue se sentir diferente num funeral?";
			link.l2.go = "WildRose_Mary_218_2";
		break;

		case "WildRose_Mary_218_1":
			dialog.text = "Quando entregamos o Eric e tantos outros da Ilha da Justiça ao mar, não foi assim, sabe? Havia uma espécie de... união. Mas hoje—alguns se olhavam como lobos, mesmo todo mundo dizendo a mesma oração.";
			link.l1 = "Você quer dizer o Leighton e o Donald?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;

		case "WildRose_Mary_218_2":
			dialog.text = "Quando entregamos o Eric e tantos outros da Ilha da Justiça ao mar, não foi assim, sabe? Havia uma espécie de... união. Mas hoje—alguns deles se olhavam como lobos, mesmo todos recitando a mesma oração.";
			link.l1 = "Você quer dizer o Leighton e o Donald?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Mary_219":
			dialog.text = "Então, você também percebeu, sabe.";
			link.l1 = "O Dexter fica nervoso sempre que o Greenspen tenta se meter nos exercícios – e quem pode culpá-lo, né?";
			link.l1.go = "WildRose_Mary_220";
		break;

		case "WildRose_Mary_220":
			dialog.text = "Isso não vai acabar bem, sabe.";
			link.l1 = "Se for assim, então hoje não foi só o funeral de Orelie Bertine, mas também desta... Cidade dos Navios Abandonados.";
			link.l1.go = "WildRose_Mary_221";
		break;

		case "WildRose_Mary_221":
			dialog.text = "Cidades dos Navios Abandonados?";
			link.l1 = "Me perdoa, Mary, mas eu simplesmente não consigo chamar esse lugar de Ilha da Justiça.";
			link.l1.go = "WildRose_Mary_222";
		break;

		case "WildRose_Mary_222":
			dialog.text = "Agora que eu vi o mundo e percebi o quanto ele é imenso, esse lugar parece... uma prisão, sabe? Difícil acreditar que cresci aqui.";
			link.l1 = "E eu mal posso acreditar que, entre todos esses navios naufragados, uma rosa tão selvagem e linda como você conseguiu florescer.";
			link.l1.go = "WildRose_Mary_223";
		break;

		case "WildRose_Mary_223":
			dialog.text = "Quero me despedir deste lugar, "+pchar.name+"... Acho que a gente nunca mais vai voltar aqui, sabe. Eu não quero. Não quero ver com meus próprios olhos o que pode acontecer aqui.";
			link.l1 = "Vou falar com o Eddie e o Donald. Talvez eu consiga acalmar eles um pouco, sabe?";
			link.l1.go = "WildRose_Mary_224";
		break;

		case "WildRose_Mary_224":
			dialog.text = "Você não entende... Isso só vai adiar o inevitável, então não vale o seu esforço. O dia vai chegar em que vamos voltar – e aqui\nÉ o melhor, "+pchar.name+", sabe... Não tem mais nada me prendendo aqui.";
			link.l1 = "Como você diz, querido. Vamos terminar o que precisamos fazer – e depois vamos deixar este lugar para sempre.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_20");
		break;
		
		// =================================================================
		// ==================== ЭТАП 5. «ЧУЖИМИ РУКАМИ» ====================
		// =================================================================
		case "WildRose_Mary_231":
			dialog.text = "Rupert Casper? Joshua Northwood?";
			link.l1 = "Eu estive pensando nisso o caminho todo, "+npchar.name+". E eu cheguei à conclusão de que seu pai não teria se escondido usando um nome e sobrenome que já tinha usado antes. Ao mesmo tempo, talvez ele não tivesse coragem de abrir mão do nome ou sobrenome verdadeiro: e se, na hora errada, ele não respondesse ao nome falso?";
			link.l1.go = "WildRose_Mary_232";
		break;

		case "WildRose_Mary_232":
			dialog.text = "Ele podia ter se chamado de qualquer coisa, sabe.";
			link.l1 = "Ele podia, claro. E talvez tenha feito exatamente isso. Se sobreviveu em Cuba, onde chegou numa tartana de contrabandista. Se conseguiu chegar lá, e não virou comida para os caranguejos da Ilha da Justiça. Agora tudo que podemos fazer é esperar – pelo menos não tanto quanto da última vez. Acho que conseguimos aguentar um mês numa boa.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Mary_235":
			dialog.text = "Meu pai está vivo, "+pchar.name+". Eu sempre soube disso, sabe!";
			link.l1 = "Assim como eu, querido. Bem, está na hora de ir ver esse Jerome – e quanto antes, melhor.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_7");
		break;
		
		// =================================================================
		// ================= ЭТАП 6. «ЖИЗНЬ ПОСЛЕ СМЕРТИ» ==================
		// =================================================================
		case "WildRose_Mary_241":
			dialog.text = "Finalmente cheguei, sabe. E agora, "+pchar.name+"?";
			link.l1 = "Precisamos encontrar o Jerome. Ele deve estar descansando em algum quarto da taverna ou alugando uma casa – tenho certeza de que ele tem dinheiro suficiente pra isso.";
			link.l1.go = "WildRose_Mary_242";
		break;

		case "WildRose_Mary_242":
			dialog.text = "Considerando quanto o Fadey pagou pra ele... Acho que ele escolheu mesmo a segunda opção.";
			link.l1 = "Combinado. A gente pode perguntar sobre ele pro dono do 'Olho de Vidro', ou só conversar com o pessoal da cidade, sabe? Vamos, o tempo é precioso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_2");
		break;
		
		case "WildRose_BanditBeliz_1":
			dialog.text = "Olha só, olha só... Aqui estão os nossos pombinhos. Sabe, rapazes, vamos acabar logo com isso e avisar ele.";
			link.l1 = "Jerome Souvernier? Que diabos está acontecendo aqui?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_5");
		break;
		
		case "WildRose_BanditBeliz_2":
			if (!CharacterIsAlive("WildRose_Bandit_1") && !CharacterIsAlive("WildRose_Bandit_2"))
			{
				dialog.text = "Ah, seus desgraçados, cof-cof. Mas tudo bem, sabe...";
				link.l1 = "Eu tomaria cuidado com o que fala se valoriza a própria pele... ";
				link.l1.go = "WildRose_BanditBeliz_2_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "WildRose_BanditBeliz_2_1":
			dialog.text = "...";
			link.l1 = "Isso também. Agora fala logo: que diabos te fez atacar a gente – e ainda por cima junto com o Souvernier...";
			link.l1.go = "WildRose_BanditBeliz_3";
		break;

		case "WildRose_BanditBeliz_3":
			dialog.text = "Seu Souvernier é um canalha ganancioso e covarde. Bastou o Casper dar uma boa surra nele e prometer umas moedas – na mesma hora, ele rabiscou aquela carta feito um bom menino, sabe...";
			link.l1 = "Então ele realmente encontrou mesmo, né?";
			link.l1.go = "WildRose_BanditBeliz_4";
		break;

		case "WildRose_BanditBeliz_4":
			dialog.text = "Te achei, te achei. Então, logo você vai morrer. O mesmo vale pra sua namoradinha. Casper vai picar vocês dois todinhos, heh-heh. Eu já tô praticamente morto mesmo, mas vou ajudar você a encontrar seu fim. Pena que não vou ouvir você implorar por misericórdia quando ele botar as mãos em você...";
			link.l1 = "Sabe, não me resta muito tempo neste mundo, é verdade. Então fala logo, antes que eu dê meu último suspiro.";
			link.l1.go = "WildRose_BanditBeliz_6";
		break;

		case "WildRose_BanditBeliz_6":
			dialog.text = "Se quiser encontrá-lo, vá até a Baía de Chetumal, é lá que ele mora. Não vai precisar procurar por ele, ele mesmo vai te achar.";
			link.l1 = " Maravilha. Fique à vontade para morrer no seu tempo. Terminamos aqui.";
			link.l1.go = "WildRose_BanditBeliz_Just_Deth";
			link.l2 = "Espero que sim. Agora vai pro inferno.";
			link.l2.go = "WildRose_BanditBeliz_Hit_Deth";
		break;
		
		case "WildRose_BanditBeliz_Just_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_8");
		break;
		
		case "WildRose_BanditBeliz_Hit_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_7");
		break;
		
		case "WildRose_Mary_251":
			dialog.text = "Ai meu Deus, "+pchar.name+"... Eu não acredito, simplesmente não dá pra acreditar, sabe! Meu pai fez isso?!";
			link.l1 = "Parece que sim, sabe. "+npchar.name+". Eu não faço ideia do que levou ele a isso ou quem diabos ele é, sabe... Mas duvido que seja outro Rupert Casper. Coincidências assim simplesmente não acontecem.";
			link.l1.go = "WildRose_Mary_252";
		break;

		case "WildRose_Mary_252":
			dialog.text = "E o que a gente faz agora? O que eu digo quando olhar nos olhos dele?";
			link.l1 = "Primeiro, a gente precisa encontrar ele. Provavelmente, ele virou um fora da lei, já que só de procurar por ele causou... uma reação tão nervosa. Mas, seja como for, ele ainda é seu pai. E a gente gastou uma fortuna de esforço, tempo e dinheiro tentando achar ele.";
			link.l1.go = "WildRose_Mary_253";
		break;

		case "WildRose_Mary_253":
			dialog.text = "Mas e se ele nem quiser falar com a gente? Por que ele mandou matarem a gente?";
			link.l1 = "Pelo menos, ele talvez nem soubesse exatamente quem estava atrás dele. O Fadey podia ter só dado seu nome e deixado de fora os detalhes sobre você. Caso contrário, duvido que a gente precisasse sujar as lâminas de sangue agora.";
			link.l1.go = "WildRose_Mary_254";
		break;

		case "WildRose_Mary_254":
			dialog.text = "E agora? A gente vai pra Baía de Chetumal? Mas se ele armou uma armadilha pra gente aqui... quem sabe o que tá esperando a gente lá, né?";
			link.l1 = "Temos a vantagem do tempo antes que ele descubra o que aconteceu aqui. Vamos aproveitar isso. Vamos navegar até a baía e mandar um grupo por terra, liderado por um dos oficiais, para nos apoiar.";
			link.l1.go = "WildRose_Mary_255";
		break;

		case "WildRose_Mary_255":
			dialog.text = "Parece razoável, sabe? Mas quem vai liderar isso?";
			if (CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				link.l1 = "Tichingitu. Ele é um veterano de batalhas em terra. Ninguém saberia lidar com isso melhor do que ele.";
				link.l1.go = "WildRose_Etap6_Tichingitu";
			}
			if (CheckPassengerInCharacter(pchar, "Duran"))
			{
				link.l2 = "Claude. Ele não vai gostar, claro, mas vai superar, sabe?";
				link.l2.go = "WildRose_Etap6_Duran";
			}
			if (CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l3 = "Hercule. Ele sabe exatamente como essas coisas são feitas.";
				link.l3.go = "WildRose_Etap6_Tonzag";
			}
			if (CheckPassengerInCharacter(pchar, "Irons"))
			{
				link.l4 = "Tommy. Mesmo que algo dê errado, esse cara vai dar um jeito, pode confiar em mim.";
				link.l4.go = "WildRose_Etap6_Irons";
			}
			if (CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l5 = "Longway. Não é a primeira vez dele rastreando um inimigo pela selva.";
				link.l5.go = "WildRose_Etap6_Longway";
			}
			if (!CheckPassengerInCharacter(pchar, "Tichingitu") && !CheckPassengerInCharacter(pchar, "Duran") && !CheckPassengerInCharacter(pchar, "Tonzag") && !CheckPassengerInCharacter(pchar, "Irons") && !CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l99 = "Alonso. Ele é rápido com a espada, e não é nenhum bobo.";
				link.l99.go = "WildRose_Etap6_Alonso";
			}
		break;
		
		case "WildRose_Etap6_Tichingitu":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tichingitu");
		break;
		
		case "WildRose_Etap6_Duran":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Duran");
		break;
		
		case "WildRose_Etap6_Tonzag":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tonzag");
		break;
		
		case "WildRose_Etap6_Irons":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Irons");
		break;
		
		case "WildRose_Etap6_Longway":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Longway");
		break;
		
		case "WildRose_Etap6_Alonso":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Alonso");
		break;
		
		//
		case "WildRose_Tichingitu_1":
			dialog.text = "Tichingitu ouve com atenção, capitão "+pchar.name+".";
			link.l1 = "Meu amigo, você tem uma tarefa importante pela frente. Uma gangue de assassinos está escondida na Baía de Chetumal. Você precisa rastreá-los e acabar com eles. Vamos nos aproximar pelo mar, no nosso navio.";
			link.l1.go = "WildRose_Tichingitu_2";
		break;

		case "WildRose_Tichingitu_2":
			dialog.text = "";
			link.l1 = "Você vai liderar um grupo dos nossos homens pela selva para pegar aqueles desgraçados por trás. Tem alguma pergunta pra mim?";
			link.l1.go = "WildRose_Tichingitu_3";
		break;

		case "WildRose_Tichingitu_3":
			dialog.text = "O índio não tem perguntas. Amanhã ao meio-dia o grupo estará no lugar e vai esperar lá em emboscada.";
			link.l1 = "Muito bem, Tichingitu. Boa sorte pra você.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Duran_1":
			dialog.text = " Chamou, capitão? ";
			link.l1 = "Tenho um trabalho pra você, Claude.";
			link.l1.go = "WildRose_Duran_2";
		break;

		case "WildRose_Duran_2":
			dialog.text = "";
			link.l1 = "Precisamos reunir um grupo de combatentes e guiá-los pela selva até a Baía de Chetumal. Lá, uma gangue liderada por um tal de Rupert Casper está nos esperando. Eles prepararam uma armadilha para a gente. Mas quem vai surpreender são eles – ou melhor, você que vai. Ataque quando eu der o sinal. Alguma dúvida? ";
			link.l1.go = "WildRose_Duran_3";
		break;

		case "WildRose_Duran_3":
			dialog.text = "Odeio atravessar a selva. Mas, como dizem, ordem é ordem. Te vejo lá - acho que por volta do meio-dia amanhã. ";
			link.l1 = "Boa sorte, Claude.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Tonzag_1":
			dialog.text = " Ouvindo, capitão. ";
			link.l1 = "Hercule, tem um trabalho pra você.";
			link.l1.go = "WildRose_Tonzag_2";
		break;

		case "WildRose_Tonzag_2":
			dialog.text = "Precisa de alguém pra encher de bala algum idiota cabeça-dura? Sou eu mesma, sempre pronta, sabe disso.";
			link.l1 = "Acertou. Você precisa liderar um grupo de combatentes do nosso navio pela selva até a Baía de Chetumal. Lá, você vai preparar uma emboscada para a gangue que, eu acho, vai estar esperando por nós.";
			link.l1.go = "WildRose_Tonzag_3";
		break;

		case "WildRose_Tonzag_3":
			dialog.text = "Eu achei que você tinha algo desafiador em mente, Cap. Mas isso aqui é só um passeio na taverna pra mim. Pode contar que estaremos lá até o meio-dia de amanhã.";
			link.l1 = "Te vejo lá. Boa sorte, Hercule.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Irons_1":
			dialog.text = " Ha, Capitão, por que essa cara séria? Vai pra um velório ou o quê? ";
			link.l1 = "Sempre o engraçadinho, né Tommy? Tenho uma pra você também – você não vai receber este mês. Nem no próximo. Por que essa tensão toda?";
			link.l1.go = "WildRose_Irons_2";
		break;

		case "WildRose_Irons_2":
			dialog.text = "Nem posso brincar...";
			link.l1 = "Há um tempo pra tudo, Tommy. Você ainda tem muito o que aprender. Agora presta atenção: reúna seu grupo e siga pela selva até a Baía de Chetumal. Quando chegar lá, espere pelo meu sinal.";
			link.l1.go = "WildRose_Irons_3";
		break;

		case "WildRose_Irons_3":
			dialog.text = "Atravessar a selva? A gente não chega lá antes do meio-dia de amanhã, no mínimo.";
			link.l1 = "Então, vamos nos encontrar lá amanhã ao meio-dia. Não ataquem sem ordens e não abandonem suas posições. Entendido? Vejo que sim. Agora, mãos à obra.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Longway_1":
			dialog.text = "Ouvindo de longe, Capitão.";
			link.l1 = "Oi, tenho um trabalho pra você.";
			link.l1.go = "WildRose_Longway_2";
		break;

		case "WildRose_Longway_2":
			dialog.text = "...";
			link.l1 = "Você vai liderar um grupo dos nossos homens pela selva até a Baía de Chetumal. Pode ser que encontrem inimigos por lá, então garanta que sua equipe esteja preparada.";
			link.l1.go = "WildRose_Longway_3";
		break;

		case "WildRose_Longway_3":
			dialog.text = "Longway entende tudo, não precisa se preocupar, Capitão. Vamos chegar ao nosso destino por volta do meio-dia de amanhã.";
			link.l1 = "Vai lá, e toma cuidado.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Alonso_1":
			dialog.text = "Chamou por mim, Capitão?";
			link.l1 = "Sabe? Escuta bem, Alonso.";
			link.l1.go = "WildRose_Alonso_2";
		break;
		
		case "WildRose_Alonso_2":
			dialog.text = "";
			link.l1 = "Você vai liderar um grupo de combatentes pela selva até a Baía de Chetumal. É bem provável que uma quadrilha de canalhas esteja esperando por lá. Vocês vão precisar se posicionar e atacar por trás quando eu der o sinal.";
			link.l1.go = "WildRose_Alonso_3";
		break;

		case "WildRose_Alonso_3":
			dialog.text = "Fácil demais, Capitão. Mas não desembarque na baía antes do meio-dia de amanhã – minha tripulação e eu não vamos chegar lá antes disso, sabe?";
			link.l1 = "Prepare-se, Alonso. E que Deus nos ajude.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Mary_256":
			dialog.text = "Charles, você viu aquilo?";
			link.l1 = "Parece que já estão esperando a gente. Aposto que estão só nos espreitando logo depois daquela curva.";
			link.l1.go = "WildRose_Mary_257";
		break;

		case "WildRose_Mary_257":
			dialog.text = "Ainda estamos de pé. Eles nem estão tentando atirar na gente, sabe. ";
			link.l1 = "Talvez ele ainda queira conversar com a gente primeiro. Vamos evitar provocar ele – a gente vai lá, nossa tripulação vai estar do nosso lado. Vem, vamos acabar logo com isso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_18_1");
		break;
		
		case "WildRose_Rupert_1":
			dialog.text = "Pare aí mesmo! Nem mais um passo! Rapazes, se esse almofadinha se mexer – encham ele de bala. Não toquem na garota.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_1_add";
			// link.l1.go = "WildRose_Rupert_87";
		break;

		case "WildRose_Rupert_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_2", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_2":
			dialog.text = "Pai?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_3":
			sld = CharacterFromID("Mary");
			if (CheckCharacterItem(sld, "hat11")) // У Мэри есть своя шляпа
			{
				dialog.text = " Bomm... Já vi muita coisa nessa minha vida longa e difícil. Quando acho que nada mais pode me surpreender, a vida me mostra que estou errada. Então, você realmente sobreviveu... E ainda ficou com o chapéu da Theresa. Nunca pensei que fosse ver esse chapéu de novo. ";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_1_add";
			}
			else
			{
				dialog.text = " Bomm... Já vi muita coisa nessa minha vida longa e difícil. Quando acho que nada mais pode me surpreender, a vida me mostra que estou errada. Então, você realmente sobreviveu, Julia... ";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_add";
			}
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_3_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_2":
			dialog.text = "A Orelie me deu isso antes de... partir.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_3":
			dialog.text = "Que emocionante... Estou quase chorando. E eu achava que tinham enterrado a Teresa junto com ele. Ela nunca se separou disso nem por um segundo desde que eu dei pra ela. Sua mãe, mesmo sendo só uma criada, tinha tanta sede de aventura que parecia transbordar dela, sabe? Quando encontrei isso durante a captura do Fleur-de-Lys, soube na hora que a Teresa ia adorar. Ela ficava engraçada com aquele chapéu, mas não ligava: só tirava pra dormir. Mas você, Julia, ficou perfeito em você.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_add":
			StartInstantDialog("Mary", "WildRose_Rupert_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_4":
			dialog.text = "Julia? Não, você está enganado, meu nome é Mary...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_4_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_5":
			dialog.text = "Hum, é mesmo. Então aqueles desgraçados ignoraram o que eu disse e resolveram agir por conta própria. Bem, não dava pra esperar outra coisa desses cães católicos.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_5_add":
			StartInstantDialog("Mary", "WildRose_Rupert_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_6":
			dialog.text = "Você... Você... Você é mesmo meu pai?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_6_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_6_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_7":
			dialog.text = "Bem, se não fosse por isso, você e seu amigo já estariam caídos no chão, cheios de chumbo. Faz tempo que não acredito em Deus nem no Diabo, mas talvez eles existam mesmo. O primeiro com certeza—já que Ele te deu o rosto da Teresa. E foi isso que salvou sua vida agora. Como é mesmo aquele ditado... Deus escreve certo por linhas tortas, sabe? Ha-ha-ha!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_7_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_7_add":
			StartInstantDialog("Mary", "WildRose_Rupert_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_8":
			dialog.text = "Papai... Eu... Eu não entendo, sabe...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_8_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_8_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_9":
			dialog.text = " Claro que não. Como você poderia...";
			link.l1 = "Você não parece exatamente feliz em ver sua filha, senhor Casper. Principalmente depois de admitir que ela é sua, sabe?";
			link.l1.go = "WildRose_Rupert_10";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_10":
			dialog.text = "Você não é bobo, não, dândi... Qual é mesmo o seu nome?";
			link.l1 = ""+GetFullName(pchar)+". Enquanto a gente procurava por você, ficava pensando como você tinha vivido esse tempo todo. Se é que tinha sobrevivido, sabe? Mas vejo que você se adaptou muito bem aqui, senhor... Northwood.";
			link.l1.go = "WildRose_Rupert_11";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_11":
			dialog.text = "Ah, então você até descobriu isso. Olha, meus respeitos, monsieur Come-Sapo, o que mais posso dizer – já que eu mesma cuidei de não deixar nenhuma ponta solta.";
			link.l1 = "Tem mais. A gente sabe sobre o 'Cornwall', sobre a carga dele, e sobre o Joshua Casper, o nome que você pegou emprestado por um tempo, e o sobrenome dele—esse aí parece que você resolveu ficar pra sempre, né?";
			link.l1.go = "WildRose_Rupert_12";
		break;

		case "WildRose_Rupert_12":
			dialog.text = "Bravo (aplausos). Estou impressionada. Descobriu tudo isso sozinho, ou meu querido filho também te ajudou?";
			link.l1 = "Eu não teria conseguido sem a Mary. Ela estava decidida a descobrir tudo sobre os pais dela. Não foi difícil entender o que aconteceu com a Theresa, mas encontrar você nos levou um bom tempo...";
			link.l1.go = "WildRose_Rupert_13";
		break;
		
		case "WildRose_Rupert_13":
			dialog.text = "Isso tudo é tão comovente que quase me faz chorar. E aí, filha, ficou satisfeita? Feliz agora? Quer dar um abraço no papai?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_13_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_13_add":
			StartInstantDialog("Mary", "WildRose_Rupert_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_14":
			dialog.text = "Eu não entendo, pai... Por que você está me atormentando? Pra quê?! (grita) Foi você quem me deixou lá—naqueles destroços de navio! E depois nunca nem pensou em voltar, sabe! Por quê? Quem é você, afinal, e quem são essas pessoas aí atrás de você?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_14_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_14_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_15":
			dialog.text = "Me conta, "+pchar.lastname+", ela sempre faz esses escândalos? Ela puxou isso da mãe. Teresa era uma mulher incrível, a melhor que já conheci. Mas, olha, quando ficava brava, gritava como ninguém... O que posso dizer... Irlandesa.";
			link.l1 = "Não ouse insultá-la! A Mary não tem culpa das suas desgraças, e com certeza não merece ser tratada assim.";
			link.l1.go = "WildRose_Rupert_16";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;
		
		case "WildRose_Rupert_16":
			dialog.text = "Tá tentando me calar, garoto?!";
			link.l1 = "Pelo contrário. Quero que você conte a sua história pra gente. É muito importante pra Mary saber disso. Mas não vou deixar você insultá-la. Então se controle.";
			link.l1.go = "WildRose_Rupert_17";
		break;
		
		case "WildRose_Rupert_17":
			dialog.text = "Você acha que eu estou louca pra abrir meu coração pra você? Minha vida foi do jeito que foi e, como vocês católicos gostam de dizer—Deus é minha testemunha—não me arrependo de nada. Só de ter perdido a Teresa naquela época—por causa dela. Eu te odeio, minha filha? Talvez já tenha odiado, mas agora, sinceramente, não me importo mais com você.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_17_add";
		break;

		case "WildRose_Rupert_17_add":
			StartInstantDialog("Mary", "WildRose_Rupert_18", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_18":
			dialog.text = "You’re blaming me for Mama’s death?! How does that make any sense? What did I do - get born? Is that my crime? Fine, Father. +pchar.name+ is right - just tell us everything. After that, we’ll leave. You’ll never see my face again... if that’s what you want... (begins sobbing)";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_18_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_19", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_19":
			dialog.text = "Ahhh, igualzinha à Theresa. Parece até que voltei vinte anos no tempo, sabe? Ah, quer saber, faz do seu jeito. Não vou gostar nada de reviver todas essas lembranças... Então, se no fim dessa historinha eu sentir vontade de enfiar uma bala no seu crânio, querido — bem, a culpa é toda sua.";
			link.l1 = "Então você vai levar um tiro também, Rupert. E acho que isso não faz parte dos seus planos – você parece alguém que valoriza a própria vida.";
			link.l1.go = "WildRose_Rupert_20";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_20": //
			dialog.text = "Eu sei o valor da minha vida, garoto. Isso não é o mesmo que dar valor a ela. Mas o que você entende disso, né? Tá bom, vamos direto ao ponto. Quer ouvir a história toda? Então lá vai. Eu nasci numa fazenda perto de Eastbourne – uma cidadezinha na costa do Canal – lá por 1611. Um ano a mais, um ano a menos, quem sabe – minha mãe nunca acertava as datas mesmo, também, com tanto álcool que ela bebia, né?";
			link.l1 = "Infância difícil? Entendi.";
			link.l1.go = "WildRose_Rupert_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_21":
			dialog.text = "Se você pediu, então escuta e fica quieta, não vem bancar a esperta. Eu nunca tive pai, e nem sabia o motivo—mas diferente de você, garotinha, eu nunca liguei pra isso. O sobrenome que herdei dele já me bastava. Quando eu tinha treze anos, numa noite, corsários de Dunquerque desembarcaram na costa. Sabe, hoje em dia o pessoal não gosta de lembrar disso, mas não foram só os holandeses que sofreram com eles, nós também—nós que vivíamos na velha costa leste da Inglaterra.";
			link.l1 = "Fiquei sabendo disso. Aqueles caras não pouparam ninguém. Como é que você conseguiu sair viva, sabe?";
			link.l1.go = "WildRose_Rupert_22_1";
			link.l2 = "Eu sei bem os horrores que eles deixaram pra trás. Não pouparam ninguém – nem velhos, nem jovens. Por isso é ainda mais incrível que você tenha sobrevivido.";
			link.l2.go = "WildRose_Rupert_22_2";
		break;

		case "WildRose_Rupert_22_1":
			dialog.text = "Naquela noite, aqueles porcos papistas incendiaram várias fazendas, inclusive a nossa. Eu consegui escapar, mas minha mãe, que tinha enchido a cara de sidra a ponto de não conseguir tirar o traseiro gordo da cama, queimou ali mesmo. Foi culpa dela, claro – mas ainda assim, era minha mãe.";
			link.l1 = "E foi aí que você começou a odiar todos os papistas?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_22_2":
			dialog.text = "Aquela noite, aqueles porcos papistas queimaram várias fazendas, inclusive a nossa. Eu consegui escapar, mas minha mãe, que tinha enchido a cara de sidra a ponto de não conseguir tirar o traseiro gordo da cama, acabou queimando ali mesmo. Culpa dela, claro – mas ainda assim era minha mãe.";
			link.l1 = "E foi aí que você começou a odiar todos os papistas?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_23":
			dialog.text = "Foi aí que eu aprendi a odiar a fome, sabe? Aposto que você nunca sentiu isso de verdade, mas eu senti—na pele mesmo. Fui pro norte, pra capital, e me alistei na marinha—lá, distribuíam mais chicotada do que comida, mas umas boas dúzias já foram o bastante pra me colocar nos eixos. Depois disso, me acostumei—e acabei me apaixonando pela vida no mar. Principalmente porque nunca tinha um momento de tédio...";
			link.l1 = "Eu acredito nisso. A reputação da Marinha Real fala por si só.";
			link.l1.go = "WildRose_Rupert_24";
		break;

		case "WildRose_Rupert_24":
			dialog.text = "Em 1633, passei no exame para tenente e fui designado para a corveta Cornwall.";
			link.l1 = "Sob o comando de Joshua Casper.";
			link.l1.go = "WildRose_Rupert_26";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_26":
			dialog.text = "Ah, sim... Joshua Casper... Não existe canalha maior em toda essa maldita frota. Já se passaram tantos anos, e mesmo assim aquele porco ainda assombra meus sonhos.";
			link.l1 = "O que ele fez, então? Te colocou de vigia extra por ser animada demais? Ou será que ele era papista em segredo?";
			link.l1.go = "WildRose_Rupert_27";
		break;

		case "WildRose_Rupert_27":
			dialog.text = "Aquele desgraçado cruel treinava a tripulação tão duro que tinha gente caindo no mar de puro cansaço. Já que você sabe o nome dele e que ele era o comandante do 'Cornwall', deve ter visto os papéis dele—brilhando como bunda de gato lambida, sabe?   Nosso heróico Joshua tinha uma caixa cheia de medalhas. Um monte de rapaz ingênuo como você queria servir sob o comando dele—pode falar o que quiser, mas ele cortava vocês, comedores de rã, como foice afiada passando na grama molhada depois da chuva, né?—mas quando botavam os pés no 'Cornwall', percebiam rapidinho o erro que tinham feito.   A gente já estava de saco cheio de aguentar aquilo, "+pchar.lastname+". Alguns até escreveram petições pedindo transferência – mas elas sumiram nas prateleiras do Almirantado, ou viraram cinzas em seus fornos. Mesmo assim, a vida nos deu uma chance – não tiraram a gente do 'Cornwall', mas colocaram outra pessoa a bordo. John Lawson – o queridinho do Cromwell, você já deve ter ouvido falar dele, né?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_28";
		break;

		case "WildRose_Rupert_28":
			dialog.text = "Ele já sabia puxar o saco naquela época — e talvez ele e o Casper até tivessem se dado bem, mas eu não deixei isso acontecer. Eu armei pro Johnny, e o Joshua, sem saber de tudo, bateu nele com a bengala, tomado pela raiva.";
			link.l1 = "Uma verdadeira humilhação para um oficial. E o Lawson contou tudo pro pai dele?";
			link.l1.go = "WildRose_Rupert_32";
		break;

		case "WildRose_Rupert_32":
			dialog.text = "Claro que ele fez – esse era o meu plano. Mas, sabe, o sistema não pode se devorar. Tudo foi abafado – ofereceram uma promoção antecipada pro Lawson, e o Joshua e o 'Cornwall' foram jogados pras sombras – transferiram a gente de Londres pra Plymouth, lá no sul da Inglaterra. A gente podia ter continuado aterrorizando vocês, comedores de rã, mas o 'Cornwall' virou navio de suprimentos, levando carga militar pra Dundalk, uma cidadezinha na Irlanda.";
			link.l1 = "E foi lá que você conheceu a Teresa?";
			link.l1.go = "WildRose_Rupert_33";
		break;

		case "WildRose_Rupert_33":
			dialog.text = "Primeira vez que atracamos lá. Theresa O’Fatt – ela era garçonete numa taverna local. Levou três dias pra gente perceber que fomos feitos um pro outro. Acho que você entende o que eu quero dizer, né? "+pchar.lastname+", não é?";
			link.l1 = "Acho que sim.";
			link.l1.go = "WildRose_Rupert_34_1";
			link.l2 = "Olhando pra você agora, ninguém diria que você sabe o que é 'amor'.";
			link.l2.go = "WildRose_Rupert_34_2";
		break;

		case "WildRose_Rupert_34_1":
			dialog.text = "Eu nunca conheci alguém tão incrível – nem antes, nem em todos esses vinte anos depois. Pela primeira vez na vida, me senti realmente feliz, e ela também – ou pelo menos foi o que disse.";
			link.l1 = "E você pediu pra ela ir embora com você?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Rupert_34_2":
			dialog.text = "Eu nunca conheci alguém mais incrível – nem antes, nem em todos esses vinte anos depois. Pela primeira vez na vida, eu me senti realmente feliz, e ela também – ou pelo menos foi o que disse.";
			link.l1 = "E você pediu pra ela ir embora com você?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_35":
			dialog.text = "Claro que não – isso era impossível, já que o 'Cornwall' ainda era um navio de guerra comandado por um desgraçado. Depois de uma semana que pareceu uma eternidade, nosso brigue partiu de volta para Plymouth. Voltamos para Dundalk dois meses depois – e a Teresa me deixou sem chão com a notícia: ela estava grávida.";
			link.l1 = "É, isso costuma acontecer quando você dorme com uma garota.";
			link.l1.go = "WildRose_Rupert_36";
		break;

		case "WildRose_Rupert_36":
			dialog.text = "Não venha bancar a esperta, sua pestinha. Teresa estava chorando no meu ombro, e eu tentando entender o que fazer. Eu queria ficar com ela, de verdade – mas mesmo assim, sentia que nada de bom sairia daquela criança.   Tentei convencer a Teresa a se livrar disso enquanto ainda dava tempo – mas, em vez disso, veio uma crise de histeria ainda pior. Não conseguimos pensar em nada na hora – então decidimos esperar mais dois meses, até a próxima vez que o ‘Cornwall’ voltasse para Dundalk, já que naquela época o Almirantado ainda não tinha transformado sua fúria contra Casper em misericórdia.   Quando voltamos, não encontrei ela de imediato — a barriga da Teresa já estava evidente, e, como o dono da taverna onde ela trabalhava me contou, o desgraçado do pai dela bateu nela e a trancou em casa. Nem preciso dizer que acertei as contas com aquele velho de um jeito que ele quase vomitou as próprias tripas. Obviamente, não tinha como ela continuar morando naquela casa.";
			link.l1 = "E você trouxe ela para o 'Cornwall'?";
			link.l1.go = "WildRose_Rupert_37";
		break;

		case "WildRose_Rupert_37":
			dialog.text = "Eu tive que tomar uma decisão rápida. Eu sabia que o Casper não ia aceitar uma mulher a bordo, então planejei roubar um barco na noite depois que partíssemos e seguir para Dublin, que ficaria logo ao nosso lado de estibordo.";
			link.l1 = "E o que aconteceu? Eles te pegaram?";
			link.l1.go = "WildRose_Rupert_38";
		break;

		case "WildRose_Rupert_38":
			dialog.text = "Exatamente. Casper já tinha se servido de uma boa dose de uísque, então estava surdo a qualquer súplica, simplesmente mandou jogar a menina ao mar. Não importava o quanto eu implorasse, ele só ria até perder o fôlego—caramba, tô te contando isso e ainda consigo ouvir a risada dele na minha cabeça...";
			link.l1 = "E foi aí que você decidiu começar um motim?";
			link.l1.go = "WildRose_Rupert_39";
		break;

		case "WildRose_Rupert_39":
			dialog.text = "Eu não tinha outra escolha. Peguei uma pistola do cinto de um guarda ali perto e enfiei uma bala na testa daquele desgraçado. Na mesma hora começou um massacre a bordo — ninguém gostava do capitão, mas o medo do tribunal era mais forte. Quase um terço da tripulação perdeu a vida — quando finalmente caímos em nós, o convés inteiro do 'Cornwall' estava coberto de sangue e cheio dos corpos dos nossos companheiros mortos.";
			link.l1 = " Depois disso, acho que voltar pra Inglaterra estava fora de questão. Vocês iam acabar todos na forca lá, sabe?";
			link.l1.go = "WildRose_Rupert_40";
		break;
		
		case "WildRose_Rupert_40":
			dialog.text = "Eu tinha certeza de que conseguiria conduzir o ‘Cornwell’ pelo oceano. Aqui, ninguém conhecia nossos rostos, e isso nos dava uma chance de começar uma vida nova. Convencer os outros oficiais foi fácil — não tanto pela minha autoridade, mas pelo conteúdo de alguns baús, dos quais os marinheiros comuns não faziam ideia. A tripulação decidiu — Joshua Casper deveria ser mantido vivo. Nós, os oficiais das terras altas, resolvemos ganhar tempo, sacrificar um dos baús e aportar em Antígua, onde eu assumiria o nome dele. Depois disso, pretendíamos seguir para Providence. E foi exatamente assim que aconteceu: ninguém desconfiou da troca, mas quando estávamos a apenas alguns dias de Providence, algum desgraçado abriu a boca sobre o segundo baú — e isso dividiu a tripulação.";
			link.l1 = "Então agora eles se amotinaram contra você?";
			link.l1.go = "WildRose_Rupert_45";
		break;

		case "WildRose_Rupert_45":
			dialog.text = "Não, mas o número de homens dispostos a continuar servindo nosso glorioso rei caiu rápido. E também não tinha muitos querendo virar pirata, sabe? Então a gente achou um meio-termo – ancoramos em um porto francês, vendemos o navio, dividimos o dinheiro da venda e do baú, e cada um seguiu seu caminho.";
			link.l1 = "E você não se importou em ter que viver entre esses católicos que você tanto despreza?";
			link.l1.go = "WildRose_Rupert_46";
		break;

		case "WildRose_Rupert_46":
			dialog.text = "Nessa altura, eu já não me importava onde a gente fosse parar. A Teresa — ela fazia de conta que estava bem, mas depois de três meses balançando sem parar, estava como qualquer mulher grávida ficaria. E assim como três meses antes, eu não ligava nem um pouco se estava cercada de católicos, desde que estivesse com ela.";
			link.l1 = "Mas não existem assentamentos franceses no noroeste do Mar do Caribe, e nunca existiram.";
			link.l1.go = "WildRose_Rupert_47";
		break;

		case "WildRose_Rupert_47":
			dialog.text = "Quando as coisas a bordo do 'Cornwall' chegaram ao limite, já tínhamos percorrido metade do caminho com um vento favorável, que naquela altura não nos deixava mais mudar o rumo para St. Christopher...";
			link.l1 = "E você escolheu Tortuga como destino?";
			link.l1.go = "WildRose_Rupert_48";
		break;

		case "WildRose_Rupert_48":
			dialog.text = "Naquela época, era só uma vila simples. Pra despistar qualquer possível perseguição das autoridades, a gente trocou a placa do nome na popa—então 'Cornwall' virou 'Wrangler'.";
			link.l1 = "Mas por algum motivo, você nunca chegou à Ilha da Tartaruga. Não é possível que tenha se desviado tanto a ponto de acabar a oeste de Cuba em vez de Tortuga, né?";
			link.l1.go = "WildRose_Rupert_49";
		break;

		case "WildRose_Rupert_49":
			dialog.text = "Só pra você saber, eu sou uma navegadora experiente—melhor que a maioria. Não teve erro, a gente estava mantendo o rumo firme pro norte. Mas assim que entramos no Canal do Vento, uma tempestade terrível pegou a gente. Até hoje eu me pergunto como diabos a gente não foi jogado contra a costa de Cuba, mas arrastado ao longo dela...";
			link.l1 = "Um verdadeiro milagre, nada menos que isso.";
			link.l1.go = "WildRose_Rupert_50";
		break;

		case "WildRose_Rupert_50":
			dialog.text = "Abracei Teresa, que chorava sem parar, e rezei ao Senhor com todo o meu coração, implorando que nos enviasse salvação. E Ele realmente nos ajudou.";
			link.l1 = "Você foi levado pela corrente até a Ilha da Justiça.";
			link.l1.go = "WildRose_Rupert_51";
		break;

		case "WildRose_Rupert_51":
			dialog.text = "Justiça – ah, sim! Quando o 'Wrangler' bateu no recife, ele se partiu em dois, mas de algum jeito conseguiu não afundar – só o bastante pra ser levado até onde estavam aqueles outros destroços. A tempestade continuou furiosa por quase mais dois dias e, quando finalmente acalmou – o pessoal daquela ilhota miserável veio nos salvar.";
			link.l1 = "Você, Teresa e mais dois marinheiros. Já temos uma ideia geral do que aconteceu depois. Melhor você contar como saiu da prisão e deixou a ilha.";
			link.l1.go = "WildRose_Rupert_63";
		break;

		case "WildRose_Rupert_63":
			dialog.text = "Eu queria que tivessem me matado logo naquela época... Se eu soubesse o que me esperava, tinha me acorrentado àquelas grades e não teria saído do lugar, sabe?";
			link.l1 = "Era mesmo menos confortável na tartana do que no brigue, sabe? "+npchar.name+"?";
			link.l1.go = "WildRose_Rupert_64_1";
			link.l2 = "Só não me diga que você também ficou preso numa tempestade numa tartana, sabe?";
			link.l2.go = "WildRose_Rupert_64_2";
		break;

		case "WildRose_Rupert_64_1":
			dialog.text = "Tartana? Ha-ha-ha... Sabe, esse era o meu plano. Achei que tinha dado sorte. O chefe da guarda da prisão era um ex-oficial da Marinha Inglesa, e acabou tendo pena de mim. Ele me contou tudo sobre as tartanas dos contrabandistas cubanos, e que estavam planejando me executar. Acho que dá pra dizer que ele era um homem de honra—foi ele quem me ofereceu a chance de fugir, pra deixar meu destino nas mãos do acaso.";
			link.l1 = "Eu não entendo... Se não foi nas tartanas, então como você saiu da ilha?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_64_2":
			dialog.text = "Tartana? Ha-ha-ha... Sabe, esse era o meu plano. Achei que tinha dado sorte. O chefe dos guardas da prisão era um ex-oficial da Marinha Inglesa, e acabou se compadecendo da minha situação. Foi ele quem me contou sobre as tartanas dos contrabandistas cubanos, e que estavam planejando me executar. Talvez você possa dizer que ele era um homem de honra — ele mesmo se ofereceu para me deixar fugir, pra eu deixar meu destino nas mãos do acaso.";
			link.l1 = "Eu não entendo... Se não foi nas tartanas, então como você saiu da ilha?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Rupert_68":
			dialog.text = "Se você só calar a boca e ouvir, vai entender. Eu estava nadando em direção às tartanas, nadando por um bom tempo—até que vi uma luz além da parede de chuva. Era algo absolutamente inacreditável, sabe? Brilhava como o sol no convés de um dos galeões meio afundados, e eu fui direto pra lá. Sem saber ainda que estava cometendo o pior erro da minha vida. Saí da água usando a escada de embarque—e fiquei cara a cara com a luz. Ela cintilava acima de uma estátua dourada e...";
			link.l1 = "O ídolo de Kukulkan. Isso mesmo, naquela época o 'San Jeronimo' ainda não tinha afundado...";
			link.l1.go = "WildRose_Rupert_69";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_69":
			dialog.text = "Então, você também viu ele, "+pchar.lastname+"?";
			link.l1 = "Não só vi, não. Eu viajei pelo espaço com a ajuda dele, e mais de uma vez, sabe.";
			link.l1.go = "WildRose_Rupert_70";
		break;

		case "WildRose_Rupert_70":
			dialog.text = "Você está mentindo! Várias vezes, é isso?! Então como é que você está aqui, tão cheia de vida?!";
			link.l1 = "Depois que fui levada, tomei uma poção indígena, e foi isso que me ajudou a sobreviver e recuperar minhas forças.";
			link.l1.go = "WildRose_Rupert_71";
		break;

		case "WildRose_Rupert_71":
			dialog.text = "Ah, então é assim. Você faz ideia de quanto tempo eu levei pra recuperar minhas forças? Faz ideia?!";
			link.l1 = "Acho que já sei. Você tocou no ídolo, aí ele te mandou pra Dominica – pra aldeia indígena, onde te sacrificaram pra estátua, e depois você foi parar no continente, né?";
			link.l1.go = "WildRose_Rupert_72";
		break;

		case "WildRose_Rupert_72":
			dialog.text = "Exatamente. Nunca senti uma dor como aquela, deitada ao lado daquela estátua. Nem sei com o que comparar. Talvez se uma casa de pedra desabasse em cima de você — ainda assim, não sofreria tanto. Assim que recobrei a consciência, vi um monte de nativos vindo de novo pra cima de mim. Se eu falasse a língua deles — juro por Deus, eu teria implorado pra me matarem ali mesmo.";
			link.l1 = "Eram aqueles índios Miskito da aldeia aqui perto?";
			link.l1.go = "WildRose_Rupert_76";
		break;

		case "WildRose_Rupert_76":
			dialog.text = "São eles. Me arrastaram para uma das cabanas, onde um nativo estranho—não parecia com os outros—me fez engolir alguma coisa. A dor aliviou um pouco, mas não passou de verdade. No fim do dia, me levaram até a fogueira, e aquele desgraçado pintado começou a fazer algum tipo de ritual. Covarde miserável.";
			link.l1 = "Olho de Cobra... Você devia era agradecer a ele por ter salvado sua pele.";
			link.l1.go = "WildRose_Rupert_77";
		break;

		case "WildRose_Rupert_77":
			dialog.text = "Resgate?.. Três anos, "+pchar.lastname+". Por três anos eu fiquei quase imóvel, me sujando e me molhando, acordando no meu próprio vômito – porque eu simplesmente não aguentava mais aquelas poções e misturas fedorentas que eles enfiavam goela abaixo! E depois passei quase mais um ano reaprendendo a andar.";
			link.l1 = "Uma história de partir o coração. Mas, sinceramente, eu quase sinto pena de você.";
			link.l1.go = "WildRose_Rupert_78";
		break;

		case "WildRose_Rupert_78":
			dialog.text = "Enfia sua piedade no rabo gordo do seu Papa católico. Não preciso da simpatia de ninguém. Quer que eu continue, ou vai chorar um pouco, pavãozinho?";
			link.l1 = "Essa viagem com certeza não melhorou seus modos. Mas, sabe, pela Mary, eu vou aguentar. Embora eu ache que já aprendemos o principal—mas vamos ouvir você até o fim.";
			link.l1.go = "WildRose_Rupert_79";
		break;

		case "WildRose_Rupert_79":
			dialog.text = "De algum jeito, consegui me reerguer, deixei aquela vila amaldiçoada e segui para a costa, para a Baía de Amatique. Lá, encontrei alguns contrabandistas cujo navio estava ancorado por perto e me juntei a eles, dizendo que me chamava Rupert Casper — não queria abrir mão do meu primeiro nome, mas também mantive o sobrenome de um daqueles que destruíram minha vida. Só pra nunca esquecer por que vim parar aqui.";
			link.l1 = " Todo mundo é culpado, na sua cabeça, Northwood... menos você. Mas até entendo — anos de humilhação e sofrimento, e agora você está preso nesse mato. Quem não perderia a cabeça? ";
			link.l1.go = "WildRose_Rupert_80_1";
			link.l2 = "Você já passou por muita coisa, Northwood – disso ninguém duvida. E agora, olha só onde você está... No meio do mato, no limite da civilização. Aqui você não vai enlouquecer...";
			link.l2.go = "WildRose_Rupert_80_2";
		break;

		case "WildRose_Rupert_80_1":
			dialog.text = "Eu sou a dona dessas matas, "+pchar.lastname+". Em mais de quinze anos, eu passei de uma marinheira infeliz num navio de contrabandistas para a líder deles. Não só a capitã de um barquinho qualquer, mas a dona de toda a costa, da Baía de Amatique até a Baía da Perdição.";
			link.l1 = "Bom, essa foi uma resposta e tanto, admito.";
			link.l1.go = "WildRose_Rupert_81";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_80_2":
			dialog.text = "Eu sou a dona dessas matas, "+pchar.lastname+". Em mais de quinze anos, eu passei de uma marinheira infeliz num navio de contrabandistas para líder deles. Não só a capitã de um barquinho qualquer, mas a dona de toda a costa, da Baía de Amatique até a Baía do Destino.";
			link.l1 = "Bom, isso foi uma bela resposta, admito.";
			link.l1.go = "WildRose_Rupert_81";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "WildRose_Rupert_81":
			dialog.text = "Alguns dizem que isso aqui é domínio do Demônio da Floresta... Que mentira descarada – essas terras são minhas. E o Svensson sabe disso, sabe? Já mandou os capangas dele aqui mais de uma vez, tentou descobrir quem eu sou – e nenhum deles voltou pra contar a história. Vivo, né? Dá pra contar nos dedos de uma mão quem sabe o nome com que comecei minha carreira de contrabandista, ou onde é que eu moro nesse mato.";
			link.l1 = "Então, agora você usa outro nome. Não me surpreende que tenha ficado nervosa quando ouviu que alguém estava procurando por Rupert Casper.";
			link.l1.go = "WildRose_Rupert_82";
		break;
		
		case "WildRose_Rupert_82":
			dialog.text = "Entrando em pânico? Sério mesmo, garoto? O único em pânico aqui é você – no meu território, cercado pelo meu povo, totalmente à minha mercê! Posso fazer o que eu quiser com você. E com ela também – só por ser o motivo de eu ter passado por todo aquele tormento!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_82_add";
		break;

		case "WildRose_Rupert_82_add":
			StartInstantDialog("Mary", "WildRose_Rupert_83", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_83":
			dialog.text = "Você é louco, simplesmente louco, sabe? Eu não conheço remédio ou médico que possa te consertar, Rupert Northwood! Você passou por um inferno, mas... como pode jogar toda a culpa em mim?!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_83_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_83_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_84", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_84":
			dialog.text = "Já te falei – se não fosse por você, nada disso teria acontecido. Só admite, sabe?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_84_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_84_add":
			StartInstantDialog("Mary", "WildRose_Rupert_85", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_85":
			dialog.text = "...";
			link.l1 = "Deixa ele, "+npchar.name+". Já ouvimos o suficiente. Tem caminhos que realmente não foram feitos pra gente seguir até o fim. Eu senti um pressentimento ruim quando a gente resolveu se meter nisso tudo. Mas não dei ouvidos. Uma pena.";
			link.l1.go = "WildRose_Rupert_85_add";
		break;
		
		case "WildRose_Rupert_85_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_86", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_86":
			dialog.text = "Pois é, então nenhum de vocês teria acabado aqui, presos e sem poder fazer nada. Agora sinta por si mesma, filha, o que eu passei!";
			link.l1 = "E quem foi que te disse que a gente não pode fazer nada? Tro-o-o-pa, às armas!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_20");
		break;
		
		case "WildRose_Rupert_87":
			dialog.text = "O que foi, novato? Perdeu alguém? Ha-ha-ha... Ha-ha-ha. HA-HA-HA-HA-HA-HA!!! Ah, você devia ver a sua cara agora, seu bobo! Ei, Mason, traz meu presente pros nossos convidados.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_22");
		break;
		
		case "WildRose_Rupert_88":
			dialog.text = "...";
			link.l1 = "Desgraçado! Onde estão as minhas pessoas?";
			link.l1.go = "WildRose_Rupert_89";
		break;
		
		case "WildRose_Rupert_89":
			dialog.text = "Você está falando daquele punhado de idiotas que achou que podia me pegar de surpresa? Meu amigo, o dono da taverna, me avisou a tempo da sua chegada na cidade, então eu dei a eles a recepção que mereciam... Alguns conseguiram escapar. Mas não se preocupe – peguei um deles vivo. Assim você mesmo pode ver qual destino te espera hoje.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_25");
			
			// WildRose_Etap6_LifeAfterDeath_24_1();
		break;
		
		case "WildRose_Rupert_90":
			dialog.text = "Canalha! Você vai pagar por isso! (chora) Eu juro, sabe!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_29");
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Alonso_11":
			dialog.text = "...";
			link.l1 = "Alonso! Que bom te ver!";
			link.l1.go = "WildRose_Alonso_12";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_12":
			dialog.text = "E eu também fico muito feliz em te ver, Capitão! Alguém avisou aquele canalha que você estava atrás dele — e fomos recebidos com uma chuva de balas de canhão no meio do caminho. Consegui recuar com alguns homens, e corremos direto para o porto para te alertar. Por sorte, o vigia de plantão me viu no barco que comprei às pressas na cidade e entendeu logo o que estava acontecendo. Ele reuniu os homens rapidinho — e viemos direto pra cá ajudar.";
			link.l1 = "Obrigada, meu amigo. Você nos salvou da morte certa.";
			link.l1.go = "WildRose_Alonso_13";
		break;

		case "WildRose_Alonso_13":
			dialog.text = "Isso não é nada. O que a gente faz agora, Cap?";
			link.l1 = "Reúna a tripulação e vá para o navio. Mary e eu precisamos de um tempo a sós.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		case "WildRose_Mary_261":
			dialog.text = "Meu Deus, "+pchar.name+"... Eu ainda não consigo, simplesmente não consigo acreditar. Meu pai... Ele é um monstro... Por que ele faria isso comigo? Será que ele enlouqueceu de vez?";
			link.l1 = "Ele teve que suportar um sofrimento terrível. O motim no 'Cornwall', a fuga pelo Atlântico, a tempestade e a morte da sua mãe. Não consigo imaginar como ele sobreviveu à travessia pelos portais daqueles ídolos sem a poção dos Comanche – mas foi isso que destruiu a mente dele.";
			link.l1.go = "WildRose_Mary_262";
			locCameraFromToPos(-3.80, 1.10, 52.00, false, 0.61, 0.27, 49.69);
			LAi_ActorAnimation(pchar, "sharle_mary_sit", "", 50.0);
			LAi_ActorAnimation(npchar, "sharle_mary_sit", "", 50.0);
			CharacterTurnAy(pchar, 6.00);
			CharacterTurnAy(npchar, 6.00);
		break;

		case "WildRose_Mary_262":
			dialog.text = "E se ele sempre foi assim? Ou talvez ele fosse tão canalha quanto, só que um pouco mais suave, mas amava de verdade minha mãe? E se tudo isso só libertou o que já estava dentro dele? E se for esse o caso... e se eu também tiver algo dele em mim? Isso pode acontecer, "+pchar.name+", sabe?";
			link.l1 = "Você com certeza pegou alguma coisa dele, "+npchar.name+". Na luta de hoje eu percebi – você luta com a mesma determinação, o mesmo fogo nos olhos e exatamente aquela fúria que ele tinha. Mas você não tem a loucura dele. Você é completamente diferente. Viva, aberta, com o coração na mão. É exatamente por isso que me apaixonei por você. E parece que Northwood estava certo: você tem o espírito da sua mãe, de cabo a rabo.";
			link.l1.go = "WildRose_Mary_263";
		break;

		case "WildRose_Mary_263":
			dialog.text = "Você acha mesmo isso, amor?";
			link.l1 = "Claro, meu amor. Se eu tivesse conhecido ele assim, sem saber quem ele era, nunca ia imaginar que vocês eram parentes.";
			link.l1.go = "WildRose_Mary_264";
		break;

		case "WildRose_Mary_264":
			dialog.text = "Sabe, não tem muita diversão na Ilha da Justiça. Desde pequena, eu amo esgrima—primeiro eu lutava com os meninos usando gravetos, depois com homens de verdade, lâminas de verdade, sabe? Sempre quis ser igual a eles... mas, de algum jeito, eu sempre me sentia mais fraca, mesmo quando eu ganhava.   Então eu só voltava pra casa e treinava mais um pouco. Ficava horas praticando, até minhas mãos começarem a tremer, sabe? É esse fogo que você quer dizer? Essa raiva de que você tá falando?";
			link.l1 = "De certa forma – sim. Acho que esse fogo te dá muito mais força do que você enxerga em si mesma. E, goste ou não, é um presente do seu pai. Mesmo que ele nunca tenha tido a intenção de te dar nada.";
			link.l1.go = "WildRose_Mary_265";
			locCameraSleep(false);
			locCameraFromToPos(-1.95, 1.81, 48.29, true, -2.11, -0.04, 52.55);
		break;

		case "WildRose_Mary_265":
			dialog.text = "Você acha que a gente fez certo em mexer no passado, sabe?";
			link.l1 = "Agora que a gente sabe de tudo... não parece mais uma ideia tão boa assim. Mas se você quer mesmo saber a verdade, tem que estar pronto pra encarar que talvez não vá gostar do que descobrir, sabe?";
			link.l1.go = "WildRose_Mary_266";
		break;

		case "WildRose_Mary_266":
			dialog.text = "Você está certa, "+pchar.name+", sabe... Vamos ficar aqui mais um pouco. Não estou com vontade de voltar pro navio agora. Só quero... sentar aqui, no silêncio.";
			link.l1 = "Claro, meu amor. Eu estava prestes a sugerir o mesmo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_38");
		break;
		
		// Тичингиту
		case "WildRose_Tichingitu_Final_1":  
			dialog.text = npchar.name+", chegou bem na hora, Capitão "+pchar.name+".";
			link.l1 = "Eu sabia que podia contar com você, meu amigo. Obrigada — ninguém teria feito melhor.";
			link.l1.go = "WildRose_Tichingitu_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tichingitu_Final_2":
			dialog.text = "A selva é "+npchar.name+"é casa. "+npchar.name+" feliz por lutar na selva. Selva me dá força "+npchar.name+".";
			link.l1 = "É exatamente por isso que eu te coloquei no comando do grupo. E valeu a pena — como você pode ver, eles nos receberam de braços abertos.";
			link.l1.go = "WildRose_Tichingitu_Final_3";
		break;

		case "WildRose_Tichingitu_Final_3":
			dialog.text = "Que capitão "+pchar.name+" planejando fazer agora?";
			link.l1 = "Eu e a Mary precisamos de um tempo a sós. Reúna os feridos e leve-os para o navio. Traga também os mortos — vamos enterrá-los no mar. E, "+npchar.name+"... diga ao Alonso que o pai da Mary deve ser enterrado aqui, do jeito protestante, sabe? Só ele e você podem saber disso. Mais ninguém — nem mesmo a Mary. Ela não precisa sofrer mais do que já sofreu.";
			link.l1.go = "WildRose_Tichingitu_Final_4";
		break;

		case "WildRose_Tichingitu_Final_4":
			dialog.text = npchar.name+" Entendi, Capitão "+pchar.name+". Tichingitu vai fazer tudo.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Дюран
		case "WildRose_Duran_Final_1":   
			dialog.text = "Caras duros... Mas a gente foi mais esperta, sabe? Ha-ha! Deixa eles apodrecerem aqui e pensarem duas vezes antes de mexer com a gente de novo.";
			link.l1 = "Obrigada, "+npchar.name+", você fez um ótimo trabalho. Só de pensar no que poderia ter acontecido com a Mary... ou comigo... se eu não tivesse mandado você pra nos proteger, me dá até um arrepio...";
			link.l1.go = "WildRose_Duran_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Duran_Final_2":
			dialog.text = "Ha, Capitão, você teria dado um jeito — eu te conheço. Viu aquela lâmina enorme que o chefe deles tinha? Eu não conseguia tirar os olhos dela. Se não gostar dela, não vou ficar chateada se quiser me dar de presente, sabe?";
			link.l1 = "Hm... Vamos ver, né, vamos ver. Por enquanto, reúna os sobreviventes e vá para o navio. Traga os que caíram a bordo — vamos entregá-los ao mar. E... aquele líder — ele era o pai da Mary. Leve o Alonso e enterre-o direito, conforme a tradição protestante, em algum lugar por aqui. Ninguém deve saber onde fica o túmulo. Principalmente a Mary. Ela não precisa desse tipo de dor.";
			link.l1.go = "WildRose_Duran_Final_3";
		break;

		case "WildRose_Duran_Final_3":
			dialog.text = "Pode deixar, capitão. Espera... Pensando bem... deixa pra lá. Eu vou.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Тонзаг
		case "WildRose_Tonzag_Final_1": 
			dialog.text = "Tá quente pra caramba aqui fora, Cap’n. Aqueles desgraçados tiveram o que mereciam. Viu a cara daquele fedelho quando a gente apareceu, sabe?";
			link.l1 = "Ele claramente não esperava por isso. Assim como eu e a Mary não imaginávamos que ele fosse um canalha desses. Mesmo assim, minha intuição não falhou quando decidi cobrir nossa retaguarda.";
			link.l1.go = "WildRose_Tonzag_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tonzag_Final_2":
			dialog.text = "Você não é novo no Caribe, capitão. Já deve ter se acostumado com o tipo de gente que anda por aqui, e aprendeu a sentir o cheiro de encrenca de longe. E agora? Vamos voltar pro navio?";
			link.l1 = "Reúnam os feridos, recolham os mortos e embarquem todos. Os que perdemos — vamos entregá-los ao mar, como verdadeiros filhos do oceano. Eu e a Mary vamos ficar aqui por um tempo — precisamos de um momento a sós. Mais uma coisa: enterrem o pai da Mary conforme o costume protestante. Levem o Alonso com vocês, se for preciso. Só façam questão de que ninguém saiba onde foi o enterro. Principalmente a Mary. Não quero que ela seja assombrada pelas lembranças.";
			link.l1.go = "WildRose_Tonzag_Final_3";
		break;

		case "WildRose_Tonzag_Final_3":
			dialog.text = "Você tem razão. Não faz sentido ela voltar aqui só pra chorar. Fica tranquilo — a gente vai fazer tudo direito, e ninguém vai ficar sabendo de nada.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Айронс
		case "WildRose_Irons_Final_1":
			dialog.text = "Capitão, senhor, apresentando-me: emboscada bem-sucedida, canalhas eliminados, capitão em segurança.";
			link.l1 = "Agora não é hora pra sarcasmo, e se está tentando ser engraçado — péssima ideia. Você não quer acabar esfregando o convés na frente da tripulação, né? Ah, eles iam adorar isso... Eu sugiro que não teste a minha paciência. Hoje não.";
			link.l1.go = "WildRose_Irons_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Irons_Final_2":
			dialog.text = "Ah... bem, eu *sou* uma oficial, sabe, e...";
			link.l1 = "Por enquanto. Hoje um oficial — amanhã um marinheiro, e depois de amanhã — um mendigo.";
			link.l1.go = "WildRose_Irons_Final_3";
		break;

		case "WildRose_Irons_Final_3":
			dialog.text = "Entendi: "+GetFullName(pchar)+" é o Capitão Sério. Chega de piadas. Ordens, senhor?";
			link.l1 = "Recolham os feridos e levem todos a bordo. Diga ao Alonso para reunir uma equipe e recuperar os corpos dos nossos homens — vamos entregá-los ao mar. E peça pra ele enterrar o pai da Mary conforme as tradições protestantes. Só ele e quem ajudar devem saber onde é o túmulo. A Mary não precisa saber. Não quero que ela fique atormentada pelas lembranças.";
			link.l1.go = "WildRose_Irons_Final_4";
		break;

		case "WildRose_Irons_Final_4":
			dialog.text = "Sabe, sabe... Pode deixar. E não se preocupa — eu sei guardar segredo.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Лонгвэй
		case "WildRose_Longway_Final_1":
			dialog.text = "Capitão, senhor, conseguimos. Nenhum desgraçado escapou.";
			link.l1 = "Mandou bem, "+npchar.name+", obrigada. Eu sabia que podia contar com você. Reúna todos os sobreviventes e volte para o navio. A Mary e eu vamos ficar em terra mais um pouco.";
			link.l1.go = "WildRose_Longway_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Longway_Final_2":
			dialog.text = "O que a gente faz com os corpos dos mortos?";
			link.l1 = "Vamos entregá-los ao mar. Diga ao Alonso para cuidar dos preparativos. E mais uma coisa: peça para ele enterrar o pai da Mary conforme os costumes protestantes, em algum lugar aqui na mata, longe de olhares curiosos. Ninguém pode saber onde fica o túmulo — especialmente a Mary. Conhecendo ela, vai querer voltar aqui, e isso não vai fazer bem pra ela.";
			link.l1.go = "WildRose_Longway_Final_3";
		break;

		case "WildRose_Longway_Final_3":
			dialog.text = "Entendi. Mais alguma coisa, senhor?";
			link.l1 = "É só isso, meu amigo. Vai descansar e cuidar dos seus ferimentos.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Алонсо
		case "WildRose_Alonso_Final_1":
			dialog.text = "Que carnificina, hein... Tá bem, Capitão?";
			link.l1 = "Eu estou bem... tirando o fato de que a Mary e eu acabamos de matar o pai dela...";
			link.l1.go = "WildRose_Alonso_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_Final_2":
			dialog.text = "Pelo que parece, ele era um verdadeiro canalha...";
			link.l1 = "Acertou mesmo, "+npchar.name+". Ainda assim, ele merece um enterro digno — ritos protestantes. Quero que você cuide disso pessoalmente. Ninguém pode saber onde fica o túmulo. Principalmente a Mary.";
			link.l1.go = "WildRose_Alonso_Final_3";
		break;

		case "WildRose_Alonso_Final_3":
			dialog.text = "Você quer poupá-la das lembranças ruins?";
			link.l1 = "E sofrimento desnecessário. Mande todo mundo pro navio pra se recuperar. Traga os que caíram — vamos enterrá-los no mar quando eu e a Mary voltarmos. Agora, precisamos ficar a sós.";
			link.l1.go = "WildRose_Alonso_Final_4";
		break;

		case "WildRose_Alonso_Final_4":
			dialog.text = "Vou dizer pros caras te deixarem em paz.";
			link.l1 = "Obrigada, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
	}
}
