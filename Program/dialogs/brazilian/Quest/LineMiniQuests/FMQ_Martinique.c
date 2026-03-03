// Addon-2016 Jason, французские миниквесты (ФМК) Мартиника
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Um bug óbvio. Avise os desenvolvedores sobre isso.";
			link.l1 = "Oh, eu vou.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "carpenter":
			DelMapQuestMarkCity("Fortfrance");
			LAi_SetImmortal(npchar, false);
			npchar.lifeday = 0;
			DelLandQuestMark(npchar);
			dialog.text = TimeGreeting()+", capitão. Permita-me apresentar - "+GetFullName(npchar)+". Embora tenhamos nos conhecido há pouco tempo, duvido que você se lembre de mim.";
			link.l1 = "Saudações, monsieur. E onde será que já te vi antes?";
			link.l1.go = "carpenter_1";
		break;
		
		case "carpenter_1":
			sTemp = "lugger 'Adeline'";
			if (pchar.questTemp.Sharlie.Ship == "sloop") sTemp = "sloop 'Black Dog'";
			dialog.text = "Nosso estaleiro. Você fez uma compra "+sTemp+". Lembra agora? Eu sou carpinteiro lá.";
			link.l1 = "É, eu realmente comprei aquele navio. Então, o que você quer, monsieur "+GetFullName(npchar)+"?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
			sld = characterFromId("FortFrance_shipyarder");
			AddLandQuestMark(sld, "questmarkmain");
			dialog.text = "Nosso construtor naval "+GetFullName(sld)+" quer falar com você. Acho que ele tem uma proposta de negócio. Ele viu seu navio no nosso porto e me mandou te procurar. Aceitaria o convite, por favor?";
			link.l1 = "Tudo bem. Vou fazer uma visita ao seu chefe assim que terminar meus assuntos na cidade.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			pchar.questTemp.FMQM = "begin";
			AddQuestRecord("FMQ_Martinique", "1");
			SetFunctionTimerCondition("FMQM_Denial", 0, 0, 2, false);
		break;
		
		case "officer":
			PlaySound("Voice\English\soldier_arest_4.wav");
			dialog.text = "Ora, ora... Contrabandistas novatos na minha rede!";
			link.l1 = "É...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			dialog.text = "Chega de papo furado! Há vários barris de resina neste estaleiro. Capitão, você entregou tudo ao seu comparsa. Os dois estão presos e estou confiscando a carga em nome da lei!";
			link.l1 = "...";
			link.l1.go = "officer_2";
		break;
		
		case "officer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_3":
			dialog.text = "Não se faça de bobo, patrão! Que barris? Você sabe muito bem que estou falando dos barris que você descarregou agora há pouco do navio deste marinheiro! Vocês dois vão apodrecer nas masmorras! Andem logo, seus desgraçados...";
			link.l1 = "";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\soldier\soldier arest-02.wav");
			dialog.text = "Esta resina, meu caro mestre construtor naval, é um bem de valor estratégico que está sob o controle direto do nosso governador! Já que você insiste que ela é toda sua - então fique com ela. Você está preso, vai passar esta noite em nossas confortáveis masmorras e amanhã nos dará um relatório detalhado de como conseguiu isso e para que finalidade. Não se preocupe, vamos descobrir tudo eventualmente. Você, capitão, está livre para ir. Hoje é seu dia de sorte.";
			link.l1 = "";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("FMQM_officer"));
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "FortFrance_town", "officers", "reload5_3", "FMQM_ArestContinue", 8);
		break;
		
		case "officer_7":
			PlaySound("Voice\English\soldier_arest_2.wav");
			dialog.text = "Eu sabia que tinha algo errado com este navio... Parece que subestimei você, capitão.";
			link.l1 = "Exatamente, tenente. Não sou tão idiota assim. Sua parceria aconchegante com o construtor naval agora está comprometida.";
			link.l1.go = "officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "officer_8":
			dialog.text = "Entendi. Parabéns, você deve ser talentoso para ter conseguido me encontrar e ainda me pegar de surpresa. Agora me diga, o que você quer.";
			link.l1 = "Não está claro? Eu quero minha resina de volta. A resina que você e seu amigo roubaram de mim.";
			link.l1.go = "officer_9";
		break;
		
		case "officer_9":
			dialog.text = "Certo. Você pode ficar com isso, mas só metade do seu lote. É tudo o que tenho guardado aqui. Espero que seja suficiente pra você, porque é tudo o que posso oferecer.";
			link.l1 = "Você ainda está tentando me enganar? Compense a outra metade com ouro ou com as mercadorias escondidas aí atrás.";
			link.l1.go = "officer_10";
		break;
		
		case "officer_10":
			dialog.text = "Nem pensar. Peça a outra metade ao nosso amigo em comum.";
			link.l1 = "Você só pode estar de brincadeira comigo! Você realmente acredita nisso "+GetFullName(characterFromId("FortFrance_shipyarder"))+" vai me devolver meus barris? Isso é ridículo.";
			link.l1.go = "officer_11";
		break;
		
		case "officer_11":
			dialog.text = "Capitão, leve toda a resina que tenho, salve sua pele e suma daqui. Posso acrescentar a essa barganha minha promessa de não te causar problemas em St. Pierre. Essa é minha última oferta.";
			link.l1 = "Desde quando a minha vida faz parte do acordo? Ha!";
			link.l1.go = "officer_12";
		break;
		
		case "officer_12":
			dialog.text = "Looks like you still consider yourself invincible after the fight, captain. Let me explain this to you: those were rookies, untrained and unmotivated; you have no chance against my squad. I could have you killed right here without any bargaining, but I value the lives of my men. Some of them might get injured or even killed in the process of killing you. So you either accept my generous offer or stay here forever. Time to choose.";
			link.l1 = "Dane-se, tenente, mas sou obrigado a aceitar seus termos. Aqui estou em grande desvantagem.";
			link.l1.go = "officer_13";
			link.l2 = "Confiante demais, tenente? Acho que devo ensinar uma lição a você e seus mercenários. Seu maldito vira-lata de resina!";
			link.l2.go = "officer_15";
		break;
		
		case "officer_13":
			dialog.text = "Você é um homem sensato, capitão. Pegue seus barris e suma daqui. Vou te avisar, me acusar na frente do governador não vai adiantar nada. Hoje mesmo vou mudar o esconderijo do meu estoque. Não perca seu tempo.";
			link.l1 = "Não ia fazer isso. Eu entendo como é inútil procurar as autoridades.";
			link.l1.go = "officer_14";
		break;
		
		case "officer_14":
			dialog.text = "Rápido, não tenho muito tempo para perder.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_PeaceExit");
		break;
		
		case "officer_15":
			DialogExit();
			AddDialogExitQuestFunction("FMQM_BattleExit");
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_02.wav");
			dialog.text = "Oh! Que encontro! Saudações, monsieur! Está aproveitando a noite?";
			link.l1 = "Boa noite... ah, é você! Eu me lembro de você, nos conhecemos no meu primeiro dia aqui no Caribe. Monsieur Gregoire Valinnie.";
			link.l1.go = "greguar_1";
		break;
		
		case "greguar_1":
			dialog.text = "Que bom que ainda se lembra. Vejo que agora você é capitão. Capitão "+GetFullName(pchar)+". Parabéns.";
			link.l1 = "Obrigado...";
			link.l1.go = "greguar_2";
		break;
		
		case "greguar_2":
			dialog.text = "Você parece preocupado, capitão. O que aconteceu aqui? Tem algo errado?";
			link.l1 = "Tem algo errado...";
			link.l1.go = "greguar_3";
		break;
		
		case "greguar_3":
			dialog.text = "Monsieur, ao invés de ficar parado no meio da rua, vamos para uma taverna. Você está precisando de uma caneca ou duas. Podemos conversar lá. Vamos!";
			link.l1 = "...";
			link.l1.go = "greguar_4";
		break;
		
		case "greguar_4":
			DialogExit();
			NextDiag.CurrentNode = "greguar_5"; 
			FreeSitLocator("Fortfrance_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Fortfrance_tavern", "sit", "sit_front4", "FMQM_InTavern", -1);
		break;
		
		case "greguar_5":
			LAi_SetSitType(Pchar);
			dialog.text = "Pode servir, capitão...";
			link.l1 = "Vai em frente...";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,20);
			RecalculateJumpTable();
			dialog.text = "Ufa... Agora me diz, o que aconteceu? Você está com a mesma cara daquele sujeito que enforcaram semana passada. Ele tinha exatamente esse olhar quando subiu no cadafalso.";
			link.l1 = "Veja, monsieur Gregoire... Digamos apenas que estou com problemas no trabalho.";
			link.l1.go = "greguar_7";
		break;
		
		case "greguar_7":
			dialog.text = "Capitão, você pode contar tudo pra mim. Não vou te entregar pro governador ou pro comandante, pode confiar em mim. Você não confia em mim?";
			link.l1 = "Confio em você, monsieur.";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			dialog.text = "Então confesse e alivie sua alma. Talvez eu possa te ajudar.";
			link.l1 = "Um construtor naval local me contratou para saquear uma caravana espanhola que saiu de Trinidad. Ele precisava muito de resina, esse era meu alvo, e prometeu pagar quinze dobrões por barril. Eu rastreei a caravana, saqueei e trouxe a mercadoria pra cá. Colocaram meu navio para conserto e descarregaram os barris no estaleiro. Estávamos prestes a fechar o negócio quando aquele oficial apareceu... Como será que ele ficou sabendo?";
			link.l1.go = "greguar_9";
		break;
		
		case "greguar_9":
			dialog.text = "";
			link.l1 = "Foi isso, eles nos pegaram. Acho que devo dar crédito ao construtor naval – ele assumiu toda a culpa, disse que a resina era dele e que eu não tinha nada a ver com aquilo. No fim, ele foi preso e meu dinheiro sumiu. Toda aquela confusão com a caravana espanhola foi perda de tempo e dinheiro, embora eu tenha tido sorte de não acabar na cadeia. Sirva mais uma, monsieur Gregoire.";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			dialog.text = "Então, o construtor naval está preso?";
			link.l1 = "Bem, sim. Ele foi levado para a prisão justamente pelo oficial de quem eu estava falando. Você devia ter visto os dois.";
			link.l1.go = "greguar_11";
		break;
		
		case "greguar_11":
			dialog.text = "Sim, eu vi os dois, embora eu não fizesse ideia de que o tenente Felicien Gronier pudesse mesmo prender um velho amigo.";
			link.l1 = "O q... o que você acabou de dizer?";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "Você ouviu direito. O tenente Felicien Gronier e o construtor naval "+GetFullName(characterFromId("FortFrance_shipyarder"))+" são velhos amigos. Eles serviram juntos no exército na Europa. Gronier continuou na vida militar e "+GetFullName(characterFromId("FortFrance_shipyarder"))+" conseguiu abrir o próprio negócio.";
			link.l1 = "Então eles se conhecem... Agora entendi...";
			link.l1.go = "greguar_13";
		break;
		
		case "greguar_13":
			dialog.text = "Meu querido "+pchar.name+", parece que você foi enganado. Você ainda é novo por aqui e eles se aproveitaram disso. Aposto cem dobrões que o monsieur "+GetFullName(characterFromId("FortFrance_shipyarder"))+" vai estar andando pelo estaleiro dele de novo em três dias ou menos.";
			link.l1 = "Parece que você está certo, monsieur. Eles me ferraram. Não tinha como aquele oficial saber da resina. E a hora foi perfeita também.";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			dialog.text = "Isso aqui é o Caribe, monsieur "+pchar.name+"  Acostume-se com isso. Esqueça as aparências, a pior escória daqui sempre parece um nobre respeitável.";
			link.l1 = "Já ouvi essa conversa em algum lugar antes... O que eu faço com eles? Devo avisar o governador?";
			link.l1.go = "greguar_15";
		break;
		
		case "greguar_15":
			dialog.text = "Receio que, neste caso "+GetFullName(characterFromId("FortFrance_shipyarder"))+" vou contar outra história para eles e você vai acabar na prisão.";
			link.l1 = "É claro. Muito bem, então! Já que a lei não está do meu lado, vou fazer do meu jeito, droga! Não vou desistir assim tão fácil.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			dialog.text = "Por favor, se acalme "+pchar.name+". É a raiva e o rum falando, não você. Vai dormir um pouco e depois pensa nisso de novo. Talvez seja melhor você deixar pra lá. Tenente Felicien Gronier e "+GetFullName(characterFromId("FortFrance_shipyarder"))+" Tem gente poderosa aqui, eles estão muito acima do seu nível. Não faça nenhuma besteira.";
			link.l1 = "Vamos ver. Obrigado por me esclarecer. Ainda bem que te conheci.";
			link.l1.go = "greguar_17";
		break;
		
		case "greguar_17":
			dialog.text = "Tome cuidado. Lembre-se do que eu te falei.";
			link.l1 = "Eu vou. Agora vamos tomar mais uma antes de ir!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_OutTavern");
		break;
		
		case "greguar_18":
			PlaySound("Voice\English\LE\Greguar\Greguar_03.wav");
			dialog.text = "Capitão "+GetFullName(pchar)+"!";
			link.l1 = "Oh, monsieur Gregoire! Você de novo!";
			link.l1.go = "greguar_19";
		break;
		
		case "greguar_19":
			dialog.text = "Yes. After our tavern talk, I made inquiries regarding Lieutenant Felicien Gronier. It turns out that he requested a ten-day leave not long ago. His petition was approved. I saw him today; he took a longboat to a tartane which soon sailed to Guadeloupe. She's called the Topaz. I've told you everything; it's your call now. I'm sure you can see the pattern in Gronier's sudden request for leave and his departure from the island on a newly built tartane.";
			link.l1 = "Agora está mais do que claro pra mim, com certeza! Essa tartana está com minha resina guardada no porão de carga! Monsieur Gregoire, obrigado, você realmente me ajudou! Tem algo que eu possa fazer por você em troca?";
			link.l1.go = "greguar_20";
		break;
		
		case "greguar_20":
			dialog.text = "Ah, vamos lá, meu amigo. Somos nobres, devemos ajudar uns aos outros. É assim que vivemos. Tenho certeza de que você faria o mesmo se estivesse no meu lugar. Não perca tempo, navegue para o norte e encontre o oficial. Não entre em combate, apenas siga-o e descubra o que ele está tramando. Depressa, capitão!";
			link.l1 = "Muito obrigado de novo!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_HurryToSea");
		break;
		
		case "pirate":
			dialog.text = "O que você está olhando? O que quer aqui?";
			link.l1 = "Ei, camarada, vim buscar minha mercadoria. Tá vendo aqueles barris ali? Aquela é a minha resina, e não me pagaram um tostão por ela.";
			link.l1.go = "pirate_1";
			DelLandQuestMark(characterFromId("FMQM_Enemy_crew_2"));
		break;
		
		case "pirate_1":
			dialog.text = "Você é idiota ou o quê? Cai fora enquanto ainda dá tempo!";
			link.l1 = "Eu me esforcei demais para conseguir essa resina para deixar uns canalhas imundos me impedirem.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "Vamos enterrar seu terninho chique bem aqui!";
			link.l1 = "Ah, que gentil da sua parte sugerir um enterro, mas receio que vamos ter que te deixar aqui na praia mesmo, para as gaivotas comerem suas tripas!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_ShoreFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
