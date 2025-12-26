// диалог прочих НПС по квесту Саги
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

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
		
//---------------------------------------------Джимми в доме в Марун-Тауне------------------------------------
		case "Jimmy":
			dialog.text = "O que você quer? Não está vendo que estou de luto! Cai fora antes que eu te jogue escada abaixo!";
			link.l1 = "Então compre uma casa maior com escada pra isso. Aí a gente conversa sobre empurrar gente escada abaixo, herói...";
			link.l1.go = "Jimmy_1_1";
			link.l2 = "Por que você está tão chateado, Jimmy? Eu juro que nunca mais bebo rum na vida se isso não tiver a ver com alguma mulher bonita! Só uma mulher pra fazer um lobo do mar como você ameaçar os próprios amigos...";
			link.l2.go = "Jimmy_1_2";
		break;
		
		case "Jimmy_1_1":
			dialog.text = "Eu detesto gente meticulosa como você! Vocês sempre ficam com a melhor parte do bolo. Não me deixaram matar um metido, então vou descontar minha raiva em você!";
			link.l1 = "...";
			link.l1.go = "Jimmy_fight";
		break;
		
		case "Jimmy_fight":
			DialogExit();
			AddDialogExitQuestFunction("Saga_Jimmy_fight");
		break;
		
		case "Jimmy_1_2":
			dialog.text = "É mesmo?! Eu te conheço? Não me lembro de você, droga...";
			link.l1 = "Sou eu, "+pchar.name+"! Nos divertimos muito em Blueweld depois que você quase abriu aquele sujeito insolente no casaco. Qual era o nome dele mesmo? Já me esqueci... Enfim, eu não daria a mínima pros canhões da corveta dele se algum dia cruzar com ele no mar!";
			link.l1.go = "Jimmy_2";
		break;
		
		case "Jimmy_2":
			dialog.text = "O nome dele era Arthur! Arthur Donovan, capitão da corveta 'Arbutus'! Maldito canalha! Então você concorda que eu quase mandei ele pro inferno?";
			link.l1 = "Claro! Ele realmente não tinha chance nenhuma, mas seus amigos se meteram. Perdoe-os, eles só não queriam que você fosse enforcado pelo assassinato de um oficial da marinha.";
			link.l1.go = "Jimmy_3";
		break;
		
		case "Jimmy_3":
			dialog.text = "Ah! Se ao menos eu tivesse um navio! Aquele desgraçado pode ser facilmente encontrado perto de Antígua... ha! Te devo uma se você mandar ele pro fundo!";
			link.l1 = "Fechado, ha-ha! Aliás, a Rumba realmente vale todo esse sofrimento seu?";
			link.l1.go = "Jimmy_4";
		break;
		
		case "Jimmy_4":
			dialog.text = "Com certeza! Nunca conheci ninguém melhor do que ela. Mas ela só ri de mim. Todo mundo quer aquela sereia. Uns marinheiros me contaram em segredo que o nosso Jacob está procurando uma moça igualzinha à minha Rumba. Ele também a quer! Como é que eu vou obedecer às ordens dele agora?";
			link.l1 = "Fica quieto, amigo! As paredes têm ouvidos... E por que você acha que o Jackman está procurando a Rumba?";
			link.l1.go = "Jimmy_5";
		break;
		
		case "Jimmy_5":
			dialog.text = "Com certeza! Ele está procurando por um tal de Henry Carrasco e uma moça de vinte anos, loira de olhos azuis. Parece que uma Gladys Chandler de Belize é a responsável por ela.";
			link.l1 = "Espere! Gladys tem um sobrenome diferente. E ela é a mãe dela!";
			link.l1.go = "Jimmy_6";
		break;
		
		case "Jimmy_6":
			dialog.text = "Jackman é astuto! Você nunca vai pegá-lo desprevenido! Eu andei cortejando a Rumba por um tempo e descobri que a Gladys se casou com o Sean McArthur exatamente há vinte anos. E antes disso, ela morava em Belize. O primeiro marido dela se chamava Pete Chandler.\nO pobre Pete foi morto numa briga de bêbados. Dizem que foi o próprio McArthur o responsável, já que ele tinha um caso de amor com a rechonchuda Gladys naquela época. Ela ficou viúva com um bebê nos braços. A criança não sobreviveu muito tempo ao pai e morreu de febre logo depois.\nE só alguns meses depois, Gladys e Sean apareceram em Blueweld com uma menina, que diziam ser filha do McArthur. Então, como é que a Gladys poderia ter tido outro bebê tão rápido assim? Entendeu onde quero chegar?";
			link.l1 = "Você contou isso para mais alguém?";
			link.l1.go = "Jimmy_7";
		break;
		
		case "Jimmy_7":
			dialog.text = "Ainda não. Fique de boca fechada ou... bem, você me conhece!";
			link.l1 = "Sim, eu sei. Você tem uma língua podre que conta todos os seus segredos. Rumba fez bem em te mandar embora, tagarela...";
			link.l1.go = "Jimmy_8_1";
			link.l2 = "Claro! Eu vou ficar de boca fechada! Agora preciso ir. Adeus, Jimmy.";
			link.l2.go = "Jimmy_8_2";
		break;
		
		case "Jimmy_8_1":
			dialog.text = "O quê... o que você disse?!";
			link.l1 = "Você não vai conseguir contar isso pra mais ninguém...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_KillToJimmy_kino");
		break;
		
		case "Jimmy_8_2":
			DialogExit();
			AddDialogExitQuestFunction("Saga_Jimmy_DlgExit");
		break;
// <-- Джимми 
		
//-------------------------------------------корвет Донована, абордаж-----------------------------------------
		//Донован
		case "Donovan_abordage":
			PlaySound("Voice\English\saga\Artur Donovan.wav");
			dialog.text = "Seu monstro!";
			link.l1 = "Está falando sozinho, senhor?! Onde está a Rumba?";
			link.l1.go = "Donovan_abordage_1";
		break;
		
		case "Donovan_abordage_1":
			dialog.text = "Que Rumba? Eu não tenho vagabundos com apelidos no meu navio. Isto é um navio da Marinha inglesa!";
			link.l1 = "Não se faça de bobo comigo, Donovan. Você sabe muito bem de quem estou falando. Onde está a garota? Onde está a Helen? Responda, seu desgraçado imundo...";
			link.l1.go = "Donovan_abordage_2";
		break;
		
		case "Donovan_abordage_2":
			dialog.text = "Helen? Não tem puta de terra firme no meu navio, seu merda!";
			link.l1 = "Sem prostitutas em terra? Difícil de acreditar, já que uma delas está bem na minha frente neste exato momento... Acho que não faz sentido continuar nossa conversa. Morra, seu verme patético!";
			link.l1.go = "Donovan_abordage_3";
		break;
		
		case "Donovan_abordage_3":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterDonovanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Takehelen = "true";//признак, что абордировали судно
		break;
		
		//наш матрос
		case "Tempsailor":
			dialog.text = "Capitão, nós revistamos todas as cabines e o porão de carga, como o senhor mandou. Encontramos uma garota acorrentada no porão...";
			link.l1 = "Que canalha! Bem que eu imaginei... Você já soltou a garota?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Certamente, Capitão. Ela foi trazida em segurança para o seu navio.";
			link.l1 = "Muito bem! Leve-a para a minha cabine, quero falar com ela assim que terminarmos aqui.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Sim, senhor, Capitão!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
		break;
		//<-- абордаж корвета Донована
		
//----------------------------------------поиск Энрике Гонсалеса, Картахена----------------------------------
		//фальшивый Гонсалес №1, дом
		case "GonsalesA":
			dialog.text = "Quer alguma coisa?";
			link.l1 = "Olá, Carrasco! O Capitão Butcher manda lembranças.";
			link.l1.go = "GonsalesA_1_1";
			link.l2 = "Meu nome é Charles de Maure. Estou procurando por Enrique, filho da senhora Gonzales, a pedido de uma velha amiga dela. Acredito que seja você...";
			link.l2.go = "GonsalesA_2_1";
		break;
		
		case "GonsalesA_1_1":
			dialog.text = "Que diabos! Eu não conheço nenhum Açougueiro!";
			link.l1 = "Vamos, Henry. Me diga por que os piratas do Jackman estão atrás de você e eu não vou te machucar.";
			link.l1.go = "GonsalesA_1_2";
		break;
		
		case "GonsalesA_1_2":
			dialog.text = "Socorro! Piratas! Assassinato!";
			link.l1 = "Cale a boca, idiota! Metade da cidade vai aparecer aqui por causa dos seus gritos. Ah, é isso que você quer?!";
			link.l1.go = "GonsalesA_1_fight";
		break;
		
		case "GonsalesA_1_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesA");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesA_2_1":
			dialog.text = "Hm... Senhor, o senhor deve estar enganado. Eu cresci em uma família estrangeira, não me lembro da minha mãe biológica. Adotei o sobrenome do meu tutor. Não sei o nome da minha mãe, mas duvido que fosse Gonzales. Pode perguntar sobre mim, qualquer morador antigo vai confirmar o que digo. Meu padrasto era um homem conhecido, ele não tinha filhos próprios, então herdei esta casa e...";
			link.l1 = "Me desculpe. Parece que eu estava enganado. Adeus.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesA_3_1";
			else link.l1.go = "GonsalesA_2_2";
		break;
		
		case "GonsalesA_2_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "17");
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesA_3_1":
			dialog.text = "Acho que não.";
			link.l1 = "Com licença?";
			link.l1.go = "GonsalesA_3_2";
		break;
		
		case "GonsalesA_3_2":
			dialog.text = "Sabe, recentemente nossa colônia foi brutalmente atacada por piratas. Acredito que já tenha ouvido falar disso? Por causa desse ataque, muita gente sofreu. Eu saí ileso, mas o negócio que herdei está passando por tempos difíceis agora. E o responsável por toda essa desgraça é o líder desses piratas, um canalha chamado Charlie Prince.";
			link.l1 = "Sinto muito, mas o que isso tem a ver comigo?";
			link.l1.go = "GonsalesA_3_3";
		break;
		
		case "GonsalesA_3_3":
			dialog.text = "Ha-ha, olha só pra esse cordeirinho inocente! Acho que você deveria cobrir meus prejuízos, já que é o responsável por eles. Quinze mil pesos me deixam satisfeito. E eu finjo que você nunca esteve na minha casa.";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "Como vocês são rancorosos... Aqui está o seu dinheiro. E lembrem-se, se alguém descobrir que estive nesta cidade, eu volto para acertar com vocês.";
				link.l1.go = "GonsalesA_3_4";
			}
			link.l2 = "Quinze mil? Hm... Não acho que sua vida valha tanto assim. Então, acho que sai mais barato simplesmente te eliminar pra você não sair por aí falando demais.";
			link.l2.go = "GonsalesA_3_5";
		break;
		
		case "GonsalesA_3_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "171");
		break;
		
		case "GonsalesA_3_5":
			dialog.text = "Guardas! Piratas! Assassinato!";
			link.l1 = "Cala a boca, seu idiota!";
			link.l1.go = "GonsalesA_3_6";
		break;
		
		case "GonsalesA_3_6":
			DialogExit();
			iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2;
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SpSold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, iTemp, true);         
				LAi_SetWarriorType(sld); 
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
			sld = GetCharacter(NPC_GenerateCharacter("SpOfficer", "off_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 100, 100, "blade_13", "pistol6", "bullet", 150);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesAK");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		// <-- участвовал в событиях Картахены
		
		// фальшивый Гонсалес №2, улицы
		case "GonsalesB":
			PlaySound("Voice\English\citizen\Pirati v Gorode-08.wav");
			dialog.text = "Vejo que gostou do meu sabre. Posso vender pra você, se quiser. Não vou pedir muito, estou morrendo de vontade de um gole de rum e meus bolsos estão vazios.";
			link.l1 = "E por que diabos eu precisaria disso? O Diabo da Floresta pediu para eu te mandar lembranças.";
			link.l1.go = "GonsalesB_1_1";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = "Bem, sim. Você tem uma bela cutelo, de fato. Quanto custa?";
				link.l2.go = "GonsalesB_2_1";
			}
		break;
		
		case "GonsalesB_1_1":
			dialog.text = "Ele teria feito melhor se tivesse me dado uns duzentos pesos em vez disso!";
			link.l1 = "Então você conhece o Svenson?";
			link.l1.go = "GonsalesB_1_2";
		break;
		
		case "GonsalesB_1_2":
			dialog.text = "Vai se foder e foda-se o seu Svenson, manda ele pro diabo. Pro diabo da floresta ou do mar, tanto faz pra mim. Se você não quer ajudar um homem doente comprando o sabre dele, então eu enfio essa merda no seu rabo de graça.";
			link.l1 = "Sério? Quero ver como você vai fazer isso, seu merda!";
			link.l1.go = "GonsalesB_1_fight";
		break;
		
		case "GonsalesB_1_fight":
			chrDisableReloadToLocation = true;
			DialogExit();
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesB");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesB_2_1":
			dialog.text = "Vejo que você entende do assunto! Mil pesos e é seu.";
			link.l1 = "Feito!";
			link.l1.go = "GonsalesB_2_2";
		break;
		
		case "GonsalesB_2_2":
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(pchar, "blade_10");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "Existem apenas duas espadas como esta em Cartagena – a minha e a do velho Alvares, do farol. Mas ele não vende a dele. É um hipócrita, sinto o cheiro de ex-pirata de longe. Aquela lâmina é um tipo de talismã pra ele.  Parece que o pobre coitado lamenta coisas que preferia esquecer. Deve ser por isso que vai à igreja todo mês, atormentado por pecados que não deixam ele dormir.";
			link.l1 = "E eu vejo que você também tem uma certa história. Deve ser de você que o Svenson estava falando. Ele pediu para te mandar lembranças caso eu te encontrasse em Cartagena.";
			link.l1.go = "GonsalesB_2_3";
		break;
		
		case "GonsalesB_2_3":
			dialog.text = "Svenson? Nunca ouvi falar dele. Meu nome é Enrique Gallardo. Mas se esse Svenson tiver uma garrafa de rum pra mim, posso ser o Henry pra ele. Me chame do que quiser, só não me chame pra jantar depois da hora. Então, vamos ou não?";
			link.l1 = "Hoje não. Svenson está longe, mas a taverna está logo ali. Seus bolsos não estão mais vazios, então se cuida, Enrique.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesB_3_1";
			else link.l1.go = "GonsalesB_2_4";
		break;
		
		case "GonsalesB_2_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "19");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesB_3_1":
			dialog.text = "Elas não estão completamente cheias, ainda. Eu quero mais. E você vai me pagar.";
			link.l1 = "Estou perplexo... Você não valoriza a própria vida? Vai tentar me roubar bem no meio da cidade? E logo depois de ter me vendido sua arma?";
			link.l1.go = "GonsalesB_3_2";
		break;
		
		case "GonsalesB_3_2":
			dialog.text = "Não, você vai me pagar pessoalmente. E sabe por quê?";
			link.l1 = "Curioso para ouvir.";
			link.l1.go = "GonsalesB_3_3";
		break;
		
		case "GonsalesB_3_3":
			dialog.text = "Eu te reconheci. Eu estava nas masmorras por causa de uma briga de bar na taverna quando seus homens invadiram a prisão e mataram todos os guardas. Consegui alcançar o corpo do guarda com as chaves e escapei para as ruas. A cidade estava em chamas, cadáveres, sangue e fumaça de pólvora por toda parte... Igualzinho a um abordo! E através daquela fumaça, vi você saindo da residência do governador. Poético, não acha? Yo-ho-ho, olá, Príncipe Charlie!";
			link.l1 = "Pare de gritar desse jeito! Sabendo o que você sabe, você menos ainda deveria tentar arrancar dinheiro de mim. Você tem ideia do que eu posso fazer com você?";
			link.l1.go = "GonsalesB_3_4";
		break;
		
		case "GonsalesB_3_4":
			dialog.text = "No meio da cidade que você já assaltou? Você não pode fazer nada. Então, para concluir... vamos fazer o seguinte: você me dá... digamos, dez mil pesos agora mesmo. Acho que isso vai bastar por um mês. E você segue seu caminho! Seja para o seu querido Henry, para o Svenson, ou para qualquer outro diabo que você escolher... E se não fizer isso, basta eu gritar, e eles vão te arrastar para uma câmara pessoal especialmente preparada, cheia de instrumentos de tortura.";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Droga, pega seus dez mil e desapareça da minha frente! E, por Deus, que eu não te veja de novo.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "Chega, já cansei disso. Sua arma agora é minha, então você não tem a menor chance, verme.";
			link.l2.go = "GonsalesB_3_7";
			link.l3 = "Haha, você é bom! Sabe de uma coisa? Qualquer outro já teria levado uma faca do ventre à garganta. Mas gente como você, eu preciso por perto. Que tal isso: eu te dou dez mil pesos, devolvo seu 'Enforcado' e ainda te pago mais três mil por mês — deve dar pra bebida — e você vira um hóspede no meu navio.";
			link.l3.go = "GonsalesB_3_9";
		break;
		
		case "GonsalesB_3_5":
			dialog.text = "Tá bom, tá bom, já estou indo! Boa sorte na sua busca, Charlie Príncipe!";
			link.l1 = "...";
			link.l1.go = "GonsalesB_3_6";
		break;
		
		case "GonsalesB_3_6":
			AddMoneyToCharacter(pchar, -10000);
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "191");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		case "GonsalesB_3_7":
			dialog.text = "Guardas! Guardas!!! É o Charlie Prince!!!";
			link.l1 = "Seu desgraçado!";
			link.l1.go = "GonsalesB_3_8";
		break;
		
		case "GonsalesB_3_8":
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			LAi_group_AttackGroup("Spain_citizens", LAI_GROUP_PLAYER);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "192");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
		break;
		
		case "GonsalesB_3_9":
			dialog.text = "Você está sugerindo que eu entre para a sua tripulação?";
			link.l1 = "Exatamente. Mas essa é uma oferta única. Então, o que me diz? Aceita, ou eu arranco suas tripas. Você realmente acha que pode chantagear Charlie Prince assim tão fácil, acha mesmo?";
			link.l1.go = "GonsalesB_3_10";
		break;
		
		case "GonsalesB_3_10":
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 && makeint(pchar.reputation.nobility) < 48)
			{
				dialog.text = "Diabo! O próprio Charlie Prince está me oferecendo um lugar na tripulação dele! Maldição, eu aceito! Me devolva minha espada e dez mil pesos. Nunca imaginei que as coisas acabariam assim!";
				link.l1 = "Aqui. E fique de boca fechada: ninguém nesta cidade precisa saber quem eu sou, entendeu?";
				link.l1.go = "GonsalesB_3_11";
				break;
			}
			if(makeint(pchar.reputation.nobility) > 47)
			{
				dialog.text = "Não. Você pode até ser um capitão decente, mas me parece que é meio certinho demais. Sim, já fez os espanhóis tremerem de medo uma vez, atacando Cartagena com ousadia – mas tudo isso só foi possível com a ajuda do Marcus Tyrex. Você não tem coragem de saquear de verdade sozinho. Então, desembolsa a grana!";
			}
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
			{
				dialog.text = "Não. Você até tem fama de pirata, mas como capitão não parece grande coisa. Só conseguiu saquear a colônia com a ajuda do Marcus Tyrex – sozinho, não teria coragem nem de abordar uma escuna caindo aos pedaços. Então, desembolsa logo o dinheiro!";
			}
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Droga, pega seus dez mil e desapareça da minha frente! E, por Deus, que eu não te veja de novo.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "Chega, já cansei disso. Sua arma agora é minha, então você não tem a menor chance, verme.";
			link.l2.go = "GonsalesB_3_7";
		break;
		
		case "GonsalesB_3_11":
			dialog.text = "Entendi, não sou idiota.";
			link.l1 = "Bom.";
			link.l1.go = "GonsalesB_3_12";
		break;
		
		case "GonsalesB_3_12":
			DialogExit();
			AddMoneyToCharacter(pchar, -10000);
			LAi_RemoveLoginTime(npchar);
			npchar.quest.OfficerPrice = 3000;
			npchar.reputation.nobility = 30;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			npchar.loyality = MAX_LOYALITY;
			GiveItem2Character(npchar, "blade_10");
			EquipCharacterByItem(npchar, "blade_10");
			TakeItemFromCharacter(pchar, "blade_10");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			AddQuestRecord("Saga", "193");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
		break;
		// <-- участвовал в событиях Картахены
		
		//настоящий Гонсалес - Ортега, маяк
		case "Ortega":
			dialog.text = "Não estou esperando nenhuma visita, nem hoje nem em qualquer outro dia. O que você quer?";
			link.l1 = "Olá, Carrasco. O Diabo da Floresta me enviou. Ainda bem que te encontrei antes dos homens do Jackman. Os capangas dele estão te procurando por todo o Caribe. Sorte sua, Henry, só o Svenson sabe onde você nasceu. Ele pediu pra eu te avisar.";
			link.l1.go = "Ortega_1";
		break;
		
		case "Ortega_1":
			dialog.text = "Agora entendo... Então, parece que Svenson ainda está vivo e não esqueceu seu velho amigo. Muito sangue já correu desde a primeira vez que o vi, um novato de pé num brigue avariado... A vida passou rápido demais e não me resta muito tempo\nEu queria morrer de causas naturais neste fim de mundo, longe dos homens e perto do mar. Mas se Jackman voltou ao Caribe, ele não vai me deixar em paz. Não foi minha culpa, mas devo ao mestre dele. De qualquer forma, quem vai acreditar em mim agora.\nNão temo a morte, mas sim a dor. E Jackman entende muito de dor. Só de pensar nisso meu coração quase para e tudo começa a escurecer.";
			link.l1 = "Butcher foi enforcado há vinte anos, então você não precisa pagar suas dívidas a ninguém. Se tem medo do Jackman, pode passar sua dívida para mim. Acho que vai acabar encontrando ele de qualquer jeito.";
			link.l1.go = "Ortega_2";
		break;
		
		case "Ortega_2":
			dialog.text = "Não é fácil enforcar gente como o Açougueiro. O antigo carrasco de St. John's poderia te contar muitas histórias interessantes sobre mortos que voltaram do inferno. E Jacob foi muito bem ensinado pelo capitão dele, então nem sei de quem eu tenho mais medo.";
			link.l1 = "Por que o Jackman precisa de você?";
			link.l1.go = "Ortega_3";
		break;
		
		case "Ortega_3":
			dialog.text = "Eu tive que entregar ouro a uma viúva como pagamento por manter a filha do Açougueiro em segurança. Por que está me olhando assim? Sim, ela nasceu pouco antes do 'Neptune' afundar. Ele não conseguiu voltar a tempo para buscá-la, então me mandou cuidar do bebê e da mulher que tomava conta dela.";
			link.l1 = "O nome da zeladora era Gladys Chandler?";
			link.l1.go = "Ortega_4";
		break;
		
		case "Ortega_4":
			dialog.text = "Não se faça de bobo. Se Jackman está me procurando, é porque ele precisa da filha do Açougueiro. Você já deve saber que ele está atrás de uma mulher de Belize chamada Gladys e de sua filha adotiva. Seja honesto comigo e talvez eu confie em você.";
			link.l1 = "O que era para você dizer à Gladys?";
			link.l1.go = "Ortega_5";
		break;
		
		case "Ortega_5":
			dialog.text = "Nada. Eu devia mostrar a ela o anel do Açougueiro, era assim que ela saberia que eu era o mensageiro enviado pelo capitão. Também tinha que entregar um baú de dobrões para as necessidades do bebê. Precisei matar um desgraçado para pegar o anel. Isso me fez ficar mais um mês em Antígua.\nE quando finalmente cheguei a Belize, Gladys já tinha ido embora e a cidade tinha sido queimada e saqueada pelos espanhóis. Ela conseguiu vender a casa e fugir com o novo amante e a pequena Helen. Espero que ela tenha cuidado bem da menina e não a vendido para ciganos ou para um bordel.";
			link.l1 = "O nome da filha do Açougueiro era Helen, certo?";
			link.l1.go = "Ortega_6";
		break;
		
		case "Ortega_6":
			dialog.text = "Exato. Em homenagem à mãe do Açougueiro. Se você não tem medo de mortos-vivos e piratas te encarando com olhos vazios, então posso te dar o anel e o ouro. Eu nunca toquei neles. Estava morrendo de fome, mas não toquei. Faça com eles o que quiser. E em troca eu peço s...";
			link.l1 = "O que está acontecendo, Henry?!";
			link.l1.go = "Ortega_7";
		break;
		
		case "Ortega_7":
			dialog.text = "Vo... v... eu que...ro... ah!";
			link.l1 = "Não!";
			link.l1.go = "Ortega_8";
		break;
		
		case "Ortega_8":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			AddQuestRecord("Saga", "20");
			pchar.questTemp.Saga = "svenson1";
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "bucher_ring"); //перстень Бучера
			//таймер на возврат смотрителя
			SetFunctionTimerCondition("Saga_LightmanReturn", 0, 0, 10, false);
			//ставим прерывания, если ГГ наследил в городе
			if (CheckAttribute(pchar, "questTemp.Saga.Trap"))
			{
				pchar.quest.Saga_Trap.win_condition.l1 = "location";
				pchar.quest.Saga_Trap.win_condition.l1.location = "Mayak11";
				pchar.quest.Saga_Trap.function = "Saga_CreateTrapBandos";
				TraderHunterOnMap(true);
			}
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs");
			//pchar.questTemp.HelenDrinking = "end_henry";
		break;
		
		//бандиты в поисках Гонсалеса, маяк
		case "saga_trap":
			dialog.text = "A-ah, aí está o nosso amigo curioso! Finalmente encontrou o Gonzales? Muito bem, nos trouxe até ele... não precisamos mais de você. Rapazes, matem esse palhaço!";
			link.l1 = "Hora de morrer, tripas de caranguejo!";
			link.l1.go = "saga_trap_1";
		break;
		
		case "saga_trap_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			int n = makeint(MOD_SKILL_ENEMY_RATE/3);
			for (i=1; i<=3+n; i++)
			{	
				sld = characterFromId("sagatrap_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		//<-- поиск Гонсалеса, Картахена
		
//--------------------------------------------НПС по квесту Возвращение барона---------------------------------
		
		// доминиканский вождь
		case "DominicaHead":
			dialog.text = "U-ah! U-ah! O grande Kukulcán exige uma nova vítima! O-eh! O espírito de um poderoso guerreiro do passado veio à nossa aldeia para ser sacrificado ao grande Kukulcán! O-eh! Todos se curvem diante do espírito do grande guerreiro!";
			link.l1 = "(baixinho) Que diabos, onde é que eu estou?";
			link.l1.go = "DominicaHead_1";
			NextDiag.TempNode = "DominicaHead";
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A Comanche potion is used", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("You are feeling that your health is restored!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "DominicaHead_1":
			dialog.text = "O-eh! Grande guerreiro deseja ser devorado pelo grande Kukulcan! O sol está nascendo, as sombras estão encurtando! O grande Kukulcan logo despertará! Nós o levaremos até ele, ó poderoso guerreiro, e você continuará sua jornada pela terra dos ancestrais!";
			link.l1 = "(baixinho) Bobagem... Kukulcan de novo? Ei, chefe, eu vim em paz! Eu estou aqui para...";
			link.l1.go = "DominicaHead_2";
		break;
		
		case "DominicaHead_2":
			dialog.text = "O-eh! O grande guerreiro diz que deseja ser sacrificado a Kukulcan imediatamente. Oh, grande guerreiro! Vamos até Kukulcan agora e aguardamos sua chegada! Guerreiros! É uma grande honra para nós levar o espírito do ancestral a Kukulcan!";
			link.l1 = "(baixo) Idiota... Tudo bem, vou ter que ir com eles. Ainda bem que não me atacaram, eu não conseguiria me defender com isso aqui...";
			link.l1.go = "DominicaHead_3";
		break;
		
		case "DominicaHead_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1_back", "Saga_DominicaDollyReload", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
			}
		break;
		
		case "DominicaHead_4":
			dialog.text = "Viemos até Kukulcan, grande espírito ancestral. Logo o sol vai se pôr, as sombras vão crescer, e Kukulcan nos visitará. Espere, grande guerreiro...";
			link.l1 = "(baixo) Agora eu entendo, chefe de guerra indígena...";
			link.l1.go = "DominicaHead_5";
		break;
		
		case "DominicaHead_5":
			DialogExit();
			bDisableCharacterMenu = true;//лочим Ф2
			AddQuestRecord("BaronReturn", "7");
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_DominicaDollyWait", 5.0);
			pchar.questTemp.Saga.BaronReturn = "third_teleport";
		break;
		
		case "DominicaHead_6":
			dialog.text = "Kukulcan vive! Kukulcan está conosco! O grande guerreiro pode ser sacrificado a Kukulcan! Guerreiros, ajoelhem-se diante do grande espírito ancestral!";
			link.l1 = "(baixinho) Fique longe, chefe. Eu faço isso sozinho. Não é a primeira vez...";
			link.l1.go = "DominicaHead_7";
		break;
		
		case "DominicaHead_7":
			DialogExit();
			bDisableCharacterMenu = false;//разлочим Ф2
			AddQuestRecord("BaronReturn", "8");
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
			}
		break;
		
//----------------------------------------НПС по квесту Искушение Барбазона----------------------------------
		// капитан рыболовного баркаса, стыривший шелк, море
		case "BarbCapBarkas":
			dialog.text = "Como posso ajudá-lo, senhor?";
			link.l1 = "Então, então...  me diga, camarada, o que você está fazendo aqui?";
			link.l1.go = "BarbCapBarkas_1";
		break;
		
		case "BarbCapBarkas_1":
			dialog.text = "O que eu estou fazendo aqui? Sou pescador e estou pescando aqui. E por que diabos você está me interrogando desse jeito?";
			link.l1 = "Não minta para mim, camarada. Talvez você seja mesmo um pescador, mas não estava pescando aqui. Seda valiosa de um navio foi jogada ao mar, bem neste ponto. E só a sua presença aqui já me parece bastante suspeita.";
			link.l1.go = "BarbCapBarkas_2";
		break;
		
		case "BarbCapBarkas_2":
			dialog.text = "Que bobagem é essa? Que seda é essa de que você está falando?";
			link.l1 = "Que seda? Aquela chinesa... Não se faça de bobo! Escuta aqui: ou você pega a seda do seu porão agora mesmo e me entrega, ou eu mesmo vou pegar. Mas antes, meu grupo de abordagem vai cuidar de você e da sua tripulação. E então? Chamo meus homens?";
			link.l1.go = "BarbCapBarkas_3";
		break;
		
		case "BarbCapBarkas_3":
			dialog.text = "Não! Senhor, eu não sabia... Aqueles fardos estavam só boiando por aí, então eu resolvi...";
			link.l1 = "Leve a seda para o meu navio. Depressa!";
			link.l1.go = "BarbCapBarkas_4";
		break;
		
		case "BarbCapBarkas_4":
			dialog.text = "Sim, sim, claro. Vamos fazer isso agora mesmo, só não leve meu barco!";
			link.l1 = "Anda logo! Não tenho muito tempo...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_BarbBarkasSilk");
		break;
		
		case "BarbCapBarkas_5":
			dialog.text = "Aqui, trouxemos tudo o que encontramos – todos os nove fardos. Isso é tudo, eu juro...";
			link.l1 = "Tudo bem. Pode continuar pescando, mas não coloque os olhos nas coisas dos outros da próxima vez!";
			link.l1.go = "BarbCapBarkas_6";
		break;
		
		case "BarbCapBarkas_6":
			DialogExit();
			npchar.DontDeskTalk = true;
			npchar.lifeday = 0;
			LAi_SetStayType(npchar);
			pchar.quest.BarbBarkas_Sink.over = "yes"; //снять прерывание
			pchar.quest.BarbBarkas_Abordage.over = "yes"; //снять прерывание
			NextDiag.CurrentNode = "BarbCapBarkas_7";
			AddQuestRecord("BarbTemptation", "6");
			pchar.questTemp.Saga.BarbTemptation = "give_silk";
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "BarbCapBarkas_7":
			dialog.text = "Você já conseguiu o que queria. Eu não tenho mais nada! O que mais você quer?";
			link.l1 = "Relaxa, amigo. Estou indo embora.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BarbCapBarkas_7";
		break;
		
		// Моррель, капитан потопленного судна, тюрьма
		case "Morelle":
			dialog.text = "Se você foi mandado pelo Barbazon, diga a ele que eu não quero sair da prisão por conta própria. Prefiro esperar pelo julgamento. Até mesmo o cânhamo holandês no meu pescoço é melhor do que a bondade dele.";
			link.l1 = "Não se precipite. Seu navegador contou ao Jacques que você está morto. Ele me mandou encontrar a seda que você jogou no mar. Quanto dela estava no seu bergantim?";
			link.l1.go = "Morelle_1";
		break;
		
		case "Morelle_1":
			dialog.text = "A culpa foi minha, droga. O mensageiro trouxe nove fardos de seda para Barbazon. Mandei seguirem ele. Ele fez um escândalo, então tivemos que cortar sua garganta. Ele tinha mais três fardos escondidos, que peguei para mim e escondi no meu próprio esconderijo. Mas parece que chamamos atenção indesejada.  Nos acharam rápido, e uma patrulha holandesa estava esperando pelo 'Salt Dog' em mar aberto. Não conseguimos escapar. Pode ficar com a seda, se não contar nada sobre mim para o Barbazon. O esconderijo está na Praia de Grand Case, entre as pedras perto do beco sem saída. Duvido que eu vá precisar dela de novo.";
			link.l1 = "Certo. Não vou contar ao Barbazon que você ainda está vivo. Se o que dizem sobre ele for verdade, é melhor ser enforcado pelos holandeses. Ou talvez você tenha sorte e eles te condenem à trabalhos forçados.";
			link.l1.go = "Morelle_2";
		break;
		
		case "Morelle_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			// тайник - модель
			//int m = Findlocation("Shore40");
			//locations[m].models.always.Roll = "Roll_of_rolls";
			//Locations[m].models.always.Roll.locator.group = "quest";
			//Locations[m].models.always.Roll.locator.name = "quest1";
			pchar.quest.Saga_MorelGoods.win_condition.l1 = "locator";
			pchar.quest.Saga_MorelGoods.win_condition.l1.location = "Shore40";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator = "quest1";
			pchar.quest.Saga_MorelGoods.function = "Saga_SetMorelGoods";
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
		
		// Валет, брат Джекмана в Капстервиле
		case "valet":
			dialog.text = "Estou esperando o homem que sabe quando começará a caçada ao tubarão branco.";
			link.l1 = "A caçada começou.";
			link.l1.go = "valet_1";
		break;
		
		case "valet_1":
			dialog.text = "Finalmente! Agora preste atenção. Você vai ter que procurar Marcus Tyrex em La Vega e dizer a ele que o brigantine 'Separator' foi atacado perto da Ilha Turks e agora está escondido na Baía do Sul. O capitão está gravemente ferido e a tripulação espera por ajuda. Você resgatou um marinheiro do 'Separator' e ele contou tudo isso pra você. Agora ele está morto. Isso é tudo que você sabe. Entendeu?";
			link.l1 = "E por que você precisa de mim pra isso? Esperei tanto tempo só por isso...";
			link.l1.go = "valet_2";
		break;
		
		case "valet_2":
			dialog.text = "Você está sendo pago para fazer o seu trabalho, não para fazer perguntas. Mas você tem razão. Preciso te avisar que Tyrex não vai te deixar ir até ter certeza de que está dizendo a verdade. Mas, quando ele descobrir tudo, vai te pagar bem. Se conseguir fazer isso...";
			link.l1 = "Você está tentando me enganar, senhor... Por que não quer receber o agradecimento dele pessoalmente?";
			link.l1.go = "valet_3";
		break;
		
		case "valet_3":
			dialog.text = "Caramba! Não gosto dessa sua curiosidade! Um dia esse seu falatório ainda vai te levar direto pra cova.";
			link.l1 = "É, às vezes eu sou insuportável. Principalmente quando percebo que alguém está tentando me passar a perna. Não, camarada, agora quem manda aqui sou eu. Quem é o seu chefe, caramba? Responde, ou eu te faço falar!";
			link.l1.go = "valet_4";
		break;
		
		case "valet_4":
			dialog.text = "Seu... desgraçado! Barbazon vai pagar por isso, e a sua vida vai acabar, seu comedor de merda!";
			link.l1 = "Ha! Eu já esperava por isso. Prepare-se, canalha!";
			link.l1.go = "valet_5";
		break;
		
		case "valet_5":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_ValetDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "vensan":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				dialog.text = "Charlie Prince? O que você está fazendo aqui? A-argh, droga, foi você! Isso tudo é culpa sua!";
				link.l1 = "Relaxa, Bernie. Estou do seu lado. A emboscada foi eliminada, você e seu navio estão seguros.";
				link.l1.go = "vensan_8";
			}
			else
			{
				dialog.text = "Quem é você, diabos? Como chegou aqui? Saia agora, meu navio está cheio de explosivos e aqueles desgraçados na costa podem explodi-lo com um único disparo.";
				link.l1 = "Não se preocupe, senhor. A emboscada na praia já foi resolvida. Seu navio está seguro agora, desde que não acenda um cachimbo no convés, é claro. Qual é o seu nome?";
				link.l1.go = "vensan_1";
			}
		break;
		
		case "vensan_1":
			dialog.text = "Vincent. Bernard Vincent. E qual é o seu nome?";
			link.l1 = "Capitão "+GetFullName(pchar)+". Vou cortar essas cordas e te libertar...";
			link.l1.go = "vensan_2";
		break;
		
		case "vensan_2":
			LAi_SetStayType(npchar);
			dialog.text = "Oh... minha gratidão. Como eu poderia te agradecer?";
			link.l1 = "Ainda não acabou, senhor. Alguém da sua tripulação ainda está vivo?";
			link.l1.go = "vensan_3";
		break;
		
		case "vensan_3":
			dialog.text = "Três dezenas dos meus homens estão trancados no porão de carga...";
			link.l1 = "Solte-os e saia daqui imediatamente. ";
			link.l1.go = "vensan_4";
		break;
		
		case "vensan_4":
			dialog.text = "Mas...";
			link.l1 = "Não perca tempo, Bernard. Você pode me agradecer depois em La Vega... Tyrex talvez também me agradeça.";
			link.l1.go = "vensan_5";
		break;
		
		case "vensan_5":
			dialog.text = "Então, você não está aqui por acaso? Você sabia de tudo?";
			link.l1 = "Sim, eu sabia. Consegui descobrir o esquema do Jackman e os planos dele para matar o Marcus. Ah, peça para o Tyrex ficar quieto, a intromissão dele pode assustar o Jackman.";
			link.l1.go = "vensan_6";
		break;
		
		case "vensan_6":
			dialog.text = "Vou avisá-lo com certeza! Você já vai embora?";
			link.l1 = "Sim. E você também deveria se apressar.";
			link.l1.go = "vensan_7";
		break;
		
		case "vensan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto2", "none", "", "", "", 5.0);
			Ship_SetTaskRunaway(SECONDARY_TASK, GetCharacterIndex("Cap_Vensan"), GetMainCharacterIndex());
			pchar.questTemp.Saga.BarbTemptation.Vensan_free = "true";
			if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.vensan_attack"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
				else sld = characterFromId("Helena");
				sld.dialog.currentnode = "sea_bomb"; 
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			sld = characterFromId("Cap_Vensan");
			sld.lifeday = 1;
			sld.DontDeskTalk = true;
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "vensan_8":
			dialog.text = "Sério? Olha, me desculpa, irmão...";
			link.l1 = "Esquece. Deixa eu cortar as cordas e te soltar.";
			link.l1.go = "vensan_9";
		break;
		
		case "vensan_9":
			LAi_SetStayType(npchar);
			dialog.text = "Merda... não sinto minhas mãos...";
			link.l1 = "Bernie, há mais sobreviventes no navio?";
			link.l1.go = "vensan_10";
		break;
		
		case "vensan_10":
			dialog.text = "Trinta homens estão trancados no porão de carga...";
			link.l1 = "Solte-os e caia fora daqui. Agora!";
			link.l1.go = "vensan_11";
		break;
		
		case "vensan_11":
			dialog.text = "Mas...";
			link.l1 = "Vá para La Vega imediatamente. Conte tudo a Marcus sobre essa confusão, nos mínimos detalhes.";
			link.l1.go = "vensan_12";
		break;
		
		case "vensan_12":
			dialog.text = "Marcus te enviou?";
			link.l1 = "Ele não fez isso. Eu consegui descobrir o plano de um canalha. Ele queria eliminar o Marcus com essa intriga. Peça para ele ficar quieto e não se meter por enquanto... Depois eu mesmo vou explicar tudo para ele. E, por favor, diga para ele parar de ficar bravo comigo.";
			link.l1.go = "vensan_7";
		break;
		
 //--------------------------------------НПС по Завещанию Шарпа--------------------------------------------------
		// Устрица, Поль Моллиган
		case "molligan":
			dialog.text = "O que o senhor quer no meu navio?";
			link.l1 = "Bom dia, Paul. Seu nome é Paul Molligan, não é?";
			link.l1.go = "molligan_0";
		break;
		
		case "molligan_0":
			dialog.text = "Sim, sou eu. Como posso ajudar você?";
			link.l1 = "Meu nome é "+GetFullName(pchar)+" e Jan Svenson me enviou.";
			link.l1.go = "molligan_1";
		break;
		
		case "molligan_1":
			dialog.text = "Jan? A-ah, eu me lembro de você. Claro! Você tem visitado a casa dele com frequência ultimamente. Então, o que o Jan quer de mim?";
			link.l1 = "Você estava com tanta pressa de zarpar de Blueweld. Jan queria carregar seu navio com mais duzentos centos de mogno para entregá-los ao Lorde Willoughby em Bridgetown. Prepare sua embarcação, meus homens vão colocar o mogno no seu porão de carga.";
			link.l1.go = "molligan_2";
		break;
		
		case "molligan_2":
			dialog.text = "Mogno? O Jan disse isso? Hm. E por que você mesmo não entrega isso em Barbados? Por que eu?";
			link.l1 = "Porque é você quem vai até lá, não eu. Tenho uma tarefa urgente do Svenson, então não posso perder tempo indo até Bridgetown também. Além disso, Jan não confia em mim para tratar negócios com Lord Willoughby e quer que você cuide disso. Sinto muito. Agora vamos logo com o carregamento, preciso ir.";
			link.l1.go = "molligan_3";
		break;
		
		case "molligan_3":
			dialog.text = "Olha, não tenho nenhum espaço livre no meu porão de carga. Não vou conseguir fazer o que o Jan me pediu, embora eu queira.";
			link.l1 = "Sem quartos? Que estranho... Jan me disse que vocês tinham espaço livre.";
			link.l1.go = "molligan_4";
		break;
		
		case "molligan_4":
			dialog.text = "É verdade, mas o Jan não sabia que equipei a 'Ostra' com canhões mais pesados. Não consigo carregar mais carga do que já tenho. Então entrega a madeira em Barbados você mesmo, tá bom, camarada? Diz pro Jan que não consegui fazer isso. Lidar com o Willoughby é fácil: só encontrar com ele, entregar a carga e pegar o recibo. Moleza.";
			link.l1 = "Hm. Isso não estava nos meus planos... Vamos dar uma olhada no seu porão, certo? Meu imediato é ótimo em organizar cargas, ele vai conseguir acomodar as mercadorias aí e ainda deixar um espaço livre pra você...";
			link.l1.go = "molligan_5";
		break;
		
		case "molligan_5":
			dialog.text = "Amigo, não posso carregar mais mercadorias. Quer que eu jogue fora meus canhões e deixe a 'Ostra' desprotegida?";
			link.l1 = "Bem, se você está tão certo assim... Mas o Jan não vai gostar, lembre-se disso!";
			link.l1.go = "molligan_6";
		break;
		
		case "molligan_6":
			dialog.text = "Vou explicar isso para o Svenson, não se preocupe. Afinal, a culpa é dele—ele nem perguntou sobre a tonelagem do meu navio.";
			link.l1 = "Ah, agora vou ter que levar esses troncos até Barbados, droga... Até mais, camarada.";
			link.l1.go = "molligan_7";
		break;
		
		case "molligan_7":
			DialogExit();
			// ставим проверку скрытности
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > (10+hrand(50)))
			{
				pchar.questTemp.Saga.Molligan.friend = "true"; // будет шанс критического залпа картечью
				sTemp = "The scoundrel is still not suspecting a thing. I should get closer and shoot at him with grapeshot. A sudden strike will always win in any battle. ";
				log_Testinfo("Friends");
				AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
				AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			}
			else
			{
				pchar.questTemp.Saga.Molligan.enemy = "true"; // нападет
				sTemp = "";
				log_Testinfo("Enemies");
				AddCharacterExpToSkill(pchar, "Sneak", 150);//скрытность
			}
			AddQuestRecord("Testament", "7");
			AddQuestUserData("Saga", "sText", sTemp);
			NextDiag.CurrentNode = "molligan_8";
			npchar.DontDeskTalk = true; // patch-5
		break;
		
		case "molligan_8":
			dialog.text = "Estamos entendidos, não é?";
			link.l1 = "Sim, sim. Estou indo para o meu navio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "molligan_8";
		break;
		
	//-----------------------------------------НПС по Теням прошлого--------------------------------------------
		// Джим Бенсон, плешивая мэгги
		case "benson":
			dialog.text = "O que você quer de mim? Não me interesso por fofocas nem por jogos. E eu bebo meu rum sozinho. Além disso, estou de mau humor depois da minha última viagem.";
			link.l1 = "E o que de notável aconteceu durante a sua última viagem?";
			link.l1.go = "benson_1";
		break;
		
		case "benson_1":
			dialog.text = "Um homem bom confiou em mim e eu o joguei ao mar porque minha tripulação exigiu.";
			link.l1 = "E qual foi o crime dele?";
			link.l1.go = "benson_2";
		break;
		
		case "benson_2":
			dialog.text = "Sou novo por aqui e não conheço muita gente. Por isso acabei contratando aquele gordo de bom coração como cirurgião, sem saber nada sobre o passado dele. Os piratas começaram a nos perseguir desde que saímos de Barbados. Por que eles iriam querer minha casca de ovo? Só conseguimos escapar graças a uma ventania forte. Bebemos para comemorar. E o idiota do gordo não teve ideia melhor do que contar para todo mundo que provavelmente os piratas estavam atrás dele, porque ele era um ex-carrasco e sabia de coisas que não devia. Claro que minha tripulação ficou furiosa. Dá pra acreditar? Um carrasco a bordo, servindo de cirurgião! E ninguém queria se meter com piratas também... Então tive que deixar o pobre coitado em terra. A culpa é toda dele, não conseguia ficar de boca fechada. Mas fiquei com pena do matuto, ele era um médico excelente. Levou só um minuto para curar minha ressaca.";
			link.l1 = "Maldição! O nome do seu médico era Raymond Baker, certo?";
			link.l1.go = "benson_3";
		break;
		
		case "benson_3":
			dialog.text = "Sim. Exatamente. E como você sabe disso? Estava me seguindo?";
			link.l1 = "Não, não fui eu. Só preciso desse homem, ele é um ótimo médico. Onde vocês o deixaram em terra?";
			link.l1.go = "benson_4";
		break;
		
		case "benson_4":
			dialog.text = "Latitude 15 graus 28' norte, longitude 63 graus 28' oeste. Depressa, senhor! Ele ainda deve estar vivo e você vai me livrar da culpa se conseguir salvá-lo!";
			link.l1 = "Já estou levantando âncoras!";
			link.l1.go = "benson_5";
		break;
		
		case "benson_5":
			DialogExit();
			NextDiag.CurrentNode = "benson_6";
			AddQuestRecord("Shadows", "3");
			npchar.lifeday = 0;
			bQuestDisableMapEnter = false;
			pchar.quest.Saga_Shadows_Baker.win_condition.l1 = "location";
			pchar.quest.Saga_Shadows_Baker.win_condition.l1.location = "Dominica";
			pchar.quest.Saga_Shadows_Baker.function = "Saga_SetBakerBoat";
			DeleteAttribute(pchar, "Cheats.SeaTeleport");
		break;
		
		case "benson_6":
			dialog.text = "Capitão, depressa! Ele ainda deve estar vivo!";
			link.l1 = "Sim, sim, já estou indo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "benson_6";
		break;
		
	//---------------------------------------бандиты у джекмановского рудника-------------------------------
		case "mine_bandit":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Ei! Fique aí mesmo! Não se mexa. Este território está protegido!";
				link.l1 = "Não seja tão duro, amigo! Amigos! Jackman nos enviou. Precisamos chegar à mina. Ordem do patrão...";
				link.l1.go = "mine_attack";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ei! Fique aí mesmo! Não se mexa. Este território está protegido!";
				link.l1 = "Hm. Mas eu quero passar... Por que diabos você está me impedindo?";
				link.l1.go = "mine_bandit_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "A-ah, você de novo? Vejo que você não entende... Rapazes, fogo!!";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_bandit_0":
			dialog.text = "Vamos, ande logo!";
			link.l1 = "Tudo bem...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_bandit_0";
		break;
		
		case "mine_bandit_1":
			dialog.text = "Because the mine behind me is private property and I am here to stop any stranger like you from passing. You'd better turn around and leave this place, stranger. Our cannons are loaded with grapeshot; just one more step and you'll be turned into a wet puddle.";
			link.l1 = "Heh, entendi. Sua mina está bem protegida. Tudo bem, estou indo embora.";
			link.l1.go = "mine_bandit_exit";
			link.l2 = "Seu desgraçado! Vamos ver quem vai acabar feito uma poça!";
			link.l2.go = "mine_bandit_2";
		break;
		
		case "mine_bandit_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestReloadToLocation("Mine_02", "reload", "reload3", "");
		break;
		
		case "mine_bandit_2":
			dialog.text = "Eu te dei uma chance... Rapazes, fogo!!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_bandit_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsFire", 1.5);
		break;
		
		case "mine_banditx":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Ei! Cai fora! Esta área é restrita!";
				link.l1 = "Ei, calma, amigo! Jackman nos mandou. Precisamos chegar à mina. Ordem do patrão...";
				link.l1.go = "mine_attackx";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ei! Cai fora! Este território está protegido!";
				link.l1 = "Hm. E o que tem lá?";
				link.l1.go = "mine_banditx_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "A-ah, você de novo? Vejo que você não entende... Rapazes, fogo!!";
				link.l1 = "...";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_banditx_1":
			dialog.text = "Isso não te interessa. Cai fora ou a gente atira, juro!";
			link.l1 = "Calma. Eu já estou indo.";
			link.l1.go = "mine_banditx_exit";
			link.l2 = "Seu desgraçado! Vamos ver quem atira em quem!";
			link.l2.go = "mine_banditx_2";
		break;
		
		case "mine_banditx_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			DoQuestReloadToLocation("Mine_04", "reload", "reload3", "");
		break;
		
		case "mine_banditx_2":
			dialog.text = "Eu te dei uma chance... Mosquetes prontos! Fogo!!";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_banditx_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsxFire", 0.6);
		break;
		
		case "mine_attackx":
			dialog.text = "Sério? Então você deve saber a senha. Fale logo, mas vai se arrepender se estiver mentindo...";
			link.l1 = "Triton";
			link.l1.go = "mine_wrongx_password";
			link.l2 = "Neptuno";
			link.l2.go = "mine_attackx_1";
			link.l3 = "Centurion";
			link.l3.go = "mine_wrongx_password";
			link.l4 = "Harpoon";
			link.l4.go = "mine_wrongx_password";
		break;
		
		case "mine_attackx_1":
			dialog.text = "Certo. Mas você, amigo, veio pelo lado errado. Não te avisaram? Volte e pegue o caminho à esquerda do poço seco. Depois contorne o morro e lá você vai ver o portão principal.";
			link.l1 = "Não posso entrar aqui?";
			link.l1.go = "mine_attackx_2";
		break;
		
		case "mine_wrongx_password":
			dialog.text = "Galera, temos um espião! Mosquetes prontos! Fogo!!";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_attackx_2":
			dialog.text = "Não. Só pela entrada principal.";
			link.l1 = "Certo, camarada... Ei! Olha! Que diabos é aquilo em cima da paliçada?";
			link.l1.go = "mine_attackx_3";
		break;
		
		case "mine_attackx_3":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mine_banditx_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			sld = characterFromId("Svensons_sold_12");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
			LAi_ActorAnimation(sld, "shot", "Saga_MineBanditxDie", 1.0);
		break;
		
		case "mine_attack":
			dialog.text = "Sério? Então você deve saber a senha. Fale alto para eu ouvir. E se tentar me enganar, essa vai ser a última piada que você faz na sua vida.";
			link.l1 = "Triton";
			link.l1.go = "mine_wrong_password";
			link.l2 = "Neptuno";
			link.l2.go = "mine_attack_1";
			link.l3 = "Centurion";
			link.l3.go = "mine_wrong_password";
			link.l4 = "Harpoon";
			link.l4.go = "mine_wrong_password";
		break;
		
		case "mine_attack_1":
			dialog.text = "Certo. Pode seguir. O chefe do acampamento está na casa à esquerda da entrada da mina. Vá falar com ele.";
			link.l1 = "Tá bom, camarada...";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_wrong_password":
			dialog.text = "Galera, temos um espião! Canhões, fogo!!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_attack_2":
			DialogExit();
			locCameraFollowEx(true);
			NextDiag.CurrentNode = "mine_attack_3";
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetActorDialogAny2Pchar(npchar.id, "", 0.0, 0.0);
		break;
		
		case "mine_attack_3":
			dialog.text = "O que mais? Esqueceu de alguma coisa?";
			link.l1 = "Sim. Pediram para eu lhe enviar os melhores cumprimentos.";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "Para mim? Ha-ha! De quem?";
			link.l1 = "Jan Svenson, seu desgraçado!";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			DialogExit();
			AddDialogExitQuestFunction("Saga_MineAttack");
		break;
		
	// ----------------------------- диалоги НПС при штурме бандитского рудника -------------------------------
		case "Svensons_off":
			dialog.text = LinkRandPhrase("Vamos acabar com esses desgraçados!","Mal posso esperar para dar uma surra nesses canalhas!","Os capangas do Jackman não têm direito de estar no Western Main! Vamos expulsá-los daqui!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_off";
		break;
		
		case "Svensons_sold":
			dialog.text = LinkRandPhrase("Estamos prontos para lutar!","Vamos mostrar pra eles!","Eles nem sabem com quem estão se metendo!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_sold";
		break;
		
		case "gunner":
			PlaySound("Voice\English\evilpirates01.wav");
			dialog.text = "Comandante, o canhão está pronto. Está carregado com uma bomba, como você ordenou.";
			link.l1 = "Acho que ninguém está esperando a gente aqui... Hora de nos apresentarmos. Jan me disse que o acampamento deles fica atrás daquela colina. Você consegue chegar lá?";
			link.l1.go = "gunner_0_1";
		break;
		
		case "gunner_0_1":
			dialog.text = "Tranquilo, comandante. Vamos levantar um pouco o canhão, isso deve resolver... pronto.\nPrepare-se!.. Fogo!!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "1";
		break;
		
		case "gunner_0_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_Gunfire", 3.0);
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_1":
			dialog.text = "";
			link.l1 = "Hm. Randolf, você acha que acertamos alguma coisa? Gostaria de ouvir sua opinião.";
			link.l1.go = "gunner_1_1";
		break;
		
		case "gunner_1_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Comandante, acertamos alguma coisa ou alguém, mas não consigo dizer ao certo... essa maldita colina está bloqueando a visão. Vou mudar o ângulo.\nPronto! Fogo!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "2";
		break;
		
		case "gunner_2":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			dialog.text = "Ha! Olha, comandante! Tem fumaça! Droga, acertamos o celeiro de algum bandido! Hurra-aaah!";
			link.l1 = "Sim, estou vendo a fumaça... Já é uma vitória épica, sem dúvida. Recarregue o canhão e aponte para o caminho, parece que nossos convidados estão chegando. Vamos recebê-los como merecem!";
			link.l1.go = "gunner_2_1";
		break;
		
		case "gunner_2_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Sim, senhor, comandante! Carreguem a bomba! Tripulação do canhão a postos! Estopim pronto! Fogo ao meu comando!";
			link.l1 = "...";
			link.l1.go = "gunner_2_2";
			npchar.quest.canonada = "3";
		break;
		
		case "gunner_2_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_01", 6.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_3":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			PlaySound("Voice\English\evilpirates05.wav");
			dialog.text = "Ha-ha, isso deve ter doído!";
			link.l1 = "Não relaxa ainda! Carregue o canhão! Acho que eles ainda não tiveram o suficiente. Vem mais gente aí!";
			link.l1.go = "gunner_3_1";
		break;
		
		case "gunner_3_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");//
			dialog.text = "Sim, senhor, comandante! Carreguem uma bomba! Pronto! Atirem ao meu comando!";
			link.l1 = "...";
			link.l1.go = "gunner_3_2";
			npchar.quest.canonada = "4";
		break;
		
		case "gunner_3_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_02", 5.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_5":
			PlaySound("types\warrior04.wav");
			PlaySound("Voice\English\evilpirates06.wav");
			dialog.text = "Ha-ha-ha, os desgraçados estão fugindo! Carne de cachorro! A metralha está despedaçando eles daqui! Parece que não têm coragem de atacar de novo!";
			link.l1 = "Agora é a nossa vez. Randolph, você vai ficar aqui junto ao canhão. Atire algumas vezes no caminho, depois mire na fumaça – queime o esconderijo deles! Só não atire na gente.";
			link.l1.go = "gunner_5_1";
		break;
		
		case "gunner_5_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Sim, senhor comandante! Prepare o canhão! Carregue o projétil!";
			link.l1 = "Homens! Às armas! Sigam-me, ataquem! Hurra!!";
			link.l1.go = "attack";
		break;
		
		case "attack":
			DialogExit();
			n = Findlocation("mine");
			Locations[n].hidden_fire = true;
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			if (GetCharacterIndex("Svensons_sold_12") != -1 && pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=8; i++)
			{
				if (GetCharacterIndex("Ourmine_sold_"+i) != -1)
				{
					sld = characterFromId("Ourmine_sold_"+i);
					if (i == 1) sld.MusketerDistance = 10; 
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_NEITRAL);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_05Die");
			AddDialogExitQuest("MainHeroFightModeOn");	
			DoQuestCheckDelay("Saga_MineSetMusic", 0.3);
			// запускаем автобабахалку на 10 выстрелов
			iTotalTemp = 0;
			DoQuestCheckDelay("Saga_GunAutoFire", 7.0);
			bDisableCharacterMenu = false;//разлочим интерфейсы
			InterfaceStates.Buttons.Save.enable = true;//разрешим сохраняться
		break;
		
		case "convict":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = LinkRandPhrase("Não me machuque, eu não sou um deles! Mate os bandidos!","Liberta a gente, camarada! E acaba com todos eles!","Corte eles, amigo, corte eles! Faça-os morrer!");
				link.l1 = "Ha! Não se preocupe, é exatamente isso que estamos fazendo agora.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("A nossa escravidão acabou? Você vai nos libertar?","Heh, será que eu vivi mesmo pra ver esse dia?","Esses desgraçados sugaram todo o nosso sangue....");
				link.l1 = "Acho que logo você vai poder aproveitar sua liberdade, camarada...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "convict";
		break;
		
		// жена Яна Свенсона
		case "js_girl":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "É melhor o senhor ir embora daqui. Não abrigamos criminosos e não queremos problemas com as autoridades da colônia.";
				link.l1 = "Tudo bem, estou indo embora...";
				link.l1.go = "exit";
				NextDiag.TempNode = "js_girl";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				// Первый диалог с Элен
				if(startHeroType == 4)
				{
					dialog.text = "Ah, Helen. Você podia ter se vestido de forma mais decente antes de vir ver o Jan, em vez de mostrar pra ele quem você realmente é. Pena que ele não acredita em mim.";
					link.l1 = "E como exatamente eu sou? Ele me criou desde pequena e me conhece melhor do que ninguém. Não escondo nada dele. Sofro com esse calor desde criança, então precisei aprender a lidar com isso do meu jeito, só isso.";
					link.l1.go = "js_helen_ft";
					NextDiag.TempNode = "js_girl";
					NPChar.quest.meeting = "1";
					break;
				}
				dialog.text = TimeGreeting()+", senhor. Gostaria de ver Jan?";
				link.l1 = "Bom dia. Foi um prazer conhecê-la, senhorita?.. ";
				link.l1.go = "js_girl_1";
			}
			else
			{
				// заглушка элен
				if(startHeroType == 4)
				{
					dialog.text = "Jan está lá dentro. Pode ir, não tem nada pra ver aqui, e você já está me irritando.";
					link.l1 = "Também não estava muito a fim mesmo.";
					link.l1.go = "exit";
					NextDiag.TempNode = "js_girl";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Joan")) {
					dialog.text = "Grr!";
					link.l1 = "E boa saúde para você também, Sra. Svensson.";
					link.l1.go = "exit";
					break;
				}
				
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
				{
					dialog.text = TimeGreeting()+", Capitão "+GetFullName(pchar)+". Se você veio por causa do Jan, tenho que te decepcionar – ele não está aqui. Saiu para resolver um assunto importante.";
					link.l1 = "Droga! E eu preciso dele! Diga-me, senhora Svenson, ele lhe disse quando voltaria?";
					link.l1.go = "js_girl_3";
					break;
				}
				dialog.text = "A-ah, você de novo, Capitão "+GetFullName(pchar)+"... pode ir andando, Jan está lá em cima como sempre.";
				link.l1 = "Obrigada, senhora Svenson...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_1":
			dialog.text = "Senhora, Senhora Johanna Svenson.";
			link.l1 = "Capitão "+GetFullName(pchar)+".";
			link.l1.go = "js_girl_2";
		break;
		
		case "js_girl_2":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				dialog.text = "Capitão? Bem, fico feliz em recebê-lo na minha casa. Mas se veio por causa do Jan, tenho que decepcioná-lo – ele não está aqui. Saiu para tratar de um assunto importante.";
				link.l1 = "Droga! E eu preciso dele! Diga-me, dona Svenson, ele lhe disse quando voltaria?";
				link.l1.go = "js_girl_3";
				break;
			}
			dialog.text = "Capitão? Fico feliz em recebê-lo na minha casa. Meu marido está no segundo andar, no escritório dele. Suba, por favor.";
			link.l1 = "Entendo, Sra. Svenson...";
			link.l1.go = "exit";
			NPChar.quest.meeting = "1";
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_3":
			dialog.text = "Não. Ele nem me disse a data exata de quando voltaria, porque nem ele sabe quanto tempo a busca vai durar.";
			link.l1 = "Me desculpe por interromper, mas eu realmente preciso dele... Que busca ele está fazendo?";
			link.l1.go = "js_girl_4";
		break;
		
		case "js_girl_4":
			dialog.text = "Vou te contar. A encantadora Helen, também conhecida como Rumba, filha do falecido amigo dele, Sean McArthur, desapareceu. Jan trata essa jovem endiabrada como se fosse sua própria filha. Ela lembra a ele um antigo amor, que tinha o mesmo temperamento impulsivo. Pelo menos, é esse o motivo da atração dele, eu acho.   De qualquer forma, a garota sumiu há uma semana junto com sua escuna, a 'Rainbow', e toda a tripulação. Sean McArthur ensinou tudo sobre navegação para ela, e a 'Rainbow' foi deixada para ela em testamento. E agora ela anda por aí se fazendo de capitã...";
			link.l1 = "O que será que aconteceu com ela?";
			link.l1.go = "js_girl_5";
		break;
		
		case "js_girl_5":
			dialog.text = "Quem sabe... Uma semana não é tanto tempo assim, mas a viúva McArthur está convencida de que algo aconteceu com a filha, e conseguiu convencer o Jan disso também. Ele reuniu seus homens e começou a procurá-la pessoalmente, mas até agora sem sucesso. Pessoalmente, acho que a Helen está bem e que o Jan só está se martirizando à toa.\nEle deu ouvidos demais às bobagens daquela velha gorda e entrou em pânico. Muito provavelmente, a garota está se divertindo com outro namorado neste exato momento, longe de olhos curiosos, em algum lugar seguro. Ela vai voltar assim que matar a saudade.";
			link.l1 = "Johanna, onde posso encontrar a Gladys? Quero falar com ela...";
			link.l1.go = "js_girl_6";
		break;
		
		case "js_girl_6":
			dialog.text = "A casa dela fica perto do cais, à esquerda. Mas provavelmente ela não está lá. Ela passa os dias em cima dos muros do forte, procurando pela filha querida.";
			link.l1 = "Entendi. Muito obrigado pela sua informação!";
			link.l1.go = "js_girl_7";
		break;
		
		case "js_girl_7":
			DialogExit();
			NextDiag.CurrentNode = "js_girl_8";
			sld = characterFromId("Gladis"); //устанавливаем Глэдис на форт
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "js_girl_8":
			dialog.text = "Jan ainda não chegou, Capitão, então volte mais tarde.";
			link.l1 = "Entendi...";
			link.l1.go = "exit";
			NextDiag.TempNode = "js_girl_8";
		break;
		
		case "js_helen_ft":
			dialog.text = "You're always in heat, I'd say. You should go to church; I've barely ever seen you there.";
			link.l1 = "Minha consciência está limpa – não tenho nada pelo que pedir perdão. Ainda está ressentida porque ele ajudou a abastecer meu navio em vez de te comprar outro vestido, Joanna?";
			link.l1.go = "js_helen_ft_1";
		break;
		
		case "js_helen_ft_1":
			dialog.text = "Eu? Amargurado? Você não vale esse esforço. É só que tudo vem fácil demais pra você, e você não merece.";
			link.l1 = "Mas assim que consegui aquele navio, comecei a ganhar a vida por conta própria. E desde que ele te acolheu feito um gato perdido, você não trabalhou um dia sequer. Então, quem é que está vivendo às custas dele de verdade?";
			link.l1.go = "js_helen_ft_2";
		break;
		
		case "js_helen_ft_2":
			dialog.text = "Você continua falando assim e um dia vai acabar recebendo o que merece. Jan e Gladys já deviam ter te ensinado um pouco de respeito. Tá bom, fala logo o que veio falar – e sai da minha frente, Helen. Ele está lá dentro.";
			link.l1 = "Galinha estúpida. Claro, pode deixar.";
			link.l1.go = "exit";
		break;
		
		// хронометр Алекса
		case "Alexs_bandos":
			dialog.text = "Ei! O que você está fazendo aqui?";
			link.l1 = "Eu é que gostaria de perguntar o mesmo – o que você e seus amigos estão fazendo aqui, na minha masmorra?";
			link.l1.go = "Alexs_bandos_1";
		break;
		
		case "Alexs_bandos_1":
			dialog.text = "Ha! Sua masmorra? E desde quando ela é sua, seu desgraçado?";
			link.l1 = "O dia em que seu pai cometeu o erro de transar com sua mãe.";
			link.l1.go = "Alexs_bandos_2";
		break;
		
		case "Alexs_bandos_2":
			dialog.text = "Está procurando encrenca?";
			link.l1 = "Escuta aqui, camarada, estou te dando uma última chance de sair daqui. Esta masmorra é minha e não vou deixar qualquer um entrar assim, entendeu? Basta eu assobiar uma vez e metade dos piratas da Isla Tesoro vai aparecer aqui em menos de um minuto.";
			link.l1.go = "Alexs_bandos_3";
		break;
		
		case "Alexs_bandos_3":
			dialog.text = "Então vamos tentar calar essa sua boca!";
			link.l1 = "Ha-ha! Você é patético, seu lixo!";
			link.l1.go = "Alexs_bandos_4";
		break;
		
		case "Alexs_bandos_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Bermudes_Dungeon")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Alexs_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int iScl = 25+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Alexs_bandos_5", "mush_ctz_8", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl*2+50);
			ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "AlexClock_BandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "helendrinking_gypsy":
			dialog.text = "Espere um instante, falcão!";
			link.l1 = "Não é o melhor momento, querida.";
			link.l1.go = "helendrinking_gypsy_1";
		break;
		
		case "helendrinking_gypsy_1":
			dialog.text = "Ah, você está enganado, bonitão. Essa moça gosta de você, e dá pra ver que o sentimento é recíproco.";
			link.l1 = "Não é a melhor recomendação... Certo, o que você quer? Uma esmola?";
			link.l1.go = "helendrinking_gypsy_2";
		break;
		
		case "helendrinking_gypsy_2":
			dialog.text = "Quero te oferecer uma ajuda nessa empreitada difícil. Veja só! Uma caneca mágica e um unguento proibido. A caneca vai te ajudar com a bebida, e o unguento — nos assuntos do amor. O que vai escolher? Só dois mil!";
			link.l1 = "Não preciso de nada – já dei uma porção de prata para gente como você.";
			link.l1.go = "helendrinking_gypsy_refuse";
			if (sti(pchar.money) >= 2000) {
				link.l2 = "Unguento proibido, é isso? Bem, não sou nenhum santo, admito. Me dê aqui.";
				link.l2.go = "helendrinking_gypsy_fuck";
				link.l3 = "Uma caneca? Eu pareço um bêbado? Ah, quem eu quero enganar... Aceito sim!";
				link.l3.go = "helendrinking_gypsy_drink";
			}
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_refuse":
			dialog.text = "Bonito, mas tolo. Então voe, falcão.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_drink":
			dialog.text = "Ah, não esconda isso nos seus bolsos sem fundo! Voe, falcão, e não peque!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_01");
			Log_Info("Talisman 'Throat of cast iron' acquired!");
			PlaySound("interface\important_item.wav");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_fuck":
			dialog.text = "Ah, não esconda isso nesses bolsos sem fundo! Voe, falcão, e não peque!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_03");
			Log_Info("Talisman 'Cupid's Balm' acquired!");
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_joan":
			dialog.text = "Ah! Saia daqui, seu canalha! Quantas vezes eu já te disse para não entrar escondido na minha casa! E quem é esse aí?";
			link.l1 = "Senhora, nós já nos conhecemos.";
			link.l1.go = "helendrinking_joan_1";
		break;
		
		case "helendrinking_joan_1":
			dialog.text = "Monsieur de Maure? Ora, que maravilha! É assim que você faz negócios com meu marido?! Eu sabia! Avisei ao Jan: um dia essa descarada ia começar a desviar os homens dela! E o que você tem aí nas mãos?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog1");
		break;
		
		case "helendrinking_joan_2":
			dialog.text = "Wha-a-a-at?! How dare you, wretch?! You're not going anywhere; my husband will be here any moment now and he'll teach you how to talk to the elders!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog3");
		break;
		
		case "helendrinking_fort_officer":
			dialog.text = "O que está acontecendo aqui? Senhorita MacArthur! Eu tinha grande respeito pelo seu pai, e o senhor Svensson é nosso amigo... Mas você não se lembra de como tudo terminou da última vez?\nÉ decepcionante, palavra de oficial, decepcionante! Você poderia ter nos convidado!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog");
		break;
		
		case "helendrinking_fort_officer_1":
			dialog.text = "Obrigado pela sua hospitalidade, senhorita MacArthur. Deixe-me dizer que todos nós estamos muito felizes em vê-la de volta. O que aconteceu é um grande mistério, mas não é surpresa que a cidade já saiba. Ainda assim, posso garantir que ninguém vai fofocar. Peço desculpas sinceras pelo comportamento recente de um dos nossos capitães. E quero agradecer especialmente a você, senhor de Maure.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog3");
		break;
		
		case "helendrinking_fort_officer_2":
			dialog.text = "Vai ficar tudo bem, senhorita. Senhor de Maure, serei franco – apesar de Donovan agir como um verdadeiro canalha e bandido, a frota nunca vai condená-lo abertamente. Na verdade, é mais provável que até o defendam. Sua pequena expedição entrou nos relatórios e complicou bastante as relações entre nossos países. Ainda assim, considerando a influência do senhor Svensson, além das concessões notáveis que Capsterville fez a vocês, não há motivo para se preocupar.";
			link.l1 = "Isso é maravilhoso. Eu digo que devemos brindar a isso!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog1");
		break;
		
		case "helendrinking_poorman":
			dialog.text = "Com licença, por favor, e quanto ao trabalho?";
			link.l1 = "Você ainda está aqui?";
			link.l1.go = "helendrinking_poorman_1";
		break;
		
		case "helendrinking_poorman_1":
			dialog.text = "Caro senhor, para onde mais eu iria? Só fui ali me aliviar, acabei ouvindo sua conversa sentimental e fiquei um pouco tocado. Emocionalmente, quero dizer!";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.BoughtRainbow")) {
				link.l1 = "Meu Deus! Bem, já que dei minha palavra, não tem jeito. Vá, assuma o comando.";
				link.l1.go = "helendrinking_poorman_bought";
			} else {
				link.l1 = "Não tenho trabalho para você, senhor.";
				link.l1.go = "helendrinking_poorman_notbought";
			}
		break;
		
		case "helendrinking_poorman_bought":
			dialog.text = "Sim, senhor, Capitão!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helendrinking_poorman_notbought":
			dialog.text = "Que pena! De qualquer forma, obrigado pela bebida, Capitão!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helensleep_amelia_mary":
			dialog.text = "In nomine Patris et Filii et Spiritus Sancti... entre, meu filho.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Oi, Madre Amélia. Você também vai gritar comigo?";
				link.l1.go = "helensleep_amelia_mary_know";
			} else {
				link.l1 = "Desapareça! Que pesadelo é esse? O que está acontecendo? Estou sonhando?";
				link.l1.go = "helensleep_amelia_mary_notknow";
			}
		break;
		
		case "helensleep_amelia_mary_know":
			dialog.text = "Não, meu falcãozinho. E perdoe o Jan – o coitado se exaltou. Mas sim, quero te dar uma bronca. Por que veio à igreja? Para se arrepender dos seus pecados? Ou estava atrás da ruiva?";
			link.l1 = "Nem eu sei direito...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Você também a viu? Ela chamou minha atenção.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_mary_notknow":
			dialog.text = "Desapareça. Já devíamos ter nos encontrado, mas você está enrolando tudo. Por que veio à igreja? Para se arrepender dos seus pecados? Ou estava atrás da ruiva?";
			link.l1 = "Nem eu sei direito...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Você também a viu? Ela chamou minha atenção.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen":
			dialog.text = "Bom dia, meu falcão. A recepção ainda não começou, por favor, aguarde na fila.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Olá, Sua Excelência. Vai gritar comigo também?";
				link.l1.go = "helensleep_amelia_helen_know";
			} else {
				link.l1 = "Desapareça! Que pesadelo é esse? O que está acontecendo? Estou sonhando?";
				link.l1.go = "helensleep_amelia_helen_notknow";
			}
		break;
		
		case "helensleep_amelia_helen_know":
			dialog.text = "No, my falcon. And forgive Jan, the poor man got worked up. No need to scold you; you did everything right - didn't go after the red-haired one to the church. Good boy!";
			link.l1 = "Ser elogiado é bom. Principalmente quando fica claro o motivo.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Você também a viu? Ela chamou minha atenção.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen_notknow":
			dialog.text = "Desapareça. Já devíamos ter nos encontrado, mas você está enrolando tudo. Venha cá, vou te elogiar – você não correu atrás da ruiva até a igreja. Bom garoto!";
			link.l1 = "Ser elogiado é bom. Principalmente quando fica claro o motivo.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Você também a viu? Ela chamou minha atenção.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia":
			dialog.text = "Não vou te aborrecer com os detalhes, bobo, mas vou te dizer isto: você está destinado a ser alguém grandioso. Vai causar muito mal, mas muito mais bem. Só que a felicidade não te é garantida. Felicidade, meu falcão, só é concedida a quem segue seu próprio caminho sem se desviar. E uma mulher fiel vai te ajudar a não se perder.  Você terá duas, e ambas vão te trazer felicidade, mas deve escolher a de cabelos claros.";
			link.l1 = "Por que seria? Eu decido por mim mesmo!";
			link.l1.go = "helensleep_amelia_1";
		break;
		
		case "helensleep_amelia_1":
			dialog.text = "Claro, escolha você mesmo, mas a loira é melhor. Foi assim que decidimos.";
			link.l1 = "Quem somos nós?";
			link.l1.go = "helensleep_amelia_2";
		break;
		
		case "helensleep_amelia_2":
			dialog.text = "A pobre coitada nem sabe seu verdadeiro nome. Diga-o, e ela será sua. Assim dizem.";
			link.l1 = "Eu não entendo mais nada.";
			link.l1.go = "helensleep_amelia_3";
		break;
		
		case "helensleep_amelia_3":
			dialog.text = "Ouviu essa batida? Abra a porta, e não erre.";
			link.l1 = "De fato, alguém está batendo... Entre!";
			link.l1.go = "exit";
			
			PlaySound("interface\knock.wav");
			
			AddDialogExitQuestFunction("HelenSleep_WakeUp");
		break;
		
		case "helendrinking_notifier":
			dialog.text = "Monsieur, o Sr. Svensson pediu que você lhe conceda um pouco do seu tempo.";
			link.l1 = "Droga, isso não é um bom sinal. Vou tentar, mas não prometo nada.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_End");
		break;
		
		case "islatesoro_pirate1":
			dialog.text = "Dia de sorte, rapazes! Eu disse que ela apareceria aqui mais cedo ou mais tarde, não disse? Muito bem, querida, entregue as armas e venha conosco.";
			link.l1 = "Vocês estão enganados, rapazes. Ela está comigo.";
			link.l1.go = "islatesoro_pirate1_1";
		break;
		
		case "islatesoro_pirate1_1":
			dialog.text = "Fique fora disso, ou eu atiro em você como um cachorro. Estão pagando bem pela garota, e nós somos homens famintos, sem nenhum princípio.";
			link.l1 = "Continue falando comigo nesse tom, e eu resolvo seu problema de fome de uma vez por todas.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroSpawnSecond");
		break;
		
		case "islatesoro_pirate1_2":
			dialog.text = "Você ficou maluco de vez, Lucky? Fomos nós que a encontramos primeiro! É bom que você tenha um ótimo motivo pra vir falar besteira pra mim!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog1");
		break;
		
		case "islatesoro_pirate1_3":
			dialog.text = "You're the rat here! We had just torn a big fat Spaniard apart; we can sit on our asses for a year!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog3");
		break;
		
		case "islatesoro_pirate2":
			dialog.text = "Ora, vejam só quem apareceu por aqui. Muito bem, o resto pode sair, e você, madame, venha conosco.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog");
		break;
		
		case "islatesoro_pirate2_1":
			dialog.text = "Nós somos mais numerosos e mais duros que você, dinamarquês. Precisa de outro motivo, seu rato de porão? Faz seis meses que você não vê um saque decente, e anda comendo as migalhas da mesa do Vuazie!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog2");
		break;
		
		case "islatesoro_pirate2_2":
			dialog.text = "";
			link.l1 = "Parece que não vai ter uma solução pacífica aqui.";
			link.l1.go = "islatesoro_pirate_a";
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB")) {
				link.l2 = "O que você disse? Sortudo? Ouvi um boato de que ele e Vuazie conspiraram para te passar dicas furadas. Isso explica sua maré de azar no mar.";
				link.l2.go = "islatesoro_pirate_b";
			}
			bOk = (!CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice")) || (pchar.questTemp.Mtraxx.Retribution.Choice == "bad");
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC") && CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold") && bOk) {
				link.l3 = "Estou cansado dessa farsa. Isla Tesoro, me escutem! Quem estava comigo em Cartagena?! Quem queimou Mérida ao meu lado?! Essas ratazanas ousam desafiar o próprio Charlie Prince! Vamos mostrar pra eles, rapazes!";
				link.l3.go = "islatesoro_pirate_c";
			}
		break;
		
		case "islatesoro_pirate_a":
			dialog.text = "Você ainda está aqui, água-viva? Certo, rapazes, vamos lá: amarrem o capitão, e a garota a gente resolve depois, entendido?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog4");
		break;
		
		case "islatesoro_pirate_a_1":
			dialog.text = "Claro, vamos derramar um pouco de sangue pelo menos. Hehe.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroA");
		break;
		
		case "islatesoro_pirate_b":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedB = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 60) {
				dialog.text = "O quê?! Droga, eu sabia que você estava de conluio com aquele canalha de óculos! Matem todos eles, rapazes, e depois pegamos a garota!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroB");
			} else {
				dialog.text = "O que você está tagarelando, capitão? Cai fora enquanto gente decente discute negócios.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "islatesoro_pirate_c":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedC = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 50) {
				DialogExit();
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroC");
			} else {
				dialog.text = "O que você está resmungando, Capitão? Eu já vi Charlie Prince, e você não chega aos pés dele. Cai fora enquanto as pessoas decentes estão discutindo negócios.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "francois":
			dialog.text = "Charles de Maure? Filho de Henri de Monpe?";
			link.l1 = "Está certo, monsieur. E quem é você?";
			link.l1.go = "francois_1";
		break;
		
		case "francois_1":
			dialog.text = "Colonel Francois de Tavanne. You may consider this a direct challenge, monsieur; the gauntlet for the duel has been laid. I don't even wish to dirty my hands with you, but I swear, my blade will taste your blood!";
			link.l1 = "Um duelo? Nesse caso, vai ter que se esforçar bem mais, coronel. Agora mesmo, só daria pra te confundir com um bandido, e por aqui, a conversa com esse tipo de gente é curta! Explique-se!";
			link.l1.go = "francois_2";
		break;
		
		case "francois_2":
			dialog.text = "Você seduziu minha esposa, monsieur! Enquanto eu derramava sangue pelo rei e pelo país, você... você se divertia com a minha esposa!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog");
		break;
		
		case "francois_3":
			dialog.text = "Silêncio, madame. Sua roupa ousada desonra a honra de qualquer mulher, embora você pareça bem adequada ao lado desse sedutor indigno de uma dama nobre!";
			link.l1 = "Ainda não é motivo suficiente para um duelo, coronel. E permita-me dizer que o senhor também não está se comportando de maneira digna aqui.";
			link.l1.go = "francois_4";
		break;
		
		case "francois_4":
			dialog.text = "Isso não é suficiente? Eu perguntei – no meu lugar agora poderiam estar uma dúzia de maridos nobres, senhor. Mas se quer saber os detalhes, então, para minha vergonha, confesso que uma das suas paixões foi Lulu de Tavann, a mais bela e honesta das mulheres!";
			link.l1 = "Lulu, você diz... E como ela está?";
			link.l1.go = "francois_5";
		break;
		
		case "francois_5":
			dialog.text = "Silêncio! Minha esposa, incapaz de suportar o tormento que você causou, faleceu recentemente! Passei quase um ano e uma fortuna para te encontrar, canalha! Chega de palavras! Ou aceita o desafio, ou eu te mato como um cachorro. Richard! Seja minha testemunha!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog2");
		break;
		
		case "francois_6":
			dialog.text = "Silêncio, senhor! Aceite o desafio ou perca o que resta da sua honra!";
			if (pchar.HeroParam.HeroType == "HeroType_1") {
				link.l1 = "Um duelo é um duelo. Não vou mentir, eu gosto disso. Capitão, avise ao Coronel que está na hora dele providenciar um caixão à altura.";
			} else {
				link.l1 = "Quer briga? Vai ter! Capitão, avise ao Coronel que já está na hora dele providenciar um caixão à altura.";
			}
			link.l1.go = "francois_duel";
			link.l2 = "Isto aqui não é a Europa, Coronel. Honra no Caribe é mais difícil de conquistar, mas também não se perde tão facilmente. Recuso seu duelo simplesmente porque não quero.";
			link.l2.go = "francois_refuse";
		break;
		
		case "francois_7":
			dialog.text = "Seu pai já está com um pé na cova, seu canalha! E eu vou garantir que ele saiba da sua covardia!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog7");
		break;
		
		case "richard":
			dialog.text = "Coronel, confirmo seu direito ao duelo, mas não vou permitir banditismo! Monsieur de Maure, sou o Capitão Richard Small. Está disposto a dar satisfação ao Coronel de Tavannes?";
			link.l1 = "Um momento, Capitão. Eu conhecia bem a Lulu... e ela... costumava trocar de admiradores com frequência, e a saúde dela era melhor que a minha... Como ela morreu, Coronel? Antes ou depois do seu retorno para casa?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog3");
		break;
		
		case "richard_1":
			dialog.text = "Por favor, François, deixe comigo. Monsieur de Maure, você foi desafiado. A sociedade dos oficiais de Blueweld reconhece que a exigência de satisfação do coronel de Tavannes é justificada. Aceite o desafio ou perca sua honra.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog5");
		break;
		
		case "richard_2":
			dialog.text = "Charles, por favor, somos cavalheiros aqui. Isso não é apropriado. O Coronel veio de tão longe só para te conhecer! É um escândalo!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog8");
		break;
		
		case "richard_3":
			dialog.text = "S-sim, claro, senhorita. Mas eu vou...";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "helen");
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath1");
		break;
		
		case "richard_4":
			dialog.text = "Capitão de Maure, o dia é seu! Não foi a luta mais justa, mas você defendeu sua honra hoje.";
			link.l1 = "Disse alguma coisa, Capitão? Acho que ainda consigo encaixar mais um duelo na minha agenda de hoje.";
			link.l1.go = "richard_5";
		break;
		
		case "richard_5":
			dialog.text = "Me desculpe, capitão. É só o nervosismo!";
			link.l1 = "Acho que sua presença aqui já não é mais necessária.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory");
		break;
		
		case "richard_duel":
			dialog.text = "Uma decisão justa! Mesmo que não tenha sido apresentada da maneira mais digna... Senhores! Vamos começar!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuel");
		break;
		
		case "alonso":
			dialog.text = "Capitão, talvez eu não entenda todas essas palavras bonitas que esses dignitários ficam jogando, mas olha, se alguém é chamado de covarde, normalmente não dá pra deixar passar. Bata nesse homem, Capitão, ou nossa tripulação vai começar a ficar preocupada.";
			link.l1 = "Querem sangue? A vida está sem graça, sem emoção? Vão ter o sangue de vocês, seus animais!";
			link.l1.go = "francois_duel";
			link.l2 = "Ah, coitadinho, estou morrendo de medo. Já terminaram aqui, senhores? Tenho mais o que fazer.";
			link.l2.go = "alonso_refuse";
		break;
		
		case "alonso_1":
			dialog.text = "It won't look good if our captain backs down from a public challenge. Just give that nobleman a good whack; we know you're great with a sword!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog9");
		break;
		
		case "alonso_refuse":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog6");
		break;
		
		case "francois_refuse":
			dialog.text = "Covarde! Libertino! Rato! Está com medo, canalha? Vocês todos viram isso?! Ricardo, eu vou matar ele de qualquer jeito!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog4");
		break;
		
		case "francois_duel":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuelDialog");
		break;
		
		case "francois_sit":
			dialog.text = "V-você canalha! Tudo bem, já estou acostumado a me machucar. Eu vou me recuperar, e...";
			link.l1 = "Parece uma ameaça, coronel. E eu não gosto nada de ameaças.";
			link.l1.go = "francois_sit_kill";
			link.l2 = "Assim que estiver recuperado, não se esqueça de contar para todos os oficiais como se machucou.";
			link.l2.go = "francois_sit_taunt";
		break;
		
		case "francois_sit_kill":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_FinishFrancois");
		break;
		
		case "francois_sit_taunt":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			Notification_Approve(true, "Helena");
			AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 300);
			AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 300);
			
			AddDialogExitQuestFunction("HelenDrinking_SpareFrancois");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenSleep_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}
