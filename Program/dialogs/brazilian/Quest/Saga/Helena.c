// Элен МакАртур - сомнительная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "O que foi?";
			link.l1 = "Não, não é nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "After_boarding":
			dialog.text = "Obrigada pela ajuda, capitão!";
			link.l1 = "Meu Deus... Você é ainda mais lindo do que eu imaginei!";
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = "Que se dane a minha beleza! Você faz ideia do quanto de sofrimento ela já me trouxe? Eu cortaria o próprio nariz se isso não acabasse com a minha reputação. Aquele desgraçado não queria me deixar sair viva da corveta, ficava repetindo que eu 'sabia demais'. Ontem mesmo disse que estava cansado de esperar e que ia me tomar à força\nVocê chegou na hora exata! Mas onde estão meus modos, meu nome é Helen McArthur. Meu pai costumava me chamar de Rumba porque eu vivia quebrando, sem querer, as porcelanas finas que ele tinha 'adquirido', então é assim que minha tripulação me chama agora.";
			link.l1 = "Meu nome é "+GetFullName(pchar)+" e estou aqui para te resgatar. Passei vários dias vasculhando o Caribe, procurando por você a pedido da dona Gladys.";
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = "Dona Gladys!? Como ela está?";
			link.l1 = "Estava morrendo de preocupação com você. Mas logo vai vê-la, estamos navegando para Blueweld. Pode me contar tudo o que aconteceu com você no caminho.";
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = "Para ser sincera, "+pchar.name+", eu adoraria comer alguma coisa e tirar um cochilo agora. Estou exausta depois de todos esses dias naquele navio do monstro...";
			link.l1 = "Claro, Sra. McArthur. Vou pedir ao mordomo que lhe sirva uma refeição e prepare uma cama para você em seus aposentos privados.";
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = "Capitão de Maure, agradeço de coração pelo seu resgate na hora certa. Você precisa me visitar, junto com minha mãe. Nossa casa não fica longe daqui, está à sua esquerda quando vier do cais. E saiba disso "+pchar.name+", eu nunca vou te perdoar se você partir sem se despedir!";
			link.l1 = "O prazer foi todo meu, Srta. McArthur. Farei questão de procurá-la!";
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // открыть кабинет Свенсона
			pchar.questTemp.Saga = "svenson";//идем к Свенсону
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			// закрыть город до беседы с Глэдис
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = "Ah, aí está você, Capitão de Maure! Que bom que veio, tenho tantas perguntas para lhe fazer.";
			link.l1 = "Me desculpe, Sra. McArthur, mas precisamos adiar nossa conversa por um tempo. Preciso reunir mais informações antes de poder lhe dar respostas satisfatórias. Por enquanto, peço que não apareça na rua. Espero que sua espera não seja longa. Confie em mim e aguarde.";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CanDrink")) {
				link.l1.go = "drinking_refuse";
				link.l2 = "Você mesma disse que não me perdoaria se eu não aparecesse.";
				link.l2.go = "drinking_accept";
				
				DeleteQuestCondition("HelenDrinking_NoVisit");
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CanDrink");
			} else {
				link.l1.go = "exit";
				NextDiag.TempNode = "Helena_wait";
			}
		break;
		
		case "Helena_hire":
			dialog.text = "Ah, aí está você, meu capitão! Seus olhos dizem que você tem novidades para mim!";
			link.l1 = "O Capitão Svenson me disse que você quer navegar comigo. Agradeço seu interesse, e a dona Gladys comentou que você sentia falta do mar. Seja bem-vinda a bordo, Srta. Helen McArthur!";
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = "O Capitão Svenson me disse que você quer navegar comigo. Fico grata pelo seu interesse, e a Sra. Gladys comentou que você sente falta do mar. Bem-vinda à minha tripulação, Sra. Helen Sharp!";
				link.l2.go = "Helena_hire_2";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 2;
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			dialog.text = "Sim, sim, capitão! Odeio ter que dizer isso, senhor, mas eu sei me defender e não vou tolerar homem passando dos limites. Não me responsabilizo por mãos decepadas ou olhos arrancados.";
			link.l1 = "Não se preocupe, tenho uma disciplina inabalável no meu navio. Mas preciso te perguntar uma coisa...";
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = "...Sim?";
			link.l1 = "Jan Svenson e eu descobrimos que você é a verdadeira herdeira de Isla Tesoro. Sim, é verdade, não balance a cabeça! Eu tenho metade do mapa que comprova seu direito. Não vai ser fácil, mas Jan e eu vamos fazer o possível para te ajudar a se tornar a legítima dona.";
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = ""+pchar.name+", você está falando sério? Não é gentil brincar assim com uma pobre garota! Como eu poderia ter o direito de possuir uma ilha inteira?!";
			link.l1 = "Estou falando muito sério, Srta. McArthur. E vou ajudá-la a recuperar o que é seu por direito. Vamos zarpar agora!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = "O-o que você disse? Helen Sharp? Por que Sharp?";
			link.l1 = "Helen, você é filha de Beatrice Sharp e a única herdeira da dinastia Sharp. Esta é metade do mapa que ficou guardada com a dona Gladys todos esses anos. É a prova do seu direito sobre Isla Tesoro. Não vai ser fácil, mas Jan Svenson e eu vamos fazer de tudo para te ajudar a herdar a ilha do seu avô.";
			link.l1.go = "Helena_hire_3";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
			Notification_Approve(true, "Helena");
			npchar.lastname = "Sharp";
		break;
		
		case "Helena_hire_3":
			dialog.text = "Oh... Minha pobre mãe! Eu queria tanto encontrar o túmulo dela um dia e rezar pela alma dela lá. Mas... espere! Impossível!";
			link.l1 = "O que foi, senhorita Sharp?";
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = "A profecia da cigana acabou de se cumprir... Agora eu finalmente entendi.";
			link.l1 = "Hã? Que profecia?";
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+pchar.name+", você pode me chamar de ingênua, mas vou te contar mesmo assim. Quando eu era menina, uma cigana me disse: 'Seu destino estará nas mãos do homem que não aceitará a moeda da viúva, que devolverá o ouro do morto e que pronunciará o nome da mãe.'\nNa época achei tudo uma bobagem, mas de alguma forma você conseguiu cumprir cada parte da profecia. Não tinha como você saber disso!";
			link.l1 = "Seu destino, você diz... Bem, talvez você esteja certa. Não vou te decepcionar. Vamos procurar o túmulo da sua mãe juntos. E por agora... Srta. Helen Sharp! Prepare-se para a partida e não se atrase!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = "Aos seus comandos, capitão!";
			link.l1 = "...";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			AddQuestUserData("Saga", "sTimer", AddDaysToDateString(367));
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2, false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				AddQuestRecord("HelenDrinking", "3");
				
				SetFunctionLocationCondition("HelenDrinking_IslaTesoroAmbush", "Pirates_town", false);
				sld = &locations[FindLocation("Pirates_town")];
				sld.locators_radius.quest.detector1 = 4.0;
			}
		break;
		
		//-->  консультации по морским сражениям в искушении барбазона
		case "sea_bomb":
			dialog.text = "Capitão "+pchar.name+"! Eu tive uma ideia...";
			link.l1 = ""+npchar.name+"? Não é seguro aqui, e eu te disse para ficar no navio...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = "Charles, tem tanta pólvora guardada nesse velho casco que, se explodir, a ilha inteira vai voar direto pra porta de São Pedro! Não faz diferença se você mandar eu me esconder ou não, então me escuta!";
			link.l1 = "Certo, fale logo!";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "A corveta e a fragata. Eles não reconhecem o navio do Knive como uma ameaça. Podemos usar essa confiança deles contra eles. Vamos pegar alguns barris de pólvora, preparar um pavio e navegar até os navios\nEles vão nos deixar chegar perto, acendemos o pavio, jogamos o barril em um deles e fugimos o mais rápido possível. E então vamos assistir a uma explosão espetacular... O que me diz?";
			link.l1 = "Um navio incendiário improvisado... muito astuto! Seu plano é tão louco que pode mesmo dar certo... se conseguirmos nos aproximar sem sermos reconhecidos.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "O que temos a perder "+pchar.name+"? Não vai ser fácil enfrentar dois navios ao mesmo tempo, mas vamos ter uma chance de equilibrar as coisas...";
			link.l1 = "Certo. Vamos acabar logo com isso! Rapazes! Peguem três barris de pólvora! Vamos dar o fora daqui! Adoro a sua criatividade, "+npchar.name+"... Eu mesma nunca teria pensado nisso.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = "O que foi, capitão?";
			link.l1 = "O navio do Jackman está na enseada de Sabo-Matila, o pesado navio de guerra 'Centurion'. Esse navio já pertenceu aos Hawkes, então deve haver itens e documentos importantes na cabine do Jackman... precisamos embarcar nele.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Falar é fácil. Como você pretende fazer isso com a nossa polaca? Eles têm mais homens e mais armas que a gente.";
			link.l1 = "Você tem razão. Jackman tem pelo menos o dobro de homens que nós, e todos são espadachins experientes. Seria loucura atacá-los sem antes bombardeá-los. Mas uma luta prolongada também não é a melhor opção. Então estive pensando no que fazer.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", ainda não nos reconheceram como inimigos, assim como aqueles idiotas lá em Turks... Podemos tentar nosso truque de novo...";
			link.l1 = "Helen, I have just told you that we have to board and search the frigate; blowing it to kingdom come is not an option.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Espere um minuto, "+pchar.name+", não vamos afundá-la. Vamos fazer diferente.  Escuta, vamos pegar alguns barris vazios de rum e enchê-los com pólvora, balins e estopilhas curtas. Depois, vamos nos aproximar da fragata deles e lançar os explosivos improvisados no convés.";
			link.l1 = "Ha! Sua engenhosidade feminina continua a me surpreender! Em vez de um navio incendiário, você sugere uma fougasse? Acha mesmo que pode funcionar?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "E por que não? O costado deles é mais alto que o nosso, mas dois ou três homens com uma roldana conseguem içar e lançar um barril cheio sem dificuldade. A gente grita: 'Aqui tem rum de graça do Knive!' E os barris explodem antes que eles possam reagir.";
			link.l1 = "A rajada de balins vai transformar os melhores homens dele no convés em carne moída... Droga, isso até que soa tentador.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Vamos jogar cinco barris de uma vez do tombadilho até a popa. "+pchar.name+", temos o elemento surpresa. Eles ainda não vão suspeitar de nada! E então vamos zarpar imediatamente antes que tenham chance de nos abordar.";
			link.l1 = "Bem, vamos tentar. Eles não podem nos identificar antes de colocarmos aqueles barris explosivos no convés deles... Não vai ser fácil chegar perto. Jackman não é tão tolo quanto o Ghoul era.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Vamos arriscar, "+pchar.name+"! Como eu disse antes, o que temos a perder?";
			link.l1 = "Bem lembrado... Fiquem atentos, rapazes! Preparem as fougasses e se aprontem para lutar!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//<--  консультации по морским сражениям
		
	// --> разговор по итогам Саги
		case "result":
			//if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // не друзья
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 11) {
				Achievment_Set("ach_CL_83");
			}
			
			if (sti(pchar.questTemp.Saga.HelenRelation) < 6)
			{
				dialog.text = "Bem, meu querido capitão... Chegou a hora de nos despedirmos. Meu serviço terminou, e agora preciso me acostumar a ser a Rainha Pirata de Isla Tesoro. Espero ser uma sucessora digna do meu tio. Obrigada pela sua ajuda.";
				link.l1 = "É uma pena ter que me despedir de você, mas assim são os caprichos do destino. Agora você tem responsabilidades muito mais importantes do que servir no meu navio.";
				link.l1.go = "result_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Mary")) {
					dialog.text = "Eu adoraria poder ficar no seu navio. Perto de você... Mas é impossível. Seja feliz, Charles. E tomara que ela realmente mereça você!";
					link.l1 = "Me desculpe, Helen.";
					link.l1.go = "result_mary";
				} else {
					dialog.text = "É tão estranho, "+pchar.name+"! Acabei de me tornar dona de uma ilha inteira, mas não me sinto a Rainha de Isla Tesoro... Acho que o novo líder da Irmandade vai administrar a colônia melhor do que eu conseguiria. Ainda tenho muito o que aprender.";
					link.l1 = "Não se preocupe com isso, Helen, você é uma mulher que sabe se cuidar – exatamente como me disse quando subiu a bordo pela primeira vez.";
					link.l1.go = "result_9";
				}
			}
			
			DeleteQuestCondition("HelenDrinking_AtSHDN");
			DeleteQuestCondition("HelenDrinking_InBlueweldAfterCave");
		break;
		
		case "result_mary":
			dialog.text = "Bem, ainda seremos amigos, não é?";
			link.l1 = "Claro... Helen, nós vamos nos encontrar de novo em Isla Tesoro. Quer que eu te leve até sua ilha?";
			link.l1.go = "result_12";
		break;
		
		case "result_1":
			dialog.text = "Você tem razão... Olha, eu guardei minha parte do saque enquanto navegava no seu navio. Pegue, e nem pense em recusar minha oferta – não quero ficar te devendo.";
			link.l1 = "Ei, espere um instante...";
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = "Eu sei o que você vai dizer. Claro, sua ajuda foi muito mais valiosa do que esse baúzinho de tesouros. Mas é tudo o que tenho comigo agora e preciso te retribuir. Aceite, se você não aceitar, vou deixar no seu camarote.";
			link.l1 = "Vai navegar sozinho agora? Talvez eu possa te levar até Isla Tesoro?";
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			Log_Info("You have received a chest with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Não precisa disso, "+pchar.name+". Eu vou chegar à ilha sozinha. Estou com minha espada e pistola, isso basta por enquanto... Tenho certeza de que a Rainha de Isla Tesoro não vai precisar se preocupar com dinheiro quando eu chegar lá.";
			link.l1 = "Pois bem, Vossa Majestade. Desejo sorte na sua nova vida.";
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = "Chega disso, mesmo de brincadeira. Ainda sou a Helen pra você. Mas não era só isso que eu queria dizer. Encontrei meu pai de novo, embora tenha sido meio estranho. Ele pagou pela minha herança com o bom nome dele como nobre inglês, e isso me incomoda. O Commonwealth inglês está caçando ele e eu não quero você, "+pchar.name+", para fazer parte disso.";
			link.l1 = "Caia em si, Helen! Ele é um bandido e um pirata!";
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = "Pirata? E quem diabos é você pra dizer uma coisa dessas? Ele é meu pai e é isso que importa pra mim! E eu, filha de um bandido e de um pirata, não dou a mínima pro que a justiça inglesa pensa dele. Se você tentar fazer mal ao meu pai de qualquer forma, eu vou esquecer tudo de bom que você já fez por mim, saiba disso. Considere isso um aviso.";
			link.l1 = "É mesmo? Olha, mocinha, era melhor você ser mais educada. Não ouvi nenhuma reclamação sua sobre meu jeito de pirata quando salvei sua pele bonita das mãos daquele canalha do Donovan, ou quando a gente dividiu o lucro das nossas capturas!";
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = "Eu... me desculpe. Retiro o que disse, me perdoe. Perdi a cabeça... Mas ainda assim, gostaria de continuar sendo sua amiga, o que seria impossível se você começar a perseguir meu pai.";
			link.l1 = "Entendido. Mas nunca ouse me ameaçar, mulher. Você já deveria saber, depois de navegar no meu navio, que não temo ninguém, nem nada. E muito menos vou tolerar falta de respeito de uma mulher – seja Rainha dos Piratas ou não. Posso ser um cavalheiro, mas até a minha paciência tem limites. Agora que isso está resolvido, adeus. Te desejo sorte.";
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = "Obrigada... Talvez a gente se encontre de novo, "+pchar.name+"...";
			link.l1 = "E por que não? Vou visitar Isla Tesoro mais de uma vez no futuro. Te vejo lá... Adeus, Helen.";
			link.l1.go = "result_8";
		break;
		
		case "result_8": // Элен уходит, но её не затираем
			DialogExit();
			RemovePassenger(pchar, npchar);
			//chrDisableReloadToLocation = true;//закрыть локацию  // уже не надо.
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto24", "", "", "", "", 7);//OpenTheDoors лесник . чтобы бежала и исчезла а не стояла.
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться		
			if (CheckAttribute(pchar, "questTemp.LSC.MaryWait")) {
				pchar.questTemp.LSC.Mary = "return";
			}
		break;
		
		case "result_9": // вот тут - ключевой момент, если игрок нашёл Мэри - выбирай, какая девушка милее
			dialog.text = "Tenho certeza. "+pchar.name+", eu gostaria de ficar no seu navio, se você permitir. Ficar com você...";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "(choose Mary) You don't understand, Helen. Your whole future is ahead of you and there is nothing for you to worry about. All I have ahead of me is war, political intrigue and total uncertainty. You must build a life of your own; there is no room in it for a wild rover like me.";
				link.l1.go = "result_10";
				link.l2 = "(escolher Helen) É mais do que eu poderia ter esperado, Helen. Claro que não quero te perder, mas seria melhor para você ir para Isla Tesoro. Quem sabe onde meu destino ainda vai me levar. Agora, tenho guerra, intrigas políticas e incerteza pela frente.";
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = "É mais do que eu poderia esperar, Helen. Claro que não quero te perder, mas seria melhor para você ir para Isla Tesoro. Quem sabe onde o meu destino ainda vai me levar. Agora, tenho uma guerra, intrigas políticas e um futuro incerto pela frente.";
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+pchar.name+"! Não minta para mim. Você só não quer... Me diga, quem é ela? É aquela vadia ruiva da Cidade dos Navios Abandonados, não é?";
			link.l1 = "Helen! Estou tentando te dizer o que acho melhor pra você! Como você não entende isso?!";
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = "Ah, claro, é óbvio que você é... E como foi que ela conseguiu te encantar, hein? O que ela tem que *eu* não tenho?! Ela é realmente tão boa assim? É, "+pchar.name+"... Bem, é a sua decisão, não me resta nada além de voltar para a minha ilha. Não posso ficar entre vocês dois\nObrigada por tudo que fez por mim, Charles. Você é o melhor homem que já conheci. Espero que possamos continuar amigos?";
			link.l1 = "Claro... Helen, eu vou te ver de novo na Isla Tesoro. Quer que eu te leve até lá?";
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = "Não precisa. Eu vou comprar um novo navio. Economizei dinheiro suficiente para comprar e equipar uma escuna enquanto servia sob seu comando. Vou velejar um novo 'Arco-Íris' de novo.";
			link.l1 = "Fico feliz, Helen, que você tenha sido tão... cuidadosa. Mas velejar em uma escuna não combina com a Rainha Pirata de Isla Tesoro. Em breve, você deveria ter sua própria fragata.";
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = "Talvez, "+pchar.name+". Tudo bem. Eu vou até o estaleiro, mas antes... me dá um beijo de despedida... Por favor...?";
			link.l1 = "Helen...";
			link.l1.go = "result_14";
		break;
		
		case "result_14": // прощальный поцелуй
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 0.5);
			pchar.questTemp.LSC.Mary = "return"; // к Мэри
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться
		break;
		
		case "result_15":
			dialog.text = "O meu destino está ligado ao seu desde o momento em que nos conhecemos. Você não entende isso? "+pchar.name+"? Eu te seguiria até o fim do mundo!";
			link.l1 = "E o seu pai? Laurence Beltrope? Ele é meu inimigo...";
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = "Meu pai é Sean McArthur. Eu o amava e lamentei sua morte. Ele era meu único pai. E aquele pirata... Eu nem quero falar sobre ele.";
			link.l1 = "Helen... Minha querida Helen!";
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+", eu sempre quis te dizer que você é o homem mais incrível que já conheci! Você fez tanto por mim que nunca vou conseguir retribuir. Quero ficar com você. Para sempre. Eu me casaria com você, se você quiser... Eu te amo.";
			link.l1 = "Vamos ficar juntos. Eu prometo!"; // а куда же ты теперь денешься :)
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) {
				link.l1.go = "result_17A";
			} else {
				link.l1.go = "result_18";
			}
		break;
		
		case "result_17A":
			dialog.text = "Promete que vai fazer uma coisa pra mim agora? E, por favor, não ria!";
			link.l1 = "Eu prometo, meu querido!";
			link.l1.go = "result_17A_1";
		break;
		
		case "result_17A_1":
			dialog.text = "Me chame pelo meu nome de verdade. Por favor!";
			link.l1 = "Eu te amo, Helen Sharp.";
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+pchar.name+", querido... Me abraça! Esperei por esse momento tempo demais!";
			link.l1 = "Helen, minha querida...";
			link.l1.go = "result_19";
		break;
		
		case "result_19": // романтик-сцена
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.																					   
			
			pchar.quest.HelenUpgradeShip.win_condition.l1 = "Timer";
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.day = GetAddingDataDay(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l2 = "location";
			pchar.quest.HelenUpgradeShip.win_condition.l2.location = "PortRoyal_town";
			pchar.quest.HelenUpgradeShip.function = "HelenUpgradeShip";
			
			// Квест Лонгвея "Путеводная звезда", начало 5 этапа
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap5_Start") && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
			{
				PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
				PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
				AddMapQuestMarkCity("Pirates", false);
			}
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! Isso foi... incrível! Não quero ir a lugar nenhum... Vamos ficar aqui até de manhã. O mundo pode esperar!";
			link.l1 = "Vamos deixar isso pra depois, Helen!";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // показатель, что Элен - наша навсегда
			npchar.SpecialRole = "fgirl";
			
			pchar.GenQuest.BrothelCount = 0;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
			
			// Выполнено требование для Дороже золота
			pchar.questTemp.GoldenGirl_Ready = true;
		break;
		
	// -------------------------------------------- провалы саги ------------------------------------
		case "failcenturion":
			dialog.text = "Capitão! Jackman está morto... Minha família finalmente está a salvo?";
			link.l1 = "Sim, Helen, vocês estão todos a salvo. Mas o 'Centurion' afundou, junto com todos os documentos que poderiam nos ajudar a encontrar o túmulo da sua mãe e provar seu direito sobre Isla Tesoro... Eh... Agora vou ter que invadir Tortuga sozinho...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = ""+pchar.name+", não se preocupe tanto. Não há nada que possamos fazer quanto a isso. E não se preocupe comigo também, vou ficar bem sem aquela ilha. Obrigada por tudo o que fez por mim!";
			link.l1 = "Parece que você vai... me deixar, não é?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Sim, meu capitão. Consegui juntar dinheiro suficiente para comprar e equipar uma escuna. Vou velejar no meu 'Arco-Íris' de novo. Vamos nos encontrar novamente em Blueweld... Estou voltando para casa.";
			link.l1 = "Bem... boa sorte, Helen!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // к Мэри
			}
		break;
		
		case "late_l1":
			dialog.text = "Bem, meu capitão... Parece que fracassamos. Adeus. Estou voltando para casa. Ganhei dinheiro suficiente sob seu comando para comprar uma nova escuna. Nos encontraremos de novo no mar!";
			link.l1 = "Boa sorte, Helen. Me desculpe por tudo. Adeus.";
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = "Capitão! Jackman está morto... Então minha família está a salvo, não está?";
			link.l1 = "Sim, Helen, está seguro. Mas não estou satisfeito, perdi tempo demais e Isla Tesoro agora é uma colônia inglesa. Você ficou sem sua herança, então vou ter que invadir Tortuga sozinho...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+", o que o advogado te disse?";
			link.l1 = "Perdi tempo demais e agora Isla Tesoro é uma colônia inglesa. Você ficou sem sua herança, então vou ter que invadir Tortuga sozinho... Infelizmente, perdemos.";
			link.l1.go = "failcenturion_1";
		break;
	// <-- провалы Саги
		
		// секс - Элен соглашается не всегда (голова болит, а что вы хотели? :)) и сама не требует секса
		case "cabin_sex":
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Não, querido, isso não vai dar certo.";
				link.l1 = "Ué, por que não?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0)// вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", hoje não estou me sentindo bem. Por favor, não fique chateado, não é culpa sua. Vamos deixar para outro dia...",""+pchar.name+", querido, estive tão cansada esses últimos dias. Para ser sincera, só quero dormir. Me perdoe. Vamos deixar para outra hora.");
				link.l1 = RandPhraseSimple("Tudo bem...","Tudo bem. Como quiser...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", o clima está perfeito, vamos!",""+pchar.name+", claro, sem perguntas! Vamos!");
				link.l1 = RandPhraseSimple("Essa é minha garota...","Você é tão encantadora, Helen...");
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			}
		break;
		
		case "sex_after":
			dialog.text = LinkRandPhrase(RandPhraseSimple("Foi maravilhoso, "+pchar.name+"!..","Você foi maravilhoso como sempre, querido..."),RandPhraseSimple("Foi maravilhoso, Charles!","Foi maravilhoso, querido!"),RandPhraseSimple("Nunca há um momento de tédio com você, meu capitão!","Você foi maravilhoso, querido!"));
			link.l1 = RandPhraseSimple("Eu te amo...","Sempre é bom estar com você, Helen...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//открыть локаци.
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", você sabe que sempre fico feliz em... Mas agora não é o momento certo – precisamos pegar aquele canalha do Thibaut antes que ele fuja.";
				link.l1 = "Você está certa como sempre, Helen...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Não, querido, isso não vai funcionar.";
				link.l1 = "Ué, por que não?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0) // вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", eu não estou me sentindo bem hoje. Por favor, não fique chateado. Vamos deixar para outro dia...",""+pchar.name+", querido, estou tão cansada nesses últimos dias. Para ser sincera, só quero dormir. Me perdoe. Vamos deixar para outra hora.");
				link.l1 = RandPhraseSimple("Tudo bem...","Tudo bem. Como quiser...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", eu te amo! Vamos!",""+pchar.name+", sim senhor, capitão! Vamos nessa!");
				link.l1 = RandPhraseSimple("Você é minha boa menina...","Você é linda, Helen...");
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
			pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;
			//npchar.quest.daily_sex_room = true; // для первого раза в таверне чтобы счетчик запустить . лесник
			//npchar.quest.daily_sex_cabin = true;
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			sld = CharacterFromID("Helena");
			ChangeCharacterAddressGroup(sld, loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest3");
			DoFunctionReloadToLocation(loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest4", "LoveSex_Room_Go");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Sim, "+pchar.name+"?","Sim, meu capitão?","Estou ouvindo. "+pchar.name+"...");
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining");
				dialog.text = "Olha isso, meu capitão!";
				link.l1 = "Que força, hein! Vejo que você não perdeu tempo, Helen.";
				link.l1.go = "cutlass_training";
				NextDiag.TempNode = "Helena_officer";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && sti(pchar.GenQuest.BrothelCount) > 0 && !CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Querido, sobre suas visitas a prostitutas.";
				npchar.quest.refusesex = true;
				link.l1 = "O quê? Helen, você entendeu tudo errado! Eu só...";
				link.l1.go = "brothel_found";
				NextDiag.TempNode = "Helena_officer";
				SetFunctionTimerCondition("Helena_ClearRefuseSex", 0, 0, 180, false);
				DeleteQuestCondition("Helen_GiveSex");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Helen, eu vou visitar a cidade perdida dos índios, Tayasal. Não vou mentir pra você: essa viagem é muito perigosa, e além disso... envolve teletransporte através do ídolo. Você vai... me acompanhar?";
				Link.l4.go = "tieyasal";
			}
       ////////////////////////казначей///////////////////////////////////////////////////////////
           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Helen, me faça um relatório completo sobre o navio.";
			    Link.l11.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
				Link.l12 = "Quero que você compre certos produtos toda vez que atracarmos.";
				Link.l12.go = "QMASTER_2";
			}
			
            /////////////////////////////////////казначей////////////////////////////////////////////////////////////     			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Cheguei conforme sua ordem, capitã.";
				Link.l2 = "Helen, preciso te dar algumas ordens.";
				Link.l2.go = "Companion_Tasks";
				
				sld = GetCharacter(sti(npchar.RealCompanionIdx));
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Rainbow") && sld.ship.type == pchar.questTemp.HelenDrinking.Rainbow && CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
					DeleteAttribute(link, "");
					dialog.text = "Você acha que isso é engraçado?";
					link.l1 = "Belo navio, não é? Consegui pra você, Helen! Pensa só, que tipo de homem no Caribe dá um navio de verdade pra sua dama, hein?";
					link.l1.go = "rainbow";
					
					NextDiag.TempNode = "Helena_officer";
					break;
				}
				
				NextDiag.TempNode = "Helena_officer";// не забыть менять в зависисомости от оффа
				break;
			}																															
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Helen, preciso do seu conselho.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Helen, tenho uma tarefa para você...";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Helen, vamos ficar juntos na cabine, só nós dois... por algumas horas? O que você acha?","Querido, que tal passarmos as próximas horas a sós? Gosta da ideia?");
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && sti(pchar.money) >= 10 && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Helen, por que não alugamos um quarto e passamos um tempo a sós... só nós dois por algumas horas? O que acha disso?","Meu bem, que tal passarmos as próximas horas a sós? Podemos alugar um quarto... o que acha?");
				Link.l2.go = "room_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "town" && sti(pchar.money) >= 1000 && GetNpcQuestPastDayWOInit(npchar, "special_sex_date") >= 30 && !CheckAttribute(npchar, "quest.refusesex"))
			{
				Link.l2 = "Helen, querida, posso te convidar para passar um tempo na taverna?";
				Link.l2.go = "special_sex";
			}
			if (CheckAttribute(pchar, "questTemp.MysteryPortRoyal_Helena")) {
				link.l4 = "Helen, parece que encontrei o testamento do seu admirador – Francis. Ele deixou a herança para você.";
				link.l4.go = "MysteryPortRoyal_Helena_1";
			}
			if (CheckCharacterItem(pchar, "pirate_cutlass") && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
				link.l4 = "Acho que este sabre agora é seu. Blaise é o seu chamado tio...";
				link.l4.go = "give_cutlass";
			}
			link.l9 = "Nada por agora, Helen.";
			NPChar.id = "Helena"; // лесник . Идентификация Элен на всяк. случай . если потеряет сознание.
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
		break;
		
		/////////////////////////// ответы для казнаячея - Элен ..(элен казначей - ужас!))///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, querido, você está doente ou algo assim? O quê, espera que eu desça, varra o porão e comece a contar os ratos?";
			Link.l1 = "Certo, desculpe querida, foi culpa minha...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "E eu quero meu próprio navio de linha, com cem canhões navegando a vinte nós. Fui capitã como você a vida toda. Vai procurar um intendente e enche o saco dele com isso.";
			link.l1 = "É, você tem razão, Helen. Desculpe por isso.";
			link.l1.go = "exit";
		break;
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Estou ouvindo.";
			Link.l1 = "Sobre nossa política de abordagem...";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Sobre o navio que você comanda...";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Nada até agora.";
			Link.l8.go = "exit";
			 
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Qual é o seu desejo, meu capitão?";
			Link.l1 = "Eu não quero que você aborde nada. Mantenha você e seus homens em segurança.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Quero que você aborde os navios inimigos na primeira oportunidade.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Sim, meu capitão?";
			Link.l1 = "Eu agradeceria se você evitasse trocar de navio depois de embarcar. Ela é valiosa demais para mim.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Se você acabar abordando alguém, dê uma boa olhada no navio capturado. Se ele valer a pena, fique à vontade para ficar com ele para você.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Tudo bem, vou pensar nisso.";
			Link.l1 = "Ela vai pensar nisso... Como se eu pudesse dar ordens pra ela mesmo.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Tudo bem, vou pensar nisso.";
			Link.l1 = "Ela vai pensar no assunto... Como se eu pudesse mesmo dar ordens pra ela.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Tudo bem, vou pensar nisso.";
			Link.l1 = "Ela vai pensar no assunto... Como se eu pudesse dar ordens pra ela mesmo.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Tá bom, vou pensar nisso.";
			Link.l1 = "Ela vai pensar no assunto... Como se eu pudesse dar ordens pra ela mesmo.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========//////////////////////////////////////																																			  
		
		case "stay_follow":
            dialog.Text = "Ordens?";
            Link.l1 = "Fique aqui!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Me siga e não fique para trás!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Mude o tipo de munição das suas armas de fogo.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Escolha o tipo de munição:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Já vou, capitão!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Já vou, Capitão!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "Aí está você! Finalmente te encontrei... Isso foi incrível, meu capitão! Nunca vi uma corrida pelos telhados e um salto de uma altura tão de tirar o fôlego! Meu coração quase saiu pela boca! Um dia desses você ainda me mata com essas suas loucuras, querido... Ah, você não está sozinho... Quem é essa moça?";
			link.l1 = "Esta é Catherine Fox, filha do Coronel Fox, comandante do famoso Regimento Marítimo de Infantaria Inglês, os 'Sea Foxes'. Estamos levando ela para Antígua.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "É mesmo... Bem-vinda a bordo, Srta. Fox! Não, não, não segure no braço do Capitão de Maure, você consegue andar muito bem sozinha! Agora vamos para o escaler – precisamos sair daqui."; 
			link.l1 = "Ha! Obrigado, Helen! O que eu faria sem você? Catherine, venha com a gente!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Finalmente, você acordou, querido! Como está se sentindo? Você quase me matou de susto...";
			link.l1 = "Helen, o que aconteceu? Minha cabeça está latejando...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Quando entramos na cabine do capitão, você estava caído no chão, imóvel. Meu coração quase parou! Os rapazes te levantaram e te arrastaram de volta para o nosso navio—bem a tempo, porque os mortos que estavam no convés começaram a se levantar de novo.   Que horror! Isso quase me faz querer acreditar em Deus! Eles eram completamente imunes às nossas lâminas e balas! Cortamos as cordas às pressas e tentamos zarpar, mas uma rajada do navio deles danificou gravemente o nosso e perdemos o controle. Depois, eles içaram as velas e sumiram num piscar de olhos.   Nosso navio encalhou, então tivemos que fugir para esta praia antes que a tempestade o destruísse. Muita gente boa morreu hoje, mas o navio sobreviveu no fim... se ao menos eu não tivesse dado a ordem de abandoná-lo...";
			link.l1 = "Não foi culpa sua, Helen. Você fez o certo. O que eu faria sem você?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Eu te arrastei para o barco e depois te levei até a praia. Você parecia morto, só o seu coração batia bem fraquinho. Olha! Minhas mãos ainda estão tremendo";
			link.l1 = "Obrigada, meu amor. Estou em dívida com você. Há quanto tempo estou deitada aqui?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Passei o dia inteiro cuidando dos seus ferimentos, limpando, fazendo curativos, te dando remédios e até um pouco de rum. Agora você precisa melhorar!";
			link.l1 = "Eu não vou morrer desta vez, querido. Mas não estou me sentindo bem... urgh....";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Me diga... Era mesmo o 'Holandês Voador', Charles? Por que eles nos atacaram? E por que não atiraram quando se aproximaram, mas tentaram nos afundar logo depois de embarcarem?";
			link.l1 = "O capitão deles precisava daquele amuleto, que eu havia discutido com Tuttuathapak, um xamã indígena. Por que eles precisavam dele, eu não sei... mas assim que o líder deles conseguiu o amuleto, eles se livraram de nós... Deus do céu, que pesadelo horrível! Um navio tripulado por mortos-vivos! É impossível de acreditar...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Pois é, agora foi a nossa vez de cruzar com o 'Holandês Voador'. Aff! Isso me dá arrepios! No próximo porto em que a gente parar, vou direto pra igreja, acender uma vela e rezar ao Nosso Senhor Jesus Cristo agradecendo por esse livramento milagroso. Olha, tô tão agradecida que até vou rezar pra uns santos católicos...";
			link.l1 = "Eu vou estar bem ao seu lado, Helen. Faz tempo que não me confesso de verdade... Mas antes, precisamos voltar àquela vila. Preciso contar tudo para Tuttuathapak. Aquele navio maldito nos atacou por causa do amuleto! Espero que aquele diabo de pele vermelha tenha alguma ideia de por que diabos esses mortos-vivos precisavam dele.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Certo. Mas precisamos ter cuidado – seus ferimentos mal cicatrizaram.";
			link.l1 = "Mas você vai me ajudar a melhorar mais rápido, não vai? Eu te amo, Helen...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = "Eu também te amo, meu querido...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+",   já te disse uma vez que agora nossos destinos estão ligados. O seu destino é o meu destino. Quando vamos partir?";
			link.l1 = "Fico muito feliz em ouvir isso. Te conto mais tarde, quando formos até lá. Precisamos nos preparar.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Estou pronta, meu capitão! Vou te seguir até os confins da Terra!";
			link.l1 = "Obrigada, meu amor...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// на Исла Тесоро
		case "islatesoro":
			dialog.text = "Oh, "+pchar.name+"! Que bom te ver! O que te traz aqui à Isla Tesoro?";
			link.l1 = "O mesmo de sempre – negócios. Só queria passar aqui e te ver também. Como vão as coisas, Helen?";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			dialog.text = "O que há com o nosso querido governador, Capitão? De quem vamos chutar o traseiro desta vez? Espanhóis, piratas ou alguém ainda pior?";
			link.l1 = "É pior, Helen, muito pior. O governador pretende visitar uma cortesã cara, e eu devo acompanhá-lo como uma espécie de atração. Ele prometeu à amante que levaria um autêntico corsário, aventureiro e, em geral, um lobo do mar. Ou seja, me espera uma conversa entediante, vinho caro demais e nobres sem graça.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Na verdade, é o contrário: um convite para um evento social agradável, organizado por uma dama. Sua Excelência me pegou de surpresa ao pedir que eu o acompanhasse, mas, para ser sincera, estou feliz por ter a chance de distrair um pouco a cabeça do trabalho, pelo menos por um tempo.";
			link.l2.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "Então... o temido Capitão Charles de Maure vai se fantasiar e dançar como um macaquinho de estimação só pra divertir essa gente? Que fofo! Tenho uma ideia melhor. Vamos zarpar e cair fora daqui. Se você estiver querendo umas férias merecidas faz tempo, vamos pra Isla Tesoro. Lá, a gente sempre é bem-vindo. Sol, areia branca, velhos amigos, ponche de rum, esquecer dos problemas – o que você quiser.";
			link.l1 = "Olha, tudo isso parece incrível, e eu adoraria... mas depois. Prometi ao governador, isso é importante para o velho e...";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "E daí? Você acha que seu sangue nobre vale alguma coisa pra eles? Eu posso não ser francesa, mas conheço muito bem essa tal 'alta sociedade', e pra eles, Charles de Maure não é um capitão em quem se confia a própria vida. Ele não é um cavalheiro como eles. Cavalheiros de verdade não vão pro mar lutar em meio à fumaça da pólvora. Charles de Maure é só uma curiosidade no banquete deles. Como um leopardo de estimação ou um negro de casa fantasiado! Um brinquedo de luxo! Desde quando você aceita ser tratado assim?!";
			link.l1 = "Helen, por favor, acalme-se. Tenho certeza de que posso lidar com alguns olhares desconfortáveis para satisfazer o governador e garantir nosso futuro. É bom ter amigos influentes. Afinal, isso vai ser mais fácil do que liderar um ataque de abordagem! E esses 'inúteis' nem sempre são assim. Até na alta sociedade há pessoas de valor... pelo menos, deveria haver.";
			link.l1.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "Tanto faz. (joga o cabelo) Mas fique avisado – de jeito nenhum eu vou me enfiar num vestido chique. Se você me obrigar a ir, vou de calças. Não tô nem aí se todas as senhoras finas do Caribe desmaiarem de desgosto.";
			link.l1 = "Eu não ia te obrigar. Não faz sentido nós dois sofrermos. Eu vou aguentar essa festa e depois vamos zarpar para Isla Tesoro. Para comemorar, guardei uma caixa de um excelente Madeira espanhol no porão...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "Oh ho ho, Charles! Está dizendo que eu não sou boa o bastante para uma companhia tão ilustre? Que uma garota de calças arruinaria sua noite? Que curioso. Muito bem, mas não esqueça de se vestir como um dândi. Macacos em roupas elegantes podem até conquistar o coração de uma cortesã. Aproveite o espetáculo!";
			link.l1 = "Helen, espera! Droga... mulheres!";
			link.l1.go = "GoldenGirl_8";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "É, a gente merece um descanso, com certeza. Mas que me condenem se eu for me enfiar num vestido chique pra isso. Até onde você acha que vai chegar a fofoca sobre sua mulher vestida de homem e de marinheira?";
			link.l1 = "Ah... Acho que isso não é uma boa ideia. Como posso dizer... esse não é o tipo de evento onde homens trazem suas esposas ou senhoras respeitáveis...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_6":
			dialog.text = "Ha! Prostitutas e devassidão! Que maravilha – então você vai a uma orgia! Por que não disse logo de uma vez? Você tem sorte de eu não ser uma ciumenta maluca e não te dar um tiro aí mesmo. Pelo menos, não agora.";
			link.l1 = "Helen, por favor, tudo o que estou fazendo é acompanhar o nosso governador, ele me pediu e foi bem insistente nisso. Não vai ter nenhuma maldita cortesã\nEspera, falei errado... Quero dizer, vai ter sim sexo com cortesãs... ah, droga! Eu só estou indo prestar meus respeitos!";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_7":
			dialog.text = "Eu sugiro que você se vista com elegância para 'prestar seus respeitos', Capitão de Maure. Afinal, é alta sociedade. É um escândalo aparecer lá sem colarinho e punhos. Mesmo que seja para uma orgia. Divirta-se.";
			link.l1 = "Helen, espera! Droga... mulheres!";
			link.l1.go = "GoldenGirl_9";
		break;
		
		case "GoldenGirl_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_9":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Algemas e uma coleira, Capitão. E talvez renda. Ouvi dizer que está na moda de novo. Mas o que eu sei!";
			link.l1 = "Ah, Helen, vamos lá!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Olha só! Meu querido capitão, voltando para casa depois da sua orgia!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "A nobreza local ainda aprova o seu novo macaquinho? Dizem que o espetáculo de ontem à noite foi lendário! Apostando navios e mulheres, desafiando príncipes de sangue azul para duelos? Você se importaria de me explicar que diabos está acontecendo com você?";
			link.l1 = "Helen, deixa eu explicar! Não é tão simples assim. Droga, me desculpa, mas eu nunca imaginei que teria que passar a noite na casa da Madame Botot. Eu só dormi lá, sim, sozinho, juro! E sim, ganhei uma fragata num jogo de cartas. Dá pra acreditar?";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Muito bem! Ou você é um grande mentiroso, um santo ou um tolo. Depois conversamos sobre as prostitutas e os navios que você ganhou – agora me conte tudo sobre o duelo e por que todo mundo está dizendo que você desafiou um príncipe herdeiro?";
			link.l1 = "Não sou um príncipe herdeiro, só um bastardo de conde. Ele é filho de um nobre muito influente, o Conde de Levi Vantadour. Olha, não fui eu que comecei! Foi ele quem me desafiou primeiro, e agora preciso vencer o duelo sem machucá-lo demais para não atrair a fúria do pai dele.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Ah, 'só o filho de um conde', é isso? Você tá falando sério agora, Charles?! E como é que a gente vai fazer isso? E se ele trapacear? Ele vai te matar!";
			link.l1 = "É por isso que Sua Excelência me deu segundos nobres. Só vou levar eles comigo – se algo der errado, pelo menos posso provar que tudo foi feito conforme o código do duelo e a lei. Peço que cuide da fragata enquanto eu estiver fora.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "Deixa eu ver se entendi direito... Você sumiu por um dia e uma noite inteiros e ganhou uma prostituta e uma fragata num jogo de cartas. E agora, vai duelar com um filho da nobreza que você não pode matar, enquanto *eu* fico aqui sentada esperando? Como é que eu deveria me sentir com tudo isso?!";
			link.l1 = "Helen, escute, você tem todo o direito de estar brava comigo e eu realmente sinto muito, mas é que...";
			link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "Sabe de uma coisa, já cansei disso. Vai lá e faz o que quiser! Eu vou só tirar o pó da sua cabine e lavar suas roupas sujas! Nem pense que está livre dessa. Vamos conversar sobre isso quando tudo acabar. Eu cuido da sua nova fragata, grande Capitão de Maure, pode ficar tranquilo. Ah, e Capitão de Maure, tenta não morrer... porque eu mesma estou planejando te matar depois. Agora, com licença, vou me trancar nos meus aposentos e tomar uma garrafa daquele bom madeira que encontrei na sua cabine.";
			link.l1 = "Helen, me deixa explicar! Droga... Lá vamos nós de novo!";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "Ouvi dizer que a última moda parisiense exige que os cavalheiros conquistem navios e cortesãs em jogos de cartas, em vez de comprá-los! Além disso, se quiser causar uma boa impressão, tem que desafiar os antigos donos para um duelo. Em que diabos você se meteu dessa vez?!";
			link.l1 = "Helen, não é tão simples assim. Droga, me desculpe, mas nunca pensei que teria que passar a noite na casa da Madame Botot! Ontem à noite virou uma batalha exaustiva e brutal de inteligência. E sim, ganhei uma maldita fragata no carteado. Dá pra acreditar?";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Que lindo. Isso quer dizer que você também ganhou uma cortesã? E a fragata que ganhou—o que apostou contra ela? Não foi o nosso navio, não é possível...";
			link.l1 = "Eu tive que fazer isso. Olha, agora não importa mais, no fim das contas eu venci. Meu oponente me desafiou para um duelo e me acusou de trapaça. Ele é o filho bastardo de um nobre extremamente influente, o Conde de Levi Vantadur. O que significa que vou ter que me esforçar ao máximo para não matá-lo ou feri-lo gravemente.";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Ele faria o mesmo? Você ficou louco, Charles? Arriscar seu navio, arriscar sua vida, por outra mulher?! Ela realmente vale tudo isso? Eu não significo nada pra você?!";
			link.l1 = "Helen, não há motivo para ciúmes, eu juro. Simplesmente aconteceu. Eu precisei fazer isso, e o governador me deu oficiais nobres como testemunhas para garantir que tudo aconteça conforme as regras. Não posso levar você nem nenhum dos nossos homens comigo. Por favor, cuide da fragata enquanto eu estiver fora.";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			dialog.text = "Ótimo, maravilhoso! Primeiro, você vai para uma orgia com mulheres estranhas e aparece só na manhã seguinte, e eu nem te dei uma bronca por isso. Agora, você me diz que quase perdeu nosso navio num jogo de cartas, mas ganhou uma cortesã! E agora vai lutar pela 'honra' dela contra algum bastardo de sangue azul que você nem pode matar! Como você acha que eu devo me sentir com tudo isso? Me diz.";
			link.l1 = "Helen, escute, você tem todo o direito de estar brava comigo, mas me deixe explicar...";
			link.l1.go = "GoldenGirl_22";
		break;
		
		case "GoldenGirl_22":
			dialog.text = "Sabe de uma coisa, já cansei disso. Vai lá e luta seu maldito duelo. Eu cuido da sua nova fragata, grande Capitão de Maure, não se preocupe. Agora me dá licença, vou me trancar na minha cabine e beber uma garrafa daquele bom madeira que achei no seu camarote. Mas se acontecer alguma coisa com você, juro por Deus que vou trazer o inferno pra essa cidade e enterrar esse bordel junto com o palácio do seu querido Excelentíssimo!";
			link.l1 = "Helen, vai ficar tudo bem, confie em mim... Espera, pra onde você vai?! Droga! Lá vamos nós de novo...";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, você tem algumas explicações a dar. Poderia me dizer o que diabos aconteceu? Eu não coloquei uma vigia decente e os rapazes estavam bebendo... uns canalhas atacaram nosso navio e nos amarraram enquanto dormíamos. Depois, aqueles desgraçados começaram a me perguntar até onde você iria para me resgatar. No fim, me trancaram no porão. Já perdi a conta de quantos dias estou esperando!";
			link.l1 = "Aquele desgraçado queria se vingar da vergonha que causei a ele. Eu estava com medo que ele fizesse algo com você! Graças a Deus você está bem!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			dialog.text = "Imagino que você teve que fazer alguma coisa para me trazer de volta? Algo ruim, não é?";
			link.l1 = "O que importa é que você voltou para mim. Eu falhei com você, Helen. Me desculpe, de verdade! Espero que consiga me perdoar de coração!";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Já fiz isso. Tive muito tempo para pensar no que disse... Eu também sinto muito, Charles. Se ao menos eu não tivesse levado tão para o lado pessoal seus negócios com aquele marquês. Eu teria colocado uma vigia de verdade naquela noite, teria ficado alerta. Ah! Eu sou mesmo uma inútil!";
			link.l1 = "Pare de dizer isso, o passado ficou para trás. Eu te amo e nunca mais vou te deixar. Eu prometo!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "Acho melhor eu nem saber exatamente o que você fez, certo? Tudo bem, estamos juntos de novo e é isso que importa.";
			link.l1 = "Não tenho segredos para você. Vou te contar...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Que confusão... Eu sei que você não tinha escolha, mas como vai explicar isso para Di Lu Parkes e os amigos dele? Digo, agora você é um criminoso!";
				link.l1 = "Eu escolhi pagar esse preço, mas na verdade não tive escolha. Não se preocupe, vou dar um jeito de consertar tudo e restaurar nosso bom nome. Se não conseguir, sempre seremos bem-vindos em Isla Tesoro! Eu aguento, se você estiver ao meu lado.";
			}
			else
			{
				dialog.text = "Que história, Charles... Eu acredito que você não teve escolha, mas e agora? Aquele inglês vai resolver tudo, ou vai ser guerra? Tem certeza de que não quer vir para Basse-Terre ver eles acorrentando aquele desgraçado?";
				link.l1 = "Sabe, Helen, duas semanas atrás eu jamais teria deixado passar. Mas hoje, que ele vá para o inferno! Nem me importo mais com a punição que ele merece. Estamos juntos de novo, e isso é tudo o que importa!";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Você sabe que sempre vou estar ao seu lado. Ha! Não é como se fosse a primeira vez que nós dois acabamos até o pescoço na lama. Vamos sair dessa de novo.";
				link.l1 = "É verdade. Vamos zarpar, querido! O horizonte nos espera!";
			}
			else
			{
				dialog.text = "Gostei do seu jeito de pensar, Charles! Chega de nobres: franceses, britânicos, espanhóis – tanto faz. Acho que merecemos umas férias!";
				link.l1 = "Combinado. Só eu e você! Chega de governadores e bastardos de sangue nobre!";
			}
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Sim, sim, Capitão!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Parece ótimo! Vou avisar os rapazes que é hora de içar âncora! E Charles...";
				link.l1 = "Eu sei, Helen, eu sei. Já vou me juntar a você.";
			}
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, você conseguiu! Os portugueses me contaram tudo! Que história!";
			link.l1 = "Graças a Deus, você está viva, Helen! Você não faz ideia de como estou feliz em te ver de novo!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Falando nisso. Você prometeu me contar algo, lembra? Algo grande e complicado. Essa é sua chance, Capitão. O que diabos aconteceu?!";
			link.l1 = "Eu te amo, Helen. O resto não importa.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Sim, isso ajudou, mas... Droga, eu também, Charles. Eu te amo também. Meu Deus, senti tanto a sua falta!";
			link.l1 = "Eu também. Vem comigo, não vou te deixar essa noite nem que o céu desabe sobre essa cidade miserável. Nunca mais vou te abandonar. Nunca.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Acho melhor eu nem saber exatamente o que você fez, né? Sim, estamos juntos de novo e é isso que importa.";
			link.l1 = "Não tenho segredos para você. Vou te contar...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "Inacreditável! Você está dizendo que França e Inglaterra estão prestes a entrar em guerra uma com a outra por minha causa?";
			link.l1 = "Não, Helen. É porque eu cometi um erro de julgamento muito grave. Mas eu precisava te trazer de volta e consertar tudo.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "Isso tudo é muito tocante e romântico, estou quase pronta para esquecer como tudo começou. Quase. Mas falando sério, eles te prenderam porque os portugueses deram o nome errado da maldita brigantina?";
			link.l1 = "Na verdade, ele me deu a certa! Queria entender como ele conseguiu fazer isso, e por quê. Aliás, onde está o próprio?!";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "Ele se foi. Logo depois de me trazer aqui. Eu não quis aceitar a 'hospitalidade' da cortesã que você ganhou, então pedi para o Bartholomew alugar um quarto pra mim. Ele pagou e sumiu sem dizer uma palavra. Na verdade, espera, não, ele deixou uma carta pra você sim!";
			link.l1 = "Uma carta? Do Bartolomeu, o Português? Isso é novidade. Não estou gostando do rumo disso...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Certo, vou deixar você ler aqui enquanto vou cumprimentar os rapazes. Devem estar preocupados. Nunca pensei que sentiria falta daquelas caras de cachorro sem dono! Enquanto isso, tente não se meter em mais uma encrenca!";
			link.l1 = "Maldição... Ainda não acredito que consegui te trazer de volta!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "Areia branca, água verde cristalina, você, eu e um bom vinho – Charles, isso é tão romântico! A gente devia passear assim juntos mais vezes, tá bom!";
			link.l1 = "Que bom que você gostou. Acho que deveríamos arranjar mais tempo para isso agora.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "Charles, o que você está fazendo e por que está de joelhos? Isso foi tão inesperado...";
			link.l1 = "Helen, eu te amo. E quero viver ao seu lado todos os dias que me forem concedidos. Por isso, aqui e agora, diante deste mar e deste céu, eu te peço – Helen Beatrice Sharp – me conceda a honra de ficar ao meu lado diante dos homens e de Deus até que a morte nos separe. Eu, Charles de Maure, Chevalier de Monper, te pergunto – você aceita se casar comigo?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore_ship1")
			{
				dialog.text = "Sabe, nunca gostei dessas formalidades, mas estou com você até o fim do mundo. E quanto à sua pergunta, a resposta é... ah, desculpe, eu derramei!";
				link.l1 = "Deixa pra lá, é só vinho e eu nunca gostei dessa camisa...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, é claro que sim! Sim, sim, e mais uma vez sim!!! Mas espero mesmo que você não esteja pensando em nos aposentar em algum castelo de família empoeirado para cultivar nabos até o fim dos nossos dias?";
				link.l1 = "Bem, nós até temos um castelo de família, mas ele não é empoeirado e não vamos ficar lá. Nossa vida é liberdade e o horizonte ao nosso alcance!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Então um brinde a você, meu capitão, meu marido, e ao nosso casamento!";
			link.l1 = "A você, meu amor! E ao nosso futuro juntos, temos tanto pela frente!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Então um brinde a você, meu capitão, meu marido, e ao nosso casamento!";
			link.l1 = "A você, meu amor! E ao nosso futuro juntos, temos tanto pela frente!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Helena_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Então, o Abade Benoit voltou e está pronto para nos casar. Mas só pra você saber, eu não vou usar vestido nem numa ocasião dessas! Acha que eu de calças vai causar escândalo?";
			link.l1 = "Helen, eu te amo de qualquer jeito, e eles vão superar. Primeiro, queria conversar com você sobre os convidados e a cerimônia.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			dialog.text = "Tem um problema – a maioria dos nossos melhores amigos, com quem adoraríamos compartilhar esse dia, não vai poder entrar na cidade, muito menos na igreja. Então, vamos nos casar aqui com todas as pessoas importantes, como manda o figurino, e depois partimos para Isla Tesoro para comemorar de verdade com nossos verdadeiros amigos. O que acha?";
			link.l1 = "Parece ótimo para mim! Vou falar com o Abade Benoit, mas precisamos enviar os convites e mais...";
			link.l1.go = "LongHappy_9";
		break;
		
		case "LongHappy_9":
			dialog.text = "Calma, capitão. Sua futura esposa adorada vai dividir um pouco desse fardo! Vou organizar tudo na Isla Tesoro e avisar nossos amigos, só me diga: você quer um casamento grande ou pequeno?";
			link.l1 = "Só você, eu e nossos amigos mais próximos. Depois de toda essa pompa oficial aqui na Martinica, vamos querer um pouco de intimidade de verdade.";
			link.l1.go = "LongHappy_10";
			link.l2 = "Todos devem se lembrar deste dia! Chamem todos! Ninguém vai ficar de fora!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Confortável e acolhedor – você leu meus pensamentos! Vamos ter que visitar Sharptown e eu vou preparar tudo. Acho que cinquenta barris de rum e duas dúzias de barris de vinho devem ser suficientes. E, para comida e diversão, vamos precisar de trezentos mil peças de oito.";
			link.l1 = "Me lembra – por que mesmo você não cuida das finanças do navio? Eu resolvo tudo. Só preciso dar um pulo no abade e depois partimos para Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Então, você quer dar uma festa como verdadeiros lobos do mar? Tudo bem! Vamos ter que passar em Sharptown e eu cuido de tudo. Vamos precisar abastecer de verdade – acho que cem barris de rum e cinquenta de vinho devem bastar. E o resto das despesas vai dar pelo menos quinhentas mil peças de oito.";
			link.l1 = "Você está convidando toda a Irmandade da Costa? Ah, que se dane, vamos nessa! Eu cuido dos suprimentos. Só preciso passar rapidinho no abade e já partimos para Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Helen");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Charles, eu cuido do carregamento, depois entrego os convites para o barão e acerto as coisas com o dono do bar. Não deve demorar muito.";
			link.l1 = "Não se preocupe, minha querida, vou arranjar algo útil pra fazer... Ou então tirar um cochilo na areia. Nunca imaginei que seria mais fácil invadir Tortuga do que planejar meu próprio casamento, pelo amor de Deus.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "Conseguiu descansar um pouco, Charles? Tenho boas e más notícias. A má notícia é que os locais se divertiram tanto na semana passada que acabaram incendiando, sem querer, a maldita taverna 'Pica-Pau Velho'! Agora a boa notícia: o barão prometeu que ela será reconstruída, maior e melhor do que antes, até a nossa volta. Já deixei tudo acertado, então podemos zarpar.";
			link.l1 = "Espero que o nosso casamento não deixe uma pilha de cinzas parecida na cidade quando partirmos. Que pena, eu gostava bastante do 'Pica-Pau Velho' – aconchegante, íntimo, com só um leve cheiro de vômito e estopa! Mas enfim, meu bem, você tem razão – é melhor irmos.";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "Jan já está na cidade com a Gladys, você acredita? Nunca pensei que eles realmente viriam ao meu casamento! Ai, meu Deus do céu! Nem quando estávamos naquela terrível cidade-templo dos índios eu fiquei tão nervosa quanto agora!";
			link.l1 = "Está tudo bem, querido, está tudo bem. Eu também estou nervosa – é normal ficar assim. Já que os convidados já chegaram, vou até o padre Benoit para saber quando a cerimônia vai começar.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Vai ser um dia longo e difícil pra caramba... Vou ver o Jan e a Gladys.";
			link.l1 = "Fico feliz que eles puderam vir. O velho Svensson te ama como se fosse filha dele, e a dona McArthur te ama ainda mais. É bom que eles estejam aqui hoje. Vai lá e não se preocupe – vai dar tudo certo.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Helen");
		break;
		
		case "LongHappy_20":
			dialog.text = "Sim.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Sim.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Sim.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "Eu, Charles Henry de Maure, chevalier de Monper, te recebo, Helen Beatrice Sharp, como minha esposa, para ter e cuidar, de hoje em diante, na alegria e na tristeza, na riqueza e na pobreza, na saúde e na doença, até que a morte nos separe. Segundo a Santa Lei de Deus, na presença Dele, faço este voto.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "Eu, Helen Beatrice Sharp, te recebo, Charles Henry de Maure, como meu marido, para ter e manter, a partir deste dia, na alegria e na tristeza, na riqueza e na pobreza, na saúde e na doença, até que a morte nos separe. Segundo a Santa Lei de Deus, na presença de Deus, faço este voto.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amém.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "Helen Beatrice de Maure, Madame de Monper - ah, eu adoro como isso soa, meu querido marido!";
			link.l1 = "Não ouvi nada melhor, minha esposa!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			dialog.text = "Você sabe – achei que isso não mudaria nada, e talvez não tenha mudado mesmo – eu já te amava antes e queria passar o resto dos meus dias com você, mas este dia, esta cerimônia sagrada... Estou realmente feliz, Charles! Mais feliz do que nunca, e olha para a Gladys e o Jan – eles estão radiantes! Tem tantos rostos alegres ao nosso redor! Aliás – está na hora de você circular entre os convidados e receber os parabéns. Volte quando terminar, não esqueça – estamos sendo esperados em Sharptown.";
			link.l1 = "Vou fazer isso agora mesmo, querida. Um beijo antes de eu ir!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Olá, marido, você já falou com os convidados?";
			link.l1 = "Ainda não, tenha paciência, esposa, eu volto logo.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Sim, nunca ouvi tantos parabéns de uma vez só. E sabe de uma coisa? Acho que a maioria deles foi sincera!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			dialog.text = "Sim, esses nobres são surpreendentemente sinceros – devo admitir, eu esperava mais falsidade e hipocrisia. Ou talvez eu esteja simplesmente tão feliz que não percebo nada. Mas afinal, nossos amigos estão nos esperando em Sharptown! Quando partimos?";
			link.l1 = "Agora mesmo. Vamos voar alto como águias direto para um banquete entre amigos. Espero, minha esposa, que não se importe de passar esta noite em nossa cabine?";
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "Oh sim, meu marido, você é tão romântico! E não se mexa assim, agora eu tenho o direito de te beijar em público... Sim, podemos ir agora!";
			link.l1 = "Navegador, trace a rota para Sharptown e não nos incomode por motivo nenhum! Não me importa se até uma frota fantasma estiver vindo atrás de nós!";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Ah, meu querido marido, estou tão feliz! Hoje é um dia maravilhoso...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Vamos, Charles. Esse mentiroso vai estar morto antes de tocar o chão!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "Estou bem, Charles, está tudo certo. E o Nathan, como está?";
			link.l1 = "Tanto sangue... Dannie, ele está respirando? Eu vejo ele respirando!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Mais rápido, querido, não perca tempo!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "Charles, você está bem? Que carnificina! Desculpe, estávamos presos no andar de cima, havia uma dúzia daqueles desgraçados, então precisei lidar com eles primeiro!";
			link.l1 = "Está tudo bem, eu resolvi. Fico feliz por finalmente ter encerrado aquela história com o Jacques... finalmente. Ele teve o que merecia.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Tudo bem, meu querido, vamos terminar aqui e voltar. Não consigo parar de pensar no Nathan, como ele está? Ele me protegeu daquela bala!";
			link.l1 = "Você tem razão, querido, eu também me preocupo. Vá em frente, estou logo atrás de você.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "Encontramos o Marcus! Ele estava no porão de carga, amarrado e desacordado.";
			link.l1 = "Ele está vivo?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Não se preocupe, querido, o Barão Tyrex vai enterrar todos nós. Mal acordou e já está elétrico, não para de pedir rum, o sabre e a ponte – nessa ordem.";
			link.l1 = "Esse é o nosso velho Marcus! Deixa ele descansar um pouco enquanto terminamos aqui e depois voltamos para a praia.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Me desculpe tanto, querido... Primeiro nosso fiel amigo Tichingitu, agora o Gino... Barbazon já devia ter morrido umas dez vezes por tudo o que fez!";
				link.l1 = "Infelizmente, só fiz isso uma vez. Também me sinto mal... Mas vencemos, e ele nunca mais vai machucar ninguém.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Eu me sinto tão mal pelo Gino, Charles! Quando eu soube, não consegui acreditar! Como você está, meu amor?";
					link.l1 = "Também não consigo acreditar... que fim terrível... Nunca imaginei que este dia acabaria assim.";
				}
				else
				{
					dialog.text = "Será que os futuros historiadores vão escrever sobre a grande batalha da Baía dos Corsários? O dia em que os barões da Irmandade da Costa se enfrentaram em campo aberto – aposto que os espanhóis da Costa Guarda estão enxugando lágrimas de gratidão! Mas vencemos de novo! Nossos amigos estão vivos, e nossos inimigos, mortos – um presente de casamento glorioso!";
					link.l1 = "Sim, foi mesmo uma celebração, mas conseguimos, meu anjo. Conseguimos.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Vamos, Dannie encontrou uma casa pra gente aqui nos arredores da cidade, não quero voltar pro navio agora até que esteja limpo. Vamos sentar e brindar àqueles que não conseguiram.";
			link.l1 = "Sim, Helen, vamos.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Eu fiquei tão mal pelo Gino, Charles! Quando soube, não consegui acreditar! Como você está?";
				link.l1 = "Também não consigo acreditar... que fim terrível... Nunca imaginei que este dia acabaria assim.";
			}
			else
			{
				dialog.text = "Você viu o Hawk? A Dannie me deixou sair quando o Gino disse 'o perigo passou'. Fico feliz que esteja tudo bem. Nossos amigos estão vivos, e nossos inimigos mortos – um presente de casamento glorioso!";
				link.l1 = "Eu também, querido. E nós vencemos. Barbazon está morto, os barões estão reunindo o que sobrou de suas tripulações. A luta acabou.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, vejo que mal consegue ficar de pé, mas estive na taverna e você não vai acreditar no que ouvi do barman.";
			link.l1 = "Sim, ouvi isso do Jan, ele também esteve lá. Pelo que parece, nosso querido índio entrou em pé de guerra. Vamos dar uma passada na enseada de Sabo-Matila, algumas pessoas o viram indo naquela direção.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Deus do céu! Isso sim é espírito, Tichingitu! Ufa, estou rindo até não aguentar mais! Por que nós, europeus, não adotamos um costume desses também?! Ah, Charles, você mal consegue ficar de pé de sono! Vamos, Dannie achou uma casa pra gente aqui nos arredores – você precisa descansar.";
			link.l1 = "Vamos lá ... Acho que já dormi naquela praia antes.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "tonzag_jailed":
			dialog.text = "... Está tudo bem.";
			link.l1 = "Que bom ouvir isso.";
			link.l1.go = "exit";
			link.l2 = "Sério?";
			link.l2.go = "tonzag_jailed_1";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Sim.";
			link.l1 = "Que bom ouvir isso.";
			link.l1.go = "exit";
			link.l2 = "Vamos, eu vejo que tem algo te incomodando!";
			link.l2.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Estou perfeitamente bem, deixa pra lá!\nCharles, vai pro inferno! Eu odeio masmorras, odeio você e odeio essa ilha maldita! Me tira daqui agora!\nDesculpa... Eu realmente não suporto masmorras, não encosta em mim!";
			link.l1 = "Desculpe. Todos nós temos medo de alguma coisa.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "AAAA! Tira a gente daqui! Charles, faz alguma coisa!";
			link.l1 = "Se controle!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Meu capitão, o inimigo abriu um rombo no casco do segundo convés e já colocou uma equipe de abordagem a bordo. A luta está por todo o navio, e a maioria dos artilheiros já foi derrubada! Precisamos resgatar nossa tripulação e o Hercule! Você vai, ou devo ir eu?";
			link.l1 = "Dessa vez, eu mesmo vou, Helen! Assuma o comando do navio e nos tire daqui!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Sim, meu Capitão. Não vou te decepcionar, e por favor, tome cuidado!";
			link.l1 = "Eu sei, Helen. E você também tome cuidado!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Vitória, meu capitão! O grupo de desembarque foi eliminado, o inimigo decidiu recuar e seguiu para o sul. O estado do navio é aceitável. Tripulação viva: "+GetCrewQuantity(pchar)+" pessoas. Relatório concluído!";
			link.l1 = "Obrigada, Helen, e o que...";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Me despeça, vencedor, seu prêmio é fazer comigo o que quiser!";
			link.l1 = "Ah...";
			link.l1.go = "tonzag_after_victory_2";
			link.l2 = "Vamos!";
			link.l2.go = "tonzag_after_victory_2";
		break;
		
		case "tonzag_after_victory_2":
			dialog.text = "Oi, Hercule. Desculpa, você chegou numa hora meio ruim! Mas, caramba, fico feliz de te ver vivo e coberto de sangue alheio – seu estado natural, né!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog");
		break;
		
		case "tonzag_after_victory_3":
			dialog.text = "";
			link.l1 = "Bem, Helen, você é incrível!";
			link.l1.go = "tonzag_after_victory_4";
		break;
		
		case "tonzag_after_victory_4":
			dialog.text = "Eu ainda nem comecei, meu capitão. Vamos comemorar?";
			link.l1 = "Não preciso ser convencida!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "Não olhe, não olhe, não olhe... Este é outro mundo, meu capitão! Não pode ser assim!";
			link.l1 = "Acho que este agora é o nosso mundo, querido. E você tem razão, vamos seguir em frente...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "Receio que essa pandemia esteja afetando suas garotas, Rodrigo. Mantenha elas ocupadas com tricô ou algo assim!";
			link.l1 = "Essa conversa claramente não vai levar a lugar nenhum. Combinamos que iríamos à igreja amanhã. Para rezar... claro.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "Tenho orgulho de você, meu amor!";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "Bem, Charles...";
			link.l1 = "O que está te preocupando agora, Helen?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "O fato de que o casal mais escandaloso do Caribe é dono de duas ilhas inteiras! Meu refúgio pirata em Isla Tesoro e sua terra prometida – quanto tempo você acha que elas vão durar quando a civilização finalmente chegar às Índias Ocidentais?";
			link.l1 = "Tempo suficiente para durar a nossa vida inteira, meu bem. E depois? Não podemos controlar o que vai acontecer. Outros vão contar a nossa história. O mais importante é que você e eu estamos aqui e agora, juntos e felizes.";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "Falando em felicidade... Estou prestes a subir agora: preciso acender as velas, arrumar a cama, talvez escrever no meu diário...";
			link.l1 = "Vou ficar aqui mais um pouco, depois subo para te ajudar a 'arrumar a cama.'";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "Não demore muito...";
			link.l1 = "";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestFunctionDelay("LoveSex_Classic", 2.5);
			NextDiag.CurrentNode = "sex_after";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "drinking_refuse":
			dialog.text = "Você está mesmo tão ocupado assim? Que pena, mas eu entendo. Vou encontrar outra coisa para me distrair.";
			link.l1 = "";
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
			
			pchar.questTemp.HelenDrinking.Result = "no_visit";
			CloseQuestHeader("HelenDrinking");
		break;
		
		case "drinking_accept":
			dialog.text = "Que bom que você se lembra. Eu queria te dizer que sou muito grata. Não é todo dia que alguém te salva de... você sabe do quê. Vamos tomar um drink. É por minha conta.";
			link.l1 = "Helen... O que a Gladys vai dizer?";
			link.l1.go = "drinking_accept_1";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToHouse");
		break;
		
		case "drinking_accept_1":
			dialog.text = "Muito engraçado, Charles. Vamos, e não me irrita.";
			link.l1 = "Isso é um encontro?";
			link.l1.go = "drinking_accept_1_1";
			link.l2 = "Já estou indo, não precisa ficar irritada.";
			link.l2.go = "drinking_accept_1_2";
		break;
		
		case "drinking_accept_1_1":
			dialog.text = "Ha-ha! Queria você! Eu teria que estar completamente bêbada!";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_accept_1_2":
			dialog.text = "Assim está melhor.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_in_tavern":
			dialog.text = "";
			link.l1 = "... ela tinha muitas virtudes, mas não aguentava bebida. Foi assim que nos conhecemos.";
			link.l1.go = "drinking_in_tavern_1";
			link.l2 = "... meu pai insistiu que eu servisse ao exército. Acabei cedendo e fui para Paris com uma carta de recomendação. Mas nunca cheguei ao endereço indicado e virei artista.";
			link.l2.go = "drinking_in_tavern_2";
		break;
				
		case "drinking_in_tavern_1":
			dialog.text = "Ah, agora entendi de quais virtudes você está falando. Qual era o nome dela?";
			link.l1 = "Lulu.";
			link.l1.go = "drinking_in_tavern_1_1";
		break;
		
		case "drinking_in_tavern_1_1":
			dialog.text = "Lulu... Com essas histórias, você acabou de arruinar Paris pra mim. Eu achava que era uma cidade cheia de vida, mas agora só parece um grande bordel de luxo.";
			link.l1 = "Você condena os bordéis?";
			link.l1.go = "drinking_in_tavern_1_2";
		break;
		
		case "drinking_in_tavern_1_2":
			dialog.text = "Sim, Capitão, e eu não entendo os homens que as frequentam.";
			link.l1 = "(encarar a caneca)";
			link.l1.go = "drinking_in_tavern_1_4";
			link.l2 = "(tem uma tosse terrível)";
			link.l2.go = "drinking_in_tavern_1_4";
			link.l3 = "Ah... cada um com seu gosto... eu acho?";
			link.l3.go = "drinking_in_tavern_1_4";
		break;
		
		case "drinking_in_tavern_1_4":
			dialog.text = "(risos) Ha! Você precisava ver a sua cara! Assustado? Vamos tomar mais uma! À Paris!";
			link.l1 = "Para Paris!";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_2":
			dialog.text = "(ri) Você?! Um artista? Então, a beleza e o orgulho da frota inglesa, um estuprador e verdadeiro filho da puta, Donovan, morreu pelas mãos de um artista parisiense? Ah, pena que você não usava seu jabô impecável durante o abordo e não espancou aquele canalha com uma bengala!";
			link.l1 = "É, uma grande infelicidade. Justo naquele dia, a gravata estava para lavar.";
			link.l1.go = "drinking_in_tavern_2_1";
		break;
		
		case "drinking_in_tavern_2_1":
			dialog.text = "(ri) Bem, obrigada, Charles. Não sei como será o resto da noite, mas a noite já está maravilhosa. Quem sabe eu até deixe você pintar meu retrato. Mas, olha, nada daquele estilo que você usava com as suas parisienses!";
			link.l1 = "Ha! Isso é, se eu concordar em te pintar.";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_3":
			dialog.text = "Com licença, meu capitão, ouvindo suas aventuras e as vidas das nobres... cortesãs de ambos os sexos. Que eu seja devorada por tubarões, nunca vou acreditar que você não encontrou nada melhor pra fazer com seu tempo! Nem ouse me dizer que tudo o que fez foi sujar telas e torrar o dinheiro do seu pai. Se fosse só isso, você não teria sobrevivido um dia conosco.";
			link.l1 = "Eu tinha... outros interesses.";
			link.l1.go = "drinking_in_tavern_" + pchar.HeroParam.HeroType;
		break;
		
		case "drinking_in_tavern_herotype_3":
			dialog.text = "";
			link.l1 = "Eu conciliava a vida na corte com o serviço militar, mas não... hehe, não exatamente do jeito que meu pai queria, claro. Depois de umas fugas pela janela e uma briga ou outra, acabei ficando amigo dos guardas. E, naturalmente, aprendi muita coisa, fiquei mais forte. Os camaradas mais velhos me ensinaram a aguentar pancada, usar armadura, manejar uma espada e, claro, aproveitar a vida do jeito certo. Essa última parte, aliás, era a minha preferida. Você pode não acreditar, mas nem todo mundo consegue brandir uma espada da manhã até o meio-dia e depois beber do meio-dia até o amanhecer seguinte.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_1":
			dialog.text = "";
			link.l1 = "Você acha que foi fácil na capital para um nobre com má fama e bolso vazio, perdendo a carta de recomendação do papai logo no primeiro dia? Tive que me impor e não deixar ninguém zombar de mim. As aulas de esgrima em casa não foram esquecidas, e eu respondia a qualquer olhar atravessado com um duelo. Acabei até gostando da coisa. Mas nunca matei ninguém, e consegui sair de Paris antes de topar com algum espadachim experiente que me mandasse para o outro mundo.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_4":
			dialog.text = "";
			link.l1 = "Passei muito tempo em cemitérios. Não pense nada de ruim – era só um passatempo popular no meu círculo social. Para mostrar coragem, íamos ao cemitério à noite, colocávamos garrafas vazias na cerca e atirávamos nelas contra o relógio. De manhã, já tínhamos desperdiçado cem balas e uma caixa de champanhe. Hoje, claro, me envergonho desse tipo de comportamento, mas naquela época o vencedor levava um belo prêmio e ainda ganhava alguns... favores das damas da corte. Tudo era aproveitado – até me aventurei um pouco com misturas de pólvora. Mas por que nenhum de nós pensou em aprender a fazer cartuchos de papel – isso eu nunca vou entender.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_2":
			dialog.text = "";
			link.l1 = "Estudei, e com bastante dedicação – cheguei até a quase entrar na Sorbonne. Trabalhei em escritório até ficar entediante e, no geral, fiz um pouco de tudo. O professor, um velho amigo do meu pai, preferia a prática à teoria, então pude conhecer Paris de todos os ângulos e conversar com todo tipo de gente: de bandidos a nobres. Tudo isso acabou sendo útil aqui.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_4":
			dialog.text = "E... é só isso? Então ainda existe algo em você, meu capitão. Algo que você ainda não enxergou em si mesmo. À sua!";
			link.l1 = "Um brinde!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernChange");
		break;
		
		case "drinking_my_background":
			dialog.text = "";
			link.l1 = "Conte-me sua história, Helen. Minhas aventuras na Capital não são nada perto de uma garota com menos de trinta anos comandando uma escuna com cem homens a bordo.";
			link.l1.go = "drinking_my_background_1";
		break;
		
		case "drinking_my_background_1":
			dialog.text = "Menos de trinta, hein, Charles? Por um comentário tão ousado, você vai ter que pagar a próxima rodada! Todos os meus homens estão mortos, e eu não comando mais uma escuna. Sinceramente, não sei se algum dia vou comandar outra de novo.";
			link.l1 = "Desculpe, Helen. Não quis tocar em um ponto sensível. Mas por que você acha que a sua carreira de capitã acabou?";
			link.l1.go = "drinking_my_background_2";
		break;
		
		case "drinking_my_background_2":
			dialog.text = "Because my crew is dead, and a different one won't ever accept me. Eh! Fine, my captain, you've told me a lot about your life; now it's my turn! The truth is not at the bottom of this mug, so let's dispense with the mystery.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_3";
		break;
		
		case "drinking_my_background_3":
			dialog.text = "Meu caso, Charles, é único. Meu pai foi um dos melhores marinheiros dessas bandas, muito respeitado pelo Diabo da Floresta, sua tripulação o adorava, e ele me amava mais do que a própria vida.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_4";
		break;
		
		case "drinking_my_background_4":
			dialog.text = "Tira qualquer uma dessas coisas, e ele teria me mandado para Londres para viver na... civilização, ou me deixado murchar aqui como minha mãe. No começo, tudo deu certo: eu queria liberdade, liberdade de verdade, Charles, e comandar um navio de guerra com uma tripulação leal te dá exatamente isso. E meu pai me deu tudo o que podia. Fui para o mar com ele aos doze anos, passei os primeiros seis meses caçando ratos no porão, e só então me deixaram trabalhar com os marinheiros.";
			link.l1 = "Sean MacArthur te fez virar um rato de navio? Sinto muito, Helen, mas depois disso não tem mais volta! E a tripulação, como te recebeu?";
			link.l1.go = "drinking_my_background_5";
		break;
		
		case "drinking_my_background_5":
			dialog.text = "Well, perhaps I'm exaggerating a bit for the sake of a good story? My father's crew accepted me; he gathered fine people. But since then, I've been afraid... of holds and any small dark spaces in general. Ha! Svensson almost killed my father when he found out!";
			link.l1 = "Ele é importante para você. Claramente teve um papel no seu destino, não menos que o Sean.";
			link.l1.go = "drinking_my_background_6";
		break;
		
		case "drinking_my_background_6":
			dialog.text = "Sim. Todos os barões disseram abertamente ao meu pai que ele era um tolo, mas foi o Diabo da Floresta quem lhe deu sua aprovação e apertou sua mão depois que eu bati o recorde da tripulação subindo no mastro. Esse momento vai ficar comigo para sempre: os gritos triunfantes da tripulação e, para onde quer que eu olhasse, o horizonte infinito do mar. E o olhar de aprovação do meu pai—eu não podia ver, mas senti com todo o meu coração.";
			link.l1 = "Meu triunfo terminou comigo caindo do cordame no primeiro dia a caminho de Guadalupe.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.TakeFolke")) {
				link.l1 = link.l1+" Meu timoneiro, Deluc, também tinha um olhar bem revelador."}
			link.l1.go ="drinking_my_background_7";
		break;
		
		case "drinking_my_background_7":
			dialog.text = "Ah-ha-ha! I can imagine! Don't worry, that was a long time ago; now you're a real sea wolf!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_8";
		break;
		
		case "drinking_my_background_8":
			dialog.text = "Aos nossos triunfos!";
			link.l1 = "Ouçam, ouçam!";
			link.l1.go = "drinking_my_background_12";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "... And then I gradually rose through the ranks, served at the captain's table in councils with my father and officers. Learned a lot. From the age of fifteen, they started taking me on military campaigns, and I killed a man in my very first battle. It was a disgusting campaign; we shouldn't have set sail on a Monday... Really shouldn't have!";
			link.l1 = "Aos quinze? Você está me assustando, Helen.";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "Eu nem entendi o que aconteceu. O mercador holandês tinha sua vanguarda — mercenários da Companhia. Eles resolveram agir com ousadia e contra-atacaram nosso convés de popa. E eu, feito uma tola, sem medo nenhum pela minha vida, enfiei minha cabeça loira pra fora. Levei logo uma coronhada de pistola. Mas um instante antes disso, ainda consegui enfiar minha rapieira em algum idiota da Companhia.";
			link.l1 = "Meu Deus, e o Sean? Como é que ele não te mandou pra terra firme depois disso?";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_13":
			dialog.text = "Meu pai também não saiu ileso daquela batalha, e ver minha cabeça rachada e tola certamente não ajudou. Ele foi definhando aos poucos, e provavelmente ninguém percebeu além de mim. E então ele se foi. Segundo o testamento, herdei o Rainbow com sua tripulação e dinheiro suficiente para manter o navio navegando por um ano.";
			link.l1 = "E a tripulação te aceitou como capitã?";
			link.l1.go = "drinking_my_background_14";
		break;
		
		case "drinking_my_background_14":
			dialog.text = "Não vivemos em um conto de fadas, meu capitão. Alguns receberam a vontade do meu pai com hostilidade – as coisas tomaram um rumo desagradável\nSe ao menos um marinheiro tivesse abandonado o Arco-Íris, se recusando a servir sob meu comando, teria sido desastroso para minha reputação. Mas Svensson interveio e colocou todos no lugar. Ninguém deixou a tripulação abertamente... naquela época. Por sete anos, comandei minha beleza, transportei mercadorias duvidosas para o Demônio da Floresta, procurei tesouros, vivi... Mas agora, tudo isso ficou no passado.";
			link.l1 = "No passado, não. Eu acredito que você ainda vai comandar seu próprio navio de novo! Vamos brindar a isso!";
			link.l1.go = "drinking_my_background_sea";
			link.l2 = "Talvez não consigamos recuperar o navio, mas sua espada ainda está com você.";
			link.l2.go = "drinking_my_background_land";
		break;
		
		case "drinking_my_background_sea":
			dialog.text = "Sabe, quando você fala assim, eu também acredito. Vamos beber!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_COMMERCE, 5);
			AddCharacterSkill(npchar, SKILL_ACCURACY, 5);
			AddCharacterSkill(npchar, SKILL_CANNONS, 5);
			AddCharacterSkill(npchar, SKILL_SAILING, 5);
			AddCharacterSkill(npchar, SKILL_REPAIR, 5);
			AddCharacterSkill(npchar, SKILL_GRAPPLING, 5);
			AddCharacterSkill(npchar, SKILL_DEFENCE, 5);
			notification("Naval Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "sea";
		break;
		
		case "drinking_my_background_land":
			dialog.text = "Mas será que minha espada vai me trazer felicidade? A resposta deve estar no fundo desta caneca. Vamos beber!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_F_LIGHT, 5);
			AddCharacterSkill(npchar, SKILL_FENCING, 5);
			AddCharacterSkill(npchar, SKILL_F_HEAVY, 5);
			AddCharacterSkill(npchar, SKILL_PISTOL, 5);
			AddCharacterSkill(npchar, SKILL_FORTUNE, 5);
			AddCharacterSkill(npchar, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(npchar, SKILL_SNEAK, 5);
			notification("Personal Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "land";
		break;
		
		case "drinking_my_background_15":
			dialog.text = "Estive pensando na sua vida na Europa... Olha, você é um dândi da cidade, e eu sou só uma garota comum, mas nós já conquistamos nossos nomes no canto mais perigoso do mundo.";
			link.l1 = "Parece um brinde! Então, existe algo que nos une?";
			link.l1.go = "drinking_my_background_16";
		break;
		
		case "drinking_my_background_16":
			dialog.text = "Bem, eu sigo os passos do meu pai. Não sei quanto a você, mas talvez sua família também tenha tido uma influência parecida em você? Talvez você ainda não tenha percebido?";
			link.l1 = "Vou perguntar ao meu querido irmão assim que eu tirá-lo da prisão.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernEmpty");
		break;
		
		case "drinking_game":
			dialog.text = "Bem, é isso, meu capitão. Já trocamos histórias, hora de encerrar a noite.";
			link.l1 = "Hum, eu esperava um final diferente para esta noite.";
			link.l1.go = "drinking_game_1";
		break;
		
		case "drinking_game_1":
			dialog.text = "A noite ainda não acabou. Que tal um jogo? Se você jogar bem suas cartas, talvez seus desejos sejam atendidos.";
			link.l1 = "Vamos jogar cartas? Tô dentro!";
			link.l1.go = "drinking_game_2";
		break;
		
		case "drinking_game_2":
			dialog.text = "Calma aí, lobo do mar. Não vou jogar strip poker com você.";
			link.l1 = "É, você tem razão, Helen. Não temos privacidade aqui.";
			link.l1.go = "drinking_game_3";
		break;
		
		case "drinking_game_3":
			dialog.text = "Isso não é a única coisa que está faltando, Charles... Não é um jogo de cartas, mas não se preocupe, aposto que você é um mestre nisso. 'Eu Nunca' — já ouviu falar?";
			link.l1 = "Familiar. De uma vida passada. E você toca com frequência?";
			link.l1.go = "drinking_game_4";
		break;
		
		case "drinking_game_4":
			dialog.text = "Sempre quis tentar, mas nunca tive com quem jogar.";
			link.l1 = "Esse é um jogo bem ousado para o nosso primeiro brinde juntos. Tem certeza?";
			link.l1.go = "drinking_game_5";
			link.l2 = "Aliás, onde está todo mundo? Estamos sozinhos aqui?";
			link.l2.go = "drinking_game_6";
		break;
		
		case "drinking_game_5":
			dialog.text = "Sim, depois dos últimos acontecimentos, preciso aproveitar um pouco a vida. Fazer alguma loucura, sabe?";
			link.l1 = "Não, isso sempre termina mal, Rumba.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Vamos começar! Damas primeiro!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_6":
			dialog.text = "Mandei todos embora - não precisamos deixar estranhos ouvirem.";
			link.l1 = "Não, isso sempre termina mal, Rumba.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Vamos nessa! Damas primeiro!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_refuse":
			dialog.text = "Que pena, mas talvez você tenha razão. Mais uma bebida então?";
			link.l1 = "Vamos começar! Damas primeiro!";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_refuse_1":
			dialog.text = "Já está tudo certo – o quarto no andar de cima é seu. Antes estava ocupado por um oficial francês importante, mas os rapazes do Diabo da Floresta pediram educadamente para ele desocupar. Vai descansar um pouco – não vou deixar você perambulando pela rua, ou pior ainda, indo pro mar, desse jeito.";
			link.l1 = "Sim, senhora!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToTavernRoom");
		break;
		
		case "drinking_game_accept":
			dialog.text = "Ha! Hic! Isso significa que você está começando!";
			link.l1 = "Cuidado, querido! Hmm. Nunca persegui ratos no porão!";
			link.l1.go = "drinking_game_accept_1";
		break;
		
		case "drinking_game_accept_1":
			dialog.text = "Então é assim? Preciso ficar de olho em você! (Bebe)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_2";
		break;
		
		case "drinking_game_accept_2":
			dialog.text = "Brr! Só de lembrar disso... Bem, se prepara, bonitão: eu nunca caí do mastro!";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_3";
		break;
		
		case "drinking_game_accept_3":
			dialog.text = "";
			link.l1 = "Muito bem feito! Permita-me, mademoiselle, brindar a você! (Bebe)";
			link.l1.go = "drinking_game_accept_4";
		break;
		
		case "drinking_game_accept_4":
			dialog.text = "";
			link.l1 = "Eu nunca fui supersticiosa.";
			link.l1.go = "drinking_game_accept_5";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 1;
			SetCamShuttle(loadedLocation);
			SetPitch(0.95);
		break;
		
		case "drinking_game_accept_5":
			dialog.text = "E você ainda se chama de marinheiro! Você sabe muito bem que tipo de gente nós somos. Nunca se sabe o que uma viagem vai trazer, nem quando ou onde vai enxergar terra, se é que vai. Tem que buscar respostas além dos mapas e instrumentos de navegação! À sua saúde! (Bebe)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_6";
		break;
		
		case "drinking_game_accept_6":
			dialog.text = "E as garotas que você pintou pessoalmente... Elas gostaram do resultado?";
			link.l1 = "Eles nem sempre gostavam das pinturas, mas, hum... do resultado – sempre.";
			link.l1.go = "drinking_game_accept_7";
		break;
		
		case "drinking_game_accept_7":
			dialog.text = "Charles! Se a gente tivesse se conhecido naquela época, eu teria atirado em você ou te feito refém por resgate. E, aliás, eu nunca peguei num pincel.";
			link.l1 = "Ei! Bem, isso é totalmente banal. Querida Helen, se eu começar a listar as coisas que você nunca tentou...";
			link.l1.go = "drinking_game_accept_8";
		break;
		
		case "drinking_game_accept_8":
			dialog.text = "Tudo bem, certo, vou jogar limpo. Sua vez, meu capitão.";
			link.l1 = "(Bebe) Hic! Hmm... Nunca tive uma das minhas modelos me acertando na cabeça com a coronha de uma pistola.";
			link.l1.go = "drinking_game_accept_9";
		break;
		
		case "drinking_game_accept_9":
			dialog.text = "(Bebe um gole) Aff. Estamos jogando isso tudo errado, querido. Achei que íamos beber e nos conhecer melhor, mas estamos só trocando farpas e... e... *hic*. Droga!";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_10";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 2;
			SetCamShuttle(loadedLocation);
			SetPitch(0.90);
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "Vamos deixar isso mais interessante! E, de preferência, algo diferente do que estávamos falando uma hora atrás!";
			link.l1 = "Eu nunca acordei em um lugar estranho depois de uma bebedeira.";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "Ai! Droga, Charles! (Bebe)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_11":
			dialog.text = "Eu... Hic... não acredito nisso. Confesso, sou culpada – a pequena Rumba já gostou de uma bebida. Mas nunca estive na prisão!";
			link.l1 = "Como você...?";
			link.l1.go = "drinking_game_accept_12";
		break;
		
		case "drinking_game_accept_12":
			dialog.text = "Hahaha! Beba, beba!";
			link.l1 = "Vou me arrepender disso. (Bebe)";
			
			if (IsCharacterEquippedArtefact(pchar, "totem_01")) {
				link.l1.go = "drinking_game_accept_13";
			} else {
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_LightsOut");
			}
		break;
		
		case "drinking_game_accept_13":
			dialog.text = "Vamos lá, meu querido. A última pergunta e a última chance de me superar!";
			link.l1 = "Não... Eu... Vamos tomar um pouco de ar fresco.";
			link.l1.go = "drinking_game_enough";
			link.l2 = "Já bebi muito, mas nunca assim... Nunca fiquei t-tão bêbado com uma mulher. Juro pela minha p-palavra, b-beber é mesmo um g-grande pecado...";
			link.l2.go = "drinking_game_accept_14";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 3;
			SetCamShuttle(loadedLocation);
			SetPitch(0.85);
		break;
		
		case "drinking_game_enough":
			dialog.text = "Eh!";
			link.l1 = "";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_accept_14":
			dialog.text = "";
			link.l1 = "E-ei...   Você não vai beber?";
			link.l1.go = "drinking_game_accept_15";
		break;
		
		case "drinking_game_accept_15":
			dialog.text = "Ah-ha-ha! Isso é hilário! Você mira alto, meu capitão. Que fique... hic!... claro para você...";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_16";
		break;
		
		case "drinking_game_accept_16":
			dialog.text = "Tenho o azar de viver entre uma tripulação só de homens, então preciso tomar cuidado. Sou uma moça honesta.";
			link.l1 = "F-fico feliz por você, H-Helen.";
			link.l1.go = "drinking_game_accept_17";
		break;
		
		case "drinking_game_accept_17":
			dialog.text = "Você vai ficar ainda mais feliz, porque eu ganhei! Mas, pra ser sincera, nunca fiquei tão bêbada com um homem também.";
			link.l1 = "(Silenciosamente toma um gole) P-para você. Parabéns... h-hic...";
			link.l1.go = "drinking_game_accept_18";
		break;
		
		case "drinking_game_accept_18":
			dialog.text = "Ei, ei, ei! Capitão, pra onde você vai? Ficou ofendido, por acaso?";
			link.l1 = "Eu p-preciso... de uma pausa? Só vou procurar minha e-espada...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_ExitTavern");
		break;
		
		case "drinking_at_svenson":
			dialog.text = "Capitão, está pronto? Não tem mais volta, e se algo der errado, vou te obrigar a se casar comigo.";
			link.l1 = "Ufa! Deixa eu pelo menos recuperar o fôlego! Você tem certeza disso, Helen?";
			link.l1.go = "drinking_at_svenson_1";
		break;
		
		case "drinking_at_svenson_1":
			dialog.text = "Sim, droga, e não fique aí parado feito um poste! Eu preciso me perder, nem que seja só por uma noite!";
			link.l1 = "Receio que depois desta noite, serei eu quem vai querer se perder. Vamos antes que acordemos a cidade inteira.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_EnterSvenson");
		break;
		
		case "drinking_give_key":
			dialog.text = "Cap, take the key and go upstairs. There should be a chest; you probably saw it when Svensson had it. Grab the barrel and head back immediately.";
			link.l1 = "Calma aí, querida, por que eu tenho que roubar seu chefe?";
			link.l1.go = "drinking_give_key_1";
			
			GiveItem2Character(pchar, "key3");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_give_key_1":
			dialog.text = "Don't be silly. I've been here since childhood; if the owners return, I can handle it and cover for you. Come on, don't lower your sail now!";
			link.l1 = "Afiada como uma faca, uma verdadeira contrabandista! Espere aí, vou ser rápida.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GotKey");
		break;
		
		case "drinking_got_whiskey":
			dialog.text = "Entendeu?";
			link.l1 = "Pode apostar! Não é o primeiro baú que esvazio, e com certeza não será o último!";
			link.l1.go = "drinking_got_whiskey_1";
		break;
		
		case "drinking_got_whiskey_1":
			dialog.text = "Estou orgulhosa de você! Haha! Uísque irlandês de primeira, 'Bushmills'! Nunca serviriam uma bebida dessas pra gente na taverna.";
			link.l1 = "Parece bom, mas o Svensson não vai perceber que está faltando?";
			link.l1.go = "drinking_got_whiskey_2";
		break;
		
		case "drinking_got_whiskey_2":
			dialog.text = "Ele vai perceber, com certeza, mas ele mesmo não bebe. Parece que guardou como presente para o amigo pirata dele, o Dodson, e o Dodson ou sumiu ou matou alguém...";
			link.l1 = "Isso é terrível! Um presente desses não pode ser desperdiçado. Pegue o barril e vamos mudar de ares!";
			link.l1.go = "drinking_got_whiskey_3";
		break;
		
		case "drinking_got_whiskey_3":
			dialog.text = "Muito bem dito, capitão. Mas me diga uma coisa – você pegou mais alguma coisa do baú? Seja sincero.";
			if (HelenDrinking_RobbedSvenson()) {
				link.l1 = "Peguei um costume, sabe.";
				link.l1.go = "drinking_got_whiskey_notbelieve";
			}
			
			link.l2 = "Não. Não sei se sou uma pirata, mas com certeza não sou ladra.";
			link.l2.go = "drinking_got_whiskey_believe";
			
			if (HelenDrinking_RobbedSvenson()) {
				link.l2.go = "drinking_got_whiskey_notbelieve";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 2;
				Notification_Approve(false, "Helena");
				pchar.questTemp.HelenDrinking.RobbedSvenson = true;
			}
		break;
		
		case "drinking_got_whiskey_believe":
			dialog.text = "De algum jeito, eu acredito em você... tola que sou!";
			link.l1 = "";
			link.l1.go = "drinking_get_out";
		break;
		
		case "drinking_got_whiskey_notbelieve":
			dialog.text = "Vá e confira se você não pegou nada por engano.";
			link.l1 = "";
			link.l1.go = "exit";
			if (!HelenDrinking_RobbedSvenson()) {
				AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
				TakeItemFromCharacter(pchar, "cask_whisky");
				sld = ItemsFromID("cask_whisky");
				sld.price = sld.pricebak;
				DeleteAttribute(sld, "pricebak");
			}
			
			NextDiag.TempNode = "drinking_got_whiskey_notbelieve";
		break;
		
		case "drinking_get_out":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
			TakeItemFromCharacter(pchar, "cask_whisky");
			sld = ItemsFromID("cask_whisky");
			sld.price = sld.pricebak;
			DeleteAttribute(sld, "pricebak");
		break;
		
		case "drinking_at_fort":
			dialog.text = "Ei, ei, querido! Concentre-se! Meu rosto, beijado pela brisa do mar, está bem aqui!";
			link.l1 = "Ufa, olha, seu traje é realmente algo! Deve ter economizado muito tecido. E eu... hic! Já vi muita coisa! Mas isso... Mas isso é a melhor coisa que já vi na vida.";
			link.l1.go = "drinking_at_fort_1";
			locCameraFromToPos(-1.65, 44.45, 76.64, true, -5.93, 42.10, 70.13);
		break;
		
		case "drinking_at_fort_1":
			dialog.text = "Todo mundo diz isso, mas por algum motivo, eu acredito em você! Você está falando sério mesmo?";
			link.l1 = "Bem, é claro, isso realmente valoriza sua silhueta, embora...";
			link.l1.go = "drinking_at_fort_2";
		break;
		
		case "drinking_at_fort_2":
			dialog.text = "Ah, agora você estragou tudo!";
			link.l1 = "... embora eu não tenha dúvidas de que entre o povo comum, isso desperte admiração!";
			link.l1.go = "drinking_at_fort_3";
		break;
		
		case "drinking_at_fort_3":
			dialog.text = "Fico realmente impressionada com esse estranho hábito tão comum, até entre os menos comuns, de usar roupas pesadas europeias nesse calor. Isso faz nossas vilas parecerem ainda mais engraçadas... Eu gosto da minha roupa, Charles. Com ela, me sinto bonita, e isso é importante para uma mulher.";
			link.l1 = "Você continuaria linda mesmo sem essa roupa, Helen.";
			link.l1.go = "drinking_at_fort_4";
		break;
		
		case "drinking_at_fort_4":
			dialog.text = "Cuidado, meu capitão! Dizer coisas tão doces pode corromper uma pobre garota!";
			link.l1 = "Se ela não se opõe, então eu também não me oponho.";
			link.l1.go = "drinking_at_fort_5";
		break;
		
		case "drinking_at_fort_5":
			dialog.text = "Ha-ha! Melhor me perguntar outra coisa. Gosto quando você fica curioso.";
			link.l1 = "Então vamos aproveitar para perguntar sobre o seu traje. Não acredito que esses marujos levem a sério um capitão vestido assim.";
			link.l1.go = "drinking_at_fort_6";
		break;
		
		case "drinking_at_fort_6":
			dialog.text = "E eu não acredito que esses marujos, no geral, consigam aceitar uma mulher como capitã, então minha roupa provavelmente só piorou as coisas. Ou talvez nem tenha dado tempo, já que é algo novo. Eu mesma costurei!\nAh-ha-ha! Antes eu usava uma daquelas... como se chama? Nosso exército ainda usa! Brr... Só de ver uma daquelas agora já me dá enjoo.";
			link.l1 = "Uniformes?";
			link.l1.go = "drinking_at_fort_7";
		break;
		
		case "drinking_at_fort_7":
			dialog.text = "Ah, isso mesmo, um uniforme! Um uniforme vermelho! Igual ao que aquele homem está vestindo.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.GenQuest.BlockDialogCamera = true;
			AddDialogExitQuestFunction("HelenDrinking_OfficerAtFort");
		break;
		
		case "drinking_at_fort_7_1":
			dialog.text = "Ah, me desculpe, Major, deixa eu te oferecer um bom uísque irlandês como um... hic!... pedido de desculpas.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog2");
		break;
		
		case "drinking_at_fort_7_2":
			dialog.text = "O Charles não vai se meter em encrenca, vai, Major? Diz que não vai, por favorzinho!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog4");
		break;
		
		case "drinking_at_fort_8":
			dialog.text = "Que alegria! Vamos tomar um drinque!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToVillage");
		break;
		
		case "drinking_at_miskito":
			dialog.text = "Aff. Olha só o que eu arrumei!";
			link.l1 = "Helen... Você está pensando em usar isso... para se animar?!.. Nem pense nisso! A datura pode dominar uma pessoa por completo, sugar todas as forças, esmagar a vontade! Quando você percebe, já virou um morto-vivo... e logo depois, um morto de verdade...";
			link.l1.go = "drinking_at_miskito_1";
		break;
		
		case "drinking_at_miskito_1":
			dialog.text = "Charles, mas... agora...";
			link.l1 = "Sem mas. Desculpe por ser dura, mas isso não é brincadeira. Vou tirar isso de você. Não acredito no que estava pensando... Aqui, beba isso e volte ao normal.";
			link.l1.go = "drinking_at_miskito_2";
			
			GiveItem2Character(pchar, "cannabis7");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_at_miskito_2":
			dialog.text = "Me desculpe, Charles. Você está absolutamente certo, eu sei. Foi uma fraqueza momentânea. Não vai acontecer de novo. Obrigada por me salvar da tentação do diabo...";
			link.l1 = "Vamos deixar isso pra lá... Agora, me conta, como você conseguiu ganhar respeito na cidade, manter boas relações com os oficiais da guarnição e ainda fazer amizade com os nativos?";
			link.l1.go = "drinking_at_miskito_3";
		break;
		
		case "drinking_at_miskito_3":
			dialog.text = "Eles respeitam o Svensson, e um pouco desse respeito acaba recaindo sobre mim. Nossa pequena cidade só sobrevive graças aos acordos do Jan. Ele divide uma parte dos lucros das plantações de cacau com os casacas vermelhas, e os Miskitos devem toda a sua sobrevivência a ele.";
			link.l1 = "Como isso aconteceu?";
			link.l1.go = "drinking_at_miskito_4";
		break;
		
		case "drinking_at_miskito_4":
			dialog.text = "Quando os castelhanos estavam no comando, eles não incomodavam muito os índios. Mas depois que expulsaram os nobres Hidalgos, nosso povo resolveu tomar conta das florestas locais. Jan resolveu a situação de forma bem decisiva naquela época – até mandou gente para Londres! Claro, não foi por bondade: extrair cacau numa floresta onde cada arbusto te odeia é uma tarefa impossível. Mas agora, os índios não só ajudam Jan a contrabandear de Porto Bello para Blueweld, como também derrubam suas próprias florestas por uma ninharia. Bravo, Diabo da Floresta, bravo!";
			link.l1 = "Parece que você não aprova totalmente os métodos dele.";
			link.l1.go = "drinking_at_miskito_5";
		break;
		
		case "drinking_at_miskito_5":
			dialog.text = "Eu amo e respeito o povo Miskito, mas também respeito a estratégia do Jan. Não vivemos em um conto de fadas, meu capitão.";
			link.l1 = "Hm... Vejo que sua relação com o Svensson é mais complicada do que parece à primeira vista...";
			link.l1.go = "drinking_at_miskito_6";
		break;
		
		case "drinking_at_miskito_6":
			dialog.text = "Even more than you know. His wife has a good reason to be venomous towards me... Jan has been eyeing me since I was about fifteen. It was around the time I started walking the decks of the Rainbow as an equal, and apparently, something clicked in the Forest Devil's mind back then... But I've said too much, my captain. Let's not delve into this topic; gossiping about our patron is not very decent.";
			link.l1 = "Então vamos mudar de assunto. Eu queria dizer que você claramente se encaixa bem com esse grupo, e eles já te consideram um dos deles.";
			link.l1.go = "drinking_at_miskito_7";
		break;
		
		case "drinking_at_miskito_7":
			dialog.text = "Acontece que é muito mais fácil pra mim estar na companhia de índios, ciganos e outros desajustados decentes. Os ensopados da minha mãe, as fogueiras na praia, a prancha do Arco-Íris – construí pra mim um mundinho aconchegante, Capitão. Pena que tudo desabou justo quando achei que já tinha entendido como as coisas funcionavam.";
			link.l1 = "O barril está quase vazio... Mais uma rodada?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToShipyard");
		break;
		
		case "drinking_at_perlas":
			dialog.text = "É tão bom... Fico feliz que você tenha aceitado passar um tempo comigo, Capitão. Eu realmente estava precisando disso. Acho que você também.";
			link.l1 = "Sim, faz tempo que não relaxo assim. Vai ser algo para se lembrar!";
			link.l1.go = "drinking_at_perlas_1";
		break;
		
		case "drinking_at_perlas_1":
			dialog.text = "Você provavelmente está pensando Deus sabe o quê sobre mim agora. Eu sou uma pessoa muito reservada por natureza, Charles. Eu só... droga, eu só queria me sentir viva! Só queria conversar com alguém!";
			link.l1 = "E a Gladys? E o Jan?";
			link.l1.go = "drinking_at_perlas_2";
		break;
		
		case "drinking_at_perlas_2":
			dialog.text = "Tudo o que mamãe faz é chorar, e o Jan parece outra pessoa agora. Talvez seja coisa da minha cabeça, não sei, mas é como se ele tivesse vergonha de mim agora? Me perdoe, eu... (fungando).\nJá chega, garota. Desculpe, me deixei levar um pouco.";
			link.l1 = "Não precisa se desculpar. Eu entendo tudo, ou pelo menos acho que entendo.";
			link.l1.go = "drinking_at_perlas_3";
		break;
		
		case "drinking_at_perlas_3":
			dialog.text = "Estou dizendo tudo isso porque acabamos de nos conhecer, e não costumo ser tão aberta nem com quem conheço há muito tempo. Me chamam de Rumba, supostamente por causa do meu jeito, mas como pode ver, não faz o menor sentido. Já acabou a bebida?";
			link.l1 = "Faz um tempo, e o dia já está amanhecendo.";
			link.l1.go = "drinking_at_perlas_4";
		break;
		
		case "drinking_at_perlas_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend") && !CheckAttribute(pchar, "questTemp.HelenDrinking.RobbedSvenson")) {
				dialog.text = "Me desculpe, meu capitão, se você esperava outra coisa para nossa noite. Eu... eu não posso. Não hoje.";
			} else {
				dialog.text = "Obrigada pela noite, Capitão. Quem sabe, talvez a gente repita isso algum dia.";
			}
			link.l1 = "Claro, Helen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_PoormanTalk");
		break;
		
		case "ambush":
			dialog.text = "Obrigada por me trazer aqui, capitão. Vamos dar uma olhada, certo? Vamos conhecer minha herança.";
			link.l1 = "Você já não esteve aqui antes?";
			link.l1.go = "ambush_1";
		break;
		
		case "ambush_1":
			dialog.text = "No, it's quite a ways away; besides, I'm no pirate. This place has never been particularly fascinating, and after they killed Blaise... It's better not to linger here.";
			link.l1 = "Não vamos. Já me arrependo de ter te trazido aqui.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPrepareAmbush");
		break;
		
		case "after_ambush":
			switch (pchar.questTemp.HelenDrinking.IslaTesoroAmbush) {
				case "A":
					if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB") && !CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC")) {
						dialog.text = "Did you have to, Captain? Why so quick to fight? Well, one should not just a winner, I guess. Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
						pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
						Notification_Approve(false, "Helena");
					} else {
						dialog.text = "Kudos, my Captain, for trying to resolve the issue wisely before getting into a fight. Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
					}
					
					link.l1 = "E aquele navio enorme encalhado na praia?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "B":
					dialog.text = "You skillfully fooled those fools, my Captain! I almost burst out laughing, honest! Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					Notification_Approve(true, "Helena");
					
					link.l1 = "E aquele navio enorme encalhado na praia?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "C":
					dialog.text = "Calma, deixa uma garota recuperar o fôlego! É você mesmo, Charlie Prince?";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					Notification_Approve(true, "Helena");
					
					link.l1 = "Houve um tempo assim na minha vida, sim. Está impressionado?";
					link.l1.go = "after_ambush_c";
				break;
			}
		break;
		
		case "after_ambush_1":
			dialog.text = "Sim, você tem razão. Eu adoraria explorar, mas para ser sincera, Charles, estou um pouco assustada com isso. Vamos.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroGoToResidence");
		break;
		
		case "after_ambush_c":
			dialog.text = "Meu Deus, sim! Depois me conta tudo, tá bom? Porque só ouvi histórias... histórias bem indecentes!";
			link.l1 = "Eu vou te contar tudo... quase tudo.";
			link.l1.go = "after_ambush_c_1";
		break;
		
		case "after_ambush_c_1":
			dialog.text = "I'll be waiting eagerly! Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
			link.l1 = "E aquele navio enorme puxado para a praia?";
			link.l1.go = "after_ambush_1";
		break;
		
		case "ambush_inresidence":
			dialog.text = "Um cubículo apertado e frio, com exigências absurdas. Já me sinto como se estivesse numa armadilha!";
			link.l1 = "Vejo que até agora você não está satisfeito com a possível propriedade?";
			link.l1.go = "ambush_inresidence_1";
		break;
		
		case "ambush_inresidence_1":
			dialog.text = "Não, Charles. Talvez eu seja exigente demais, mas por enquanto, isso representa tudo o que eu temo e detesto. Espero conseguir alugá-lo... Embora eu nem saiba onde vou gastar esse dinheiro.";
			link.l1 = "Não subestime o valor do aluguel. Eu não pago aluguel, e muitas vezes preciso dar um jeito de pagar minha tripulação. Você vai comprar um novo navio, 'Arco-íris II' – soa bem, não acha?!";
			link.l1.go = "ambush_inresidence_sea";
			link.l2 = "Existem muitas maneiras de gastar dinheiro consigo mesma. Comece com uma espada personalizada e uma garrafa de vinho excelente. Se presenteie, Helen, você merece.";
			link.l2.go = "ambush_inresidence_land";
		break;
		
		case "ambush_inresidence_sea":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "sea") {
				dialog.text = "Obrigada, meu capitão. Fico feliz em ouvir isso. É ainda melhor escutar pela segunda vez. Você me conhece bem.";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
				Notification_Approve(true, "Helena");
			} else {
				dialog.text = "Obrigada, meu capitão. Fico feliz em ouvir isso.";
			}
			
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_COMMERCE, 5);
			AddCharacterSkill(sld, SKILL_ACCURACY, 5);
			AddCharacterSkill(sld, SKILL_CANNONS, 5);
			AddCharacterSkill(sld, SKILL_SAILING, 5);
			AddCharacterSkill(sld, SKILL_REPAIR, 5);
			AddCharacterSkill(sld, SKILL_GRAPPLING, 5);
			AddCharacterSkill(sld, SKILL_DEFENCE, 5);
		break;
		
		case "ambush_inresidence_land":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "land") {
				dialog.text = "Você acha que eu mereço? Nunca gastei dinheiro com essas bobagens, mas acho que sempre há uma primeira vez para tudo. Vejo que você não vai desistir de tentar me fazer esquecer do mar, hein, Capitão? Talvez você esteja certo...";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 3;
				Notification_Approve(false, "Helena");
			} else {
				dialog.text = "Você acha que eu mereço? Nunca gastei dinheiro com essas bobagens, mas acho que sempre tem uma primeira vez para tudo.";
			}
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_F_LIGHT, 5);
			AddCharacterSkill(sld, SKILL_FENCING, 5);
			AddCharacterSkill(sld, SKILL_F_HEAVY, 5);
			AddCharacterSkill(sld, SKILL_PISTOL, 5);
			AddCharacterSkill(sld, SKILL_FORTUNE, 5);
			AddCharacterSkill(sld, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(sld, SKILL_SNEAK, 5);
		break;
		
		case "ambush_inresidence_2":
			dialog.text = "De qualquer forma, a inspeção está concluída. Não parece haver nada de valor aqui – a ralé já conseguiu saquear tudo, e tenho certeza de que o segundo andar está na mesma situação.";
			link.l1 = "É como se você tivesse mudado, Helen. Da última vez que estivemos juntos, você era... não sei, mais aberta?";
			link.l1.go = "ambush_inresidence_3";
		break;
		
		case "ambush_inresidence_3":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Nada mudou, meu capitão, mas muita coisa caiu sobre os ombros de uma pobre garota, haha! Não quis te ofender. Só preciso pensar em muita coisa agora. Sabe, essas reviravoltas na vida não acontecem todo dia. E ainda temos muito tempo juntos!";
				link.l1 = "Que bom ouvir isso! Vamos sair daqui.";
			} else {
				dialog.text = "Much has changed, Captain. I'm afraid I have to be more mature now and look at life differently. It's not a fairy tale about a princess and inheritance; it's big politics, and I still have to realize my place in it. And my family's place too.";
				link.l1 = "Fico feliz que esclarecemos isso. Vamos sair daqui.";
			}
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroBeforeExit");
		break;
		
		case "ambush_inresidence_wait":
			dialog.text = "Sim?";
			if (CheckCharacterItem(pchar, "pirate_cutlass")) {
				link.l1 = "Ei, nem tudo foi saqueado! Olha, Helen! Este sabre parece ser lendário, já que até a ralé local hesitou em pegá-lo.";
				link.l1.go = "ambush_inresidence_give_cutlass";
			}
			
			link.l2 = "Não, nada.";
			link.l2.go = "exit";
			
			NextDiag.TempNode = "ambush_inresidence_wait";
		break;
		
		case "ambush_inresidence_give_cutlass":
			dialog.text = "Por todos os mares, isso é... a lendária cutelo do próprio Blaise! Os piratas o respeitavam tanto que não ousaram tirar o cutelo de sua casa, nem mesmo após sua morte. Pegaram o dinheiro e os objetos de valor, claro, mas até mesmo futuros enforcados ainda têm um resto de honra...";
			link.l1 = "It looks like someone is clearly tidying up here. As if the owner will come back... This is not a home; it's a memorial!";
			link.l1.go = "ambush_inresidence_give_cutlass_1";
		break;
		
		case "ambush_inresidence_give_cutlass_1":
			dialog.text = "Obrigada pela observação perspicaz, Charles. Você acabou de estragar esse lugar pra mim, ha-ha!";
			link.l1 = "Acho que este sabre agora é seu. Blaise é o seu chamado tio...";
			link.l1.go = "ambush_inresidence_give_cutlass_2";
		break;
		
		case "ambush_inresidence_give_cutlass_2":
			dialog.text = "Você está tornando tudo ainda mais assustador, meu capitão. Eu... Eu não posso. Tenho medo de que, se eu aceitar, minha vida passada acabe de vez.";
			link.l1 = "Então aceite, não como parte da herança, mas como um presente de um homem bonito.";
			link.l1.go = "ambush_inresidence_give_cutlass_3";
		break;
		
		case "ambush_inresidence_give_cutlass_3":
			dialog.text = "Quem será? Brincadeira! Obrigada por afastar meus pensamentos sombrios, capitão. Prometo que vou treinar muito para me tornar digna desta lâmina!";
			link.l1 = "Você merece a melhor arma, Helen. Vamos, já terminamos aqui.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "give_cutlass":
			dialog.text = "Meu Deus do céu, essa é... a lendária cutelo do próprio Blaise! Os piratas o respeitavam tanto que nem depois da morte dele ousaram tirar o sabre de sua casa. Claro, levaram o dinheiro e os objetos de valor, mas até mesmo futuros enforcados ainda têm um resto de honra\nEu... eu não posso. Tenho medo de que, se eu aceitar, minha vida passada acabe de vez.";
			link.l1 = "Então aceite isso não como parte da herança, mas como um presente de um homem bonito.";
			link.l1.go = "give_cutlass_1";
		break;
		
		case "give_cutlass_1":
			dialog.text = "Quem será? Brincadeira! Obrigada por afastar meus pensamentos sombrios, meu capitão.";
			link.l1 = "Você merece a melhor arma, Helen. Fico feliz que tenha gostado.";
			link.l1.go = "give_cutlass_2";
		break;
		
		case "give_cutlass_2":
			dialog.text = "Prometo que vou treinar muito para me tornar digno desta lâmina!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "arrive":
			dialog.text = "Meu capitão! Charlie!";
			link.l1 = "Charlie? Isso é novo! Que bom te ver, querido.";
			link.l1.go = "arrive_1";
		break;

		case "arrive_1":
			dialog.text = "Eu escorreguei sem querer, ha! Também fico feliz em te ver...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog1");
		break;

		case "arrive_2":
			dialog.text = "Tanto faz para a solidariedade entre irmãs! Meu capitão, eu... eu fiquei realmente preocupada e senti tanto a sua falta!";
			link.l1 = "Então por que você teve que correr pra casa?";
			link.l1.go = "arrive_3";
		break;

		case "arrive_3":
			dialog.text = "Ah... Certo! Tenho um presentinho pra você, aqui!";
			link.l1 = "Três amuletos... Helen, por quê? Você queria me seguir?";
			link.l1.go = "arrive_4";
			
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Indian);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Amulet);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Obereg);
		break;

		case "arrive_4":
			dialog.text = "Vem aqui, seu tolo!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FirstKiss");
		break;

		case "after_kiss":
			dialog.text = "Só não ouse estragar esse momento – sonhei com ele a minha vida inteira!";
			link.l1 = "Eu não vou, Helen.";
			link.l1.go = "after_kiss_a";
			link.l2 = "Você passou a vida inteira esperando me conhecer? Fico lisonjeada!";
			link.l2.go = "after_kiss_b";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l3 = "Helen, tem uma coisa... Na Ilha da Justiça, conheci uma mulher, e...";
				link.l3.go = "after_kiss_c";
			}
			locCameraFromToPos(-19.00, 1.56, 19.07, true, -11.19, -0.90, 17.49);
		break;
		
		case "after_kiss_a":
			dialog.text = "Isso mesmo! Você vai me contar tudo, tudo! Vou te esperar no navio, Capitão!";
			link.l1 = "Espere!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_b":
			dialog.text = "Idiota! Quer me ofender? Tudo bem, estou ofendida! Ha-ha! Vou para o navio por enquanto, antes que o Danny zombe ainda mais de mim...";
			link.l1 = "Espere!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_c":
			dialog.text = "Idiota! Eu pedi pra você não estragar o momento! Conheceu... bem, conheceu – ainda não vejo um anel no seu dedo. Mas não pense que vai escapar dessa – quero ouvir essa história em detalhes quando voltar pro navio.";
			link.l1 = "Espere!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "loot_good":
			dialog.text = "Meu capitão, quais são as novidades? Pelo seu rosto pálido, já vejo que o advogado resolveu te arrumar mais problemas em vez de ajudar.";
			link.l1 = "Você tem razão, Helen. Loxley exigiu um adiantamento generoso, e o caso em si vai me custar uma bela quantia. Vou lá dar uma sacudida no Jan – já chega! Parece que a Irmandade resolveu jogar todas as despesas nas minhas costas!";
			link.l1.go = "loot_good_1";
		break;
		
		case "loot_good_1":
			dialog.text = "Não há maldade nisso, Charles. Eles são assim mesmo – não movem um dedo a menos que seja necessário. Tenho certeza de que Jan vai te ajudar, e eu também não vou ficar parada.";
			link.l1 = "Eu sei, Helen. Me diga o que você está pensando.";
			link.l1.go = "loot_good_2";
		break;
		
		case "loot_good_2":
			dialog.text = "Eu trabalhava para o Jan — contrabandeando madeira valiosa por todo o Maine. Mas sou uma mulher esperta, e sempre guardava algo para mim nessas viagens.";
			link.l1 = "E o Jan nunca descobriu? Esperta!";
			link.l1.go = "loot_good_3";
		break;
		
		case "loot_good_3":
			dialog.text = "Eu tinha um bom tesoureiro. Resumindo, juntei uma quantia razoável de dinheiro e escondi não muito longe daqui. Você vai ver o Jan agora? Então vamos passar por San Juan del Norte. Tem uma caverna ali perto, e só vamos precisar de alguns marinheiros para ajudar, assim não precisamos carregar tudo sozinhos.";
			link.l1 = "Você já entendeu tudo, não é? Obrigado, Helen, vamos visitar com certeza se tivermos tempo.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "loot_bad":
			dialog.text = "Meu capitão, quais são as novidades? Pelo seu rosto pálido, já vejo que o advogado resolveu te arrumar mais problemas em vez de ajudar.";
			link.l1 = "Você tem razão, Helen. Loxley exigiu um adiantamento generoso, e esse caso vai me custar uma bela quantia. Vou lá sacudir o Jan – já chega! Parece que a Irmandade resolveu jogar todas as despesas nas minhas costas!";
			link.l1.go = "loot_bad_1";
		break;
		
		case "loot_bad_1":
			dialog.text = "Você achou que estava em um conto de fadas? Não se preocupe, estamos todos no mesmo barco aqui, e eu vou te ajudar. Afinal, tenho direito a uma herança, não é?";
			link.l1 = "É verdade... Me conta, o que está passando pela sua cabeça!";
			link.l1.go = "loot_bad_2";
		break;
		
		case "loot_bad_2":
			dialog.text = "Tenho algo escondido em San Juan del Norte. Tem uma caverna por perto – só precisamos reunir alguns marinheiros para não carregarmos tudo sozinhos.";
			link.l1 = "Você já entendeu tudo, não é? Obrigado, Helen, com certeza vamos visitar se tivermos tempo.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "shdn":
			dialog.text = "É isso, Charles! Mas você vai ter que ir sozinho – eu detesto cavernas!";
			link.l1 = "Como qualquer lugar fechado, eu sei, Helen. Espere por mim aqui.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoForLoot");
		break;
		
		case "shdn_ambush":
			dialog.text = "Temos um problema! Um grupo de soldados está vindo para cá, e eles parecem ameaçadores. Cuidado, Charles, esses não são apenas guardas costeiros comuns – tem um oficial francês entre eles! Eu te imploro, só não faça nenhuma besteira!";
			link.l1 = "Quando foi que eu já fiz alguma besteira?!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SpawnAmbushSoldiers");
		break;
		
		case "shdn_ambush_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Ha, a segunda opção parece mais tentadora, mas espero que você não seja convencido demais, Charles?";
			} else {
				dialog.text = "Não posso dizer que estou surpresa, Charles...";
			}
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog1");
		break;
		
		case "shdn_ambush_2":
			dialog.text = "Terminou? Agora é minha vez de falar!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_HelenKillFrancois");
		break;
		
		case "shdn_ambush_3":
			dialog.text = "Meu nome é Helen MacArthur! Capitão, você sabe quem eu sou e para quem trabalho! Avise seus homens, especialmente aquele idiota metido estirado no chão, sobre o resultado de hoje, que vou anunciar agora!";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "richard");
			sld = CharacterFromID("HelenDrinking_Richard");
			CharacterTurnByChr(sld, npchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath2");
		break;
		
		case "shdn_ambush_4":
			dialog.text = "Protestar? Não me importo se você escrever até para o próprio Cromwell. Primeiro, Monsieur de Maure não perdeu sua honra hoje.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_5";
			CharacterTurnToLoc(npchar, "quest", "richard");
		break;
		
		case "shdn_ambush_5":
			dialog.text = "Segundo, o coronel de Tavann levou um tiro de uma moça vestida de forma bem provocante por chamá-la de prostituta.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_6";
		break;
		
		case "shdn_ambush_6":
			dialog.text = "Terceiro, você retira imediatamente seus soldados e esquece o que aconteceu, a menos que queira que o Diabo da Floresta fique sabendo disso.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_7";
		break;
		
		case "shdn_ambush_7":
			locCameraSleep(false);
			dialog.text = "Sem perguntas, entendi. Tenha um bom dia, Capitão.";
			link.l1 = "Meu Deus, Helen, você está pegando fogo!";
			link.l1.go = "shdn_ambush_8";
		break;
		
		case "shdn_ambush_8":
			dialog.text = "Depois, Charles. Vamos sair daqui antes que eles se recuperem do choque. Eu também estou tremendo toda. Podemos conversar em Blueweld?";
			link.l1 = "Combinado.";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, pchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath3");
		break;
		
		case "duel_victory":
			dialog.text = "Vamos sair daqui antes que eles se recuperem do choque. Ainda precisamos recuperar o pau-ferro, lembra? Podemos conversar em Blueweld.";
			link.l1 = "Nem uma palavra de parabéns? Tudo bem, vamos logo.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory1");
		break;
		
		case "after_cave":
			dialog.text = "Finalmente, em casa...";
			link.l1 = "O que você acha do que aconteceu?";
			link.l1.go = "after_cave_1";
		break;
		
		case "after_cave_1":
			dialog.text = "Eu não entendo duelos. Uma diversão masculina, que geralmente termina com dois cadáveres e, em um dia de sorte, até mais. E honra... Acredito que a verdadeira honra está no desejo de evitar o conflito até o último instante, já que raramente vale a pena. Ha! Olha só pra mim — falando besteira!";
			link.l1 = "É uma perspectiva interessante, Helen. Mas nem todos concordariam com isso.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Duel")) {
				link.l1.go = "after_cave_duel";
			} else {
				link.l1.go = "after_cave_notduel";
			}
		break;
		
		case "after_cave_duel":
			dialog.text = "Uma pena que você caiu na armadilha deles. O coronel estava claramente obcecado, e o resto só queria um pouco de espetáculo e assunto para fofoca. Bem, não vou ficar te lembrando disso – você já passou por bastante hoje.";
			link.l1 = "Sim, depois dos duelos, sempre fica uma sensação de vazio. Já chega de aventura por hoje. O que você quer fazer agora?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_notduel":
			dialog.text = "Argh! Eu só queria dizer que estou orgulhosa de nós. Você mostrou muita coragem hoje, meu capitão. Não se deixou levar pelo pânico da tripulação, que só queria te dar ordens pela primeira vez. Você se manteve firme diante da arrogância do uniforme vermelho e da obsessão do azul. O coronel claramente estava procurando a morte, mas acabou só com um ferimento num lugar bem inconveniente, haha!";
			link.l1 = "Obrigada, Helen. Você nos tirou do perigo com maestria, como uma verdadeira oficial da marinha. Está orgulhosa de si mesma?";
			link.l1.go = "after_cave_notduel_1";
		break;
		
		case "after_cave_notduel_1":
			dialog.text = "Sim, eu precisava disso. Só é uma pena que fosse um uniforme azul, e não um vermelho, mas pelo menos quem o vestia teve o que merecia.";
			link.l1 = "Essa pessoa realmente não importa, eu admito. Já tivemos aventuras suficientes por hoje. O que você gostaria de fazer agora?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_mild":
			dialog.text = "Estou indo para casa, meu capitão. Senti falta da minha mo... Gladys. Pena que ela está em casa agora, senão eu teria te convidado para ir junto!";
			link.l1 = "De fato, que pena!";
			link.l1.go = "after_cave_mild_1";
		break;
		
		case "after_cave_mild_1":
			dialog.text = "Não fique assim tão chateado. Logo, meu querido. Enquanto isso...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "Hmm, este aqui está ainda melhor do que o nosso primeiro. Lembra? Perto do ídolo?";
				link.l1 = "Isso não é algo que se esquece, querido.";
				link.l1.go = "after_second_kiss_1";
			} else {
				dialog.text = "Só não ouse estragar esse momento – eu esperei por ele a vida inteira!";
				link.l1 = "Eu não vou, Helen.";
				link.l1.go = "after_second_kiss_a";
				link.l2 = "Você passou a vida inteira esperando para me conhecer? Fico lisonjeada!";
				link.l2.go = "after_second_kiss_b";
			}
		break;
		
		case "after_second_kiss_1":
			dialog.text = "Oh! Se controla, garota! Até a próxima, meu capitão.";
			link.l1 = "Até logo, Helen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_a":
			dialog.text = "Isso mesmo! Logo a gente se vê, meu capitão.";
			link.l1 = "Até a próxima, Helen. Meu Deus, que mulher...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_b":
			dialog.text = "Idiota! Quer me ofender? Tudo bem, estou ofendida! Ha-ha! Logo nos veremos, meu capitão.";
			link.l1 = "Até a próxima, Helen. Meu Deus, que mulher...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_cave_cold":
			dialog.text = "Estou indo para casa, capitão. Imagino que a questão do dinheiro com o advogado já está resolvida? Temos grandes desafios pela frente, então vamos tentar evitar confusão daqui pra frente. Os problemas vão nos encontrar de qualquer jeito.";
			link.l1 = "Sério mesmo?";
			link.l1.go = "after_cave_cold_1";
		break;
		
		case "after_cave_cold_1":
			dialog.text = "Desculpe a franqueza, capitão. Meu destino também está sendo decidido agora, sabia?";
			link.l1 = "Eu sei, vou tentar lidar com isso da forma mais digna possível. Te vejo no navio, Helen.";
			link.l1.go = "after_cave_cold_2";
		break;
		
		case "after_cave_cold_2":
			dialog.text = "Sim, sim, capitão!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveCold");
		break;
		
		case "after_cave_lewd":
			dialog.text = "O que vem agora? Eu te mostro.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss1":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "Hmm, esse aqui está ainda melhor que o primeiro. Lembra? Perto do ídolo?";
				link.l1 = "Isso não é algo que se esquece, querido.";
				link.l1.go = "after_second_kiss1_1";
			} else {
				dialog.text = "Só não ouse estragar esse momento – eu esperei por ele a minha vida inteira!";
				link.l1 = "Eu não vou, Helen.";
				link.l1.go = "after_second_kiss1_a";
				link.l2 = "Você passou a vida inteira esperando me conhecer? Fico lisonjeada!";
				link.l2.go = "after_second_kiss1_b";
			}
		break;
		
		case "after_second_kiss1_1":
			dialog.text = "Isso mesmo! Que surpresa! A Gladys não está em casa agora. Quer entrar?";
			link.l1 = "Me convidando para ir até aí? E o que vamos fazer?";
			link.l1.go = "after_cave_lewd_accept";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l2 = "Não, Helen. Outra mulher está me esperando na Ilha da Justiça. Eu não posso fazer isso com ela.";
				link.l2.go = "after_cave_lewd_refuse_mary";
			}
			link.l3 = "Outra hora, meu querido. Eu realmente quero, mas hoje quase acabou comigo. Vamos nos encontrar e compensar o tempo perdido em dobro.";
			link.l3.go = "after_cave_lewd_refuse_head";
		break;
		
		case "after_second_kiss1_a":
			dialog.text = "Isso mesmo! Pode apostar! A Gladys não está em casa agora. Quer entrar?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "Não, Helen. Outra mulher está me esperando na Ilha da Justiça. Eu não posso fazer isso com ela.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "Outra hora, meu querido. Eu quero muito, mas hoje quase acabou comigo. Vamos nos encontrar e compensar o tempo perdido em dobro.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "Me convidando para entrar? E o que vamos fazer?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_second_kiss1_b":
			dialog.text = "Idiota! Quer me ofender? Muito bem, estou ofendida! Ha-ha! Vai ter que se redimir, meu capitão. Pois bem! A Gladys não está em casa agora. Quer entrar?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "Não, Helen. Outra mulher me espera na Ilha da Justiça. Não posso fazer isso com ela.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "Outra hora, meu querido. Eu realmente quero, mas hoje quase acabou comigo. Vamos nos encontrar e compensar o tempo perdido em dobro.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "Me convidando para ir até aí? E o que vamos fazer?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_cave_lewd_refuse_mary":
			dialog.text = "Ah, então eu não sou habilidosa o bastante na arte da sedução? E ela é? Quem é ela?";
			link.l1 = "O nome dela é Mary Casper, e eu a amo.";
			link.l1.go = "after_cave_lewd_refuse_mary_1";
		break;
		
		case "after_cave_lewd_refuse_mary_1":
			dialog.text = "Aquela ruiva de uniforme vermelho? De uniforme vermelho... Bem, se eu precisava de um sinal, aí está. Não era pra ser. E não se preocupe, capitão, isso não vai afetar meu trabalho no seu navio.";
			link.l1 = "Desculpe, Helen.";
			link.l1.go = "exit";
			
			pchar.questTemp.HelenDrinking.Mary = true;
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMary");
		break;
		
		case "after_cave_lewd_refuse_head":
			dialog.text = "Oh, meu capitão! É perigoso deixar uma mulher nesse estado! Vou cobrar sua palavra, agora vá... Preciso ficar sozinha e tentar lidar com meu problema... do meu jeito! Te vejo no navio!";
			link.l1 = "Que garota!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMild");
		break;
		
		case "after_cave_lewd_accept":
			dialog.text = "Não se preocupe, meu querido, eu vou te guiar se você se perder.";
			link.l1 = "Então... vamos em frente!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveAccept");
		break;
		
		case "after_cave_bedroom":
			dialog.text = "Não diga nada, eu te imploro.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex1");
		break;
		
		case "after_cave_sex":
			dialog.text = "... claro, até hoje, meu entendimento desse assunto vinha só das conversas vulgares da tripulação do 'Arco-Íris', se é que dá pra chamar aquilo de conversa, claro.";
			link.l1 = "E como foi? A realidade correspondeu às suas expectativas?";
			link.l1.go = "after_cave_sex_1";
		break;
		
		case "after_cave_sex_1":
			dialog.text = "Eu gostei muito, mas sinto que ainda não vivi tudo o que podia. E como...";
			link.l1 = "Deixe-me te mostrar! Vamos continuar?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex2");
		break;
		
		case "after_cave_sex_again":
			dialog.text = "Ah, agora entendi! Foi simplesmente maravilhoso, meu capitão!";
			link.l1 = "Você realmente me surpreendeu, para dizer o mínimo!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysEnter");
		break;
		
		case "after_cave_gladys":
			dialog.text = "Ah-ha-ha! Essa foi boa, com certeza! Agora ela vai tapar os ouvidos com cera ou correr pro topo mais alto do forte!";
			link.l1 = "Isso foi inesperado, mas muito engraçado, ah-ha-ha!";
			link.l1.go = "after_cave_gladys_1";
			locCameraFromToPos(-0.62, 1.93, -0.39, true, -2.46, -1.20, 1.01);	// Sinistra - постельная камера
		break;
		
		case "after_cave_gladys_1":
			dialog.text = "Pronta, meu capitão?";
			link.l1 = "Já?! Não, Helen, tenha piedade de mim, por favor. O aparecimento repentino da Gladys definitivamente não ajudou em nada o clima.";
			link.l1.go = "after_cave_gladys_2";
		break;
		
		case "after_cave_gladys_2":
			dialog.text = "Bem, o que se pode fazer... Embora...";
			link.l1 = "Não, não, abaixe as velas!";
			link.l1.go = "after_cave_gladys_3";
		break;
		
		case "after_cave_gladys_3":
			dialog.text = "Certo, então vamos apenas ficar juntos por um tempo. Nosso futuro é tão incerto e assustador, mas pela primeira vez em muito tempo, não tenho medo de mais nada. Sei que algum novo medo pode aparecer, mas hoje não. Hoje não, meu capitão.";
			link.l1 = "Hoje não, meu querido. Hoje não.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveFin");
		break;
		
		case "give_potions":
			dialog.text = "Permissão para falar, Capitão?";
			link.l1 = "Sim, Helen?";
			link.l1.go = "give_potions_1";
		break;
		
		case "give_potions_1":
			dialog.text = "Eu conheço esse Snake Eye – ele é um bom sujeito, mas um pouco estranho. Ele vive mandando as pessoas em missões sabe-se lá pra quê. Vejo que você também recebeu essa honra duvidosa.";
			if (!CheckAttribute(CharacterFromID("SnakeEye"), "quest.amulet")) {
				link.l1 = "Isso mesmo, preciso levar três amuletos para ele, senão não vai conseguir me ajudar a chegar até o esconderijo do Hawk. Mas sabe o que é engraçado? Eu já estava com eles! Será que ele sabia disso desde o começo?";
				link.l1.go = "give_potions_already";
			} else {
				link.l1 = "Isso mesmo, preciso trazer três amuletos para ele, senão não vai conseguir me ajudar a chegar até o esconderijo do Hawk. Agora não faço ideia de onde encontrá-los, e o tempo está se esgotando.";
				link.l1.go = "give_potions_3";
			}
		break;
		
		case "give_potions_already":
			dialog.text = "Ah, que pena! Fico feliz que você não tenha precisado correr atrás daqueles amuletos com os guardiões do farol, mas eu estava torcendo para, pelo menos uma vez, poder ser útil para você, para mostrar do que sou capaz.";
			link.l1 = "Besteira, Helen. Você não precisa me provar nada.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_3":
			dialog.text = "Eu vou te ajudar! Admito que, dessa vez, eu queria ser útil pra você, queria mostrar meu valor.";
			link.l1 = "Besteira, Helen. Você não precisa me provar nada.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_4":
			dialog.text = "Mesmo assim, quero te ajudar. Aqui, pegue a chave do meu quarto... digo, do baú no meu quarto! Não tem muita coisa, mas pode ser útil pra você. E... Charles, só tenta não cair na risada agora!";
			link.l1 = "Hum, eu não ia fazer isso. Vejo que você se interessa por essas coisas?";
			link.l1.go = "give_potions_5";
		break;
		
		case "give_potions_5":
			dialog.text = "Sou uma marinheira, capitão, assim como você. No nosso ramo, precisamos fazer de tudo para ter a sorte ao nosso lado.";
			link.l1 = "Obrigada, Helen. Eu agradeço de verdade.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GivePotionsKey");
		break;
		
		case "upgrade":
			dialog.text = "Querido, tenho um presente para você!";
			link.l1 = "Entendi, ali está – de pé e sorrindo!";
			link.l1.go = "upgrade_1";
		break;
		
		case "upgrade_1":
			dialog.text = "Ah-ha, pare com isso! Uma vez entreguei um bom lote de seda ao construtor naval local, então agora ele me deve uma reforma completa de um navio. Pensei em dar o 'Arco-Íris' para esse serviço, mas não era pra ser. Já o seu navio, por outro lado, poderia se beneficiar muito desse cuidado, não acha?";
			link.l1 = "De fato, um presente e tanto, Helen – é a sua cara!";
			link.l1.go = "upgrade_2";
		break;
		
		case "upgrade_2":
			dialog.text = "Fico feliz que tenha gostado. Visite-o quando quiser e diga que fui eu quem te mandou. Ele vai caprichar no serviço.";
			link.l1 = "Com certeza!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("HelenUpgradeShip1");
		break;
		
		case "give_sex":
			dialog.text = "Permissão para falar, meu capitão?";
			link.l1 = "Claro, meu querido.";
			link.l1.go = "give_sex_1";
		break;
		
		case "give_sex_1":
			dialog.text = LinkRandPhrase("Sua dama sente sua falta e exige sua atenção. Posso pedir que seja preparado um quarto para ela, e que você dedique um tempo a ela","Relatório: sua presença é requisitada numa cama da taverna local. Só cinco minutinhos do seu tempo, mas a tripulação espera que você fique um pouco mais!","Motim no navio, capitão! Fui encarregada de lhe entregar uma marca negra em particular. Venha comigo imediatamente!");
			link.l1 = "He-he, aham! Seu pedido foi atendido, Oficial Sharp!";
			link.l1.go = "give_sex_1_yes";
			link.l2 = "Hoje não, querido. Muita coisa está acontecendo agora.";
			link.l2.go = "give_sex_1_no";
		break;
		
		case "give_sex_1_yes":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			DialogExit();
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "give_sex_1_no":
			dialog.text = "Ah, e o que você queria que uma pobre garota fizesse, hein? Tudo bem, meu querido, fica pra outra vez então.";
			link.l1 = "";
			link.l1.go = "give_sex_2_no";
		break;
		
		case "give_sex_2_no":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			npchar.location = "None";
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			chrDisableReloadToLocation = false;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
		break;
		
		case "special_sex":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			SaveCurrentNpcQuestDateParam(npchar, "special_sex_date");
			
			dialog.text = "Ha! Não precisa pedir duas vezes! Claro, vamos!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "rainbow":
			dialog.text = "Vou te jogar no mar agora mesmo!";
			link.l1 = "Ei, ei, ei! Calma, querida!";
			link.l1.go = "rainbow_1";
		break;
		
		case "rainbow_1":
			dialog.text = "Vem aqui, seu canalha!";
			link.l1 = "Estou brincando, Helen! Não quis te ofender!";
			link.l1.go = "rainbow_2";
		break;
		
		case "rainbow_2":
			dialog.text = "Ah é? Que engraçadinho...";
			link.l1 = "Você é a mais linda, e eu te amo loucamente!";
			link.l1.go = "rainbow_3";
		break;
		
		case "rainbow_3":
			dialog.text = "Cai fora, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Rainbow");
			Achievment_Set("ach_CL_84");
		break;
		
		case "joan":
			dialog.text = "Você que é a descarada! Agradeça ao Jan por ter te dado respeito, senão ainda estaria abrindo as pernas pra qualquer um que passasse!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog2");
		break;
		
		case "joan_1":
			dialog.text = "Vagabunda! Vamos, Charles!";
			link.l1 = "";
			link.l1.go = "exit";
			
			ResetSound();
			SetMusic("helendrinking_shanty");
			pchar.questTemp.lockedMusic = true;
			AddDialogExitQuestFunction("HelenDrinking_GoToFort");
		break;
		
		case "cutlass_training":
			dialog.text = "A cutelo encaixa perfeitamente na minha mão! Eu nem sei como explicar... Sempre tive dificuldade com outros tipos de lâminas, como espadas e floretes. Mas esse cutelo é diferente! É uma sensação incrível! Obrigada, Charles!";
			link.l1 = "O destino sempre encontra um jeito de nos achar. Fico feliz por você, Helen!";
			link.l1.go = "exit";
			notification("Medium Weapons +", "Helena");
		break;
		
		case "brothel_found":
			dialog.text = "Guarde suas histórias para outra pessoa, comigo elas não colam. Eu pareço uma tola ingênua apaixonada? Quer dizer, EU estou completamente apaixonada por você, mas me chamar de tola já é demais\n Escute, querido, faça o que quiser, mas lembre-se de que você não vai encontrar mulher melhor do que eu. Se quiser procurá-la em bordéis, fique à vontade, mas aí eu desapareço da sua vida para sempre.";
			link.l1 = "Helen, eu...";
			link.l1.go = "brothel_found_1";
		break;
		
		case "brothel_found_1":
			dialog.text = "Eu entendo tudo, Charles. Você ama só a mim, e esses são apenas impulsos naturais. Sabe qual é o meu impulso natural? Respeito do meu homem. O amor pode não ser suficiente para uma mulher, querido. Vamos deixar esse mal-entendido de lado por enquanto, mas pense um pouco no que eu disse. Está bem?";
			link.l1 = "Tudo bem, Helen.";
			link.l1.go = "exit";
		break;
		
		case "refuse":
			dialog.text = "Você sabe como é. Deixa a garota esfriar a cabeça primeiro.";
			link.l1 = "Suspiro...";
			link.l1.go = "exit";
		break;
		
		// Тайна Порт-Рояля
		case "MysteryPortRoyal_Helena_1":
			dialog.text = "Francis... Eu me lembro dele. Ele sempre esperava minha chegada em Port Royal e era um romântico incorrigível. Eu gostava de passar tempo com alguém tão distante do mar – todos aqueles poemas e serenatas... Era algo novo. Um vislumbre de um mundo que eu nunca conheci. Francis era rico, inteligente e bonito – um verdadeiro partido. Qualquer moça da região teria enlouquecido por sua atenção, mas naquela época, eu estava mais preocupada em manter o Rainbow navegando.";
			link.l1 = "Parece que a alma sensível de um poeta não suportou sua rejeição. Em todas as cartas dele, ele só falava de você, lembrando dos lugares onde se encontraram. Posso te entregar tudo o que ele deixou, se quiser.";
			link.l1.go = "MysteryPortRoyal_Helena_2";
		break;
		
		case "MysteryPortRoyal_Helena_2":
			dialog.text = "Eu não sabia que ele estava doente. Agora tudo isso parece tão tolo. Quanto ao presente dele... Já tive o bastante de testamentos e heranças. Pode acreditar, tenho tudo o que preciso – e mais. É melhor você ficar com isso.";
			link.l1 = "De um jeito ou de outro, o legado dele ainda vai te servir no final – o que significa que, sem querer, acabei realizando o último desejo dele. Que história, hein.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.MysteryPortRoyal_Helena");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenDrinking_RobbedSvenson() {
	sld = &locations[FindLocation("SantaCatalina_houseS1_residence")];
	if (!CheckAttribute(sld, "private1.items.chest")) { 
		return true;
	}
	
	if (sti(sld.private1.items.chest) < 2) {
		return true;
	}
	
	return false;
}
